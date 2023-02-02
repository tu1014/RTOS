
#include "Uart.h"
#include "HalUart.h"
#include "HalInterrupt.h"
#include "Kernel.h"
#include "event.h"

extern volatile PL011_t* Uart;

static void interrupt_handler(void);

void Hal_uart_init(void) {
    // enable UART
    Uart->uartcr.bits.UARTEN = 0;
    Uart->uartcr.bits.TXE = 1; // enable uart output
    Uart->uartcr.bits.RXE - 1; // enable uart input
    Uart->uartcr.bits.UARTEN = 1;

    // enable input interrupt
    Uart->uartimsc.bits.RXIM = 1;

    // register UART interrupt handler
    Hal_interrupt_enable(UART_INTERRUPT0);
    Hal_interrupt_register_handler(interrupt_handler, UART_INTERRUPT0);
}

void Hal_uart_put_char(uint8_t ch) {
    while(Uart->uartfr.bits.TXFF); // wait until output buffer is empty
    Uart->uartdr.all = (ch & 0xFF);
}

uint8_t Hal_uart_get_char(void) {

    uint8_t data;

    while(Uart->uartfr.bits.RXFE); // wait until input buffer is filled

    data = Uart->uartdr.all;

    // check 4 error flag
    if (data & 0xFFFFFF00) {

        // clear all error flag
        Uart->uartdr.all = 0xFF;
        return 0;
    }

    return (uint8_t)(data & 0xFF);
}

static void interrupt_handler(void)
{
    uint8_t ch = Hal_uart_get_char();
    Hal_uart_put_char(ch);
    Hal_uart_put_char('\n');

    Kernel_send_events(KernelEventFlag_UartIn | KernelEventFlag_CmdIn);

    if(ch == 'X') {
        Kernel_send_events(KernelEventFlag_CmdOut);
    }
}
