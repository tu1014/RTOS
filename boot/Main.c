
#include "stdint.h"
#include "HalUart.h"
#include "HalInterrupt.h"
#include "HalTimer.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "task.h"
#include "Kernel.h"
#include "event.h"

static void Hw_init(void);
static void Printf_test(void);
static void Timer_test(void);
static void Kernel_init(void);

void User_task0(void);
void User_task1(void);
void User_task2(void);

void main(void) {

    Hw_init();

    putstr("This is Navilos RTOS!\n");

    Kernel_init();
}

static void Hw_init(void) {
    Hal_interrupt_init();
    Hal_uart_init();
    Hal_timer_init();
}

static void Printf_test(void)
{
    char* str = "printf pointer test";
    char* nullptr = 0;
    uint32_t i = 5;
    uint32_t* sysctrl0 = (uint32_t*) 0x10001000;

    debug_printf("%s\n", "Hello printf");
    debug_printf("output string pointer: %s\n", str);
    debug_printf("%s is null pointer, %u number\n", nullptr, 10);
    debug_printf("%u = 5\n", i);
    debug_printf("dec=%u hex=%x\n", 0xff, 0xff);
    debug_printf("print zero %u\n", 0);
    debug_printf("SYSCTRL0 %x\n", *sysctrl0);
}

static void Timer_test(void) {
    while(true) {
        debug_printf("current count : %u\n", Hal_timer_get_1ms_counter());
        delay(1000);
    }
}

static Kernel_init(void) {

    uint32_t taskId;

    Kernel_task_init();
    Kernel_event_flag_init();

    taskId = Kernel_task_create(User_task0);
    if(taskId == NOT_ENOUGH_TASK_NUM)
        putstr("TASK0 creation fail\n");

    taskId = Kernel_task_create(User_task1);
    if(taskId == NOT_ENOUGH_TASK_NUM)
        putstr("TASK1 creation fail\n");

    taskId = Kernel_task_create(User_task2);
    if(taskId == NOT_ENOUGH_TASK_NUM)
        putstr("TASK2 creation fail\n");

    Kernel_start();
}

void User_task0(void) {

    uint32_t local = 0;
    uint32_t count = 0;

    debug_printf("User Task #%u start!\n", local);
    while(true) {
        // debug_printf("User Task #%u SP = 0x%x\n",local, &local);
        // debug_printf("User Task #%u COUNT : %u\n", local, count++);
        // delay(1000);

        bool pendingEvent = true;

        while(pendingEvent) {
            
            KernelEventFlag_t handle_event = Kernel_wait_events(
                KernelEventFlag_UartIn | KernelEventFlag_CmdOut
            );

            switch(handle_event) {
                case KernelEventFlag_UartIn:
                    debug_printf("=====UARTIn Event Handled!=====\n");
                    break;

                case KernelEventFlag_CmdOut:
                    debug_printf("CmdOut Event by Task#%u\n", local);
                    break;
                
                case KernelEventFlag_Empty:
                    pendingEvent = false;
                    break;
            }
        }
    
        Kernel_yield();
    }
}

void User_task1(void) {

    uint32_t local = 1;
    uint32_t count = 0;

    debug_printf("User Task #%u start!\n", local);
    while(true) {
        // debug_printf("User Task #%u SP = 0x%x\n",local, &local);
        // debug_printf("User Task #%u COUNT : %u\n", local, count++);
        // delay(1000);

        KernelEventFlag_t handle_event = Kernel_wait_events(KernelEventFlag_CmdIn);

        switch(handle_event) {
            case KernelEventFlag_CmdIn:
                debug_printf("====CmdIn Event Handled====\n");
                break;
        }

        Kernel_yield();
    }
}

void User_task2(void) {

    uint32_t local = 2;
    uint32_t count = 0;

    debug_printf("User Task #%u start!\n", local);
    while(true) {
        // debug_printf("User Task #%u SP = 0x%x\n",local, &local);
        // debug_printf("User Task #%u COUNT : %u\n", local, count++);
        // delay(1000);
        Kernel_yield();
    }
}