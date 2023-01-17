
#include "HalUart.h"
#include "stdio.h"

uint32_t putstr(const char* s) {

    uint32_t count = 0;
    char* cursor = s;

    while(*cursor) {
        Hal_uart_put_char(*cursor++);
        count++;
    }

    return count;
}