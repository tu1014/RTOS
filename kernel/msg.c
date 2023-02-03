
#include "msg.h"
#include "stdlib.h"

KernelCirQ_t sMsgQ[KernelMsgQ_Num];

void Kernel_msgQ_init(void) {
    for(uint32_t i=0; i<KernelMsgQ_Num; i++) {
        sMsgQ[i].front = 0;
        sMsgQ[i].rear = 0;
        memclr(sMsgQ[i].Queue, MSG_Q_SIZE_BYTE);
    }
}

bool Kernel_msgQ_is_empty(KernelMsgQ_t Qname) {
    if(Qname >= KernelMsgQ_Num)
        return false;

    if(sMsgQ[Qname].front == sMsgQ[Qname].rear)
        return true;

    return false;
}

bool Kernel_msgQ_is_full(KernelMsgQ_t Qname) {
    if(Qname >= KernelMsgQ_Num)
        return false;

    if(((sMsgQ[Qname].rear + 1) % MSG_Q_SIZE_BYTE) == sMsgQ[Qname].front)
        return true;

    return false;
}

bool Kernel_msgQ_enqueue(KernelMsgQ_t Qname, uint8_t data) {
    if(Qname >= KernelMsgQ_Num)
        return false;

    if(Kernel_msgQ_is_full(Qname))
        return false;

    uint32_t index = sMsgQ[Qname].rear;
    sMsgQ[Qname].Queue[index] = data;

    sMsgQ[Qname].rear++;
    sMsgQ[Qname].rear %= MSG_Q_SIZE_BYTE;

    return true;
}

bool Kernel_msgQ_dequeue(KernelMsgQ_t Qname, uint8_t* out_data) {
    if(Qname >= KernelMsgQ_Num)
        return false;

    if(Kernel_msgQ_is_empty(Qname))
        return false;

    uint32_t index = sMsgQ[Qname].front;
    *out_data = sMsgQ[Qname].Queue[index];

    sMsgQ[Qname].front++;
    sMsgQ[Qname].front %= MSG_Q_SIZE_BYTE;

    return true;
}