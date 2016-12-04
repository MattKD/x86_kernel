# x86_kernel
Hobby x86 kernel

To compile the kernel you need to build a i686-elf-gcc cross compiler. Follow the directions here: http://wiki.osdev.org/GCC_Cross-Compiler and compile binutils and gcc from source. Everything else listed can be installed from a package manager.

To run the kernel use qemu, and run as "qemu-system-i386 -kernel kernel.bin
