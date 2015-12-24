AS = i686-elf-as
CC = i686-elf-g++

CFLAGS = -Wall -Wextra -pedantic -std=c++11 -O2 -ffreestanding \
				 -fno-exceptions -fno-rtti
LFLAGS = -Wall -Wextra -pedantic -std=c++11 -O2 -ffreestanding -nostdlib \
				 -lgcc -fno-exceptions -fno-rtti

ODIR = build
_OBJ = gdt.o gdt_load.o global_dtors.o idt.o idt_load.o ioport.o \
			 isr_exception_wrappers.o isr_exceptions.o isr_irq_wrappers.o \
			 isr_irqs.o kb.o kernel.o kernel_init.o kernel_panic.o loader.o \
			 stdio.o string.o terminal.o timer.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
CRTI = $(ODIR)/crti.o
CRTN = $(ODIR)/crtn.o
CRT_BEGIN = $(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRT_END = $(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)

kernel.bin: $(ODIR) $(OBJ) $(CRTI) $(CRTN) 
	$(CC) -T linker.ld -o $@ $(CRTI) $(CRT_BEGIN) $(OBJ) $(CRT_END) $(CRTN) \
		$(LFLAGS)

$(ODIR):
	mkdir $@

$(ODIR)/crti.o: crti.s
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/crtn.o: crtn.s
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/gdt.o: gdt.cpp gdt.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/gdt_load.o: gdt_load.s
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/global_dtors.o: global_dtors.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/idt.o: idt.cpp idt.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/idt_load.o: idt_load.s 
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/ioport.o: ioport.s 
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/isr_exception_wrappers.o: isr_exception_wrappers.s
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/isr_exceptions.o: isr_exceptions.cpp isr_exceptions.h idt.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/isr_irq_wrappers.o: isr_irq_wrappers.s
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/isr_irqs.o: isr_irqs.cpp isr_irqs.h idt.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/kb.o: kb.cpp kb.h ioport.h isr_irqs.h terminal.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/kernel.o: kernel.cpp multiboot.h terminal.h stdio.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/kernel_init.o: kernel_init.cpp gdt.h idt.h isr_exceptions.h terminal.h 
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/kernel_panic.o: kernel_panic.cpp kernel_panic.h stdio.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/loader.o: loader.s
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/stdio.o: stdio.cpp stdio.h terminal.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/string.o: string.cpp string.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/terminal.o: terminal.cpp terminal.h string.h 
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/timer.o: timer.cpp timer.h isr_irqs.h
	$(CC) -o $@ -c $< $(CFLAGS)

