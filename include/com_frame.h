#ifndef COM_FRAME_H
#define COM_FRAME_H

#include <stdint.h>

/*
[0] SYNC BYTE = 0xCF
[1] SENDER BYTE, 
[2] COMMAND BYTE, 
[3] DATA LENGTH BYTE,
[4-N] DATA BYTES
[N+1] EOT BYTE = 0xFC
*/

#define SYNC_BYTE 0xCF
#define EOT_BYTE 0xFC

enum class SENDER_BYTE{
    SENDER_CAN_MODULE_RESP = 0x0,
    SENDER_PC_RESP,
    SENDER_PHONE_RESP,

    SENDER_CAN_MODULE_REQ,
    SENDER_PC_REQ,
    SENDER_PHONE_REQ,
};

enum class COMMAND_BYTE{
    SYN = 0x00,
    ACK = 0x01,
    CAN_FRAME = 0x02,
    CAN_FRAME_DUMMY = 0x03,
    STATUS_REQ = 0x04,
    STATUS_ANS = 0x05,
};

class COM_FRAME{

public:
    COM_FRAME(
        SENDER_BYTE     sb, 
        COMMAND_BYTE    cb,
        uint8_t         data_len,
        uint8_t         data_buff[]     
        );

    COM_FRAME();

        uint8_t m_sync;
        SENDER_BYTE m_sb;
        COMMAND_BYTE m_cb;
        uint8_t m_data_len;
        uint8_t* m_data_buff;
        uint8_t m_eot;

        void toByteArray(uint8_t* ba, int& len);
        bool fromByteArrar(uint8_t* buff, int len);

        void toDummyFrame();
    
private:

};

#endif