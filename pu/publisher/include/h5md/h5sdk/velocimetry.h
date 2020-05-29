#ifndef __VELOCIMETRY_H__
#define __VELOCIMETRY_H__

#include "h5sdk_export.h"
#include <Include/hscomm_message_interface.h>

// ����ʧ�ܵĴ����ö��
enum VelocimetryErrorNo {
    TIME_OUT = 1,  // ��ʱ
    USER_CANCEL,   // �û�����ȡ������
    PORT_NOT_OPEN, // ����˳���δ���������˳���æ���ô���Ҳ���ܰ�ʾ�����˴���ķ�������
    SERVER_CLOSE,  // ����������ر����ӣ��ô���һ����ζ�������˴���ķ�������
};

// ����վ�㼰�ش����ݶ���
class Endpoint {
public:
    char userData[32];
    char ip[64];
    unsigned short port;
};

// ���ٻص��ӿ�
class VelocimetryCallback {
public:
    // ��ĳ��վ����ٳɹ��Ļص�
    // delayΪ�÷������ɲ��ٵĺ�ʱ����λ:����
    // loadΪ�÷���˵ĸ��أ���ֵ��ΧΪ[0, 100]��0��ʾ������ͣ�100��ʾ�������
    virtual int H5SDKAPI OnVelocimetrySucceed(Endpoint *endpoint, int delay, int load) = 0;
    // ��ĳ��վ�����ʧ�ܵĻص�
    virtual int H5SDKAPI OnVelocimetryFail(Endpoint *endpoint, VelocimetryErrorNo errorNo) = 0;
    // ������վ�㶼���ٽ��������۳ɹ�ʧ�ܣ��Ļص�
    virtual int H5SDKAPI OnVelocimetryComplete() = 0;
};

// ���ٽӿ�
class Velocimetry: public IHSKnown {
public:
    virtual ~Velocimetry() {}

    // �������
    virtual int H5SDKAPI Start(Endpoint *endpoints, size_t endpointCount, VelocimetryCallback *velocimetryCallback, int milliseconds) = 0;
    // ȡ������
    virtual int H5SDKAPI Stop() = 0;
};

#endif
