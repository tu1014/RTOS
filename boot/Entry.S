
#include "ARMv7AR.h"
#include "MemoryMap.h"

.text

    .code 32

    .global vector_start
    .global vector_end

    vector_start:
        LDR		PC, reset_handler_addr
		LDR		PC, undef_handler_addr
		LDR		PC, svc_handler_addr
		LDR		PC, pftch_abt_handler_addr
		LDR		PC, data_abt_handler_addr
		B		.
		LDR		PC, irq_handler_addr
		LDR		PC, fiq_handler_addr

		reset_handler_addr: 	.word reset_handler
		undef_handler_addr: 	.word dummy_handler
		svc_handler_addr: 		.word dummy_handler
		pftch_abt_handler_addr: .word dummy_handler
		data_abt_handler_addr:  .word dummy_handler
		irq_handler_addr:		.word Irq_Handler
		fiq_handler_addr:		.word Fiq_Handler

    vector_end:
		LDR		R0, =0x10000000
		LDR		R1, [R0]


    reset_handler:
        /* SVC Mode Stack Init */
		MRS r0, cpsr
        BIC r1, r0, #ARM_MODE_BIT_FLAG
        ORR r1, r1, #ARM_MODE_BIT_SVC
        MSR cpsr, r1
        LDR sp, =SVC_STACK_TOP

		/* IRQ Mode Stack Init */
        MRS r0, cpsr
        BIC r1, r0, #ARM_MODE_BIT_FLAG
        ORR r1, r1, #ARM_MODE_BIT_IRQ
        MSR cpsr, r1
        LDR sp, =IRQ_STACK_TOP

		/* FIQ Mode Stack Init */
        MRS r0, cpsr
        BIC r1, r0, #ARM_MODE_BIT_FLAG
        ORR r1, r1, #ARM_MODE_BIT_FIQ
        MSR cpsr, r1
        LDR sp, =FIQ_STACK_TOP

		/* ABT Mode Stack Init */
        MRS r0, cpsr
        BIC r1, r0, #ARM_MODE_BIT_FLAG
        ORR r1, r1, #ARM_MODE_BIT_ABT
        MSR cpsr, r1
        LDR sp, =ABT_STACK_TOP

		/* UND Mode Stack Init */
        MRS r0, cpsr
        BIC r1, r0, #ARM_MODE_BIT_FLAG
        ORR r1, r1, #ARM_MODE_BIT_UND
        MSR cpsr, r1
        LDR sp, =UND_STACK_TOP

		/* USR, SYS Mode Stack Init */
        MRS r0, cpsr
        BIC r1, r0, #ARM_MODE_BIT_FLAG
        ORR r1, r1, #ARM_MODE_BIT_SYS
        MSR cpsr, r1
        LDR sp, =USRSYS_STACK_TOP


		BL main


    dummy_handler:
		B .

.end