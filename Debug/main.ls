   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.13.3 - 22 May 2025
   3                     ; Generator (Limited) V4.6.6 - 07 Jan 2026
  43                     ; 6 void main(void)
  43                     ; 7 {
  45                     	switch	.text
  46  0000               _main:
  50                     ; 12     GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_IN_PU_NO_IT);
  52  0000 4b40          	push	#64
  53  0002 4b04          	push	#4
  54  0004 ae500f        	ldw	x,#20495
  55  0007 cd0000        	call	_GPIO_Init
  57  000a 85            	popw	x
  58                     ; 13     GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_PU_NO_IT);
  60  000b 4b40          	push	#64
  61  000d 4b08          	push	#8
  62  000f ae500f        	ldw	x,#20495
  63  0012 cd0000        	call	_GPIO_Init
  65  0015 85            	popw	x
  66                     ; 14     GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_IN_PU_NO_IT);
  68  0016 4b40          	push	#64
  69  0018 4b10          	push	#16
  70  001a ae500f        	ldw	x,#20495
  71  001d cd0000        	call	_GPIO_Init
  73  0020 85            	popw	x
  74                     ; 15     GPIO_Init(GPIOD, GPIO_PIN_7, GPIO_MODE_IN_PU_NO_IT);
  76  0021 4b40          	push	#64
  77  0023 4b80          	push	#128
  78  0025 ae500f        	ldw	x,#20495
  79  0028 cd0000        	call	_GPIO_Init
  81  002b 85            	popw	x
  82                     ; 17 }
  85  002c 81            	ret
  98                     	xdef	_main
  99                     	xref	_GPIO_Init
 118                     	end
