;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.8.0 #10562 (Mac OS X x86_64)
;--------------------------------------------------------
	.module main
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _pool
	.globl _gator2_raw
	.globl _gator1_raw
	.globl _harry_raw
	.globl _pallet
	.globl _ST7735_Write
	.globl _SPI_transfer
	.globl _SPI_write
	.globl _SPI_init
	.globl _main
	.globl _drawGator
	.globl _clearHarry
	.globl _drawHarry
	.globl _drawscene
	.globl _init_clock
	.globl _clock
	.globl _ST7735_Write16
	.globl _ST7735_SetAddrWindow
	.globl _ST7735_DrawPixel
	.globl _ST7735_DrawLine
	.globl _ST7735_Init
	.globl _ST7735_Clear
	.globl _ST7735_Draw
	.globl _ST7735_Fill
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area INITIALIZED
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG
__start__stack:
	.ds	1

;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area DABS (ABS)

; default segment ordering for linker
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area CONST
	.area INITIALIZER
	.area CODE

;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------
	.area HOME
__interrupt_vect:
	int s_GSINIT ; reset
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area GSINIT
__sdcc_gs_init_startup:
__sdcc_init_data:
; stm8_genXINIT() start
	ldw x, #l_DATA
	jreq	00002$
00001$:
	clr (s_DATA - 1, x)
	decw x
	jrne	00001$
00002$:
	ldw	x, #l_INITIALIZER
	jreq	00004$
00003$:
	ld	a, (s_INITIALIZER - 1, x)
	ld	(s_INITIALIZED - 1, x), a
	decw	x
	jrne	00003$
00004$:
; stm8_genXINIT() end
	.area GSFINAL
	jp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME
	.area HOME
__sdcc_program_startup:
	jp	_main
;	return from main will return to caller
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CODE
;	main.c: 30: static inline void delay_ms(uint16_t ms) {
;	-----------------------------------------
;	 function delay_ms
;	-----------------------------------------
_delay_ms:
	sub	sp, #8
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	clrw	x
	ldw	(0x07, sp), x
	ldw	(0x05, sp), x
00103$:
	ldw	x, (0x0b, sp)
	pushw	x
	push	#0x6f
	push	#0x00
	call	___muluint2ulong
	addw	sp, #4
	ldw	(0x03, sp), x
	ldw	(0x01, sp), y
	ldw	x, (0x07, sp)
	cpw	x, (0x03, sp)
	ld	a, (0x06, sp)
	sbc	a, (0x02, sp)
	ld	a, (0x05, sp)
	sbc	a, (0x01, sp)
	jrnc	00105$
;	main.c: 33: __asm__("nop");
	nop
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	ldw	x, (0x07, sp)
	incw	x
	ldw	(0x07, sp), x
	jrne	00103$
	ldw	x, (0x05, sp)
	incw	x
	ldw	(0x05, sp), x
	jra	00103$
00105$:
;	main.c: 34: }
	addw	sp, #8
	ret
;	main.c: 36: unsigned int clock(void)
;	-----------------------------------------
;	 function clock
;	-----------------------------------------
_clock:
	sub	sp, #4
;	main.c: 38: unsigned char h = TIM1_CNTRH;
	ld	a, 0x525e
	ld	xh, a
;	main.c: 39: unsigned char l = TIM1_CNTRL;
	ld	a, 0x525f
;	main.c: 40: return((unsigned int)(h) << 8 | l);
	clr	(0x04, sp)
	clr	(0x01, sp)
	or	a, (0x04, sp)
	rlwa	x
	or	a, (0x01, sp)
	ld	xh, a
;	main.c: 41: }
	addw	sp, #4
	ret
;	main.c: 43: void init_clock(void) {
;	-----------------------------------------
;	 function init_clock
;	-----------------------------------------
_init_clock:
;	main.c: 44: CLK_CKDIVR = 0;//0x18; // Set the frequency to 2 MHz
	mov	0x50c6+0, #0x00
;	main.c: 45: CLK_PCKENR1 = 0x02; //SPI
	mov	0x50c7+0, #0x02
;	main.c: 46: CLK_PCKENR2 = 0x73; //off
	mov	0x50ca+0, #0x73
;	main.c: 48: }
	ret
