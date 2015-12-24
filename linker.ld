ENTRY (loader)

SECTIONS
{
    . = 1M;

    .text ALIGN (4K) :
    {
        _mb_header_addr = .;
        _mb_load_addr = .;
        *(.multiboot)
        *(.text)
    }

    .rodata ALIGN (4K) :
    {
        *(.rodata)
    }

    .data ALIGN (4K) :
    {
        *(.data)
        _mb_load_end_addr = .;
    }

    .bss ALIGN (4K) :
    {
        *(COMMON)
        *(.bss)
        _mb_bss_end_addr = .;
    }
   
    _kernel_end_addr = .; 
}

