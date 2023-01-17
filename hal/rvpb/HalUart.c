
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