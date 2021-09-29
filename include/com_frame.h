#ifndef COM_FRAME_H
#define COM_FRAME_H

#include <stdint.h>

/*
[0] SYNC BYTE = 0xCF
[1] SENDER BYTE,
[2] COMMAD TYPE BYTE ,
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

    SENDER_NULL_SENDER = 0xFF,
};

enum class COMMNAD_TYPE_BYTE{
    GET = 0x00,
    SET = 0x01,
    NULL_TYPE_BYTE = 0xFF,
};

enum class COMMAND_BYTE{
    SYN = 0x00,
    ACK = 0x01,
    CAN_FRAME = 0x02,
    CAN_FRAME_DUMMY = 0x03,
    STATUS_REQ = 0x04,
    STATUS_ANS = 0x05,
    CAN_RATE = 0x06,
    CAN_STREAM = 0x07,
    INFO_STRING = 0x08,

    NULL_COMMAND_BYTE = 0xFF
};

class CAN_FRAME{

public:
    CAN_FRAME();

    unsigned long id = 0;
    uint8_t bf = 0;
    uint8_t len = 0;
    bool received = false;

private:

};

class COM_FRAME{

public:
    COM_FRAME(
        SENDER_BYTE     sb,
        COMMNAD_TYPE_BYTE cbt,
        COMMAND_BYTE    cb,
        uint8_t         data_len,
        uint8_t         data_buff[]
        );

    COM_FRAME();

        //FRAME
        uint8_t m_sync = SYNC_BYTE;
        SENDER_BYTE m_sb;
        COMMNAD_TYPE_BYTE m_ctb = COMMNAD_TYPE_BYTE::NULL_TYPE_BYTE;
        COMMAND_BYTE m_cb = COMMAND_BYTE::NULL_COMMAND_BYTE;
        uint8_t m_data_len = 0;
        uint8_t m_data_buff[16];
        uint8_t m_eot = EOT_BYTE;

        //CONST
        static const uint8_t k_empty_size = 6;
        static const uint8_t k_header_size = 5;

        void toByteArray(uint8_t* ba, int& len);
        bool fromByteArray(uint8_t* buff, int len);

        void toDummyFrame();
        void addCanFrame(const CAN_FRAME& frame);

private:

};

#endif
