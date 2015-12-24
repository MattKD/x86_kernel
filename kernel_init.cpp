#include "terminal.h"
#include "gdt.h"
#include "idt.h"
#include "isr_exceptions.h"
#include "isr_irqs.h"
#include "kb.h"
#include "timer.h"

using namespace kernel;

extern "C"
void kernelInit()
{
  Terminal::initMainTerm();
  GDT_init();
  IDT_init();
  PIC_init();
  IDT_install_Exception_ISRs();
  IDT_install_IRQ_ISRs();
  keyboardInit();
  timerInit();
}
