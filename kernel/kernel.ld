SECTIONS
{

   . = 0x100000;
   
   .text :
   {
      start_text = .;
      *(.text*)
      *(.gnu.linkonce.t*)
      end_text = .;
   }
   
   .rodata :
   {
      start_data = .;
      start_ctors = .;
		*(.ctor*)
		end_ctors = .;

		start_dtors = .;
		*(.dtor*)
		end_dtors = .;

		*(.rodata*)
		*(.gnu.linkonce.r*)
   }
   
   .data :
	{
		*(.data*)
		*(.gnu.linkonce.d*)
		end_data = .;
	}

	.bss :
	{
	   start_bss = .;
		*(.COMMON*)
		*(.bss*)
		*(.gnu.linkonce.b*)
		end_bss = .;
	}


}

