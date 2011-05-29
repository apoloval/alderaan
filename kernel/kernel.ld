SECTIONS
{

   . = 0x100000;

   .setup :
   {
      i386/boot.o
      i386/entry.o(.text*)
      . = ALIGN(0x1000);
   }

	vma_ksetup     = ADDR(.setup);
	lma_ksetup     = ADDR(.setup);

   . = 0xc0000000 + . - 0x100000;

   .text : AT ( lma_ksetup + SIZEOF ( .setup ) )
   {
      *(.text*)
      *(.gnu.linkonce.t*)
      . = ALIGN(0x1000);
   }
   
	vma_ktext      = ADDR(.text);
	lma_ktext      = lma_ksetup + SIZEOF(.setup);

   .rodata : AT ( lma_ktext + SIZEOF ( .text ) )
   {
      start_ctors = .;
		*(.ctor*)
		end_ctors = .;

		start_dtors = .;
		*(.dtor*)
		end_dtors = .;

		*(.rodata*)
		*(.gnu.linkonce.r*)
      . = ALIGN(0x1000);
   }
   
	vma_krodata    = ADDR(.rodata);
	lma_krodata    = lma_ktext + SIZEOF(.text);

   .data : AT ( lma_krodata + SIZEOF ( .rodata ) )
	{
		*(.data*)
		*(.gnu.linkonce.d*)
      . = ALIGN(0x1000);
	}

	vma_kdata      = ADDR(.data);
	lma_kdata      = lma_krodata + SIZEOF(.rodata);

	.bss : AT ( lma_kdata + SIZEOF ( .data ) )
	{
		*(.COMMON*)
		*(.bss*)
		*(.gnu.linkonce.b*)
		. += 0x4000;
      . = ALIGN(0x1000);      
	}
	
	vma_kbss       = ADDR(.bss);	
	lma_kbss       = lma_kdata + SIZEOF(.data);
	
	lma_kstart     = lma_ksetup;
	lma_kend       = lma_kbss + SIZEOF(.bss);
		
}

