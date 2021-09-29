#include "com_frame.h"

COM_FRAME::COM_FRAME(
        SENDER_BYTE             sb,
        COMMNAD_TYPE_BYTE       ctb,
        COMMAND_BYTE            cb,
        uint8_t                 data_len,
        uint8_t*                data_buff)


{
        m_sync = SYNC_BYTE;
        m_sb = sb;
        m_ctb = ctb;
        m_cb = cb;
        m_data_len = data_len;
        for(int i = 0; i < data_len; i++){
            m_data_buff[i] = data_buff[i];
        }
        m_eot = EOT_BYTE;
}

COM_FRAME::COM_FRAME()
{
        m_sync = SYNC_BYTE;
        m_sb = SENDER_BYTE::SENDER_NULL_SENDER;
        m_ctb = COMMNAD_TYPE_BYTE::NULL_TYPE_BYTE;
        m_cb = COMMAND_BYTE::CAN_FRAME_DUMMY;
        m_data_len = 1;
        m_data_buff[0] = 0xFF;
        m_eot = EOT_BYTE;
}

void COM_FRAME::toByteArray(uint8_t* ba, int& len)
{
    ba[0] = (uint8_t)SYNC_BYTE;
    ba[1] = (uint8_t)m_sb;
    ba[2] = (uint8_t)m_ctb;
    ba[3] = (uint8_t)m_cb;
    ba[4] = m_data_len;

    int i = 0;
    for(; i < m_data_len;){
        ba[5+i] = m_data_buff[i];
        ba[5+i+1] = EOT_BYTE;
        i++;
    }

    len = m_data_len + 6;
}

bool COM_FRAME::fromByteArray(uint8_t* buff, int len)
{
    m_sync  = buff[0];
    m_sb    = (SENDER_BYTE)buff[1];
    m_ctb   = (COMMNAD_TYPE_BYTE)buff[2];
    m_cb    = (COMMAND_BYTE)buff[3];
    m_data_len = buff[4];

    int i = 0;
    for (; i < m_data_len; i++)
    {
        m_data_buff[i] = buff[5 + i];
    }

    m_eot = buff[5 + i +1];

    return true;
}

void COM_FRAME::toDummyFrame()
{
    m_cb = COMMAND_BYTE::CAN_FRAME_DUMMY;
    m_data_len = 2;
    m_data_buff[0] = 0xAA;
    m_data_buff[1] = 0xAB;

}

void COM_FRAME::addCanFrame(const CAN_FRAME& frame)
{
    //Data length of COM_FRAME WITH CAN_FRAME
    //[0] = Arbitration 0
    //[1] = Arbitration 1
    //[2] = Control
    //[3] = Data
    //Total = 4 bytes
    m_data_len = 5;
    m_data_buff[0] = frame.id << 24;
    m_data_buff[1] = frame.id << 16;
    m_data_buff[2] = frame.id << 8;
    m_data_buff[3] = frame.id << 0;

    m_data_buff[4] = frame.bf;

}


