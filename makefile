CC := i686-elf-g++
CFLAGS := -Wall -Wextra -pedantic -std=c++11 -O2 -ffreestanding \
				 -fno-exceptions -fno-rtti
LFLAGS := -Wall -Wextra -pedantic -std=c++11 -O2 -ffreestanding -nostdlib \
				 -lgcc -fno-exceptions -fno-rtti

CPP_SRCS := gdt.cpp  global_dtors.cpp idt.cpp isr_exceptions.cpp \
					 isr_irqs.cpp kb.cpp kernel.cpp kernel_init.cpp kernel_panic.cpp \
					 stdio.cpp string.cpp terminal.cpp timer.cpp 
ASM_SRCS := gdt_load.s idt_load.s ioport.s isr_exception_wrappers.s \
					 isr_irq_wrappers.s loader.s  

DEPDIR := deps
ODIR := build
DEPS := $(patsubst %, $(DEPDIR)/%.makefile, $(CPP_SRCS))
CPP_OBJS := $(patsubst %.cpp, $(ODIR)/%.o, $(CPP_SRCS))
ASM_OBJS := $(patsubst %.s, $(ODIR)/%.o, $(ASM_SRCS))
OBJS := $(CPP_OBJS) $(ASM_OBJS)

CRTI := $(ODIR)/crti.o
CRTN := $(ODIR)/crtn.o
CRT_BEGIN := $(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRT_END := $(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)

kernel.bin: $(DEPS) $(ASM_OBJS) $(CRTI) $(CRTN) 
	$(CC) -T linker.ld -o $@ $(CRTI) $(CRT_BEGIN) $(OBJS) $(CRT_END) $(CRTN) \
		$(LFLAGS)

$(DEPDIR):
	mkdir $@

$(ODIR):
	mkdir $@

$(DEPDIR)/%.cpp.makefile: $(ODIR)/%.o | $(DEPDIR)
	$(CC) -MM $*.cpp -MT $(ODIR)/$*.o > $@

-include $(DEPS)

$(CPP_OBJS): $(ODIR)/%.o: | $(ODIR)
	$(CC) -o $@ -c $*.cpp $(CFLAGS)
		
$(ASM_OBJS) $(CRTI) $(CRTN): $(ODIR)/%.o: %.s | $(ODIR)
	$(CC) -o $@ -c $*.s $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(DEPS)
