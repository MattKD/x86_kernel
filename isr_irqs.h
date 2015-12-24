#ifndef KERNEL_ISR_IRQS_H
#define KERNEL_ISR_IRQS_H

namespace kernel {

typedef void (*IRQ_Handler)();

void IDT_install_IRQ_ISRs();
void IRQ_addHandler(int irq, IRQ_Handler f);
void PIC_init();

}

#endif