;	main.c: 50: void drawscene(void) {
;	-----------------------------------------
;	 function drawscene
;	-----------------------------------------
_drawscene:
	sub	sp, #17
;	main.c: 52: ST7735_SetAddrWindow(0, 0, 160, 80);
	push	#0x50
	push	#0xa0
	push	#0x00
	push	#0x00
	call	_ST7735_SetAddrWindow
	addw	sp, #4
;	main.c: 53: for (int i=0; i<480; ++i)
	clrw	x
00137$:
	cpw	x, #0x01e0
	jrsge	00101$
;	main.c: 54: ST7735_Write16(RGB(17,72,0));
	pushw	x
	push	#0x40
	push	#0x12
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 53: for (int i=0; i<480; ++i)
	incw	x
	jra	00137$
00101$:
;	main.c: 57: for (int j=0; j<2; ++j) {
	clrw	x
	ldw	(0x10, sp), x
00155$:
	ldw	x, (0x10, sp)
	cpw	x, #0x0002
	jrsge	00107$
;	main.c: 58: for (int i=0; i<48; ++i)
	clrw	x
00140$:
	cpw	x, #0x0030
	jrsge	00102$
;	main.c: 59: ST7735_Write16(RGB(17,72,0));
	pushw	x
	push	#0x40
	push	#0x12
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 58: for (int i=0; i<48; ++i)
	incw	x
	jra	00140$
00102$:
;	main.c: 60: for (int i=0; i<16;++i)
	clrw	x
00143$:
	cpw	x, #0x0010
	jrsge	00103$
;	main.c: 61: ST7735_Write16(RGB(95,144,47));
	pushw	x
	push	#0x85
	push	#0x5c
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 60: for (int i=0; i<16;++i)
	incw	x
	jra	00143$
00103$:
;	main.c: 62: for (int i=0; i<32; ++i)
	clrw	x
00146$:
	cpw	x, #0x0020
	jrsge	00104$
;	main.c: 63: ST7735_Write16(RGB(17,72,0));
	pushw	x
	push	#0x40
	push	#0x12
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 62: for (int i=0; i<32; ++i)
	incw	x
	jra	00146$
00104$:
;	main.c: 64: for (int i=0; i<16;++i)
	clrw	x
00149$:
	cpw	x, #0x0010
	jrsge	00105$
;	main.c: 65: ST7735_Write16(RGB(95,144,47));
	pushw	x
	push	#0x85
	push	#0x5c
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 64: for (int i=0; i<16;++i)
	incw	x
	jra	00149$
00105$:
;	main.c: 66: for (int i=0; i<48; ++i)
	clrw	x
00152$:
	cpw	x, #0x0030
	jrsge	00156$
;	main.c: 67: ST7735_Write16(RGB(17,72,0));
	pushw	x
	push	#0x40
	push	#0x12
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 66: for (int i=0; i<48; ++i)
	incw	x
	jra	00152$
00156$:
;	main.c: 57: for (int j=0; j<2; ++j) {
	ldw	x, (0x10, sp)
	incw	x
	ldw	(0x10, sp), x
	jra	00155$
00107$:
;	main.c: 69: for (int j=0; j<2; ++j) {
	clrw	x
	ldw	(0x0e, sp), x
00173$:
	ldw	x, (0x0e, sp)
	cpw	x, #0x0002
	jrsge	00113$
;	main.c: 70: for (int i=0; i<32; ++i)
	clrw	x
00158$:
	cpw	x, #0x0020
	jrsge	00108$
;	main.c: 71: ST7735_Write16(RGB(17,72,0));
	pushw	x
	push	#0x40
	push	#0x12
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 70: for (int i=0; i<32; ++i)
	incw	x
	jra	00158$
00108$:
;	main.c: 72: for (int i=0; i<40;++i)
	clrw	x
00161$:
	cpw	x, #0x0028
	jrsge	00109$
;	main.c: 73: ST7735_Write16(RGB(95,144,47));
	pushw	x
	push	#0x85
	push	#0x5c
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 72: for (int i=0; i<40;++i)
	incw	x
	jra	00161$
00109$:
;	main.c: 74: for (int i=0; i<16; ++i)
	clrw	x
00164$:
	cpw	x, #0x0010
	jrsge	00110$
;	main.c: 75: ST7735_Write16(RGB(17,72,0));
	pushw	x
	push	#0x40
	push	#0x12
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 74: for (int i=0; i<16; ++i)
	incw	x
	jra	00164$
00110$:
;	main.c: 76: for (int i=0; i<40;++i)
	clrw	x
00167$:
	cpw	x, #0x0028
	jrsge	00111$
;	main.c: 77: ST7735_Write16(RGB(95,144,47));
	pushw	x
	push	#0x85
	push	#0x5c
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 76: for (int i=0; i<40;++i)
	incw	x
	jra	00167$
00111$:
;	main.c: 78: for (int i=0; i<32; ++i)
	clrw	x
00170$:
	cpw	x, #0x0020
	jrsge	00174$
;	main.c: 79: ST7735_Write16(RGB(17,72,0));
	pushw	x
	push	#0x40
	push	#0x12
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 78: for (int i=0; i<32; ++i)
	incw	x
	jra	00170$
00174$:
;	main.c: 69: for (int j=0; j<2; ++j) {
	ldw	x, (0x0e, sp)
	incw	x
	ldw	(0x0e, sp), x
	jra	00173$
00113$:
;	main.c: 82: for (int j=0; j<2; ++j){
	clrw	x
	ldw	(0x0c, sp), x
00203$:
	ldw	x, (0x0c, sp)
	cpw	x, #0x0002
	jrslt	00657$
	jp	00123$
00657$:
;	main.c: 83: for (int i=0; i<8; ++i)
	clrw	x
00176$:
	cpw	x, #0x0008
	jrsge	00114$
;	main.c: 84: ST7735_Write16(RGB(17,72,0));
	pushw	x
	push	#0x40
	push	#0x12
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 83: for (int i=0; i<8; ++i)
	incw	x
	jra	00176$
00114$:
;	main.c: 85: for (int i=0; i<16; ++i)
	clrw	x
00179$:
	cpw	x, #0x0010
	jrsge	00115$
;	main.c: 86: ST7735_Write16(RGB(17,72,0));
	pushw	x
	push	#0x40
	push	#0x12
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 85: for (int i=0; i<16; ++i)
	incw	x
	jra	00179$
00115$:
;	main.c: 87: for (int i=0; i<2;++i)
	clrw	x
00182$:
	cpw	x, #0x0002
	jrsge	00116$
;	main.c: 88: ST7735_Write16(RGB(8,27,0));
	pushw	x
	push	#0xc0
	push	#0x08
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 87: for (int i=0; i<2;++i)
	incw	x
	jra	00182$
00116$:
;	main.c: 89: for (int i=0; i<2;++i)
	clrw	x
00185$:
	cpw	x, #0x0002
	jrsge	00117$
;	main.c: 90: ST7735_Write16(j?RGB(95,144,47):RGB(8,27,0));
	ldw	y, (0x0c, sp)
	jreq	00243$
	ldw	y, #0x5c85
	jra	00244$
00243$:
	ldw	y, #0x08c0
00244$:
	pushw	x
	pushw	y
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 89: for (int i=0; i<2;++i)
	incw	x
	jra	00185$
00117$:
;	main.c: 91: for (int i=0; i<104;++i)
	clrw	x
00188$:
	cpw	x, #0x0068
	jrsge	00118$
;	main.c: 92: ST7735_Write16(RGB(95,144,47));
	pushw	x
	push	#0x85
	push	#0x5c
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 91: for (int i=0; i<104;++i)
	incw	x
	jra	00188$
00118$:
;	main.c: 93: for (int i=0; i<2;++i)
	clrw	x
00191$:
	cpw	x, #0x0002
	jrsge	00119$
;	main.c: 94: ST7735_Write16(j?RGB(95,144,47):RGB(8,27,0));
	ldw	y, (0x0c, sp)
	jreq	00245$
	ldw	y, #0x5c85
	jra	00246$
00245$:
	ldw	y, #0x08c0
00246$:
	pushw	x
	pushw	y
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 93: for (int i=0; i<2;++i)
	incw	x
	jra	00191$
00119$:
;	main.c: 95: for (int i=0; i<2;++i)
	clrw	x
00194$:
	cpw	x, #0x0002
	jrsge	00120$
;	main.c: 96: ST7735_Write16(RGB(8,27,0));
	pushw	x
	push	#0xc0
	push	#0x08
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 95: for (int i=0; i<2;++i)
	incw	x
	jra	00194$
00120$:
;	main.c: 97: for (int i=0; i<16; ++i)
	clrw	x
00197$:
	cpw	x, #0x0010
	jrsge	00121$
;	main.c: 98: ST7735_Write16(RGB(17,72,0));
	pushw	x
	push	#0x40
	push	#0x12
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 97: for (int i=0; i<16; ++i)
	incw	x
	jra	00197$
00121$:
;	main.c: 99: for (int i=0; i<8; ++i)
	clrw	x
00200$:
	cpw	x, #0x0008
	jrsge	00204$
;	main.c: 100: ST7735_Write16(RGB(17,72,0));
	pushw	x
	push	#0x40
	push	#0x12
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 99: for (int i=0; i<8; ++i)
	incw	x
	jra	00200$
00204$:
;	main.c: 82: for (int j=0; j<2; ++j){
	ldw	x, (0x0c, sp)
	incw	x
	ldw	(0x0c, sp), x
	jp	00203$
00123$:
;	main.c: 103: for (int j=0; j<52; ++j) {
	clrw	x
	ldw	(0x0a, sp), x
00221$:
	ldw	x, (0x0a, sp)
	cpw	x, #0x0034
	jrsge	00129$
;	main.c: 104: for (int i=0; i<16;++i)
	clrw	x
00206$:
	cpw	x, #0x0010
	jrsge	00124$
;	main.c: 105: ST7735_Write16(RGB(95,144,47));
	pushw	x
	push	#0x85
	push	#0x5c
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 104: for (int i=0; i<16;++i)
	incw	x
	jra	00206$
00124$:
;	main.c: 106: for (int i=0; i<8;++i)
	clrw	x
00209$:
	cpw	x, #0x0008
	jrsge	00125$
;	main.c: 107: ST7735_Write16(RGB(8,27,0));
	pushw	x
	push	#0xc0
	push	#0x08
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 106: for (int i=0; i<8;++i)
	incw	x
	jra	00209$
00125$:
;	main.c: 108: for (int i=0; i<112;++i)
	clrw	x
00212$:
	cpw	x, #0x0070
	jrsge	00126$
;	main.c: 109: ST7735_Write16(RGB(95,144,47));
	pushw	x
	push	#0x85
	push	#0x5c
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 108: for (int i=0; i<112;++i)
	incw	x
	jra	00212$
00126$:
;	main.c: 110: for (int i=0; i<8;++i)
	clrw	x
00215$:
	cpw	x, #0x0008
	jrsge	00127$
;	main.c: 111: ST7735_Write16(RGB(8,27,0));
	pushw	x
	push	#0xc0
	push	#0x08
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 110: for (int i=0; i<8;++i)
	incw	x
	jra	00215$
00127$:
;	main.c: 112: for (int i=0; i<16;++i)
	clrw	x
00218$:
	cpw	x, #0x0010
	jrsge	00222$
;	main.c: 113: ST7735_Write16(RGB(95,144,47));
	pushw	x
	push	#0x85
	push	#0x5c
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 112: for (int i=0; i<16;++i)
	incw	x
	jra	00218$
00222$:
;	main.c: 103: for (int j=0; j<52; ++j) {
	ldw	x, (0x0a, sp)
	incw	x
	ldw	(0x0a, sp), x
	jra	00221$
00129$:
;	main.c: 116: for (int j=0; j<16; ++j) {
	clrw	x
	ldw	(0x08, sp), x
00233$:
	ldw	x, (0x08, sp)
	cpw	x, #0x0010
	jrsge	00133$
;	main.c: 117: uint8_t r = pool[j];
	ldw	x, (0x08, sp)
	addw	x, #_pool
	ld	a, (x)
;	main.c: 118: uint8_t t = 80-r/2;
	ld	(0x04, sp), a
	clr	(0x03, sp)
	push	#0x02
	push	#0x00
	ldw	x, (0x05, sp)
	pushw	x
	call	__divsint
	addw	sp, #4
	ld	a, #0x50
	pushw	x
	sub	a, (#2, sp)
	popw	x
	ld	(0x07, sp), a
;	main.c: 119: for (int i=0; i<t; ++i)
	clrw	x
00224$:
	ld	a, (0x07, sp)
	ld	(0x02, sp), a
	clr	(0x01, sp)
	cpw	x, (0x01, sp)
	jrsge	00130$
;	main.c: 120: ST7735_Write16(RGB(159,174,29));
	pushw	x
	push	#0x63
	push	#0x9d
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 119: for (int i=0; i<t; ++i)
	incw	x
	jra	00224$
00130$:
;	main.c: 121: for (int i=0; i<r; ++i)
	clrw	x
00227$:
	cpw	x, (0x03, sp)
	jrsge	00131$
;	main.c: 122: ST7735_Write16(RGB(27,98,139));
	pushw	x
	push	#0x11
	push	#0x1b
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 121: for (int i=0; i<r; ++i)
	incw	x
	jra	00227$
00131$:
;	main.c: 123: for (int i=0; i<t; ++i)
	clrw	x
00230$:
	cpw	x, (0x01, sp)
	jrsge	00234$
;	main.c: 124: ST7735_Write16(RGB(159,174,29));
	pushw	x
	push	#0x63
	push	#0x9d
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 123: for (int i=0; i<t; ++i)
	incw	x
	jra	00230$
00234$:
;	main.c: 116: for (int j=0; j<16; ++j) {
	ldw	x, (0x08, sp)
	incw	x
	ldw	(0x08, sp), x
	jra	00233$
00133$:
;	main.c: 126: for (int j=0; j<3; ++j) 
	clrw	x
	ldw	(0x05, sp), x
00239$:
	ldw	x, (0x05, sp)
	cpw	x, #0x0003
	jrsge	00241$
;	main.c: 127: for (int i=0; i<160; ++i)
	clrw	x
00236$:
	cpw	x, #0x00a0
	jrsge	00240$
;	main.c: 128: ST7735_Write16(RGB(88,104,0)); 
	pushw	x
	push	#0x40
	push	#0x5b
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 127: for (int i=0; i<160; ++i)
	incw	x
	jra	00236$
00240$:
;	main.c: 126: for (int j=0; j<3; ++j) 
	ldw	x, (0x05, sp)
	incw	x
	ldw	(0x05, sp), x
	jra	00239$
00241$:
;	main.c: 129: }
	addw	sp, #17
	ret
;	main.c: 131: void drawHarry(int x, int y) {
;	-----------------------------------------
;	 function drawHarry
;	-----------------------------------------
_drawHarry:
	sub	sp, #7
;	main.c: 132: for (int j=0; j<15; ++j)
	clrw	x
	ldw	(0x01, sp), x
00109$:
	ldw	x, (0x01, sp)
	cpw	x, #0x000f
	jrsge	00111$
;	main.c: 133: for (int i=0; i<8; ++i) 
	ldw	x, (0x0c, sp)
	addw	x, (0x01, sp)
	ldw	(0x05, sp), x
	clrw	x
	ldw	(0x03, sp), x
00106$:
	ldw	x, (0x03, sp)
	cpw	x, #0x0008
	jrsge	00110$
;	main.c: 135: uint8_t d = harry_raw[j*8 + i];
	ld	a, (0x02, sp)
	sll	a
	sll	a
	sll	a
	ld	(0x07, sp), a
	ld	a, (0x04, sp)
	add	a, (0x07, sp)
	ld	xl, a
	rlc	a
	clr	a
	sbc	a, #0x00
	ld	xh, a
	addw	x, #_harry_raw
	ld	a, (x)
;	main.c: 136: uint8_t b1 = HIGH_NIB(d);
	swap	a
	and	a, #0x0f
	and	a, #0x0f
;	main.c: 138: if (b1 != 2)
	cp	a, #0x02
	jreq	00107$
;	main.c: 139: ST7735_DrawPixel(x+i*2,y+j, pallet[b1]);
	clrw	x
	ld	xl, a
	sllw	x
	addw	x, #_pallet
	ldw	x, (x)
	ldw	y, (0x03, sp)
	sllw	y
	addw	y, (0x0a, sp)
	pushw	x
	ldw	x, (0x07, sp)
	pushw	x
	pushw	y
	call	_ST7735_DrawPixel
	addw	sp, #6
00107$:
;	main.c: 133: for (int i=0; i<8; ++i) 
	ldw	x, (0x03, sp)
	incw	x
	ldw	(0x03, sp), x
	jra	00106$
00110$:
;	main.c: 132: for (int j=0; j<15; ++j)
	ldw	x, (0x01, sp)
	incw	x
	ldw	(0x01, sp), x
	jra	00109$
00111$:
;	main.c: 143: }
	addw	sp, #7
	ret
;	main.c: 145: void clearHarry(int x, int y) {
;	-----------------------------------------
;	 function clearHarry
;	-----------------------------------------
_clearHarry:
	sub	sp, #10
;	main.c: 146: for (int j=0; j<15; ++j)
	clrw	x
	ldw	(0x09, sp), x
00112$:
	ldw	x, (0x09, sp)
	cpw	x, #0x000f
	jrsge	00114$
;	main.c: 147: for (int i=0; i<8; ++i) 
	ldw	x, (0x0f, sp)
	addw	x, (0x09, sp)
	ldw	(0x01, sp), x
	clrw	x
	ldw	(0x03, sp), x
00109$:
	ldw	x, (0x03, sp)
	cpw	x, #0x0008
	jrsge	00113$
;	main.c: 149: uint8_t d = harry_raw[j*8 + i];
	ld	a, (0x0a, sp)
	sll	a
	sll	a
	sll	a
	ld	xl, a
	ld	a, (0x04, sp)
	ld	(0x08, sp), a
	addw	x, (7, sp)
	ld	a, xl
	rlc	a
	clr	a
	sbc	a, #0x00
	ld	xh, a
	addw	x, #_harry_raw
	ld	a, (x)
;	main.c: 150: uint8_t b1 = HIGH_NIB(d);
	swap	a
	and	a, #0x0f
	and	a, #0x0f
;	main.c: 152: uint16_t c = RGB(95,144,47);
	ldw	x, #0x5c85
	ldw	(0x05, sp), x
;	main.c: 153: if (b1 != 2) {
	cp	a, #0x02
	jreq	00110$
;	main.c: 154: uint8_t cx = (x+2*i);
	ld	a, (0x0e, sp)
	ld	(0x07, sp), a
	ld	a, (0x08, sp)
	sll	a
	add	a, (0x07, sp)
;	main.c: 155: if ((cx<23) || (cx>135))
	cp	a, #0x17
	jrc	00101$
	cp	a, #0x87
	jrule	00102$
00101$:
;	main.c: 156: c = RGB(8,27,0);
	ldw	x, #0x08c0
	ldw	(0x05, sp), x
00102$:
;	main.c: 157: ST7735_DrawPixel(cx,y+j, c);
	clrw	x
	ld	xl, a
	ldw	y, (0x05, sp)
	pushw	y
	ldw	y, (0x03, sp)
	pushw	y
	pushw	x
	call	_ST7735_DrawPixel
	addw	sp, #6
00110$:
;	main.c: 147: for (int i=0; i<8; ++i) 
	ldw	x, (0x03, sp)
	incw	x
	ldw	(0x03, sp), x
	jra	00109$
00113$:
;	main.c: 146: for (int j=0; j<15; ++j)
	ldw	x, (0x09, sp)
	incw	x
	ldw	(0x09, sp), x
	jra	00112$
00114$:
;	main.c: 166: }
	addw	sp, #10
	ret
;	main.c: 168: void drawGator(int x, int y, int id) {
;	-----------------------------------------
;	 function drawGator
;	-----------------------------------------
_drawGator:
	sub	sp, #11
;	main.c: 169: for (int j=0; j<8; ++j)
	clrw	x
	ldw	(0x0a, sp), x
00109$:
	ldw	x, (0x0a, sp)
	cpw	x, #0x0008
	jrsge	00111$
;	main.c: 170: for (int i=0; i<8; ++i) 
	ldw	x, (0x10, sp)
	addw	x, (0x0a, sp)
	ldw	(0x08, sp), x
	clrw	x
	ldw	(0x01, sp), x
00106$:
	ldw	x, (0x01, sp)
	cpw	x, #0x0008
	jrsge	00110$
;	main.c: 172: uint8_t d = id?gator1_raw[j*8 + i]:gator2_raw[j*8 + i];
	ld	a, (0x0b, sp)
	push	a
	ld	a, (0x03, sp)
	ld	(0x08, sp), a
	pop	a
	sll	a
	sll	a
	sll	a
	add	a, (0x07, sp)
	ld	(0x06, sp), a
	ld	a, (0x06, sp)
	rlc	a
	clr	a
	sbc	a, #0x00
	ld	(0x05, sp), a
	ldw	x, (0x12, sp)
	jreq	00113$
	ldw	x, (0x05, sp)
	addw	x, #_gator1_raw
	ld	a, (x)
	jra	00114$
00113$:
	ldw	x, (0x05, sp)
	addw	x, #_gator2_raw
	ldw	(0x03, sp), x
	ld	a, (x)
00114$:
;	main.c: 173: uint8_t b1 = HIGH_NIB(d);
	swap	a
	and	a, #0x0f
	and	a, #0x0f
;	main.c: 175: if (b1 != 2)
	cp	a, #0x02
	jreq	00107$
;	main.c: 176: ST7735_DrawPixel(x+i*2,y+j, pallet[b1]);
	clrw	x
	ld	xl, a
	sllw	x
	addw	x, #_pallet
	ldw	x, (x)
	ldw	y, (0x01, sp)
	sllw	y
	addw	y, (0x0e, sp)
	pushw	x
	ldw	x, (0x0a, sp)
	pushw	x
	pushw	y
	call	_ST7735_DrawPixel
	addw	sp, #6
00107$:
;	main.c: 170: for (int i=0; i<8; ++i) 
	ldw	x, (0x01, sp)
	incw	x
	ldw	(0x01, sp), x
	jra	00106$
00110$:
;	main.c: 169: for (int j=0; j<8; ++j)
	ldw	x, (0x0a, sp)
	incw	x
	ldw	(0x0a, sp), x
	jra	00109$
00111$:
;	main.c: 180: }
	addw	sp, #11
	ret
;	main.c: 182: void main(void)
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
	sub	sp, #125
;	main.c: 184: const uint8_t sine[48] = {
	ldw	x, sp
	addw	x, #49
	ldw	(0x61, sp), x
	ld	a, #0x37
	ld	(x), a
	ldw	x, (0x61, sp)
	incw	x
	ld	a, #0x3e
	ld	(x), a
	ldw	x, (0x61, sp)
	incw	x
	incw	x
	ld	a, #0x45
	ld	(x), a
	ldw	x, (0x61, sp)
	ld	a, #0x4b
	ld	(0x0003, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x52
	ld	(0x0004, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x58
	ld	(0x0005, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x5d
	ld	(0x0006, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x62
	ld	(0x0007, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x66
	ld	(0x0008, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x69
	ld	(0x0009, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x6b
	ld	(0x000a, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x6d
	ld	(0x000b, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x6d
	ld	(0x000c, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x6d
	ld	(0x000d, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x6b
	ld	(0x000e, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x69
	ld	(0x000f, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x66
	ld	(0x0010, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x62
	ld	(0x0011, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x5d
	ld	(0x0012, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x58
	ld	(0x0013, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x52
	ld	(0x0014, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x4b
	ld	(0x0015, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x45
	ld	(0x0016, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x3e
	ld	(0x0017, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x37
	ld	(0x0018, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x2f
	ld	(0x0019, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x28
	ld	(0x001a, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x22
	ld	(0x001b, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x1b
	ld	(0x001c, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x15
	ld	(0x001d, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x10
	ld	(0x001e, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x0b
	ld	(0x001f, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x07
	ld	(0x0020, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x04
	ld	(0x0021, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x02
	ld	(0x0022, x), a
	ldw	x, (0x61, sp)
	clr	(0x0023, x)
	ldw	x, (0x61, sp)
	clr	(0x0024, x)
	ldw	x, (0x61, sp)
	clr	(0x0025, x)
	ldw	x, (0x61, sp)
	ld	a, #0x02
	ld	(0x0026, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x04
	ld	(0x0027, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x07
	ld	(0x0028, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x0b
	ld	(0x0029, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x10
	ld	(0x002a, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x15
	ld	(0x002b, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x1b
	ld	(0x002c, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x22
	ld	(0x002d, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x28
	ld	(0x002e, x), a
	ldw	x, (0x61, sp)
	ld	a, #0x2f
	ld	(0x002f, x), a
;	main.c: 189: const uint8_t cos[48] = {
	ldw	x, sp
	incw	x
	ldw	(0x6f, sp), x
	ld	a, #0x0d
	ld	(x), a
	ldw	x, (0x6f, sp)
	incw	x
	ld	a, #0x0d
	ld	(x), a
	ldw	x, (0x6f, sp)
	incw	x
	incw	x
	ld	a, #0x0d
	ld	(x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0c
	ld	(0x0003, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0b
	ld	(0x0004, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0a
	ld	(0x0005, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x09
	ld	(0x0006, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x08
	ld	(0x0007, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x06
	ld	(0x0008, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x05
	ld	(0x0009, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x03
	ld	(0x000a, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x01
	ld	(0x000b, x), a
	ldw	x, (0x6f, sp)
	clr	(0x000c, x)
	ldw	x, (0x6f, sp)
	ld	a, #0x02
	ld	(0x000d, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x03
	ld	(0x000e, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x05
	ld	(0x000f, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x07
	ld	(0x0010, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x08
	ld	(0x0011, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x09
	ld	(0x0012, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0b
	ld	(0x0013, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0c
	ld	(0x0014, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0c
	ld	(0x0015, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0d
	ld	(0x0016, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0d
	ld	(0x0017, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0d
	ld	(0x0018, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0d
	ld	(0x0019, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0d
	ld	(0x001a, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0c
	ld	(0x001b, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0c
	ld	(0x001c, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0b
	ld	(0x001d, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x09
	ld	(0x001e, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x08
	ld	(0x001f, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x07
	ld	(0x0020, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x05
	ld	(0x0021, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x03
	ld	(0x0022, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x02
	ld	(0x0023, x), a
	ldw	x, (0x6f, sp)
	clr	(0x0024, x)
	ldw	x, (0x6f, sp)
	ld	a, #0x01
	ld	(0x0025, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x03
	ld	(0x0026, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x05
	ld	(0x0027, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x06
	ld	(0x0028, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x08
	ld	(0x0029, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x09
	ld	(0x002a, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0a
	ld	(0x002b, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0b
	ld	(0x002c, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0c
	ld	(0x002d, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0d
	ld	(0x002e, x), a
	ldw	x, (0x6f, sp)
	ld	a, #0x0d
	ld	(0x002f, x), a
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	clrw	y
	clrw	x
	ldw	(0x71, sp), x
00113$:
	cpw	y, #0x14c8
	ld	a, (0x72, sp)
	sbc	a, #0x05
	ld	a, (0x71, sp)
	sbc	a, #0x00
	jrnc	00109$
;	main.c: 33: __asm__("nop");
	nop
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	incw	y
	jrne	00113$
	ldw	x, (0x71, sp)
	incw	x
	ldw	(0x71, sp), x
	jra	00113$
;	main.c: 194: delay_ms(3000);
00109$:
;	main.c: 196: init_clock();
	call	_init_clock
;	main.c: 197: ST7735_Init();
	call	_ST7735_Init
;	main.c: 199: __asm__ ("rim"); //enable interrupts
	rim
;	main.c: 207: drawscene();
	call	_drawscene
;	main.c: 210: uint8_t lx =80;
	ld	a, #0x50
	ld	(0x7d, sp), a
;	main.c: 211: uint8_t ly =20;
	ld	a, #0x14
	ld	(0x7c, sp), a
;	main.c: 213: while(1) {
	clrw	x
	ldw	(0x67, sp), x
	ldw	(0x65, sp), x
00106$:
;	main.c: 214: uint8_t x = 24 + sine[frame%48];
	push	#0x30
	clrw	x
	pushw	x
	push	#0x00
	ldw	x, (0x6b, sp)
	pushw	x
	ldw	x, (0x6b, sp)
	pushw	x
	call	__modulong
	addw	sp, #8
	ldw	(0x6b, sp), y
	ldw	y, x
	addw	y, (0x61, sp)
	ld	a, (y)
	add	a, #0x18
	ld	(0x7b, sp), a
;	main.c: 215: uint8_t y = 36 + cos[frame%48];
	addw	x, (0x6f, sp)
	ld	a, (x)
	add	a, #0x24
	ld	(0x7a, sp), a
;	main.c: 216: ST7735_DrawLine(80, 0, lx, ly, RGB(95,144,47));
	clrw	y
	ld	a, (0x7c, sp)
	ld	yl, a
	clrw	x
	ld	a, (0x7d, sp)
	ld	xl, a
	pushw	x
	pushw	y
	push	#0x85
	push	#0x5c
	pushw	y
	pushw	x
	push	#0x00
	push	#0x00
	push	#0x50
	push	#0x00
	call	_ST7735_DrawLine
	addw	sp, #10
	popw	y
	popw	x
;	main.c: 217: clearHarry(lx-8,ly-2);
	subw	y, #0x0002
	subw	x, #0x0008
	pushw	y
	pushw	x
	call	_clearHarry
	addw	sp, #4
;	main.c: 218: ST7735_Fill(30, 61, 100, 1, RGB(159,174,29));
	push	#0x63
	push	#0x9d
	push	#0x01
	push	#0x64
	push	#0x3d
	push	#0x1e
	call	_ST7735_Fill
	addw	sp, #6
;	main.c: 219: ST7735_Fill(23, 34, 1, 24, RGB(8,27,0));
	push	#0xc0
	push	#0x08
	push	#0x18
	push	#0x01
	push	#0x22
	push	#0x17
	call	_ST7735_Fill
	addw	sp, #6
;	main.c: 220: ST7735_Fill(136, 34, 1, 24, RGB(8,27,0));
	push	#0xc0
	push	#0x08
	push	#0x18
	push	#0x01
	push	#0x22
	push	#0x88
	call	_ST7735_Fill
	addw	sp, #6
;	main.c: 221: ST7735_DrawLine(80, 0, x, y, RGB(8,27,0));
	clrw	y
	ld	a, (0x7a, sp)
	ld	yl, a
	clrw	x
	ld	a, (0x7b, sp)
	ld	xl, a
	pushw	x
	pushw	y
	push	#0xc0
	push	#0x08
	pushw	y
	pushw	x
	push	#0x00
	push	#0x00
	push	#0x50
	push	#0x00
	call	_ST7735_DrawLine
	addw	sp, #10
	popw	y
	popw	x
;	main.c: 222: drawHarry(x-8,y-2);
	subw	y, #0x0002
	subw	x, #0x0008
	pushw	y
	pushw	x
	call	_drawHarry
	addw	sp, #4
;	main.c: 224: ST7735_SetAddrWindow(0, 63, 160, 4);
	push	#0x04
	push	#0xa0
	push	#0x3f
	push	#0x00
	call	_ST7735_SetAddrWindow
	addw	sp, #4
;	main.c: 225: for (int j=2; j<6; ++j) {
	ldw	x, #0x0002
	ldw	(0x78, sp), x
00125$:
	ldw	x, (0x78, sp)
	cpw	x, #0x0006
	jrsge	00104$
;	main.c: 226: uint8_t r = pool[j];
	ldw	x, (0x78, sp)
	addw	x, #_pool
	ld	a, (x)
;	main.c: 227: uint8_t t = 80-r/2;
	ld	(0x6a, sp), a
	clr	(0x69, sp)
	push	#0x02
	push	#0x00
	ldw	x, (0x6b, sp)
	pushw	x
	call	__divsint
	addw	sp, #4
	ld	a, #0x50
	pushw	x
	sub	a, (#2, sp)
	popw	x
	ld	(0x77, sp), a
;	main.c: 228: for (int i=0; i<t; ++i)
	clrw	x
00116$:
	ld	a, (0x77, sp)
	ld	(0x64, sp), a
	clr	(0x63, sp)
	cpw	x, (0x63, sp)
	jrsge	00101$
;	main.c: 229: ST7735_Write16(RGB(159,174,29));
	pushw	x
	push	#0x63
	push	#0x9d
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 228: for (int i=0; i<t; ++i)
	incw	x
	jra	00116$
00101$:
;	main.c: 230: for (int i=0; i<r; ++i)
	clrw	x
00119$:
	cpw	x, (0x69, sp)
	jrsge	00102$
;	main.c: 231: ST7735_Write16(RGB(27,98,139));
	pushw	x
	push	#0x11
	push	#0x1b
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 230: for (int i=0; i<r; ++i)
	incw	x
	jra	00119$
00102$:
;	main.c: 232: for (int i=0; i<t; ++i)
	clrw	x
	ldw	(0x75, sp), x
00122$:
	ldw	x, (0x75, sp)
	cpw	x, (0x63, sp)
	jrsge	00126$
;	main.c: 233: ST7735_Write16(RGB(159,174,29));
	push	#0x63
	push	#0x9d
	call	_ST7735_Write16
	addw	sp, #2
;	main.c: 232: for (int i=0; i<t; ++i)
	ldw	x, (0x75, sp)
	incw	x
	ldw	(0x75, sp), x
	jra	00122$
00126$:
;	main.c: 225: for (int j=2; j<6; ++j) {
	ldw	x, (0x78, sp)
	incw	x
	ldw	(0x78, sp), x
	jra	00125$
00104$:
;	main.c: 236: drawGator(40, 64, (frame%64)<32);
	ld	a, (0x68, sp)
	and	a, #0x3f
	ld	xl, a
	clr	a
	ld	xh, a
	clrw	y
	cpw	x, #0x0020
	ld	a, yl
	sbc	a, #0x00
	ld	a, yh
	sbc	a, #0x00
	clr	a
	rlc	a
	clrw	x
	ld	xl, a
	pushw	x
	pushw	x
	push	#0x40
	push	#0x00
	push	#0x28
	push	#0x00
	call	_drawGator
	addw	sp, #6
	popw	x
;	main.c: 237: drawGator(72, 64, (frame%64)<32);
	pushw	x
	pushw	x
	push	#0x40
	push	#0x00
	push	#0x48
	push	#0x00
	call	_drawGator
	addw	sp, #6
	push	#0x40
	push	#0x00
	push	#0x68
	push	#0x00
	call	_drawGator
	addw	sp, #6
;	main.c: 239: frame++;
	ldw	x, (0x67, sp)
	incw	x
	ldw	(0x67, sp), x
	jrne	00210$
	ldw	x, (0x65, sp)
	incw	x
	ldw	(0x65, sp), x
00210$:
;	main.c: 240: lx = x;
	ld	a, (0x7b, sp)
	ld	(0x7d, sp), a
;	main.c: 241: ly = y;
	ld	a, (0x7a, sp)
	ld	(0x7c, sp), a
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	clrw	y
	clrw	x
00128$:
	cpw	y, #0x56b8
	ld	a, xl
	sbc	a, #0x00
	ld	a, xh
	sbc	a, #0x00
	jrc	00211$
	jp	00106$
00211$:
;	main.c: 33: __asm__("nop");
	nop
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	incw	y
	jrne	00128$
	incw	x
	jra	00128$
;	main.c: 244: delay_ms(200);
;	main.c: 248: }
	addw	sp, #125
	ret
;	main.c: 256: void SPI_init() {
;	-----------------------------------------
;	 function SPI_init
;	-----------------------------------------
_SPI_init:
;	main.c: 258: PC_DDR |= (1<<5) | (1<<6); // clock and MOSI
	ld	a, 0x500c
	or	a, #0x60
	ld	0x500c, a
;	main.c: 259: PC_CR1 |= (1<<5) | (1<<6) | (1<<7);
	ld	a, 0x500d
	or	a, #0xe0
	ld	0x500d, a
;	main.c: 263: SPI_CR2 = SPI_CR2_SSM | SPI_CR2_SSI;
	mov	0x5201+0, #0x03
;	main.c: 264: SPI_CR1 = SPI_CR1_MSTR;// | SPI_CR1_BR(3);
	mov	0x5200+0, #0x04
;	main.c: 265: SPI_CR1 |= SPI_CR1_SPE;
	bset	20992, #6
;	main.c: 266: }
	ret
;	main.c: 268: void SPI_write(uint8_t data) {
;	-----------------------------------------
;	 function SPI_write
;	-----------------------------------------
_SPI_write:
;	main.c: 269: SPI_DR = data;
	ldw	x, #0x5204
	ld	a, (0x03, sp)
	ld	(x), a
;	main.c: 270: while (!(SPI_SR & SPI_SR_TXE));
00101$:
	ld	a, 0x5203
	bcp	a, #0x02
	jreq	00101$
;	main.c: 271: }
	ret
;	main.c: 273: void SPI_transfer(uint8_t *data, size_t len) {
;	-----------------------------------------
;	 function SPI_transfer
;	-----------------------------------------
_SPI_transfer:
;	main.c: 274: for (size_t i=0; i< len; ++i) {
	clrw	x
00103$:
	cpw	x, (0x05, sp)
	jrc	00118$
	ret
00118$:
;	main.c: 275: SPI_write(data[i]);
	ldw	y, x
	addw	y, (0x03, sp)
	ld	a, (y)
	pushw	x
	push	a
	call	_SPI_write
	pop	a
	popw	x
;	main.c: 274: for (size_t i=0; i< len; ++i) {
	incw	x
	jra	00103$
;	main.c: 277: }
	ret
;	main.c: 283: void ST7735_Write(uint8_t val, uint8_t cmd) {
;	-----------------------------------------
;	 function ST7735_Write
;	-----------------------------------------
_ST7735_Write:
;	main.c: 285: PA_ODR &= ~(1 << DC_PIN);
	ld	a, 0x5000
;	main.c: 284: if (cmd==CMD)
	tnz	(0x04, sp)
	jrne	00102$
;	main.c: 285: PA_ODR &= ~(1 << DC_PIN);
	and	a, #0xf7
	ld	0x5000, a
	jra	00103$
00102$:
;	main.c: 287: PA_ODR |= (1 << DC_PIN);
	or	a, #0x08
	ld	0x5000, a
00103$:
;	main.c: 288: SPI_write(val);
	ld	a, (0x03, sp)
	push	a
	call	_SPI_write
	pop	a
;	main.c: 291: PA_ODR |= (1 << DC_PIN);
	bset	20480, #3
;	main.c: 292: }
	ret
;	main.c: 302: void ST7735_Write16(uint16_t value) {
;	-----------------------------------------
;	 function ST7735_Write16
;	-----------------------------------------
_ST7735_Write16:
	sub	sp, #2
;	main.c: 303: ST7735_WriteData(((value & 0xFF00) >> 0x08));
	clr	(0x02, sp)
	ld	a, (0x05, sp)
	ld	xl, a
;	main.c: 295: PA_ODR |= (1 << DC_PIN);
	bset	20480, #3
;	main.c: 296: SPI_write(val);
	ld	a, xl
	push	a
	call	_SPI_write
	pop	a
;	main.c: 299: PA_ODR |= (1 << DC_PIN);
	bset	20480, #3
;	main.c: 304: ST7735_WriteData((value & 0x00FF));
	ld	a, (0x06, sp)
	ld	xl, a
;	main.c: 295: PA_ODR |= (1 << DC_PIN);
	bset	20480, #3
;	main.c: 296: SPI_write(val);
	ld	a, xl
	push	a
	call	_SPI_write
	pop	a
;	main.c: 299: PA_ODR |= (1 << DC_PIN);
	bset	20480, #3
;	main.c: 304: ST7735_WriteData((value & 0x00FF));
;	main.c: 305: }
	addw	sp, #2
	ret
;	main.c: 307: void ST7735_SetAddrWindow(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
;	-----------------------------------------
;	 function ST7735_SetAddrWindow
;	-----------------------------------------
_ST7735_SetAddrWindow:
	sub	sp, #2
;	main.c: 308: y += 0x18;
	ld	a, (0x06, sp)
	add	a, #0x18
	ld	(0x06, sp), a
;	main.c: 309: w += x -1;
	ld	a, (0x05, sp)
	dec	a
	ld	(0x02, sp), a
	ld	a, (0x07, sp)
	add	a, (0x02, sp)
	ld	(0x07, sp), a
;	main.c: 310: h += y -1;
	ld	a, (0x06, sp)
	dec	a
	ld	(0x01, sp), a
	ld	a, (0x08, sp)
	add	a, (0x01, sp)
	ld	(0x08, sp), a
;	main.c: 311: ST7735_Write(ST7735_CASET, CMD);
	push	#0x00
	push	#0x2a
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 312: ST7735_Write(0x00, DAT);
	push	#0x01
	push	#0x00
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 313: ST7735_Write(x, DAT);
	push	#0x01
	ld	a, (0x06, sp)
	push	a
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 314: ST7735_Write(0x00, DAT);
	push	#0x01
	push	#0x00
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 315: ST7735_Write(w, DAT);
	push	#0x01
	ld	a, (0x08, sp)
	push	a
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 316: ST7735_Write(ST7735_RASET, CMD);
	push	#0x00
	push	#0x2b
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 317: ST7735_Write(0x00, DAT);
	push	#0x01
	push	#0x00
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 318: ST7735_Write(y, DAT);
	push	#0x01
	ld	a, (0x07, sp)
	push	a
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 319: ST7735_Write(0x00, DAT);
	push	#0x01
	push	#0x00
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 320: ST7735_Write(h, DAT);
	push	#0x01
	ld	a, (0x09, sp)
	push	a
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 321: ST7735_Write(ST7735_RAMWR, CMD);
	push	#0x00
	push	#0x2c
	call	_ST7735_Write
;	main.c: 322: }
	addw	sp, #4
	ret
;	main.c: 324: void ST7735_DrawPixel(int16_t x, int16_t y, uint16_t color) {
;	-----------------------------------------
;	 function ST7735_DrawPixel
;	-----------------------------------------
_ST7735_DrawPixel:
;	main.c: 325: ST7735_SetAddrWindow(x,y,2,1);
	ld	a, (0x06, sp)
	ld	xl, a
	ld	a, (0x04, sp)
	push	#0x01
	push	#0x02
	pushw	x
	addw	sp, #1
	push	a
	call	_ST7735_SetAddrWindow
	addw	sp, #4
;	main.c: 326: ST7735_Write16(color);
	ldw	x, (0x07, sp)
	pushw	x
	call	_ST7735_Write16
	addw	sp, #2
;	main.c: 327: ST7735_Write16(color);
	ldw	x, (0x07, sp)
	pushw	x
	call	_ST7735_Write16
	addw	sp, #2
;	main.c: 328: }
	ret
;	main.c: 336: void ST7735_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
;	-----------------------------------------
;	 function ST7735_DrawLine
;	-----------------------------------------
_ST7735_DrawLine:
	sub	sp, #24
;	main.c: 337: int dx = abs(x2-x1), sx = x1<x2?1:-1;
	ldw	x, (0x1f, sp)
	subw	x, (0x1b, sp)
	tnzw	x
	jrpl	00110$
	negw	x
	ldw	(0x09, sp), x
	jra	00111$
00110$:
	ldw	(0x09, sp), x
00111$:
	ldw	y, (0x09, sp)
	ldw	(0x17, sp), y
	ldw	x, (0x1b, sp)
	cpw	x, (0x1f, sp)
	jrsge	00119$
	clrw	x
	incw	x
	jra	00120$
00119$:
	clrw	x
	decw	x
00120$:
	ldw	(0x15, sp), x
;	main.c: 338: int dy = abs(y2-y1), sy = y1<y2?1:-1;
	ldw	x, (0x21, sp)
	subw	x, (0x1d, sp)
	tnzw	x
	jrpl	00113$
	negw	x
	ldw	(0x07, sp), x
	jra	00114$
00113$:
	ldw	(0x07, sp), x
00114$:
	ldw	y, (0x07, sp)
	ldw	(0x13, sp), y
	ldw	x, (0x1d, sp)
	cpw	x, (0x21, sp)
	jrsge	00121$
	clrw	x
	incw	x
	jra	00122$
00121$:
	clrw	x
	decw	x
00122$:
	ldw	(0x11, sp), x
;	main.c: 340: int err = (dx>dy?dx:-dy)/2, e2;
	ldw	x, (0x17, sp)
	cpw	x, (0x13, sp)
	jrsle	00123$
	ldw	y, (0x17, sp)
	ldw	(0x05, sp), y
	jra	00124$
00123$:
	ldw	x, (0x13, sp)
	negw	x
	ldw	(0x05, sp), x
00124$:
	push	#0x02
	push	#0x00
	ldw	x, (0x07, sp)
	pushw	x
	call	__divsint
	addw	sp, #4
	ldw	(0x0f, sp), x
;	main.c: 341: int x=x1, y=y1;
	ldw	y, (0x1b, sp)
	ldw	(0x0d, sp), y
	ldw	y, (0x1d, sp)
	ldw	(0x0b, sp), y
	ld	a, (0x18, sp)
	neg	a
	ld	(0x04, sp), a
	clr	a
	sbc	a, (0x17, sp)
	ld	(0x03, sp), a
00115$:
;	main.c: 343: ST7735_DrawPixel(x, y, (y<6)?RGB(17,72,0):color);
	ldw	x, (0x0b, sp)
	cpw	x, #0x0006
	jrsge	00125$
	ldw	x, #0x1240
	ldw	(0x01, sp), x
	jra	00126$
00125$:
	ldw	y, (0x23, sp)
	ldw	(0x01, sp), y
00126$:
	ldw	x, (0x01, sp)
	pushw	x
	ldw	x, (0x0d, sp)
	pushw	x
	ldw	x, (0x11, sp)
	pushw	x
	call	_ST7735_DrawPixel
	addw	sp, #6
;	main.c: 344: if (x==x2 && y==y2) break;
	ldw	x, (0x0d, sp)
	cpw	x, (0x1f, sp)
	jrne	00102$
	ldw	x, (0x0b, sp)
	cpw	x, (0x21, sp)
	jreq	00117$
00102$:
;	main.c: 345: e2 = err;
	ldw	y, (0x0f, sp)
;	main.c: 346: if (e2 >-dx) { err -= dy; x += sx; }
	ldw	x, (0x0f, sp)
	cpw	x, (0x03, sp)
	jrsle	00105$
	ldw	x, (0x0f, sp)
	subw	x, (0x13, sp)
	ldw	(0x0f, sp), x
	ldw	x, (0x0d, sp)
	addw	x, (0x15, sp)
	ldw	(0x0d, sp), x
00105$:
;	main.c: 347: if (e2 < dy) { err += dx; y += sy; }
	ldw	x, y
	cpw	x, (0x13, sp)
	jrsge	00115$
	ldw	x, (0x0f, sp)
	addw	x, (0x17, sp)
	ldw	(0x0f, sp), x
	ldw	x, (0x0b, sp)
	addw	x, (0x11, sp)
	ldw	(0x0b, sp), x
	jra	00115$
00117$:
;	main.c: 349: }
	addw	sp, #24
	ret
;	main.c: 351: void ST7735_Init() {
;	-----------------------------------------
;	 function ST7735_Init
;	-----------------------------------------
_ST7735_Init:
;	main.c: 353: PA_DDR |= (1 << DC_PIN);
	bset	20482, #3
;	main.c: 354: PA_CR1 |= (1 << DC_PIN);
	bset	20483, #3
;	main.c: 355: PA_ODR |= (1 << DC_PIN);
	bset	20480, #3
;	main.c: 357: PD_DDR |= (1 << RST_PIN);
	bset	20497, #6
;	main.c: 358: PD_CR1 |= (1 << RST_PIN);
	bset	20498, #6
;	main.c: 359: PD_ODR &= ~(1 << RST_PIN);
	ld	a, 0x500f
	and	a, #0xbf
	ld	0x500f, a
;	main.c: 361: SPI_init();
	call	_SPI_init
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	clrw	y
	clrw	x
00116$:
	cpw	y, #0x2b5c
	ld	a, xl
	sbc	a, #0x00
	ld	a, xh
	sbc	a, #0x00
	jrnc	00102$
;	main.c: 33: __asm__("nop");
	nop
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	incw	y
	jrne	00116$
	incw	x
	jra	00116$
;	main.c: 362: delay_ms(100);
00102$:
;	main.c: 364: PD_ODR |= (1 << RST_PIN);
	ld	a, 0x500f
	or	a, #0x40
	ld	0x500f, a
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	clrw	y
	clrw	x
00119$:
	cpw	y, #0x2b5c
	ld	a, xl
	sbc	a, #0x00
	ld	a, xh
	sbc	a, #0x00
	jrnc	00104$
;	main.c: 33: __asm__("nop");
	nop
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	incw	y
	jrne	00119$
	incw	x
	jra	00119$
;	main.c: 365: delay_ms(100);
00104$:
;	main.c: 367: ST7735_Write(ST7735_SWRESET, CMD);
	push	#0x00
	push	#0x01
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	clrw	y
	clrw	x
00122$:
	cpw	y, #0x410a
	ld	a, xl
	sbc	a, #0x00
	ld	a, xh
	sbc	a, #0x00
	jrnc	00106$
;	main.c: 33: __asm__("nop");
	nop
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	incw	y
	jrne	00122$
	incw	x
	jra	00122$
;	main.c: 368: delay_ms(150);
00106$:
;	main.c: 369: ST7735_Write(ST7735_SLPOUT, CMD);
	push	#0x00
	push	#0x11
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	clrw	y
	clrw	x
00125$:
	cpw	y, #0xd8cc
	ld	a, xl
	sbc	a, #0x00
	ld	a, xh
	sbc	a, #0x00
	jrnc	00108$
;	main.c: 33: __asm__("nop");
	nop
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	incw	y
	jrne	00125$
	incw	x
	jra	00125$
;	main.c: 370: delay_ms(500);
00108$:
;	main.c: 371: ST7735_Write(ST7735_FRMCTR1, CMD);
	push	#0x00
	push	#0xb1
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 372: ST7735_Write(0x01, DAT);
	push	#0x01
	push	#0x01
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 373: ST7735_Write(0x2C, DAT);
	push	#0x01
	push	#0x2c
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 374: ST7735_Write(0x2D, DAT);
	push	#0x01
	push	#0x2d
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 375: ST7735_Write(ST7735_FRMCTR2, CMD);
	push	#0x00
	push	#0xb2
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 376: ST7735_Write(0x01, DAT);
	push	#0x01
	push	#0x01
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 377: ST7735_Write(0x2C, DAT);
	push	#0x01
	push	#0x2c
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 378: ST7735_Write(0x2D, DAT);
	push	#0x01
	push	#0x2d
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 379: ST7735_Write(ST7735_FRMCTR3, CMD);
	push	#0x00
	push	#0xb3
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 380: ST7735_Write(0x01, DAT);
	push	#0x01
	push	#0x01
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 381: ST7735_Write(0x2C, DAT);
	push	#0x01
	push	#0x2c
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 382: ST7735_Write(0x2D, DAT);
	push	#0x01
	push	#0x2d
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 383: ST7735_Write(0x01, DAT);
	push	#0x01
	push	#0x01
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 384: ST7735_Write(0x2C, DAT);
	push	#0x01
	push	#0x2c
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 385: ST7735_Write(0x2D, DAT);
	push	#0x01
	push	#0x2d
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 386: ST7735_Write(ST7735_INVCTR, CMD);
	push	#0x00
	push	#0xb4
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 387: ST7735_Write(0x07, DAT);
	push	#0x01
	push	#0x07
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 388: ST7735_Write(ST7735_PWCTR1, CMD);
	push	#0x00
	push	#0xc0
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 389: ST7735_Write(0xA2, DAT);
	push	#0x01
	push	#0xa2
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 390: ST7735_Write(0x02, DAT);
	push	#0x01
	push	#0x02
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 391: ST7735_Write(0x84, DAT);
	push	#0x01
	push	#0x84
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 392: ST7735_Write(ST7735_PWCTR2, CMD);
	push	#0x00
	push	#0xc1
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 393: ST7735_Write(0xC5, DAT);
	push	#0x01
	push	#0xc5
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 394: ST7735_Write(ST7735_PWCTR3, CMD);
	push	#0x00
	push	#0xc2
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 395: ST7735_Write(0x0A, DAT);
	push	#0x01
	push	#0x0a
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 396: ST7735_Write(0x00, DAT);
	push	#0x01
	push	#0x00
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 397: ST7735_Write(ST7735_PWCTR4, CMD);
	push	#0x00
	push	#0xc3
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 398: ST7735_Write(0x8A, DAT);
	push	#0x01
	push	#0x8a
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 399: ST7735_Write(0x2A, DAT);
	push	#0x01
	push	#0x2a
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 400: ST7735_Write(ST7735_PWCTR5, CMD);
	push	#0x00
	push	#0xc4
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 401: ST7735_Write(0x8A, DAT);
	push	#0x01
	push	#0x8a
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 402: ST7735_Write(0xEE, DAT);
	push	#0x01
	push	#0xee
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 403: ST7735_Write(ST7735_VMCTR1, CMD);
	push	#0x00
	push	#0xc5
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 404: ST7735_Write(0x0E, DAT);
	push	#0x01
	push	#0x0e
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 405: ST7735_Write(ST7735_INVOFF, CMD);
	push	#0x00
	push	#0x20
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 406: ST7735_Write(ST7735_MADCTL, CMD);
	push	#0x00
	push	#0x36
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 407: ST7735_Write(0xC8, DAT);
	push	#0x01
	push	#0xc8
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 408: ST7735_Write(ST7735_COLMOD, CMD);
	push	#0x00
	push	#0x3a
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 409: ST7735_Write(0x05, DAT);
	push	#0x01
	push	#0x05
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 413: ST7735_Write(ST7735_CASET, CMD);
	push	#0x00
	push	#0x2a
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 414: ST7735_Write(0x00, DAT);
	push	#0x01
	push	#0x00
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 415: ST7735_Write(0x00, DAT);
	push	#0x01
	push	#0x00
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 416: ST7735_Write(0x00, DAT);
	push	#0x01
	push	#0x00
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 417: ST7735_Write(0x4F, DAT);
	push	#0x01
	push	#0x4f
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 418: ST7735_Write(ST7735_RASET, CMD);
	push	#0x00
	push	#0x2b
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 419: ST7735_Write(0x00, DAT);
	push	#0x01
	push	#0x00
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 420: ST7735_Write(0x00, DAT);
	push	#0x01
	push	#0x00
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 421: ST7735_Write(0x00, DAT);
	push	#0x01
	push	#0x00
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 422: ST7735_Write(0x9F, DAT);
	push	#0x01
	push	#0x9f
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 426: ST7735_Write(ST7735_GMCTRP1, CMD);
	push	#0x00
	push	#0xe0
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 427: ST7735_Write(0x02, DAT);
	push	#0x01
	push	#0x02
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 428: ST7735_Write(0x1C, DAT);
	push	#0x01
	push	#0x1c
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 429: ST7735_Write(0x07, DAT);
	push	#0x01
	push	#0x07
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 430: ST7735_Write(0x12, DAT);
	push	#0x01
	push	#0x12
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 431: ST7735_Write(0x37, DAT);
	push	#0x01
	push	#0x37
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 432: ST7735_Write(0x32, DAT);
	push	#0x01
	push	#0x32
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 433: ST7735_Write(0x29, DAT);
	push	#0x01
	push	#0x29
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 434: ST7735_Write(0x2D, DAT);
	push	#0x01
	push	#0x2d
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 435: ST7735_Write(0x29, DAT);
	push	#0x01
	push	#0x29
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 436: ST7735_Write(0x25, DAT);
	push	#0x01
	push	#0x25
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 437: ST7735_Write(0x2B, DAT);
	push	#0x01
	push	#0x2b
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 438: ST7735_Write(0x39, DAT);
	push	#0x01
	push	#0x39
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 439: ST7735_Write(0x00, DAT);
	push	#0x01
	push	#0x00
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 440: ST7735_Write(0x01, DAT);
	push	#0x01
	push	#0x01
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 441: ST7735_Write(0x03, DAT);
	push	#0x01
	push	#0x03
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 442: ST7735_Write(0x10, DAT);
	push	#0x01
	push	#0x10
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 443: ST7735_Write(ST7735_GMCTRN1, CMD);
	push	#0x00
	push	#0xe1
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 444: ST7735_Write(0x03, DAT);
	push	#0x01
	push	#0x03
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 445: ST7735_Write(0x1D, DAT);
	push	#0x01
	push	#0x1d
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 446: ST7735_Write(0x07, DAT);
	push	#0x01
	push	#0x07
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 447: ST7735_Write(0x06, DAT);
	push	#0x01
	push	#0x06
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 448: ST7735_Write(0x2E, DAT);
	push	#0x01
	push	#0x2e
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 449: ST7735_Write(0x2C, DAT);
	push	#0x01
	push	#0x2c
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 450: ST7735_Write(0x29, DAT);
	push	#0x01
	push	#0x29
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 451: ST7735_Write(0x2D, DAT);
	push	#0x01
	push	#0x2d
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 452: ST7735_Write(0x2E, DAT);
	push	#0x01
	push	#0x2e
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 453: ST7735_Write(0x2E, DAT);
	push	#0x01
	push	#0x2e
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 454: ST7735_Write(0x37, DAT);
	push	#0x01
	push	#0x37
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 455: ST7735_Write(0x3F, DAT);
	push	#0x01
	push	#0x3f
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 456: ST7735_Write(0x00, DAT);
	push	#0x01
	push	#0x00
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 457: ST7735_Write(0x00, DAT);
	push	#0x01
	push	#0x00
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 458: ST7735_Write(0x02, DAT);
	push	#0x01
	push	#0x02
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 459: ST7735_Write(0x10, DAT);
	push	#0x01
	push	#0x10
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 460: ST7735_Write(ST7735_NORON, CMD);
	push	#0x00
	push	#0x13
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	clrw	y
	clrw	x
00128$:
	cpw	y, #0x0456
	ld	a, xl
	sbc	a, #0x00
	ld	a, xh
	sbc	a, #0x00
	jrnc	00110$
;	main.c: 33: __asm__("nop");
	nop
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	incw	y
	jrne	00128$
	incw	x
	jra	00128$
;	main.c: 461: delay_ms(10);
00110$:
;	main.c: 462: ST7735_Write(ST7735_DISPON, CMD);
	push	#0x00
	push	#0x29
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	clrw	y
	clrw	x
00131$:
	cpw	y, #0x2b5c
	ld	a, xl
	sbc	a, #0x00
	ld	a, xh
	sbc	a, #0x00
	jrnc	00112$
;	main.c: 33: __asm__("nop");
	nop
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	incw	y
	jrne	00131$
	incw	x
	jra	00131$
;	main.c: 463: delay_ms(100);
00112$:
;	main.c: 465: ST7735_Write(ST7735_MADCTL, CMD);
	push	#0x00
	push	#0x36
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 466: ST7735_Write(MADCTL_MX | MADCTL_MV | MADCTL_RGB, DAT);
	push	#0x01
	push	#0x68
	call	_ST7735_Write
	addw	sp, #2
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	clrw	y
	clrw	x
00134$:
	cpw	y, #0x0456
	ld	a, xl
	sbc	a, #0x00
	ld	a, xh
	sbc	a, #0x00
	jrc	00227$
	ret
00227$:
;	main.c: 33: __asm__("nop");
	nop
;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	incw	y
	jrne	00134$
	incw	x
	jra	00134$
;	main.c: 467: delay_ms(10);
;	main.c: 468: }
	ret
;	main.c: 471: void ST7735_Clear(uint16_t color) {
;	-----------------------------------------
;	 function ST7735_Clear
;	-----------------------------------------
_ST7735_Clear:
	sub	sp, #2
;	main.c: 472: ST7735_SetAddrWindow(0,0,ST7735_TFTLENGTH+3,ST7735_TFTWIDTH+3);
	push	#0x53
	push	#0xa3
	push	#0x00
	push	#0x00
	call	_ST7735_SetAddrWindow
	addw	sp, #4
;	main.c: 473: for (int i=0; i< ST7735_TFTWIDTH+3; ++i)
	clrw	x
	ldw	(0x01, sp), x
00107$:
	ldw	x, (0x01, sp)
	cpw	x, #0x0053
	jrsge	00109$
;	main.c: 474: for(int j=0; j< ST7735_TFTLENGTH+3; ++j)
	clrw	x
00104$:
	cpw	x, #0x00a3
	jrsge	00108$
;	main.c: 475: ST7735_Write16(color);
	pushw	x
	ldw	y, (0x07, sp)
	pushw	y
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 474: for(int j=0; j< ST7735_TFTLENGTH+3; ++j)
	incw	x
	jra	00104$
00108$:
;	main.c: 473: for (int i=0; i< ST7735_TFTWIDTH+3; ++i)
	ldw	x, (0x01, sp)
	incw	x
	ldw	(0x01, sp), x
	jra	00107$
00109$:
;	main.c: 476: }
	addw	sp, #2
	ret
;	main.c: 478: void ST7735_Draw(int16_t x, int16_t y, const uint8_t *data, uint8_t w, uint8_t h) {
;	-----------------------------------------
;	 function ST7735_Draw
;	-----------------------------------------
_ST7735_Draw:
	sub	sp, #18
;	main.c: 479: uint8_t xoff=0, yoff=0, wend=w, hend=h;
	clr	(0x06, sp)
	clr	(0x05, sp)
	ld	a, (0x1b, sp)
	ld	(0x04, sp), a
	ld	a, (0x1c, sp)
	ld	(0x03, sp), a
;	main.c: 481: xoff = 0 - x;
	ld	a, (0x16, sp)
	ld	xl, a
;	main.c: 480: if (x < 0)
	tnz	(0x15, sp)
	jrpl	00102$
;	main.c: 481: xoff = 0 - x;
	ld	a, xl
	neg	a
	ld	(0x06, sp), a
00102$:
;	main.c: 482: if ((x+w) > ST7735_TFTLENGTH)
	ld	a, (0x04, sp)
	clrw	y
	ld	yl, a
	addw	y, (0x15, sp)
	cpw	y, #0x00a0
	jrsle	00104$
;	main.c: 483: wend = ST7735_TFTLENGTH-x;
	ld	a, #0xa0
	pushw	x
	sub	a, (#2, sp)
	popw	x
	ld	(0x04, sp), a
00104$:
;	main.c: 485: yoff = 0 - y;
	ld	a, (0x18, sp)
	ld	xh, a
;	main.c: 484: if (y<0)
	tnz	(0x17, sp)
	jrpl	00106$
;	main.c: 485: yoff = 0 - y;
	ld	a, xh
	neg	a
	ld	(0x05, sp), a
00106$:
;	main.c: 486: if ((y+h) > ST7735_TFTWIDTH)
	ld	a, (0x03, sp)
	clrw	y
	ld	yl, a
	addw	y, (0x17, sp)
	cpw	y, #0x0050
	jrsle	00108$
;	main.c: 487: hend = ST7735_TFTWIDTH-y;
	ld	a, #0x50
	pushw	x
	sub	a, (#1, sp)
	popw	x
	ld	(0x03, sp), a
00108$:
;	main.c: 488: ST7735_SetAddrWindow(x+xoff,y+yoff,wend,hend);
	ld	a, (0x05, sp)
	ld	(0x11, sp), a
	ld	a, xh
	add	a, (0x11, sp)
	ld	xh, a
	ld	a, (0x06, sp)
	ld	(0x12, sp), a
	ld	a, xl
	add	a, (0x12, sp)
	ld	xl, a
	ld	a, (0x03, sp)
	push	a
	ld	a, (0x05, sp)
	push	a
	ld	a, xh
	push	a
	ld	a, xl
	push	a
	call	_ST7735_SetAddrWindow
	addw	sp, #4
;	main.c: 489: for (int j=yoff; j<hend/2; ++j)
	ld	a, (0x05, sp)
	ld	(0x02, sp), a
	clr	(0x01, sp)
	ldw	y, (0x01, sp)
	ldw	(0x09, sp), y
00115$:
	ld	a, (0x03, sp)
	ld	(0x08, sp), a
	clr	(0x07, sp)
	push	#0x02
	push	#0x00
	ldw	x, (0x09, sp)
	pushw	x
	call	__divsint
	addw	sp, #4
	ldw	(0x0f, sp), x
	ldw	x, (0x09, sp)
	cpw	x, (0x0f, sp)
	jrsge	00117$
;	main.c: 490: for (int i=xoff; i<wend; ++i) {
	clrw	x
	ld	a, (0x06, sp)
	ld	xl, a
	ldw	(0x0d, sp), x
00112$:
	ld	a, (0x04, sp)
	ld	(0x0c, sp), a
	clr	(0x0b, sp)
	ldw	x, (0x0d, sp)
	cpw	x, (0x0b, sp)
	jrsge	00116$
	ldw	x, (0x0d, sp)
	incw	x
	ldw	(0x0d, sp), x
	jra	00112$
00116$:
;	main.c: 489: for (int j=yoff; j<hend/2; ++j)
	ldw	x, (0x09, sp)
	incw	x
	ldw	(0x09, sp), x
	jra	00115$
00117$:
;	main.c: 496: }
	addw	sp, #18
	ret
;	main.c: 499: void ST7735_Fill(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) {
;	-----------------------------------------
;	 function ST7735_Fill
;	-----------------------------------------
_ST7735_Fill:
	sub	sp, #6
;	main.c: 500: ST7735_SetAddrWindow(x, y, w, h);
	ld	a, (0x0c, sp)
	push	a
	ld	a, (0x0c, sp)
	push	a
	ld	a, (0x0c, sp)
	push	a
	ld	a, (0x0c, sp)
	push	a
	call	_ST7735_SetAddrWindow
	addw	sp, #4
;	main.c: 501: for (int i=0; i< w; ++i)
	clrw	x
	ldw	(0x05, sp), x
00107$:
	ld	a, (0x0b, sp)
	ld	(0x04, sp), a
	clr	(0x03, sp)
	ldw	x, (0x05, sp)
	cpw	x, (0x03, sp)
	jrsge	00109$
;	main.c: 502: for(int j=0; j< h; ++j)
	clrw	x
00104$:
	ld	a, (0x0c, sp)
	ld	(0x02, sp), a
	clr	(0x01, sp)
	cpw	x, (0x01, sp)
	jrsge	00108$
;	main.c: 503: ST7735_Write16(color);
	pushw	x
	ldw	y, (0x0f, sp)
	pushw	y
	call	_ST7735_Write16
	addw	sp, #2
	popw	x
;	main.c: 502: for(int j=0; j< h; ++j)
	incw	x
	jra	00104$
00108$:
;	main.c: 501: for (int i=0; i< w; ++i)
	ldw	x, (0x05, sp)
	incw	x
	ldw	(0x05, sp), x
	jra	00107$
00109$:
;	main.c: 504: }
	addw	sp, #6
	ret
	.area CODE
	.area CONST
_pallet:
	.dw #0x3200
	.dw #0x1240
	.dw #0x5c85
	.dw #0x75ad
	.dw #0x1b11
	.dw #0x0980
	.dw #0xfcd6
_harry_raw:
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x66	; 102	'f'
	.db #0x66	; 102	'f'
	.db #0x22	; 34
	.db #0x66	; 102	'f'
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x66	; 102	'f'
	.db #0x66	; 102	'f'
	.db #0x22	; 34
	.db #0x66	; 102	'f'
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x66	; 102	'f'
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x66	; 102	'f'
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x33	; 51	'3'
	.db #0x33	; 51	'3'
	.db #0x22	; 34
	.db #0x33	; 51	'3'
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x33	; 51	'3'
	.db #0x33	; 51	'3'
	.db #0x33	; 51	'3'
	.db #0x33	; 51	'3'
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x33	; 51	'3'
	.db #0x33	; 51	'3'
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x33	; 51	'3'
	.db #0x33	; 51	'3'
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x33	; 51	'3'
	.db #0x33	; 51	'3'
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x33	; 51	'3'
	.db #0x33	; 51	'3'
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x33	; 51	'3'
	.db #0x33	; 51	'3'
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x11	; 17
	.db #0x11	; 17
	.db #0x22	; 34
	.db #0x11	; 17
	.db #0x11	; 17
	.db #0x11	; 17
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x11	; 17
	.db #0x11	; 17
	.db #0x11	; 17
	.db #0x11	; 17
	.db #0x22	; 34
	.db #0x11	; 17
	.db #0x11	; 17
	.db #0x22	; 34
	.db #0x11	; 17
	.db #0x11	; 17
	.db #0x11	; 17
	.db #0x11	; 17
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x11	; 17
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x11	; 17
	.db #0x11	; 17
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x11	; 17
	.db #0x11	; 17
_gator1_raw:
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
_gator2_raw:
	.db #0x55	; 85	'U'
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x22	; 34
	.db #0x55	; 85	'U'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x22	; 34
	.db #0x55	; 85	'U'
	.db #0x22	; 34
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x44	; 68	'D'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
	.db #0x55	; 85	'U'
_pool:
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x10	; 16
	.db #0x40	; 64
	.db #0x60	; 96
	.db #0x70	; 112	'p'
	.db #0x80	; 128
	.db #0x80	; 128
	.db #0x70	; 112	'p'
	.db #0x60	; 96
	.db #0x40	; 64
	.db #0x10	; 16
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.area INITIALIZER
	.area CABS (ABS)
