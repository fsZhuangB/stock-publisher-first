#pragma once
#include <string>
#include "queue.h"
#include "utility.h"

namespace TD
{
    /**
    *@  ����ģ���ͨ�ŵ���Ϣ�����࣬�������β���ģ���뽻�״����Լ����״����ڲ�ͨ�ţ�
    *   �ײ�ʹ��cdisruptor
    **/
    //����cdisruptor�Ĺ����ڴ���Ϣ����
    template <typename T>
    struct MsgQueue
    {
        struct vrt_queue *queue_addr = nullptr;     //���ƿ鹲���ڴ�����ַ
        T *data_addr = nullptr;                     //���ݿ鹲���ڴ����׵�ַ
        int data_len = 0;                           //���ݿ�鹲���ڴ�����С
        int ctrl_shm_fd = -1;                       //���ƿ鹲���ڴ��ļ�������
        int data_shm_fd = -1;                       //���ݿ鹲���ڴ��ļ�������
        int id = -1;                                //����id                          
        std::string name;                           //��������
        std::string data_name;                      //���ݿ�������
        std::string ctrl_name;                      //���ƿ�������

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

    //�����ڴ���Ϣ���е�������
    template <typename T>
    struct MsgQueueReader
    {
    private:
        MsgQueue<T> queue;                      //�ڴ���Ϣ����
        struct vrt_consumer *consumer=nullptr;  //������ָ��
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

    //�����ڴ���Ϣ���е�������
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
            //������ƿ鹲���ڴ�
            queue_addr = vrt_queue_new(ctrl_name.c_str(), buffer_size, sizeof(T), &ctrl_shm_fd);
            data_len = buffer_size * sizeof(T);
        }
        else
        {
            //����Ѿ�����õĿ��ƿ鹲���ڴ�
            queue_addr = vrt_queue_acquire(ctrl_name.c_str(), &ctrl_shm_fd);
            data_len = (queue_addr->value_mask + 1) * sizeof(T);
        }

        //�������ݿ鹲���ڴ�        
        data_addr = (T*)vrt_data_new(data_name.c_str(), data_len, &data_shm_fd);
        //LOG_DEBUG("createQueue:begin data queue buffer preload\n");
        //Ԥ�������ݿ��ڴ�
        vm_preload((unsigned char *)data_addr, buffer_size * sizeof(T));
        //LOG_DEBUG("createQueue:end data queue buffer preload\n");
    }

    template <typename T>
    MsgQueue<T>::~MsgQueue()
    {
        //Ϊ�˱���Ǳ�ڵ�crash���򻯴����������ܣ������Ȳ��ͷ��ڴ�
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
        //Ϊ�˱���crash���򻯴����������ܣ������Ȳ��ͷ��ڴ�
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
        //Ϊ�˱���crash���򻯴����������ܣ������Ȳ��ͷ��ڴ�
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