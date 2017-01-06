#include <stdint.h>
#include "isr_irqs.h"
#include "ioport.h"
#include "stdio.h"
#include "kb.h"

extern "C" {

void kernel_halt();

}

namespace {

// Total ticks system has been running. Incremented every IRQ 0
unsigned timer_ticks = 0;

// IRQ 0
// Increment timer_ticks 1000x per sec
void IRQ_timerHandler()
{
  timer_ticks++;
}

} // unnamed namespace

namespace kernel {

void timerInit()
{
  const int PIT_CMD = 0x43;
  const int CHANNEL0 = 0x40;
  uint16_t divisor = 1193; // 1193180 Hz / 1000 Ticks Per Sec 
  // 0x36 = channel 0, Send lo then hi byte of divisor, Square Root Mode 
  kernel_outport(PIT_CMD, 0x36); 
  kernel_outport(CHANNEL0, divisor & 0xFF); // send low byte of divisor
  kernel_outport(CHANNEL0, divisor >> 8); // send high byte of divisor 

  IRQ_addHandler(0, IRQ_timerHandler);
}

void sleep(unsigned ms)
{
  bool kb_was_disabled = isKeyboardDisabled();
  disableKeyboardInput();

  unsigned end_ticks = timer_ticks + ms;
  while(timer_ticks < end_ticks) 
  { 
    kernel_halt();
  }

  // reenable keyboard if it wasn't disabled before sleep
  if (!kb_was_disabled) {
    enableKeyboardInput();
  }
}

} // namespace kernel
