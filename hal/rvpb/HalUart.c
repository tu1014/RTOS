
#include "Uart.h"
#include "HalUart.h"

extern volatile PL011_t* Uart;

void Hal_uart_init(void) {
    Uart->uartcr.bits.UARTEN = 0;
    Uart->uartcr.bits.TXE = 1; // enable uart output
    Uart->uartcr.bits.RXE - 1; // enable uart input
    Uart->uartcr.bits.UARTEN = 1;
}

void Hal_uart_put_char(uint8_t ch) {
    while(Uart->uartfr.bits.TXFF); // wait until output buffer is empty
    Uart->uartdr.all = (ch & 0xFF);
}

uint8_t Hal_uart_get_char(void) {

    uint8_t data;

    while(Uart->uartfr.bits.RXFE);

    data = Uart->uartdr.all;

    // check 4 error flag
    if (data & 0xFFFFFF00) {

        // clear all error flag
        Uart->uartdr.all = 0xFF;
        return 0;
    }

    return (uint8_t)(data & 0xFF);
}