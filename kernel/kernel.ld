SECTIONS
{

   .setup 0x100000 :
   {
      i386/boot.o
      i386/entry.o(.text*)
   }

   .text 0xc0000000 : AT ( ADDR(.setup) + SIZEOF ( .setup ) )
   {
      *(.text*)
      *(.gnu.linkonce.t*)
   }
   
   .rodata ALIGN (4096) : AT ( ADDR(.text) + SIZEOF ( .text ) )
   {
      start_ctors = .;
		*(.ctor*)
		end_ctors = .;

		start_dtors = .;
		*(.dtor*)
		end_dtors = .;

		*(.rodata*)
		*(.gnu.linkonce.r*)
   }
   
   .data ALIGN (4096) : AT ( ADDR(.rodata) + SIZEOF ( .rodata ) )
	{
		*(.data*)
		*(.gnu.linkonce.d*)
	}

	.bss ALIGN (4096) : AT ( ADDR(.data) + SIZEOF ( .data ) )
	{
		*(.COMMON*)
		*(.bss*)
		*(.gnu.linkonce.b*)
	}
	
	ktext_start = ADDR(.setup);
	kdata_end = ktext_start + SIZEOF(.setup) + SIZEOF(.text) + 
	            SIZEOF(.rodata) + SIZEOF(.data);
	kbss_end = kdata_end + SIZEOF(.bss);
	
}

