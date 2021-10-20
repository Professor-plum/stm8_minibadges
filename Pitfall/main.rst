                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.8.0 #10562 (Mac OS X x86_64)
                                      4 ;--------------------------------------------------------
                                      5 	.module main
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _pool
                                     12 	.globl _gator2_raw
                                     13 	.globl _gator1_raw
                                     14 	.globl _harry_raw
                                     15 	.globl _pallet
                                     16 	.globl _ST7735_Write
                                     17 	.globl _SPI_transfer
                                     18 	.globl _SPI_write
                                     19 	.globl _SPI_init
                                     20 	.globl _main
                                     21 	.globl _drawGator
                                     22 	.globl _clearHarry
                                     23 	.globl _drawHarry
                                     24 	.globl _drawscene
                                     25 	.globl _init_clock
                                     26 	.globl _clock
                                     27 	.globl _ST7735_Write16
                                     28 	.globl _ST7735_SetAddrWindow
                                     29 	.globl _ST7735_DrawPixel
                                     30 	.globl _ST7735_DrawLine
                                     31 	.globl _ST7735_Init
                                     32 	.globl _ST7735_Clear
                                     33 	.globl _ST7735_Draw
                                     34 	.globl _ST7735_Fill
                                     35 ;--------------------------------------------------------
                                     36 ; ram data
                                     37 ;--------------------------------------------------------
                                     38 	.area DATA
                                     39 ;--------------------------------------------------------
                                     40 ; ram data
                                     41 ;--------------------------------------------------------
                                     42 	.area INITIALIZED
                                     43 ;--------------------------------------------------------
                                     44 ; Stack segment in internal ram 
                                     45 ;--------------------------------------------------------
                                     46 	.area	SSEG
      FFFFFF                         47 __start__stack:
      FFFFFF                         48 	.ds	1
                                     49 
                                     50 ;--------------------------------------------------------
                                     51 ; absolute external ram data
                                     52 ;--------------------------------------------------------
                                     53 	.area DABS (ABS)
                                     54 
                                     55 ; default segment ordering for linker
                                     56 	.area HOME
                                     57 	.area GSINIT
                                     58 	.area GSFINAL
                                     59 	.area CONST
                                     60 	.area INITIALIZER
                                     61 	.area CODE
                                     62 
                                     63 ;--------------------------------------------------------
                                     64 ; interrupt vector 
                                     65 ;--------------------------------------------------------
                                     66 	.area HOME
      008000                         67 __interrupt_vect:
      008000 82 00 80 07             68 	int s_GSINIT ; reset
                                     69 ;--------------------------------------------------------
                                     70 ; global & static initialisations
                                     71 ;--------------------------------------------------------
                                     72 	.area HOME
                                     73 	.area GSINIT
                                     74 	.area GSFINAL
                                     75 	.area GSINIT
      008007                         76 __sdcc_gs_init_startup:
      008007                         77 __sdcc_init_data:
                                     78 ; stm8_genXINIT() start
      008007 AE 00 00         [ 2]   79 	ldw x, #l_DATA
      00800A 27 07            [ 1]   80 	jreq	00002$
      00800C                         81 00001$:
      00800C 72 4F 00 00      [ 1]   82 	clr (s_DATA - 1, x)
      008010 5A               [ 2]   83 	decw x
      008011 26 F9            [ 1]   84 	jrne	00001$
      008013                         85 00002$:
      008013 AE 00 00         [ 2]   86 	ldw	x, #l_INITIALIZER
      008016 27 09            [ 1]   87 	jreq	00004$
      008018                         88 00003$:
      008018 D6 81 39         [ 1]   89 	ld	a, (s_INITIALIZER - 1, x)
      00801B D7 00 00         [ 1]   90 	ld	(s_INITIALIZED - 1, x), a
      00801E 5A               [ 2]   91 	decw	x
      00801F 26 F7            [ 1]   92 	jrne	00003$
      008021                         93 00004$:
                                     94 ; stm8_genXINIT() end
                                     95 	.area GSFINAL
      008021 CC 80 04         [ 2]   96 	jp	__sdcc_program_startup
                                     97 ;--------------------------------------------------------
                                     98 ; Home
                                     99 ;--------------------------------------------------------
                                    100 	.area HOME
                                    101 	.area HOME
      008004                        102 __sdcc_program_startup:
      008004 CC 85 E6         [ 2]  103 	jp	_main
                                    104 ;	return from main will return to caller
                                    105 ;--------------------------------------------------------
                                    106 ; code
                                    107 ;--------------------------------------------------------
                                    108 	.area CODE
                                    109 ;	main.c: 30: static inline void delay_ms(uint16_t ms) {
                                    110 ;	-----------------------------------------
                                    111 ;	 function delay_ms
                                    112 ;	-----------------------------------------
      00813A                        113 _delay_ms:
      00813A 52 08            [ 2]  114 	sub	sp, #8
                                    115 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      00813C 5F               [ 1]  116 	clrw	x
      00813D 1F 07            [ 2]  117 	ldw	(0x07, sp), x
      00813F 1F 05            [ 2]  118 	ldw	(0x05, sp), x
      008141                        119 00103$:
      008141 1E 0B            [ 2]  120 	ldw	x, (0x0b, sp)
      008143 89               [ 2]  121 	pushw	x
      008144 4B 6F            [ 1]  122 	push	#0x6f
      008146 4B 00            [ 1]  123 	push	#0x00
      008148 CD 91 33         [ 4]  124 	call	___muluint2ulong
      00814B 5B 04            [ 2]  125 	addw	sp, #4
      00814D 1F 03            [ 2]  126 	ldw	(0x03, sp), x
      00814F 17 01            [ 2]  127 	ldw	(0x01, sp), y
      008151 1E 07            [ 2]  128 	ldw	x, (0x07, sp)
      008153 13 03            [ 2]  129 	cpw	x, (0x03, sp)
      008155 7B 06            [ 1]  130 	ld	a, (0x06, sp)
      008157 12 02            [ 1]  131 	sbc	a, (0x02, sp)
      008159 7B 05            [ 1]  132 	ld	a, (0x05, sp)
      00815B 12 01            [ 1]  133 	sbc	a, (0x01, sp)
      00815D 24 0F            [ 1]  134 	jrnc	00105$
                                    135 ;	main.c: 33: __asm__("nop");
      00815F 9D               [ 1]  136 	nop
                                    137 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008160 1E 07            [ 2]  138 	ldw	x, (0x07, sp)
      008162 5C               [ 1]  139 	incw	x
      008163 1F 07            [ 2]  140 	ldw	(0x07, sp), x
      008165 26 DA            [ 1]  141 	jrne	00103$
      008167 1E 05            [ 2]  142 	ldw	x, (0x05, sp)
      008169 5C               [ 1]  143 	incw	x
      00816A 1F 05            [ 2]  144 	ldw	(0x05, sp), x
      00816C 20 D3            [ 2]  145 	jra	00103$
      00816E                        146 00105$:
                                    147 ;	main.c: 34: }
      00816E 5B 08            [ 2]  148 	addw	sp, #8
      008170 81               [ 4]  149 	ret
                                    150 ;	main.c: 36: unsigned int clock(void)
                                    151 ;	-----------------------------------------
                                    152 ;	 function clock
                                    153 ;	-----------------------------------------
      008171                        154 _clock:
      008171 52 04            [ 2]  155 	sub	sp, #4
                                    156 ;	main.c: 38: unsigned char h = TIM1_CNTRH;
      008173 C6 52 5E         [ 1]  157 	ld	a, 0x525e
      008176 95               [ 1]  158 	ld	xh, a
                                    159 ;	main.c: 39: unsigned char l = TIM1_CNTRL;
      008177 C6 52 5F         [ 1]  160 	ld	a, 0x525f
                                    161 ;	main.c: 40: return((unsigned int)(h) << 8 | l);
      00817A 0F 04            [ 1]  162 	clr	(0x04, sp)
      00817C 0F 01            [ 1]  163 	clr	(0x01, sp)
      00817E 1A 04            [ 1]  164 	or	a, (0x04, sp)
      008180 02               [ 1]  165 	rlwa	x
      008181 1A 01            [ 1]  166 	or	a, (0x01, sp)
      008183 95               [ 1]  167 	ld	xh, a
                                    168 ;	main.c: 41: }
      008184 5B 04            [ 2]  169 	addw	sp, #4
      008186 81               [ 4]  170 	ret
                                    171 ;	main.c: 43: void init_clock(void) {
                                    172 ;	-----------------------------------------
                                    173 ;	 function init_clock
                                    174 ;	-----------------------------------------
      008187                        175 _init_clock:
                                    176 ;	main.c: 44: CLK_CKDIVR = 0;//0x18; // Set the frequency to 2 MHz
      008187 35 00 50 C6      [ 1]  177 	mov	0x50c6+0, #0x00
                                    178 ;	main.c: 45: CLK_PCKENR1 = 0x02; //SPI
      00818B 35 02 50 C7      [ 1]  179 	mov	0x50c7+0, #0x02
                                    180 ;	main.c: 46: CLK_PCKENR2 = 0x73; //off
      00818F 35 73 50 CA      [ 1]  181 	mov	0x50ca+0, #0x73
                                    182 ;	main.c: 48: }
      008193 81               [ 4]  183 	ret
                                    184 ;	main.c: 50: void drawscene(void) {
                                    185 ;	-----------------------------------------
                                    186 ;	 function drawscene
                                    187 ;	-----------------------------------------
      008194                        188 _drawscene:
      008194 52 11            [ 2]  189 	sub	sp, #17
                                    190 ;	main.c: 52: ST7735_SetAddrWindow(0, 0, 160, 80);
      008196 4B 50            [ 1]  191 	push	#0x50
      008198 4B A0            [ 1]  192 	push	#0xa0
      00819A 4B 00            [ 1]  193 	push	#0x00
      00819C 4B 00            [ 1]  194 	push	#0x00
      00819E CD 8A 9C         [ 4]  195 	call	_ST7735_SetAddrWindow
      0081A1 5B 04            [ 2]  196 	addw	sp, #4
                                    197 ;	main.c: 53: for (int i=0; i<480; ++i)
      0081A3 5F               [ 1]  198 	clrw	x
      0081A4                        199 00137$:
      0081A4 A3 01 E0         [ 2]  200 	cpw	x, #0x01e0
      0081A7 2E 0E            [ 1]  201 	jrsge	00101$
                                    202 ;	main.c: 54: ST7735_Write16(RGB(17,72,0));
      0081A9 89               [ 2]  203 	pushw	x
      0081AA 4B 40            [ 1]  204 	push	#0x40
      0081AC 4B 12            [ 1]  205 	push	#0x12
      0081AE CD 8A 73         [ 4]  206 	call	_ST7735_Write16
      0081B1 5B 02            [ 2]  207 	addw	sp, #2
      0081B3 85               [ 2]  208 	popw	x
                                    209 ;	main.c: 53: for (int i=0; i<480; ++i)
      0081B4 5C               [ 1]  210 	incw	x
      0081B5 20 ED            [ 2]  211 	jra	00137$
      0081B7                        212 00101$:
                                    213 ;	main.c: 57: for (int j=0; j<2; ++j) {
      0081B7 5F               [ 1]  214 	clrw	x
      0081B8 1F 10            [ 2]  215 	ldw	(0x10, sp), x
      0081BA                        216 00155$:
      0081BA 1E 10            [ 2]  217 	ldw	x, (0x10, sp)
      0081BC A3 00 02         [ 2]  218 	cpw	x, #0x0002
      0081BF 2E 6B            [ 1]  219 	jrsge	00107$
                                    220 ;	main.c: 58: for (int i=0; i<48; ++i)
      0081C1 5F               [ 1]  221 	clrw	x
      0081C2                        222 00140$:
      0081C2 A3 00 30         [ 2]  223 	cpw	x, #0x0030
      0081C5 2E 0E            [ 1]  224 	jrsge	00102$
                                    225 ;	main.c: 59: ST7735_Write16(RGB(17,72,0));
      0081C7 89               [ 2]  226 	pushw	x
      0081C8 4B 40            [ 1]  227 	push	#0x40
      0081CA 4B 12            [ 1]  228 	push	#0x12
      0081CC CD 8A 73         [ 4]  229 	call	_ST7735_Write16
      0081CF 5B 02            [ 2]  230 	addw	sp, #2
      0081D1 85               [ 2]  231 	popw	x
                                    232 ;	main.c: 58: for (int i=0; i<48; ++i)
      0081D2 5C               [ 1]  233 	incw	x
      0081D3 20 ED            [ 2]  234 	jra	00140$
      0081D5                        235 00102$:
                                    236 ;	main.c: 60: for (int i=0; i<16;++i)
      0081D5 5F               [ 1]  237 	clrw	x
      0081D6                        238 00143$:
      0081D6 A3 00 10         [ 2]  239 	cpw	x, #0x0010
      0081D9 2E 0E            [ 1]  240 	jrsge	00103$
                                    241 ;	main.c: 61: ST7735_Write16(RGB(95,144,47));
      0081DB 89               [ 2]  242 	pushw	x
      0081DC 4B 85            [ 1]  243 	push	#0x85
      0081DE 4B 5C            [ 1]  244 	push	#0x5c
      0081E0 CD 8A 73         [ 4]  245 	call	_ST7735_Write16
      0081E3 5B 02            [ 2]  246 	addw	sp, #2
      0081E5 85               [ 2]  247 	popw	x
                                    248 ;	main.c: 60: for (int i=0; i<16;++i)
      0081E6 5C               [ 1]  249 	incw	x
      0081E7 20 ED            [ 2]  250 	jra	00143$
      0081E9                        251 00103$:
                                    252 ;	main.c: 62: for (int i=0; i<32; ++i)
      0081E9 5F               [ 1]  253 	clrw	x
      0081EA                        254 00146$:
      0081EA A3 00 20         [ 2]  255 	cpw	x, #0x0020
      0081ED 2E 0E            [ 1]  256 	jrsge	00104$
                                    257 ;	main.c: 63: ST7735_Write16(RGB(17,72,0));
      0081EF 89               [ 2]  258 	pushw	x
      0081F0 4B 40            [ 1]  259 	push	#0x40
      0081F2 4B 12            [ 1]  260 	push	#0x12
      0081F4 CD 8A 73         [ 4]  261 	call	_ST7735_Write16
      0081F7 5B 02            [ 2]  262 	addw	sp, #2
      0081F9 85               [ 2]  263 	popw	x
                                    264 ;	main.c: 62: for (int i=0; i<32; ++i)
      0081FA 5C               [ 1]  265 	incw	x
      0081FB 20 ED            [ 2]  266 	jra	00146$
      0081FD                        267 00104$:
                                    268 ;	main.c: 64: for (int i=0; i<16;++i)
      0081FD 5F               [ 1]  269 	clrw	x
      0081FE                        270 00149$:
      0081FE A3 00 10         [ 2]  271 	cpw	x, #0x0010
      008201 2E 0E            [ 1]  272 	jrsge	00105$
                                    273 ;	main.c: 65: ST7735_Write16(RGB(95,144,47));
      008203 89               [ 2]  274 	pushw	x
      008204 4B 85            [ 1]  275 	push	#0x85
      008206 4B 5C            [ 1]  276 	push	#0x5c
      008208 CD 8A 73         [ 4]  277 	call	_ST7735_Write16
      00820B 5B 02            [ 2]  278 	addw	sp, #2
      00820D 85               [ 2]  279 	popw	x
                                    280 ;	main.c: 64: for (int i=0; i<16;++i)
      00820E 5C               [ 1]  281 	incw	x
      00820F 20 ED            [ 2]  282 	jra	00149$
      008211                        283 00105$:
                                    284 ;	main.c: 66: for (int i=0; i<48; ++i)
      008211 5F               [ 1]  285 	clrw	x
      008212                        286 00152$:
      008212 A3 00 30         [ 2]  287 	cpw	x, #0x0030
      008215 2E 0E            [ 1]  288 	jrsge	00156$
                                    289 ;	main.c: 67: ST7735_Write16(RGB(17,72,0));
      008217 89               [ 2]  290 	pushw	x
      008218 4B 40            [ 1]  291 	push	#0x40
      00821A 4B 12            [ 1]  292 	push	#0x12
      00821C CD 8A 73         [ 4]  293 	call	_ST7735_Write16
      00821F 5B 02            [ 2]  294 	addw	sp, #2
      008221 85               [ 2]  295 	popw	x
                                    296 ;	main.c: 66: for (int i=0; i<48; ++i)
      008222 5C               [ 1]  297 	incw	x
      008223 20 ED            [ 2]  298 	jra	00152$
      008225                        299 00156$:
                                    300 ;	main.c: 57: for (int j=0; j<2; ++j) {
      008225 1E 10            [ 2]  301 	ldw	x, (0x10, sp)
      008227 5C               [ 1]  302 	incw	x
      008228 1F 10            [ 2]  303 	ldw	(0x10, sp), x
      00822A 20 8E            [ 2]  304 	jra	00155$
      00822C                        305 00107$:
                                    306 ;	main.c: 69: for (int j=0; j<2; ++j) {
      00822C 5F               [ 1]  307 	clrw	x
      00822D 1F 0E            [ 2]  308 	ldw	(0x0e, sp), x
      00822F                        309 00173$:
      00822F 1E 0E            [ 2]  310 	ldw	x, (0x0e, sp)
      008231 A3 00 02         [ 2]  311 	cpw	x, #0x0002
      008234 2E 6B            [ 1]  312 	jrsge	00113$
                                    313 ;	main.c: 70: for (int i=0; i<32; ++i)
      008236 5F               [ 1]  314 	clrw	x
      008237                        315 00158$:
      008237 A3 00 20         [ 2]  316 	cpw	x, #0x0020
      00823A 2E 0E            [ 1]  317 	jrsge	00108$
                                    318 ;	main.c: 71: ST7735_Write16(RGB(17,72,0));
      00823C 89               [ 2]  319 	pushw	x
      00823D 4B 40            [ 1]  320 	push	#0x40
      00823F 4B 12            [ 1]  321 	push	#0x12
      008241 CD 8A 73         [ 4]  322 	call	_ST7735_Write16
      008244 5B 02            [ 2]  323 	addw	sp, #2
      008246 85               [ 2]  324 	popw	x
                                    325 ;	main.c: 70: for (int i=0; i<32; ++i)
      008247 5C               [ 1]  326 	incw	x
      008248 20 ED            [ 2]  327 	jra	00158$
      00824A                        328 00108$:
                                    329 ;	main.c: 72: for (int i=0; i<40;++i)
      00824A 5F               [ 1]  330 	clrw	x
      00824B                        331 00161$:
      00824B A3 00 28         [ 2]  332 	cpw	x, #0x0028
      00824E 2E 0E            [ 1]  333 	jrsge	00109$
                                    334 ;	main.c: 73: ST7735_Write16(RGB(95,144,47));
      008250 89               [ 2]  335 	pushw	x
      008251 4B 85            [ 1]  336 	push	#0x85
      008253 4B 5C            [ 1]  337 	push	#0x5c
      008255 CD 8A 73         [ 4]  338 	call	_ST7735_Write16
      008258 5B 02            [ 2]  339 	addw	sp, #2
      00825A 85               [ 2]  340 	popw	x
                                    341 ;	main.c: 72: for (int i=0; i<40;++i)
      00825B 5C               [ 1]  342 	incw	x
      00825C 20 ED            [ 2]  343 	jra	00161$
      00825E                        344 00109$:
                                    345 ;	main.c: 74: for (int i=0; i<16; ++i)
      00825E 5F               [ 1]  346 	clrw	x
      00825F                        347 00164$:
      00825F A3 00 10         [ 2]  348 	cpw	x, #0x0010
      008262 2E 0E            [ 1]  349 	jrsge	00110$
                                    350 ;	main.c: 75: ST7735_Write16(RGB(17,72,0));
      008264 89               [ 2]  351 	pushw	x
      008265 4B 40            [ 1]  352 	push	#0x40
      008267 4B 12            [ 1]  353 	push	#0x12
      008269 CD 8A 73         [ 4]  354 	call	_ST7735_Write16
      00826C 5B 02            [ 2]  355 	addw	sp, #2
      00826E 85               [ 2]  356 	popw	x
                                    357 ;	main.c: 74: for (int i=0; i<16; ++i)
      00826F 5C               [ 1]  358 	incw	x
      008270 20 ED            [ 2]  359 	jra	00164$
      008272                        360 00110$:
                                    361 ;	main.c: 76: for (int i=0; i<40;++i)
      008272 5F               [ 1]  362 	clrw	x
      008273                        363 00167$:
      008273 A3 00 28         [ 2]  364 	cpw	x, #0x0028
      008276 2E 0E            [ 1]  365 	jrsge	00111$
                                    366 ;	main.c: 77: ST7735_Write16(RGB(95,144,47));
      008278 89               [ 2]  367 	pushw	x
      008279 4B 85            [ 1]  368 	push	#0x85
      00827B 4B 5C            [ 1]  369 	push	#0x5c
      00827D CD 8A 73         [ 4]  370 	call	_ST7735_Write16
      008280 5B 02            [ 2]  371 	addw	sp, #2
      008282 85               [ 2]  372 	popw	x
                                    373 ;	main.c: 76: for (int i=0; i<40;++i)
      008283 5C               [ 1]  374 	incw	x
      008284 20 ED            [ 2]  375 	jra	00167$
      008286                        376 00111$:
                                    377 ;	main.c: 78: for (int i=0; i<32; ++i)
      008286 5F               [ 1]  378 	clrw	x
      008287                        379 00170$:
      008287 A3 00 20         [ 2]  380 	cpw	x, #0x0020
      00828A 2E 0E            [ 1]  381 	jrsge	00174$
                                    382 ;	main.c: 79: ST7735_Write16(RGB(17,72,0));
      00828C 89               [ 2]  383 	pushw	x
      00828D 4B 40            [ 1]  384 	push	#0x40
      00828F 4B 12            [ 1]  385 	push	#0x12
      008291 CD 8A 73         [ 4]  386 	call	_ST7735_Write16
      008294 5B 02            [ 2]  387 	addw	sp, #2
      008296 85               [ 2]  388 	popw	x
                                    389 ;	main.c: 78: for (int i=0; i<32; ++i)
      008297 5C               [ 1]  390 	incw	x
      008298 20 ED            [ 2]  391 	jra	00170$
      00829A                        392 00174$:
                                    393 ;	main.c: 69: for (int j=0; j<2; ++j) {
      00829A 1E 0E            [ 2]  394 	ldw	x, (0x0e, sp)
      00829C 5C               [ 1]  395 	incw	x
      00829D 1F 0E            [ 2]  396 	ldw	(0x0e, sp), x
      00829F 20 8E            [ 2]  397 	jra	00173$
      0082A1                        398 00113$:
                                    399 ;	main.c: 82: for (int j=0; j<2; ++j){
      0082A1 5F               [ 1]  400 	clrw	x
      0082A2 1F 0C            [ 2]  401 	ldw	(0x0c, sp), x
      0082A4                        402 00203$:
      0082A4 1E 0C            [ 2]  403 	ldw	x, (0x0c, sp)
      0082A6 A3 00 02         [ 2]  404 	cpw	x, #0x0002
      0082A9 2F 03            [ 1]  405 	jrslt	00657$
      0082AB CC 83 82         [ 2]  406 	jp	00123$
      0082AE                        407 00657$:
                                    408 ;	main.c: 83: for (int i=0; i<8; ++i)
      0082AE 5F               [ 1]  409 	clrw	x
      0082AF                        410 00176$:
      0082AF A3 00 08         [ 2]  411 	cpw	x, #0x0008
      0082B2 2E 0E            [ 1]  412 	jrsge	00114$
                                    413 ;	main.c: 84: ST7735_Write16(RGB(17,72,0));
      0082B4 89               [ 2]  414 	pushw	x
      0082B5 4B 40            [ 1]  415 	push	#0x40
      0082B7 4B 12            [ 1]  416 	push	#0x12
      0082B9 CD 8A 73         [ 4]  417 	call	_ST7735_Write16
      0082BC 5B 02            [ 2]  418 	addw	sp, #2
      0082BE 85               [ 2]  419 	popw	x
                                    420 ;	main.c: 83: for (int i=0; i<8; ++i)
      0082BF 5C               [ 1]  421 	incw	x
      0082C0 20 ED            [ 2]  422 	jra	00176$
      0082C2                        423 00114$:
                                    424 ;	main.c: 85: for (int i=0; i<16; ++i)
      0082C2 5F               [ 1]  425 	clrw	x
      0082C3                        426 00179$:
      0082C3 A3 00 10         [ 2]  427 	cpw	x, #0x0010
      0082C6 2E 0E            [ 1]  428 	jrsge	00115$
                                    429 ;	main.c: 86: ST7735_Write16(RGB(17,72,0));
      0082C8 89               [ 2]  430 	pushw	x
      0082C9 4B 40            [ 1]  431 	push	#0x40
      0082CB 4B 12            [ 1]  432 	push	#0x12
      0082CD CD 8A 73         [ 4]  433 	call	_ST7735_Write16
      0082D0 5B 02            [ 2]  434 	addw	sp, #2
      0082D2 85               [ 2]  435 	popw	x
                                    436 ;	main.c: 85: for (int i=0; i<16; ++i)
      0082D3 5C               [ 1]  437 	incw	x
      0082D4 20 ED            [ 2]  438 	jra	00179$
      0082D6                        439 00115$:
                                    440 ;	main.c: 87: for (int i=0; i<2;++i)
      0082D6 5F               [ 1]  441 	clrw	x
      0082D7                        442 00182$:
      0082D7 A3 00 02         [ 2]  443 	cpw	x, #0x0002
      0082DA 2E 0E            [ 1]  444 	jrsge	00116$
                                    445 ;	main.c: 88: ST7735_Write16(RGB(8,27,0));
      0082DC 89               [ 2]  446 	pushw	x
      0082DD 4B C0            [ 1]  447 	push	#0xc0
      0082DF 4B 08            [ 1]  448 	push	#0x08
      0082E1 CD 8A 73         [ 4]  449 	call	_ST7735_Write16
      0082E4 5B 02            [ 2]  450 	addw	sp, #2
      0082E6 85               [ 2]  451 	popw	x
                                    452 ;	main.c: 87: for (int i=0; i<2;++i)
      0082E7 5C               [ 1]  453 	incw	x
      0082E8 20 ED            [ 2]  454 	jra	00182$
      0082EA                        455 00116$:
                                    456 ;	main.c: 89: for (int i=0; i<2;++i)
      0082EA 5F               [ 1]  457 	clrw	x
      0082EB                        458 00185$:
      0082EB A3 00 02         [ 2]  459 	cpw	x, #0x0002
      0082EE 2E 1A            [ 1]  460 	jrsge	00117$
                                    461 ;	main.c: 90: ST7735_Write16(j?RGB(95,144,47):RGB(8,27,0));
      0082F0 16 0C            [ 2]  462 	ldw	y, (0x0c, sp)
      0082F2 27 06            [ 1]  463 	jreq	00243$
      0082F4 90 AE 5C 85      [ 2]  464 	ldw	y, #0x5c85
      0082F8 20 04            [ 2]  465 	jra	00244$
      0082FA                        466 00243$:
      0082FA 90 AE 08 C0      [ 2]  467 	ldw	y, #0x08c0
      0082FE                        468 00244$:
      0082FE 89               [ 2]  469 	pushw	x
      0082FF 90 89            [ 2]  470 	pushw	y
      008301 CD 8A 73         [ 4]  471 	call	_ST7735_Write16
      008304 5B 02            [ 2]  472 	addw	sp, #2
      008306 85               [ 2]  473 	popw	x
                                    474 ;	main.c: 89: for (int i=0; i<2;++i)
      008307 5C               [ 1]  475 	incw	x
      008308 20 E1            [ 2]  476 	jra	00185$
      00830A                        477 00117$:
                                    478 ;	main.c: 91: for (int i=0; i<104;++i)
      00830A 5F               [ 1]  479 	clrw	x
      00830B                        480 00188$:
      00830B A3 00 68         [ 2]  481 	cpw	x, #0x0068
      00830E 2E 0E            [ 1]  482 	jrsge	00118$
                                    483 ;	main.c: 92: ST7735_Write16(RGB(95,144,47));
      008310 89               [ 2]  484 	pushw	x
      008311 4B 85            [ 1]  485 	push	#0x85
      008313 4B 5C            [ 1]  486 	push	#0x5c
      008315 CD 8A 73         [ 4]  487 	call	_ST7735_Write16
      008318 5B 02            [ 2]  488 	addw	sp, #2
      00831A 85               [ 2]  489 	popw	x
                                    490 ;	main.c: 91: for (int i=0; i<104;++i)
      00831B 5C               [ 1]  491 	incw	x
      00831C 20 ED            [ 2]  492 	jra	00188$
      00831E                        493 00118$:
                                    494 ;	main.c: 93: for (int i=0; i<2;++i)
      00831E 5F               [ 1]  495 	clrw	x
      00831F                        496 00191$:
      00831F A3 00 02         [ 2]  497 	cpw	x, #0x0002
      008322 2E 1A            [ 1]  498 	jrsge	00119$
                                    499 ;	main.c: 94: ST7735_Write16(j?RGB(95,144,47):RGB(8,27,0));
      008324 16 0C            [ 2]  500 	ldw	y, (0x0c, sp)
      008326 27 06            [ 1]  501 	jreq	00245$
      008328 90 AE 5C 85      [ 2]  502 	ldw	y, #0x5c85
      00832C 20 04            [ 2]  503 	jra	00246$
      00832E                        504 00245$:
      00832E 90 AE 08 C0      [ 2]  505 	ldw	y, #0x08c0
      008332                        506 00246$:
      008332 89               [ 2]  507 	pushw	x
      008333 90 89            [ 2]  508 	pushw	y
      008335 CD 8A 73         [ 4]  509 	call	_ST7735_Write16
      008338 5B 02            [ 2]  510 	addw	sp, #2
      00833A 85               [ 2]  511 	popw	x
                                    512 ;	main.c: 93: for (int i=0; i<2;++i)
      00833B 5C               [ 1]  513 	incw	x
      00833C 20 E1            [ 2]  514 	jra	00191$
      00833E                        515 00119$:
                                    516 ;	main.c: 95: for (int i=0; i<2;++i)
      00833E 5F               [ 1]  517 	clrw	x
      00833F                        518 00194$:
      00833F A3 00 02         [ 2]  519 	cpw	x, #0x0002
      008342 2E 0E            [ 1]  520 	jrsge	00120$
                                    521 ;	main.c: 96: ST7735_Write16(RGB(8,27,0));
      008344 89               [ 2]  522 	pushw	x
      008345 4B C0            [ 1]  523 	push	#0xc0
      008347 4B 08            [ 1]  524 	push	#0x08
      008349 CD 8A 73         [ 4]  525 	call	_ST7735_Write16
      00834C 5B 02            [ 2]  526 	addw	sp, #2
      00834E 85               [ 2]  527 	popw	x
                                    528 ;	main.c: 95: for (int i=0; i<2;++i)
      00834F 5C               [ 1]  529 	incw	x
      008350 20 ED            [ 2]  530 	jra	00194$
      008352                        531 00120$:
                                    532 ;	main.c: 97: for (int i=0; i<16; ++i)
      008352 5F               [ 1]  533 	clrw	x
      008353                        534 00197$:
      008353 A3 00 10         [ 2]  535 	cpw	x, #0x0010
      008356 2E 0E            [ 1]  536 	jrsge	00121$
                                    537 ;	main.c: 98: ST7735_Write16(RGB(17,72,0));
      008358 89               [ 2]  538 	pushw	x
      008359 4B 40            [ 1]  539 	push	#0x40
      00835B 4B 12            [ 1]  540 	push	#0x12
      00835D CD 8A 73         [ 4]  541 	call	_ST7735_Write16
      008360 5B 02            [ 2]  542 	addw	sp, #2
      008362 85               [ 2]  543 	popw	x
                                    544 ;	main.c: 97: for (int i=0; i<16; ++i)
      008363 5C               [ 1]  545 	incw	x
      008364 20 ED            [ 2]  546 	jra	00197$
      008366                        547 00121$:
                                    548 ;	main.c: 99: for (int i=0; i<8; ++i)
      008366 5F               [ 1]  549 	clrw	x
      008367                        550 00200$:
      008367 A3 00 08         [ 2]  551 	cpw	x, #0x0008
      00836A 2E 0E            [ 1]  552 	jrsge	00204$
                                    553 ;	main.c: 100: ST7735_Write16(RGB(17,72,0));
      00836C 89               [ 2]  554 	pushw	x
      00836D 4B 40            [ 1]  555 	push	#0x40
      00836F 4B 12            [ 1]  556 	push	#0x12
      008371 CD 8A 73         [ 4]  557 	call	_ST7735_Write16
      008374 5B 02            [ 2]  558 	addw	sp, #2
      008376 85               [ 2]  559 	popw	x
                                    560 ;	main.c: 99: for (int i=0; i<8; ++i)
      008377 5C               [ 1]  561 	incw	x
      008378 20 ED            [ 2]  562 	jra	00200$
      00837A                        563 00204$:
                                    564 ;	main.c: 82: for (int j=0; j<2; ++j){
      00837A 1E 0C            [ 2]  565 	ldw	x, (0x0c, sp)
      00837C 5C               [ 1]  566 	incw	x
      00837D 1F 0C            [ 2]  567 	ldw	(0x0c, sp), x
      00837F CC 82 A4         [ 2]  568 	jp	00203$
      008382                        569 00123$:
                                    570 ;	main.c: 103: for (int j=0; j<52; ++j) {
      008382 5F               [ 1]  571 	clrw	x
      008383 1F 0A            [ 2]  572 	ldw	(0x0a, sp), x
      008385                        573 00221$:
      008385 1E 0A            [ 2]  574 	ldw	x, (0x0a, sp)
      008387 A3 00 34         [ 2]  575 	cpw	x, #0x0034
      00838A 2E 6B            [ 1]  576 	jrsge	00129$
                                    577 ;	main.c: 104: for (int i=0; i<16;++i)
      00838C 5F               [ 1]  578 	clrw	x
      00838D                        579 00206$:
      00838D A3 00 10         [ 2]  580 	cpw	x, #0x0010
      008390 2E 0E            [ 1]  581 	jrsge	00124$
                                    582 ;	main.c: 105: ST7735_Write16(RGB(95,144,47));
      008392 89               [ 2]  583 	pushw	x
      008393 4B 85            [ 1]  584 	push	#0x85
      008395 4B 5C            [ 1]  585 	push	#0x5c
      008397 CD 8A 73         [ 4]  586 	call	_ST7735_Write16
      00839A 5B 02            [ 2]  587 	addw	sp, #2
      00839C 85               [ 2]  588 	popw	x
                                    589 ;	main.c: 104: for (int i=0; i<16;++i)
      00839D 5C               [ 1]  590 	incw	x
      00839E 20 ED            [ 2]  591 	jra	00206$
      0083A0                        592 00124$:
                                    593 ;	main.c: 106: for (int i=0; i<8;++i)
      0083A0 5F               [ 1]  594 	clrw	x
      0083A1                        595 00209$:
      0083A1 A3 00 08         [ 2]  596 	cpw	x, #0x0008
      0083A4 2E 0E            [ 1]  597 	jrsge	00125$
                                    598 ;	main.c: 107: ST7735_Write16(RGB(8,27,0));
      0083A6 89               [ 2]  599 	pushw	x
      0083A7 4B C0            [ 1]  600 	push	#0xc0
      0083A9 4B 08            [ 1]  601 	push	#0x08
      0083AB CD 8A 73         [ 4]  602 	call	_ST7735_Write16
      0083AE 5B 02            [ 2]  603 	addw	sp, #2
      0083B0 85               [ 2]  604 	popw	x
                                    605 ;	main.c: 106: for (int i=0; i<8;++i)
      0083B1 5C               [ 1]  606 	incw	x
      0083B2 20 ED            [ 2]  607 	jra	00209$
      0083B4                        608 00125$:
                                    609 ;	main.c: 108: for (int i=0; i<112;++i)
      0083B4 5F               [ 1]  610 	clrw	x
      0083B5                        611 00212$:
      0083B5 A3 00 70         [ 2]  612 	cpw	x, #0x0070
      0083B8 2E 0E            [ 1]  613 	jrsge	00126$
                                    614 ;	main.c: 109: ST7735_Write16(RGB(95,144,47));
      0083BA 89               [ 2]  615 	pushw	x
      0083BB 4B 85            [ 1]  616 	push	#0x85
      0083BD 4B 5C            [ 1]  617 	push	#0x5c
      0083BF CD 8A 73         [ 4]  618 	call	_ST7735_Write16
      0083C2 5B 02            [ 2]  619 	addw	sp, #2
      0083C4 85               [ 2]  620 	popw	x
                                    621 ;	main.c: 108: for (int i=0; i<112;++i)
      0083C5 5C               [ 1]  622 	incw	x
      0083C6 20 ED            [ 2]  623 	jra	00212$
      0083C8                        624 00126$:
                                    625 ;	main.c: 110: for (int i=0; i<8;++i)
      0083C8 5F               [ 1]  626 	clrw	x
      0083C9                        627 00215$:
      0083C9 A3 00 08         [ 2]  628 	cpw	x, #0x0008
      0083CC 2E 0E            [ 1]  629 	jrsge	00127$
                                    630 ;	main.c: 111: ST7735_Write16(RGB(8,27,0));
      0083CE 89               [ 2]  631 	pushw	x
      0083CF 4B C0            [ 1]  632 	push	#0xc0
      0083D1 4B 08            [ 1]  633 	push	#0x08
      0083D3 CD 8A 73         [ 4]  634 	call	_ST7735_Write16
      0083D6 5B 02            [ 2]  635 	addw	sp, #2
      0083D8 85               [ 2]  636 	popw	x
                                    637 ;	main.c: 110: for (int i=0; i<8;++i)
      0083D9 5C               [ 1]  638 	incw	x
      0083DA 20 ED            [ 2]  639 	jra	00215$
      0083DC                        640 00127$:
                                    641 ;	main.c: 112: for (int i=0; i<16;++i)
      0083DC 5F               [ 1]  642 	clrw	x
      0083DD                        643 00218$:
      0083DD A3 00 10         [ 2]  644 	cpw	x, #0x0010
      0083E0 2E 0E            [ 1]  645 	jrsge	00222$
                                    646 ;	main.c: 113: ST7735_Write16(RGB(95,144,47));
      0083E2 89               [ 2]  647 	pushw	x
      0083E3 4B 85            [ 1]  648 	push	#0x85
      0083E5 4B 5C            [ 1]  649 	push	#0x5c
      0083E7 CD 8A 73         [ 4]  650 	call	_ST7735_Write16
      0083EA 5B 02            [ 2]  651 	addw	sp, #2
      0083EC 85               [ 2]  652 	popw	x
                                    653 ;	main.c: 112: for (int i=0; i<16;++i)
      0083ED 5C               [ 1]  654 	incw	x
      0083EE 20 ED            [ 2]  655 	jra	00218$
      0083F0                        656 00222$:
                                    657 ;	main.c: 103: for (int j=0; j<52; ++j) {
      0083F0 1E 0A            [ 2]  658 	ldw	x, (0x0a, sp)
      0083F2 5C               [ 1]  659 	incw	x
      0083F3 1F 0A            [ 2]  660 	ldw	(0x0a, sp), x
      0083F5 20 8E            [ 2]  661 	jra	00221$
      0083F7                        662 00129$:
                                    663 ;	main.c: 116: for (int j=0; j<16; ++j) {
      0083F7 5F               [ 1]  664 	clrw	x
      0083F8 1F 08            [ 2]  665 	ldw	(0x08, sp), x
      0083FA                        666 00233$:
      0083FA 1E 08            [ 2]  667 	ldw	x, (0x08, sp)
      0083FC A3 00 10         [ 2]  668 	cpw	x, #0x0010
      0083FF 2E 64            [ 1]  669 	jrsge	00133$
                                    670 ;	main.c: 117: uint8_t r = pool[j];
      008401 1E 08            [ 2]  671 	ldw	x, (0x08, sp)
      008403 1C 81 2A         [ 2]  672 	addw	x, #_pool
      008406 F6               [ 1]  673 	ld	a, (x)
                                    674 ;	main.c: 118: uint8_t t = 80-r/2;
      008407 6B 04            [ 1]  675 	ld	(0x04, sp), a
      008409 0F 03            [ 1]  676 	clr	(0x03, sp)
      00840B 4B 02            [ 1]  677 	push	#0x02
      00840D 4B 00            [ 1]  678 	push	#0x00
      00840F 1E 05            [ 2]  679 	ldw	x, (0x05, sp)
      008411 89               [ 2]  680 	pushw	x
      008412 CD 91 FB         [ 4]  681 	call	__divsint
      008415 5B 04            [ 2]  682 	addw	sp, #4
      008417 A6 50            [ 1]  683 	ld	a, #0x50
      008419 89               [ 2]  684 	pushw	x
      00841A 10 02            [ 1]  685 	sub	a, (#2, sp)
      00841C 85               [ 2]  686 	popw	x
      00841D 6B 07            [ 1]  687 	ld	(0x07, sp), a
                                    688 ;	main.c: 119: for (int i=0; i<t; ++i)
      00841F 5F               [ 1]  689 	clrw	x
      008420                        690 00224$:
      008420 7B 07            [ 1]  691 	ld	a, (0x07, sp)
      008422 6B 02            [ 1]  692 	ld	(0x02, sp), a
      008424 0F 01            [ 1]  693 	clr	(0x01, sp)
      008426 13 01            [ 2]  694 	cpw	x, (0x01, sp)
      008428 2E 0E            [ 1]  695 	jrsge	00130$
                                    696 ;	main.c: 120: ST7735_Write16(RGB(159,174,29));
      00842A 89               [ 2]  697 	pushw	x
      00842B 4B 63            [ 1]  698 	push	#0x63
      00842D 4B 9D            [ 1]  699 	push	#0x9d
      00842F CD 8A 73         [ 4]  700 	call	_ST7735_Write16
      008432 5B 02            [ 2]  701 	addw	sp, #2
      008434 85               [ 2]  702 	popw	x
                                    703 ;	main.c: 119: for (int i=0; i<t; ++i)
      008435 5C               [ 1]  704 	incw	x
      008436 20 E8            [ 2]  705 	jra	00224$
      008438                        706 00130$:
                                    707 ;	main.c: 121: for (int i=0; i<r; ++i)
      008438 5F               [ 1]  708 	clrw	x
      008439                        709 00227$:
      008439 13 03            [ 2]  710 	cpw	x, (0x03, sp)
      00843B 2E 0E            [ 1]  711 	jrsge	00131$
                                    712 ;	main.c: 122: ST7735_Write16(RGB(27,98,139));
      00843D 89               [ 2]  713 	pushw	x
      00843E 4B 11            [ 1]  714 	push	#0x11
      008440 4B 1B            [ 1]  715 	push	#0x1b
      008442 CD 8A 73         [ 4]  716 	call	_ST7735_Write16
      008445 5B 02            [ 2]  717 	addw	sp, #2
      008447 85               [ 2]  718 	popw	x
                                    719 ;	main.c: 121: for (int i=0; i<r; ++i)
      008448 5C               [ 1]  720 	incw	x
      008449 20 EE            [ 2]  721 	jra	00227$
      00844B                        722 00131$:
                                    723 ;	main.c: 123: for (int i=0; i<t; ++i)
      00844B 5F               [ 1]  724 	clrw	x
      00844C                        725 00230$:
      00844C 13 01            [ 2]  726 	cpw	x, (0x01, sp)
      00844E 2E 0E            [ 1]  727 	jrsge	00234$
                                    728 ;	main.c: 124: ST7735_Write16(RGB(159,174,29));
      008450 89               [ 2]  729 	pushw	x
      008451 4B 63            [ 1]  730 	push	#0x63
      008453 4B 9D            [ 1]  731 	push	#0x9d
      008455 CD 8A 73         [ 4]  732 	call	_ST7735_Write16
      008458 5B 02            [ 2]  733 	addw	sp, #2
      00845A 85               [ 2]  734 	popw	x
                                    735 ;	main.c: 123: for (int i=0; i<t; ++i)
      00845B 5C               [ 1]  736 	incw	x
      00845C 20 EE            [ 2]  737 	jra	00230$
      00845E                        738 00234$:
                                    739 ;	main.c: 116: for (int j=0; j<16; ++j) {
      00845E 1E 08            [ 2]  740 	ldw	x, (0x08, sp)
      008460 5C               [ 1]  741 	incw	x
      008461 1F 08            [ 2]  742 	ldw	(0x08, sp), x
      008463 20 95            [ 2]  743 	jra	00233$
      008465                        744 00133$:
                                    745 ;	main.c: 126: for (int j=0; j<3; ++j) 
      008465 5F               [ 1]  746 	clrw	x
      008466 1F 05            [ 2]  747 	ldw	(0x05, sp), x
      008468                        748 00239$:
      008468 1E 05            [ 2]  749 	ldw	x, (0x05, sp)
      00846A A3 00 03         [ 2]  750 	cpw	x, #0x0003
      00846D 2E 1B            [ 1]  751 	jrsge	00241$
                                    752 ;	main.c: 127: for (int i=0; i<160; ++i)
      00846F 5F               [ 1]  753 	clrw	x
      008470                        754 00236$:
      008470 A3 00 A0         [ 2]  755 	cpw	x, #0x00a0
      008473 2E 0E            [ 1]  756 	jrsge	00240$
                                    757 ;	main.c: 128: ST7735_Write16(RGB(88,104,0)); 
      008475 89               [ 2]  758 	pushw	x
      008476 4B 40            [ 1]  759 	push	#0x40
      008478 4B 5B            [ 1]  760 	push	#0x5b
      00847A CD 8A 73         [ 4]  761 	call	_ST7735_Write16
      00847D 5B 02            [ 2]  762 	addw	sp, #2
      00847F 85               [ 2]  763 	popw	x
                                    764 ;	main.c: 127: for (int i=0; i<160; ++i)
      008480 5C               [ 1]  765 	incw	x
      008481 20 ED            [ 2]  766 	jra	00236$
      008483                        767 00240$:
                                    768 ;	main.c: 126: for (int j=0; j<3; ++j) 
      008483 1E 05            [ 2]  769 	ldw	x, (0x05, sp)
      008485 5C               [ 1]  770 	incw	x
      008486 1F 05            [ 2]  771 	ldw	(0x05, sp), x
      008488 20 DE            [ 2]  772 	jra	00239$
      00848A                        773 00241$:
                                    774 ;	main.c: 129: }
      00848A 5B 11            [ 2]  775 	addw	sp, #17
      00848C 81               [ 4]  776 	ret
                                    777 ;	main.c: 131: void drawHarry(int x, int y) {
                                    778 ;	-----------------------------------------
                                    779 ;	 function drawHarry
                                    780 ;	-----------------------------------------
      00848D                        781 _drawHarry:
      00848D 52 07            [ 2]  782 	sub	sp, #7
                                    783 ;	main.c: 132: for (int j=0; j<15; ++j)
      00848F 5F               [ 1]  784 	clrw	x
      008490 1F 01            [ 2]  785 	ldw	(0x01, sp), x
      008492                        786 00109$:
      008492 1E 01            [ 2]  787 	ldw	x, (0x01, sp)
      008494 A3 00 0F         [ 2]  788 	cpw	x, #0x000f
      008497 2E 56            [ 1]  789 	jrsge	00111$
                                    790 ;	main.c: 133: for (int i=0; i<8; ++i) 
      008499 1E 0C            [ 2]  791 	ldw	x, (0x0c, sp)
      00849B 72 FB 01         [ 2]  792 	addw	x, (0x01, sp)
      00849E 1F 05            [ 2]  793 	ldw	(0x05, sp), x
      0084A0 5F               [ 1]  794 	clrw	x
      0084A1 1F 03            [ 2]  795 	ldw	(0x03, sp), x
      0084A3                        796 00106$:
      0084A3 1E 03            [ 2]  797 	ldw	x, (0x03, sp)
      0084A5 A3 00 08         [ 2]  798 	cpw	x, #0x0008
      0084A8 2E 3E            [ 1]  799 	jrsge	00110$
                                    800 ;	main.c: 135: uint8_t d = harry_raw[j*8 + i];
      0084AA 7B 02            [ 1]  801 	ld	a, (0x02, sp)
      0084AC 48               [ 1]  802 	sll	a
      0084AD 48               [ 1]  803 	sll	a
      0084AE 48               [ 1]  804 	sll	a
      0084AF 6B 07            [ 1]  805 	ld	(0x07, sp), a
      0084B1 7B 04            [ 1]  806 	ld	a, (0x04, sp)
      0084B3 1B 07            [ 1]  807 	add	a, (0x07, sp)
      0084B5 97               [ 1]  808 	ld	xl, a
      0084B6 49               [ 1]  809 	rlc	a
      0084B7 4F               [ 1]  810 	clr	a
      0084B8 A2 00            [ 1]  811 	sbc	a, #0x00
      0084BA 95               [ 1]  812 	ld	xh, a
      0084BB 1C 80 32         [ 2]  813 	addw	x, #_harry_raw
      0084BE F6               [ 1]  814 	ld	a, (x)
                                    815 ;	main.c: 136: uint8_t b1 = HIGH_NIB(d);
      0084BF 4E               [ 1]  816 	swap	a
      0084C0 A4 0F            [ 1]  817 	and	a, #0x0f
      0084C2 A4 0F            [ 1]  818 	and	a, #0x0f
                                    819 ;	main.c: 138: if (b1 != 2)
      0084C4 A1 02            [ 1]  820 	cp	a, #0x02
      0084C6 27 19            [ 1]  821 	jreq	00107$
                                    822 ;	main.c: 139: ST7735_DrawPixel(x+i*2,y+j, pallet[b1]);
      0084C8 5F               [ 1]  823 	clrw	x
      0084C9 97               [ 1]  824 	ld	xl, a
      0084CA 58               [ 2]  825 	sllw	x
      0084CB 1C 80 24         [ 2]  826 	addw	x, #_pallet
      0084CE FE               [ 2]  827 	ldw	x, (x)
      0084CF 16 03            [ 2]  828 	ldw	y, (0x03, sp)
      0084D1 90 58            [ 2]  829 	sllw	y
      0084D3 72 F9 0A         [ 2]  830 	addw	y, (0x0a, sp)
      0084D6 89               [ 2]  831 	pushw	x
      0084D7 1E 07            [ 2]  832 	ldw	x, (0x07, sp)
      0084D9 89               [ 2]  833 	pushw	x
      0084DA 90 89            [ 2]  834 	pushw	y
      0084DC CD 8B 22         [ 4]  835 	call	_ST7735_DrawPixel
      0084DF 5B 06            [ 2]  836 	addw	sp, #6
      0084E1                        837 00107$:
                                    838 ;	main.c: 133: for (int i=0; i<8; ++i) 
      0084E1 1E 03            [ 2]  839 	ldw	x, (0x03, sp)
      0084E3 5C               [ 1]  840 	incw	x
      0084E4 1F 03            [ 2]  841 	ldw	(0x03, sp), x
      0084E6 20 BB            [ 2]  842 	jra	00106$
      0084E8                        843 00110$:
                                    844 ;	main.c: 132: for (int j=0; j<15; ++j)
      0084E8 1E 01            [ 2]  845 	ldw	x, (0x01, sp)
      0084EA 5C               [ 1]  846 	incw	x
      0084EB 1F 01            [ 2]  847 	ldw	(0x01, sp), x
      0084ED 20 A3            [ 2]  848 	jra	00109$
      0084EF                        849 00111$:
                                    850 ;	main.c: 143: }
      0084EF 5B 07            [ 2]  851 	addw	sp, #7
      0084F1 81               [ 4]  852 	ret
                                    853 ;	main.c: 145: void clearHarry(int x, int y) {
                                    854 ;	-----------------------------------------
                                    855 ;	 function clearHarry
                                    856 ;	-----------------------------------------
      0084F2                        857 _clearHarry:
      0084F2 52 0A            [ 2]  858 	sub	sp, #10
                                    859 ;	main.c: 146: for (int j=0; j<15; ++j)
      0084F4 5F               [ 1]  860 	clrw	x
      0084F5 1F 09            [ 2]  861 	ldw	(0x09, sp), x
      0084F7                        862 00112$:
      0084F7 1E 09            [ 2]  863 	ldw	x, (0x09, sp)
      0084F9 A3 00 0F         [ 2]  864 	cpw	x, #0x000f
      0084FC 2E 6A            [ 1]  865 	jrsge	00114$
                                    866 ;	main.c: 147: for (int i=0; i<8; ++i) 
      0084FE 1E 0F            [ 2]  867 	ldw	x, (0x0f, sp)
      008500 72 FB 09         [ 2]  868 	addw	x, (0x09, sp)
      008503 1F 01            [ 2]  869 	ldw	(0x01, sp), x
      008505 5F               [ 1]  870 	clrw	x
      008506 1F 03            [ 2]  871 	ldw	(0x03, sp), x
      008508                        872 00109$:
      008508 1E 03            [ 2]  873 	ldw	x, (0x03, sp)
      00850A A3 00 08         [ 2]  874 	cpw	x, #0x0008
      00850D 2E 52            [ 1]  875 	jrsge	00113$
                                    876 ;	main.c: 149: uint8_t d = harry_raw[j*8 + i];
      00850F 7B 0A            [ 1]  877 	ld	a, (0x0a, sp)
      008511 48               [ 1]  878 	sll	a
      008512 48               [ 1]  879 	sll	a
      008513 48               [ 1]  880 	sll	a
      008514 97               [ 1]  881 	ld	xl, a
      008515 7B 04            [ 1]  882 	ld	a, (0x04, sp)
      008517 6B 08            [ 1]  883 	ld	(0x08, sp), a
      008519 72 FB 07         [ 2]  884 	addw	x, (7, sp)
      00851C 9F               [ 1]  885 	ld	a, xl
      00851D 49               [ 1]  886 	rlc	a
      00851E 4F               [ 1]  887 	clr	a
      00851F A2 00            [ 1]  888 	sbc	a, #0x00
      008521 95               [ 1]  889 	ld	xh, a
      008522 1C 80 32         [ 2]  890 	addw	x, #_harry_raw
      008525 F6               [ 1]  891 	ld	a, (x)
                                    892 ;	main.c: 150: uint8_t b1 = HIGH_NIB(d);
      008526 4E               [ 1]  893 	swap	a
      008527 A4 0F            [ 1]  894 	and	a, #0x0f
      008529 A4 0F            [ 1]  895 	and	a, #0x0f
                                    896 ;	main.c: 152: uint16_t c = RGB(95,144,47);
      00852B AE 5C 85         [ 2]  897 	ldw	x, #0x5c85
      00852E 1F 05            [ 2]  898 	ldw	(0x05, sp), x
                                    899 ;	main.c: 153: if (b1 != 2) {
      008530 A1 02            [ 1]  900 	cp	a, #0x02
      008532 27 26            [ 1]  901 	jreq	00110$
                                    902 ;	main.c: 154: uint8_t cx = (x+2*i);
      008534 7B 0E            [ 1]  903 	ld	a, (0x0e, sp)
      008536 6B 07            [ 1]  904 	ld	(0x07, sp), a
      008538 7B 08            [ 1]  905 	ld	a, (0x08, sp)
      00853A 48               [ 1]  906 	sll	a
      00853B 1B 07            [ 1]  907 	add	a, (0x07, sp)
                                    908 ;	main.c: 155: if ((cx<23) || (cx>135))
      00853D A1 17            [ 1]  909 	cp	a, #0x17
      00853F 25 04            [ 1]  910 	jrc	00101$
      008541 A1 87            [ 1]  911 	cp	a, #0x87
      008543 23 05            [ 2]  912 	jrule	00102$
      008545                        913 00101$:
                                    914 ;	main.c: 156: c = RGB(8,27,0);
      008545 AE 08 C0         [ 2]  915 	ldw	x, #0x08c0
      008548 1F 05            [ 2]  916 	ldw	(0x05, sp), x
      00854A                        917 00102$:
                                    918 ;	main.c: 157: ST7735_DrawPixel(cx,y+j, c);
      00854A 5F               [ 1]  919 	clrw	x
      00854B 97               [ 1]  920 	ld	xl, a
      00854C 16 05            [ 2]  921 	ldw	y, (0x05, sp)
      00854E 90 89            [ 2]  922 	pushw	y
      008550 16 03            [ 2]  923 	ldw	y, (0x03, sp)
      008552 90 89            [ 2]  924 	pushw	y
      008554 89               [ 2]  925 	pushw	x
      008555 CD 8B 22         [ 4]  926 	call	_ST7735_DrawPixel
      008558 5B 06            [ 2]  927 	addw	sp, #6
      00855A                        928 00110$:
                                    929 ;	main.c: 147: for (int i=0; i<8; ++i) 
      00855A 1E 03            [ 2]  930 	ldw	x, (0x03, sp)
      00855C 5C               [ 1]  931 	incw	x
      00855D 1F 03            [ 2]  932 	ldw	(0x03, sp), x
      00855F 20 A7            [ 2]  933 	jra	00109$
      008561                        934 00113$:
                                    935 ;	main.c: 146: for (int j=0; j<15; ++j)
      008561 1E 09            [ 2]  936 	ldw	x, (0x09, sp)
      008563 5C               [ 1]  937 	incw	x
      008564 1F 09            [ 2]  938 	ldw	(0x09, sp), x
      008566 20 8F            [ 2]  939 	jra	00112$
      008568                        940 00114$:
                                    941 ;	main.c: 166: }
      008568 5B 0A            [ 2]  942 	addw	sp, #10
      00856A 81               [ 4]  943 	ret
                                    944 ;	main.c: 168: void drawGator(int x, int y, int id) {
                                    945 ;	-----------------------------------------
                                    946 ;	 function drawGator
                                    947 ;	-----------------------------------------
      00856B                        948 _drawGator:
      00856B 52 0B            [ 2]  949 	sub	sp, #11
                                    950 ;	main.c: 169: for (int j=0; j<8; ++j)
      00856D 5F               [ 1]  951 	clrw	x
      00856E 1F 0A            [ 2]  952 	ldw	(0x0a, sp), x
      008570                        953 00109$:
      008570 1E 0A            [ 2]  954 	ldw	x, (0x0a, sp)
      008572 A3 00 08         [ 2]  955 	cpw	x, #0x0008
      008575 2E 6C            [ 1]  956 	jrsge	00111$
                                    957 ;	main.c: 170: for (int i=0; i<8; ++i) 
      008577 1E 10            [ 2]  958 	ldw	x, (0x10, sp)
      008579 72 FB 0A         [ 2]  959 	addw	x, (0x0a, sp)
      00857C 1F 08            [ 2]  960 	ldw	(0x08, sp), x
      00857E 5F               [ 1]  961 	clrw	x
      00857F 1F 01            [ 2]  962 	ldw	(0x01, sp), x
      008581                        963 00106$:
      008581 1E 01            [ 2]  964 	ldw	x, (0x01, sp)
      008583 A3 00 08         [ 2]  965 	cpw	x, #0x0008
      008586 2E 54            [ 1]  966 	jrsge	00110$
                                    967 ;	main.c: 172: uint8_t d = id?gator1_raw[j*8 + i]:gator2_raw[j*8 + i];
      008588 7B 0B            [ 1]  968 	ld	a, (0x0b, sp)
      00858A 88               [ 1]  969 	push	a
      00858B 7B 03            [ 1]  970 	ld	a, (0x03, sp)
      00858D 6B 08            [ 1]  971 	ld	(0x08, sp), a
      00858F 84               [ 1]  972 	pop	a
      008590 48               [ 1]  973 	sll	a
      008591 48               [ 1]  974 	sll	a
      008592 48               [ 1]  975 	sll	a
      008593 1B 07            [ 1]  976 	add	a, (0x07, sp)
      008595 6B 06            [ 1]  977 	ld	(0x06, sp), a
      008597 7B 06            [ 1]  978 	ld	a, (0x06, sp)
      008599 49               [ 1]  979 	rlc	a
      00859A 4F               [ 1]  980 	clr	a
      00859B A2 00            [ 1]  981 	sbc	a, #0x00
      00859D 6B 05            [ 1]  982 	ld	(0x05, sp), a
      00859F 1E 12            [ 2]  983 	ldw	x, (0x12, sp)
      0085A1 27 08            [ 1]  984 	jreq	00113$
      0085A3 1E 05            [ 2]  985 	ldw	x, (0x05, sp)
      0085A5 1C 80 AA         [ 2]  986 	addw	x, #_gator1_raw
      0085A8 F6               [ 1]  987 	ld	a, (x)
      0085A9 20 08            [ 2]  988 	jra	00114$
      0085AB                        989 00113$:
      0085AB 1E 05            [ 2]  990 	ldw	x, (0x05, sp)
      0085AD 1C 80 EA         [ 2]  991 	addw	x, #_gator2_raw
      0085B0 1F 03            [ 2]  992 	ldw	(0x03, sp), x
      0085B2 F6               [ 1]  993 	ld	a, (x)
      0085B3                        994 00114$:
                                    995 ;	main.c: 173: uint8_t b1 = HIGH_NIB(d);
      0085B3 4E               [ 1]  996 	swap	a
      0085B4 A4 0F            [ 1]  997 	and	a, #0x0f
      0085B6 A4 0F            [ 1]  998 	and	a, #0x0f
                                    999 ;	main.c: 175: if (b1 != 2)
      0085B8 A1 02            [ 1] 1000 	cp	a, #0x02
      0085BA 27 19            [ 1] 1001 	jreq	00107$
                                   1002 ;	main.c: 176: ST7735_DrawPixel(x+i*2,y+j, pallet[b1]);
      0085BC 5F               [ 1] 1003 	clrw	x
      0085BD 97               [ 1] 1004 	ld	xl, a
      0085BE 58               [ 2] 1005 	sllw	x
      0085BF 1C 80 24         [ 2] 1006 	addw	x, #_pallet
      0085C2 FE               [ 2] 1007 	ldw	x, (x)
      0085C3 16 01            [ 2] 1008 	ldw	y, (0x01, sp)
      0085C5 90 58            [ 2] 1009 	sllw	y
      0085C7 72 F9 0E         [ 2] 1010 	addw	y, (0x0e, sp)
      0085CA 89               [ 2] 1011 	pushw	x
      0085CB 1E 0A            [ 2] 1012 	ldw	x, (0x0a, sp)
      0085CD 89               [ 2] 1013 	pushw	x
      0085CE 90 89            [ 2] 1014 	pushw	y
      0085D0 CD 8B 22         [ 4] 1015 	call	_ST7735_DrawPixel
      0085D3 5B 06            [ 2] 1016 	addw	sp, #6
      0085D5                       1017 00107$:
                                   1018 ;	main.c: 170: for (int i=0; i<8; ++i) 
      0085D5 1E 01            [ 2] 1019 	ldw	x, (0x01, sp)
      0085D7 5C               [ 1] 1020 	incw	x
      0085D8 1F 01            [ 2] 1021 	ldw	(0x01, sp), x
      0085DA 20 A5            [ 2] 1022 	jra	00106$
      0085DC                       1023 00110$:
                                   1024 ;	main.c: 169: for (int j=0; j<8; ++j)
      0085DC 1E 0A            [ 2] 1025 	ldw	x, (0x0a, sp)
      0085DE 5C               [ 1] 1026 	incw	x
      0085DF 1F 0A            [ 2] 1027 	ldw	(0x0a, sp), x
      0085E1 20 8D            [ 2] 1028 	jra	00109$
      0085E3                       1029 00111$:
                                   1030 ;	main.c: 180: }
      0085E3 5B 0B            [ 2] 1031 	addw	sp, #11
      0085E5 81               [ 4] 1032 	ret
                                   1033 ;	main.c: 182: void main(void)
                                   1034 ;	-----------------------------------------
                                   1035 ;	 function main
                                   1036 ;	-----------------------------------------
      0085E6                       1037 _main:
      0085E6 52 7D            [ 2] 1038 	sub	sp, #125
                                   1039 ;	main.c: 184: const uint8_t sine[48] = {
      0085E8 96               [ 1] 1040 	ldw	x, sp
      0085E9 1C 00 31         [ 2] 1041 	addw	x, #49
      0085EC 1F 61            [ 2] 1042 	ldw	(0x61, sp), x
      0085EE A6 37            [ 1] 1043 	ld	a, #0x37
      0085F0 F7               [ 1] 1044 	ld	(x), a
      0085F1 1E 61            [ 2] 1045 	ldw	x, (0x61, sp)
      0085F3 5C               [ 1] 1046 	incw	x
      0085F4 A6 3E            [ 1] 1047 	ld	a, #0x3e
      0085F6 F7               [ 1] 1048 	ld	(x), a
      0085F7 1E 61            [ 2] 1049 	ldw	x, (0x61, sp)
      0085F9 5C               [ 1] 1050 	incw	x
      0085FA 5C               [ 1] 1051 	incw	x
      0085FB A6 45            [ 1] 1052 	ld	a, #0x45
      0085FD F7               [ 1] 1053 	ld	(x), a
      0085FE 1E 61            [ 2] 1054 	ldw	x, (0x61, sp)
      008600 A6 4B            [ 1] 1055 	ld	a, #0x4b
      008602 E7 03            [ 1] 1056 	ld	(0x0003, x), a
      008604 1E 61            [ 2] 1057 	ldw	x, (0x61, sp)
      008606 A6 52            [ 1] 1058 	ld	a, #0x52
      008608 E7 04            [ 1] 1059 	ld	(0x0004, x), a
      00860A 1E 61            [ 2] 1060 	ldw	x, (0x61, sp)
      00860C A6 58            [ 1] 1061 	ld	a, #0x58
      00860E E7 05            [ 1] 1062 	ld	(0x0005, x), a
      008610 1E 61            [ 2] 1063 	ldw	x, (0x61, sp)
      008612 A6 5D            [ 1] 1064 	ld	a, #0x5d
      008614 E7 06            [ 1] 1065 	ld	(0x0006, x), a
      008616 1E 61            [ 2] 1066 	ldw	x, (0x61, sp)
      008618 A6 62            [ 1] 1067 	ld	a, #0x62
      00861A E7 07            [ 1] 1068 	ld	(0x0007, x), a
      00861C 1E 61            [ 2] 1069 	ldw	x, (0x61, sp)
      00861E A6 66            [ 1] 1070 	ld	a, #0x66
      008620 E7 08            [ 1] 1071 	ld	(0x0008, x), a
      008622 1E 61            [ 2] 1072 	ldw	x, (0x61, sp)
      008624 A6 69            [ 1] 1073 	ld	a, #0x69
      008626 E7 09            [ 1] 1074 	ld	(0x0009, x), a
      008628 1E 61            [ 2] 1075 	ldw	x, (0x61, sp)
      00862A A6 6B            [ 1] 1076 	ld	a, #0x6b
      00862C E7 0A            [ 1] 1077 	ld	(0x000a, x), a
      00862E 1E 61            [ 2] 1078 	ldw	x, (0x61, sp)
      008630 A6 6D            [ 1] 1079 	ld	a, #0x6d
      008632 E7 0B            [ 1] 1080 	ld	(0x000b, x), a
      008634 1E 61            [ 2] 1081 	ldw	x, (0x61, sp)
      008636 A6 6D            [ 1] 1082 	ld	a, #0x6d
      008638 E7 0C            [ 1] 1083 	ld	(0x000c, x), a
      00863A 1E 61            [ 2] 1084 	ldw	x, (0x61, sp)
      00863C A6 6D            [ 1] 1085 	ld	a, #0x6d
      00863E E7 0D            [ 1] 1086 	ld	(0x000d, x), a
      008640 1E 61            [ 2] 1087 	ldw	x, (0x61, sp)
      008642 A6 6B            [ 1] 1088 	ld	a, #0x6b
      008644 E7 0E            [ 1] 1089 	ld	(0x000e, x), a
      008646 1E 61            [ 2] 1090 	ldw	x, (0x61, sp)
      008648 A6 69            [ 1] 1091 	ld	a, #0x69
      00864A E7 0F            [ 1] 1092 	ld	(0x000f, x), a
      00864C 1E 61            [ 2] 1093 	ldw	x, (0x61, sp)
      00864E A6 66            [ 1] 1094 	ld	a, #0x66
      008650 E7 10            [ 1] 1095 	ld	(0x0010, x), a
      008652 1E 61            [ 2] 1096 	ldw	x, (0x61, sp)
      008654 A6 62            [ 1] 1097 	ld	a, #0x62
      008656 E7 11            [ 1] 1098 	ld	(0x0011, x), a
      008658 1E 61            [ 2] 1099 	ldw	x, (0x61, sp)
      00865A A6 5D            [ 1] 1100 	ld	a, #0x5d
      00865C E7 12            [ 1] 1101 	ld	(0x0012, x), a
      00865E 1E 61            [ 2] 1102 	ldw	x, (0x61, sp)
      008660 A6 58            [ 1] 1103 	ld	a, #0x58
      008662 E7 13            [ 1] 1104 	ld	(0x0013, x), a
      008664 1E 61            [ 2] 1105 	ldw	x, (0x61, sp)
      008666 A6 52            [ 1] 1106 	ld	a, #0x52
      008668 E7 14            [ 1] 1107 	ld	(0x0014, x), a
      00866A 1E 61            [ 2] 1108 	ldw	x, (0x61, sp)
      00866C A6 4B            [ 1] 1109 	ld	a, #0x4b
      00866E E7 15            [ 1] 1110 	ld	(0x0015, x), a
      008670 1E 61            [ 2] 1111 	ldw	x, (0x61, sp)
      008672 A6 45            [ 1] 1112 	ld	a, #0x45
      008674 E7 16            [ 1] 1113 	ld	(0x0016, x), a
      008676 1E 61            [ 2] 1114 	ldw	x, (0x61, sp)
      008678 A6 3E            [ 1] 1115 	ld	a, #0x3e
      00867A E7 17            [ 1] 1116 	ld	(0x0017, x), a
      00867C 1E 61            [ 2] 1117 	ldw	x, (0x61, sp)
      00867E A6 37            [ 1] 1118 	ld	a, #0x37
      008680 E7 18            [ 1] 1119 	ld	(0x0018, x), a
      008682 1E 61            [ 2] 1120 	ldw	x, (0x61, sp)
      008684 A6 2F            [ 1] 1121 	ld	a, #0x2f
      008686 E7 19            [ 1] 1122 	ld	(0x0019, x), a
      008688 1E 61            [ 2] 1123 	ldw	x, (0x61, sp)
      00868A A6 28            [ 1] 1124 	ld	a, #0x28
      00868C E7 1A            [ 1] 1125 	ld	(0x001a, x), a
      00868E 1E 61            [ 2] 1126 	ldw	x, (0x61, sp)
      008690 A6 22            [ 1] 1127 	ld	a, #0x22
      008692 E7 1B            [ 1] 1128 	ld	(0x001b, x), a
      008694 1E 61            [ 2] 1129 	ldw	x, (0x61, sp)
      008696 A6 1B            [ 1] 1130 	ld	a, #0x1b
      008698 E7 1C            [ 1] 1131 	ld	(0x001c, x), a
      00869A 1E 61            [ 2] 1132 	ldw	x, (0x61, sp)
      00869C A6 15            [ 1] 1133 	ld	a, #0x15
      00869E E7 1D            [ 1] 1134 	ld	(0x001d, x), a
      0086A0 1E 61            [ 2] 1135 	ldw	x, (0x61, sp)
      0086A2 A6 10            [ 1] 1136 	ld	a, #0x10
      0086A4 E7 1E            [ 1] 1137 	ld	(0x001e, x), a
      0086A6 1E 61            [ 2] 1138 	ldw	x, (0x61, sp)
      0086A8 A6 0B            [ 1] 1139 	ld	a, #0x0b
      0086AA E7 1F            [ 1] 1140 	ld	(0x001f, x), a
      0086AC 1E 61            [ 2] 1141 	ldw	x, (0x61, sp)
      0086AE A6 07            [ 1] 1142 	ld	a, #0x07
      0086B0 E7 20            [ 1] 1143 	ld	(0x0020, x), a
      0086B2 1E 61            [ 2] 1144 	ldw	x, (0x61, sp)
      0086B4 A6 04            [ 1] 1145 	ld	a, #0x04
      0086B6 E7 21            [ 1] 1146 	ld	(0x0021, x), a
      0086B8 1E 61            [ 2] 1147 	ldw	x, (0x61, sp)
      0086BA A6 02            [ 1] 1148 	ld	a, #0x02
      0086BC E7 22            [ 1] 1149 	ld	(0x0022, x), a
      0086BE 1E 61            [ 2] 1150 	ldw	x, (0x61, sp)
      0086C0 6F 23            [ 1] 1151 	clr	(0x0023, x)
      0086C2 1E 61            [ 2] 1152 	ldw	x, (0x61, sp)
      0086C4 6F 24            [ 1] 1153 	clr	(0x0024, x)
      0086C6 1E 61            [ 2] 1154 	ldw	x, (0x61, sp)
      0086C8 6F 25            [ 1] 1155 	clr	(0x0025, x)
      0086CA 1E 61            [ 2] 1156 	ldw	x, (0x61, sp)
      0086CC A6 02            [ 1] 1157 	ld	a, #0x02
      0086CE E7 26            [ 1] 1158 	ld	(0x0026, x), a
      0086D0 1E 61            [ 2] 1159 	ldw	x, (0x61, sp)
      0086D2 A6 04            [ 1] 1160 	ld	a, #0x04
      0086D4 E7 27            [ 1] 1161 	ld	(0x0027, x), a
      0086D6 1E 61            [ 2] 1162 	ldw	x, (0x61, sp)
      0086D8 A6 07            [ 1] 1163 	ld	a, #0x07
      0086DA E7 28            [ 1] 1164 	ld	(0x0028, x), a
      0086DC 1E 61            [ 2] 1165 	ldw	x, (0x61, sp)
      0086DE A6 0B            [ 1] 1166 	ld	a, #0x0b
      0086E0 E7 29            [ 1] 1167 	ld	(0x0029, x), a
      0086E2 1E 61            [ 2] 1168 	ldw	x, (0x61, sp)
      0086E4 A6 10            [ 1] 1169 	ld	a, #0x10
      0086E6 E7 2A            [ 1] 1170 	ld	(0x002a, x), a
      0086E8 1E 61            [ 2] 1171 	ldw	x, (0x61, sp)
      0086EA A6 15            [ 1] 1172 	ld	a, #0x15
      0086EC E7 2B            [ 1] 1173 	ld	(0x002b, x), a
      0086EE 1E 61            [ 2] 1174 	ldw	x, (0x61, sp)
      0086F0 A6 1B            [ 1] 1175 	ld	a, #0x1b
      0086F2 E7 2C            [ 1] 1176 	ld	(0x002c, x), a
      0086F4 1E 61            [ 2] 1177 	ldw	x, (0x61, sp)
      0086F6 A6 22            [ 1] 1178 	ld	a, #0x22
      0086F8 E7 2D            [ 1] 1179 	ld	(0x002d, x), a
      0086FA 1E 61            [ 2] 1180 	ldw	x, (0x61, sp)
      0086FC A6 28            [ 1] 1181 	ld	a, #0x28
      0086FE E7 2E            [ 1] 1182 	ld	(0x002e, x), a
      008700 1E 61            [ 2] 1183 	ldw	x, (0x61, sp)
      008702 A6 2F            [ 1] 1184 	ld	a, #0x2f
      008704 E7 2F            [ 1] 1185 	ld	(0x002f, x), a
                                   1186 ;	main.c: 189: const uint8_t cos[48] = {
      008706 96               [ 1] 1187 	ldw	x, sp
      008707 5C               [ 1] 1188 	incw	x
      008708 1F 6F            [ 2] 1189 	ldw	(0x6f, sp), x
      00870A A6 0D            [ 1] 1190 	ld	a, #0x0d
      00870C F7               [ 1] 1191 	ld	(x), a
      00870D 1E 6F            [ 2] 1192 	ldw	x, (0x6f, sp)
      00870F 5C               [ 1] 1193 	incw	x
      008710 A6 0D            [ 1] 1194 	ld	a, #0x0d
      008712 F7               [ 1] 1195 	ld	(x), a
      008713 1E 6F            [ 2] 1196 	ldw	x, (0x6f, sp)
      008715 5C               [ 1] 1197 	incw	x
      008716 5C               [ 1] 1198 	incw	x
      008717 A6 0D            [ 1] 1199 	ld	a, #0x0d
      008719 F7               [ 1] 1200 	ld	(x), a
      00871A 1E 6F            [ 2] 1201 	ldw	x, (0x6f, sp)
      00871C A6 0C            [ 1] 1202 	ld	a, #0x0c
      00871E E7 03            [ 1] 1203 	ld	(0x0003, x), a
      008720 1E 6F            [ 2] 1204 	ldw	x, (0x6f, sp)
      008722 A6 0B            [ 1] 1205 	ld	a, #0x0b
      008724 E7 04            [ 1] 1206 	ld	(0x0004, x), a
      008726 1E 6F            [ 2] 1207 	ldw	x, (0x6f, sp)
      008728 A6 0A            [ 1] 1208 	ld	a, #0x0a
      00872A E7 05            [ 1] 1209 	ld	(0x0005, x), a
      00872C 1E 6F            [ 2] 1210 	ldw	x, (0x6f, sp)
      00872E A6 09            [ 1] 1211 	ld	a, #0x09
      008730 E7 06            [ 1] 1212 	ld	(0x0006, x), a
      008732 1E 6F            [ 2] 1213 	ldw	x, (0x6f, sp)
      008734 A6 08            [ 1] 1214 	ld	a, #0x08
      008736 E7 07            [ 1] 1215 	ld	(0x0007, x), a
      008738 1E 6F            [ 2] 1216 	ldw	x, (0x6f, sp)
      00873A A6 06            [ 1] 1217 	ld	a, #0x06
      00873C E7 08            [ 1] 1218 	ld	(0x0008, x), a
      00873E 1E 6F            [ 2] 1219 	ldw	x, (0x6f, sp)
      008740 A6 05            [ 1] 1220 	ld	a, #0x05
      008742 E7 09            [ 1] 1221 	ld	(0x0009, x), a
      008744 1E 6F            [ 2] 1222 	ldw	x, (0x6f, sp)
      008746 A6 03            [ 1] 1223 	ld	a, #0x03
      008748 E7 0A            [ 1] 1224 	ld	(0x000a, x), a
      00874A 1E 6F            [ 2] 1225 	ldw	x, (0x6f, sp)
      00874C A6 01            [ 1] 1226 	ld	a, #0x01
      00874E E7 0B            [ 1] 1227 	ld	(0x000b, x), a
      008750 1E 6F            [ 2] 1228 	ldw	x, (0x6f, sp)
      008752 6F 0C            [ 1] 1229 	clr	(0x000c, x)
      008754 1E 6F            [ 2] 1230 	ldw	x, (0x6f, sp)
      008756 A6 02            [ 1] 1231 	ld	a, #0x02
      008758 E7 0D            [ 1] 1232 	ld	(0x000d, x), a
      00875A 1E 6F            [ 2] 1233 	ldw	x, (0x6f, sp)
      00875C A6 03            [ 1] 1234 	ld	a, #0x03
      00875E E7 0E            [ 1] 1235 	ld	(0x000e, x), a
      008760 1E 6F            [ 2] 1236 	ldw	x, (0x6f, sp)
      008762 A6 05            [ 1] 1237 	ld	a, #0x05
      008764 E7 0F            [ 1] 1238 	ld	(0x000f, x), a
      008766 1E 6F            [ 2] 1239 	ldw	x, (0x6f, sp)
      008768 A6 07            [ 1] 1240 	ld	a, #0x07
      00876A E7 10            [ 1] 1241 	ld	(0x0010, x), a
      00876C 1E 6F            [ 2] 1242 	ldw	x, (0x6f, sp)
      00876E A6 08            [ 1] 1243 	ld	a, #0x08
      008770 E7 11            [ 1] 1244 	ld	(0x0011, x), a
      008772 1E 6F            [ 2] 1245 	ldw	x, (0x6f, sp)
      008774 A6 09            [ 1] 1246 	ld	a, #0x09
      008776 E7 12            [ 1] 1247 	ld	(0x0012, x), a
      008778 1E 6F            [ 2] 1248 	ldw	x, (0x6f, sp)
      00877A A6 0B            [ 1] 1249 	ld	a, #0x0b
      00877C E7 13            [ 1] 1250 	ld	(0x0013, x), a
      00877E 1E 6F            [ 2] 1251 	ldw	x, (0x6f, sp)
      008780 A6 0C            [ 1] 1252 	ld	a, #0x0c
      008782 E7 14            [ 1] 1253 	ld	(0x0014, x), a
      008784 1E 6F            [ 2] 1254 	ldw	x, (0x6f, sp)
      008786 A6 0C            [ 1] 1255 	ld	a, #0x0c
      008788 E7 15            [ 1] 1256 	ld	(0x0015, x), a
      00878A 1E 6F            [ 2] 1257 	ldw	x, (0x6f, sp)
      00878C A6 0D            [ 1] 1258 	ld	a, #0x0d
      00878E E7 16            [ 1] 1259 	ld	(0x0016, x), a
      008790 1E 6F            [ 2] 1260 	ldw	x, (0x6f, sp)
      008792 A6 0D            [ 1] 1261 	ld	a, #0x0d
      008794 E7 17            [ 1] 1262 	ld	(0x0017, x), a
      008796 1E 6F            [ 2] 1263 	ldw	x, (0x6f, sp)
      008798 A6 0D            [ 1] 1264 	ld	a, #0x0d
      00879A E7 18            [ 1] 1265 	ld	(0x0018, x), a
      00879C 1E 6F            [ 2] 1266 	ldw	x, (0x6f, sp)
      00879E A6 0D            [ 1] 1267 	ld	a, #0x0d
      0087A0 E7 19            [ 1] 1268 	ld	(0x0019, x), a
      0087A2 1E 6F            [ 2] 1269 	ldw	x, (0x6f, sp)
      0087A4 A6 0D            [ 1] 1270 	ld	a, #0x0d
      0087A6 E7 1A            [ 1] 1271 	ld	(0x001a, x), a
      0087A8 1E 6F            [ 2] 1272 	ldw	x, (0x6f, sp)
      0087AA A6 0C            [ 1] 1273 	ld	a, #0x0c
      0087AC E7 1B            [ 1] 1274 	ld	(0x001b, x), a
      0087AE 1E 6F            [ 2] 1275 	ldw	x, (0x6f, sp)
      0087B0 A6 0C            [ 1] 1276 	ld	a, #0x0c
      0087B2 E7 1C            [ 1] 1277 	ld	(0x001c, x), a
      0087B4 1E 6F            [ 2] 1278 	ldw	x, (0x6f, sp)
      0087B6 A6 0B            [ 1] 1279 	ld	a, #0x0b
      0087B8 E7 1D            [ 1] 1280 	ld	(0x001d, x), a
      0087BA 1E 6F            [ 2] 1281 	ldw	x, (0x6f, sp)
      0087BC A6 09            [ 1] 1282 	ld	a, #0x09
      0087BE E7 1E            [ 1] 1283 	ld	(0x001e, x), a
      0087C0 1E 6F            [ 2] 1284 	ldw	x, (0x6f, sp)
      0087C2 A6 08            [ 1] 1285 	ld	a, #0x08
      0087C4 E7 1F            [ 1] 1286 	ld	(0x001f, x), a
      0087C6 1E 6F            [ 2] 1287 	ldw	x, (0x6f, sp)
      0087C8 A6 07            [ 1] 1288 	ld	a, #0x07
      0087CA E7 20            [ 1] 1289 	ld	(0x0020, x), a
      0087CC 1E 6F            [ 2] 1290 	ldw	x, (0x6f, sp)
      0087CE A6 05            [ 1] 1291 	ld	a, #0x05
      0087D0 E7 21            [ 1] 1292 	ld	(0x0021, x), a
      0087D2 1E 6F            [ 2] 1293 	ldw	x, (0x6f, sp)
      0087D4 A6 03            [ 1] 1294 	ld	a, #0x03
      0087D6 E7 22            [ 1] 1295 	ld	(0x0022, x), a
      0087D8 1E 6F            [ 2] 1296 	ldw	x, (0x6f, sp)
      0087DA A6 02            [ 1] 1297 	ld	a, #0x02
      0087DC E7 23            [ 1] 1298 	ld	(0x0023, x), a
      0087DE 1E 6F            [ 2] 1299 	ldw	x, (0x6f, sp)
      0087E0 6F 24            [ 1] 1300 	clr	(0x0024, x)
      0087E2 1E 6F            [ 2] 1301 	ldw	x, (0x6f, sp)
      0087E4 A6 01            [ 1] 1302 	ld	a, #0x01
      0087E6 E7 25            [ 1] 1303 	ld	(0x0025, x), a
      0087E8 1E 6F            [ 2] 1304 	ldw	x, (0x6f, sp)
      0087EA A6 03            [ 1] 1305 	ld	a, #0x03
      0087EC E7 26            [ 1] 1306 	ld	(0x0026, x), a
      0087EE 1E 6F            [ 2] 1307 	ldw	x, (0x6f, sp)
      0087F0 A6 05            [ 1] 1308 	ld	a, #0x05
      0087F2 E7 27            [ 1] 1309 	ld	(0x0027, x), a
      0087F4 1E 6F            [ 2] 1310 	ldw	x, (0x6f, sp)
      0087F6 A6 06            [ 1] 1311 	ld	a, #0x06
      0087F8 E7 28            [ 1] 1312 	ld	(0x0028, x), a
      0087FA 1E 6F            [ 2] 1313 	ldw	x, (0x6f, sp)
      0087FC A6 08            [ 1] 1314 	ld	a, #0x08
      0087FE E7 29            [ 1] 1315 	ld	(0x0029, x), a
      008800 1E 6F            [ 2] 1316 	ldw	x, (0x6f, sp)
      008802 A6 09            [ 1] 1317 	ld	a, #0x09
      008804 E7 2A            [ 1] 1318 	ld	(0x002a, x), a
      008806 1E 6F            [ 2] 1319 	ldw	x, (0x6f, sp)
      008808 A6 0A            [ 1] 1320 	ld	a, #0x0a
      00880A E7 2B            [ 1] 1321 	ld	(0x002b, x), a
      00880C 1E 6F            [ 2] 1322 	ldw	x, (0x6f, sp)
      00880E A6 0B            [ 1] 1323 	ld	a, #0x0b
      008810 E7 2C            [ 1] 1324 	ld	(0x002c, x), a
      008812 1E 6F            [ 2] 1325 	ldw	x, (0x6f, sp)
      008814 A6 0C            [ 1] 1326 	ld	a, #0x0c
      008816 E7 2D            [ 1] 1327 	ld	(0x002d, x), a
      008818 1E 6F            [ 2] 1328 	ldw	x, (0x6f, sp)
      00881A A6 0D            [ 1] 1329 	ld	a, #0x0d
      00881C E7 2E            [ 1] 1330 	ld	(0x002e, x), a
      00881E 1E 6F            [ 2] 1331 	ldw	x, (0x6f, sp)
      008820 A6 0D            [ 1] 1332 	ld	a, #0x0d
      008822 E7 2F            [ 1] 1333 	ld	(0x002f, x), a
                                   1334 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008824 90 5F            [ 1] 1335 	clrw	y
      008826 5F               [ 1] 1336 	clrw	x
      008827 1F 71            [ 2] 1337 	ldw	(0x71, sp), x
      008829                       1338 00113$:
      008829 90 A3 14 C8      [ 2] 1339 	cpw	y, #0x14c8
      00882D 7B 72            [ 1] 1340 	ld	a, (0x72, sp)
      00882F A2 05            [ 1] 1341 	sbc	a, #0x05
      008831 7B 71            [ 1] 1342 	ld	a, (0x71, sp)
      008833 A2 00            [ 1] 1343 	sbc	a, #0x00
      008835 24 0C            [ 1] 1344 	jrnc	00109$
                                   1345 ;	main.c: 33: __asm__("nop");
      008837 9D               [ 1] 1346 	nop
                                   1347 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008838 90 5C            [ 1] 1348 	incw	y
      00883A 26 ED            [ 1] 1349 	jrne	00113$
      00883C 1E 71            [ 2] 1350 	ldw	x, (0x71, sp)
      00883E 5C               [ 1] 1351 	incw	x
      00883F 1F 71            [ 2] 1352 	ldw	(0x71, sp), x
      008841 20 E6            [ 2] 1353 	jra	00113$
                                   1354 ;	main.c: 194: delay_ms(3000);
      008843                       1355 00109$:
                                   1356 ;	main.c: 196: init_clock();
      008843 CD 81 87         [ 4] 1357 	call	_init_clock
                                   1358 ;	main.c: 197: ST7735_Init();
      008846 CD 8C 14         [ 4] 1359 	call	_ST7735_Init
                                   1360 ;	main.c: 199: __asm__ ("rim"); //enable interrupts
      008849 9A               [ 1] 1361 	rim
                                   1362 ;	main.c: 207: drawscene();
      00884A CD 81 94         [ 4] 1363 	call	_drawscene
                                   1364 ;	main.c: 210: uint8_t lx =80;
      00884D A6 50            [ 1] 1365 	ld	a, #0x50
      00884F 6B 7D            [ 1] 1366 	ld	(0x7d, sp), a
                                   1367 ;	main.c: 211: uint8_t ly =20;
      008851 A6 14            [ 1] 1368 	ld	a, #0x14
      008853 6B 7C            [ 1] 1369 	ld	(0x7c, sp), a
                                   1370 ;	main.c: 213: while(1) {
      008855 5F               [ 1] 1371 	clrw	x
      008856 1F 67            [ 2] 1372 	ldw	(0x67, sp), x
      008858 1F 65            [ 2] 1373 	ldw	(0x65, sp), x
      00885A                       1374 00106$:
                                   1375 ;	main.c: 214: uint8_t x = 24 + sine[frame%48];
      00885A 4B 30            [ 1] 1376 	push	#0x30
      00885C 5F               [ 1] 1377 	clrw	x
      00885D 89               [ 2] 1378 	pushw	x
      00885E 4B 00            [ 1] 1379 	push	#0x00
      008860 1E 6B            [ 2] 1380 	ldw	x, (0x6b, sp)
      008862 89               [ 2] 1381 	pushw	x
      008863 1E 6B            [ 2] 1382 	ldw	x, (0x6b, sp)
      008865 89               [ 2] 1383 	pushw	x
      008866 CD 91 8B         [ 4] 1384 	call	__modulong
      008869 5B 08            [ 2] 1385 	addw	sp, #8
      00886B 17 6B            [ 2] 1386 	ldw	(0x6b, sp), y
      00886D 90 93            [ 1] 1387 	ldw	y, x
      00886F 72 F9 61         [ 2] 1388 	addw	y, (0x61, sp)
      008872 90 F6            [ 1] 1389 	ld	a, (y)
      008874 AB 18            [ 1] 1390 	add	a, #0x18
      008876 6B 7B            [ 1] 1391 	ld	(0x7b, sp), a
                                   1392 ;	main.c: 215: uint8_t y = 36 + cos[frame%48];
      008878 72 FB 6F         [ 2] 1393 	addw	x, (0x6f, sp)
      00887B F6               [ 1] 1394 	ld	a, (x)
      00887C AB 24            [ 1] 1395 	add	a, #0x24
      00887E 6B 7A            [ 1] 1396 	ld	(0x7a, sp), a
                                   1397 ;	main.c: 216: ST7735_DrawLine(80, 0, lx, ly, RGB(95,144,47));
      008880 90 5F            [ 1] 1398 	clrw	y
      008882 7B 7C            [ 1] 1399 	ld	a, (0x7c, sp)
      008884 90 97            [ 1] 1400 	ld	yl, a
      008886 5F               [ 1] 1401 	clrw	x
      008887 7B 7D            [ 1] 1402 	ld	a, (0x7d, sp)
      008889 97               [ 1] 1403 	ld	xl, a
      00888A 89               [ 2] 1404 	pushw	x
      00888B 90 89            [ 2] 1405 	pushw	y
      00888D 4B 85            [ 1] 1406 	push	#0x85
      00888F 4B 5C            [ 1] 1407 	push	#0x5c
      008891 90 89            [ 2] 1408 	pushw	y
      008893 89               [ 2] 1409 	pushw	x
      008894 4B 00            [ 1] 1410 	push	#0x00
      008896 4B 00            [ 1] 1411 	push	#0x00
      008898 4B 50            [ 1] 1412 	push	#0x50
      00889A 4B 00            [ 1] 1413 	push	#0x00
      00889C CD 8B 45         [ 4] 1414 	call	_ST7735_DrawLine
      00889F 5B 0A            [ 2] 1415 	addw	sp, #10
      0088A1 90 85            [ 2] 1416 	popw	y
      0088A3 85               [ 2] 1417 	popw	x
                                   1418 ;	main.c: 217: clearHarry(lx-8,ly-2);
      0088A4 72 A2 00 02      [ 2] 1419 	subw	y, #0x0002
      0088A8 1D 00 08         [ 2] 1420 	subw	x, #0x0008
      0088AB 90 89            [ 2] 1421 	pushw	y
      0088AD 89               [ 2] 1422 	pushw	x
      0088AE CD 84 F2         [ 4] 1423 	call	_clearHarry
      0088B1 5B 04            [ 2] 1424 	addw	sp, #4
                                   1425 ;	main.c: 218: ST7735_Fill(30, 61, 100, 1, RGB(159,174,29));
      0088B3 4B 63            [ 1] 1426 	push	#0x63
      0088B5 4B 9D            [ 1] 1427 	push	#0x9d
      0088B7 4B 01            [ 1] 1428 	push	#0x01
      0088B9 4B 64            [ 1] 1429 	push	#0x64
      0088BB 4B 3D            [ 1] 1430 	push	#0x3d
      0088BD 4B 1E            [ 1] 1431 	push	#0x1e
      0088BF CD 90 EE         [ 4] 1432 	call	_ST7735_Fill
      0088C2 5B 06            [ 2] 1433 	addw	sp, #6
                                   1434 ;	main.c: 219: ST7735_Fill(23, 34, 1, 24, RGB(8,27,0));
      0088C4 4B C0            [ 1] 1435 	push	#0xc0
      0088C6 4B 08            [ 1] 1436 	push	#0x08
      0088C8 4B 18            [ 1] 1437 	push	#0x18
      0088CA 4B 01            [ 1] 1438 	push	#0x01
      0088CC 4B 22            [ 1] 1439 	push	#0x22
      0088CE 4B 17            [ 1] 1440 	push	#0x17
      0088D0 CD 90 EE         [ 4] 1441 	call	_ST7735_Fill
      0088D3 5B 06            [ 2] 1442 	addw	sp, #6
                                   1443 ;	main.c: 220: ST7735_Fill(136, 34, 1, 24, RGB(8,27,0));
      0088D5 4B C0            [ 1] 1444 	push	#0xc0
      0088D7 4B 08            [ 1] 1445 	push	#0x08
      0088D9 4B 18            [ 1] 1446 	push	#0x18
      0088DB 4B 01            [ 1] 1447 	push	#0x01
      0088DD 4B 22            [ 1] 1448 	push	#0x22
      0088DF 4B 88            [ 1] 1449 	push	#0x88
      0088E1 CD 90 EE         [ 4] 1450 	call	_ST7735_Fill
      0088E4 5B 06            [ 2] 1451 	addw	sp, #6
                                   1452 ;	main.c: 221: ST7735_DrawLine(80, 0, x, y, RGB(8,27,0));
      0088E6 90 5F            [ 1] 1453 	clrw	y
      0088E8 7B 7A            [ 1] 1454 	ld	a, (0x7a, sp)
      0088EA 90 97            [ 1] 1455 	ld	yl, a
      0088EC 5F               [ 1] 1456 	clrw	x
      0088ED 7B 7B            [ 1] 1457 	ld	a, (0x7b, sp)
      0088EF 97               [ 1] 1458 	ld	xl, a
      0088F0 89               [ 2] 1459 	pushw	x
      0088F1 90 89            [ 2] 1460 	pushw	y
      0088F3 4B C0            [ 1] 1461 	push	#0xc0
      0088F5 4B 08            [ 1] 1462 	push	#0x08
      0088F7 90 89            [ 2] 1463 	pushw	y
      0088F9 89               [ 2] 1464 	pushw	x
      0088FA 4B 00            [ 1] 1465 	push	#0x00
      0088FC 4B 00            [ 1] 1466 	push	#0x00
      0088FE 4B 50            [ 1] 1467 	push	#0x50
      008900 4B 00            [ 1] 1468 	push	#0x00
      008902 CD 8B 45         [ 4] 1469 	call	_ST7735_DrawLine
      008905 5B 0A            [ 2] 1470 	addw	sp, #10
      008907 90 85            [ 2] 1471 	popw	y
      008909 85               [ 2] 1472 	popw	x
                                   1473 ;	main.c: 222: drawHarry(x-8,y-2);
      00890A 72 A2 00 02      [ 2] 1474 	subw	y, #0x0002
      00890E 1D 00 08         [ 2] 1475 	subw	x, #0x0008
      008911 90 89            [ 2] 1476 	pushw	y
      008913 89               [ 2] 1477 	pushw	x
      008914 CD 84 8D         [ 4] 1478 	call	_drawHarry
      008917 5B 04            [ 2] 1479 	addw	sp, #4
                                   1480 ;	main.c: 224: ST7735_SetAddrWindow(0, 63, 160, 4);
      008919 4B 04            [ 1] 1481 	push	#0x04
      00891B 4B A0            [ 1] 1482 	push	#0xa0
      00891D 4B 3F            [ 1] 1483 	push	#0x3f
      00891F 4B 00            [ 1] 1484 	push	#0x00
      008921 CD 8A 9C         [ 4] 1485 	call	_ST7735_SetAddrWindow
      008924 5B 04            [ 2] 1486 	addw	sp, #4
                                   1487 ;	main.c: 225: for (int j=2; j<6; ++j) {
      008926 AE 00 02         [ 2] 1488 	ldw	x, #0x0002
      008929 1F 78            [ 2] 1489 	ldw	(0x78, sp), x
      00892B                       1490 00125$:
      00892B 1E 78            [ 2] 1491 	ldw	x, (0x78, sp)
      00892D A3 00 06         [ 2] 1492 	cpw	x, #0x0006
      008930 2E 6A            [ 1] 1493 	jrsge	00104$
                                   1494 ;	main.c: 226: uint8_t r = pool[j];
      008932 1E 78            [ 2] 1495 	ldw	x, (0x78, sp)
      008934 1C 81 2A         [ 2] 1496 	addw	x, #_pool
      008937 F6               [ 1] 1497 	ld	a, (x)
                                   1498 ;	main.c: 227: uint8_t t = 80-r/2;
      008938 6B 6A            [ 1] 1499 	ld	(0x6a, sp), a
      00893A 0F 69            [ 1] 1500 	clr	(0x69, sp)
      00893C 4B 02            [ 1] 1501 	push	#0x02
      00893E 4B 00            [ 1] 1502 	push	#0x00
      008940 1E 6B            [ 2] 1503 	ldw	x, (0x6b, sp)
      008942 89               [ 2] 1504 	pushw	x
      008943 CD 91 FB         [ 4] 1505 	call	__divsint
      008946 5B 04            [ 2] 1506 	addw	sp, #4
      008948 A6 50            [ 1] 1507 	ld	a, #0x50
      00894A 89               [ 2] 1508 	pushw	x
      00894B 10 02            [ 1] 1509 	sub	a, (#2, sp)
      00894D 85               [ 2] 1510 	popw	x
      00894E 6B 77            [ 1] 1511 	ld	(0x77, sp), a
                                   1512 ;	main.c: 228: for (int i=0; i<t; ++i)
      008950 5F               [ 1] 1513 	clrw	x
      008951                       1514 00116$:
      008951 7B 77            [ 1] 1515 	ld	a, (0x77, sp)
      008953 6B 64            [ 1] 1516 	ld	(0x64, sp), a
      008955 0F 63            [ 1] 1517 	clr	(0x63, sp)
      008957 13 63            [ 2] 1518 	cpw	x, (0x63, sp)
      008959 2E 0E            [ 1] 1519 	jrsge	00101$
                                   1520 ;	main.c: 229: ST7735_Write16(RGB(159,174,29));
      00895B 89               [ 2] 1521 	pushw	x
      00895C 4B 63            [ 1] 1522 	push	#0x63
      00895E 4B 9D            [ 1] 1523 	push	#0x9d
      008960 CD 8A 73         [ 4] 1524 	call	_ST7735_Write16
      008963 5B 02            [ 2] 1525 	addw	sp, #2
      008965 85               [ 2] 1526 	popw	x
                                   1527 ;	main.c: 228: for (int i=0; i<t; ++i)
      008966 5C               [ 1] 1528 	incw	x
      008967 20 E8            [ 2] 1529 	jra	00116$
      008969                       1530 00101$:
                                   1531 ;	main.c: 230: for (int i=0; i<r; ++i)
      008969 5F               [ 1] 1532 	clrw	x
      00896A                       1533 00119$:
      00896A 13 69            [ 2] 1534 	cpw	x, (0x69, sp)
      00896C 2E 0E            [ 1] 1535 	jrsge	00102$
                                   1536 ;	main.c: 231: ST7735_Write16(RGB(27,98,139));
      00896E 89               [ 2] 1537 	pushw	x
      00896F 4B 11            [ 1] 1538 	push	#0x11
      008971 4B 1B            [ 1] 1539 	push	#0x1b
      008973 CD 8A 73         [ 4] 1540 	call	_ST7735_Write16
      008976 5B 02            [ 2] 1541 	addw	sp, #2
      008978 85               [ 2] 1542 	popw	x
                                   1543 ;	main.c: 230: for (int i=0; i<r; ++i)
      008979 5C               [ 1] 1544 	incw	x
      00897A 20 EE            [ 2] 1545 	jra	00119$
      00897C                       1546 00102$:
                                   1547 ;	main.c: 232: for (int i=0; i<t; ++i)
      00897C 5F               [ 1] 1548 	clrw	x
      00897D 1F 75            [ 2] 1549 	ldw	(0x75, sp), x
      00897F                       1550 00122$:
      00897F 1E 75            [ 2] 1551 	ldw	x, (0x75, sp)
      008981 13 63            [ 2] 1552 	cpw	x, (0x63, sp)
      008983 2E 10            [ 1] 1553 	jrsge	00126$
                                   1554 ;	main.c: 233: ST7735_Write16(RGB(159,174,29));
      008985 4B 63            [ 1] 1555 	push	#0x63
      008987 4B 9D            [ 1] 1556 	push	#0x9d
      008989 CD 8A 73         [ 4] 1557 	call	_ST7735_Write16
      00898C 5B 02            [ 2] 1558 	addw	sp, #2
                                   1559 ;	main.c: 232: for (int i=0; i<t; ++i)
      00898E 1E 75            [ 2] 1560 	ldw	x, (0x75, sp)
      008990 5C               [ 1] 1561 	incw	x
      008991 1F 75            [ 2] 1562 	ldw	(0x75, sp), x
      008993 20 EA            [ 2] 1563 	jra	00122$
      008995                       1564 00126$:
                                   1565 ;	main.c: 225: for (int j=2; j<6; ++j) {
      008995 1E 78            [ 2] 1566 	ldw	x, (0x78, sp)
      008997 5C               [ 1] 1567 	incw	x
      008998 1F 78            [ 2] 1568 	ldw	(0x78, sp), x
      00899A 20 8F            [ 2] 1569 	jra	00125$
      00899C                       1570 00104$:
                                   1571 ;	main.c: 236: drawGator(40, 64, (frame%64)<32);
      00899C 7B 68            [ 1] 1572 	ld	a, (0x68, sp)
      00899E A4 3F            [ 1] 1573 	and	a, #0x3f
      0089A0 97               [ 1] 1574 	ld	xl, a
      0089A1 4F               [ 1] 1575 	clr	a
      0089A2 95               [ 1] 1576 	ld	xh, a
      0089A3 90 5F            [ 1] 1577 	clrw	y
      0089A5 A3 00 20         [ 2] 1578 	cpw	x, #0x0020
      0089A8 90 9F            [ 1] 1579 	ld	a, yl
      0089AA A2 00            [ 1] 1580 	sbc	a, #0x00
      0089AC 90 9E            [ 1] 1581 	ld	a, yh
      0089AE A2 00            [ 1] 1582 	sbc	a, #0x00
      0089B0 4F               [ 1] 1583 	clr	a
      0089B1 49               [ 1] 1584 	rlc	a
      0089B2 5F               [ 1] 1585 	clrw	x
      0089B3 97               [ 1] 1586 	ld	xl, a
      0089B4 89               [ 2] 1587 	pushw	x
      0089B5 89               [ 2] 1588 	pushw	x
      0089B6 4B 40            [ 1] 1589 	push	#0x40
      0089B8 4B 00            [ 1] 1590 	push	#0x00
      0089BA 4B 28            [ 1] 1591 	push	#0x28
      0089BC 4B 00            [ 1] 1592 	push	#0x00
      0089BE CD 85 6B         [ 4] 1593 	call	_drawGator
      0089C1 5B 06            [ 2] 1594 	addw	sp, #6
      0089C3 85               [ 2] 1595 	popw	x
                                   1596 ;	main.c: 237: drawGator(72, 64, (frame%64)<32);
      0089C4 89               [ 2] 1597 	pushw	x
      0089C5 89               [ 2] 1598 	pushw	x
      0089C6 4B 40            [ 1] 1599 	push	#0x40
      0089C8 4B 00            [ 1] 1600 	push	#0x00
      0089CA 4B 48            [ 1] 1601 	push	#0x48
      0089CC 4B 00            [ 1] 1602 	push	#0x00
      0089CE CD 85 6B         [ 4] 1603 	call	_drawGator
      0089D1 5B 06            [ 2] 1604 	addw	sp, #6
      0089D3 4B 40            [ 1] 1605 	push	#0x40
      0089D5 4B 00            [ 1] 1606 	push	#0x00
      0089D7 4B 68            [ 1] 1607 	push	#0x68
      0089D9 4B 00            [ 1] 1608 	push	#0x00
      0089DB CD 85 6B         [ 4] 1609 	call	_drawGator
      0089DE 5B 06            [ 2] 1610 	addw	sp, #6
                                   1611 ;	main.c: 239: frame++;
      0089E0 1E 67            [ 2] 1612 	ldw	x, (0x67, sp)
      0089E2 5C               [ 1] 1613 	incw	x
      0089E3 1F 67            [ 2] 1614 	ldw	(0x67, sp), x
      0089E5 26 05            [ 1] 1615 	jrne	00210$
      0089E7 1E 65            [ 2] 1616 	ldw	x, (0x65, sp)
      0089E9 5C               [ 1] 1617 	incw	x
      0089EA 1F 65            [ 2] 1618 	ldw	(0x65, sp), x
      0089EC                       1619 00210$:
                                   1620 ;	main.c: 240: lx = x;
      0089EC 7B 7B            [ 1] 1621 	ld	a, (0x7b, sp)
      0089EE 6B 7D            [ 1] 1622 	ld	(0x7d, sp), a
                                   1623 ;	main.c: 241: ly = y;
      0089F0 7B 7A            [ 1] 1624 	ld	a, (0x7a, sp)
      0089F2 6B 7C            [ 1] 1625 	ld	(0x7c, sp), a
                                   1626 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      0089F4 90 5F            [ 1] 1627 	clrw	y
      0089F6 5F               [ 1] 1628 	clrw	x
      0089F7                       1629 00128$:
      0089F7 90 A3 56 B8      [ 2] 1630 	cpw	y, #0x56b8
      0089FB 9F               [ 1] 1631 	ld	a, xl
      0089FC A2 00            [ 1] 1632 	sbc	a, #0x00
      0089FE 9E               [ 1] 1633 	ld	a, xh
      0089FF A2 00            [ 1] 1634 	sbc	a, #0x00
      008A01 25 03            [ 1] 1635 	jrc	00211$
      008A03 CC 88 5A         [ 2] 1636 	jp	00106$
      008A06                       1637 00211$:
                                   1638 ;	main.c: 33: __asm__("nop");
      008A06 9D               [ 1] 1639 	nop
                                   1640 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008A07 90 5C            [ 1] 1641 	incw	y
      008A09 26 EC            [ 1] 1642 	jrne	00128$
      008A0B 5C               [ 1] 1643 	incw	x
      008A0C 20 E9            [ 2] 1644 	jra	00128$
                                   1645 ;	main.c: 244: delay_ms(200);
                                   1646 ;	main.c: 248: }
      008A0E 5B 7D            [ 2] 1647 	addw	sp, #125
      008A10 81               [ 4] 1648 	ret
                                   1649 ;	main.c: 256: void SPI_init() {
                                   1650 ;	-----------------------------------------
                                   1651 ;	 function SPI_init
                                   1652 ;	-----------------------------------------
      008A11                       1653 _SPI_init:
                                   1654 ;	main.c: 258: PC_DDR |= (1<<5) | (1<<6); // clock and MOSI
      008A11 C6 50 0C         [ 1] 1655 	ld	a, 0x500c
      008A14 AA 60            [ 1] 1656 	or	a, #0x60
      008A16 C7 50 0C         [ 1] 1657 	ld	0x500c, a
                                   1658 ;	main.c: 259: PC_CR1 |= (1<<5) | (1<<6) | (1<<7);
      008A19 C6 50 0D         [ 1] 1659 	ld	a, 0x500d
      008A1C AA E0            [ 1] 1660 	or	a, #0xe0
      008A1E C7 50 0D         [ 1] 1661 	ld	0x500d, a
                                   1662 ;	main.c: 263: SPI_CR2 = SPI_CR2_SSM | SPI_CR2_SSI;
      008A21 35 03 52 01      [ 1] 1663 	mov	0x5201+0, #0x03
                                   1664 ;	main.c: 264: SPI_CR1 = SPI_CR1_MSTR;// | SPI_CR1_BR(3);
      008A25 35 04 52 00      [ 1] 1665 	mov	0x5200+0, #0x04
                                   1666 ;	main.c: 265: SPI_CR1 |= SPI_CR1_SPE;
      008A29 72 1C 52 00      [ 1] 1667 	bset	20992, #6
                                   1668 ;	main.c: 266: }
      008A2D 81               [ 4] 1669 	ret
                                   1670 ;	main.c: 268: void SPI_write(uint8_t data) {
                                   1671 ;	-----------------------------------------
                                   1672 ;	 function SPI_write
                                   1673 ;	-----------------------------------------
      008A2E                       1674 _SPI_write:
                                   1675 ;	main.c: 269: SPI_DR = data;
      008A2E AE 52 04         [ 2] 1676 	ldw	x, #0x5204
      008A31 7B 03            [ 1] 1677 	ld	a, (0x03, sp)
      008A33 F7               [ 1] 1678 	ld	(x), a
                                   1679 ;	main.c: 270: while (!(SPI_SR & SPI_SR_TXE));
      008A34                       1680 00101$:
      008A34 C6 52 03         [ 1] 1681 	ld	a, 0x5203
      008A37 A5 02            [ 1] 1682 	bcp	a, #0x02
      008A39 27 F9            [ 1] 1683 	jreq	00101$
                                   1684 ;	main.c: 271: }
      008A3B 81               [ 4] 1685 	ret
                                   1686 ;	main.c: 273: void SPI_transfer(uint8_t *data, size_t len) {
                                   1687 ;	-----------------------------------------
                                   1688 ;	 function SPI_transfer
                                   1689 ;	-----------------------------------------
      008A3C                       1690 _SPI_transfer:
                                   1691 ;	main.c: 274: for (size_t i=0; i< len; ++i) {
      008A3C 5F               [ 1] 1692 	clrw	x
      008A3D                       1693 00103$:
      008A3D 13 05            [ 2] 1694 	cpw	x, (0x05, sp)
      008A3F 25 01            [ 1] 1695 	jrc	00118$
      008A41 81               [ 4] 1696 	ret
      008A42                       1697 00118$:
                                   1698 ;	main.c: 275: SPI_write(data[i]);
      008A42 90 93            [ 1] 1699 	ldw	y, x
      008A44 72 F9 03         [ 2] 1700 	addw	y, (0x03, sp)
      008A47 90 F6            [ 1] 1701 	ld	a, (y)
      008A49 89               [ 2] 1702 	pushw	x
      008A4A 88               [ 1] 1703 	push	a
      008A4B CD 8A 2E         [ 4] 1704 	call	_SPI_write
      008A4E 84               [ 1] 1705 	pop	a
      008A4F 85               [ 2] 1706 	popw	x
                                   1707 ;	main.c: 274: for (size_t i=0; i< len; ++i) {
      008A50 5C               [ 1] 1708 	incw	x
      008A51 20 EA            [ 2] 1709 	jra	00103$
                                   1710 ;	main.c: 277: }
      008A53 81               [ 4] 1711 	ret
                                   1712 ;	main.c: 283: void ST7735_Write(uint8_t val, uint8_t cmd) {
                                   1713 ;	-----------------------------------------
                                   1714 ;	 function ST7735_Write
                                   1715 ;	-----------------------------------------
      008A54                       1716 _ST7735_Write:
                                   1717 ;	main.c: 285: PA_ODR &= ~(1 << DC_PIN);
      008A54 C6 50 00         [ 1] 1718 	ld	a, 0x5000
                                   1719 ;	main.c: 284: if (cmd==CMD)
      008A57 0D 04            [ 1] 1720 	tnz	(0x04, sp)
      008A59 26 07            [ 1] 1721 	jrne	00102$
                                   1722 ;	main.c: 285: PA_ODR &= ~(1 << DC_PIN);
      008A5B A4 F7            [ 1] 1723 	and	a, #0xf7
      008A5D C7 50 00         [ 1] 1724 	ld	0x5000, a
      008A60 20 05            [ 2] 1725 	jra	00103$
      008A62                       1726 00102$:
                                   1727 ;	main.c: 287: PA_ODR |= (1 << DC_PIN);
      008A62 AA 08            [ 1] 1728 	or	a, #0x08
      008A64 C7 50 00         [ 1] 1729 	ld	0x5000, a
      008A67                       1730 00103$:
                                   1731 ;	main.c: 288: SPI_write(val);
      008A67 7B 03            [ 1] 1732 	ld	a, (0x03, sp)
      008A69 88               [ 1] 1733 	push	a
      008A6A CD 8A 2E         [ 4] 1734 	call	_SPI_write
      008A6D 84               [ 1] 1735 	pop	a
                                   1736 ;	main.c: 291: PA_ODR |= (1 << DC_PIN);
      008A6E 72 16 50 00      [ 1] 1737 	bset	20480, #3
                                   1738 ;	main.c: 292: }
      008A72 81               [ 4] 1739 	ret
                                   1740 ;	main.c: 302: void ST7735_Write16(uint16_t value) {
                                   1741 ;	-----------------------------------------
                                   1742 ;	 function ST7735_Write16
                                   1743 ;	-----------------------------------------
      008A73                       1744 _ST7735_Write16:
      008A73 52 02            [ 2] 1745 	sub	sp, #2
                                   1746 ;	main.c: 303: ST7735_WriteData(((value & 0xFF00) >> 0x08));
      008A75 0F 02            [ 1] 1747 	clr	(0x02, sp)
      008A77 7B 05            [ 1] 1748 	ld	a, (0x05, sp)
      008A79 97               [ 1] 1749 	ld	xl, a
                                   1750 ;	main.c: 295: PA_ODR |= (1 << DC_PIN);
      008A7A 72 16 50 00      [ 1] 1751 	bset	20480, #3
                                   1752 ;	main.c: 296: SPI_write(val);
      008A7E 9F               [ 1] 1753 	ld	a, xl
      008A7F 88               [ 1] 1754 	push	a
      008A80 CD 8A 2E         [ 4] 1755 	call	_SPI_write
      008A83 84               [ 1] 1756 	pop	a
                                   1757 ;	main.c: 299: PA_ODR |= (1 << DC_PIN);
      008A84 72 16 50 00      [ 1] 1758 	bset	20480, #3
                                   1759 ;	main.c: 304: ST7735_WriteData((value & 0x00FF));
      008A88 7B 06            [ 1] 1760 	ld	a, (0x06, sp)
      008A8A 97               [ 1] 1761 	ld	xl, a
                                   1762 ;	main.c: 295: PA_ODR |= (1 << DC_PIN);
      008A8B 72 16 50 00      [ 1] 1763 	bset	20480, #3
                                   1764 ;	main.c: 296: SPI_write(val);
      008A8F 9F               [ 1] 1765 	ld	a, xl
      008A90 88               [ 1] 1766 	push	a
      008A91 CD 8A 2E         [ 4] 1767 	call	_SPI_write
      008A94 84               [ 1] 1768 	pop	a
                                   1769 ;	main.c: 299: PA_ODR |= (1 << DC_PIN);
      008A95 72 16 50 00      [ 1] 1770 	bset	20480, #3
                                   1771 ;	main.c: 304: ST7735_WriteData((value & 0x00FF));
                                   1772 ;	main.c: 305: }
      008A99 5B 02            [ 2] 1773 	addw	sp, #2
      008A9B 81               [ 4] 1774 	ret
                                   1775 ;	main.c: 307: void ST7735_SetAddrWindow(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
                                   1776 ;	-----------------------------------------
                                   1777 ;	 function ST7735_SetAddrWindow
                                   1778 ;	-----------------------------------------
      008A9C                       1779 _ST7735_SetAddrWindow:
      008A9C 52 02            [ 2] 1780 	sub	sp, #2
                                   1781 ;	main.c: 308: y += 0x18;
      008A9E 7B 06            [ 1] 1782 	ld	a, (0x06, sp)
      008AA0 AB 18            [ 1] 1783 	add	a, #0x18
      008AA2 6B 06            [ 1] 1784 	ld	(0x06, sp), a
                                   1785 ;	main.c: 309: w += x -1;
      008AA4 7B 05            [ 1] 1786 	ld	a, (0x05, sp)
      008AA6 4A               [ 1] 1787 	dec	a
      008AA7 6B 02            [ 1] 1788 	ld	(0x02, sp), a
      008AA9 7B 07            [ 1] 1789 	ld	a, (0x07, sp)
      008AAB 1B 02            [ 1] 1790 	add	a, (0x02, sp)
      008AAD 6B 07            [ 1] 1791 	ld	(0x07, sp), a
                                   1792 ;	main.c: 310: h += y -1;
      008AAF 7B 06            [ 1] 1793 	ld	a, (0x06, sp)
      008AB1 4A               [ 1] 1794 	dec	a
      008AB2 6B 01            [ 1] 1795 	ld	(0x01, sp), a
      008AB4 7B 08            [ 1] 1796 	ld	a, (0x08, sp)
      008AB6 1B 01            [ 1] 1797 	add	a, (0x01, sp)
      008AB8 6B 08            [ 1] 1798 	ld	(0x08, sp), a
                                   1799 ;	main.c: 311: ST7735_Write(ST7735_CASET, CMD);
      008ABA 4B 00            [ 1] 1800 	push	#0x00
      008ABC 4B 2A            [ 1] 1801 	push	#0x2a
      008ABE CD 8A 54         [ 4] 1802 	call	_ST7735_Write
      008AC1 5B 02            [ 2] 1803 	addw	sp, #2
                                   1804 ;	main.c: 312: ST7735_Write(0x00, DAT);
      008AC3 4B 01            [ 1] 1805 	push	#0x01
      008AC5 4B 00            [ 1] 1806 	push	#0x00
      008AC7 CD 8A 54         [ 4] 1807 	call	_ST7735_Write
      008ACA 5B 02            [ 2] 1808 	addw	sp, #2
                                   1809 ;	main.c: 313: ST7735_Write(x, DAT);
      008ACC 4B 01            [ 1] 1810 	push	#0x01
      008ACE 7B 06            [ 1] 1811 	ld	a, (0x06, sp)
      008AD0 88               [ 1] 1812 	push	a
      008AD1 CD 8A 54         [ 4] 1813 	call	_ST7735_Write
      008AD4 5B 02            [ 2] 1814 	addw	sp, #2
                                   1815 ;	main.c: 314: ST7735_Write(0x00, DAT);
      008AD6 4B 01            [ 1] 1816 	push	#0x01
      008AD8 4B 00            [ 1] 1817 	push	#0x00
      008ADA CD 8A 54         [ 4] 1818 	call	_ST7735_Write
      008ADD 5B 02            [ 2] 1819 	addw	sp, #2
                                   1820 ;	main.c: 315: ST7735_Write(w, DAT);
      008ADF 4B 01            [ 1] 1821 	push	#0x01
      008AE1 7B 08            [ 1] 1822 	ld	a, (0x08, sp)
      008AE3 88               [ 1] 1823 	push	a
      008AE4 CD 8A 54         [ 4] 1824 	call	_ST7735_Write
      008AE7 5B 02            [ 2] 1825 	addw	sp, #2
                                   1826 ;	main.c: 316: ST7735_Write(ST7735_RASET, CMD);
      008AE9 4B 00            [ 1] 1827 	push	#0x00
      008AEB 4B 2B            [ 1] 1828 	push	#0x2b
      008AED CD 8A 54         [ 4] 1829 	call	_ST7735_Write
      008AF0 5B 02            [ 2] 1830 	addw	sp, #2
                                   1831 ;	main.c: 317: ST7735_Write(0x00, DAT);
      008AF2 4B 01            [ 1] 1832 	push	#0x01
      008AF4 4B 00            [ 1] 1833 	push	#0x00
      008AF6 CD 8A 54         [ 4] 1834 	call	_ST7735_Write
      008AF9 5B 02            [ 2] 1835 	addw	sp, #2
                                   1836 ;	main.c: 318: ST7735_Write(y, DAT);
      008AFB 4B 01            [ 1] 1837 	push	#0x01
      008AFD 7B 07            [ 1] 1838 	ld	a, (0x07, sp)
      008AFF 88               [ 1] 1839 	push	a
      008B00 CD 8A 54         [ 4] 1840 	call	_ST7735_Write
      008B03 5B 02            [ 2] 1841 	addw	sp, #2
                                   1842 ;	main.c: 319: ST7735_Write(0x00, DAT);
      008B05 4B 01            [ 1] 1843 	push	#0x01
      008B07 4B 00            [ 1] 1844 	push	#0x00
      008B09 CD 8A 54         [ 4] 1845 	call	_ST7735_Write
      008B0C 5B 02            [ 2] 1846 	addw	sp, #2
                                   1847 ;	main.c: 320: ST7735_Write(h, DAT);
      008B0E 4B 01            [ 1] 1848 	push	#0x01
      008B10 7B 09            [ 1] 1849 	ld	a, (0x09, sp)
      008B12 88               [ 1] 1850 	push	a
      008B13 CD 8A 54         [ 4] 1851 	call	_ST7735_Write
      008B16 5B 02            [ 2] 1852 	addw	sp, #2
                                   1853 ;	main.c: 321: ST7735_Write(ST7735_RAMWR, CMD);
      008B18 4B 00            [ 1] 1854 	push	#0x00
      008B1A 4B 2C            [ 1] 1855 	push	#0x2c
      008B1C CD 8A 54         [ 4] 1856 	call	_ST7735_Write
                                   1857 ;	main.c: 322: }
      008B1F 5B 04            [ 2] 1858 	addw	sp, #4
      008B21 81               [ 4] 1859 	ret
                                   1860 ;	main.c: 324: void ST7735_DrawPixel(int16_t x, int16_t y, uint16_t color) {
                                   1861 ;	-----------------------------------------
                                   1862 ;	 function ST7735_DrawPixel
                                   1863 ;	-----------------------------------------
      008B22                       1864 _ST7735_DrawPixel:
                                   1865 ;	main.c: 325: ST7735_SetAddrWindow(x,y,2,1);
      008B22 7B 06            [ 1] 1866 	ld	a, (0x06, sp)
      008B24 97               [ 1] 1867 	ld	xl, a
      008B25 7B 04            [ 1] 1868 	ld	a, (0x04, sp)
      008B27 4B 01            [ 1] 1869 	push	#0x01
      008B29 4B 02            [ 1] 1870 	push	#0x02
      008B2B 89               [ 2] 1871 	pushw	x
      008B2C 5B 01            [ 2] 1872 	addw	sp, #1
      008B2E 88               [ 1] 1873 	push	a
      008B2F CD 8A 9C         [ 4] 1874 	call	_ST7735_SetAddrWindow
      008B32 5B 04            [ 2] 1875 	addw	sp, #4
                                   1876 ;	main.c: 326: ST7735_Write16(color);
      008B34 1E 07            [ 2] 1877 	ldw	x, (0x07, sp)
      008B36 89               [ 2] 1878 	pushw	x
      008B37 CD 8A 73         [ 4] 1879 	call	_ST7735_Write16
      008B3A 5B 02            [ 2] 1880 	addw	sp, #2
                                   1881 ;	main.c: 327: ST7735_Write16(color);
      008B3C 1E 07            [ 2] 1882 	ldw	x, (0x07, sp)
      008B3E 89               [ 2] 1883 	pushw	x
      008B3F CD 8A 73         [ 4] 1884 	call	_ST7735_Write16
      008B42 5B 02            [ 2] 1885 	addw	sp, #2
                                   1886 ;	main.c: 328: }
      008B44 81               [ 4] 1887 	ret
                                   1888 ;	main.c: 336: void ST7735_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
                                   1889 ;	-----------------------------------------
                                   1890 ;	 function ST7735_DrawLine
                                   1891 ;	-----------------------------------------
      008B45                       1892 _ST7735_DrawLine:
      008B45 52 18            [ 2] 1893 	sub	sp, #24
                                   1894 ;	main.c: 337: int dx = abs(x2-x1), sx = x1<x2?1:-1;
      008B47 1E 1F            [ 2] 1895 	ldw	x, (0x1f, sp)
      008B49 72 F0 1B         [ 2] 1896 	subw	x, (0x1b, sp)
      008B4C 5D               [ 2] 1897 	tnzw	x
      008B4D 2A 05            [ 1] 1898 	jrpl	00110$
      008B4F 50               [ 2] 1899 	negw	x
      008B50 1F 09            [ 2] 1900 	ldw	(0x09, sp), x
      008B52 20 02            [ 2] 1901 	jra	00111$
      008B54                       1902 00110$:
      008B54 1F 09            [ 2] 1903 	ldw	(0x09, sp), x
      008B56                       1904 00111$:
      008B56 16 09            [ 2] 1905 	ldw	y, (0x09, sp)
      008B58 17 17            [ 2] 1906 	ldw	(0x17, sp), y
      008B5A 1E 1B            [ 2] 1907 	ldw	x, (0x1b, sp)
      008B5C 13 1F            [ 2] 1908 	cpw	x, (0x1f, sp)
      008B5E 2E 04            [ 1] 1909 	jrsge	00119$
      008B60 5F               [ 1] 1910 	clrw	x
      008B61 5C               [ 1] 1911 	incw	x
      008B62 20 02            [ 2] 1912 	jra	00120$
      008B64                       1913 00119$:
      008B64 5F               [ 1] 1914 	clrw	x
      008B65 5A               [ 2] 1915 	decw	x
      008B66                       1916 00120$:
      008B66 1F 15            [ 2] 1917 	ldw	(0x15, sp), x
                                   1918 ;	main.c: 338: int dy = abs(y2-y1), sy = y1<y2?1:-1;
      008B68 1E 21            [ 2] 1919 	ldw	x, (0x21, sp)
      008B6A 72 F0 1D         [ 2] 1920 	subw	x, (0x1d, sp)
      008B6D 5D               [ 2] 1921 	tnzw	x
      008B6E 2A 05            [ 1] 1922 	jrpl	00113$
      008B70 50               [ 2] 1923 	negw	x
      008B71 1F 07            [ 2] 1924 	ldw	(0x07, sp), x
      008B73 20 02            [ 2] 1925 	jra	00114$
      008B75                       1926 00113$:
      008B75 1F 07            [ 2] 1927 	ldw	(0x07, sp), x
      008B77                       1928 00114$:
      008B77 16 07            [ 2] 1929 	ldw	y, (0x07, sp)
      008B79 17 13            [ 2] 1930 	ldw	(0x13, sp), y
      008B7B 1E 1D            [ 2] 1931 	ldw	x, (0x1d, sp)
      008B7D 13 21            [ 2] 1932 	cpw	x, (0x21, sp)
      008B7F 2E 04            [ 1] 1933 	jrsge	00121$
      008B81 5F               [ 1] 1934 	clrw	x
      008B82 5C               [ 1] 1935 	incw	x
      008B83 20 02            [ 2] 1936 	jra	00122$
      008B85                       1937 00121$:
      008B85 5F               [ 1] 1938 	clrw	x
      008B86 5A               [ 2] 1939 	decw	x
      008B87                       1940 00122$:
      008B87 1F 11            [ 2] 1941 	ldw	(0x11, sp), x
                                   1942 ;	main.c: 340: int err = (dx>dy?dx:-dy)/2, e2;
      008B89 1E 17            [ 2] 1943 	ldw	x, (0x17, sp)
      008B8B 13 13            [ 2] 1944 	cpw	x, (0x13, sp)
      008B8D 2D 06            [ 1] 1945 	jrsle	00123$
      008B8F 16 17            [ 2] 1946 	ldw	y, (0x17, sp)
      008B91 17 05            [ 2] 1947 	ldw	(0x05, sp), y
      008B93 20 05            [ 2] 1948 	jra	00124$
      008B95                       1949 00123$:
      008B95 1E 13            [ 2] 1950 	ldw	x, (0x13, sp)
      008B97 50               [ 2] 1951 	negw	x
      008B98 1F 05            [ 2] 1952 	ldw	(0x05, sp), x
      008B9A                       1953 00124$:
      008B9A 4B 02            [ 1] 1954 	push	#0x02
      008B9C 4B 00            [ 1] 1955 	push	#0x00
      008B9E 1E 07            [ 2] 1956 	ldw	x, (0x07, sp)
      008BA0 89               [ 2] 1957 	pushw	x
      008BA1 CD 91 FB         [ 4] 1958 	call	__divsint
      008BA4 5B 04            [ 2] 1959 	addw	sp, #4
      008BA6 1F 0F            [ 2] 1960 	ldw	(0x0f, sp), x
                                   1961 ;	main.c: 341: int x=x1, y=y1;
      008BA8 16 1B            [ 2] 1962 	ldw	y, (0x1b, sp)
      008BAA 17 0D            [ 2] 1963 	ldw	(0x0d, sp), y
      008BAC 16 1D            [ 2] 1964 	ldw	y, (0x1d, sp)
      008BAE 17 0B            [ 2] 1965 	ldw	(0x0b, sp), y
      008BB0 7B 18            [ 1] 1966 	ld	a, (0x18, sp)
      008BB2 40               [ 1] 1967 	neg	a
      008BB3 6B 04            [ 1] 1968 	ld	(0x04, sp), a
      008BB5 4F               [ 1] 1969 	clr	a
      008BB6 12 17            [ 1] 1970 	sbc	a, (0x17, sp)
      008BB8 6B 03            [ 1] 1971 	ld	(0x03, sp), a
      008BBA                       1972 00115$:
                                   1973 ;	main.c: 343: ST7735_DrawPixel(x, y, (y<6)?RGB(17,72,0):color);
      008BBA 1E 0B            [ 2] 1974 	ldw	x, (0x0b, sp)
      008BBC A3 00 06         [ 2] 1975 	cpw	x, #0x0006
      008BBF 2E 07            [ 1] 1976 	jrsge	00125$
      008BC1 AE 12 40         [ 2] 1977 	ldw	x, #0x1240
      008BC4 1F 01            [ 2] 1978 	ldw	(0x01, sp), x
      008BC6 20 04            [ 2] 1979 	jra	00126$
      008BC8                       1980 00125$:
      008BC8 16 23            [ 2] 1981 	ldw	y, (0x23, sp)
      008BCA 17 01            [ 2] 1982 	ldw	(0x01, sp), y
      008BCC                       1983 00126$:
      008BCC 1E 01            [ 2] 1984 	ldw	x, (0x01, sp)
      008BCE 89               [ 2] 1985 	pushw	x
      008BCF 1E 0D            [ 2] 1986 	ldw	x, (0x0d, sp)
      008BD1 89               [ 2] 1987 	pushw	x
      008BD2 1E 11            [ 2] 1988 	ldw	x, (0x11, sp)
      008BD4 89               [ 2] 1989 	pushw	x
      008BD5 CD 8B 22         [ 4] 1990 	call	_ST7735_DrawPixel
      008BD8 5B 06            [ 2] 1991 	addw	sp, #6
                                   1992 ;	main.c: 344: if (x==x2 && y==y2) break;
      008BDA 1E 0D            [ 2] 1993 	ldw	x, (0x0d, sp)
      008BDC 13 1F            [ 2] 1994 	cpw	x, (0x1f, sp)
      008BDE 26 06            [ 1] 1995 	jrne	00102$
      008BE0 1E 0B            [ 2] 1996 	ldw	x, (0x0b, sp)
      008BE2 13 21            [ 2] 1997 	cpw	x, (0x21, sp)
      008BE4 27 2B            [ 1] 1998 	jreq	00117$
      008BE6                       1999 00102$:
                                   2000 ;	main.c: 345: e2 = err;
      008BE6 16 0F            [ 2] 2001 	ldw	y, (0x0f, sp)
                                   2002 ;	main.c: 346: if (e2 >-dx) { err -= dy; x += sx; }
      008BE8 1E 0F            [ 2] 2003 	ldw	x, (0x0f, sp)
      008BEA 13 03            [ 2] 2004 	cpw	x, (0x03, sp)
      008BEC 2D 0E            [ 1] 2005 	jrsle	00105$
      008BEE 1E 0F            [ 2] 2006 	ldw	x, (0x0f, sp)
      008BF0 72 F0 13         [ 2] 2007 	subw	x, (0x13, sp)
      008BF3 1F 0F            [ 2] 2008 	ldw	(0x0f, sp), x
      008BF5 1E 0D            [ 2] 2009 	ldw	x, (0x0d, sp)
      008BF7 72 FB 15         [ 2] 2010 	addw	x, (0x15, sp)
      008BFA 1F 0D            [ 2] 2011 	ldw	(0x0d, sp), x
      008BFC                       2012 00105$:
                                   2013 ;	main.c: 347: if (e2 < dy) { err += dx; y += sy; }
      008BFC 93               [ 1] 2014 	ldw	x, y
      008BFD 13 13            [ 2] 2015 	cpw	x, (0x13, sp)
      008BFF 2E B9            [ 1] 2016 	jrsge	00115$
      008C01 1E 0F            [ 2] 2017 	ldw	x, (0x0f, sp)
      008C03 72 FB 17         [ 2] 2018 	addw	x, (0x17, sp)
      008C06 1F 0F            [ 2] 2019 	ldw	(0x0f, sp), x
      008C08 1E 0B            [ 2] 2020 	ldw	x, (0x0b, sp)
      008C0A 72 FB 11         [ 2] 2021 	addw	x, (0x11, sp)
      008C0D 1F 0B            [ 2] 2022 	ldw	(0x0b, sp), x
      008C0F 20 A9            [ 2] 2023 	jra	00115$
      008C11                       2024 00117$:
                                   2025 ;	main.c: 349: }
      008C11 5B 18            [ 2] 2026 	addw	sp, #24
      008C13 81               [ 4] 2027 	ret
                                   2028 ;	main.c: 351: void ST7735_Init() {
                                   2029 ;	-----------------------------------------
                                   2030 ;	 function ST7735_Init
                                   2031 ;	-----------------------------------------
      008C14                       2032 _ST7735_Init:
                                   2033 ;	main.c: 353: PA_DDR |= (1 << DC_PIN);
      008C14 72 16 50 02      [ 1] 2034 	bset	20482, #3
                                   2035 ;	main.c: 354: PA_CR1 |= (1 << DC_PIN);
      008C18 72 16 50 03      [ 1] 2036 	bset	20483, #3
                                   2037 ;	main.c: 355: PA_ODR |= (1 << DC_PIN);
      008C1C 72 16 50 00      [ 1] 2038 	bset	20480, #3
                                   2039 ;	main.c: 357: PD_DDR |= (1 << RST_PIN);
      008C20 72 1C 50 11      [ 1] 2040 	bset	20497, #6
                                   2041 ;	main.c: 358: PD_CR1 |= (1 << RST_PIN);
      008C24 72 1C 50 12      [ 1] 2042 	bset	20498, #6
                                   2043 ;	main.c: 359: PD_ODR &= ~(1 << RST_PIN);
      008C28 C6 50 0F         [ 1] 2044 	ld	a, 0x500f
      008C2B A4 BF            [ 1] 2045 	and	a, #0xbf
      008C2D C7 50 0F         [ 1] 2046 	ld	0x500f, a
                                   2047 ;	main.c: 361: SPI_init();
      008C30 CD 8A 11         [ 4] 2048 	call	_SPI_init
                                   2049 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008C33 90 5F            [ 1] 2050 	clrw	y
      008C35 5F               [ 1] 2051 	clrw	x
      008C36                       2052 00116$:
      008C36 90 A3 2B 5C      [ 2] 2053 	cpw	y, #0x2b5c
      008C3A 9F               [ 1] 2054 	ld	a, xl
      008C3B A2 00            [ 1] 2055 	sbc	a, #0x00
      008C3D 9E               [ 1] 2056 	ld	a, xh
      008C3E A2 00            [ 1] 2057 	sbc	a, #0x00
      008C40 24 08            [ 1] 2058 	jrnc	00102$
                                   2059 ;	main.c: 33: __asm__("nop");
      008C42 9D               [ 1] 2060 	nop
                                   2061 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008C43 90 5C            [ 1] 2062 	incw	y
      008C45 26 EF            [ 1] 2063 	jrne	00116$
      008C47 5C               [ 1] 2064 	incw	x
      008C48 20 EC            [ 2] 2065 	jra	00116$
                                   2066 ;	main.c: 362: delay_ms(100);
      008C4A                       2067 00102$:
                                   2068 ;	main.c: 364: PD_ODR |= (1 << RST_PIN);
      008C4A C6 50 0F         [ 1] 2069 	ld	a, 0x500f
      008C4D AA 40            [ 1] 2070 	or	a, #0x40
      008C4F C7 50 0F         [ 1] 2071 	ld	0x500f, a
                                   2072 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008C52 90 5F            [ 1] 2073 	clrw	y
      008C54 5F               [ 1] 2074 	clrw	x
      008C55                       2075 00119$:
      008C55 90 A3 2B 5C      [ 2] 2076 	cpw	y, #0x2b5c
      008C59 9F               [ 1] 2077 	ld	a, xl
      008C5A A2 00            [ 1] 2078 	sbc	a, #0x00
      008C5C 9E               [ 1] 2079 	ld	a, xh
      008C5D A2 00            [ 1] 2080 	sbc	a, #0x00
      008C5F 24 08            [ 1] 2081 	jrnc	00104$
                                   2082 ;	main.c: 33: __asm__("nop");
      008C61 9D               [ 1] 2083 	nop
                                   2084 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008C62 90 5C            [ 1] 2085 	incw	y
      008C64 26 EF            [ 1] 2086 	jrne	00119$
      008C66 5C               [ 1] 2087 	incw	x
      008C67 20 EC            [ 2] 2088 	jra	00119$
                                   2089 ;	main.c: 365: delay_ms(100);
      008C69                       2090 00104$:
                                   2091 ;	main.c: 367: ST7735_Write(ST7735_SWRESET, CMD);
      008C69 4B 00            [ 1] 2092 	push	#0x00
      008C6B 4B 01            [ 1] 2093 	push	#0x01
      008C6D CD 8A 54         [ 4] 2094 	call	_ST7735_Write
      008C70 5B 02            [ 2] 2095 	addw	sp, #2
                                   2096 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008C72 90 5F            [ 1] 2097 	clrw	y
      008C74 5F               [ 1] 2098 	clrw	x
      008C75                       2099 00122$:
      008C75 90 A3 41 0A      [ 2] 2100 	cpw	y, #0x410a
      008C79 9F               [ 1] 2101 	ld	a, xl
      008C7A A2 00            [ 1] 2102 	sbc	a, #0x00
      008C7C 9E               [ 1] 2103 	ld	a, xh
      008C7D A2 00            [ 1] 2104 	sbc	a, #0x00
      008C7F 24 08            [ 1] 2105 	jrnc	00106$
                                   2106 ;	main.c: 33: __asm__("nop");
      008C81 9D               [ 1] 2107 	nop
                                   2108 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008C82 90 5C            [ 1] 2109 	incw	y
      008C84 26 EF            [ 1] 2110 	jrne	00122$
      008C86 5C               [ 1] 2111 	incw	x
      008C87 20 EC            [ 2] 2112 	jra	00122$
                                   2113 ;	main.c: 368: delay_ms(150);
      008C89                       2114 00106$:
                                   2115 ;	main.c: 369: ST7735_Write(ST7735_SLPOUT, CMD);
      008C89 4B 00            [ 1] 2116 	push	#0x00
      008C8B 4B 11            [ 1] 2117 	push	#0x11
      008C8D CD 8A 54         [ 4] 2118 	call	_ST7735_Write
      008C90 5B 02            [ 2] 2119 	addw	sp, #2
                                   2120 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008C92 90 5F            [ 1] 2121 	clrw	y
      008C94 5F               [ 1] 2122 	clrw	x
      008C95                       2123 00125$:
      008C95 90 A3 D8 CC      [ 2] 2124 	cpw	y, #0xd8cc
      008C99 9F               [ 1] 2125 	ld	a, xl
      008C9A A2 00            [ 1] 2126 	sbc	a, #0x00
      008C9C 9E               [ 1] 2127 	ld	a, xh
      008C9D A2 00            [ 1] 2128 	sbc	a, #0x00
      008C9F 24 08            [ 1] 2129 	jrnc	00108$
                                   2130 ;	main.c: 33: __asm__("nop");
      008CA1 9D               [ 1] 2131 	nop
                                   2132 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008CA2 90 5C            [ 1] 2133 	incw	y
      008CA4 26 EF            [ 1] 2134 	jrne	00125$
      008CA6 5C               [ 1] 2135 	incw	x
      008CA7 20 EC            [ 2] 2136 	jra	00125$
                                   2137 ;	main.c: 370: delay_ms(500);
      008CA9                       2138 00108$:
                                   2139 ;	main.c: 371: ST7735_Write(ST7735_FRMCTR1, CMD);
      008CA9 4B 00            [ 1] 2140 	push	#0x00
      008CAB 4B B1            [ 1] 2141 	push	#0xb1
      008CAD CD 8A 54         [ 4] 2142 	call	_ST7735_Write
      008CB0 5B 02            [ 2] 2143 	addw	sp, #2
                                   2144 ;	main.c: 372: ST7735_Write(0x01, DAT);
      008CB2 4B 01            [ 1] 2145 	push	#0x01
      008CB4 4B 01            [ 1] 2146 	push	#0x01
      008CB6 CD 8A 54         [ 4] 2147 	call	_ST7735_Write
      008CB9 5B 02            [ 2] 2148 	addw	sp, #2
                                   2149 ;	main.c: 373: ST7735_Write(0x2C, DAT);
      008CBB 4B 01            [ 1] 2150 	push	#0x01
      008CBD 4B 2C            [ 1] 2151 	push	#0x2c
      008CBF CD 8A 54         [ 4] 2152 	call	_ST7735_Write
      008CC2 5B 02            [ 2] 2153 	addw	sp, #2
                                   2154 ;	main.c: 374: ST7735_Write(0x2D, DAT);
      008CC4 4B 01            [ 1] 2155 	push	#0x01
      008CC6 4B 2D            [ 1] 2156 	push	#0x2d
      008CC8 CD 8A 54         [ 4] 2157 	call	_ST7735_Write
      008CCB 5B 02            [ 2] 2158 	addw	sp, #2
                                   2159 ;	main.c: 375: ST7735_Write(ST7735_FRMCTR2, CMD);
      008CCD 4B 00            [ 1] 2160 	push	#0x00
      008CCF 4B B2            [ 1] 2161 	push	#0xb2
      008CD1 CD 8A 54         [ 4] 2162 	call	_ST7735_Write
      008CD4 5B 02            [ 2] 2163 	addw	sp, #2
                                   2164 ;	main.c: 376: ST7735_Write(0x01, DAT);
      008CD6 4B 01            [ 1] 2165 	push	#0x01
      008CD8 4B 01            [ 1] 2166 	push	#0x01
      008CDA CD 8A 54         [ 4] 2167 	call	_ST7735_Write
      008CDD 5B 02            [ 2] 2168 	addw	sp, #2
                                   2169 ;	main.c: 377: ST7735_Write(0x2C, DAT);
      008CDF 4B 01            [ 1] 2170 	push	#0x01
      008CE1 4B 2C            [ 1] 2171 	push	#0x2c
      008CE3 CD 8A 54         [ 4] 2172 	call	_ST7735_Write
      008CE6 5B 02            [ 2] 2173 	addw	sp, #2
                                   2174 ;	main.c: 378: ST7735_Write(0x2D, DAT);
      008CE8 4B 01            [ 1] 2175 	push	#0x01
      008CEA 4B 2D            [ 1] 2176 	push	#0x2d
      008CEC CD 8A 54         [ 4] 2177 	call	_ST7735_Write
      008CEF 5B 02            [ 2] 2178 	addw	sp, #2
                                   2179 ;	main.c: 379: ST7735_Write(ST7735_FRMCTR3, CMD);
      008CF1 4B 00            [ 1] 2180 	push	#0x00
      008CF3 4B B3            [ 1] 2181 	push	#0xb3
      008CF5 CD 8A 54         [ 4] 2182 	call	_ST7735_Write
      008CF8 5B 02            [ 2] 2183 	addw	sp, #2
                                   2184 ;	main.c: 380: ST7735_Write(0x01, DAT);
      008CFA 4B 01            [ 1] 2185 	push	#0x01
      008CFC 4B 01            [ 1] 2186 	push	#0x01
      008CFE CD 8A 54         [ 4] 2187 	call	_ST7735_Write
      008D01 5B 02            [ 2] 2188 	addw	sp, #2
                                   2189 ;	main.c: 381: ST7735_Write(0x2C, DAT);
      008D03 4B 01            [ 1] 2190 	push	#0x01
      008D05 4B 2C            [ 1] 2191 	push	#0x2c
      008D07 CD 8A 54         [ 4] 2192 	call	_ST7735_Write
      008D0A 5B 02            [ 2] 2193 	addw	sp, #2
                                   2194 ;	main.c: 382: ST7735_Write(0x2D, DAT);
      008D0C 4B 01            [ 1] 2195 	push	#0x01
      008D0E 4B 2D            [ 1] 2196 	push	#0x2d
      008D10 CD 8A 54         [ 4] 2197 	call	_ST7735_Write
      008D13 5B 02            [ 2] 2198 	addw	sp, #2
                                   2199 ;	main.c: 383: ST7735_Write(0x01, DAT);
      008D15 4B 01            [ 1] 2200 	push	#0x01
      008D17 4B 01            [ 1] 2201 	push	#0x01
      008D19 CD 8A 54         [ 4] 2202 	call	_ST7735_Write
      008D1C 5B 02            [ 2] 2203 	addw	sp, #2
                                   2204 ;	main.c: 384: ST7735_Write(0x2C, DAT);
      008D1E 4B 01            [ 1] 2205 	push	#0x01
      008D20 4B 2C            [ 1] 2206 	push	#0x2c
      008D22 CD 8A 54         [ 4] 2207 	call	_ST7735_Write
      008D25 5B 02            [ 2] 2208 	addw	sp, #2
                                   2209 ;	main.c: 385: ST7735_Write(0x2D, DAT);
      008D27 4B 01            [ 1] 2210 	push	#0x01
      008D29 4B 2D            [ 1] 2211 	push	#0x2d
      008D2B CD 8A 54         [ 4] 2212 	call	_ST7735_Write
      008D2E 5B 02            [ 2] 2213 	addw	sp, #2
                                   2214 ;	main.c: 386: ST7735_Write(ST7735_INVCTR, CMD);
      008D30 4B 00            [ 1] 2215 	push	#0x00
      008D32 4B B4            [ 1] 2216 	push	#0xb4
      008D34 CD 8A 54         [ 4] 2217 	call	_ST7735_Write
      008D37 5B 02            [ 2] 2218 	addw	sp, #2
                                   2219 ;	main.c: 387: ST7735_Write(0x07, DAT);
      008D39 4B 01            [ 1] 2220 	push	#0x01
      008D3B 4B 07            [ 1] 2221 	push	#0x07
      008D3D CD 8A 54         [ 4] 2222 	call	_ST7735_Write
      008D40 5B 02            [ 2] 2223 	addw	sp, #2
                                   2224 ;	main.c: 388: ST7735_Write(ST7735_PWCTR1, CMD);
      008D42 4B 00            [ 1] 2225 	push	#0x00
      008D44 4B C0            [ 1] 2226 	push	#0xc0
      008D46 CD 8A 54         [ 4] 2227 	call	_ST7735_Write
      008D49 5B 02            [ 2] 2228 	addw	sp, #2
                                   2229 ;	main.c: 389: ST7735_Write(0xA2, DAT);
      008D4B 4B 01            [ 1] 2230 	push	#0x01
      008D4D 4B A2            [ 1] 2231 	push	#0xa2
      008D4F CD 8A 54         [ 4] 2232 	call	_ST7735_Write
      008D52 5B 02            [ 2] 2233 	addw	sp, #2
                                   2234 ;	main.c: 390: ST7735_Write(0x02, DAT);
      008D54 4B 01            [ 1] 2235 	push	#0x01
      008D56 4B 02            [ 1] 2236 	push	#0x02
      008D58 CD 8A 54         [ 4] 2237 	call	_ST7735_Write
      008D5B 5B 02            [ 2] 2238 	addw	sp, #2
                                   2239 ;	main.c: 391: ST7735_Write(0x84, DAT);
      008D5D 4B 01            [ 1] 2240 	push	#0x01
      008D5F 4B 84            [ 1] 2241 	push	#0x84
      008D61 CD 8A 54         [ 4] 2242 	call	_ST7735_Write
      008D64 5B 02            [ 2] 2243 	addw	sp, #2
                                   2244 ;	main.c: 392: ST7735_Write(ST7735_PWCTR2, CMD);
      008D66 4B 00            [ 1] 2245 	push	#0x00
      008D68 4B C1            [ 1] 2246 	push	#0xc1
      008D6A CD 8A 54         [ 4] 2247 	call	_ST7735_Write
      008D6D 5B 02            [ 2] 2248 	addw	sp, #2
                                   2249 ;	main.c: 393: ST7735_Write(0xC5, DAT);
      008D6F 4B 01            [ 1] 2250 	push	#0x01
      008D71 4B C5            [ 1] 2251 	push	#0xc5
      008D73 CD 8A 54         [ 4] 2252 	call	_ST7735_Write
      008D76 5B 02            [ 2] 2253 	addw	sp, #2
                                   2254 ;	main.c: 394: ST7735_Write(ST7735_PWCTR3, CMD);
      008D78 4B 00            [ 1] 2255 	push	#0x00
      008D7A 4B C2            [ 1] 2256 	push	#0xc2
      008D7C CD 8A 54         [ 4] 2257 	call	_ST7735_Write
      008D7F 5B 02            [ 2] 2258 	addw	sp, #2
                                   2259 ;	main.c: 395: ST7735_Write(0x0A, DAT);
      008D81 4B 01            [ 1] 2260 	push	#0x01
      008D83 4B 0A            [ 1] 2261 	push	#0x0a
      008D85 CD 8A 54         [ 4] 2262 	call	_ST7735_Write
      008D88 5B 02            [ 2] 2263 	addw	sp, #2
                                   2264 ;	main.c: 396: ST7735_Write(0x00, DAT);
      008D8A 4B 01            [ 1] 2265 	push	#0x01
      008D8C 4B 00            [ 1] 2266 	push	#0x00
      008D8E CD 8A 54         [ 4] 2267 	call	_ST7735_Write
      008D91 5B 02            [ 2] 2268 	addw	sp, #2
                                   2269 ;	main.c: 397: ST7735_Write(ST7735_PWCTR4, CMD);
      008D93 4B 00            [ 1] 2270 	push	#0x00
      008D95 4B C3            [ 1] 2271 	push	#0xc3
      008D97 CD 8A 54         [ 4] 2272 	call	_ST7735_Write
      008D9A 5B 02            [ 2] 2273 	addw	sp, #2
                                   2274 ;	main.c: 398: ST7735_Write(0x8A, DAT);
      008D9C 4B 01            [ 1] 2275 	push	#0x01
      008D9E 4B 8A            [ 1] 2276 	push	#0x8a
      008DA0 CD 8A 54         [ 4] 2277 	call	_ST7735_Write
      008DA3 5B 02            [ 2] 2278 	addw	sp, #2
                                   2279 ;	main.c: 399: ST7735_Write(0x2A, DAT);
      008DA5 4B 01            [ 1] 2280 	push	#0x01
      008DA7 4B 2A            [ 1] 2281 	push	#0x2a
      008DA9 CD 8A 54         [ 4] 2282 	call	_ST7735_Write
      008DAC 5B 02            [ 2] 2283 	addw	sp, #2
                                   2284 ;	main.c: 400: ST7735_Write(ST7735_PWCTR5, CMD);
      008DAE 4B 00            [ 1] 2285 	push	#0x00
      008DB0 4B C4            [ 1] 2286 	push	#0xc4
      008DB2 CD 8A 54         [ 4] 2287 	call	_ST7735_Write
      008DB5 5B 02            [ 2] 2288 	addw	sp, #2
                                   2289 ;	main.c: 401: ST7735_Write(0x8A, DAT);
      008DB7 4B 01            [ 1] 2290 	push	#0x01
      008DB9 4B 8A            [ 1] 2291 	push	#0x8a
      008DBB CD 8A 54         [ 4] 2292 	call	_ST7735_Write
      008DBE 5B 02            [ 2] 2293 	addw	sp, #2
                                   2294 ;	main.c: 402: ST7735_Write(0xEE, DAT);
      008DC0 4B 01            [ 1] 2295 	push	#0x01
      008DC2 4B EE            [ 1] 2296 	push	#0xee
      008DC4 CD 8A 54         [ 4] 2297 	call	_ST7735_Write
      008DC7 5B 02            [ 2] 2298 	addw	sp, #2
                                   2299 ;	main.c: 403: ST7735_Write(ST7735_VMCTR1, CMD);
      008DC9 4B 00            [ 1] 2300 	push	#0x00
      008DCB 4B C5            [ 1] 2301 	push	#0xc5
      008DCD CD 8A 54         [ 4] 2302 	call	_ST7735_Write
      008DD0 5B 02            [ 2] 2303 	addw	sp, #2
                                   2304 ;	main.c: 404: ST7735_Write(0x0E, DAT);
      008DD2 4B 01            [ 1] 2305 	push	#0x01
      008DD4 4B 0E            [ 1] 2306 	push	#0x0e
      008DD6 CD 8A 54         [ 4] 2307 	call	_ST7735_Write
      008DD9 5B 02            [ 2] 2308 	addw	sp, #2
                                   2309 ;	main.c: 405: ST7735_Write(ST7735_INVOFF, CMD);
      008DDB 4B 00            [ 1] 2310 	push	#0x00
      008DDD 4B 20            [ 1] 2311 	push	#0x20
      008DDF CD 8A 54         [ 4] 2312 	call	_ST7735_Write
      008DE2 5B 02            [ 2] 2313 	addw	sp, #2
                                   2314 ;	main.c: 406: ST7735_Write(ST7735_MADCTL, CMD);
      008DE4 4B 00            [ 1] 2315 	push	#0x00
      008DE6 4B 36            [ 1] 2316 	push	#0x36
      008DE8 CD 8A 54         [ 4] 2317 	call	_ST7735_Write
      008DEB 5B 02            [ 2] 2318 	addw	sp, #2
                                   2319 ;	main.c: 407: ST7735_Write(0xC8, DAT);
      008DED 4B 01            [ 1] 2320 	push	#0x01
      008DEF 4B C8            [ 1] 2321 	push	#0xc8
      008DF1 CD 8A 54         [ 4] 2322 	call	_ST7735_Write
      008DF4 5B 02            [ 2] 2323 	addw	sp, #2
                                   2324 ;	main.c: 408: ST7735_Write(ST7735_COLMOD, CMD);
      008DF6 4B 00            [ 1] 2325 	push	#0x00
      008DF8 4B 3A            [ 1] 2326 	push	#0x3a
      008DFA CD 8A 54         [ 4] 2327 	call	_ST7735_Write
      008DFD 5B 02            [ 2] 2328 	addw	sp, #2
                                   2329 ;	main.c: 409: ST7735_Write(0x05, DAT);
      008DFF 4B 01            [ 1] 2330 	push	#0x01
      008E01 4B 05            [ 1] 2331 	push	#0x05
      008E03 CD 8A 54         [ 4] 2332 	call	_ST7735_Write
      008E06 5B 02            [ 2] 2333 	addw	sp, #2
                                   2334 ;	main.c: 413: ST7735_Write(ST7735_CASET, CMD);
      008E08 4B 00            [ 1] 2335 	push	#0x00
      008E0A 4B 2A            [ 1] 2336 	push	#0x2a
      008E0C CD 8A 54         [ 4] 2337 	call	_ST7735_Write
      008E0F 5B 02            [ 2] 2338 	addw	sp, #2
                                   2339 ;	main.c: 414: ST7735_Write(0x00, DAT);
      008E11 4B 01            [ 1] 2340 	push	#0x01
      008E13 4B 00            [ 1] 2341 	push	#0x00
      008E15 CD 8A 54         [ 4] 2342 	call	_ST7735_Write
      008E18 5B 02            [ 2] 2343 	addw	sp, #2
                                   2344 ;	main.c: 415: ST7735_Write(0x00, DAT);
      008E1A 4B 01            [ 1] 2345 	push	#0x01
      008E1C 4B 00            [ 1] 2346 	push	#0x00
      008E1E CD 8A 54         [ 4] 2347 	call	_ST7735_Write
      008E21 5B 02            [ 2] 2348 	addw	sp, #2
                                   2349 ;	main.c: 416: ST7735_Write(0x00, DAT);
      008E23 4B 01            [ 1] 2350 	push	#0x01
      008E25 4B 00            [ 1] 2351 	push	#0x00
      008E27 CD 8A 54         [ 4] 2352 	call	_ST7735_Write
      008E2A 5B 02            [ 2] 2353 	addw	sp, #2
                                   2354 ;	main.c: 417: ST7735_Write(0x4F, DAT);
      008E2C 4B 01            [ 1] 2355 	push	#0x01
      008E2E 4B 4F            [ 1] 2356 	push	#0x4f
      008E30 CD 8A 54         [ 4] 2357 	call	_ST7735_Write
      008E33 5B 02            [ 2] 2358 	addw	sp, #2
                                   2359 ;	main.c: 418: ST7735_Write(ST7735_RASET, CMD);
      008E35 4B 00            [ 1] 2360 	push	#0x00
      008E37 4B 2B            [ 1] 2361 	push	#0x2b
      008E39 CD 8A 54         [ 4] 2362 	call	_ST7735_Write
      008E3C 5B 02            [ 2] 2363 	addw	sp, #2
                                   2364 ;	main.c: 419: ST7735_Write(0x00, DAT);
      008E3E 4B 01            [ 1] 2365 	push	#0x01
      008E40 4B 00            [ 1] 2366 	push	#0x00
      008E42 CD 8A 54         [ 4] 2367 	call	_ST7735_Write
      008E45 5B 02            [ 2] 2368 	addw	sp, #2
                                   2369 ;	main.c: 420: ST7735_Write(0x00, DAT);
      008E47 4B 01            [ 1] 2370 	push	#0x01
      008E49 4B 00            [ 1] 2371 	push	#0x00
      008E4B CD 8A 54         [ 4] 2372 	call	_ST7735_Write
      008E4E 5B 02            [ 2] 2373 	addw	sp, #2
                                   2374 ;	main.c: 421: ST7735_Write(0x00, DAT);
      008E50 4B 01            [ 1] 2375 	push	#0x01
      008E52 4B 00            [ 1] 2376 	push	#0x00
      008E54 CD 8A 54         [ 4] 2377 	call	_ST7735_Write
      008E57 5B 02            [ 2] 2378 	addw	sp, #2
                                   2379 ;	main.c: 422: ST7735_Write(0x9F, DAT);
      008E59 4B 01            [ 1] 2380 	push	#0x01
      008E5B 4B 9F            [ 1] 2381 	push	#0x9f
      008E5D CD 8A 54         [ 4] 2382 	call	_ST7735_Write
      008E60 5B 02            [ 2] 2383 	addw	sp, #2
                                   2384 ;	main.c: 426: ST7735_Write(ST7735_GMCTRP1, CMD);
      008E62 4B 00            [ 1] 2385 	push	#0x00
      008E64 4B E0            [ 1] 2386 	push	#0xe0
      008E66 CD 8A 54         [ 4] 2387 	call	_ST7735_Write
      008E69 5B 02            [ 2] 2388 	addw	sp, #2
                                   2389 ;	main.c: 427: ST7735_Write(0x02, DAT);
      008E6B 4B 01            [ 1] 2390 	push	#0x01
      008E6D 4B 02            [ 1] 2391 	push	#0x02
      008E6F CD 8A 54         [ 4] 2392 	call	_ST7735_Write
      008E72 5B 02            [ 2] 2393 	addw	sp, #2
                                   2394 ;	main.c: 428: ST7735_Write(0x1C, DAT);
      008E74 4B 01            [ 1] 2395 	push	#0x01
      008E76 4B 1C            [ 1] 2396 	push	#0x1c
      008E78 CD 8A 54         [ 4] 2397 	call	_ST7735_Write
      008E7B 5B 02            [ 2] 2398 	addw	sp, #2
                                   2399 ;	main.c: 429: ST7735_Write(0x07, DAT);
      008E7D 4B 01            [ 1] 2400 	push	#0x01
      008E7F 4B 07            [ 1] 2401 	push	#0x07
      008E81 CD 8A 54         [ 4] 2402 	call	_ST7735_Write
      008E84 5B 02            [ 2] 2403 	addw	sp, #2
                                   2404 ;	main.c: 430: ST7735_Write(0x12, DAT);
      008E86 4B 01            [ 1] 2405 	push	#0x01
      008E88 4B 12            [ 1] 2406 	push	#0x12
      008E8A CD 8A 54         [ 4] 2407 	call	_ST7735_Write
      008E8D 5B 02            [ 2] 2408 	addw	sp, #2
                                   2409 ;	main.c: 431: ST7735_Write(0x37, DAT);
      008E8F 4B 01            [ 1] 2410 	push	#0x01
      008E91 4B 37            [ 1] 2411 	push	#0x37
      008E93 CD 8A 54         [ 4] 2412 	call	_ST7735_Write
      008E96 5B 02            [ 2] 2413 	addw	sp, #2
                                   2414 ;	main.c: 432: ST7735_Write(0x32, DAT);
      008E98 4B 01            [ 1] 2415 	push	#0x01
      008E9A 4B 32            [ 1] 2416 	push	#0x32
      008E9C CD 8A 54         [ 4] 2417 	call	_ST7735_Write
      008E9F 5B 02            [ 2] 2418 	addw	sp, #2
                                   2419 ;	main.c: 433: ST7735_Write(0x29, DAT);
      008EA1 4B 01            [ 1] 2420 	push	#0x01
      008EA3 4B 29            [ 1] 2421 	push	#0x29
      008EA5 CD 8A 54         [ 4] 2422 	call	_ST7735_Write
      008EA8 5B 02            [ 2] 2423 	addw	sp, #2
                                   2424 ;	main.c: 434: ST7735_Write(0x2D, DAT);
      008EAA 4B 01            [ 1] 2425 	push	#0x01
      008EAC 4B 2D            [ 1] 2426 	push	#0x2d
      008EAE CD 8A 54         [ 4] 2427 	call	_ST7735_Write
      008EB1 5B 02            [ 2] 2428 	addw	sp, #2
                                   2429 ;	main.c: 435: ST7735_Write(0x29, DAT);
      008EB3 4B 01            [ 1] 2430 	push	#0x01
      008EB5 4B 29            [ 1] 2431 	push	#0x29
      008EB7 CD 8A 54         [ 4] 2432 	call	_ST7735_Write
      008EBA 5B 02            [ 2] 2433 	addw	sp, #2
                                   2434 ;	main.c: 436: ST7735_Write(0x25, DAT);
      008EBC 4B 01            [ 1] 2435 	push	#0x01
      008EBE 4B 25            [ 1] 2436 	push	#0x25
      008EC0 CD 8A 54         [ 4] 2437 	call	_ST7735_Write
      008EC3 5B 02            [ 2] 2438 	addw	sp, #2
                                   2439 ;	main.c: 437: ST7735_Write(0x2B, DAT);
      008EC5 4B 01            [ 1] 2440 	push	#0x01
      008EC7 4B 2B            [ 1] 2441 	push	#0x2b
      008EC9 CD 8A 54         [ 4] 2442 	call	_ST7735_Write
      008ECC 5B 02            [ 2] 2443 	addw	sp, #2
                                   2444 ;	main.c: 438: ST7735_Write(0x39, DAT);
      008ECE 4B 01            [ 1] 2445 	push	#0x01
      008ED0 4B 39            [ 1] 2446 	push	#0x39
      008ED2 CD 8A 54         [ 4] 2447 	call	_ST7735_Write
      008ED5 5B 02            [ 2] 2448 	addw	sp, #2
                                   2449 ;	main.c: 439: ST7735_Write(0x00, DAT);
      008ED7 4B 01            [ 1] 2450 	push	#0x01
      008ED9 4B 00            [ 1] 2451 	push	#0x00
      008EDB CD 8A 54         [ 4] 2452 	call	_ST7735_Write
      008EDE 5B 02            [ 2] 2453 	addw	sp, #2
                                   2454 ;	main.c: 440: ST7735_Write(0x01, DAT);
      008EE0 4B 01            [ 1] 2455 	push	#0x01
      008EE2 4B 01            [ 1] 2456 	push	#0x01
      008EE4 CD 8A 54         [ 4] 2457 	call	_ST7735_Write
      008EE7 5B 02            [ 2] 2458 	addw	sp, #2
                                   2459 ;	main.c: 441: ST7735_Write(0x03, DAT);
      008EE9 4B 01            [ 1] 2460 	push	#0x01
      008EEB 4B 03            [ 1] 2461 	push	#0x03
      008EED CD 8A 54         [ 4] 2462 	call	_ST7735_Write
      008EF0 5B 02            [ 2] 2463 	addw	sp, #2
                                   2464 ;	main.c: 442: ST7735_Write(0x10, DAT);
      008EF2 4B 01            [ 1] 2465 	push	#0x01
      008EF4 4B 10            [ 1] 2466 	push	#0x10
      008EF6 CD 8A 54         [ 4] 2467 	call	_ST7735_Write
      008EF9 5B 02            [ 2] 2468 	addw	sp, #2
                                   2469 ;	main.c: 443: ST7735_Write(ST7735_GMCTRN1, CMD);
      008EFB 4B 00            [ 1] 2470 	push	#0x00
      008EFD 4B E1            [ 1] 2471 	push	#0xe1
      008EFF CD 8A 54         [ 4] 2472 	call	_ST7735_Write
      008F02 5B 02            [ 2] 2473 	addw	sp, #2
                                   2474 ;	main.c: 444: ST7735_Write(0x03, DAT);
      008F04 4B 01            [ 1] 2475 	push	#0x01
      008F06 4B 03            [ 1] 2476 	push	#0x03
      008F08 CD 8A 54         [ 4] 2477 	call	_ST7735_Write
      008F0B 5B 02            [ 2] 2478 	addw	sp, #2
                                   2479 ;	main.c: 445: ST7735_Write(0x1D, DAT);
      008F0D 4B 01            [ 1] 2480 	push	#0x01
      008F0F 4B 1D            [ 1] 2481 	push	#0x1d
      008F11 CD 8A 54         [ 4] 2482 	call	_ST7735_Write
      008F14 5B 02            [ 2] 2483 	addw	sp, #2
                                   2484 ;	main.c: 446: ST7735_Write(0x07, DAT);
      008F16 4B 01            [ 1] 2485 	push	#0x01
      008F18 4B 07            [ 1] 2486 	push	#0x07
      008F1A CD 8A 54         [ 4] 2487 	call	_ST7735_Write
      008F1D 5B 02            [ 2] 2488 	addw	sp, #2
                                   2489 ;	main.c: 447: ST7735_Write(0x06, DAT);
      008F1F 4B 01            [ 1] 2490 	push	#0x01
      008F21 4B 06            [ 1] 2491 	push	#0x06
      008F23 CD 8A 54         [ 4] 2492 	call	_ST7735_Write
      008F26 5B 02            [ 2] 2493 	addw	sp, #2
                                   2494 ;	main.c: 448: ST7735_Write(0x2E, DAT);
      008F28 4B 01            [ 1] 2495 	push	#0x01
      008F2A 4B 2E            [ 1] 2496 	push	#0x2e
      008F2C CD 8A 54         [ 4] 2497 	call	_ST7735_Write
      008F2F 5B 02            [ 2] 2498 	addw	sp, #2
                                   2499 ;	main.c: 449: ST7735_Write(0x2C, DAT);
      008F31 4B 01            [ 1] 2500 	push	#0x01
      008F33 4B 2C            [ 1] 2501 	push	#0x2c
      008F35 CD 8A 54         [ 4] 2502 	call	_ST7735_Write
      008F38 5B 02            [ 2] 2503 	addw	sp, #2
                                   2504 ;	main.c: 450: ST7735_Write(0x29, DAT);
      008F3A 4B 01            [ 1] 2505 	push	#0x01
      008F3C 4B 29            [ 1] 2506 	push	#0x29
      008F3E CD 8A 54         [ 4] 2507 	call	_ST7735_Write
      008F41 5B 02            [ 2] 2508 	addw	sp, #2
                                   2509 ;	main.c: 451: ST7735_Write(0x2D, DAT);
      008F43 4B 01            [ 1] 2510 	push	#0x01
      008F45 4B 2D            [ 1] 2511 	push	#0x2d
      008F47 CD 8A 54         [ 4] 2512 	call	_ST7735_Write
      008F4A 5B 02            [ 2] 2513 	addw	sp, #2
                                   2514 ;	main.c: 452: ST7735_Write(0x2E, DAT);
      008F4C 4B 01            [ 1] 2515 	push	#0x01
      008F4E 4B 2E            [ 1] 2516 	push	#0x2e
      008F50 CD 8A 54         [ 4] 2517 	call	_ST7735_Write
      008F53 5B 02            [ 2] 2518 	addw	sp, #2
                                   2519 ;	main.c: 453: ST7735_Write(0x2E, DAT);
      008F55 4B 01            [ 1] 2520 	push	#0x01
      008F57 4B 2E            [ 1] 2521 	push	#0x2e
      008F59 CD 8A 54         [ 4] 2522 	call	_ST7735_Write
      008F5C 5B 02            [ 2] 2523 	addw	sp, #2
                                   2524 ;	main.c: 454: ST7735_Write(0x37, DAT);
      008F5E 4B 01            [ 1] 2525 	push	#0x01
      008F60 4B 37            [ 1] 2526 	push	#0x37
      008F62 CD 8A 54         [ 4] 2527 	call	_ST7735_Write
      008F65 5B 02            [ 2] 2528 	addw	sp, #2
                                   2529 ;	main.c: 455: ST7735_Write(0x3F, DAT);
      008F67 4B 01            [ 1] 2530 	push	#0x01
      008F69 4B 3F            [ 1] 2531 	push	#0x3f
      008F6B CD 8A 54         [ 4] 2532 	call	_ST7735_Write
      008F6E 5B 02            [ 2] 2533 	addw	sp, #2
                                   2534 ;	main.c: 456: ST7735_Write(0x00, DAT);
      008F70 4B 01            [ 1] 2535 	push	#0x01
      008F72 4B 00            [ 1] 2536 	push	#0x00
      008F74 CD 8A 54         [ 4] 2537 	call	_ST7735_Write
      008F77 5B 02            [ 2] 2538 	addw	sp, #2
                                   2539 ;	main.c: 457: ST7735_Write(0x00, DAT);
      008F79 4B 01            [ 1] 2540 	push	#0x01
      008F7B 4B 00            [ 1] 2541 	push	#0x00
      008F7D CD 8A 54         [ 4] 2542 	call	_ST7735_Write
      008F80 5B 02            [ 2] 2543 	addw	sp, #2
                                   2544 ;	main.c: 458: ST7735_Write(0x02, DAT);
      008F82 4B 01            [ 1] 2545 	push	#0x01
      008F84 4B 02            [ 1] 2546 	push	#0x02
      008F86 CD 8A 54         [ 4] 2547 	call	_ST7735_Write
      008F89 5B 02            [ 2] 2548 	addw	sp, #2
                                   2549 ;	main.c: 459: ST7735_Write(0x10, DAT);
      008F8B 4B 01            [ 1] 2550 	push	#0x01
      008F8D 4B 10            [ 1] 2551 	push	#0x10
      008F8F CD 8A 54         [ 4] 2552 	call	_ST7735_Write
      008F92 5B 02            [ 2] 2553 	addw	sp, #2
                                   2554 ;	main.c: 460: ST7735_Write(ST7735_NORON, CMD);
      008F94 4B 00            [ 1] 2555 	push	#0x00
      008F96 4B 13            [ 1] 2556 	push	#0x13
      008F98 CD 8A 54         [ 4] 2557 	call	_ST7735_Write
      008F9B 5B 02            [ 2] 2558 	addw	sp, #2
                                   2559 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008F9D 90 5F            [ 1] 2560 	clrw	y
      008F9F 5F               [ 1] 2561 	clrw	x
      008FA0                       2562 00128$:
      008FA0 90 A3 04 56      [ 2] 2563 	cpw	y, #0x0456
      008FA4 9F               [ 1] 2564 	ld	a, xl
      008FA5 A2 00            [ 1] 2565 	sbc	a, #0x00
      008FA7 9E               [ 1] 2566 	ld	a, xh
      008FA8 A2 00            [ 1] 2567 	sbc	a, #0x00
      008FAA 24 08            [ 1] 2568 	jrnc	00110$
                                   2569 ;	main.c: 33: __asm__("nop");
      008FAC 9D               [ 1] 2570 	nop
                                   2571 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008FAD 90 5C            [ 1] 2572 	incw	y
      008FAF 26 EF            [ 1] 2573 	jrne	00128$
      008FB1 5C               [ 1] 2574 	incw	x
      008FB2 20 EC            [ 2] 2575 	jra	00128$
                                   2576 ;	main.c: 461: delay_ms(10);
      008FB4                       2577 00110$:
                                   2578 ;	main.c: 462: ST7735_Write(ST7735_DISPON, CMD);
      008FB4 4B 00            [ 1] 2579 	push	#0x00
      008FB6 4B 29            [ 1] 2580 	push	#0x29
      008FB8 CD 8A 54         [ 4] 2581 	call	_ST7735_Write
      008FBB 5B 02            [ 2] 2582 	addw	sp, #2
                                   2583 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008FBD 90 5F            [ 1] 2584 	clrw	y
      008FBF 5F               [ 1] 2585 	clrw	x
      008FC0                       2586 00131$:
      008FC0 90 A3 2B 5C      [ 2] 2587 	cpw	y, #0x2b5c
      008FC4 9F               [ 1] 2588 	ld	a, xl
      008FC5 A2 00            [ 1] 2589 	sbc	a, #0x00
      008FC7 9E               [ 1] 2590 	ld	a, xh
      008FC8 A2 00            [ 1] 2591 	sbc	a, #0x00
      008FCA 24 08            [ 1] 2592 	jrnc	00112$
                                   2593 ;	main.c: 33: __asm__("nop");
      008FCC 9D               [ 1] 2594 	nop
                                   2595 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008FCD 90 5C            [ 1] 2596 	incw	y
      008FCF 26 EF            [ 1] 2597 	jrne	00131$
      008FD1 5C               [ 1] 2598 	incw	x
      008FD2 20 EC            [ 2] 2599 	jra	00131$
                                   2600 ;	main.c: 463: delay_ms(100);
      008FD4                       2601 00112$:
                                   2602 ;	main.c: 465: ST7735_Write(ST7735_MADCTL, CMD);
      008FD4 4B 00            [ 1] 2603 	push	#0x00
      008FD6 4B 36            [ 1] 2604 	push	#0x36
      008FD8 CD 8A 54         [ 4] 2605 	call	_ST7735_Write
      008FDB 5B 02            [ 2] 2606 	addw	sp, #2
                                   2607 ;	main.c: 466: ST7735_Write(MADCTL_MX | MADCTL_MV | MADCTL_RGB, DAT);
      008FDD 4B 01            [ 1] 2608 	push	#0x01
      008FDF 4B 68            [ 1] 2609 	push	#0x68
      008FE1 CD 8A 54         [ 4] 2610 	call	_ST7735_Write
      008FE4 5B 02            [ 2] 2611 	addw	sp, #2
                                   2612 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008FE6 90 5F            [ 1] 2613 	clrw	y
      008FE8 5F               [ 1] 2614 	clrw	x
      008FE9                       2615 00134$:
      008FE9 90 A3 04 56      [ 2] 2616 	cpw	y, #0x0456
      008FED 9F               [ 1] 2617 	ld	a, xl
      008FEE A2 00            [ 1] 2618 	sbc	a, #0x00
      008FF0 9E               [ 1] 2619 	ld	a, xh
      008FF1 A2 00            [ 1] 2620 	sbc	a, #0x00
      008FF3 25 01            [ 1] 2621 	jrc	00227$
      008FF5 81               [ 4] 2622 	ret
      008FF6                       2623 00227$:
                                   2624 ;	main.c: 33: __asm__("nop");
      008FF6 9D               [ 1] 2625 	nop
                                   2626 ;	main.c: 32: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008FF7 90 5C            [ 1] 2627 	incw	y
      008FF9 26 EE            [ 1] 2628 	jrne	00134$
      008FFB 5C               [ 1] 2629 	incw	x
      008FFC 20 EB            [ 2] 2630 	jra	00134$
                                   2631 ;	main.c: 467: delay_ms(10);
                                   2632 ;	main.c: 468: }
      008FFE 81               [ 4] 2633 	ret
                                   2634 ;	main.c: 471: void ST7735_Clear(uint16_t color) {
                                   2635 ;	-----------------------------------------
                                   2636 ;	 function ST7735_Clear
                                   2637 ;	-----------------------------------------
      008FFF                       2638 _ST7735_Clear:
      008FFF 52 02            [ 2] 2639 	sub	sp, #2
                                   2640 ;	main.c: 472: ST7735_SetAddrWindow(0,0,ST7735_TFTLENGTH+3,ST7735_TFTWIDTH+3);
      009001 4B 53            [ 1] 2641 	push	#0x53
      009003 4B A3            [ 1] 2642 	push	#0xa3
      009005 4B 00            [ 1] 2643 	push	#0x00
      009007 4B 00            [ 1] 2644 	push	#0x00
      009009 CD 8A 9C         [ 4] 2645 	call	_ST7735_SetAddrWindow
      00900C 5B 04            [ 2] 2646 	addw	sp, #4
                                   2647 ;	main.c: 473: for (int i=0; i< ST7735_TFTWIDTH+3; ++i)
      00900E 5F               [ 1] 2648 	clrw	x
      00900F 1F 01            [ 2] 2649 	ldw	(0x01, sp), x
      009011                       2650 00107$:
      009011 1E 01            [ 2] 2651 	ldw	x, (0x01, sp)
      009013 A3 00 53         [ 2] 2652 	cpw	x, #0x0053
      009016 2E 1B            [ 1] 2653 	jrsge	00109$
                                   2654 ;	main.c: 474: for(int j=0; j< ST7735_TFTLENGTH+3; ++j)
      009018 5F               [ 1] 2655 	clrw	x
      009019                       2656 00104$:
      009019 A3 00 A3         [ 2] 2657 	cpw	x, #0x00a3
      00901C 2E 0E            [ 1] 2658 	jrsge	00108$
                                   2659 ;	main.c: 475: ST7735_Write16(color);
      00901E 89               [ 2] 2660 	pushw	x
      00901F 16 07            [ 2] 2661 	ldw	y, (0x07, sp)
      009021 90 89            [ 2] 2662 	pushw	y
      009023 CD 8A 73         [ 4] 2663 	call	_ST7735_Write16
      009026 5B 02            [ 2] 2664 	addw	sp, #2
      009028 85               [ 2] 2665 	popw	x
                                   2666 ;	main.c: 474: for(int j=0; j< ST7735_TFTLENGTH+3; ++j)
      009029 5C               [ 1] 2667 	incw	x
      00902A 20 ED            [ 2] 2668 	jra	00104$
      00902C                       2669 00108$:
                                   2670 ;	main.c: 473: for (int i=0; i< ST7735_TFTWIDTH+3; ++i)
      00902C 1E 01            [ 2] 2671 	ldw	x, (0x01, sp)
      00902E 5C               [ 1] 2672 	incw	x
      00902F 1F 01            [ 2] 2673 	ldw	(0x01, sp), x
      009031 20 DE            [ 2] 2674 	jra	00107$
      009033                       2675 00109$:
                                   2676 ;	main.c: 476: }
      009033 5B 02            [ 2] 2677 	addw	sp, #2
      009035 81               [ 4] 2678 	ret
                                   2679 ;	main.c: 478: void ST7735_Draw(int16_t x, int16_t y, const uint8_t *data, uint8_t w, uint8_t h) {
                                   2680 ;	-----------------------------------------
                                   2681 ;	 function ST7735_Draw
                                   2682 ;	-----------------------------------------
      009036                       2683 _ST7735_Draw:
      009036 52 12            [ 2] 2684 	sub	sp, #18
                                   2685 ;	main.c: 479: uint8_t xoff=0, yoff=0, wend=w, hend=h;
      009038 0F 06            [ 1] 2686 	clr	(0x06, sp)
      00903A 0F 05            [ 1] 2687 	clr	(0x05, sp)
      00903C 7B 1B            [ 1] 2688 	ld	a, (0x1b, sp)
      00903E 6B 04            [ 1] 2689 	ld	(0x04, sp), a
      009040 7B 1C            [ 1] 2690 	ld	a, (0x1c, sp)
      009042 6B 03            [ 1] 2691 	ld	(0x03, sp), a
                                   2692 ;	main.c: 481: xoff = 0 - x;
      009044 7B 16            [ 1] 2693 	ld	a, (0x16, sp)
      009046 97               [ 1] 2694 	ld	xl, a
                                   2695 ;	main.c: 480: if (x < 0)
      009047 0D 15            [ 1] 2696 	tnz	(0x15, sp)
      009049 2A 04            [ 1] 2697 	jrpl	00102$
                                   2698 ;	main.c: 481: xoff = 0 - x;
      00904B 9F               [ 1] 2699 	ld	a, xl
      00904C 40               [ 1] 2700 	neg	a
      00904D 6B 06            [ 1] 2701 	ld	(0x06, sp), a
      00904F                       2702 00102$:
                                   2703 ;	main.c: 482: if ((x+w) > ST7735_TFTLENGTH)
      00904F 7B 04            [ 1] 2704 	ld	a, (0x04, sp)
      009051 90 5F            [ 1] 2705 	clrw	y
      009053 90 97            [ 1] 2706 	ld	yl, a
      009055 72 F9 15         [ 2] 2707 	addw	y, (0x15, sp)
      009058 90 A3 00 A0      [ 2] 2708 	cpw	y, #0x00a0
      00905C 2D 08            [ 1] 2709 	jrsle	00104$
                                   2710 ;	main.c: 483: wend = ST7735_TFTLENGTH-x;
      00905E A6 A0            [ 1] 2711 	ld	a, #0xa0
      009060 89               [ 2] 2712 	pushw	x
      009061 10 02            [ 1] 2713 	sub	a, (#2, sp)
      009063 85               [ 2] 2714 	popw	x
      009064 6B 04            [ 1] 2715 	ld	(0x04, sp), a
      009066                       2716 00104$:
                                   2717 ;	main.c: 485: yoff = 0 - y;
      009066 7B 18            [ 1] 2718 	ld	a, (0x18, sp)
      009068 95               [ 1] 2719 	ld	xh, a
                                   2720 ;	main.c: 484: if (y<0)
      009069 0D 17            [ 1] 2721 	tnz	(0x17, sp)
      00906B 2A 04            [ 1] 2722 	jrpl	00106$
                                   2723 ;	main.c: 485: yoff = 0 - y;
      00906D 9E               [ 1] 2724 	ld	a, xh
      00906E 40               [ 1] 2725 	neg	a
      00906F 6B 05            [ 1] 2726 	ld	(0x05, sp), a
      009071                       2727 00106$:
                                   2728 ;	main.c: 486: if ((y+h) > ST7735_TFTWIDTH)
      009071 7B 03            [ 1] 2729 	ld	a, (0x03, sp)
      009073 90 5F            [ 1] 2730 	clrw	y
      009075 90 97            [ 1] 2731 	ld	yl, a
      009077 72 F9 17         [ 2] 2732 	addw	y, (0x17, sp)
      00907A 90 A3 00 50      [ 2] 2733 	cpw	y, #0x0050
      00907E 2D 08            [ 1] 2734 	jrsle	00108$
                                   2735 ;	main.c: 487: hend = ST7735_TFTWIDTH-y;
      009080 A6 50            [ 1] 2736 	ld	a, #0x50
      009082 89               [ 2] 2737 	pushw	x
      009083 10 01            [ 1] 2738 	sub	a, (#1, sp)
      009085 85               [ 2] 2739 	popw	x
      009086 6B 03            [ 1] 2740 	ld	(0x03, sp), a
      009088                       2741 00108$:
                                   2742 ;	main.c: 488: ST7735_SetAddrWindow(x+xoff,y+yoff,wend,hend);
      009088 7B 05            [ 1] 2743 	ld	a, (0x05, sp)
      00908A 6B 11            [ 1] 2744 	ld	(0x11, sp), a
      00908C 9E               [ 1] 2745 	ld	a, xh
      00908D 1B 11            [ 1] 2746 	add	a, (0x11, sp)
      00908F 95               [ 1] 2747 	ld	xh, a
      009090 7B 06            [ 1] 2748 	ld	a, (0x06, sp)
      009092 6B 12            [ 1] 2749 	ld	(0x12, sp), a
      009094 9F               [ 1] 2750 	ld	a, xl
      009095 1B 12            [ 1] 2751 	add	a, (0x12, sp)
      009097 97               [ 1] 2752 	ld	xl, a
      009098 7B 03            [ 1] 2753 	ld	a, (0x03, sp)
      00909A 88               [ 1] 2754 	push	a
      00909B 7B 05            [ 1] 2755 	ld	a, (0x05, sp)
      00909D 88               [ 1] 2756 	push	a
      00909E 9E               [ 1] 2757 	ld	a, xh
      00909F 88               [ 1] 2758 	push	a
      0090A0 9F               [ 1] 2759 	ld	a, xl
      0090A1 88               [ 1] 2760 	push	a
      0090A2 CD 8A 9C         [ 4] 2761 	call	_ST7735_SetAddrWindow
      0090A5 5B 04            [ 2] 2762 	addw	sp, #4
                                   2763 ;	main.c: 489: for (int j=yoff; j<hend/2; ++j)
      0090A7 7B 05            [ 1] 2764 	ld	a, (0x05, sp)
      0090A9 6B 02            [ 1] 2765 	ld	(0x02, sp), a
      0090AB 0F 01            [ 1] 2766 	clr	(0x01, sp)
      0090AD 16 01            [ 2] 2767 	ldw	y, (0x01, sp)
      0090AF 17 09            [ 2] 2768 	ldw	(0x09, sp), y
      0090B1                       2769 00115$:
      0090B1 7B 03            [ 1] 2770 	ld	a, (0x03, sp)
      0090B3 6B 08            [ 1] 2771 	ld	(0x08, sp), a
      0090B5 0F 07            [ 1] 2772 	clr	(0x07, sp)
      0090B7 4B 02            [ 1] 2773 	push	#0x02
      0090B9 4B 00            [ 1] 2774 	push	#0x00
      0090BB 1E 09            [ 2] 2775 	ldw	x, (0x09, sp)
      0090BD 89               [ 2] 2776 	pushw	x
      0090BE CD 91 FB         [ 4] 2777 	call	__divsint
      0090C1 5B 04            [ 2] 2778 	addw	sp, #4
      0090C3 1F 0F            [ 2] 2779 	ldw	(0x0f, sp), x
      0090C5 1E 09            [ 2] 2780 	ldw	x, (0x09, sp)
      0090C7 13 0F            [ 2] 2781 	cpw	x, (0x0f, sp)
      0090C9 2E 20            [ 1] 2782 	jrsge	00117$
                                   2783 ;	main.c: 490: for (int i=xoff; i<wend; ++i) {
      0090CB 5F               [ 1] 2784 	clrw	x
      0090CC 7B 06            [ 1] 2785 	ld	a, (0x06, sp)
      0090CE 97               [ 1] 2786 	ld	xl, a
      0090CF 1F 0D            [ 2] 2787 	ldw	(0x0d, sp), x
      0090D1                       2788 00112$:
      0090D1 7B 04            [ 1] 2789 	ld	a, (0x04, sp)
      0090D3 6B 0C            [ 1] 2790 	ld	(0x0c, sp), a
      0090D5 0F 0B            [ 1] 2791 	clr	(0x0b, sp)
      0090D7 1E 0D            [ 2] 2792 	ldw	x, (0x0d, sp)
      0090D9 13 0B            [ 2] 2793 	cpw	x, (0x0b, sp)
      0090DB 2E 07            [ 1] 2794 	jrsge	00116$
      0090DD 1E 0D            [ 2] 2795 	ldw	x, (0x0d, sp)
      0090DF 5C               [ 1] 2796 	incw	x
      0090E0 1F 0D            [ 2] 2797 	ldw	(0x0d, sp), x
      0090E2 20 ED            [ 2] 2798 	jra	00112$
      0090E4                       2799 00116$:
                                   2800 ;	main.c: 489: for (int j=yoff; j<hend/2; ++j)
      0090E4 1E 09            [ 2] 2801 	ldw	x, (0x09, sp)
      0090E6 5C               [ 1] 2802 	incw	x
      0090E7 1F 09            [ 2] 2803 	ldw	(0x09, sp), x
      0090E9 20 C6            [ 2] 2804 	jra	00115$
      0090EB                       2805 00117$:
                                   2806 ;	main.c: 496: }
      0090EB 5B 12            [ 2] 2807 	addw	sp, #18
      0090ED 81               [ 4] 2808 	ret
                                   2809 ;	main.c: 499: void ST7735_Fill(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) {
                                   2810 ;	-----------------------------------------
                                   2811 ;	 function ST7735_Fill
                                   2812 ;	-----------------------------------------
      0090EE                       2813 _ST7735_Fill:
      0090EE 52 06            [ 2] 2814 	sub	sp, #6
                                   2815 ;	main.c: 500: ST7735_SetAddrWindow(x, y, w, h);
      0090F0 7B 0C            [ 1] 2816 	ld	a, (0x0c, sp)
      0090F2 88               [ 1] 2817 	push	a
      0090F3 7B 0C            [ 1] 2818 	ld	a, (0x0c, sp)
      0090F5 88               [ 1] 2819 	push	a
      0090F6 7B 0C            [ 1] 2820 	ld	a, (0x0c, sp)
      0090F8 88               [ 1] 2821 	push	a
      0090F9 7B 0C            [ 1] 2822 	ld	a, (0x0c, sp)
      0090FB 88               [ 1] 2823 	push	a
      0090FC CD 8A 9C         [ 4] 2824 	call	_ST7735_SetAddrWindow
      0090FF 5B 04            [ 2] 2825 	addw	sp, #4
                                   2826 ;	main.c: 501: for (int i=0; i< w; ++i)
      009101 5F               [ 1] 2827 	clrw	x
      009102 1F 05            [ 2] 2828 	ldw	(0x05, sp), x
      009104                       2829 00107$:
      009104 7B 0B            [ 1] 2830 	ld	a, (0x0b, sp)
      009106 6B 04            [ 1] 2831 	ld	(0x04, sp), a
      009108 0F 03            [ 1] 2832 	clr	(0x03, sp)
      00910A 1E 05            [ 2] 2833 	ldw	x, (0x05, sp)
      00910C 13 03            [ 2] 2834 	cpw	x, (0x03, sp)
      00910E 2E 20            [ 1] 2835 	jrsge	00109$
                                   2836 ;	main.c: 502: for(int j=0; j< h; ++j)
      009110 5F               [ 1] 2837 	clrw	x
      009111                       2838 00104$:
      009111 7B 0C            [ 1] 2839 	ld	a, (0x0c, sp)
      009113 6B 02            [ 1] 2840 	ld	(0x02, sp), a
      009115 0F 01            [ 1] 2841 	clr	(0x01, sp)
      009117 13 01            [ 2] 2842 	cpw	x, (0x01, sp)
      009119 2E 0E            [ 1] 2843 	jrsge	00108$
                                   2844 ;	main.c: 503: ST7735_Write16(color);
      00911B 89               [ 2] 2845 	pushw	x
      00911C 16 0F            [ 2] 2846 	ldw	y, (0x0f, sp)
      00911E 90 89            [ 2] 2847 	pushw	y
      009120 CD 8A 73         [ 4] 2848 	call	_ST7735_Write16
      009123 5B 02            [ 2] 2849 	addw	sp, #2
      009125 85               [ 2] 2850 	popw	x
                                   2851 ;	main.c: 502: for(int j=0; j< h; ++j)
      009126 5C               [ 1] 2852 	incw	x
      009127 20 E8            [ 2] 2853 	jra	00104$
      009129                       2854 00108$:
                                   2855 ;	main.c: 501: for (int i=0; i< w; ++i)
      009129 1E 05            [ 2] 2856 	ldw	x, (0x05, sp)
      00912B 5C               [ 1] 2857 	incw	x
      00912C 1F 05            [ 2] 2858 	ldw	(0x05, sp), x
      00912E 20 D4            [ 2] 2859 	jra	00107$
      009130                       2860 00109$:
                                   2861 ;	main.c: 504: }
      009130 5B 06            [ 2] 2862 	addw	sp, #6
      009132 81               [ 4] 2863 	ret
                                   2864 	.area CODE
                                   2865 	.area CONST
      008024                       2866 _pallet:
      008024 32 00                 2867 	.dw #0x3200
      008026 12 40                 2868 	.dw #0x1240
      008028 5C 85                 2869 	.dw #0x5c85
      00802A 75 AD                 2870 	.dw #0x75ad
      00802C 1B 11                 2871 	.dw #0x1b11
      00802E 09 80                 2872 	.dw #0x0980
      008030 FC D6                 2873 	.dw #0xfcd6
      008032                       2874 _harry_raw:
      008032 00                    2875 	.db #0x00	; 0
      008033 00                    2876 	.db #0x00	; 0
      008034 22                    2877 	.db #0x22	; 34
      008035 22                    2878 	.db #0x22	; 34
      008036 22                    2879 	.db #0x22	; 34
      008037 22                    2880 	.db #0x22	; 34
      008038 22                    2881 	.db #0x22	; 34
      008039 22                    2882 	.db #0x22	; 34
      00803A 66                    2883 	.db #0x66	; 102	'f'
      00803B 66                    2884 	.db #0x66	; 102	'f'
      00803C 22                    2885 	.db #0x22	; 34
      00803D 66                    2886 	.db #0x66	; 102	'f'
      00803E 22                    2887 	.db #0x22	; 34
      00803F 22                    2888 	.db #0x22	; 34
      008040 22                    2889 	.db #0x22	; 34
      008041 22                    2890 	.db #0x22	; 34
      008042 66                    2891 	.db #0x66	; 102	'f'
      008043 66                    2892 	.db #0x66	; 102	'f'
      008044 22                    2893 	.db #0x22	; 34
      008045 66                    2894 	.db #0x66	; 102	'f'
      008046 22                    2895 	.db #0x22	; 34
      008047 22                    2896 	.db #0x22	; 34
      008048 22                    2897 	.db #0x22	; 34
      008049 22                    2898 	.db #0x22	; 34
      00804A 66                    2899 	.db #0x66	; 102	'f'
      00804B 22                    2900 	.db #0x22	; 34
      00804C 22                    2901 	.db #0x22	; 34
      00804D 66                    2902 	.db #0x66	; 102	'f'
      00804E 22                    2903 	.db #0x22	; 34
      00804F 22                    2904 	.db #0x22	; 34
      008050 22                    2905 	.db #0x22	; 34
      008051 22                    2906 	.db #0x22	; 34
      008052 33                    2907 	.db #0x33	; 51	'3'
      008053 33                    2908 	.db #0x33	; 51	'3'
      008054 22                    2909 	.db #0x22	; 34
      008055 33                    2910 	.db #0x33	; 51	'3'
      008056 22                    2911 	.db #0x22	; 34
      008057 22                    2912 	.db #0x22	; 34
      008058 22                    2913 	.db #0x22	; 34
      008059 22                    2914 	.db #0x22	; 34
      00805A 33                    2915 	.db #0x33	; 51	'3'
      00805B 33                    2916 	.db #0x33	; 51	'3'
      00805C 33                    2917 	.db #0x33	; 51	'3'
      00805D 33                    2918 	.db #0x33	; 51	'3'
      00805E 22                    2919 	.db #0x22	; 34
      00805F 22                    2920 	.db #0x22	; 34
      008060 22                    2921 	.db #0x22	; 34
      008061 22                    2922 	.db #0x22	; 34
      008062 33                    2923 	.db #0x33	; 51	'3'
      008063 33                    2924 	.db #0x33	; 51	'3'
      008064 22                    2925 	.db #0x22	; 34
      008065 22                    2926 	.db #0x22	; 34
      008066 22                    2927 	.db #0x22	; 34
      008067 22                    2928 	.db #0x22	; 34
      008068 22                    2929 	.db #0x22	; 34
      008069 22                    2930 	.db #0x22	; 34
      00806A 33                    2931 	.db #0x33	; 51	'3'
      00806B 33                    2932 	.db #0x33	; 51	'3'
      00806C 22                    2933 	.db #0x22	; 34
      00806D 22                    2934 	.db #0x22	; 34
      00806E 22                    2935 	.db #0x22	; 34
      00806F 22                    2936 	.db #0x22	; 34
      008070 22                    2937 	.db #0x22	; 34
      008071 22                    2938 	.db #0x22	; 34
      008072 33                    2939 	.db #0x33	; 51	'3'
      008073 33                    2940 	.db #0x33	; 51	'3'
      008074 22                    2941 	.db #0x22	; 34
      008075 22                    2942 	.db #0x22	; 34
      008076 22                    2943 	.db #0x22	; 34
      008077 22                    2944 	.db #0x22	; 34
      008078 22                    2945 	.db #0x22	; 34
      008079 22                    2946 	.db #0x22	; 34
      00807A 33                    2947 	.db #0x33	; 51	'3'
      00807B 33                    2948 	.db #0x33	; 51	'3'
      00807C 22                    2949 	.db #0x22	; 34
      00807D 22                    2950 	.db #0x22	; 34
      00807E 22                    2951 	.db #0x22	; 34
      00807F 22                    2952 	.db #0x22	; 34
      008080 22                    2953 	.db #0x22	; 34
      008081 22                    2954 	.db #0x22	; 34
      008082 33                    2955 	.db #0x33	; 51	'3'
      008083 33                    2956 	.db #0x33	; 51	'3'
      008084 22                    2957 	.db #0x22	; 34
      008085 22                    2958 	.db #0x22	; 34
      008086 22                    2959 	.db #0x22	; 34
      008087 22                    2960 	.db #0x22	; 34
      008088 22                    2961 	.db #0x22	; 34
      008089 22                    2962 	.db #0x22	; 34
      00808A 11                    2963 	.db #0x11	; 17
      00808B 11                    2964 	.db #0x11	; 17
      00808C 22                    2965 	.db #0x22	; 34
      00808D 11                    2966 	.db #0x11	; 17
      00808E 11                    2967 	.db #0x11	; 17
      00808F 11                    2968 	.db #0x11	; 17
      008090 22                    2969 	.db #0x22	; 34
      008091 22                    2970 	.db #0x22	; 34
      008092 11                    2971 	.db #0x11	; 17
      008093 11                    2972 	.db #0x11	; 17
      008094 11                    2973 	.db #0x11	; 17
      008095 11                    2974 	.db #0x11	; 17
      008096 22                    2975 	.db #0x22	; 34
      008097 11                    2976 	.db #0x11	; 17
      008098 11                    2977 	.db #0x11	; 17
      008099 22                    2978 	.db #0x22	; 34
      00809A 11                    2979 	.db #0x11	; 17
      00809B 11                    2980 	.db #0x11	; 17
      00809C 11                    2981 	.db #0x11	; 17
      00809D 11                    2982 	.db #0x11	; 17
      00809E 22                    2983 	.db #0x22	; 34
      00809F 22                    2984 	.db #0x22	; 34
      0080A0 11                    2985 	.db #0x11	; 17
      0080A1 22                    2986 	.db #0x22	; 34
      0080A2 22                    2987 	.db #0x22	; 34
      0080A3 11                    2988 	.db #0x11	; 17
      0080A4 11                    2989 	.db #0x11	; 17
      0080A5 22                    2990 	.db #0x22	; 34
      0080A6 22                    2991 	.db #0x22	; 34
      0080A7 22                    2992 	.db #0x22	; 34
      0080A8 11                    2993 	.db #0x11	; 17
      0080A9 11                    2994 	.db #0x11	; 17
      0080AA                       2995 _gator1_raw:
      0080AA 22                    2996 	.db #0x22	; 34
      0080AB 22                    2997 	.db #0x22	; 34
      0080AC 22                    2998 	.db #0x22	; 34
      0080AD 22                    2999 	.db #0x22	; 34
      0080AE 22                    3000 	.db #0x22	; 34
      0080AF 22                    3001 	.db #0x22	; 34
      0080B0 22                    3002 	.db #0x22	; 34
      0080B1 22                    3003 	.db #0x22	; 34
      0080B2 22                    3004 	.db #0x22	; 34
      0080B3 22                    3005 	.db #0x22	; 34
      0080B4 22                    3006 	.db #0x22	; 34
      0080B5 22                    3007 	.db #0x22	; 34
      0080B6 22                    3008 	.db #0x22	; 34
      0080B7 22                    3009 	.db #0x22	; 34
      0080B8 22                    3010 	.db #0x22	; 34
      0080B9 22                    3011 	.db #0x22	; 34
      0080BA 44                    3012 	.db #0x44	; 68	'D'
      0080BB 44                    3013 	.db #0x44	; 68	'D'
      0080BC 44                    3014 	.db #0x44	; 68	'D'
      0080BD 44                    3015 	.db #0x44	; 68	'D'
      0080BE 44                    3016 	.db #0x44	; 68	'D'
      0080BF 55                    3017 	.db #0x55	; 85	'U'
      0080C0 44                    3018 	.db #0x44	; 68	'D'
      0080C1 44                    3019 	.db #0x44	; 68	'D'
      0080C2 44                    3020 	.db #0x44	; 68	'D'
      0080C3 44                    3021 	.db #0x44	; 68	'D'
      0080C4 44                    3022 	.db #0x44	; 68	'D'
      0080C5 44                    3023 	.db #0x44	; 68	'D'
      0080C6 44                    3024 	.db #0x44	; 68	'D'
      0080C7 55                    3025 	.db #0x55	; 85	'U'
      0080C8 55                    3026 	.db #0x55	; 85	'U'
      0080C9 44                    3027 	.db #0x44	; 68	'D'
      0080CA 55                    3028 	.db #0x55	; 85	'U'
      0080CB 55                    3029 	.db #0x55	; 85	'U'
      0080CC 55                    3030 	.db #0x55	; 85	'U'
      0080CD 55                    3031 	.db #0x55	; 85	'U'
      0080CE 55                    3032 	.db #0x55	; 85	'U'
      0080CF 55                    3033 	.db #0x55	; 85	'U'
      0080D0 55                    3034 	.db #0x55	; 85	'U'
      0080D1 55                    3035 	.db #0x55	; 85	'U'
      0080D2 44                    3036 	.db #0x44	; 68	'D'
      0080D3 55                    3037 	.db #0x55	; 85	'U'
      0080D4 44                    3038 	.db #0x44	; 68	'D'
      0080D5 55                    3039 	.db #0x55	; 85	'U'
      0080D6 44                    3040 	.db #0x44	; 68	'D'
      0080D7 55                    3041 	.db #0x55	; 85	'U'
      0080D8 44                    3042 	.db #0x44	; 68	'D'
      0080D9 55                    3043 	.db #0x55	; 85	'U'
      0080DA 55                    3044 	.db #0x55	; 85	'U'
      0080DB 44                    3045 	.db #0x44	; 68	'D'
      0080DC 55                    3046 	.db #0x55	; 85	'U'
      0080DD 44                    3047 	.db #0x44	; 68	'D'
      0080DE 55                    3048 	.db #0x55	; 85	'U'
      0080DF 44                    3049 	.db #0x44	; 68	'D'
      0080E0 55                    3050 	.db #0x55	; 85	'U'
      0080E1 55                    3051 	.db #0x55	; 85	'U'
      0080E2 55                    3052 	.db #0x55	; 85	'U'
      0080E3 55                    3053 	.db #0x55	; 85	'U'
      0080E4 55                    3054 	.db #0x55	; 85	'U'
      0080E5 55                    3055 	.db #0x55	; 85	'U'
      0080E6 55                    3056 	.db #0x55	; 85	'U'
      0080E7 55                    3057 	.db #0x55	; 85	'U'
      0080E8 55                    3058 	.db #0x55	; 85	'U'
      0080E9 55                    3059 	.db #0x55	; 85	'U'
      0080EA                       3060 _gator2_raw:
      0080EA 55                    3061 	.db #0x55	; 85	'U'
      0080EB 22                    3062 	.db #0x22	; 34
      0080EC 22                    3063 	.db #0x22	; 34
      0080ED 22                    3064 	.db #0x22	; 34
      0080EE 22                    3065 	.db #0x22	; 34
      0080EF 22                    3066 	.db #0x22	; 34
      0080F0 22                    3067 	.db #0x22	; 34
      0080F1 22                    3068 	.db #0x22	; 34
      0080F2 55                    3069 	.db #0x55	; 85	'U'
      0080F3 55                    3070 	.db #0x55	; 85	'U'
      0080F4 55                    3071 	.db #0x55	; 85	'U'
      0080F5 22                    3072 	.db #0x22	; 34
      0080F6 22                    3073 	.db #0x22	; 34
      0080F7 22                    3074 	.db #0x22	; 34
      0080F8 22                    3075 	.db #0x22	; 34
      0080F9 22                    3076 	.db #0x22	; 34
      0080FA 55                    3077 	.db #0x55	; 85	'U'
      0080FB 44                    3078 	.db #0x44	; 68	'D'
      0080FC 55                    3079 	.db #0x55	; 85	'U'
      0080FD 55                    3080 	.db #0x55	; 85	'U'
      0080FE 55                    3081 	.db #0x55	; 85	'U'
      0080FF 22                    3082 	.db #0x22	; 34
      008100 55                    3083 	.db #0x55	; 85	'U'
      008101 22                    3084 	.db #0x22	; 34
      008102 44                    3085 	.db #0x44	; 68	'D'
      008103 44                    3086 	.db #0x44	; 68	'D'
      008104 55                    3087 	.db #0x55	; 85	'U'
      008105 44                    3088 	.db #0x44	; 68	'D'
      008106 55                    3089 	.db #0x55	; 85	'U'
      008107 55                    3090 	.db #0x55	; 85	'U'
      008108 55                    3091 	.db #0x55	; 85	'U'
      008109 44                    3092 	.db #0x44	; 68	'D'
      00810A 44                    3093 	.db #0x44	; 68	'D'
      00810B 44                    3094 	.db #0x44	; 68	'D'
      00810C 44                    3095 	.db #0x44	; 68	'D'
      00810D 44                    3096 	.db #0x44	; 68	'D'
      00810E 55                    3097 	.db #0x55	; 85	'U'
      00810F 44                    3098 	.db #0x44	; 68	'D'
      008110 55                    3099 	.db #0x55	; 85	'U'
      008111 55                    3100 	.db #0x55	; 85	'U'
      008112 44                    3101 	.db #0x44	; 68	'D'
      008113 44                    3102 	.db #0x44	; 68	'D'
      008114 44                    3103 	.db #0x44	; 68	'D'
      008115 44                    3104 	.db #0x44	; 68	'D'
      008116 44                    3105 	.db #0x44	; 68	'D'
      008117 44                    3106 	.db #0x44	; 68	'D'
      008118 55                    3107 	.db #0x55	; 85	'U'
      008119 55                    3108 	.db #0x55	; 85	'U'
      00811A 55                    3109 	.db #0x55	; 85	'U'
      00811B 44                    3110 	.db #0x44	; 68	'D'
      00811C 55                    3111 	.db #0x55	; 85	'U'
      00811D 44                    3112 	.db #0x44	; 68	'D'
      00811E 55                    3113 	.db #0x55	; 85	'U'
      00811F 44                    3114 	.db #0x44	; 68	'D'
      008120 55                    3115 	.db #0x55	; 85	'U'
      008121 55                    3116 	.db #0x55	; 85	'U'
      008122 55                    3117 	.db #0x55	; 85	'U'
      008123 55                    3118 	.db #0x55	; 85	'U'
      008124 55                    3119 	.db #0x55	; 85	'U'
      008125 55                    3120 	.db #0x55	; 85	'U'
      008126 55                    3121 	.db #0x55	; 85	'U'
      008127 55                    3122 	.db #0x55	; 85	'U'
      008128 55                    3123 	.db #0x55	; 85	'U'
      008129 55                    3124 	.db #0x55	; 85	'U'
      00812A                       3125 _pool:
      00812A 00                    3126 	.db #0x00	; 0
      00812B 00                    3127 	.db #0x00	; 0
      00812C 00                    3128 	.db #0x00	; 0
      00812D 10                    3129 	.db #0x10	; 16
      00812E 40                    3130 	.db #0x40	; 64
      00812F 60                    3131 	.db #0x60	; 96
      008130 70                    3132 	.db #0x70	; 112	'p'
      008131 80                    3133 	.db #0x80	; 128
      008132 80                    3134 	.db #0x80	; 128
      008133 70                    3135 	.db #0x70	; 112	'p'
      008134 60                    3136 	.db #0x60	; 96
      008135 40                    3137 	.db #0x40	; 64
      008136 10                    3138 	.db #0x10	; 16
      008137 00                    3139 	.db #0x00	; 0
      008138 00                    3140 	.db #0x00	; 0
      008139 00                    3141 	.db #0x00	; 0
                                   3142 	.area INITIALIZER
                                   3143 	.area CABS (ABS)
