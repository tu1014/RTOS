
#include "stdint.h"
#include "HalUart.h"
#include "HalInterrupt.h"
#include "stdio.h"

static void Hw_init(void);
static void Printf_test(void);

void main(void) {

    Hw_init();

    putstr("Hello World!\n");
    Printf_test();
    putstr("Finish!\n");

    while(1);

}

static void Hw_init(void) {
    Hal_interrupt_init();
    Hal_uart_init();
}

static void Printf_test(void)
{
    char* str = "printf pointer test";
    char* nullptr = 0;
    uint32_t i = 5;

    debug_printf("%s\n", "Hello printf");
    debug_printf("output string pointer: %s\n", str);
    debug_printf("%s is null pointer, %u number\n", nullptr, 10);
    debug_printf("%u = 5\n", i);
    debug_printf("dec=%u hex=%x\n", 0xff, 0xff);
    debug_printf("print zero %u\n", 0);
}