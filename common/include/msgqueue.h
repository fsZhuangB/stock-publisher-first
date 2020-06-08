#pragma once
#include <string>
#include "queue.h"
#include "utility.h"

namespace TD
{
    /**
    *@  定义模块间通信的消息队列类，用于上游策略模块与交易代理，以及交易代理内部通信，
    *   底层使用cdisruptor
    **/
    //基于cdisruptor的共享内存消息队列
    template <typename T>
    struct MsgQueue
    {
        struct vrt_queue *queue_addr = nullptr;     //控制块共享内存区地址
        T *data_addr = nullptr;                     //数据块共享内存区首地址
        int data_len = 0;                           //数据库块共享内存区大小
        int ctrl_shm_fd = -1;                       //控制块共享内存文件描述符
        int data_shm_fd = -1;                       //数据块共享内存文件描述符
        int id = -1;                                //队列id                          
        std::string name;                           //队列名字
        std::string data_name;                      //数据块区名字
        std::string ctrl_name;                      //控制块区名字

    public:
        explicit MsgQueue(std::string queue_name, std::string data_name, std::string ctrl_name,
            unsigned int id, unsigned int buffer_size, bool creator = true);

        MsgQueue(const MsgQueue<T>&) = default;
        MsgQueue<T>& operator = (const MsgQueue<T>&) = default;

        ~MsgQueue();

        int getLastConsumedId()
        {
            return queue_addr->last_consumed_id;
        }

        int getLastClaimedId()
        {
            return queue_addr->last_claimed_id.value;
        }

        int getCursor()
        {
            return queue_addr->cursor.value;
        }
    };

    //共享内存消息队列的消费者
    template <typename T>
    struct MsgQueueReader
    {
    private:
        MsgQueue<T> queue;                      //内存消息队列
        struct vrt_consumer *consumer=nullptr;  //消费者指针
    public:
        MsgQueueReader(MsgQueue<T>& queue);
        ~MsgQueueReader();

        MsgQueueReader(const MsgQueueReader<T>&) = default;
        MsgQueueReader& operator = (const MsgQueueReader<T>&) = default;

        T* consumerNextNoWaiting();
        std::string getQueueName() const
        {
            return queue.name;
        }

        int getCurrId()
        {
            return consumer->current_id;
        }

        int getLastAvalId()
        {
            return consumer->last_available_id;
        }

    };

    //共享内存消息队列的消费者
    template <typename T>
    struct MsgQueueWriter
    {
    private:
        MsgQueue<T> queue;
        struct vrt_producer *producer = nullptr;

    public:
        MsgQueueWriter(MsgQueue<T>& queue, bool is_single_producer = false);
        ~MsgQueueWriter();

        MsgQueueWriter(const MsgQueueWriter<T>&) = default;
        MsgQueueWriter<T>& operator = (const MsgQueueWriter<T>&) = default;

        std::string getQueueName() const
        {
            return queue.name;
        }

        T& claim();
        void publish();

    };

    //MsgQueue
    template <typename T>
    MsgQueue<T>::MsgQueue(std::string queue_name, std::string data_name,
        std::string ctrl_name, unsigned int id, unsigned int buffer_size, bool creator)
        : name(queue_name)
        , data_name(data_name)
        , ctrl_name(ctrl_name)
        , id(id)
    {
        if (creator)
        {
            //分配控制块共享内存
            queue_addr = vrt_queue_new(ctrl_name.c_str(), buffer_size, sizeof(T), &ctrl_shm_fd);
            data_len = buffer_size * sizeof(T);
        }
        else
        {
            //获得已经分配好的控制块共享内存
            queue_addr = vrt_queue_acquire(ctrl_name.c_str(), &ctrl_shm_fd);
            data_len = (queue_addr->value_mask + 1) * sizeof(T);
        }

        //分配数据块共享内存        
        data_addr = (T*)vrt_data_new(data_name.c_str(), data_len, &data_shm_fd);
        //LOG_DEBUG("createQueue:begin data queue buffer preload\n");
        //预加载数据块内存
        vm_preload((unsigned char *)data_addr, buffer_size * sizeof(T));
        //LOG_DEBUG("createQueue:end data queue buffer preload\n");
    }

    template <typename T>
    MsgQueue<T>::~MsgQueue()
    {
        //为了避免潜在的crash，简化代码和提高性能，考虑先不释放内存
        //TO DO
        //if (data_addr)
        //{
        //    vrt_data_free(data_addr, data_name.c_str(), data_len, data_shm_fd, false);
        //    data_addr = nullptr;
        //}
        //
        //if (queue_addr)
        //{
        //    vrt_queue_free(queue_addr, ctrl_shm_fd, false);
        //    queue_addr = nullptr;
        //}
    }

    //MsgQueueConsumer<T>
    template <typename T>
    MsgQueueReader<T>::MsgQueueReader(MsgQueue<T>& queue)
        :queue(queue)
    {
        consumer = vrt_consumer_new(this->queue.name.c_str(), this->queue.queue_addr, 0);
    }

    template <typename T>
    MsgQueueReader<T>::~MsgQueueReader()
    {
        //为了避免crash，简化代码和提高性能，考虑先不释放内存
        //TO DO
        //if (consumer)
        //{
        //    vrt_consumer_free(consumer);
        //    consumer = nullptr;
        //}
    }
    template <typename T>
    T* MsgQueueReader<T>::consumerNextNoWaiting()
    {   
        int posi = 0;
        static unsigned int count = 0;
        static bool flag = true;
        count++;
        if (flag)
        {
            if (count > 100)
            {
                flag = false;
            }
            SPDLOG_DEBUG("queue {}: last_consumed_id {}, last_claimed_id {}, cursor {}, consumer curr_id {}, last_aval_id {}",
                getQueueName(), queue.getLastConsumedId(), queue.getLastClaimedId(), queue.getCursor(),
                getCurrId(), getLastAvalId());
        }

        if (0 == vrt_consumer_next_no_waiting(consumer, &posi))
        {
            //SPDLOG_DEBUG("queue {}, msg pos {}", getQueueName(), posi);
            return &((queue.data_addr)[posi]);
        }
        
        return nullptr;
    }

    //MsgQueueWriter
    template <typename T>
    MsgQueueWriter<T>::MsgQueueWriter(MsgQueue<T>& queue, bool is_single_producer)
        : queue(queue)
    {
        producer = vrt_producer_new(this->queue.name.c_str(), 1, this->queue.queue_addr, 0, is_single_producer);
        producer->yield = vrt_yield_strategy_spin_wait();
    }

    template <typename T>
    MsgQueueWriter<T>::~MsgQueueWriter()
    {
        //为了避免crash，简化代码和提高性能，考虑先不释放内存
        //TO DO
        //if (producer)
        //{
        //    vrt_producer_free(producer);
        //    producer = nullptr;
        //}
    }

    template <typename T>
    T& MsgQueueWriter<T>::claim()
    {
        int posi;
        vrt_producer_claim(producer, &posi);
        return *(queue.data_addr + posi);
    }

    template <typename T>
    void MsgQueueWriter<T>::publish()
    {
        vrt_producer_publish(producer);
    }
}