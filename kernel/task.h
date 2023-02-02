
#ifndef KERNEL_TASK_H_
#define KERNEL_TASK_H_

#include "MemoryMap.h"
#include "stdint.h"

#define NOT_ENOUGH_TASK_NUM 0xFFFFFFFF

#define USR_TASK_STACK_SIZE     0x100000 // (1024 * 1024) -> 1MB
#define MAX_TASK_NUM            (TASK_STACK_SIZE / USR_TASK_STACK_SIZE) // 64MB / 1MB = 64

// Abstract Context
typedef struct KernelTaskContext_t {
    uint32_t spsr; // CPSR backup
    uint32_t r0_r12[13];
    uint32_t pc; // Program Counter
} KernelTaskContext_t;

typedef struct KernelTcb_t {
    uint32_t sp; // Stack Pointer
    uint8_t* stack_base;
    // uint32_t priority;
} KernelTcb_t;

typedef void (*KernelTaskFunc_t)(void);

void Kernel_task_init(void);
void Kernel_task_scheduler(void);
void Kernel_task_context_switching(void);
void Kernel_task_start(void);
uint32_t Kernel_task_create(KernelTaskFunc_t startFunc);

#endif /* KERNEL_TASK_H_ */
