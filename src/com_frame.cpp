#include "com_frame.h"

COM_FRAME::COM_FRAME(
        SENDER_BYTE             sb, 
        COMMAND_BYTE            cb,
        uint8_t                 data_len,
        uint8_t*                data_buff)

 
{
        m_sync = SYNC_BYTE;
        m_sb = sb;
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
        m_sb = SENDER_BYTE::SENDER_CAN_MODULE_RESP;
        m_cb = COMMAND_BYTE::CAN_FRAME_DUMMY;
        m_data_len = 1;
        m_data_buff[0] = 0xFF;
        m_eot = EOT_BYTE;
}

void COM_FRAME::toByteArray(uint8_t* ba, int& len) 
{
    ba[0] = (uint8_t)SYNC_BYTE;
    ba[1] = (uint8_t)m_sb;
    ba[2] = (uint8_t)m_cb;
    ba[3] = m_data_len;

    int i = 0;
    for(; i < m_data_len; i++){
        ba[4+i] = m_data_buff[i];
    }

    ba[4+i+1] = EOT_BYTE;
    len = m_data_len + 5;
}

bool COM_FRAME::fromByteArray(uint8_t* buff, int len) 
{
    m_sync  = buff[0];
    m_sb    = (SENDER_BYTE)buff[1];
    m_cb    = (COMMAND_BYTE)buff[2];
    m_data_len = buff[3];

    int i = 0;
    for (; i < m_data_len; i++)
    {
        m_data_buff[i] = buff[4 + i];
    }

    m_eot = buff[4 + i +1];
    
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
    m_data_len = frame.len;

    for(int i = 0; i < m_data_len; i++){
        m_data_buff[i] = frame.bf[i];
    }
}


