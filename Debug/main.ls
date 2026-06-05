   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.13.3 - 22 May 2025
   3                     ; Generator (Limited) V4.6.6 - 07 Jan 2026
  54                     ; 4 void main(void)
  54                     ; 5 {
  56                     	switch	.text
  57  0000               _main:
  61                     ; 6     CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  63  0000 4f            	clr	a
  64  0001 cd0000        	call	_CLK_HSIPrescalerConfig
  66                     ; 8     DIO_Init();
  68  0004 cd0000        	call	_DIO_Init
  70  0007               L12:
  71                     ; 14         Relay1_Set(Input1_Read());
  73  0007 cd0000        	call	_Input1_Read
  75  000a cd0000        	call	_Relay1_Set
  77                     ; 15         Relay2_Set(Input2_Read());
  79  000d cd0000        	call	_Input2_Read
  81  0010 cd0000        	call	_Relay2_Set
  83                     ; 16         Relay3_Set(Input3_Read());
  85  0013 cd0000        	call	_Input3_Read
  87  0016 cd0000        	call	_Relay3_Set
  89                     ; 17         Relay4_Set(Input4_Read());
  91  0019 cd0000        	call	_Input4_Read
  93  001c cd0000        	call	_Relay4_Set
  95                     ; 19         Relay5_Set(1);
  97  001f a601          	ld	a,#1
  98  0021 cd0000        	call	_Relay5_Set
 100                     ; 20         Relay6_Set(0);
 102  0024 4f            	clr	a
 103  0025 cd0000        	call	_Relay6_Set
 106  0028 20dd          	jra	L12
 119                     	xdef	_main
 120                     	xref	_Input4_Read
 121                     	xref	_Input3_Read
 122                     	xref	_Input2_Read
 123                     	xref	_Input1_Read
 124                     	xref	_Relay6_Set
 125                     	xref	_Relay5_Set
 126                     	xref	_Relay4_Set
 127                     	xref	_Relay3_Set
 128                     	xref	_Relay2_Set
 129                     	xref	_Relay1_Set
 130                     	xref	_DIO_Init
 131                     	xref	_CLK_HSIPrescalerConfig
 150                     	end
