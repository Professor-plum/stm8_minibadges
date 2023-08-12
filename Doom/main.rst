                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ISO C Compiler 
                                      3 ; Version 4.3.0 #14184 (Mac OS X ppc)
                                      4 ;--------------------------------------------------------
                                      5 	.module main
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _doom8_raw
                                     12 	.globl _doom7_raw
                                     13 	.globl _doom6_raw
                                     14 	.globl _doom5_raw
                                     15 	.globl _doom4_raw
                                     16 	.globl _doom3_raw
                                     17 	.globl _doom2_raw
                                     18 	.globl _doom1_raw
                                     19 	.globl _pallet
                                     20 	.globl _ST7735_Write
                                     21 	.globl _SPI_write
                                     22 	.globl _SPI_init
                                     23 	.globl _main
                                     24 	.globl _drawFace
                                     25 	.globl _init_clock
                                     26 	.globl _clock
                                     27 	.globl _rand
                                     28 	.globl _ST7735_Write16
                                     29 	.globl _ST7735_SetAddrWindow
                                     30 	.globl _ST7735_Init
                                     31 	.globl _ST7735_Clear
                                     32 ;--------------------------------------------------------
                                     33 ; ram data
                                     34 ;--------------------------------------------------------
                                     35 	.area DATA
                                     36 ;--------------------------------------------------------
                                     37 ; ram data
                                     38 ;--------------------------------------------------------
                                     39 	.area INITIALIZED
                                     40 ;--------------------------------------------------------
                                     41 ; Stack segment in internal ram
                                     42 ;--------------------------------------------------------
                                     43 	.area SSEG
      000005                         44 __start__stack:
      000005                         45 	.ds	1
                                     46 
                                     47 ;--------------------------------------------------------
                                     48 ; absolute external ram data
                                     49 ;--------------------------------------------------------
                                     50 	.area DABS (ABS)
                                     51 
                                     52 ; default segment ordering for linker
                                     53 	.area HOME
                                     54 	.area GSINIT
                                     55 	.area GSFINAL
                                     56 	.area CONST
                                     57 	.area INITIALIZER
                                     58 	.area CODE
                                     59 
                                     60 ;--------------------------------------------------------
                                     61 ; interrupt vector
                                     62 ;--------------------------------------------------------
                                     63 	.area HOME
      008000                         64 __interrupt_vect:
      008000 82 00 80 07             65 	int s_GSINIT ; reset
                                     66 ;--------------------------------------------------------
                                     67 ; global & static initialisations
                                     68 ;--------------------------------------------------------
                                     69 	.area HOME
                                     70 	.area GSINIT
                                     71 	.area GSFINAL
                                     72 	.area GSINIT
      008007 CD 9F 90         [ 4]   73 	call	___sdcc_external_startup
      00800A 4D               [ 1]   74 	tnz	a
      00800B 27 03            [ 1]   75 	jreq	__sdcc_init_data
      00800D CC 80 04         [ 2]   76 	jp	__sdcc_program_startup
      008010                         77 __sdcc_init_data:
                                     78 ; stm8_genXINIT() start
      008010 AE 00 00         [ 2]   79 	ldw x, #l_DATA
      008013 27 07            [ 1]   80 	jreq	00002$
      008015                         81 00001$:
      008015 72 4F 00 00      [ 1]   82 	clr (s_DATA - 1, x)
      008019 5A               [ 2]   83 	decw x
      00801A 26 F9            [ 1]   84 	jrne	00001$
      00801C                         85 00002$:
      00801C AE 00 04         [ 2]   86 	ldw	x, #l_INITIALIZER
      00801F 27 09            [ 1]   87 	jreq	00004$
      008021                         88 00003$:
      008021 D6 99 20         [ 1]   89 	ld	a, (s_INITIALIZER - 1, x)
      008024 D7 00 00         [ 1]   90 	ld	(s_INITIALIZED - 1, x), a
      008027 5A               [ 2]   91 	decw	x
      008028 26 F7            [ 1]   92 	jrne	00003$
      00802A                         93 00004$:
                                     94 ; stm8_genXINIT() end
                                     95 	.area GSFINAL
      00802A CC 80 04         [ 2]   96 	jp	__sdcc_program_startup
                                     97 ;--------------------------------------------------------
                                     98 ; Home
                                     99 ;--------------------------------------------------------
                                    100 	.area HOME
                                    101 	.area HOME
      008004                        102 __sdcc_program_startup:
      008004 CC 99 E3         [ 2]  103 	jp	_main
                                    104 ;	return from main will return to caller
                                    105 ;--------------------------------------------------------
                                    106 ; code
                                    107 ;--------------------------------------------------------
                                    108 	.area CODE
                                    109 ;	main.c: 25: static inline void delay_ms(uint16_t ms) {
                                    110 ;	-----------------------------------------
                                    111 ;	 function delay_ms
                                    112 ;	-----------------------------------------
      009925                        113 _delay_ms:
      009925 52 0A            [ 2]  114 	sub	sp, #10
      009927 1F 05            [ 2]  115 	ldw	(0x05, sp), x
                                    116 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009929 5F               [ 1]  117 	clrw	x
      00992A 1F 09            [ 2]  118 	ldw	(0x09, sp), x
      00992C 1F 07            [ 2]  119 	ldw	(0x07, sp), x
      00992E                        120 00103$:
      00992E 1E 05            [ 2]  121 	ldw	x, (0x05, sp)
      009930 89               [ 2]  122 	pushw	x
      009931 AE 07 D0         [ 2]  123 	ldw	x, #0x07d0
      009934 CD 9E A5         [ 4]  124 	call	___muluint2ulong
      009937 5B 02            [ 2]  125 	addw	sp, #2
      009939 1F 03            [ 2]  126 	ldw	(0x03, sp), x
      00993B 17 01            [ 2]  127 	ldw	(0x01, sp), y
      00993D 1E 09            [ 2]  128 	ldw	x, (0x09, sp)
      00993F 13 03            [ 2]  129 	cpw	x, (0x03, sp)
      009941 7B 08            [ 1]  130 	ld	a, (0x08, sp)
      009943 12 02            [ 1]  131 	sbc	a, (0x02, sp)
      009945 7B 07            [ 1]  132 	ld	a, (0x07, sp)
      009947 12 01            [ 1]  133 	sbc	a, (0x01, sp)
      009949 24 0F            [ 1]  134 	jrnc	00105$
                                    135 ;	main.c: 28: __asm__("nop");
      00994B 9D               [ 1]  136 	nop
                                    137 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      00994C 1E 09            [ 2]  138 	ldw	x, (0x09, sp)
      00994E 5C               [ 1]  139 	incw	x
      00994F 1F 09            [ 2]  140 	ldw	(0x09, sp), x
      009951 26 DB            [ 1]  141 	jrne	00103$
      009953 1E 07            [ 2]  142 	ldw	x, (0x07, sp)
      009955 5C               [ 1]  143 	incw	x
      009956 1F 07            [ 2]  144 	ldw	(0x07, sp), x
      009958 20 D4            [ 2]  145 	jra	00103$
      00995A                        146 00105$:
                                    147 ;	main.c: 29: }
      00995A 5B 0A            [ 2]  148 	addw	sp, #10
      00995C 81               [ 4]  149 	ret
                                    150 ;	main.c: 31: unsigned int clock(void)
                                    151 ;	-----------------------------------------
                                    152 ;	 function clock
                                    153 ;	-----------------------------------------
      00995D                        154 _clock:
      00995D 52 04            [ 2]  155 	sub	sp, #4
                                    156 ;	main.c: 33: unsigned char h = TIM1_CNTRH;
      00995F C6 52 5E         [ 1]  157 	ld	a, 0x525e
      009962 95               [ 1]  158 	ld	xh, a
                                    159 ;	main.c: 34: unsigned char l = TIM1_CNTRL;
      009963 C6 52 5F         [ 1]  160 	ld	a, 0x525f
                                    161 ;	main.c: 35: return((unsigned int)(h) << 8 | l);
      009966 0F 02            [ 1]  162 	clr	(0x02, sp)
      009968 0F 03            [ 1]  163 	clr	(0x03, sp)
      00996A 1A 02            [ 1]  164 	or	a, (0x02, sp)
      00996C 02               [ 1]  165 	rlwa	x
      00996D 1A 03            [ 1]  166 	or	a, (0x03, sp)
      00996F 95               [ 1]  167 	ld	xh, a
                                    168 ;	main.c: 36: }
      009970 5B 04            [ 2]  169 	addw	sp, #4
      009972 81               [ 4]  170 	ret
                                    171 ;	main.c: 38: void init_clock(void) {
                                    172 ;	-----------------------------------------
                                    173 ;	 function init_clock
                                    174 ;	-----------------------------------------
      009973                        175 _init_clock:
                                    176 ;	main.c: 39: CLK_CKDIVR = 0;//0x18; // Set the frequency to 2 MHz
      009973 35 00 50 C6      [ 1]  177 	mov	0x50c6+0, #0x00
                                    178 ;	main.c: 40: CLK_PCKENR1 = 0x02; //SPI
      009977 35 02 50 C7      [ 1]  179 	mov	0x50c7+0, #0x02
                                    180 ;	main.c: 41: CLK_PCKENR2 = 0x73; //off
      00997B 35 73 50 CA      [ 1]  181 	mov	0x50ca+0, #0x73
                                    182 ;	main.c: 43: }
      00997F 81               [ 4]  183 	ret
                                    184 ;	main.c: 45: void drawFace(const uint8_t *face) { //face is a pointer to a 26x30 array of index pixels
                                    185 ;	-----------------------------------------
                                    186 ;	 function drawFace
                                    187 ;	-----------------------------------------
      009980                        188 _drawFace:
      009980 52 08            [ 2]  189 	sub	sp, #8
      009982 1F 03            [ 2]  190 	ldw	(0x03, sp), x
                                    191 ;	main.c: 47: ST7735_SetAddrWindow(41, 2, 78, 80);
      009984 4B 50            [ 1]  192 	push	#0x50
      009986 4B 4E            [ 1]  193 	push	#0x4e
      009988 4B 02            [ 1]  194 	push	#0x02
      00998A A6 29            [ 1]  195 	ld	a, #0x29
      00998C CD 9A DE         [ 4]  196 	call	_ST7735_SetAddrWindow
                                    197 ;	main.c: 49: for (int y=0; y<80; ++y) {
      00998F 5F               [ 1]  198 	clrw	x
      009990 1F 05            [ 2]  199 	ldw	(0x05, sp), x
      009992                        200 00107$:
      009992 1E 05            [ 2]  201 	ldw	x, (0x05, sp)
      009994 A3 00 50         [ 2]  202 	cpw	x, #0x0050
      009997 2E 47            [ 1]  203 	jrsge	00109$
                                    204 ;	main.c: 51: for (int i=0; i<26; ++i) {
      009999 4B 03            [ 1]  205 	push	#0x03
      00999B 4B 00            [ 1]  206 	push	#0x00
      00999D 1E 07            [ 2]  207 	ldw	x, (0x07, sp)
      00999F CD 9F AA         [ 4]  208 	call	__divsint
      0099A2 5C               [ 1]  209 	incw	x
      0099A3 89               [ 2]  210 	pushw	x
      0099A4 AE 00 1A         [ 2]  211 	ldw	x, #0x001a
      0099A7 CD 9F 73         [ 4]  212 	call	__mulint
      0099AA 1F 01            [ 2]  213 	ldw	(0x01, sp), x
      0099AC 5F               [ 1]  214 	clrw	x
      0099AD 1F 07            [ 2]  215 	ldw	(0x07, sp), x
      0099AF                        216 00104$:
      0099AF 1E 07            [ 2]  217 	ldw	x, (0x07, sp)
      0099B1 A3 00 1A         [ 2]  218 	cpw	x, #0x001a
      0099B4 2E 23            [ 1]  219 	jrsge	00108$
                                    220 ;	main.c: 52: int idx = face[(1+(y/3))*26+i];
      0099B6 1E 01            [ 2]  221 	ldw	x, (0x01, sp)
      0099B8 72 FB 07         [ 2]  222 	addw	x, (0x07, sp)
      0099BB 72 FB 03         [ 2]  223 	addw	x, (0x03, sp)
      0099BE F6               [ 1]  224 	ld	a, (x)
      0099BF 5F               [ 1]  225 	clrw	x
                                    226 ;	main.c: 53: uint16_t c = pallet[idx];
      0099C0 97               [ 1]  227 	ld	xl, a
      0099C1 58               [ 2]  228 	sllw	x
      0099C2 DE 80 2D         [ 2]  229 	ldw	x, (_pallet+0, x)
                                    230 ;	main.c: 54: ST7735_Write16(c);
      0099C5 89               [ 2]  231 	pushw	x
      0099C6 CD 9A C0         [ 4]  232 	call	_ST7735_Write16
      0099C9 85               [ 2]  233 	popw	x
                                    234 ;	main.c: 55: ST7735_Write16(c);
      0099CA 89               [ 2]  235 	pushw	x
      0099CB CD 9A C0         [ 4]  236 	call	_ST7735_Write16
      0099CE 85               [ 2]  237 	popw	x
                                    238 ;	main.c: 56: ST7735_Write16(c);
      0099CF CD 9A C0         [ 4]  239 	call	_ST7735_Write16
                                    240 ;	main.c: 51: for (int i=0; i<26; ++i) {
      0099D2 1E 07            [ 2]  241 	ldw	x, (0x07, sp)
      0099D4 5C               [ 1]  242 	incw	x
      0099D5 1F 07            [ 2]  243 	ldw	(0x07, sp), x
      0099D7 20 D6            [ 2]  244 	jra	00104$
      0099D9                        245 00108$:
                                    246 ;	main.c: 49: for (int y=0; y<80; ++y) {
      0099D9 1E 05            [ 2]  247 	ldw	x, (0x05, sp)
      0099DB 5C               [ 1]  248 	incw	x
      0099DC 1F 05            [ 2]  249 	ldw	(0x05, sp), x
      0099DE 20 B2            [ 2]  250 	jra	00107$
      0099E0                        251 00109$:
                                    252 ;	main.c: 60: }
      0099E0 5B 08            [ 2]  253 	addw	sp, #8
      0099E2 81               [ 4]  254 	ret
                                    255 ;	main.c: 62: void main(void)
                                    256 ;	-----------------------------------------
                                    257 ;	 function main
                                    258 ;	-----------------------------------------
      0099E3                        259 _main:
      0099E3 52 10            [ 2]  260 	sub	sp, #16
                                    261 ;	main.c: 64: const uint8_t* frames[7] = {doom1_raw, doom3_raw, doom4_raw, doom5_raw, doom6_raw, doom7_raw, doom8_raw};
      0099E5 AE 80 AF         [ 2]  262 	ldw	x, #(_doom1_raw+0)
      0099E8 1F 01            [ 2]  263 	ldw	(0x01, sp), x
      0099EA AE 86 C5         [ 2]  264 	ldw	x, #(_doom3_raw+0)
      0099ED 1F 03            [ 2]  265 	ldw	(0x03, sp), x
      0099EF AE 89 D0         [ 2]  266 	ldw	x, #(_doom4_raw+0)
      0099F2 1F 05            [ 2]  267 	ldw	(0x05, sp), x
      0099F4 AE 8C DB         [ 2]  268 	ldw	x, #(_doom5_raw+0)
      0099F7 1F 07            [ 2]  269 	ldw	(0x07, sp), x
      0099F9 AE 90 00         [ 2]  270 	ldw	x, #(_doom6_raw+0)
      0099FC 1F 09            [ 2]  271 	ldw	(0x09, sp), x
      0099FE AE 93 0B         [ 2]  272 	ldw	x, #(_doom7_raw+0)
      009A01 1F 0B            [ 2]  273 	ldw	(0x0b, sp), x
      009A03 AE 96 16         [ 2]  274 	ldw	x, #(_doom8_raw+0)
      009A06 1F 0D            [ 2]  275 	ldw	(0x0d, sp), x
                                    276 ;	main.c: 66: init_clock();
      009A08 CD 99 73         [ 4]  277 	call	_init_clock
                                    278 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009A0B 90 5F            [ 1]  279 	clrw	y
      009A0D 5F               [ 1]  280 	clrw	x
      009A0E                        281 00111$:
      009A0E 90 A3 8D 80      [ 2]  282 	cpw	y, #0x8d80
      009A12 9F               [ 1]  283 	ld	a, xl
      009A13 A2 5B            [ 1]  284 	sbc	a, #0x5b
      009A15 9E               [ 1]  285 	ld	a, xh
      009A16 A2 00            [ 1]  286 	sbc	a, #0x00
      009A18 24 08            [ 1]  287 	jrnc	00105$
                                    288 ;	main.c: 28: __asm__("nop");
      009A1A 9D               [ 1]  289 	nop
                                    290 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009A1B 90 5C            [ 1]  291 	incw	y
      009A1D 26 EF            [ 1]  292 	jrne	00111$
      009A1F 5C               [ 1]  293 	incw	x
      009A20 20 EC            [ 2]  294 	jra	00111$
                                    295 ;	main.c: 67: delay_ms(3000);
      009A22                        296 00105$:
                                    297 ;	main.c: 68: ST7735_Init();
      009A22 CD 9B 4C         [ 4]  298 	call	_ST7735_Init
                                    299 ;	main.c: 70: __asm__ ("rim"); //enable interrupts
      009A25 9A               [ 1]  300 	rim
                                    301 ;	main.c: 73: ST7735_Clear(RGB(0,0,0));
      009A26 5F               [ 1]  302 	clrw	x
      009A27 CD 9E 73         [ 4]  303 	call	_ST7735_Clear
                                    304 ;	main.c: 75: while(1) {
      009A2A                        305 00102$:
                                    306 ;	main.c: 77: drawFace(doom2_raw);
      009A2A AE 83 BA         [ 2]  307 	ldw	x, #(_doom2_raw+0)
      009A2D CD 99 80         [ 4]  308 	call	_drawFace
                                    309 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009A30 90 5F            [ 1]  310 	clrw	y
      009A32 5F               [ 1]  311 	clrw	x
      009A33                        312 00114$:
      009A33 90 A3 12 00      [ 2]  313 	cpw	y, #0x1200
      009A37 9F               [ 1]  314 	ld	a, xl
      009A38 A2 7A            [ 1]  315 	sbc	a, #0x7a
      009A3A 9E               [ 1]  316 	ld	a, xh
      009A3B A2 00            [ 1]  317 	sbc	a, #0x00
      009A3D 24 08            [ 1]  318 	jrnc	00107$
                                    319 ;	main.c: 28: __asm__("nop");
      009A3F 9D               [ 1]  320 	nop
                                    321 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009A40 90 5C            [ 1]  322 	incw	y
      009A42 26 EF            [ 1]  323 	jrne	00114$
      009A44 5C               [ 1]  324 	incw	x
      009A45 20 EC            [ 2]  325 	jra	00114$
                                    326 ;	main.c: 78: delay_ms(4000);
      009A47                        327 00107$:
                                    328 ;	main.c: 79: drawFace(frames[rand()%7]);
      009A47 CD 9E FC         [ 4]  329 	call	_rand
      009A4A 4B 07            [ 1]  330 	push	#0x07
      009A4C 4B 00            [ 1]  331 	push	#0x00
      009A4E CD 9F 92         [ 4]  332 	call	__modsint
      009A51 58               [ 2]  333 	sllw	x
      009A52 1F 0F            [ 2]  334 	ldw	(0x0f, sp), x
      009A54 96               [ 1]  335 	ldw	x, sp
      009A55 5C               [ 1]  336 	incw	x
      009A56 72 FB 0F         [ 2]  337 	addw	x, (0x0f, sp)
      009A59 FE               [ 2]  338 	ldw	x, (x)
      009A5A CD 99 80         [ 4]  339 	call	_drawFace
                                    340 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009A5D 90 5F            [ 1]  341 	clrw	y
      009A5F 5F               [ 1]  342 	clrw	x
      009A60                        343 00117$:
      009A60 90 A3 84 80      [ 2]  344 	cpw	y, #0x8480
      009A64 9F               [ 1]  345 	ld	a, xl
      009A65 A2 1E            [ 1]  346 	sbc	a, #0x1e
      009A67 9E               [ 1]  347 	ld	a, xh
      009A68 A2 00            [ 1]  348 	sbc	a, #0x00
      009A6A 24 BE            [ 1]  349 	jrnc	00102$
                                    350 ;	main.c: 28: __asm__("nop");
      009A6C 9D               [ 1]  351 	nop
                                    352 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009A6D 90 5C            [ 1]  353 	incw	y
      009A6F 26 EF            [ 1]  354 	jrne	00117$
      009A71 5C               [ 1]  355 	incw	x
      009A72 20 EC            [ 2]  356 	jra	00117$
                                    357 ;	main.c: 80: delay_ms(1000);
                                    358 ;	main.c: 83: }
      009A74 5B 10            [ 2]  359 	addw	sp, #16
      009A76 81               [ 4]  360 	ret
                                    361 ;	main.c: 91: void SPI_init(void) {
                                    362 ;	-----------------------------------------
                                    363 ;	 function SPI_init
                                    364 ;	-----------------------------------------
      009A77                        365 _SPI_init:
                                    366 ;	main.c: 93: PC_DDR |= (1<<5) | (1<<6); // clock and MOSI
      009A77 C6 50 0C         [ 1]  367 	ld	a, 0x500c
      009A7A AA 60            [ 1]  368 	or	a, #0x60
      009A7C C7 50 0C         [ 1]  369 	ld	0x500c, a
                                    370 ;	main.c: 94: PC_CR1 |= (1<<5) | (1<<6) | (1<<7);
      009A7F C6 50 0D         [ 1]  371 	ld	a, 0x500d
      009A82 AA E0            [ 1]  372 	or	a, #0xe0
      009A84 C7 50 0D         [ 1]  373 	ld	0x500d, a
                                    374 ;	main.c: 98: SPI_CR2 = SPI_CR2_SSM | SPI_CR2_SSI;
      009A87 35 03 52 01      [ 1]  375 	mov	0x5201+0, #0x03
                                    376 ;	main.c: 99: SPI_CR1 = SPI_CR1_MSTR;// | SPI_CR1_BR(3);
      009A8B 35 04 52 00      [ 1]  377 	mov	0x5200+0, #0x04
                                    378 ;	main.c: 100: SPI_CR1 |= SPI_CR1_SPE;
      009A8F 72 1C 52 00      [ 1]  379 	bset	0x5200, #6
                                    380 ;	main.c: 101: }
      009A93 81               [ 4]  381 	ret
                                    382 ;	main.c: 103: void SPI_write(uint8_t data) {
                                    383 ;	-----------------------------------------
                                    384 ;	 function SPI_write
                                    385 ;	-----------------------------------------
      009A94                        386 _SPI_write:
                                    387 ;	main.c: 104: SPI_DR = data;
      009A94 C7 52 04         [ 1]  388 	ld	0x5204, a
                                    389 ;	main.c: 105: while (!(SPI_SR & SPI_SR_TXE));
      009A97                        390 00101$:
      009A97 72 03 52 03 FB   [ 2]  391 	btjf	0x5203, #1, 00101$
                                    392 ;	main.c: 106: }
      009A9C 81               [ 4]  393 	ret
                                    394 ;	main.c: 112: void ST7735_Write(uint8_t val, uint8_t cmd) {
                                    395 ;	-----------------------------------------
                                    396 ;	 function ST7735_Write
                                    397 ;	-----------------------------------------
      009A9D                        398 _ST7735_Write:
      009A9D 97               [ 1]  399 	ld	xl, a
                                    400 ;	main.c: 114: PA_ODR &= ~(1 << DC_PIN);
      009A9E C6 50 00         [ 1]  401 	ld	a, 0x5000
                                    402 ;	main.c: 113: if (cmd==CMD)
      009AA1 0D 03            [ 1]  403 	tnz	(0x03, sp)
      009AA3 26 07            [ 1]  404 	jrne	00102$
                                    405 ;	main.c: 114: PA_ODR &= ~(1 << DC_PIN);
      009AA5 A4 F7            [ 1]  406 	and	a, #0xf7
      009AA7 C7 50 00         [ 1]  407 	ld	0x5000, a
      009AAA 20 05            [ 2]  408 	jra	00103$
      009AAC                        409 00102$:
                                    410 ;	main.c: 116: PA_ODR |= (1 << DC_PIN);
      009AAC AA 08            [ 1]  411 	or	a, #0x08
      009AAE C7 50 00         [ 1]  412 	ld	0x5000, a
      009AB1                        413 00103$:
                                    414 ;	main.c: 117: SPI_write(val);
      009AB1 9F               [ 1]  415 	ld	a, xl
      009AB2 CD 9A 94         [ 4]  416 	call	_SPI_write
                                    417 ;	main.c: 120: PA_ODR |= (1 << DC_PIN);
      009AB5 C6 50 00         [ 1]  418 	ld	a, 0x5000
      009AB8 AA 08            [ 1]  419 	or	a, #0x08
      009ABA C7 50 00         [ 1]  420 	ld	0x5000, a
                                    421 ;	main.c: 121: }
      009ABD 85               [ 2]  422 	popw	x
      009ABE 84               [ 1]  423 	pop	a
      009ABF FC               [ 2]  424 	jp	(x)
                                    425 ;	main.c: 131: void ST7735_Write16(uint16_t value) {
                                    426 ;	-----------------------------------------
                                    427 ;	 function ST7735_Write16
                                    428 ;	-----------------------------------------
      009AC0                        429 _ST7735_Write16:
                                    430 ;	main.c: 132: ST7735_WriteData(((value & 0xFF00) >> 0x08));
      009AC0 90 93            [ 1]  431 	ldw	y, x
                                    432 ;	main.c: 124: PA_ODR |= (1 << DC_PIN);
      009AC2 72 16 50 00      [ 1]  433 	bset	0x5000, #3
                                    434 ;	main.c: 125: SPI_write(val);
      009AC6 89               [ 2]  435 	pushw	x
      009AC7 90 9E            [ 1]  436 	ld	a, yh
      009AC9 CD 9A 94         [ 4]  437 	call	_SPI_write
      009ACC 85               [ 2]  438 	popw	x
                                    439 ;	main.c: 128: PA_ODR |= (1 << DC_PIN);
      009ACD 72 16 50 00      [ 1]  440 	bset	0x5000, #3
                                    441 ;	main.c: 133: ST7735_WriteData((value & 0x00FF));
                                    442 ;	main.c: 124: PA_ODR |= (1 << DC_PIN);
      009AD1 72 16 50 00      [ 1]  443 	bset	0x5000, #3
                                    444 ;	main.c: 125: SPI_write(val);
      009AD5 9F               [ 1]  445 	ld	a, xl
      009AD6 CD 9A 94         [ 4]  446 	call	_SPI_write
                                    447 ;	main.c: 128: PA_ODR |= (1 << DC_PIN);
      009AD9 72 16 50 00      [ 1]  448 	bset	0x5000, #3
                                    449 ;	main.c: 133: ST7735_WriteData((value & 0x00FF));
                                    450 ;	main.c: 134: }
      009ADD 81               [ 4]  451 	ret
                                    452 ;	main.c: 136: void ST7735_SetAddrWindow(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
                                    453 ;	-----------------------------------------
                                    454 ;	 function ST7735_SetAddrWindow
                                    455 ;	-----------------------------------------
      009ADE                        456 _ST7735_SetAddrWindow:
      009ADE 52 02            [ 2]  457 	sub	sp, #2
      009AE0 6B 02            [ 1]  458 	ld	(0x02, sp), a
                                    459 ;	main.c: 137: y += 0x18;
      009AE2 7B 05            [ 1]  460 	ld	a, (0x05, sp)
      009AE4 AB 18            [ 1]  461 	add	a, #0x18
      009AE6 6B 05            [ 1]  462 	ld	(0x05, sp), a
                                    463 ;	main.c: 138: w += x -1;
      009AE8 7B 02            [ 1]  464 	ld	a, (0x02, sp)
      009AEA 4A               [ 1]  465 	dec	a
      009AEB 6B 01            [ 1]  466 	ld	(0x01, sp), a
      009AED 7B 06            [ 1]  467 	ld	a, (0x06, sp)
      009AEF 1B 01            [ 1]  468 	add	a, (0x01, sp)
      009AF1 6B 06            [ 1]  469 	ld	(0x06, sp), a
                                    470 ;	main.c: 139: h += y -1;
      009AF3 7B 05            [ 1]  471 	ld	a, (0x05, sp)
      009AF5 4A               [ 1]  472 	dec	a
      009AF6 6B 01            [ 1]  473 	ld	(0x01, sp), a
      009AF8 7B 07            [ 1]  474 	ld	a, (0x07, sp)
      009AFA 1B 01            [ 1]  475 	add	a, (0x01, sp)
      009AFC 6B 07            [ 1]  476 	ld	(0x07, sp), a
                                    477 ;	main.c: 140: ST7735_Write(ST7735_CASET, CMD);
      009AFE 4B 00            [ 1]  478 	push	#0x00
      009B00 A6 2A            [ 1]  479 	ld	a, #0x2a
      009B02 CD 9A 9D         [ 4]  480 	call	_ST7735_Write
                                    481 ;	main.c: 141: ST7735_Write(0x00, DAT);
      009B05 4B 01            [ 1]  482 	push	#0x01
      009B07 4F               [ 1]  483 	clr	a
      009B08 CD 9A 9D         [ 4]  484 	call	_ST7735_Write
                                    485 ;	main.c: 142: ST7735_Write(x, DAT);
      009B0B 4B 01            [ 1]  486 	push	#0x01
      009B0D 7B 03            [ 1]  487 	ld	a, (0x03, sp)
      009B0F CD 9A 9D         [ 4]  488 	call	_ST7735_Write
                                    489 ;	main.c: 143: ST7735_Write(0x00, DAT);
      009B12 4B 01            [ 1]  490 	push	#0x01
      009B14 4F               [ 1]  491 	clr	a
      009B15 CD 9A 9D         [ 4]  492 	call	_ST7735_Write
                                    493 ;	main.c: 144: ST7735_Write(w, DAT);
      009B18 4B 01            [ 1]  494 	push	#0x01
      009B1A 7B 07            [ 1]  495 	ld	a, (0x07, sp)
      009B1C CD 9A 9D         [ 4]  496 	call	_ST7735_Write
                                    497 ;	main.c: 145: ST7735_Write(ST7735_RASET, CMD);
      009B1F 4B 00            [ 1]  498 	push	#0x00
      009B21 A6 2B            [ 1]  499 	ld	a, #0x2b
      009B23 CD 9A 9D         [ 4]  500 	call	_ST7735_Write
                                    501 ;	main.c: 146: ST7735_Write(0x00, DAT);
      009B26 4B 01            [ 1]  502 	push	#0x01
      009B28 4F               [ 1]  503 	clr	a
      009B29 CD 9A 9D         [ 4]  504 	call	_ST7735_Write
                                    505 ;	main.c: 147: ST7735_Write(y, DAT);
      009B2C 4B 01            [ 1]  506 	push	#0x01
      009B2E 7B 06            [ 1]  507 	ld	a, (0x06, sp)
      009B30 CD 9A 9D         [ 4]  508 	call	_ST7735_Write
                                    509 ;	main.c: 148: ST7735_Write(0x00, DAT);
      009B33 4B 01            [ 1]  510 	push	#0x01
      009B35 4F               [ 1]  511 	clr	a
      009B36 CD 9A 9D         [ 4]  512 	call	_ST7735_Write
                                    513 ;	main.c: 149: ST7735_Write(h, DAT);
      009B39 4B 01            [ 1]  514 	push	#0x01
      009B3B 7B 08            [ 1]  515 	ld	a, (0x08, sp)
      009B3D CD 9A 9D         [ 4]  516 	call	_ST7735_Write
                                    517 ;	main.c: 150: ST7735_Write(ST7735_RAMWR, CMD);
      009B40 4B 00            [ 1]  518 	push	#0x00
      009B42 A6 2C            [ 1]  519 	ld	a, #0x2c
      009B44 CD 9A 9D         [ 4]  520 	call	_ST7735_Write
                                    521 ;	main.c: 151: }
      009B47 1E 03            [ 2]  522 	ldw	x, (3, sp)
      009B49 5B 07            [ 2]  523 	addw	sp, #7
      009B4B FC               [ 2]  524 	jp	(x)
                                    525 ;	main.c: 153: void ST7735_Init(void) {
                                    526 ;	-----------------------------------------
                                    527 ;	 function ST7735_Init
                                    528 ;	-----------------------------------------
      009B4C                        529 _ST7735_Init:
                                    530 ;	main.c: 155: PA_DDR |= (1 << DC_PIN);
      009B4C 72 16 50 02      [ 1]  531 	bset	0x5002, #3
                                    532 ;	main.c: 156: PA_CR1 |= (1 << DC_PIN);
      009B50 72 16 50 03      [ 1]  533 	bset	0x5003, #3
                                    534 ;	main.c: 157: PA_ODR |= (1 << DC_PIN);
      009B54 72 16 50 00      [ 1]  535 	bset	0x5000, #3
                                    536 ;	main.c: 159: PD_DDR |= (1 << RST_PIN);
      009B58 72 1C 50 11      [ 1]  537 	bset	0x5011, #6
                                    538 ;	main.c: 160: PD_CR1 |= (1 << RST_PIN);
      009B5C 72 1C 50 12      [ 1]  539 	bset	0x5012, #6
                                    540 ;	main.c: 161: PD_ODR &= ~(1 << RST_PIN);
      009B60 72 1D 50 0F      [ 1]  541 	bres	0x500f, #6
                                    542 ;	main.c: 163: SPI_init();
      009B64 CD 9A 77         [ 4]  543 	call	_SPI_init
                                    544 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009B67 90 5F            [ 1]  545 	clrw	y
      009B69 5F               [ 1]  546 	clrw	x
      009B6A                        547 00116$:
      009B6A 90 A3 0D 40      [ 2]  548 	cpw	y, #0x0d40
      009B6E 9F               [ 1]  549 	ld	a, xl
      009B6F A2 03            [ 1]  550 	sbc	a, #0x03
      009B71 9E               [ 1]  551 	ld	a, xh
      009B72 A2 00            [ 1]  552 	sbc	a, #0x00
      009B74 24 08            [ 1]  553 	jrnc	00102$
                                    554 ;	main.c: 28: __asm__("nop");
      009B76 9D               [ 1]  555 	nop
                                    556 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009B77 90 5C            [ 1]  557 	incw	y
      009B79 26 EF            [ 1]  558 	jrne	00116$
      009B7B 5C               [ 1]  559 	incw	x
      009B7C 20 EC            [ 2]  560 	jra	00116$
                                    561 ;	main.c: 164: delay_ms(100);
      009B7E                        562 00102$:
                                    563 ;	main.c: 166: PD_ODR |= (1 << RST_PIN);
      009B7E 72 1C 50 0F      [ 1]  564 	bset	0x500f, #6
                                    565 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009B82 90 5F            [ 1]  566 	clrw	y
      009B84 5F               [ 1]  567 	clrw	x
      009B85                        568 00119$:
      009B85 90 A3 0D 40      [ 2]  569 	cpw	y, #0x0d40
      009B89 9F               [ 1]  570 	ld	a, xl
      009B8A A2 03            [ 1]  571 	sbc	a, #0x03
      009B8C 9E               [ 1]  572 	ld	a, xh
      009B8D A2 00            [ 1]  573 	sbc	a, #0x00
      009B8F 24 08            [ 1]  574 	jrnc	00104$
                                    575 ;	main.c: 28: __asm__("nop");
      009B91 9D               [ 1]  576 	nop
                                    577 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009B92 90 5C            [ 1]  578 	incw	y
      009B94 26 EF            [ 1]  579 	jrne	00119$
      009B96 5C               [ 1]  580 	incw	x
      009B97 20 EC            [ 2]  581 	jra	00119$
                                    582 ;	main.c: 167: delay_ms(100);
      009B99                        583 00104$:
                                    584 ;	main.c: 169: ST7735_Write(ST7735_SWRESET, CMD);
      009B99 4B 00            [ 1]  585 	push	#0x00
      009B9B A6 01            [ 1]  586 	ld	a, #0x01
      009B9D CD 9A 9D         [ 4]  587 	call	_ST7735_Write
                                    588 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009BA0 90 5F            [ 1]  589 	clrw	y
      009BA2 5F               [ 1]  590 	clrw	x
      009BA3                        591 00122$:
      009BA3 90 A3 93 E0      [ 2]  592 	cpw	y, #0x93e0
      009BA7 9F               [ 1]  593 	ld	a, xl
      009BA8 A2 04            [ 1]  594 	sbc	a, #0x04
      009BAA 9E               [ 1]  595 	ld	a, xh
      009BAB A2 00            [ 1]  596 	sbc	a, #0x00
      009BAD 24 08            [ 1]  597 	jrnc	00106$
                                    598 ;	main.c: 28: __asm__("nop");
      009BAF 9D               [ 1]  599 	nop
                                    600 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009BB0 90 5C            [ 1]  601 	incw	y
      009BB2 26 EF            [ 1]  602 	jrne	00122$
      009BB4 5C               [ 1]  603 	incw	x
      009BB5 20 EC            [ 2]  604 	jra	00122$
                                    605 ;	main.c: 170: delay_ms(150);
      009BB7                        606 00106$:
                                    607 ;	main.c: 171: ST7735_Write(ST7735_SLPOUT, CMD);
      009BB7 4B 00            [ 1]  608 	push	#0x00
      009BB9 A6 11            [ 1]  609 	ld	a, #0x11
      009BBB CD 9A 9D         [ 4]  610 	call	_ST7735_Write
                                    611 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009BBE 90 5F            [ 1]  612 	clrw	y
      009BC0 5F               [ 1]  613 	clrw	x
      009BC1                        614 00125$:
      009BC1 90 A3 42 40      [ 2]  615 	cpw	y, #0x4240
      009BC5 9F               [ 1]  616 	ld	a, xl
      009BC6 A2 0F            [ 1]  617 	sbc	a, #0x0f
      009BC8 9E               [ 1]  618 	ld	a, xh
      009BC9 A2 00            [ 1]  619 	sbc	a, #0x00
      009BCB 24 08            [ 1]  620 	jrnc	00108$
                                    621 ;	main.c: 28: __asm__("nop");
      009BCD 9D               [ 1]  622 	nop
                                    623 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009BCE 90 5C            [ 1]  624 	incw	y
      009BD0 26 EF            [ 1]  625 	jrne	00125$
      009BD2 5C               [ 1]  626 	incw	x
      009BD3 20 EC            [ 2]  627 	jra	00125$
                                    628 ;	main.c: 172: delay_ms(500);
      009BD5                        629 00108$:
                                    630 ;	main.c: 173: ST7735_Write(ST7735_FRMCTR1, CMD);
      009BD5 4B 00            [ 1]  631 	push	#0x00
      009BD7 A6 B1            [ 1]  632 	ld	a, #0xb1
      009BD9 CD 9A 9D         [ 4]  633 	call	_ST7735_Write
                                    634 ;	main.c: 174: ST7735_Write(0x01, DAT);
      009BDC 4B 01            [ 1]  635 	push	#0x01
      009BDE A6 01            [ 1]  636 	ld	a, #0x01
      009BE0 CD 9A 9D         [ 4]  637 	call	_ST7735_Write
                                    638 ;	main.c: 175: ST7735_Write(0x2C, DAT);
      009BE3 4B 01            [ 1]  639 	push	#0x01
      009BE5 A6 2C            [ 1]  640 	ld	a, #0x2c
      009BE7 CD 9A 9D         [ 4]  641 	call	_ST7735_Write
                                    642 ;	main.c: 176: ST7735_Write(0x2D, DAT);
      009BEA 4B 01            [ 1]  643 	push	#0x01
      009BEC A6 2D            [ 1]  644 	ld	a, #0x2d
      009BEE CD 9A 9D         [ 4]  645 	call	_ST7735_Write
                                    646 ;	main.c: 177: ST7735_Write(ST7735_FRMCTR2, CMD);
      009BF1 4B 00            [ 1]  647 	push	#0x00
      009BF3 A6 B2            [ 1]  648 	ld	a, #0xb2
      009BF5 CD 9A 9D         [ 4]  649 	call	_ST7735_Write
                                    650 ;	main.c: 178: ST7735_Write(0x01, DAT);
      009BF8 4B 01            [ 1]  651 	push	#0x01
      009BFA A6 01            [ 1]  652 	ld	a, #0x01
      009BFC CD 9A 9D         [ 4]  653 	call	_ST7735_Write
                                    654 ;	main.c: 179: ST7735_Write(0x2C, DAT);
      009BFF 4B 01            [ 1]  655 	push	#0x01
      009C01 A6 2C            [ 1]  656 	ld	a, #0x2c
      009C03 CD 9A 9D         [ 4]  657 	call	_ST7735_Write
                                    658 ;	main.c: 180: ST7735_Write(0x2D, DAT);
      009C06 4B 01            [ 1]  659 	push	#0x01
      009C08 A6 2D            [ 1]  660 	ld	a, #0x2d
      009C0A CD 9A 9D         [ 4]  661 	call	_ST7735_Write
                                    662 ;	main.c: 181: ST7735_Write(ST7735_FRMCTR3, CMD);
      009C0D 4B 00            [ 1]  663 	push	#0x00
      009C0F A6 B3            [ 1]  664 	ld	a, #0xb3
      009C11 CD 9A 9D         [ 4]  665 	call	_ST7735_Write
                                    666 ;	main.c: 182: ST7735_Write(0x01, DAT);
      009C14 4B 01            [ 1]  667 	push	#0x01
      009C16 A6 01            [ 1]  668 	ld	a, #0x01
      009C18 CD 9A 9D         [ 4]  669 	call	_ST7735_Write
                                    670 ;	main.c: 183: ST7735_Write(0x2C, DAT);
      009C1B 4B 01            [ 1]  671 	push	#0x01
      009C1D A6 2C            [ 1]  672 	ld	a, #0x2c
      009C1F CD 9A 9D         [ 4]  673 	call	_ST7735_Write
                                    674 ;	main.c: 184: ST7735_Write(0x2D, DAT);
      009C22 4B 01            [ 1]  675 	push	#0x01
      009C24 A6 2D            [ 1]  676 	ld	a, #0x2d
      009C26 CD 9A 9D         [ 4]  677 	call	_ST7735_Write
                                    678 ;	main.c: 185: ST7735_Write(0x01, DAT);
      009C29 4B 01            [ 1]  679 	push	#0x01
      009C2B A6 01            [ 1]  680 	ld	a, #0x01
      009C2D CD 9A 9D         [ 4]  681 	call	_ST7735_Write
                                    682 ;	main.c: 186: ST7735_Write(0x2C, DAT);
      009C30 4B 01            [ 1]  683 	push	#0x01
      009C32 A6 2C            [ 1]  684 	ld	a, #0x2c
      009C34 CD 9A 9D         [ 4]  685 	call	_ST7735_Write
                                    686 ;	main.c: 187: ST7735_Write(0x2D, DAT);
      009C37 4B 01            [ 1]  687 	push	#0x01
      009C39 A6 2D            [ 1]  688 	ld	a, #0x2d
      009C3B CD 9A 9D         [ 4]  689 	call	_ST7735_Write
                                    690 ;	main.c: 188: ST7735_Write(ST7735_INVCTR, CMD);
      009C3E 4B 00            [ 1]  691 	push	#0x00
      009C40 A6 B4            [ 1]  692 	ld	a, #0xb4
      009C42 CD 9A 9D         [ 4]  693 	call	_ST7735_Write
                                    694 ;	main.c: 189: ST7735_Write(0x07, DAT);
      009C45 4B 01            [ 1]  695 	push	#0x01
      009C47 A6 07            [ 1]  696 	ld	a, #0x07
      009C49 CD 9A 9D         [ 4]  697 	call	_ST7735_Write
                                    698 ;	main.c: 190: ST7735_Write(ST7735_PWCTR1, CMD);
      009C4C 4B 00            [ 1]  699 	push	#0x00
      009C4E A6 C0            [ 1]  700 	ld	a, #0xc0
      009C50 CD 9A 9D         [ 4]  701 	call	_ST7735_Write
                                    702 ;	main.c: 191: ST7735_Write(0xA2, DAT);
      009C53 4B 01            [ 1]  703 	push	#0x01
      009C55 A6 A2            [ 1]  704 	ld	a, #0xa2
      009C57 CD 9A 9D         [ 4]  705 	call	_ST7735_Write
                                    706 ;	main.c: 192: ST7735_Write(0x02, DAT);
      009C5A 4B 01            [ 1]  707 	push	#0x01
      009C5C A6 02            [ 1]  708 	ld	a, #0x02
      009C5E CD 9A 9D         [ 4]  709 	call	_ST7735_Write
                                    710 ;	main.c: 193: ST7735_Write(0x84, DAT);
      009C61 4B 01            [ 1]  711 	push	#0x01
      009C63 A6 84            [ 1]  712 	ld	a, #0x84
      009C65 CD 9A 9D         [ 4]  713 	call	_ST7735_Write
                                    714 ;	main.c: 194: ST7735_Write(ST7735_PWCTR2, CMD);
      009C68 4B 00            [ 1]  715 	push	#0x00
      009C6A A6 C1            [ 1]  716 	ld	a, #0xc1
      009C6C CD 9A 9D         [ 4]  717 	call	_ST7735_Write
                                    718 ;	main.c: 195: ST7735_Write(0xC5, DAT);
      009C6F 4B 01            [ 1]  719 	push	#0x01
      009C71 A6 C5            [ 1]  720 	ld	a, #0xc5
      009C73 CD 9A 9D         [ 4]  721 	call	_ST7735_Write
                                    722 ;	main.c: 196: ST7735_Write(ST7735_PWCTR3, CMD);
      009C76 4B 00            [ 1]  723 	push	#0x00
      009C78 A6 C2            [ 1]  724 	ld	a, #0xc2
      009C7A CD 9A 9D         [ 4]  725 	call	_ST7735_Write
                                    726 ;	main.c: 197: ST7735_Write(0x0A, DAT);
      009C7D 4B 01            [ 1]  727 	push	#0x01
      009C7F A6 0A            [ 1]  728 	ld	a, #0x0a
      009C81 CD 9A 9D         [ 4]  729 	call	_ST7735_Write
                                    730 ;	main.c: 198: ST7735_Write(0x00, DAT);
      009C84 4B 01            [ 1]  731 	push	#0x01
      009C86 4F               [ 1]  732 	clr	a
      009C87 CD 9A 9D         [ 4]  733 	call	_ST7735_Write
                                    734 ;	main.c: 199: ST7735_Write(ST7735_PWCTR4, CMD);
      009C8A 4B 00            [ 1]  735 	push	#0x00
      009C8C A6 C3            [ 1]  736 	ld	a, #0xc3
      009C8E CD 9A 9D         [ 4]  737 	call	_ST7735_Write
                                    738 ;	main.c: 200: ST7735_Write(0x8A, DAT);
      009C91 4B 01            [ 1]  739 	push	#0x01
      009C93 A6 8A            [ 1]  740 	ld	a, #0x8a
      009C95 CD 9A 9D         [ 4]  741 	call	_ST7735_Write
                                    742 ;	main.c: 201: ST7735_Write(0x2A, DAT);
      009C98 4B 01            [ 1]  743 	push	#0x01
      009C9A A6 2A            [ 1]  744 	ld	a, #0x2a
      009C9C CD 9A 9D         [ 4]  745 	call	_ST7735_Write
                                    746 ;	main.c: 202: ST7735_Write(ST7735_PWCTR5, CMD);
      009C9F 4B 00            [ 1]  747 	push	#0x00
      009CA1 A6 C4            [ 1]  748 	ld	a, #0xc4
      009CA3 CD 9A 9D         [ 4]  749 	call	_ST7735_Write
                                    750 ;	main.c: 203: ST7735_Write(0x8A, DAT);
      009CA6 4B 01            [ 1]  751 	push	#0x01
      009CA8 A6 8A            [ 1]  752 	ld	a, #0x8a
      009CAA CD 9A 9D         [ 4]  753 	call	_ST7735_Write
                                    754 ;	main.c: 204: ST7735_Write(0xEE, DAT);
      009CAD 4B 01            [ 1]  755 	push	#0x01
      009CAF A6 EE            [ 1]  756 	ld	a, #0xee
      009CB1 CD 9A 9D         [ 4]  757 	call	_ST7735_Write
                                    758 ;	main.c: 205: ST7735_Write(ST7735_VMCTR1, CMD);
      009CB4 4B 00            [ 1]  759 	push	#0x00
      009CB6 A6 C5            [ 1]  760 	ld	a, #0xc5
      009CB8 CD 9A 9D         [ 4]  761 	call	_ST7735_Write
                                    762 ;	main.c: 206: ST7735_Write(0x0E, DAT);
      009CBB 4B 01            [ 1]  763 	push	#0x01
      009CBD A6 0E            [ 1]  764 	ld	a, #0x0e
      009CBF CD 9A 9D         [ 4]  765 	call	_ST7735_Write
                                    766 ;	main.c: 207: ST7735_Write(ST7735_INVON, CMD);
      009CC2 4B 00            [ 1]  767 	push	#0x00
      009CC4 A6 21            [ 1]  768 	ld	a, #0x21
      009CC6 CD 9A 9D         [ 4]  769 	call	_ST7735_Write
                                    770 ;	main.c: 208: ST7735_Write(ST7735_MADCTL, CMD);
      009CC9 4B 00            [ 1]  771 	push	#0x00
      009CCB A6 36            [ 1]  772 	ld	a, #0x36
      009CCD CD 9A 9D         [ 4]  773 	call	_ST7735_Write
                                    774 ;	main.c: 209: ST7735_Write(0xC8, DAT);
      009CD0 4B 01            [ 1]  775 	push	#0x01
      009CD2 A6 C8            [ 1]  776 	ld	a, #0xc8
      009CD4 CD 9A 9D         [ 4]  777 	call	_ST7735_Write
                                    778 ;	main.c: 210: ST7735_Write(ST7735_COLMOD, CMD);
      009CD7 4B 00            [ 1]  779 	push	#0x00
      009CD9 A6 3A            [ 1]  780 	ld	a, #0x3a
      009CDB CD 9A 9D         [ 4]  781 	call	_ST7735_Write
                                    782 ;	main.c: 211: ST7735_Write(0x05, DAT);
      009CDE 4B 01            [ 1]  783 	push	#0x01
      009CE0 A6 05            [ 1]  784 	ld	a, #0x05
      009CE2 CD 9A 9D         [ 4]  785 	call	_ST7735_Write
                                    786 ;	main.c: 215: ST7735_Write(ST7735_CASET, CMD);
      009CE5 4B 00            [ 1]  787 	push	#0x00
      009CE7 A6 2A            [ 1]  788 	ld	a, #0x2a
      009CE9 CD 9A 9D         [ 4]  789 	call	_ST7735_Write
                                    790 ;	main.c: 216: ST7735_Write(0x00, DAT);
      009CEC 4B 01            [ 1]  791 	push	#0x01
      009CEE 4F               [ 1]  792 	clr	a
      009CEF CD 9A 9D         [ 4]  793 	call	_ST7735_Write
                                    794 ;	main.c: 217: ST7735_Write(0x00, DAT);
      009CF2 4B 01            [ 1]  795 	push	#0x01
      009CF4 4F               [ 1]  796 	clr	a
      009CF5 CD 9A 9D         [ 4]  797 	call	_ST7735_Write
                                    798 ;	main.c: 218: ST7735_Write(0x00, DAT);
      009CF8 4B 01            [ 1]  799 	push	#0x01
      009CFA 4F               [ 1]  800 	clr	a
      009CFB CD 9A 9D         [ 4]  801 	call	_ST7735_Write
                                    802 ;	main.c: 219: ST7735_Write(0x4F, DAT);
      009CFE 4B 01            [ 1]  803 	push	#0x01
      009D00 A6 4F            [ 1]  804 	ld	a, #0x4f
      009D02 CD 9A 9D         [ 4]  805 	call	_ST7735_Write
                                    806 ;	main.c: 220: ST7735_Write(ST7735_RASET, CMD);
      009D05 4B 00            [ 1]  807 	push	#0x00
      009D07 A6 2B            [ 1]  808 	ld	a, #0x2b
      009D09 CD 9A 9D         [ 4]  809 	call	_ST7735_Write
                                    810 ;	main.c: 221: ST7735_Write(0x00, DAT);
      009D0C 4B 01            [ 1]  811 	push	#0x01
      009D0E 4F               [ 1]  812 	clr	a
      009D0F CD 9A 9D         [ 4]  813 	call	_ST7735_Write
                                    814 ;	main.c: 222: ST7735_Write(0x00, DAT);
      009D12 4B 01            [ 1]  815 	push	#0x01
      009D14 4F               [ 1]  816 	clr	a
      009D15 CD 9A 9D         [ 4]  817 	call	_ST7735_Write
                                    818 ;	main.c: 223: ST7735_Write(0x00, DAT);
      009D18 4B 01            [ 1]  819 	push	#0x01
      009D1A 4F               [ 1]  820 	clr	a
      009D1B CD 9A 9D         [ 4]  821 	call	_ST7735_Write
                                    822 ;	main.c: 224: ST7735_Write(0x9F, DAT);
      009D1E 4B 01            [ 1]  823 	push	#0x01
      009D20 A6 9F            [ 1]  824 	ld	a, #0x9f
      009D22 CD 9A 9D         [ 4]  825 	call	_ST7735_Write
                                    826 ;	main.c: 228: ST7735_Write(ST7735_GMCTRP1, CMD);
      009D25 4B 00            [ 1]  827 	push	#0x00
      009D27 A6 E0            [ 1]  828 	ld	a, #0xe0
      009D29 CD 9A 9D         [ 4]  829 	call	_ST7735_Write
                                    830 ;	main.c: 229: ST7735_Write(0x02, DAT);
      009D2C 4B 01            [ 1]  831 	push	#0x01
      009D2E A6 02            [ 1]  832 	ld	a, #0x02
      009D30 CD 9A 9D         [ 4]  833 	call	_ST7735_Write
                                    834 ;	main.c: 230: ST7735_Write(0x1C, DAT);
      009D33 4B 01            [ 1]  835 	push	#0x01
      009D35 A6 1C            [ 1]  836 	ld	a, #0x1c
      009D37 CD 9A 9D         [ 4]  837 	call	_ST7735_Write
                                    838 ;	main.c: 231: ST7735_Write(0x07, DAT);
      009D3A 4B 01            [ 1]  839 	push	#0x01
      009D3C A6 07            [ 1]  840 	ld	a, #0x07
      009D3E CD 9A 9D         [ 4]  841 	call	_ST7735_Write
                                    842 ;	main.c: 232: ST7735_Write(0x12, DAT);
      009D41 4B 01            [ 1]  843 	push	#0x01
      009D43 A6 12            [ 1]  844 	ld	a, #0x12
      009D45 CD 9A 9D         [ 4]  845 	call	_ST7735_Write
                                    846 ;	main.c: 233: ST7735_Write(0x37, DAT);
      009D48 4B 01            [ 1]  847 	push	#0x01
      009D4A A6 37            [ 1]  848 	ld	a, #0x37
      009D4C CD 9A 9D         [ 4]  849 	call	_ST7735_Write
                                    850 ;	main.c: 234: ST7735_Write(0x32, DAT);
      009D4F 4B 01            [ 1]  851 	push	#0x01
      009D51 A6 32            [ 1]  852 	ld	a, #0x32
      009D53 CD 9A 9D         [ 4]  853 	call	_ST7735_Write
                                    854 ;	main.c: 235: ST7735_Write(0x29, DAT);
      009D56 4B 01            [ 1]  855 	push	#0x01
      009D58 A6 29            [ 1]  856 	ld	a, #0x29
      009D5A CD 9A 9D         [ 4]  857 	call	_ST7735_Write
                                    858 ;	main.c: 236: ST7735_Write(0x2D, DAT);
      009D5D 4B 01            [ 1]  859 	push	#0x01
      009D5F A6 2D            [ 1]  860 	ld	a, #0x2d
      009D61 CD 9A 9D         [ 4]  861 	call	_ST7735_Write
                                    862 ;	main.c: 237: ST7735_Write(0x29, DAT);
      009D64 4B 01            [ 1]  863 	push	#0x01
      009D66 A6 29            [ 1]  864 	ld	a, #0x29
      009D68 CD 9A 9D         [ 4]  865 	call	_ST7735_Write
                                    866 ;	main.c: 238: ST7735_Write(0x25, DAT);
      009D6B 4B 01            [ 1]  867 	push	#0x01
      009D6D A6 25            [ 1]  868 	ld	a, #0x25
      009D6F CD 9A 9D         [ 4]  869 	call	_ST7735_Write
                                    870 ;	main.c: 239: ST7735_Write(0x2B, DAT);
      009D72 4B 01            [ 1]  871 	push	#0x01
      009D74 A6 2B            [ 1]  872 	ld	a, #0x2b
      009D76 CD 9A 9D         [ 4]  873 	call	_ST7735_Write
                                    874 ;	main.c: 240: ST7735_Write(0x39, DAT);
      009D79 4B 01            [ 1]  875 	push	#0x01
      009D7B A6 39            [ 1]  876 	ld	a, #0x39
      009D7D CD 9A 9D         [ 4]  877 	call	_ST7735_Write
                                    878 ;	main.c: 241: ST7735_Write(0x00, DAT);
      009D80 4B 01            [ 1]  879 	push	#0x01
      009D82 4F               [ 1]  880 	clr	a
      009D83 CD 9A 9D         [ 4]  881 	call	_ST7735_Write
                                    882 ;	main.c: 242: ST7735_Write(0x01, DAT);
      009D86 4B 01            [ 1]  883 	push	#0x01
      009D88 A6 01            [ 1]  884 	ld	a, #0x01
      009D8A CD 9A 9D         [ 4]  885 	call	_ST7735_Write
                                    886 ;	main.c: 243: ST7735_Write(0x03, DAT);
      009D8D 4B 01            [ 1]  887 	push	#0x01
      009D8F A6 03            [ 1]  888 	ld	a, #0x03
      009D91 CD 9A 9D         [ 4]  889 	call	_ST7735_Write
                                    890 ;	main.c: 244: ST7735_Write(0x10, DAT);
      009D94 4B 01            [ 1]  891 	push	#0x01
      009D96 A6 10            [ 1]  892 	ld	a, #0x10
      009D98 CD 9A 9D         [ 4]  893 	call	_ST7735_Write
                                    894 ;	main.c: 245: ST7735_Write(ST7735_GMCTRN1, CMD);
      009D9B 4B 00            [ 1]  895 	push	#0x00
      009D9D A6 E1            [ 1]  896 	ld	a, #0xe1
      009D9F CD 9A 9D         [ 4]  897 	call	_ST7735_Write
                                    898 ;	main.c: 246: ST7735_Write(0x03, DAT);
      009DA2 4B 01            [ 1]  899 	push	#0x01
      009DA4 A6 03            [ 1]  900 	ld	a, #0x03
      009DA6 CD 9A 9D         [ 4]  901 	call	_ST7735_Write
                                    902 ;	main.c: 247: ST7735_Write(0x1D, DAT);
      009DA9 4B 01            [ 1]  903 	push	#0x01
      009DAB A6 1D            [ 1]  904 	ld	a, #0x1d
      009DAD CD 9A 9D         [ 4]  905 	call	_ST7735_Write
                                    906 ;	main.c: 248: ST7735_Write(0x07, DAT);
      009DB0 4B 01            [ 1]  907 	push	#0x01
      009DB2 A6 07            [ 1]  908 	ld	a, #0x07
      009DB4 CD 9A 9D         [ 4]  909 	call	_ST7735_Write
                                    910 ;	main.c: 249: ST7735_Write(0x06, DAT);
      009DB7 4B 01            [ 1]  911 	push	#0x01
      009DB9 A6 06            [ 1]  912 	ld	a, #0x06
      009DBB CD 9A 9D         [ 4]  913 	call	_ST7735_Write
                                    914 ;	main.c: 250: ST7735_Write(0x2E, DAT);
      009DBE 4B 01            [ 1]  915 	push	#0x01
      009DC0 A6 2E            [ 1]  916 	ld	a, #0x2e
      009DC2 CD 9A 9D         [ 4]  917 	call	_ST7735_Write
                                    918 ;	main.c: 251: ST7735_Write(0x2C, DAT);
      009DC5 4B 01            [ 1]  919 	push	#0x01
      009DC7 A6 2C            [ 1]  920 	ld	a, #0x2c
      009DC9 CD 9A 9D         [ 4]  921 	call	_ST7735_Write
                                    922 ;	main.c: 252: ST7735_Write(0x29, DAT);
      009DCC 4B 01            [ 1]  923 	push	#0x01
      009DCE A6 29            [ 1]  924 	ld	a, #0x29
      009DD0 CD 9A 9D         [ 4]  925 	call	_ST7735_Write
                                    926 ;	main.c: 253: ST7735_Write(0x2D, DAT);
      009DD3 4B 01            [ 1]  927 	push	#0x01
      009DD5 A6 2D            [ 1]  928 	ld	a, #0x2d
      009DD7 CD 9A 9D         [ 4]  929 	call	_ST7735_Write
                                    930 ;	main.c: 254: ST7735_Write(0x2E, DAT);
      009DDA 4B 01            [ 1]  931 	push	#0x01
      009DDC A6 2E            [ 1]  932 	ld	a, #0x2e
      009DDE CD 9A 9D         [ 4]  933 	call	_ST7735_Write
                                    934 ;	main.c: 255: ST7735_Write(0x2E, DAT);
      009DE1 4B 01            [ 1]  935 	push	#0x01
      009DE3 A6 2E            [ 1]  936 	ld	a, #0x2e
      009DE5 CD 9A 9D         [ 4]  937 	call	_ST7735_Write
                                    938 ;	main.c: 256: ST7735_Write(0x37, DAT);
      009DE8 4B 01            [ 1]  939 	push	#0x01
      009DEA A6 37            [ 1]  940 	ld	a, #0x37
      009DEC CD 9A 9D         [ 4]  941 	call	_ST7735_Write
                                    942 ;	main.c: 257: ST7735_Write(0x3F, DAT);
      009DEF 4B 01            [ 1]  943 	push	#0x01
      009DF1 A6 3F            [ 1]  944 	ld	a, #0x3f
      009DF3 CD 9A 9D         [ 4]  945 	call	_ST7735_Write
                                    946 ;	main.c: 258: ST7735_Write(0x00, DAT);
      009DF6 4B 01            [ 1]  947 	push	#0x01
      009DF8 4F               [ 1]  948 	clr	a
      009DF9 CD 9A 9D         [ 4]  949 	call	_ST7735_Write
                                    950 ;	main.c: 259: ST7735_Write(0x00, DAT);
      009DFC 4B 01            [ 1]  951 	push	#0x01
      009DFE 4F               [ 1]  952 	clr	a
      009DFF CD 9A 9D         [ 4]  953 	call	_ST7735_Write
                                    954 ;	main.c: 260: ST7735_Write(0x02, DAT);
      009E02 4B 01            [ 1]  955 	push	#0x01
      009E04 A6 02            [ 1]  956 	ld	a, #0x02
      009E06 CD 9A 9D         [ 4]  957 	call	_ST7735_Write
                                    958 ;	main.c: 261: ST7735_Write(0x10, DAT);
      009E09 4B 01            [ 1]  959 	push	#0x01
      009E0B A6 10            [ 1]  960 	ld	a, #0x10
      009E0D CD 9A 9D         [ 4]  961 	call	_ST7735_Write
                                    962 ;	main.c: 262: ST7735_Write(ST7735_NORON, CMD);
      009E10 4B 00            [ 1]  963 	push	#0x00
      009E12 A6 13            [ 1]  964 	ld	a, #0x13
      009E14 CD 9A 9D         [ 4]  965 	call	_ST7735_Write
                                    966 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009E17 90 5F            [ 1]  967 	clrw	y
      009E19 5F               [ 1]  968 	clrw	x
      009E1A                        969 00128$:
      009E1A 90 A3 4E 20      [ 2]  970 	cpw	y, #0x4e20
      009E1E 9F               [ 1]  971 	ld	a, xl
      009E1F A2 00            [ 1]  972 	sbc	a, #0x00
      009E21 9E               [ 1]  973 	ld	a, xh
      009E22 A2 00            [ 1]  974 	sbc	a, #0x00
      009E24 24 08            [ 1]  975 	jrnc	00110$
                                    976 ;	main.c: 28: __asm__("nop");
      009E26 9D               [ 1]  977 	nop
                                    978 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009E27 90 5C            [ 1]  979 	incw	y
      009E29 26 EF            [ 1]  980 	jrne	00128$
      009E2B 5C               [ 1]  981 	incw	x
      009E2C 20 EC            [ 2]  982 	jra	00128$
                                    983 ;	main.c: 263: delay_ms(10);
      009E2E                        984 00110$:
                                    985 ;	main.c: 264: ST7735_Write(ST7735_DISPON, CMD);
      009E2E 4B 00            [ 1]  986 	push	#0x00
      009E30 A6 29            [ 1]  987 	ld	a, #0x29
      009E32 CD 9A 9D         [ 4]  988 	call	_ST7735_Write
                                    989 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009E35 90 5F            [ 1]  990 	clrw	y
      009E37 5F               [ 1]  991 	clrw	x
      009E38                        992 00131$:
      009E38 90 A3 0D 40      [ 2]  993 	cpw	y, #0x0d40
      009E3C 9F               [ 1]  994 	ld	a, xl
      009E3D A2 03            [ 1]  995 	sbc	a, #0x03
      009E3F 9E               [ 1]  996 	ld	a, xh
      009E40 A2 00            [ 1]  997 	sbc	a, #0x00
      009E42 24 08            [ 1]  998 	jrnc	00112$
                                    999 ;	main.c: 28: __asm__("nop");
      009E44 9D               [ 1] 1000 	nop
                                   1001 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009E45 90 5C            [ 1] 1002 	incw	y
      009E47 26 EF            [ 1] 1003 	jrne	00131$
      009E49 5C               [ 1] 1004 	incw	x
      009E4A 20 EC            [ 2] 1005 	jra	00131$
                                   1006 ;	main.c: 265: delay_ms(100);
      009E4C                       1007 00112$:
                                   1008 ;	main.c: 267: ST7735_Write(ST7735_MADCTL, CMD);
      009E4C 4B 00            [ 1] 1009 	push	#0x00
      009E4E A6 36            [ 1] 1010 	ld	a, #0x36
      009E50 CD 9A 9D         [ 4] 1011 	call	_ST7735_Write
                                   1012 ;	main.c: 268: ST7735_Write(MADCTL_MX | MADCTL_MV | MADCTL_RGB, DAT);
      009E53 4B 01            [ 1] 1013 	push	#0x01
      009E55 A6 68            [ 1] 1014 	ld	a, #0x68
      009E57 CD 9A 9D         [ 4] 1015 	call	_ST7735_Write
                                   1016 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009E5A 90 5F            [ 1] 1017 	clrw	y
      009E5C 5F               [ 1] 1018 	clrw	x
      009E5D                       1019 00134$:
      009E5D 90 A3 4E 20      [ 2] 1020 	cpw	y, #0x4e20
      009E61 9F               [ 1] 1021 	ld	a, xl
      009E62 A2 00            [ 1] 1022 	sbc	a, #0x00
      009E64 9E               [ 1] 1023 	ld	a, xh
      009E65 A2 00            [ 1] 1024 	sbc	a, #0x00
      009E67 25 01            [ 1] 1025 	jrc	00227$
      009E69 81               [ 4] 1026 	ret
      009E6A                       1027 00227$:
                                   1028 ;	main.c: 28: __asm__("nop");
      009E6A 9D               [ 1] 1029 	nop
                                   1030 ;	main.c: 27: for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
      009E6B 90 5C            [ 1] 1031 	incw	y
      009E6D 26 EE            [ 1] 1032 	jrne	00134$
      009E6F 5C               [ 1] 1033 	incw	x
      009E70 20 EB            [ 2] 1034 	jra	00134$
                                   1035 ;	main.c: 269: delay_ms(10);
                                   1036 ;	main.c: 270: }
      009E72 81               [ 4] 1037 	ret
                                   1038 ;	main.c: 273: void ST7735_Clear(uint16_t color) {
                                   1039 ;	-----------------------------------------
                                   1040 ;	 function ST7735_Clear
                                   1041 ;	-----------------------------------------
      009E73                       1042 _ST7735_Clear:
      009E73 52 04            [ 2] 1043 	sub	sp, #4
      009E75 1F 01            [ 2] 1044 	ldw	(0x01, sp), x
                                   1045 ;	main.c: 274: ST7735_SetAddrWindow(0,0,ST7735_TFTLENGTH+3,ST7735_TFTWIDTH+3);
      009E77 4B 53            [ 1] 1046 	push	#0x53
      009E79 4B A3            [ 1] 1047 	push	#0xa3
      009E7B 4B 00            [ 1] 1048 	push	#0x00
      009E7D 4F               [ 1] 1049 	clr	a
      009E7E CD 9A DE         [ 4] 1050 	call	_ST7735_SetAddrWindow
                                   1051 ;	main.c: 275: for (int i=0; i< ST7735_TFTWIDTH+3; ++i)
      009E81 5F               [ 1] 1052 	clrw	x
      009E82 1F 03            [ 2] 1053 	ldw	(0x03, sp), x
      009E84                       1054 00107$:
      009E84 1E 03            [ 2] 1055 	ldw	x, (0x03, sp)
      009E86 A3 00 53         [ 2] 1056 	cpw	x, #0x0053
      009E89 2E 17            [ 1] 1057 	jrsge	00109$
                                   1058 ;	main.c: 276: for(int j=0; j< ST7735_TFTLENGTH+3; ++j)
      009E8B 5F               [ 1] 1059 	clrw	x
      009E8C                       1060 00104$:
      009E8C A3 00 A3         [ 2] 1061 	cpw	x, #0x00a3
      009E8F 2E 0A            [ 1] 1062 	jrsge	00108$
                                   1063 ;	main.c: 277: ST7735_Write16(color);
      009E91 89               [ 2] 1064 	pushw	x
      009E92 1E 03            [ 2] 1065 	ldw	x, (0x03, sp)
      009E94 CD 9A C0         [ 4] 1066 	call	_ST7735_Write16
      009E97 85               [ 2] 1067 	popw	x
                                   1068 ;	main.c: 276: for(int j=0; j< ST7735_TFTLENGTH+3; ++j)
      009E98 5C               [ 1] 1069 	incw	x
      009E99 20 F1            [ 2] 1070 	jra	00104$
      009E9B                       1071 00108$:
                                   1072 ;	main.c: 275: for (int i=0; i< ST7735_TFTWIDTH+3; ++i)
      009E9B 1E 03            [ 2] 1073 	ldw	x, (0x03, sp)
      009E9D 5C               [ 1] 1074 	incw	x
      009E9E 1F 03            [ 2] 1075 	ldw	(0x03, sp), x
      009EA0 20 E2            [ 2] 1076 	jra	00107$
      009EA2                       1077 00109$:
                                   1078 ;	main.c: 278: }
      009EA2 5B 04            [ 2] 1079 	addw	sp, #4
      009EA4 81               [ 4] 1080 	ret
                                   1081 	.area CODE
                                   1082 	.area CONST
      00802D                       1083 _pallet:
      00802D 00 00                 1084 	.dw #0x0000
      00802F 29 01                 1085 	.dw #0x2901
      008031 5A 04                 1086 	.dw #0x5a04
      008033 7A 85                 1087 	.dw #0x7a85
      008035 41 84                 1088 	.dw #0x4184
      008037 9B 07                 1089 	.dw #0x9b07
      008039 B3 88                 1090 	.dw #0xb388
      00803B 62 86                 1091 	.dw #0x6286
      00803D CC 0A                 1092 	.dw #0xcc0a
      00803F FD 0B                 1093 	.dw #0xfd0b
      008041 DC 8C                 1094 	.dw #0xdc8c
      008043 9C 0C                 1095 	.dw #0x9c0c
      008045 ED 0E                 1096 	.dw #0xed0e
      008047 FD 8F                 1097 	.dw #0xfd8f
      008049 FD 90                 1098 	.dw #0xfd90
      00804B 00 10                 1099 	.dw #0x0010
      00804D 63 0C                 1100 	.dw #0x630c
      00804F B5 96                 1101 	.dw #0xb596
      008051 FE 97                 1102 	.dw #0xfe97
      008053 58 20                 1103 	.dw #0x5820
      008055 49 A3                 1104 	.dw #0x49a3
      008057 6A 24                 1105 	.dw #0x6a24
      008059 21 24                 1106 	.dw #0x2124
      00805B 82 A6                 1107 	.dw #0x82a6
      00805D 42 28                 1108 	.dw #0x4228
      00805F 52 AA                 1109 	.dw #0x52aa
      008061 BA AA                 1110 	.dw #0xbaaa
      008063 73 AE                 1111 	.dw #0x73ae
      008065 EC B2                 1112 	.dw #0xecb2
      008067 94 B2                 1113 	.dw #0x94b2
      008069 FE 34                 1114 	.dw #0xfe34
      00806B A5 34                 1115 	.dw #0xa534
      00806D FE B7                 1116 	.dw #0xfeb7
      00806F 42 08                 1117 	.dw #0x4208
      008071 31 42                 1118 	.dw #0x3142
      008073 9A C2                 1119 	.dw #0x9ac2
      008075 78 C3                 1120 	.dw #0x78c3
      008077 89 45                 1121 	.dw #0x8945
      008079 A3 47                 1122 	.dw #0xa347
      00807B 39 C7                 1123 	.dw #0x39c7
      00807D BB C9                 1124 	.dw #0xbbc9
      00807F D4 4B                 1125 	.dw #0xd44b
      008081 5A CB                 1126 	.dw #0x5acb
      008083 E4 CD                 1127 	.dw #0xe4cd
      008085 6B 4D                 1128 	.dw #0x6b4d
      008087 F5 4F                 1129 	.dw #0xf54f
      008089 DB CF                 1130 	.dw #0xdbcf
      00808B FD D2                 1131 	.dw #0xfdd2
      00808D AD 55                 1132 	.dw #0xad55
      00808F CE 59                 1133 	.dw #0xce59
      008091 DE DB                 1134 	.dw #0xdedb
      008093 39 62                 1135 	.dw #0x3962
      008095 51 E3                 1136 	.dw #0x51e3
      008097 72 65                 1137 	.dw #0x7265
      008099 8A E6                 1138 	.dw #0x8ae6
      00809B 29 65                 1139 	.dw #0x2965
      00809D AB 68                 1140 	.dw #0xab68
      00809F CB E9                 1141 	.dw #0xcbe9
      0080A1 4A 69                 1142 	.dw #0x4a69
      0080A3 7B EF                 1143 	.dw #0x7bef
      0080A5 9C F3                 1144 	.dw #0x9cf3
      0080A7 FD F3                 1145 	.dw #0xfdf3
      0080A9 FE 76                 1146 	.dw #0xfe76
      0080AB DE FB                 1147 	.dw #0xdefb
      0080AD EF 7D                 1148 	.dw #0xef7d
      0080AF                       1149 _doom1_raw:
      0080AF 00                    1150 	.db #0x00	; 0
      0080B0 00                    1151 	.db #0x00	; 0
      0080B1 00                    1152 	.db #0x00	; 0
      0080B2 00                    1153 	.db #0x00	; 0
      0080B3 00                    1154 	.db #0x00	; 0
      0080B4 00                    1155 	.db #0x00	; 0
      0080B5 14                    1156 	.db #0x14	; 20
      0080B6 02                    1157 	.db #0x02	; 2
      0080B7 02                    1158 	.db #0x02	; 2
      0080B8 02                    1159 	.db #0x02	; 2
      0080B9 15                    1160 	.db #0x15	; 21
      0080BA 35                    1161 	.db #0x35	; 53	'5'
      0080BB 35                    1162 	.db #0x35	; 53	'5'
      0080BC 35                    1163 	.db #0x35	; 53	'5'
      0080BD 35                    1164 	.db #0x35	; 53	'5'
      0080BE 35                    1165 	.db #0x35	; 53	'5'
      0080BF 15                    1166 	.db #0x15	; 21
      0080C0 02                    1167 	.db #0x02	; 2
      0080C1 02                    1168 	.db #0x02	; 2
      0080C2 14                    1169 	.db #0x14	; 20
      0080C3 00                    1170 	.db #0x00	; 0
      0080C4 00                    1171 	.db #0x00	; 0
      0080C5 00                    1172 	.db #0x00	; 0
      0080C6 00                    1173 	.db #0x00	; 0
      0080C7 00                    1174 	.db #0x00	; 0
      0080C8 00                    1175 	.db #0x00	; 0
      0080C9 00                    1176 	.db #0x00	; 0
      0080CA 00                    1177 	.db #0x00	; 0
      0080CB 00                    1178 	.db #0x00	; 0
      0080CC 00                    1179 	.db #0x00	; 0
      0080CD 22                    1180 	.db #0x22	; 34
      0080CE 02                    1181 	.db #0x02	; 2
      0080CF 34                    1182 	.db #0x34	; 52	'4'
      0080D0 03                    1183 	.db #0x03	; 3
      0080D1 36                    1184 	.db #0x36	; 54	'6'
      0080D2 38                    1185 	.db #0x38	; 56	'8'
      0080D3 28                    1186 	.db #0x28	; 40
      0080D4 08                    1187 	.db #0x08	; 8
      0080D5 08                    1188 	.db #0x08	; 8
      0080D6 08                    1189 	.db #0x08	; 8
      0080D7 28                    1190 	.db #0x28	; 40
      0080D8 38                    1191 	.db #0x38	; 56	'8'
      0080D9 05                    1192 	.db #0x05	; 5
      0080DA 35                    1193 	.db #0x35	; 53	'5'
      0080DB 02                    1194 	.db #0x02	; 2
      0080DC 34                    1195 	.db #0x34	; 52	'4'
      0080DD 02                    1196 	.db #0x02	; 2
      0080DE 22                    1197 	.db #0x22	; 34
      0080DF 00                    1198 	.db #0x00	; 0
      0080E0 00                    1199 	.db #0x00	; 0
      0080E1 00                    1200 	.db #0x00	; 0
      0080E2 00                    1201 	.db #0x00	; 0
      0080E3 00                    1202 	.db #0x00	; 0
      0080E4 00                    1203 	.db #0x00	; 0
      0080E5 00                    1204 	.db #0x00	; 0
      0080E6 22                    1205 	.db #0x22	; 34
      0080E7 02                    1206 	.db #0x02	; 2
      0080E8 35                    1207 	.db #0x35	; 53	'5'
      0080E9 36                    1208 	.db #0x36	; 54	'6'
      0080EA 38                    1209 	.db #0x38	; 56	'8'
      0080EB 28                    1210 	.db #0x28	; 40
      0080EC 39                    1211 	.db #0x39	; 57	'9'
      0080ED 08                    1212 	.db #0x08	; 8
      0080EE 28                    1213 	.db #0x28	; 40
      0080EF 06                    1214 	.db #0x06	; 6
      0080F0 05                    1215 	.db #0x05	; 5
      0080F1 05                    1216 	.db #0x05	; 5
      0080F2 05                    1217 	.db #0x05	; 5
      0080F3 36                    1218 	.db #0x36	; 54	'6'
      0080F4 36                    1219 	.db #0x36	; 54	'6'
      0080F5 35                    1220 	.db #0x35	; 53	'5'
      0080F6 35                    1221 	.db #0x35	; 53	'5'
      0080F7 34                    1222 	.db #0x34	; 52	'4'
      0080F8 14                    1223 	.db #0x14	; 20
      0080F9 22                    1224 	.db #0x22	; 34
      0080FA 00                    1225 	.db #0x00	; 0
      0080FB 00                    1226 	.db #0x00	; 0
      0080FC 00                    1227 	.db #0x00	; 0
      0080FD 00                    1228 	.db #0x00	; 0
      0080FE 00                    1229 	.db #0x00	; 0
      0080FF 00                    1230 	.db #0x00	; 0
      008100 22                    1231 	.db #0x22	; 34
      008101 35                    1232 	.db #0x35	; 53	'5'
      008102 17                    1233 	.db #0x17	; 23
      008103 35                    1234 	.db #0x35	; 53	'5'
      008104 36                    1235 	.db #0x36	; 54	'6'
      008105 05                    1236 	.db #0x05	; 5
      008106 06                    1237 	.db #0x06	; 6
      008107 17                    1238 	.db #0x17	; 23
      008108 38                    1239 	.db #0x38	; 56	'8'
      008109 36                    1240 	.db #0x36	; 54	'6'
      00810A 26                    1241 	.db #0x26	; 38
      00810B 35                    1242 	.db #0x35	; 53	'5'
      00810C 35                    1243 	.db #0x35	; 53	'5'
      00810D 35                    1244 	.db #0x35	; 53	'5'
      00810E 35                    1245 	.db #0x35	; 53	'5'
      00810F 02                    1246 	.db #0x02	; 2
      008110 34                    1247 	.db #0x34	; 52	'4'
      008111 22                    1248 	.db #0x22	; 34
      008112 22                    1249 	.db #0x22	; 34
      008113 01                    1250 	.db #0x01	; 1
      008114 00                    1251 	.db #0x00	; 0
      008115 00                    1252 	.db #0x00	; 0
      008116 00                    1253 	.db #0x00	; 0
      008117 00                    1254 	.db #0x00	; 0
      008118 00                    1255 	.db #0x00	; 0
      008119 01                    1256 	.db #0x01	; 1
      00811A 33                    1257 	.db #0x33	; 51	'3'
      00811B 02                    1258 	.db #0x02	; 2
      00811C 35                    1259 	.db #0x35	; 53	'5'
      00811D 02                    1260 	.db #0x02	; 2
      00811E 36                    1261 	.db #0x36	; 54	'6'
      00811F 05                    1262 	.db #0x05	; 5
      008120 36                    1263 	.db #0x36	; 54	'6'
      008121 36                    1264 	.db #0x36	; 54	'6'
      008122 36                    1265 	.db #0x36	; 54	'6'
      008123 36                    1266 	.db #0x36	; 54	'6'
      008124 14                    1267 	.db #0x14	; 20
      008125 36                    1268 	.db #0x36	; 54	'6'
      008126 02                    1269 	.db #0x02	; 2
      008127 14                    1270 	.db #0x14	; 20
      008128 02                    1271 	.db #0x02	; 2
      008129 14                    1272 	.db #0x14	; 20
      00812A 22                    1273 	.db #0x22	; 34
      00812B 01                    1274 	.db #0x01	; 1
      00812C 01                    1275 	.db #0x01	; 1
      00812D 01                    1276 	.db #0x01	; 1
      00812E 01                    1277 	.db #0x01	; 1
      00812F 00                    1278 	.db #0x00	; 0
      008130 00                    1279 	.db #0x00	; 0
      008131 00                    1280 	.db #0x00	; 0
      008132 00                    1281 	.db #0x00	; 0
      008133 01                    1282 	.db #0x01	; 1
      008134 33                    1283 	.db #0x33	; 51	'3'
      008135 14                    1284 	.db #0x14	; 20
      008136 34                    1285 	.db #0x34	; 52	'4'
      008137 02                    1286 	.db #0x02	; 2
      008138 36                    1287 	.db #0x36	; 54	'6'
      008139 34                    1288 	.db #0x34	; 52	'4'
      00813A 05                    1289 	.db #0x05	; 5
      00813B 15                    1290 	.db #0x15	; 21
      00813C 15                    1291 	.db #0x15	; 21
      00813D 36                    1292 	.db #0x36	; 54	'6'
      00813E 15                    1293 	.db #0x15	; 21
      00813F 14                    1294 	.db #0x14	; 20
      008140 15                    1295 	.db #0x15	; 21
      008141 14                    1296 	.db #0x14	; 20
      008142 33                    1297 	.db #0x33	; 51	'3'
      008143 02                    1298 	.db #0x02	; 2
      008144 01                    1299 	.db #0x01	; 1
      008145 22                    1300 	.db #0x22	; 34
      008146 22                    1301 	.db #0x22	; 34
      008147 33                    1302 	.db #0x33	; 51	'3'
      008148 01                    1303 	.db #0x01	; 1
      008149 00                    1304 	.db #0x00	; 0
      00814A 00                    1305 	.db #0x00	; 0
      00814B 00                    1306 	.db #0x00	; 0
      00814C 00                    1307 	.db #0x00	; 0
      00814D 01                    1308 	.db #0x01	; 1
      00814E 14                    1309 	.db #0x14	; 20
      00814F 14                    1310 	.db #0x14	; 20
      008150 35                    1311 	.db #0x35	; 53	'5'
      008151 35                    1312 	.db #0x35	; 53	'5'
      008152 34                    1313 	.db #0x34	; 52	'4'
      008153 36                    1314 	.db #0x36	; 54	'6'
      008154 34                    1315 	.db #0x34	; 52	'4'
      008155 15                    1316 	.db #0x15	; 21
      008156 35                    1317 	.db #0x35	; 53	'5'
      008157 15                    1318 	.db #0x15	; 21
      008158 15                    1319 	.db #0x15	; 21
      008159 36                    1320 	.db #0x36	; 54	'6'
      00815A 36                    1321 	.db #0x36	; 54	'6'
      00815B 36                    1322 	.db #0x36	; 54	'6'
      00815C 17                    1323 	.db #0x17	; 23
      00815D 17                    1324 	.db #0x17	; 23
      00815E 15                    1325 	.db #0x15	; 21
      00815F 14                    1326 	.db #0x14	; 20
      008160 33                    1327 	.db #0x33	; 51	'3'
      008161 14                    1328 	.db #0x14	; 20
      008162 01                    1329 	.db #0x01	; 1
      008163 00                    1330 	.db #0x00	; 0
      008164 00                    1331 	.db #0x00	; 0
      008165 00                    1332 	.db #0x00	; 0
      008166 00                    1333 	.db #0x00	; 0
      008167 01                    1334 	.db #0x01	; 1
      008168 14                    1335 	.db #0x14	; 20
      008169 34                    1336 	.db #0x34	; 52	'4'
      00816A 35                    1337 	.db #0x35	; 53	'5'
      00816B 36                    1338 	.db #0x36	; 54	'6'
      00816C 35                    1339 	.db #0x35	; 53	'5'
      00816D 34                    1340 	.db #0x34	; 52	'4'
      00816E 26                    1341 	.db #0x26	; 38
      00816F 34                    1342 	.db #0x34	; 52	'4'
      008170 35                    1343 	.db #0x35	; 53	'5'
      008171 36                    1344 	.db #0x36	; 54	'6'
      008172 26                    1345 	.db #0x26	; 38
      008173 06                    1346 	.db #0x06	; 6
      008174 05                    1347 	.db #0x05	; 5
      008175 26                    1348 	.db #0x26	; 38
      008176 36                    1349 	.db #0x36	; 54	'6'
      008177 36                    1350 	.db #0x36	; 54	'6'
      008178 36                    1351 	.db #0x36	; 54	'6'
      008179 15                    1352 	.db #0x15	; 21
      00817A 14                    1353 	.db #0x14	; 20
      00817B 14                    1354 	.db #0x14	; 20
      00817C 01                    1355 	.db #0x01	; 1
      00817D 00                    1356 	.db #0x00	; 0
      00817E 00                    1357 	.db #0x00	; 0
      00817F 00                    1358 	.db #0x00	; 0
      008180 00                    1359 	.db #0x00	; 0
      008181 01                    1360 	.db #0x01	; 1
      008182 14                    1361 	.db #0x14	; 20
      008183 02                    1362 	.db #0x02	; 2
      008184 36                    1363 	.db #0x36	; 54	'6'
      008185 38                    1364 	.db #0x38	; 56	'8'
      008186 06                    1365 	.db #0x06	; 6
      008187 26                    1366 	.db #0x26	; 38
      008188 26                    1367 	.db #0x26	; 38
      008189 06                    1368 	.db #0x06	; 6
      00818A 06                    1369 	.db #0x06	; 6
      00818B 06                    1370 	.db #0x06	; 6
      00818C 06                    1371 	.db #0x06	; 6
      00818D 06                    1372 	.db #0x06	; 6
      00818E 06                    1373 	.db #0x06	; 6
      00818F 26                    1374 	.db #0x26	; 38
      008190 26                    1375 	.db #0x26	; 38
      008191 06                    1376 	.db #0x06	; 6
      008192 38                    1377 	.db #0x38	; 56	'8'
      008193 36                    1378 	.db #0x36	; 54	'6'
      008194 34                    1379 	.db #0x34	; 52	'4'
      008195 14                    1380 	.db #0x14	; 20
      008196 01                    1381 	.db #0x01	; 1
      008197 00                    1382 	.db #0x00	; 0
      008198 00                    1383 	.db #0x00	; 0
      008199 00                    1384 	.db #0x00	; 0
      00819A 00                    1385 	.db #0x00	; 0
      00819B 01                    1386 	.db #0x01	; 1
      00819C 14                    1387 	.db #0x14	; 20
      00819D 35                    1388 	.db #0x35	; 53	'5'
      00819E 05                    1389 	.db #0x05	; 5
      00819F 08                    1390 	.db #0x08	; 8
      0081A0 39                    1391 	.db #0x39	; 57	'9'
      0081A1 39                    1392 	.db #0x39	; 57	'9'
      0081A2 06                    1393 	.db #0x06	; 6
      0081A3 26                    1394 	.db #0x26	; 38
      0081A4 38                    1395 	.db #0x38	; 56	'8'
      0081A5 38                    1396 	.db #0x38	; 56	'8'
      0081A6 38                    1397 	.db #0x38	; 56	'8'
      0081A7 38                    1398 	.db #0x38	; 56	'8'
      0081A8 26                    1399 	.db #0x26	; 38
      0081A9 06                    1400 	.db #0x06	; 6
      0081AA 39                    1401 	.db #0x39	; 57	'9'
      0081AB 39                    1402 	.db #0x39	; 57	'9'
      0081AC 08                    1403 	.db #0x08	; 8
      0081AD 05                    1404 	.db #0x05	; 5
      0081AE 02                    1405 	.db #0x02	; 2
      0081AF 14                    1406 	.db #0x14	; 20
      0081B0 01                    1407 	.db #0x01	; 1
      0081B1 00                    1408 	.db #0x00	; 0
      0081B2 00                    1409 	.db #0x00	; 0
      0081B3 00                    1410 	.db #0x00	; 0
      0081B4 00                    1411 	.db #0x00	; 0
      0081B5 01                    1412 	.db #0x01	; 1
      0081B6 14                    1413 	.db #0x14	; 20
      0081B7 35                    1414 	.db #0x35	; 53	'5'
      0081B8 05                    1415 	.db #0x05	; 5
      0081B9 08                    1416 	.db #0x08	; 8
      0081BA 0C                    1417 	.db #0x0c	; 12
      0081BB 2B                    1418 	.db #0x2b	; 43
      0081BC 08                    1419 	.db #0x08	; 8
      0081BD 28                    1420 	.db #0x28	; 40
      0081BE 26                    1421 	.db #0x26	; 38
      0081BF 36                    1422 	.db #0x36	; 54	'6'
      0081C0 36                    1423 	.db #0x36	; 54	'6'
      0081C1 26                    1424 	.db #0x26	; 38
      0081C2 28                    1425 	.db #0x28	; 40
      0081C3 08                    1426 	.db #0x08	; 8
      0081C4 2B                    1427 	.db #0x2b	; 43
      0081C5 0C                    1428 	.db #0x0c	; 12
      0081C6 08                    1429 	.db #0x08	; 8
      0081C7 05                    1430 	.db #0x05	; 5
      0081C8 35                    1431 	.db #0x35	; 53	'5'
      0081C9 14                    1432 	.db #0x14	; 20
      0081CA 01                    1433 	.db #0x01	; 1
      0081CB 00                    1434 	.db #0x00	; 0
      0081CC 00                    1435 	.db #0x00	; 0
      0081CD 00                    1436 	.db #0x00	; 0
      0081CE 00                    1437 	.db #0x00	; 0
      0081CF 01                    1438 	.db #0x01	; 1
      0081D0 14                    1439 	.db #0x14	; 20
      0081D1 35                    1440 	.db #0x35	; 53	'5'
      0081D2 06                    1441 	.db #0x06	; 6
      0081D3 2B                    1442 	.db #0x2b	; 43
      0081D4 2F                    1443 	.db #0x2f	; 47
      0081D5 2F                    1444 	.db #0x2f	; 47
      0081D6 2B                    1445 	.db #0x2b	; 43
      0081D7 2B                    1446 	.db #0x2b	; 43
      0081D8 08                    1447 	.db #0x08	; 8
      0081D9 29                    1448 	.db #0x29	; 41
      0081DA 29                    1449 	.db #0x29	; 41
      0081DB 08                    1450 	.db #0x08	; 8
      0081DC 2B                    1451 	.db #0x2b	; 43
      0081DD 2B                    1452 	.db #0x2b	; 43
      0081DE 05                    1453 	.db #0x05	; 5
      0081DF 34                    1454 	.db #0x34	; 52	'4'
      0081E0 00                    1455 	.db #0x00	; 0
      0081E1 33                    1456 	.db #0x33	; 51	'3'
      0081E2 35                    1457 	.db #0x35	; 53	'5'
      0081E3 14                    1458 	.db #0x14	; 20
      0081E4 01                    1459 	.db #0x01	; 1
      0081E5 00                    1460 	.db #0x00	; 0
      0081E6 00                    1461 	.db #0x00	; 0
      0081E7 00                    1462 	.db #0x00	; 0
      0081E8 06                    1463 	.db #0x06	; 6
      0081E9 15                    1464 	.db #0x15	; 21
      0081EA 14                    1465 	.db #0x14	; 20
      0081EB 35                    1466 	.db #0x35	; 53	'5'
      0081EC 33                    1467 	.db #0x33	; 51	'3'
      0081ED 33                    1468 	.db #0x33	; 51	'3'
      0081EE 34                    1469 	.db #0x34	; 52	'4'
      0081EF 26                    1470 	.db #0x26	; 38
      0081F0 0A                    1471 	.db #0x0a	; 10
      0081F1 2F                    1472 	.db #0x2f	; 47
      0081F2 28                    1473 	.db #0x28	; 40
      0081F3 2D                    1474 	.db #0x2d	; 45
      0081F4 2D                    1475 	.db #0x2d	; 45
      0081F5 28                    1476 	.db #0x28	; 40
      0081F6 2F                    1477 	.db #0x2f	; 47
      0081F7 05                    1478 	.db #0x05	; 5
      0081F8 00                    1479 	.db #0x00	; 0
      0081F9 33                    1480 	.db #0x33	; 51	'3'
      0081FA 35                    1481 	.db #0x35	; 53	'5'
      0081FB 17                    1482 	.db #0x17	; 23
      0081FC 35                    1483 	.db #0x35	; 53	'5'
      0081FD 14                    1484 	.db #0x14	; 20
      0081FE 15                    1485 	.db #0x15	; 21
      0081FF 06                    1486 	.db #0x06	; 6
      008200 00                    1487 	.db #0x00	; 0
      008201 00                    1488 	.db #0x00	; 0
      008202 06                    1489 	.db #0x06	; 6
      008203 15                    1490 	.db #0x15	; 21
      008204 04                    1491 	.db #0x04	; 4
      008205 06                    1492 	.db #0x06	; 6
      008206 17                    1493 	.db #0x17	; 23
      008207 02                    1494 	.db #0x02	; 2
      008208 33                    1495 	.db #0x33	; 51	'3'
      008209 33                    1496 	.db #0x33	; 51	'3'
      00820A 33                    1497 	.db #0x33	; 51	'3'
      00820B 00                    1498 	.db #0x00	; 0
      00820C 02                    1499 	.db #0x02	; 2
      00820D 38                    1500 	.db #0x38	; 56	'8'
      00820E 38                    1501 	.db #0x38	; 56	'8'
      00820F 02                    1502 	.db #0x02	; 2
      008210 00                    1503 	.db #0x00	; 0
      008211 00                    1504 	.db #0x00	; 0
      008212 00                    1505 	.db #0x00	; 0
      008213 33                    1506 	.db #0x33	; 51	'3'
      008214 02                    1507 	.db #0x02	; 2
      008215 06                    1508 	.db #0x06	; 6
      008216 36                    1509 	.db #0x36	; 54	'6'
      008217 04                    1510 	.db #0x04	; 4
      008218 15                    1511 	.db #0x15	; 21
      008219 06                    1512 	.db #0x06	; 6
      00821A 00                    1513 	.db #0x00	; 0
      00821B 00                    1514 	.db #0x00	; 0
      00821C 36                    1515 	.db #0x36	; 54	'6'
      00821D 15                    1516 	.db #0x15	; 21
      00821E 07                    1517 	.db #0x07	; 7
      00821F 06                    1518 	.db #0x06	; 6
      008220 35                    1519 	.db #0x35	; 53	'5'
      008221 3B                    1520 	.db #0x3b	; 59
      008222 3C                    1521 	.db #0x3c	; 60
      008223 2C                    1522 	.db #0x2c	; 44
      008224 00                    1523 	.db #0x00	; 0
      008225 00                    1524 	.db #0x00	; 0
      008226 14                    1525 	.db #0x14	; 20
      008227 34                    1526 	.db #0x34	; 52	'4'
      008228 34                    1527 	.db #0x34	; 52	'4'
      008229 14                    1528 	.db #0x14	; 20
      00822A 00                    1529 	.db #0x00	; 0
      00822B 19                    1530 	.db #0x19	; 25
      00822C 3C                    1531 	.db #0x3c	; 60
      00822D 2C                    1532 	.db #0x2c	; 44
      00822E 00                    1533 	.db #0x00	; 0
      00822F 35                    1534 	.db #0x35	; 53	'5'
      008230 06                    1535 	.db #0x06	; 6
      008231 07                    1536 	.db #0x07	; 7
      008232 15                    1537 	.db #0x15	; 21
      008233 36                    1538 	.db #0x36	; 54	'6'
      008234 00                    1539 	.db #0x00	; 0
      008235 00                    1540 	.db #0x00	; 0
      008236 15                    1541 	.db #0x15	; 21
      008237 02                    1542 	.db #0x02	; 2
      008238 17                    1543 	.db #0x17	; 23
      008239 06                    1544 	.db #0x06	; 6
      00823A 36                    1545 	.db #0x36	; 54	'6'
      00823B 38                    1546 	.db #0x38	; 56	'8'
      00823C 0C                    1547 	.db #0x0c	; 12
      00823D 38                    1548 	.db #0x38	; 56	'8'
      00823E 15                    1549 	.db #0x15	; 21
      00823F 02                    1550 	.db #0x02	; 2
      008240 36                    1551 	.db #0x36	; 54	'6'
      008241 08                    1552 	.db #0x08	; 8
      008242 08                    1553 	.db #0x08	; 8
      008243 36                    1554 	.db #0x36	; 54	'6'
      008244 02                    1555 	.db #0x02	; 2
      008245 15                    1556 	.db #0x15	; 21
      008246 38                    1557 	.db #0x38	; 56	'8'
      008247 0C                    1558 	.db #0x0c	; 12
      008248 38                    1559 	.db #0x38	; 56	'8'
      008249 36                    1560 	.db #0x36	; 54	'6'
      00824A 06                    1561 	.db #0x06	; 6
      00824B 17                    1562 	.db #0x17	; 23
      00824C 02                    1563 	.db #0x02	; 2
      00824D 15                    1564 	.db #0x15	; 21
      00824E 00                    1565 	.db #0x00	; 0
      00824F 00                    1566 	.db #0x00	; 0
      008250 17                    1567 	.db #0x17	; 23
      008251 02                    1568 	.db #0x02	; 2
      008252 17                    1569 	.db #0x17	; 23
      008253 29                    1570 	.db #0x29	; 41
      008254 29                    1571 	.db #0x29	; 41
      008255 28                    1572 	.db #0x28	; 40
      008256 38                    1573 	.db #0x38	; 56	'8'
      008257 36                    1574 	.db #0x36	; 54	'6'
      008258 38                    1575 	.db #0x38	; 56	'8'
      008259 08                    1576 	.db #0x08	; 8
      00825A 38                    1577 	.db #0x38	; 56	'8'
      00825B 2D                    1578 	.db #0x2d	; 45
      00825C 2D                    1579 	.db #0x2d	; 45
      00825D 38                    1580 	.db #0x38	; 56	'8'
      00825E 08                    1581 	.db #0x08	; 8
      00825F 38                    1582 	.db #0x38	; 56	'8'
      008260 36                    1583 	.db #0x36	; 54	'6'
      008261 38                    1584 	.db #0x38	; 56	'8'
      008262 28                    1585 	.db #0x28	; 40
      008263 29                    1586 	.db #0x29	; 41
      008264 29                    1587 	.db #0x29	; 41
      008265 17                    1588 	.db #0x17	; 23
      008266 02                    1589 	.db #0x02	; 2
      008267 17                    1590 	.db #0x17	; 23
      008268 00                    1591 	.db #0x00	; 0
      008269 00                    1592 	.db #0x00	; 0
      00826A 36                    1593 	.db #0x36	; 54	'6'
      00826B 02                    1594 	.db #0x02	; 2
      00826C 36                    1595 	.db #0x36	; 54	'6'
      00826D 08                    1596 	.db #0x08	; 8
      00826E 0A                    1597 	.db #0x0a	; 10
      00826F 0C                    1598 	.db #0x0c	; 12
      008270 0A                    1599 	.db #0x0a	; 10
      008271 39                    1600 	.db #0x39	; 57	'9'
      008272 2B                    1601 	.db #0x2b	; 43
      008273 2F                    1602 	.db #0x2f	; 47
      008274 2B                    1603 	.db #0x2b	; 43
      008275 2F                    1604 	.db #0x2f	; 47
      008276 2F                    1605 	.db #0x2f	; 47
      008277 2B                    1606 	.db #0x2b	; 43
      008278 2F                    1607 	.db #0x2f	; 47
      008279 2B                    1608 	.db #0x2b	; 43
      00827A 39                    1609 	.db #0x39	; 57	'9'
      00827B 0A                    1610 	.db #0x0a	; 10
      00827C 0C                    1611 	.db #0x0c	; 12
      00827D 0A                    1612 	.db #0x0a	; 10
      00827E 08                    1613 	.db #0x08	; 8
      00827F 36                    1614 	.db #0x36	; 54	'6'
      008280 02                    1615 	.db #0x02	; 2
      008281 36                    1616 	.db #0x36	; 54	'6'
      008282 00                    1617 	.db #0x00	; 0
      008283 00                    1618 	.db #0x00	; 0
      008284 00                    1619 	.db #0x00	; 0
      008285 02                    1620 	.db #0x02	; 2
      008286 17                    1621 	.db #0x17	; 23
      008287 26                    1622 	.db #0x26	; 38
      008288 38                    1623 	.db #0x38	; 56	'8'
      008289 28                    1624 	.db #0x28	; 40
      00828A 29                    1625 	.db #0x29	; 41
      00828B 0C                    1626 	.db #0x0c	; 12
      00828C 0E                    1627 	.db #0x0e	; 14
      00828D 0A                    1628 	.db #0x0a	; 10
      00828E 29                    1629 	.db #0x29	; 41
      00828F 0D                    1630 	.db #0x0d	; 13
      008290 20                    1631 	.db #0x20	; 32
      008291 29                    1632 	.db #0x29	; 41
      008292 0A                    1633 	.db #0x0a	; 10
      008293 0E                    1634 	.db #0x0e	; 14
      008294 0C                    1635 	.db #0x0c	; 12
      008295 29                    1636 	.db #0x29	; 41
      008296 28                    1637 	.db #0x28	; 40
      008297 38                    1638 	.db #0x38	; 56	'8'
      008298 26                    1639 	.db #0x26	; 38
      008299 17                    1640 	.db #0x17	; 23
      00829A 02                    1641 	.db #0x02	; 2
      00829B 00                    1642 	.db #0x00	; 0
      00829C 00                    1643 	.db #0x00	; 0
      00829D 00                    1644 	.db #0x00	; 0
      00829E 00                    1645 	.db #0x00	; 0
      00829F 02                    1646 	.db #0x02	; 2
      0082A0 35                    1647 	.db #0x35	; 53	'5'
      0082A1 05                    1648 	.db #0x05	; 5
      0082A2 26                    1649 	.db #0x26	; 38
      0082A3 28                    1650 	.db #0x28	; 40
      0082A4 0C                    1651 	.db #0x0c	; 12
      0082A5 3D                    1652 	.db #0x3d	; 61
      0082A6 29                    1653 	.db #0x29	; 41
      0082A7 38                    1654 	.db #0x38	; 56	'8'
      0082A8 05                    1655 	.db #0x05	; 5
      0082A9 0B                    1656 	.db #0x0b	; 11
      0082AA 0B                    1657 	.db #0x0b	; 11
      0082AB 05                    1658 	.db #0x05	; 5
      0082AC 38                    1659 	.db #0x38	; 56	'8'
      0082AD 29                    1660 	.db #0x29	; 41
      0082AE 3D                    1661 	.db #0x3d	; 61
      0082AF 0C                    1662 	.db #0x0c	; 12
      0082B0 28                    1663 	.db #0x28	; 40
      0082B1 26                    1664 	.db #0x26	; 38
      0082B2 05                    1665 	.db #0x05	; 5
      0082B3 35                    1666 	.db #0x35	; 53	'5'
      0082B4 02                    1667 	.db #0x02	; 2
      0082B5 00                    1668 	.db #0x00	; 0
      0082B6 00                    1669 	.db #0x00	; 0
      0082B7 00                    1670 	.db #0x00	; 0
      0082B8 00                    1671 	.db #0x00	; 0
      0082B9 00                    1672 	.db #0x00	; 0
      0082BA 35                    1673 	.db #0x35	; 53	'5'
      0082BB 06                    1674 	.db #0x06	; 6
      0082BC 05                    1675 	.db #0x05	; 5
      0082BD 29                    1676 	.db #0x29	; 41
      0082BE 2F                    1677 	.db #0x2f	; 47
      0082BF 2B                    1678 	.db #0x2b	; 43
      0082C0 26                    1679 	.db #0x26	; 38
      0082C1 34                    1680 	.db #0x34	; 52	'4'
      0082C2 35                    1681 	.db #0x35	; 53	'5'
      0082C3 17                    1682 	.db #0x17	; 23
      0082C4 17                    1683 	.db #0x17	; 23
      0082C5 35                    1684 	.db #0x35	; 53	'5'
      0082C6 34                    1685 	.db #0x34	; 52	'4'
      0082C7 26                    1686 	.db #0x26	; 38
      0082C8 2B                    1687 	.db #0x2b	; 43
      0082C9 2F                    1688 	.db #0x2f	; 47
      0082CA 29                    1689 	.db #0x29	; 41
      0082CB 05                    1690 	.db #0x05	; 5
      0082CC 06                    1691 	.db #0x06	; 6
      0082CD 35                    1692 	.db #0x35	; 53	'5'
      0082CE 00                    1693 	.db #0x00	; 0
      0082CF 00                    1694 	.db #0x00	; 0
      0082D0 00                    1695 	.db #0x00	; 0
      0082D1 00                    1696 	.db #0x00	; 0
      0082D2 00                    1697 	.db #0x00	; 0
      0082D3 00                    1698 	.db #0x00	; 0
      0082D4 02                    1699 	.db #0x02	; 2
      0082D5 39                    1700 	.db #0x39	; 57	'9'
      0082D6 05                    1701 	.db #0x05	; 5
      0082D7 2B                    1702 	.db #0x2b	; 43
      0082D8 2D                    1703 	.db #0x2d	; 45
      0082D9 28                    1704 	.db #0x28	; 40
      0082DA 08                    1705 	.db #0x08	; 8
      0082DB 0A                    1706 	.db #0x0a	; 10
      0082DC 28                    1707 	.db #0x28	; 40
      0082DD 26                    1708 	.db #0x26	; 38
      0082DE 26                    1709 	.db #0x26	; 38
      0082DF 28                    1710 	.db #0x28	; 40
      0082E0 0A                    1711 	.db #0x0a	; 10
      0082E1 08                    1712 	.db #0x08	; 8
      0082E2 28                    1713 	.db #0x28	; 40
      0082E3 2D                    1714 	.db #0x2d	; 45
      0082E4 2B                    1715 	.db #0x2b	; 43
      0082E5 05                    1716 	.db #0x05	; 5
      0082E6 39                    1717 	.db #0x39	; 57	'9'
      0082E7 02                    1718 	.db #0x02	; 2
      0082E8 00                    1719 	.db #0x00	; 0
      0082E9 00                    1720 	.db #0x00	; 0
      0082EA 00                    1721 	.db #0x00	; 0
      0082EB 00                    1722 	.db #0x00	; 0
      0082EC 00                    1723 	.db #0x00	; 0
      0082ED 00                    1724 	.db #0x00	; 0
      0082EE 34                    1725 	.db #0x34	; 52	'4'
      0082EF 38                    1726 	.db #0x38	; 56	'8'
      0082F0 26                    1727 	.db #0x26	; 38
      0082F1 29                    1728 	.db #0x29	; 41
      0082F2 2B                    1729 	.db #0x2b	; 43
      0082F3 08                    1730 	.db #0x08	; 8
      0082F4 29                    1731 	.db #0x29	; 41
      0082F5 2D                    1732 	.db #0x2d	; 45
      0082F6 3D                    1733 	.db #0x3d	; 61
      0082F7 29                    1734 	.db #0x29	; 41
      0082F8 29                    1735 	.db #0x29	; 41
      0082F9 3D                    1736 	.db #0x3d	; 61
      0082FA 2D                    1737 	.db #0x2d	; 45
      0082FB 29                    1738 	.db #0x29	; 41
      0082FC 08                    1739 	.db #0x08	; 8
      0082FD 2B                    1740 	.db #0x2b	; 43
      0082FE 29                    1741 	.db #0x29	; 41
      0082FF 26                    1742 	.db #0x26	; 38
      008300 38                    1743 	.db #0x38	; 56	'8'
      008301 34                    1744 	.db #0x34	; 52	'4'
      008302 00                    1745 	.db #0x00	; 0
      008303 00                    1746 	.db #0x00	; 0
      008304 00                    1747 	.db #0x00	; 0
      008305 00                    1748 	.db #0x00	; 0
      008306 00                    1749 	.db #0x00	; 0
      008307 00                    1750 	.db #0x00	; 0
      008308 00                    1751 	.db #0x00	; 0
      008309 17                    1752 	.db #0x17	; 23
      00830A 38                    1753 	.db #0x38	; 56	'8'
      00830B 39                    1754 	.db #0x39	; 57	'9'
      00830C 29                    1755 	.db #0x29	; 41
      00830D 36                    1756 	.db #0x36	; 54	'6'
      00830E 35                    1757 	.db #0x35	; 53	'5'
      00830F 23                    1758 	.db #0x23	; 35
      008310 23                    1759 	.db #0x23	; 35
      008311 23                    1760 	.db #0x23	; 35
      008312 23                    1761 	.db #0x23	; 35
      008313 23                    1762 	.db #0x23	; 35
      008314 23                    1763 	.db #0x23	; 35
      008315 35                    1764 	.db #0x35	; 53	'5'
      008316 36                    1765 	.db #0x36	; 54	'6'
      008317 29                    1766 	.db #0x29	; 41
      008318 39                    1767 	.db #0x39	; 57	'9'
      008319 38                    1768 	.db #0x38	; 56	'8'
      00831A 17                    1769 	.db #0x17	; 23
      00831B 00                    1770 	.db #0x00	; 0
      00831C 00                    1771 	.db #0x00	; 0
      00831D 00                    1772 	.db #0x00	; 0
      00831E 00                    1773 	.db #0x00	; 0
      00831F 00                    1774 	.db #0x00	; 0
      008320 00                    1775 	.db #0x00	; 0
      008321 00                    1776 	.db #0x00	; 0
      008322 00                    1777 	.db #0x00	; 0
      008323 34                    1778 	.db #0x34	; 52	'4'
      008324 36                    1779 	.db #0x36	; 54	'6'
      008325 06                    1780 	.db #0x06	; 6
      008326 39                    1781 	.db #0x39	; 57	'9'
      008327 39                    1782 	.db #0x39	; 57	'9'
      008328 39                    1783 	.db #0x39	; 57	'9'
      008329 29                    1784 	.db #0x29	; 41
      00832A 2B                    1785 	.db #0x2b	; 43
      00832B 09                    1786 	.db #0x09	; 9
      00832C 09                    1787 	.db #0x09	; 9
      00832D 2B                    1788 	.db #0x2b	; 43
      00832E 29                    1789 	.db #0x29	; 41
      00832F 39                    1790 	.db #0x39	; 57	'9'
      008330 39                    1791 	.db #0x39	; 57	'9'
      008331 39                    1792 	.db #0x39	; 57	'9'
      008332 06                    1793 	.db #0x06	; 6
      008333 36                    1794 	.db #0x36	; 54	'6'
      008334 34                    1795 	.db #0x34	; 52	'4'
      008335 00                    1796 	.db #0x00	; 0
      008336 00                    1797 	.db #0x00	; 0
      008337 00                    1798 	.db #0x00	; 0
      008338 00                    1799 	.db #0x00	; 0
      008339 00                    1800 	.db #0x00	; 0
      00833A 00                    1801 	.db #0x00	; 0
      00833B 00                    1802 	.db #0x00	; 0
      00833C 00                    1803 	.db #0x00	; 0
      00833D 00                    1804 	.db #0x00	; 0
      00833E 15                    1805 	.db #0x15	; 21
      00833F 05                    1806 	.db #0x05	; 5
      008340 08                    1807 	.db #0x08	; 8
      008341 0A                    1808 	.db #0x0a	; 10
      008342 39                    1809 	.db #0x39	; 57	'9'
      008343 38                    1810 	.db #0x38	; 56	'8'
      008344 36                    1811 	.db #0x36	; 54	'6'
      008345 03                    1812 	.db #0x03	; 3
      008346 03                    1813 	.db #0x03	; 3
      008347 36                    1814 	.db #0x36	; 54	'6'
      008348 38                    1815 	.db #0x38	; 56	'8'
      008349 39                    1816 	.db #0x39	; 57	'9'
      00834A 0A                    1817 	.db #0x0a	; 10
      00834B 08                    1818 	.db #0x08	; 8
      00834C 05                    1819 	.db #0x05	; 5
      00834D 15                    1820 	.db #0x15	; 21
      00834E 00                    1821 	.db #0x00	; 0
      00834F 00                    1822 	.db #0x00	; 0
      008350 00                    1823 	.db #0x00	; 0
      008351 00                    1824 	.db #0x00	; 0
      008352 00                    1825 	.db #0x00	; 0
      008353 00                    1826 	.db #0x00	; 0
      008354 00                    1827 	.db #0x00	; 0
      008355 00                    1828 	.db #0x00	; 0
      008356 00                    1829 	.db #0x00	; 0
      008357 00                    1830 	.db #0x00	; 0
      008358 00                    1831 	.db #0x00	; 0
      008359 15                    1832 	.db #0x15	; 21
      00835A 26                    1833 	.db #0x26	; 38
      00835B 08                    1834 	.db #0x08	; 8
      00835C 0A                    1835 	.db #0x0a	; 10
      00835D 39                    1836 	.db #0x39	; 57	'9'
      00835E 39                    1837 	.db #0x39	; 57	'9'
      00835F 2B                    1838 	.db #0x2b	; 43
      008360 2B                    1839 	.db #0x2b	; 43
      008361 39                    1840 	.db #0x39	; 57	'9'
      008362 39                    1841 	.db #0x39	; 57	'9'
      008363 0A                    1842 	.db #0x0a	; 10
      008364 08                    1843 	.db #0x08	; 8
      008365 26                    1844 	.db #0x26	; 38
      008366 15                    1845 	.db #0x15	; 21
      008367 00                    1846 	.db #0x00	; 0
      008368 00                    1847 	.db #0x00	; 0
      008369 00                    1848 	.db #0x00	; 0
      00836A 00                    1849 	.db #0x00	; 0
      00836B 00                    1850 	.db #0x00	; 0
      00836C 00                    1851 	.db #0x00	; 0
      00836D 00                    1852 	.db #0x00	; 0
      00836E 00                    1853 	.db #0x00	; 0
      00836F 00                    1854 	.db #0x00	; 0
      008370 00                    1855 	.db #0x00	; 0
      008371 00                    1856 	.db #0x00	; 0
      008372 00                    1857 	.db #0x00	; 0
      008373 00                    1858 	.db #0x00	; 0
      008374 34                    1859 	.db #0x34	; 52	'4'
      008375 17                    1860 	.db #0x17	; 23
      008376 06                    1861 	.db #0x06	; 6
      008377 29                    1862 	.db #0x29	; 41
      008378 2B                    1863 	.db #0x2b	; 43
      008379 3D                    1864 	.db #0x3d	; 61
      00837A 3D                    1865 	.db #0x3d	; 61
      00837B 2B                    1866 	.db #0x2b	; 43
      00837C 29                    1867 	.db #0x29	; 41
      00837D 06                    1868 	.db #0x06	; 6
      00837E 17                    1869 	.db #0x17	; 23
      00837F 34                    1870 	.db #0x34	; 52	'4'
      008380 00                    1871 	.db #0x00	; 0
      008381 00                    1872 	.db #0x00	; 0
      008382 00                    1873 	.db #0x00	; 0
      008383 00                    1874 	.db #0x00	; 0
      008384 00                    1875 	.db #0x00	; 0
      008385 00                    1876 	.db #0x00	; 0
      008386 00                    1877 	.db #0x00	; 0
      008387 00                    1878 	.db #0x00	; 0
      008388 00                    1879 	.db #0x00	; 0
      008389 00                    1880 	.db #0x00	; 0
      00838A 00                    1881 	.db #0x00	; 0
      00838B 00                    1882 	.db #0x00	; 0
      00838C 00                    1883 	.db #0x00	; 0
      00838D 00                    1884 	.db #0x00	; 0
      00838E 00                    1885 	.db #0x00	; 0
      00838F 00                    1886 	.db #0x00	; 0
      008390 15                    1887 	.db #0x15	; 21
      008391 36                    1888 	.db #0x36	; 54	'6'
      008392 26                    1889 	.db #0x26	; 38
      008393 26                    1890 	.db #0x26	; 38
      008394 26                    1891 	.db #0x26	; 38
      008395 26                    1892 	.db #0x26	; 38
      008396 36                    1893 	.db #0x36	; 54	'6'
      008397 15                    1894 	.db #0x15	; 21
      008398 00                    1895 	.db #0x00	; 0
      008399 00                    1896 	.db #0x00	; 0
      00839A 00                    1897 	.db #0x00	; 0
      00839B 00                    1898 	.db #0x00	; 0
      00839C 00                    1899 	.db #0x00	; 0
      00839D 00                    1900 	.db #0x00	; 0
      00839E 00                    1901 	.db #0x00	; 0
      00839F 00                    1902 	.db #0x00	; 0
      0083A0 00                    1903 	.db #0x00	; 0
      0083A1 00                    1904 	.db #0x00	; 0
      0083A2 00                    1905 	.db #0x00	; 0
      0083A3 00                    1906 	.db #0x00	; 0
      0083A4 00                    1907 	.db #0x00	; 0
      0083A5 00                    1908 	.db #0x00	; 0
      0083A6 00                    1909 	.db #0x00	; 0
      0083A7 00                    1910 	.db #0x00	; 0
      0083A8 00                    1911 	.db #0x00	; 0
      0083A9 00                    1912 	.db #0x00	; 0
      0083AA 00                    1913 	.db #0x00	; 0
      0083AB 00                    1914 	.db #0x00	; 0
      0083AC 00                    1915 	.db #0x00	; 0
      0083AD 00                    1916 	.db #0x00	; 0
      0083AE 00                    1917 	.db #0x00	; 0
      0083AF 00                    1918 	.db #0x00	; 0
      0083B0 00                    1919 	.db #0x00	; 0
      0083B1 00                    1920 	.db #0x00	; 0
      0083B2 00                    1921 	.db #0x00	; 0
      0083B3 00                    1922 	.db #0x00	; 0
      0083B4 00                    1923 	.db #0x00	; 0
      0083B5 00                    1924 	.db #0x00	; 0
      0083B6 00                    1925 	.db #0x00	; 0
      0083B7 00                    1926 	.db #0x00	; 0
      0083B8 00                    1927 	.db #0x00	; 0
      0083B9 00                    1928 	.db #0x00	; 0
      0083BA                       1929 _doom2_raw:
      0083BA 00                    1930 	.db #0x00	; 0
      0083BB 00                    1931 	.db #0x00	; 0
      0083BC 00                    1932 	.db #0x00	; 0
      0083BD 00                    1933 	.db #0x00	; 0
      0083BE 00                    1934 	.db #0x00	; 0
      0083BF 00                    1935 	.db #0x00	; 0
      0083C0 14                    1936 	.db #0x14	; 20
      0083C1 02                    1937 	.db #0x02	; 2
      0083C2 02                    1938 	.db #0x02	; 2
      0083C3 02                    1939 	.db #0x02	; 2
      0083C4 15                    1940 	.db #0x15	; 21
      0083C5 35                    1941 	.db #0x35	; 53	'5'
      0083C6 35                    1942 	.db #0x35	; 53	'5'
      0083C7 35                    1943 	.db #0x35	; 53	'5'
      0083C8 35                    1944 	.db #0x35	; 53	'5'
      0083C9 35                    1945 	.db #0x35	; 53	'5'
      0083CA 15                    1946 	.db #0x15	; 21
      0083CB 02                    1947 	.db #0x02	; 2
      0083CC 02                    1948 	.db #0x02	; 2
      0083CD 14                    1949 	.db #0x14	; 20
      0083CE 00                    1950 	.db #0x00	; 0
      0083CF 00                    1951 	.db #0x00	; 0
      0083D0 00                    1952 	.db #0x00	; 0
      0083D1 00                    1953 	.db #0x00	; 0
      0083D2 00                    1954 	.db #0x00	; 0
      0083D3 00                    1955 	.db #0x00	; 0
      0083D4 00                    1956 	.db #0x00	; 0
      0083D5 00                    1957 	.db #0x00	; 0
      0083D6 00                    1958 	.db #0x00	; 0
      0083D7 00                    1959 	.db #0x00	; 0
      0083D8 22                    1960 	.db #0x22	; 34
      0083D9 02                    1961 	.db #0x02	; 2
      0083DA 34                    1962 	.db #0x34	; 52	'4'
      0083DB 03                    1963 	.db #0x03	; 3
      0083DC 36                    1964 	.db #0x36	; 54	'6'
      0083DD 38                    1965 	.db #0x38	; 56	'8'
      0083DE 28                    1966 	.db #0x28	; 40
      0083DF 08                    1967 	.db #0x08	; 8
      0083E0 08                    1968 	.db #0x08	; 8
      0083E1 08                    1969 	.db #0x08	; 8
      0083E2 28                    1970 	.db #0x28	; 40
      0083E3 38                    1971 	.db #0x38	; 56	'8'
      0083E4 05                    1972 	.db #0x05	; 5
      0083E5 35                    1973 	.db #0x35	; 53	'5'
      0083E6 02                    1974 	.db #0x02	; 2
      0083E7 34                    1975 	.db #0x34	; 52	'4'
      0083E8 02                    1976 	.db #0x02	; 2
      0083E9 22                    1977 	.db #0x22	; 34
      0083EA 00                    1978 	.db #0x00	; 0
      0083EB 00                    1979 	.db #0x00	; 0
      0083EC 00                    1980 	.db #0x00	; 0
      0083ED 00                    1981 	.db #0x00	; 0
      0083EE 00                    1982 	.db #0x00	; 0
      0083EF 00                    1983 	.db #0x00	; 0
      0083F0 00                    1984 	.db #0x00	; 0
      0083F1 22                    1985 	.db #0x22	; 34
      0083F2 02                    1986 	.db #0x02	; 2
      0083F3 35                    1987 	.db #0x35	; 53	'5'
      0083F4 36                    1988 	.db #0x36	; 54	'6'
      0083F5 38                    1989 	.db #0x38	; 56	'8'
      0083F6 28                    1990 	.db #0x28	; 40
      0083F7 39                    1991 	.db #0x39	; 57	'9'
      0083F8 08                    1992 	.db #0x08	; 8
      0083F9 28                    1993 	.db #0x28	; 40
      0083FA 06                    1994 	.db #0x06	; 6
      0083FB 05                    1995 	.db #0x05	; 5
      0083FC 05                    1996 	.db #0x05	; 5
      0083FD 05                    1997 	.db #0x05	; 5
      0083FE 36                    1998 	.db #0x36	; 54	'6'
      0083FF 36                    1999 	.db #0x36	; 54	'6'
      008400 35                    2000 	.db #0x35	; 53	'5'
      008401 35                    2001 	.db #0x35	; 53	'5'
      008402 34                    2002 	.db #0x34	; 52	'4'
      008403 14                    2003 	.db #0x14	; 20
      008404 22                    2004 	.db #0x22	; 34
      008405 00                    2005 	.db #0x00	; 0
      008406 00                    2006 	.db #0x00	; 0
      008407 00                    2007 	.db #0x00	; 0
      008408 00                    2008 	.db #0x00	; 0
      008409 00                    2009 	.db #0x00	; 0
      00840A 00                    2010 	.db #0x00	; 0
      00840B 22                    2011 	.db #0x22	; 34
      00840C 35                    2012 	.db #0x35	; 53	'5'
      00840D 17                    2013 	.db #0x17	; 23
      00840E 35                    2014 	.db #0x35	; 53	'5'
      00840F 36                    2015 	.db #0x36	; 54	'6'
      008410 05                    2016 	.db #0x05	; 5
      008411 06                    2017 	.db #0x06	; 6
      008412 17                    2018 	.db #0x17	; 23
      008413 38                    2019 	.db #0x38	; 56	'8'
      008414 36                    2020 	.db #0x36	; 54	'6'
      008415 26                    2021 	.db #0x26	; 38
      008416 35                    2022 	.db #0x35	; 53	'5'
      008417 35                    2023 	.db #0x35	; 53	'5'
      008418 35                    2024 	.db #0x35	; 53	'5'
      008419 35                    2025 	.db #0x35	; 53	'5'
      00841A 02                    2026 	.db #0x02	; 2
      00841B 34                    2027 	.db #0x34	; 52	'4'
      00841C 22                    2028 	.db #0x22	; 34
      00841D 22                    2029 	.db #0x22	; 34
      00841E 01                    2030 	.db #0x01	; 1
      00841F 00                    2031 	.db #0x00	; 0
      008420 00                    2032 	.db #0x00	; 0
      008421 00                    2033 	.db #0x00	; 0
      008422 00                    2034 	.db #0x00	; 0
      008423 00                    2035 	.db #0x00	; 0
      008424 01                    2036 	.db #0x01	; 1
      008425 33                    2037 	.db #0x33	; 51	'3'
      008426 02                    2038 	.db #0x02	; 2
      008427 35                    2039 	.db #0x35	; 53	'5'
      008428 02                    2040 	.db #0x02	; 2
      008429 36                    2041 	.db #0x36	; 54	'6'
      00842A 05                    2042 	.db #0x05	; 5
      00842B 36                    2043 	.db #0x36	; 54	'6'
      00842C 36                    2044 	.db #0x36	; 54	'6'
      00842D 36                    2045 	.db #0x36	; 54	'6'
      00842E 36                    2046 	.db #0x36	; 54	'6'
      00842F 14                    2047 	.db #0x14	; 20
      008430 36                    2048 	.db #0x36	; 54	'6'
      008431 02                    2049 	.db #0x02	; 2
      008432 14                    2050 	.db #0x14	; 20
      008433 02                    2051 	.db #0x02	; 2
      008434 14                    2052 	.db #0x14	; 20
      008435 22                    2053 	.db #0x22	; 34
      008436 01                    2054 	.db #0x01	; 1
      008437 01                    2055 	.db #0x01	; 1
      008438 01                    2056 	.db #0x01	; 1
      008439 01                    2057 	.db #0x01	; 1
      00843A 00                    2058 	.db #0x00	; 0
      00843B 00                    2059 	.db #0x00	; 0
      00843C 00                    2060 	.db #0x00	; 0
      00843D 00                    2061 	.db #0x00	; 0
      00843E 01                    2062 	.db #0x01	; 1
      00843F 33                    2063 	.db #0x33	; 51	'3'
      008440 14                    2064 	.db #0x14	; 20
      008441 34                    2065 	.db #0x34	; 52	'4'
      008442 02                    2066 	.db #0x02	; 2
      008443 36                    2067 	.db #0x36	; 54	'6'
      008444 34                    2068 	.db #0x34	; 52	'4'
      008445 05                    2069 	.db #0x05	; 5
      008446 15                    2070 	.db #0x15	; 21
      008447 15                    2071 	.db #0x15	; 21
      008448 36                    2072 	.db #0x36	; 54	'6'
      008449 15                    2073 	.db #0x15	; 21
      00844A 14                    2074 	.db #0x14	; 20
      00844B 15                    2075 	.db #0x15	; 21
      00844C 14                    2076 	.db #0x14	; 20
      00844D 33                    2077 	.db #0x33	; 51	'3'
      00844E 02                    2078 	.db #0x02	; 2
      00844F 01                    2079 	.db #0x01	; 1
      008450 22                    2080 	.db #0x22	; 34
      008451 22                    2081 	.db #0x22	; 34
      008452 33                    2082 	.db #0x33	; 51	'3'
      008453 01                    2083 	.db #0x01	; 1
      008454 00                    2084 	.db #0x00	; 0
      008455 00                    2085 	.db #0x00	; 0
      008456 00                    2086 	.db #0x00	; 0
      008457 00                    2087 	.db #0x00	; 0
      008458 01                    2088 	.db #0x01	; 1
      008459 14                    2089 	.db #0x14	; 20
      00845A 14                    2090 	.db #0x14	; 20
      00845B 35                    2091 	.db #0x35	; 53	'5'
      00845C 35                    2092 	.db #0x35	; 53	'5'
      00845D 34                    2093 	.db #0x34	; 52	'4'
      00845E 36                    2094 	.db #0x36	; 54	'6'
      00845F 34                    2095 	.db #0x34	; 52	'4'
      008460 15                    2096 	.db #0x15	; 21
      008461 35                    2097 	.db #0x35	; 53	'5'
      008462 15                    2098 	.db #0x15	; 21
      008463 15                    2099 	.db #0x15	; 21
      008464 36                    2100 	.db #0x36	; 54	'6'
      008465 36                    2101 	.db #0x36	; 54	'6'
      008466 36                    2102 	.db #0x36	; 54	'6'
      008467 17                    2103 	.db #0x17	; 23
      008468 17                    2104 	.db #0x17	; 23
      008469 15                    2105 	.db #0x15	; 21
      00846A 14                    2106 	.db #0x14	; 20
      00846B 33                    2107 	.db #0x33	; 51	'3'
      00846C 14                    2108 	.db #0x14	; 20
      00846D 01                    2109 	.db #0x01	; 1
      00846E 00                    2110 	.db #0x00	; 0
      00846F 00                    2111 	.db #0x00	; 0
      008470 00                    2112 	.db #0x00	; 0
      008471 00                    2113 	.db #0x00	; 0
      008472 01                    2114 	.db #0x01	; 1
      008473 14                    2115 	.db #0x14	; 20
      008474 34                    2116 	.db #0x34	; 52	'4'
      008475 35                    2117 	.db #0x35	; 53	'5'
      008476 36                    2118 	.db #0x36	; 54	'6'
      008477 35                    2119 	.db #0x35	; 53	'5'
      008478 34                    2120 	.db #0x34	; 52	'4'
      008479 26                    2121 	.db #0x26	; 38
      00847A 34                    2122 	.db #0x34	; 52	'4'
      00847B 35                    2123 	.db #0x35	; 53	'5'
      00847C 36                    2124 	.db #0x36	; 54	'6'
      00847D 26                    2125 	.db #0x26	; 38
      00847E 06                    2126 	.db #0x06	; 6
      00847F 05                    2127 	.db #0x05	; 5
      008480 26                    2128 	.db #0x26	; 38
      008481 36                    2129 	.db #0x36	; 54	'6'
      008482 36                    2130 	.db #0x36	; 54	'6'
      008483 36                    2131 	.db #0x36	; 54	'6'
      008484 15                    2132 	.db #0x15	; 21
      008485 14                    2133 	.db #0x14	; 20
      008486 14                    2134 	.db #0x14	; 20
      008487 01                    2135 	.db #0x01	; 1
      008488 00                    2136 	.db #0x00	; 0
      008489 00                    2137 	.db #0x00	; 0
      00848A 00                    2138 	.db #0x00	; 0
      00848B 00                    2139 	.db #0x00	; 0
      00848C 01                    2140 	.db #0x01	; 1
      00848D 14                    2141 	.db #0x14	; 20
      00848E 02                    2142 	.db #0x02	; 2
      00848F 36                    2143 	.db #0x36	; 54	'6'
      008490 38                    2144 	.db #0x38	; 56	'8'
      008491 06                    2145 	.db #0x06	; 6
      008492 26                    2146 	.db #0x26	; 38
      008493 26                    2147 	.db #0x26	; 38
      008494 06                    2148 	.db #0x06	; 6
      008495 06                    2149 	.db #0x06	; 6
      008496 06                    2150 	.db #0x06	; 6
      008497 06                    2151 	.db #0x06	; 6
      008498 06                    2152 	.db #0x06	; 6
      008499 06                    2153 	.db #0x06	; 6
      00849A 26                    2154 	.db #0x26	; 38
      00849B 26                    2155 	.db #0x26	; 38
      00849C 06                    2156 	.db #0x06	; 6
      00849D 38                    2157 	.db #0x38	; 56	'8'
      00849E 36                    2158 	.db #0x36	; 54	'6'
      00849F 34                    2159 	.db #0x34	; 52	'4'
      0084A0 14                    2160 	.db #0x14	; 20
      0084A1 01                    2161 	.db #0x01	; 1
      0084A2 00                    2162 	.db #0x00	; 0
      0084A3 00                    2163 	.db #0x00	; 0
      0084A4 00                    2164 	.db #0x00	; 0
      0084A5 00                    2165 	.db #0x00	; 0
      0084A6 01                    2166 	.db #0x01	; 1
      0084A7 14                    2167 	.db #0x14	; 20
      0084A8 35                    2168 	.db #0x35	; 53	'5'
      0084A9 05                    2169 	.db #0x05	; 5
      0084AA 08                    2170 	.db #0x08	; 8
      0084AB 39                    2171 	.db #0x39	; 57	'9'
      0084AC 39                    2172 	.db #0x39	; 57	'9'
      0084AD 06                    2173 	.db #0x06	; 6
      0084AE 26                    2174 	.db #0x26	; 38
      0084AF 38                    2175 	.db #0x38	; 56	'8'
      0084B0 38                    2176 	.db #0x38	; 56	'8'
      0084B1 38                    2177 	.db #0x38	; 56	'8'
      0084B2 38                    2178 	.db #0x38	; 56	'8'
      0084B3 26                    2179 	.db #0x26	; 38
      0084B4 06                    2180 	.db #0x06	; 6
      0084B5 39                    2181 	.db #0x39	; 57	'9'
      0084B6 39                    2182 	.db #0x39	; 57	'9'
      0084B7 08                    2183 	.db #0x08	; 8
      0084B8 05                    2184 	.db #0x05	; 5
      0084B9 02                    2185 	.db #0x02	; 2
      0084BA 14                    2186 	.db #0x14	; 20
      0084BB 01                    2187 	.db #0x01	; 1
      0084BC 00                    2188 	.db #0x00	; 0
      0084BD 00                    2189 	.db #0x00	; 0
      0084BE 00                    2190 	.db #0x00	; 0
      0084BF 00                    2191 	.db #0x00	; 0
      0084C0 01                    2192 	.db #0x01	; 1
      0084C1 14                    2193 	.db #0x14	; 20
      0084C2 35                    2194 	.db #0x35	; 53	'5'
      0084C3 05                    2195 	.db #0x05	; 5
      0084C4 08                    2196 	.db #0x08	; 8
      0084C5 0C                    2197 	.db #0x0c	; 12
      0084C6 2B                    2198 	.db #0x2b	; 43
      0084C7 08                    2199 	.db #0x08	; 8
      0084C8 28                    2200 	.db #0x28	; 40
      0084C9 26                    2201 	.db #0x26	; 38
      0084CA 36                    2202 	.db #0x36	; 54	'6'
      0084CB 36                    2203 	.db #0x36	; 54	'6'
      0084CC 26                    2204 	.db #0x26	; 38
      0084CD 28                    2205 	.db #0x28	; 40
      0084CE 08                    2206 	.db #0x08	; 8
      0084CF 2B                    2207 	.db #0x2b	; 43
      0084D0 0C                    2208 	.db #0x0c	; 12
      0084D1 08                    2209 	.db #0x08	; 8
      0084D2 05                    2210 	.db #0x05	; 5
      0084D3 35                    2211 	.db #0x35	; 53	'5'
      0084D4 14                    2212 	.db #0x14	; 20
      0084D5 01                    2213 	.db #0x01	; 1
      0084D6 00                    2214 	.db #0x00	; 0
      0084D7 00                    2215 	.db #0x00	; 0
      0084D8 00                    2216 	.db #0x00	; 0
      0084D9 00                    2217 	.db #0x00	; 0
      0084DA 01                    2218 	.db #0x01	; 1
      0084DB 14                    2219 	.db #0x14	; 20
      0084DC 35                    2220 	.db #0x35	; 53	'5'
      0084DD 06                    2221 	.db #0x06	; 6
      0084DE 2B                    2222 	.db #0x2b	; 43
      0084DF 2F                    2223 	.db #0x2f	; 47
      0084E0 2F                    2224 	.db #0x2f	; 47
      0084E1 2B                    2225 	.db #0x2b	; 43
      0084E2 2B                    2226 	.db #0x2b	; 43
      0084E3 08                    2227 	.db #0x08	; 8
      0084E4 29                    2228 	.db #0x29	; 41
      0084E5 29                    2229 	.db #0x29	; 41
      0084E6 08                    2230 	.db #0x08	; 8
      0084E7 2B                    2231 	.db #0x2b	; 43
      0084E8 2B                    2232 	.db #0x2b	; 43
      0084E9 2F                    2233 	.db #0x2f	; 47
      0084EA 2F                    2234 	.db #0x2f	; 47
      0084EB 2B                    2235 	.db #0x2b	; 43
      0084EC 06                    2236 	.db #0x06	; 6
      0084ED 35                    2237 	.db #0x35	; 53	'5'
      0084EE 14                    2238 	.db #0x14	; 20
      0084EF 01                    2239 	.db #0x01	; 1
      0084F0 00                    2240 	.db #0x00	; 0
      0084F1 00                    2241 	.db #0x00	; 0
      0084F2 00                    2242 	.db #0x00	; 0
      0084F3 06                    2243 	.db #0x06	; 6
      0084F4 15                    2244 	.db #0x15	; 21
      0084F5 14                    2245 	.db #0x14	; 20
      0084F6 35                    2246 	.db #0x35	; 53	'5'
      0084F7 15                    2247 	.db #0x15	; 21
      0084F8 15                    2248 	.db #0x15	; 21
      0084F9 34                    2249 	.db #0x34	; 52	'4'
      0084FA 26                    2250 	.db #0x26	; 38
      0084FB 0A                    2251 	.db #0x0a	; 10
      0084FC 06                    2252 	.db #0x06	; 6
      0084FD 35                    2253 	.db #0x35	; 53	'5'
      0084FE 06                    2254 	.db #0x06	; 6
      0084FF 06                    2255 	.db #0x06	; 6
      008500 35                    2256 	.db #0x35	; 53	'5'
      008501 06                    2257 	.db #0x06	; 6
      008502 0A                    2258 	.db #0x0a	; 10
      008503 26                    2259 	.db #0x26	; 38
      008504 34                    2260 	.db #0x34	; 52	'4'
      008505 15                    2261 	.db #0x15	; 21
      008506 15                    2262 	.db #0x15	; 21
      008507 35                    2263 	.db #0x35	; 53	'5'
      008508 14                    2264 	.db #0x14	; 20
      008509 15                    2265 	.db #0x15	; 21
      00850A 06                    2266 	.db #0x06	; 6
      00850B 00                    2267 	.db #0x00	; 0
      00850C 00                    2268 	.db #0x00	; 0
      00850D 06                    2269 	.db #0x06	; 6
      00850E 15                    2270 	.db #0x15	; 21
      00850F 04                    2271 	.db #0x04	; 4
      008510 36                    2272 	.db #0x36	; 54	'6'
      008511 38                    2273 	.db #0x38	; 56	'8'
      008512 02                    2274 	.db #0x02	; 2
      008513 33                    2275 	.db #0x33	; 51	'3'
      008514 33                    2276 	.db #0x33	; 51	'3'
      008515 33                    2277 	.db #0x33	; 51	'3'
      008516 14                    2278 	.db #0x14	; 20
      008517 33                    2279 	.db #0x33	; 51	'3'
      008518 36                    2280 	.db #0x36	; 54	'6'
      008519 36                    2281 	.db #0x36	; 54	'6'
      00851A 33                    2282 	.db #0x33	; 51	'3'
      00851B 14                    2283 	.db #0x14	; 20
      00851C 33                    2284 	.db #0x33	; 51	'3'
      00851D 33                    2285 	.db #0x33	; 51	'3'
      00851E 33                    2286 	.db #0x33	; 51	'3'
      00851F 02                    2287 	.db #0x02	; 2
      008520 38                    2288 	.db #0x38	; 56	'8'
      008521 36                    2289 	.db #0x36	; 54	'6'
      008522 04                    2290 	.db #0x04	; 4
      008523 15                    2291 	.db #0x15	; 21
      008524 06                    2292 	.db #0x06	; 6
      008525 00                    2293 	.db #0x00	; 0
      008526 00                    2294 	.db #0x00	; 0
      008527 36                    2295 	.db #0x36	; 54	'6'
      008528 15                    2296 	.db #0x15	; 21
      008529 07                    2297 	.db #0x07	; 7
      00852A 06                    2298 	.db #0x06	; 6
      00852B 35                    2299 	.db #0x35	; 53	'5'
      00852C 2C                    2300 	.db #0x2c	; 44
      00852D 00                    2301 	.db #0x00	; 0
      00852E 2C                    2302 	.db #0x2c	; 44
      00852F 27                    2303 	.db #0x27	; 39
      008530 00                    2304 	.db #0x00	; 0
      008531 34                    2305 	.db #0x34	; 52	'4'
      008532 29                    2306 	.db #0x29	; 41
      008533 29                    2307 	.db #0x29	; 41
      008534 34                    2308 	.db #0x34	; 52	'4'
      008535 00                    2309 	.db #0x00	; 0
      008536 2C                    2310 	.db #0x2c	; 44
      008537 00                    2311 	.db #0x00	; 0
      008538 2C                    2312 	.db #0x2c	; 44
      008539 11                    2313 	.db #0x11	; 17
      00853A 35                    2314 	.db #0x35	; 53	'5'
      00853B 06                    2315 	.db #0x06	; 6
      00853C 07                    2316 	.db #0x07	; 7
      00853D 15                    2317 	.db #0x15	; 21
      00853E 36                    2318 	.db #0x36	; 54	'6'
      00853F 00                    2319 	.db #0x00	; 0
      008540 00                    2320 	.db #0x00	; 0
      008541 15                    2321 	.db #0x15	; 21
      008542 02                    2322 	.db #0x02	; 2
      008543 17                    2323 	.db #0x17	; 23
      008544 06                    2324 	.db #0x06	; 6
      008545 36                    2325 	.db #0x36	; 54	'6'
      008546 38                    2326 	.db #0x38	; 56	'8'
      008547 1C                    2327 	.db #0x1c	; 28
      008548 1A                    2328 	.db #0x1a	; 26
      008549 15                    2329 	.db #0x15	; 21
      00854A 02                    2330 	.db #0x02	; 2
      00854B 36                    2331 	.db #0x36	; 54	'6'
      00854C 08                    2332 	.db #0x08	; 8
      00854D 2B                    2333 	.db #0x2b	; 43
      00854E 36                    2334 	.db #0x36	; 54	'6'
      00854F 02                    2335 	.db #0x02	; 2
      008550 15                    2336 	.db #0x15	; 21
      008551 1A                    2337 	.db #0x1a	; 26
      008552 1C                    2338 	.db #0x1c	; 28
      008553 38                    2339 	.db #0x38	; 56	'8'
      008554 36                    2340 	.db #0x36	; 54	'6'
      008555 06                    2341 	.db #0x06	; 6
      008556 17                    2342 	.db #0x17	; 23
      008557 02                    2343 	.db #0x02	; 2
      008558 15                    2344 	.db #0x15	; 21
      008559 00                    2345 	.db #0x00	; 0
      00855A 00                    2346 	.db #0x00	; 0
      00855B 17                    2347 	.db #0x17	; 23
      00855C 02                    2348 	.db #0x02	; 2
      00855D 17                    2349 	.db #0x17	; 23
      00855E 2E                    2350 	.db #0x2e	; 46
      00855F 29                    2351 	.db #0x29	; 41
      008560 28                    2352 	.db #0x28	; 40
      008561 38                    2353 	.db #0x38	; 56	'8'
      008562 36                    2354 	.db #0x36	; 54	'6'
      008563 38                    2355 	.db #0x38	; 56	'8'
      008564 39                    2356 	.db #0x39	; 57	'9'
      008565 29                    2357 	.db #0x29	; 41
      008566 09                    2358 	.db #0x09	; 9
      008567 0D                    2359 	.db #0x0d	; 13
      008568 29                    2360 	.db #0x29	; 41
      008569 39                    2361 	.db #0x39	; 57	'9'
      00856A 38                    2362 	.db #0x38	; 56	'8'
      00856B 36                    2363 	.db #0x36	; 54	'6'
      00856C 38                    2364 	.db #0x38	; 56	'8'
      00856D 28                    2365 	.db #0x28	; 40
      00856E 29                    2366 	.db #0x29	; 41
      00856F 2E                    2367 	.db #0x2e	; 46
      008570 17                    2368 	.db #0x17	; 23
      008571 02                    2369 	.db #0x02	; 2
      008572 17                    2370 	.db #0x17	; 23
      008573 00                    2371 	.db #0x00	; 0
      008574 00                    2372 	.db #0x00	; 0
      008575 36                    2373 	.db #0x36	; 54	'6'
      008576 02                    2374 	.db #0x02	; 2
      008577 36                    2375 	.db #0x36	; 54	'6'
      008578 08                    2376 	.db #0x08	; 8
      008579 0A                    2377 	.db #0x0a	; 10
      00857A 0C                    2378 	.db #0x0c	; 12
      00857B 0A                    2379 	.db #0x0a	; 10
      00857C 39                    2380 	.db #0x39	; 57	'9'
      00857D 09                    2381 	.db #0x09	; 9
      00857E 2F                    2382 	.db #0x2f	; 47
      00857F 2B                    2383 	.db #0x2b	; 43
      008580 09                    2384 	.db #0x09	; 9
      008581 0D                    2385 	.db #0x0d	; 13
      008582 2B                    2386 	.db #0x2b	; 43
      008583 2F                    2387 	.db #0x2f	; 47
      008584 09                    2388 	.db #0x09	; 9
      008585 39                    2389 	.db #0x39	; 57	'9'
      008586 0A                    2390 	.db #0x0a	; 10
      008587 0C                    2391 	.db #0x0c	; 12
      008588 0A                    2392 	.db #0x0a	; 10
      008589 08                    2393 	.db #0x08	; 8
      00858A 36                    2394 	.db #0x36	; 54	'6'
      00858B 02                    2395 	.db #0x02	; 2
      00858C 36                    2396 	.db #0x36	; 54	'6'
      00858D 00                    2397 	.db #0x00	; 0
      00858E 00                    2398 	.db #0x00	; 0
      00858F 00                    2399 	.db #0x00	; 0
      008590 02                    2400 	.db #0x02	; 2
      008591 17                    2401 	.db #0x17	; 23
      008592 26                    2402 	.db #0x26	; 38
      008593 38                    2403 	.db #0x38	; 56	'8'
      008594 28                    2404 	.db #0x28	; 40
      008595 29                    2405 	.db #0x29	; 41
      008596 09                    2406 	.db #0x09	; 9
      008597 1E                    2407 	.db #0x1e	; 30
      008598 0A                    2408 	.db #0x0a	; 10
      008599 29                    2409 	.db #0x29	; 41
      00859A 0D                    2410 	.db #0x0d	; 13
      00859B 20                    2411 	.db #0x20	; 32
      00859C 29                    2412 	.db #0x29	; 41
      00859D 0A                    2413 	.db #0x0a	; 10
      00859E 1E                    2414 	.db #0x1e	; 30
      00859F 09                    2415 	.db #0x09	; 9
      0085A0 29                    2416 	.db #0x29	; 41
      0085A1 28                    2417 	.db #0x28	; 40
      0085A2 38                    2418 	.db #0x38	; 56	'8'
      0085A3 26                    2419 	.db #0x26	; 38
      0085A4 17                    2420 	.db #0x17	; 23
      0085A5 02                    2421 	.db #0x02	; 2
      0085A6 00                    2422 	.db #0x00	; 0
      0085A7 00                    2423 	.db #0x00	; 0
      0085A8 00                    2424 	.db #0x00	; 0
      0085A9 00                    2425 	.db #0x00	; 0
      0085AA 02                    2426 	.db #0x02	; 2
      0085AB 35                    2427 	.db #0x35	; 53	'5'
      0085AC 05                    2428 	.db #0x05	; 5
      0085AD 26                    2429 	.db #0x26	; 38
      0085AE 28                    2430 	.db #0x28	; 40
      0085AF 0C                    2431 	.db #0x0c	; 12
      0085B0 2D                    2432 	.db #0x2d	; 45
      0085B1 29                    2433 	.db #0x29	; 41
      0085B2 38                    2434 	.db #0x38	; 56	'8'
      0085B3 05                    2435 	.db #0x05	; 5
      0085B4 0B                    2436 	.db #0x0b	; 11
      0085B5 0B                    2437 	.db #0x0b	; 11
      0085B6 05                    2438 	.db #0x05	; 5
      0085B7 38                    2439 	.db #0x38	; 56	'8'
      0085B8 29                    2440 	.db #0x29	; 41
      0085B9 2D                    2441 	.db #0x2d	; 45
      0085BA 0C                    2442 	.db #0x0c	; 12
      0085BB 28                    2443 	.db #0x28	; 40
      0085BC 26                    2444 	.db #0x26	; 38
      0085BD 05                    2445 	.db #0x05	; 5
      0085BE 35                    2446 	.db #0x35	; 53	'5'
      0085BF 02                    2447 	.db #0x02	; 2
      0085C0 00                    2448 	.db #0x00	; 0
      0085C1 00                    2449 	.db #0x00	; 0
      0085C2 00                    2450 	.db #0x00	; 0
      0085C3 00                    2451 	.db #0x00	; 0
      0085C4 00                    2452 	.db #0x00	; 0
      0085C5 35                    2453 	.db #0x35	; 53	'5'
      0085C6 06                    2454 	.db #0x06	; 6
      0085C7 05                    2455 	.db #0x05	; 5
      0085C8 29                    2456 	.db #0x29	; 41
      0085C9 2F                    2457 	.db #0x2f	; 47
      0085CA 2B                    2458 	.db #0x2b	; 43
      0085CB 28                    2459 	.db #0x28	; 40
      0085CC 34                    2460 	.db #0x34	; 52	'4'
      0085CD 35                    2461 	.db #0x35	; 53	'5'
      0085CE 17                    2462 	.db #0x17	; 23
      0085CF 17                    2463 	.db #0x17	; 23
      0085D0 35                    2464 	.db #0x35	; 53	'5'
      0085D1 34                    2465 	.db #0x34	; 52	'4'
      0085D2 28                    2466 	.db #0x28	; 40
      0085D3 2B                    2467 	.db #0x2b	; 43
      0085D4 2F                    2468 	.db #0x2f	; 47
      0085D5 29                    2469 	.db #0x29	; 41
      0085D6 05                    2470 	.db #0x05	; 5
      0085D7 06                    2471 	.db #0x06	; 6
      0085D8 35                    2472 	.db #0x35	; 53	'5'
      0085D9 00                    2473 	.db #0x00	; 0
      0085DA 00                    2474 	.db #0x00	; 0
      0085DB 00                    2475 	.db #0x00	; 0
      0085DC 00                    2476 	.db #0x00	; 0
      0085DD 00                    2477 	.db #0x00	; 0
      0085DE 00                    2478 	.db #0x00	; 0
      0085DF 02                    2479 	.db #0x02	; 2
      0085E0 39                    2480 	.db #0x39	; 57	'9'
      0085E1 05                    2481 	.db #0x05	; 5
      0085E2 2B                    2482 	.db #0x2b	; 43
      0085E3 2D                    2483 	.db #0x2d	; 45
      0085E4 08                    2484 	.db #0x08	; 8
      0085E5 08                    2485 	.db #0x08	; 8
      0085E6 29                    2486 	.db #0x29	; 41
      0085E7 28                    2487 	.db #0x28	; 40
      0085E8 26                    2488 	.db #0x26	; 38
      0085E9 26                    2489 	.db #0x26	; 38
      0085EA 28                    2490 	.db #0x28	; 40
      0085EB 29                    2491 	.db #0x29	; 41
      0085EC 08                    2492 	.db #0x08	; 8
      0085ED 08                    2493 	.db #0x08	; 8
      0085EE 2D                    2494 	.db #0x2d	; 45
      0085EF 2B                    2495 	.db #0x2b	; 43
      0085F0 05                    2496 	.db #0x05	; 5
      0085F1 39                    2497 	.db #0x39	; 57	'9'
      0085F2 02                    2498 	.db #0x02	; 2
      0085F3 00                    2499 	.db #0x00	; 0
      0085F4 00                    2500 	.db #0x00	; 0
      0085F5 00                    2501 	.db #0x00	; 0
      0085F6 00                    2502 	.db #0x00	; 0
      0085F7 00                    2503 	.db #0x00	; 0
      0085F8 00                    2504 	.db #0x00	; 0
      0085F9 34                    2505 	.db #0x34	; 52	'4'
      0085FA 38                    2506 	.db #0x38	; 56	'8'
      0085FB 26                    2507 	.db #0x26	; 38
      0085FC 29                    2508 	.db #0x29	; 41
      0085FD 2B                    2509 	.db #0x2b	; 43
      0085FE 08                    2510 	.db #0x08	; 8
      0085FF 29                    2511 	.db #0x29	; 41
      008600 2D                    2512 	.db #0x2d	; 45
      008601 3D                    2513 	.db #0x3d	; 61
      008602 0A                    2514 	.db #0x0a	; 10
      008603 0A                    2515 	.db #0x0a	; 10
      008604 3D                    2516 	.db #0x3d	; 61
      008605 2D                    2517 	.db #0x2d	; 45
      008606 29                    2518 	.db #0x29	; 41
      008607 08                    2519 	.db #0x08	; 8
      008608 2B                    2520 	.db #0x2b	; 43
      008609 29                    2521 	.db #0x29	; 41
      00860A 26                    2522 	.db #0x26	; 38
      00860B 38                    2523 	.db #0x38	; 56	'8'
      00860C 34                    2524 	.db #0x34	; 52	'4'
      00860D 00                    2525 	.db #0x00	; 0
      00860E 00                    2526 	.db #0x00	; 0
      00860F 00                    2527 	.db #0x00	; 0
      008610 00                    2528 	.db #0x00	; 0
      008611 00                    2529 	.db #0x00	; 0
      008612 00                    2530 	.db #0x00	; 0
      008613 00                    2531 	.db #0x00	; 0
      008614 17                    2532 	.db #0x17	; 23
      008615 38                    2533 	.db #0x38	; 56	'8'
      008616 39                    2534 	.db #0x39	; 57	'9'
      008617 29                    2535 	.db #0x29	; 41
      008618 36                    2536 	.db #0x36	; 54	'6'
      008619 35                    2537 	.db #0x35	; 53	'5'
      00861A 23                    2538 	.db #0x23	; 35
      00861B 23                    2539 	.db #0x23	; 35
      00861C 23                    2540 	.db #0x23	; 35
      00861D 23                    2541 	.db #0x23	; 35
      00861E 23                    2542 	.db #0x23	; 35
      00861F 23                    2543 	.db #0x23	; 35
      008620 35                    2544 	.db #0x35	; 53	'5'
      008621 36                    2545 	.db #0x36	; 54	'6'
      008622 29                    2546 	.db #0x29	; 41
      008623 39                    2547 	.db #0x39	; 57	'9'
      008624 38                    2548 	.db #0x38	; 56	'8'
      008625 17                    2549 	.db #0x17	; 23
      008626 00                    2550 	.db #0x00	; 0
      008627 00                    2551 	.db #0x00	; 0
      008628 00                    2552 	.db #0x00	; 0
      008629 00                    2553 	.db #0x00	; 0
      00862A 00                    2554 	.db #0x00	; 0
      00862B 00                    2555 	.db #0x00	; 0
      00862C 00                    2556 	.db #0x00	; 0
      00862D 00                    2557 	.db #0x00	; 0
      00862E 34                    2558 	.db #0x34	; 52	'4'
      00862F 36                    2559 	.db #0x36	; 54	'6'
      008630 06                    2560 	.db #0x06	; 6
      008631 39                    2561 	.db #0x39	; 57	'9'
      008632 39                    2562 	.db #0x39	; 57	'9'
      008633 39                    2563 	.db #0x39	; 57	'9'
      008634 29                    2564 	.db #0x29	; 41
      008635 2B                    2565 	.db #0x2b	; 43
      008636 09                    2566 	.db #0x09	; 9
      008637 09                    2567 	.db #0x09	; 9
      008638 2B                    2568 	.db #0x2b	; 43
      008639 29                    2569 	.db #0x29	; 41
      00863A 39                    2570 	.db #0x39	; 57	'9'
      00863B 39                    2571 	.db #0x39	; 57	'9'
      00863C 39                    2572 	.db #0x39	; 57	'9'
      00863D 06                    2573 	.db #0x06	; 6
      00863E 36                    2574 	.db #0x36	; 54	'6'
      00863F 34                    2575 	.db #0x34	; 52	'4'
      008640 00                    2576 	.db #0x00	; 0
      008641 00                    2577 	.db #0x00	; 0
      008642 00                    2578 	.db #0x00	; 0
      008643 00                    2579 	.db #0x00	; 0
      008644 00                    2580 	.db #0x00	; 0
      008645 00                    2581 	.db #0x00	; 0
      008646 00                    2582 	.db #0x00	; 0
      008647 00                    2583 	.db #0x00	; 0
      008648 00                    2584 	.db #0x00	; 0
      008649 15                    2585 	.db #0x15	; 21
      00864A 38                    2586 	.db #0x38	; 56	'8'
      00864B 08                    2587 	.db #0x08	; 8
      00864C 0A                    2588 	.db #0x0a	; 10
      00864D 39                    2589 	.db #0x39	; 57	'9'
      00864E 38                    2590 	.db #0x38	; 56	'8'
      00864F 36                    2591 	.db #0x36	; 54	'6'
      008650 03                    2592 	.db #0x03	; 3
      008651 03                    2593 	.db #0x03	; 3
      008652 36                    2594 	.db #0x36	; 54	'6'
      008653 38                    2595 	.db #0x38	; 56	'8'
      008654 39                    2596 	.db #0x39	; 57	'9'
      008655 0A                    2597 	.db #0x0a	; 10
      008656 08                    2598 	.db #0x08	; 8
      008657 38                    2599 	.db #0x38	; 56	'8'
      008658 15                    2600 	.db #0x15	; 21
      008659 00                    2601 	.db #0x00	; 0
      00865A 00                    2602 	.db #0x00	; 0
      00865B 00                    2603 	.db #0x00	; 0
      00865C 00                    2604 	.db #0x00	; 0
      00865D 00                    2605 	.db #0x00	; 0
      00865E 00                    2606 	.db #0x00	; 0
      00865F 00                    2607 	.db #0x00	; 0
      008660 00                    2608 	.db #0x00	; 0
      008661 00                    2609 	.db #0x00	; 0
      008662 00                    2610 	.db #0x00	; 0
      008663 00                    2611 	.db #0x00	; 0
      008664 15                    2612 	.db #0x15	; 21
      008665 38                    2613 	.db #0x38	; 56	'8'
      008666 08                    2614 	.db #0x08	; 8
      008667 0A                    2615 	.db #0x0a	; 10
      008668 39                    2616 	.db #0x39	; 57	'9'
      008669 39                    2617 	.db #0x39	; 57	'9'
      00866A 2B                    2618 	.db #0x2b	; 43
      00866B 2B                    2619 	.db #0x2b	; 43
      00866C 39                    2620 	.db #0x39	; 57	'9'
      00866D 39                    2621 	.db #0x39	; 57	'9'
      00866E 0A                    2622 	.db #0x0a	; 10
      00866F 08                    2623 	.db #0x08	; 8
      008670 38                    2624 	.db #0x38	; 56	'8'
      008671 15                    2625 	.db #0x15	; 21
      008672 00                    2626 	.db #0x00	; 0
      008673 00                    2627 	.db #0x00	; 0
      008674 00                    2628 	.db #0x00	; 0
      008675 00                    2629 	.db #0x00	; 0
      008676 00                    2630 	.db #0x00	; 0
      008677 00                    2631 	.db #0x00	; 0
      008678 00                    2632 	.db #0x00	; 0
      008679 00                    2633 	.db #0x00	; 0
      00867A 00                    2634 	.db #0x00	; 0
      00867B 00                    2635 	.db #0x00	; 0
      00867C 00                    2636 	.db #0x00	; 0
      00867D 00                    2637 	.db #0x00	; 0
      00867E 00                    2638 	.db #0x00	; 0
      00867F 34                    2639 	.db #0x34	; 52	'4'
      008680 17                    2640 	.db #0x17	; 23
      008681 06                    2641 	.db #0x06	; 6
      008682 29                    2642 	.db #0x29	; 41
      008683 2B                    2643 	.db #0x2b	; 43
      008684 3D                    2644 	.db #0x3d	; 61
      008685 3D                    2645 	.db #0x3d	; 61
      008686 2B                    2646 	.db #0x2b	; 43
      008687 29                    2647 	.db #0x29	; 41
      008688 06                    2648 	.db #0x06	; 6
      008689 17                    2649 	.db #0x17	; 23
      00868A 34                    2650 	.db #0x34	; 52	'4'
      00868B 00                    2651 	.db #0x00	; 0
      00868C 00                    2652 	.db #0x00	; 0
      00868D 00                    2653 	.db #0x00	; 0
      00868E 00                    2654 	.db #0x00	; 0
      00868F 00                    2655 	.db #0x00	; 0
      008690 00                    2656 	.db #0x00	; 0
      008691 00                    2657 	.db #0x00	; 0
      008692 00                    2658 	.db #0x00	; 0
      008693 00                    2659 	.db #0x00	; 0
      008694 00                    2660 	.db #0x00	; 0
      008695 00                    2661 	.db #0x00	; 0
      008696 00                    2662 	.db #0x00	; 0
      008697 00                    2663 	.db #0x00	; 0
      008698 00                    2664 	.db #0x00	; 0
      008699 00                    2665 	.db #0x00	; 0
      00869A 00                    2666 	.db #0x00	; 0
      00869B 15                    2667 	.db #0x15	; 21
      00869C 36                    2668 	.db #0x36	; 54	'6'
      00869D 26                    2669 	.db #0x26	; 38
      00869E 26                    2670 	.db #0x26	; 38
      00869F 26                    2671 	.db #0x26	; 38
      0086A0 26                    2672 	.db #0x26	; 38
      0086A1 36                    2673 	.db #0x36	; 54	'6'
      0086A2 15                    2674 	.db #0x15	; 21
      0086A3 00                    2675 	.db #0x00	; 0
      0086A4 00                    2676 	.db #0x00	; 0
      0086A5 00                    2677 	.db #0x00	; 0
      0086A6 00                    2678 	.db #0x00	; 0
      0086A7 00                    2679 	.db #0x00	; 0
      0086A8 00                    2680 	.db #0x00	; 0
      0086A9 00                    2681 	.db #0x00	; 0
      0086AA 00                    2682 	.db #0x00	; 0
      0086AB 00                    2683 	.db #0x00	; 0
      0086AC 00                    2684 	.db #0x00	; 0
      0086AD 00                    2685 	.db #0x00	; 0
      0086AE 00                    2686 	.db #0x00	; 0
      0086AF 00                    2687 	.db #0x00	; 0
      0086B0 00                    2688 	.db #0x00	; 0
      0086B1 00                    2689 	.db #0x00	; 0
      0086B2 00                    2690 	.db #0x00	; 0
      0086B3 00                    2691 	.db #0x00	; 0
      0086B4 00                    2692 	.db #0x00	; 0
      0086B5 00                    2693 	.db #0x00	; 0
      0086B6 00                    2694 	.db #0x00	; 0
      0086B7 00                    2695 	.db #0x00	; 0
      0086B8 00                    2696 	.db #0x00	; 0
      0086B9 00                    2697 	.db #0x00	; 0
      0086BA 00                    2698 	.db #0x00	; 0
      0086BB 00                    2699 	.db #0x00	; 0
      0086BC 00                    2700 	.db #0x00	; 0
      0086BD 00                    2701 	.db #0x00	; 0
      0086BE 00                    2702 	.db #0x00	; 0
      0086BF 00                    2703 	.db #0x00	; 0
      0086C0 00                    2704 	.db #0x00	; 0
      0086C1 00                    2705 	.db #0x00	; 0
      0086C2 00                    2706 	.db #0x00	; 0
      0086C3 00                    2707 	.db #0x00	; 0
      0086C4 00                    2708 	.db #0x00	; 0
      0086C5                       2709 _doom3_raw:
      0086C5 00                    2710 	.db #0x00	; 0
      0086C6 00                    2711 	.db #0x00	; 0
      0086C7 00                    2712 	.db #0x00	; 0
      0086C8 00                    2713 	.db #0x00	; 0
      0086C9 00                    2714 	.db #0x00	; 0
      0086CA 00                    2715 	.db #0x00	; 0
      0086CB 14                    2716 	.db #0x14	; 20
      0086CC 02                    2717 	.db #0x02	; 2
      0086CD 02                    2718 	.db #0x02	; 2
      0086CE 15                    2719 	.db #0x15	; 21
      0086CF 35                    2720 	.db #0x35	; 53	'5'
      0086D0 35                    2721 	.db #0x35	; 53	'5'
      0086D1 35                    2722 	.db #0x35	; 53	'5'
      0086D2 35                    2723 	.db #0x35	; 53	'5'
      0086D3 35                    2724 	.db #0x35	; 53	'5'
      0086D4 35                    2725 	.db #0x35	; 53	'5'
      0086D5 15                    2726 	.db #0x15	; 21
      0086D6 02                    2727 	.db #0x02	; 2
      0086D7 02                    2728 	.db #0x02	; 2
      0086D8 14                    2729 	.db #0x14	; 20
      0086D9 00                    2730 	.db #0x00	; 0
      0086DA 00                    2731 	.db #0x00	; 0
      0086DB 00                    2732 	.db #0x00	; 0
      0086DC 00                    2733 	.db #0x00	; 0
      0086DD 00                    2734 	.db #0x00	; 0
      0086DE 00                    2735 	.db #0x00	; 0
      0086DF 00                    2736 	.db #0x00	; 0
      0086E0 00                    2737 	.db #0x00	; 0
      0086E1 00                    2738 	.db #0x00	; 0
      0086E2 00                    2739 	.db #0x00	; 0
      0086E3 22                    2740 	.db #0x22	; 34
      0086E4 02                    2741 	.db #0x02	; 2
      0086E5 34                    2742 	.db #0x34	; 52	'4'
      0086E6 02                    2743 	.db #0x02	; 2
      0086E7 15                    2744 	.db #0x15	; 21
      0086E8 35                    2745 	.db #0x35	; 53	'5'
      0086E9 36                    2746 	.db #0x36	; 54	'6'
      0086EA 05                    2747 	.db #0x05	; 5
      0086EB 05                    2748 	.db #0x05	; 5
      0086EC 05                    2749 	.db #0x05	; 5
      0086ED 05                    2750 	.db #0x05	; 5
      0086EE 36                    2751 	.db #0x36	; 54	'6'
      0086EF 35                    2752 	.db #0x35	; 53	'5'
      0086F0 15                    2753 	.db #0x15	; 21
      0086F1 02                    2754 	.db #0x02	; 2
      0086F2 34                    2755 	.db #0x34	; 52	'4'
      0086F3 02                    2756 	.db #0x02	; 2
      0086F4 22                    2757 	.db #0x22	; 34
      0086F5 00                    2758 	.db #0x00	; 0
      0086F6 00                    2759 	.db #0x00	; 0
      0086F7 00                    2760 	.db #0x00	; 0
      0086F8 00                    2761 	.db #0x00	; 0
      0086F9 00                    2762 	.db #0x00	; 0
      0086FA 00                    2763 	.db #0x00	; 0
      0086FB 00                    2764 	.db #0x00	; 0
      0086FC 22                    2765 	.db #0x22	; 34
      0086FD 14                    2766 	.db #0x14	; 20
      0086FE 15                    2767 	.db #0x15	; 21
      0086FF 35                    2768 	.db #0x35	; 53	'5'
      008700 35                    2769 	.db #0x35	; 53	'5'
      008701 35                    2770 	.db #0x35	; 53	'5'
      008702 36                    2771 	.db #0x36	; 54	'6'
      008703 05                    2772 	.db #0x05	; 5
      008704 05                    2773 	.db #0x05	; 5
      008705 05                    2774 	.db #0x05	; 5
      008706 05                    2775 	.db #0x05	; 5
      008707 05                    2776 	.db #0x05	; 5
      008708 05                    2777 	.db #0x05	; 5
      008709 36                    2778 	.db #0x36	; 54	'6'
      00870A 35                    2779 	.db #0x35	; 53	'5'
      00870B 35                    2780 	.db #0x35	; 53	'5'
      00870C 35                    2781 	.db #0x35	; 53	'5'
      00870D 15                    2782 	.db #0x15	; 21
      00870E 14                    2783 	.db #0x14	; 20
      00870F 22                    2784 	.db #0x22	; 34
      008710 00                    2785 	.db #0x00	; 0
      008711 00                    2786 	.db #0x00	; 0
      008712 00                    2787 	.db #0x00	; 0
      008713 00                    2788 	.db #0x00	; 0
      008714 00                    2789 	.db #0x00	; 0
      008715 00                    2790 	.db #0x00	; 0
      008716 22                    2791 	.db #0x22	; 34
      008717 14                    2792 	.db #0x14	; 20
      008718 15                    2793 	.db #0x15	; 21
      008719 35                    2794 	.db #0x35	; 53	'5'
      00871A 35                    2795 	.db #0x35	; 53	'5'
      00871B 17                    2796 	.db #0x17	; 23
      00871C 36                    2797 	.db #0x36	; 54	'6'
      00871D 05                    2798 	.db #0x05	; 5
      00871E 05                    2799 	.db #0x05	; 5
      00871F 05                    2800 	.db #0x05	; 5
      008720 05                    2801 	.db #0x05	; 5
      008721 05                    2802 	.db #0x05	; 5
      008722 05                    2803 	.db #0x05	; 5
      008723 36                    2804 	.db #0x36	; 54	'6'
      008724 35                    2805 	.db #0x35	; 53	'5'
      008725 35                    2806 	.db #0x35	; 53	'5'
      008726 35                    2807 	.db #0x35	; 53	'5'
      008727 15                    2808 	.db #0x15	; 21
      008728 14                    2809 	.db #0x14	; 20
      008729 01                    2810 	.db #0x01	; 1
      00872A 00                    2811 	.db #0x00	; 0
      00872B 00                    2812 	.db #0x00	; 0
      00872C 00                    2813 	.db #0x00	; 0
      00872D 00                    2814 	.db #0x00	; 0
      00872E 00                    2815 	.db #0x00	; 0
      00872F 01                    2816 	.db #0x01	; 1
      008730 22                    2817 	.db #0x22	; 34
      008731 14                    2818 	.db #0x14	; 20
      008732 15                    2819 	.db #0x15	; 21
      008733 17                    2820 	.db #0x17	; 23
      008734 17                    2821 	.db #0x17	; 23
      008735 17                    2822 	.db #0x17	; 23
      008736 36                    2823 	.db #0x36	; 54	'6'
      008737 05                    2824 	.db #0x05	; 5
      008738 05                    2825 	.db #0x05	; 5
      008739 05                    2826 	.db #0x05	; 5
      00873A 05                    2827 	.db #0x05	; 5
      00873B 05                    2828 	.db #0x05	; 5
      00873C 05                    2829 	.db #0x05	; 5
      00873D 36                    2830 	.db #0x36	; 54	'6'
      00873E 35                    2831 	.db #0x35	; 53	'5'
      00873F 35                    2832 	.db #0x35	; 53	'5'
      008740 35                    2833 	.db #0x35	; 53	'5'
      008741 15                    2834 	.db #0x15	; 21
      008742 14                    2835 	.db #0x14	; 20
      008743 01                    2836 	.db #0x01	; 1
      008744 01                    2837 	.db #0x01	; 1
      008745 00                    2838 	.db #0x00	; 0
      008746 00                    2839 	.db #0x00	; 0
      008747 00                    2840 	.db #0x00	; 0
      008748 00                    2841 	.db #0x00	; 0
      008749 01                    2842 	.db #0x01	; 1
      00874A 01                    2843 	.db #0x01	; 1
      00874B 02                    2844 	.db #0x02	; 2
      00874C 35                    2845 	.db #0x35	; 53	'5'
      00874D 36                    2846 	.db #0x36	; 54	'6'
      00874E 05                    2847 	.db #0x05	; 5
      00874F 05                    2848 	.db #0x05	; 5
      008750 05                    2849 	.db #0x05	; 5
      008751 05                    2850 	.db #0x05	; 5
      008752 17                    2851 	.db #0x17	; 23
      008753 05                    2852 	.db #0x05	; 5
      008754 05                    2853 	.db #0x05	; 5
      008755 05                    2854 	.db #0x05	; 5
      008756 05                    2855 	.db #0x05	; 5
      008757 36                    2856 	.db #0x36	; 54	'6'
      008758 36                    2857 	.db #0x36	; 54	'6'
      008759 35                    2858 	.db #0x35	; 53	'5'
      00875A 35                    2859 	.db #0x35	; 53	'5'
      00875B 02                    2860 	.db #0x02	; 2
      00875C 22                    2861 	.db #0x22	; 34
      00875D 22                    2862 	.db #0x22	; 34
      00875E 01                    2863 	.db #0x01	; 1
      00875F 00                    2864 	.db #0x00	; 0
      008760 00                    2865 	.db #0x00	; 0
      008761 00                    2866 	.db #0x00	; 0
      008762 00                    2867 	.db #0x00	; 0
      008763 01                    2868 	.db #0x01	; 1
      008764 01                    2869 	.db #0x01	; 1
      008765 35                    2870 	.db #0x35	; 53	'5'
      008766 17                    2871 	.db #0x17	; 23
      008767 35                    2872 	.db #0x35	; 53	'5'
      008768 36                    2873 	.db #0x36	; 54	'6'
      008769 05                    2874 	.db #0x05	; 5
      00876A 17                    2875 	.db #0x17	; 23
      00876B 17                    2876 	.db #0x17	; 23
      00876C 17                    2877 	.db #0x17	; 23
      00876D 36                    2878 	.db #0x36	; 54	'6'
      00876E 26                    2879 	.db #0x26	; 38
      00876F 35                    2880 	.db #0x35	; 53	'5'
      008770 35                    2881 	.db #0x35	; 53	'5'
      008771 35                    2882 	.db #0x35	; 53	'5'
      008772 35                    2883 	.db #0x35	; 53	'5'
      008773 02                    2884 	.db #0x02	; 2
      008774 34                    2885 	.db #0x34	; 52	'4'
      008775 14                    2886 	.db #0x14	; 20
      008776 01                    2887 	.db #0x01	; 1
      008777 22                    2888 	.db #0x22	; 34
      008778 01                    2889 	.db #0x01	; 1
      008779 00                    2890 	.db #0x00	; 0
      00877A 00                    2891 	.db #0x00	; 0
      00877B 00                    2892 	.db #0x00	; 0
      00877C 00                    2893 	.db #0x00	; 0
      00877D 01                    2894 	.db #0x01	; 1
      00877E 22                    2895 	.db #0x22	; 34
      00877F 02                    2896 	.db #0x02	; 2
      008780 35                    2897 	.db #0x35	; 53	'5'
      008781 02                    2898 	.db #0x02	; 2
      008782 36                    2899 	.db #0x36	; 54	'6'
      008783 05                    2900 	.db #0x05	; 5
      008784 36                    2901 	.db #0x36	; 54	'6'
      008785 36                    2902 	.db #0x36	; 54	'6'
      008786 36                    2903 	.db #0x36	; 54	'6'
      008787 36                    2904 	.db #0x36	; 54	'6'
      008788 14                    2905 	.db #0x14	; 20
      008789 36                    2906 	.db #0x36	; 54	'6'
      00878A 02                    2907 	.db #0x02	; 2
      00878B 14                    2908 	.db #0x14	; 20
      00878C 02                    2909 	.db #0x02	; 2
      00878D 14                    2910 	.db #0x14	; 20
      00878E 22                    2911 	.db #0x22	; 34
      00878F 22                    2912 	.db #0x22	; 34
      008790 22                    2913 	.db #0x22	; 34
      008791 22                    2914 	.db #0x22	; 34
      008792 01                    2915 	.db #0x01	; 1
      008793 00                    2916 	.db #0x00	; 0
      008794 00                    2917 	.db #0x00	; 0
      008795 00                    2918 	.db #0x00	; 0
      008796 00                    2919 	.db #0x00	; 0
      008797 01                    2920 	.db #0x01	; 1
      008798 22                    2921 	.db #0x22	; 34
      008799 14                    2922 	.db #0x14	; 20
      00879A 34                    2923 	.db #0x34	; 52	'4'
      00879B 02                    2924 	.db #0x02	; 2
      00879C 36                    2925 	.db #0x36	; 54	'6'
      00879D 34                    2926 	.db #0x34	; 52	'4'
      00879E 05                    2927 	.db #0x05	; 5
      00879F 15                    2928 	.db #0x15	; 21
      0087A0 15                    2929 	.db #0x15	; 21
      0087A1 36                    2930 	.db #0x36	; 54	'6'
      0087A2 15                    2931 	.db #0x15	; 21
      0087A3 14                    2932 	.db #0x14	; 20
      0087A4 15                    2933 	.db #0x15	; 21
      0087A5 14                    2934 	.db #0x14	; 20
      0087A6 33                    2935 	.db #0x33	; 51	'3'
      0087A7 02                    2936 	.db #0x02	; 2
      0087A8 01                    2937 	.db #0x01	; 1
      0087A9 34                    2938 	.db #0x34	; 52	'4'
      0087AA 01                    2939 	.db #0x01	; 1
      0087AB 14                    2940 	.db #0x14	; 20
      0087AC 01                    2941 	.db #0x01	; 1
      0087AD 00                    2942 	.db #0x00	; 0
      0087AE 00                    2943 	.db #0x00	; 0
      0087AF 00                    2944 	.db #0x00	; 0
      0087B0 00                    2945 	.db #0x00	; 0
      0087B1 01                    2946 	.db #0x01	; 1
      0087B2 22                    2947 	.db #0x22	; 34
      0087B3 14                    2948 	.db #0x14	; 20
      0087B4 17                    2949 	.db #0x17	; 23
      0087B5 35                    2950 	.db #0x35	; 53	'5'
      0087B6 34                    2951 	.db #0x34	; 52	'4'
      0087B7 36                    2952 	.db #0x36	; 54	'6'
      0087B8 34                    2953 	.db #0x34	; 52	'4'
      0087B9 15                    2954 	.db #0x15	; 21
      0087BA 35                    2955 	.db #0x35	; 53	'5'
      0087BB 15                    2956 	.db #0x15	; 21
      0087BC 15                    2957 	.db #0x15	; 21
      0087BD 36                    2958 	.db #0x36	; 54	'6'
      0087BE 36                    2959 	.db #0x36	; 54	'6'
      0087BF 36                    2960 	.db #0x36	; 54	'6'
      0087C0 17                    2961 	.db #0x17	; 23
      0087C1 17                    2962 	.db #0x17	; 23
      0087C2 15                    2963 	.db #0x15	; 21
      0087C3 35                    2964 	.db #0x35	; 53	'5'
      0087C4 02                    2965 	.db #0x02	; 2
      0087C5 14                    2966 	.db #0x14	; 20
      0087C6 01                    2967 	.db #0x01	; 1
      0087C7 00                    2968 	.db #0x00	; 0
      0087C8 00                    2969 	.db #0x00	; 0
      0087C9 00                    2970 	.db #0x00	; 0
      0087CA 00                    2971 	.db #0x00	; 0
      0087CB 01                    2972 	.db #0x01	; 1
      0087CC 14                    2973 	.db #0x14	; 20
      0087CD 34                    2974 	.db #0x34	; 52	'4'
      0087CE 26                    2975 	.db #0x26	; 38
      0087CF 38                    2976 	.db #0x38	; 56	'8'
      0087D0 35                    2977 	.db #0x35	; 53	'5'
      0087D1 34                    2978 	.db #0x34	; 52	'4'
      0087D2 26                    2979 	.db #0x26	; 38
      0087D3 34                    2980 	.db #0x34	; 52	'4'
      0087D4 35                    2981 	.db #0x35	; 53	'5'
      0087D5 36                    2982 	.db #0x36	; 54	'6'
      0087D6 26                    2983 	.db #0x26	; 38
      0087D7 06                    2984 	.db #0x06	; 6
      0087D8 05                    2985 	.db #0x05	; 5
      0087D9 26                    2986 	.db #0x26	; 38
      0087DA 36                    2987 	.db #0x36	; 54	'6'
      0087DB 36                    2988 	.db #0x36	; 54	'6'
      0087DC 36                    2989 	.db #0x36	; 54	'6'
      0087DD 36                    2990 	.db #0x36	; 54	'6'
      0087DE 02                    2991 	.db #0x02	; 2
      0087DF 14                    2992 	.db #0x14	; 20
      0087E0 01                    2993 	.db #0x01	; 1
      0087E1 00                    2994 	.db #0x00	; 0
      0087E2 00                    2995 	.db #0x00	; 0
      0087E3 00                    2996 	.db #0x00	; 0
      0087E4 00                    2997 	.db #0x00	; 0
      0087E5 01                    2998 	.db #0x01	; 1
      0087E6 14                    2999 	.db #0x14	; 20
      0087E7 35                    3000 	.db #0x35	; 53	'5'
      0087E8 38                    3001 	.db #0x38	; 56	'8'
      0087E9 08                    3002 	.db #0x08	; 8
      0087EA 39                    3003 	.db #0x39	; 57	'9'
      0087EB 39                    3004 	.db #0x39	; 57	'9'
      0087EC 06                    3005 	.db #0x06	; 6
      0087ED 26                    3006 	.db #0x26	; 38
      0087EE 38                    3007 	.db #0x38	; 56	'8'
      0087EF 38                    3008 	.db #0x38	; 56	'8'
      0087F0 38                    3009 	.db #0x38	; 56	'8'
      0087F1 38                    3010 	.db #0x38	; 56	'8'
      0087F2 26                    3011 	.db #0x26	; 38
      0087F3 06                    3012 	.db #0x06	; 6
      0087F4 39                    3013 	.db #0x39	; 57	'9'
      0087F5 39                    3014 	.db #0x39	; 57	'9'
      0087F6 08                    3015 	.db #0x08	; 8
      0087F7 05                    3016 	.db #0x05	; 5
      0087F8 35                    3017 	.db #0x35	; 53	'5'
      0087F9 14                    3018 	.db #0x14	; 20
      0087FA 01                    3019 	.db #0x01	; 1
      0087FB 00                    3020 	.db #0x00	; 0
      0087FC 00                    3021 	.db #0x00	; 0
      0087FD 00                    3022 	.db #0x00	; 0
      0087FE 06                    3023 	.db #0x06	; 6
      0087FF 00                    3024 	.db #0x00	; 0
      008800 14                    3025 	.db #0x14	; 20
      008801 35                    3026 	.db #0x35	; 53	'5'
      008802 06                    3027 	.db #0x06	; 6
      008803 08                    3028 	.db #0x08	; 8
      008804 0C                    3029 	.db #0x0c	; 12
      008805 2B                    3030 	.db #0x2b	; 43
      008806 08                    3031 	.db #0x08	; 8
      008807 28                    3032 	.db #0x28	; 40
      008808 26                    3033 	.db #0x26	; 38
      008809 36                    3034 	.db #0x36	; 54	'6'
      00880A 36                    3035 	.db #0x36	; 54	'6'
      00880B 26                    3036 	.db #0x26	; 38
      00880C 28                    3037 	.db #0x28	; 40
      00880D 08                    3038 	.db #0x08	; 8
      00880E 2B                    3039 	.db #0x2b	; 43
      00880F 0C                    3040 	.db #0x0c	; 12
      008810 08                    3041 	.db #0x08	; 8
      008811 05                    3042 	.db #0x05	; 5
      008812 35                    3043 	.db #0x35	; 53	'5'
      008813 14                    3044 	.db #0x14	; 20
      008814 00                    3045 	.db #0x00	; 0
      008815 06                    3046 	.db #0x06	; 6
      008816 00                    3047 	.db #0x00	; 0
      008817 00                    3048 	.db #0x00	; 0
      008818 06                    3049 	.db #0x06	; 6
      008819 33                    3050 	.db #0x33	; 51	'3'
      00881A 14                    3051 	.db #0x14	; 20
      00881B 36                    3052 	.db #0x36	; 54	'6'
      00881C 06                    3053 	.db #0x06	; 6
      00881D 2B                    3054 	.db #0x2b	; 43
      00881E 2F                    3055 	.db #0x2f	; 47
      00881F 2F                    3056 	.db #0x2f	; 47
      008820 0E                    3057 	.db #0x0e	; 14
      008821 2B                    3058 	.db #0x2b	; 43
      008822 08                    3059 	.db #0x08	; 8
      008823 26                    3060 	.db #0x26	; 38
      008824 26                    3061 	.db #0x26	; 38
      008825 08                    3062 	.db #0x08	; 8
      008826 2B                    3063 	.db #0x2b	; 43
      008827 0E                    3064 	.db #0x0e	; 14
      008828 2F                    3065 	.db #0x2f	; 47
      008829 2F                    3066 	.db #0x2f	; 47
      00882A 2B                    3067 	.db #0x2b	; 43
      00882B 06                    3068 	.db #0x06	; 6
      00882C 36                    3069 	.db #0x36	; 54	'6'
      00882D 14                    3070 	.db #0x14	; 20
      00882E 33                    3071 	.db #0x33	; 51	'3'
      00882F 06                    3072 	.db #0x06	; 6
      008830 00                    3073 	.db #0x00	; 0
      008831 00                    3074 	.db #0x00	; 0
      008832 36                    3075 	.db #0x36	; 54	'6'
      008833 33                    3076 	.db #0x33	; 51	'3'
      008834 14                    3077 	.db #0x14	; 20
      008835 36                    3078 	.db #0x36	; 54	'6'
      008836 34                    3079 	.db #0x34	; 52	'4'
      008837 00                    3080 	.db #0x00	; 0
      008838 34                    3081 	.db #0x34	; 52	'4'
      008839 26                    3082 	.db #0x26	; 38
      00883A 0A                    3083 	.db #0x0a	; 10
      00883B 2F                    3084 	.db #0x2f	; 47
      00883C 06                    3085 	.db #0x06	; 6
      00883D 08                    3086 	.db #0x08	; 8
      00883E 2D                    3087 	.db #0x2d	; 45
      00883F 06                    3088 	.db #0x06	; 6
      008840 2F                    3089 	.db #0x2f	; 47
      008841 0A                    3090 	.db #0x0a	; 10
      008842 26                    3091 	.db #0x26	; 38
      008843 34                    3092 	.db #0x34	; 52	'4'
      008844 00                    3093 	.db #0x00	; 0
      008845 34                    3094 	.db #0x34	; 52	'4'
      008846 36                    3095 	.db #0x36	; 54	'6'
      008847 14                    3096 	.db #0x14	; 20
      008848 33                    3097 	.db #0x33	; 51	'3'
      008849 36                    3098 	.db #0x36	; 54	'6'
      00884A 00                    3099 	.db #0x00	; 0
      00884B 00                    3100 	.db #0x00	; 0
      00884C 15                    3101 	.db #0x15	; 21
      00884D 02                    3102 	.db #0x02	; 2
      00884E 02                    3103 	.db #0x02	; 2
      00884F 02                    3104 	.db #0x02	; 2
      008850 33                    3105 	.db #0x33	; 51	'3'
      008851 02                    3106 	.db #0x02	; 2
      008852 33                    3107 	.db #0x33	; 51	'3'
      008853 15                    3108 	.db #0x15	; 21
      008854 06                    3109 	.db #0x06	; 6
      008855 15                    3110 	.db #0x15	; 21
      008856 14                    3111 	.db #0x14	; 20
      008857 26                    3112 	.db #0x26	; 38
      008858 26                    3113 	.db #0x26	; 38
      008859 14                    3114 	.db #0x14	; 20
      00885A 15                    3115 	.db #0x15	; 21
      00885B 06                    3116 	.db #0x06	; 6
      00885C 15                    3117 	.db #0x15	; 21
      00885D 33                    3118 	.db #0x33	; 51	'3'
      00885E 02                    3119 	.db #0x02	; 2
      00885F 33                    3120 	.db #0x33	; 51	'3'
      008860 02                    3121 	.db #0x02	; 2
      008861 02                    3122 	.db #0x02	; 2
      008862 02                    3123 	.db #0x02	; 2
      008863 15                    3124 	.db #0x15	; 21
      008864 00                    3125 	.db #0x00	; 0
      008865 00                    3126 	.db #0x00	; 0
      008866 17                    3127 	.db #0x17	; 23
      008867 02                    3128 	.db #0x02	; 2
      008868 02                    3129 	.db #0x02	; 2
      008869 02                    3130 	.db #0x02	; 2
      00886A 01                    3131 	.db #0x01	; 1
      00886B 3B                    3132 	.db #0x3b	; 59
      00886C 0F                    3133 	.db #0x0f	; 15
      00886D 00                    3134 	.db #0x00	; 0
      00886E 19                    3135 	.db #0x19	; 25
      00886F 00                    3136 	.db #0x00	; 0
      008870 14                    3137 	.db #0x14	; 20
      008871 34                    3138 	.db #0x34	; 52	'4'
      008872 34                    3139 	.db #0x34	; 52	'4'
      008873 14                    3140 	.db #0x14	; 20
      008874 00                    3141 	.db #0x00	; 0
      008875 19                    3142 	.db #0x19	; 25
      008876 00                    3143 	.db #0x00	; 0
      008877 0F                    3144 	.db #0x0f	; 15
      008878 3B                    3145 	.db #0x3b	; 59
      008879 01                    3146 	.db #0x01	; 1
      00887A 02                    3147 	.db #0x02	; 2
      00887B 02                    3148 	.db #0x02	; 2
      00887C 02                    3149 	.db #0x02	; 2
      00887D 17                    3150 	.db #0x17	; 23
      00887E 00                    3151 	.db #0x00	; 0
      00887F 00                    3152 	.db #0x00	; 0
      008880 36                    3153 	.db #0x36	; 54	'6'
      008881 02                    3154 	.db #0x02	; 2
      008882 17                    3155 	.db #0x17	; 23
      008883 06                    3156 	.db #0x06	; 6
      008884 36                    3157 	.db #0x36	; 54	'6'
      008885 38                    3158 	.db #0x38	; 56	'8'
      008886 0C                    3159 	.db #0x0c	; 12
      008887 38                    3160 	.db #0x38	; 56	'8'
      008888 15                    3161 	.db #0x15	; 21
      008889 02                    3162 	.db #0x02	; 2
      00888A 15                    3163 	.db #0x15	; 21
      00888B 38                    3164 	.db #0x38	; 56	'8'
      00888C 38                    3165 	.db #0x38	; 56	'8'
      00888D 15                    3166 	.db #0x15	; 21
      00888E 02                    3167 	.db #0x02	; 2
      00888F 15                    3168 	.db #0x15	; 21
      008890 38                    3169 	.db #0x38	; 56	'8'
      008891 0C                    3170 	.db #0x0c	; 12
      008892 38                    3171 	.db #0x38	; 56	'8'
      008893 36                    3172 	.db #0x36	; 54	'6'
      008894 06                    3173 	.db #0x06	; 6
      008895 17                    3174 	.db #0x17	; 23
      008896 02                    3175 	.db #0x02	; 2
      008897 36                    3176 	.db #0x36	; 54	'6'
      008898 00                    3177 	.db #0x00	; 0
      008899 00                    3178 	.db #0x00	; 0
      00889A 00                    3179 	.db #0x00	; 0
      00889B 02                    3180 	.db #0x02	; 2
      00889C 17                    3181 	.db #0x17	; 23
      00889D 29                    3182 	.db #0x29	; 41
      00889E 29                    3183 	.db #0x29	; 41
      00889F 26                    3184 	.db #0x26	; 38
      0088A0 29                    3185 	.db #0x29	; 41
      0088A1 2B                    3186 	.db #0x2b	; 43
      0088A2 2D                    3187 	.db #0x2d	; 45
      0088A3 29                    3188 	.db #0x29	; 41
      0088A4 38                    3189 	.db #0x38	; 56	'8'
      0088A5 2D                    3190 	.db #0x2d	; 45
      0088A6 2D                    3191 	.db #0x2d	; 45
      0088A7 38                    3192 	.db #0x38	; 56	'8'
      0088A8 29                    3193 	.db #0x29	; 41
      0088A9 2D                    3194 	.db #0x2d	; 45
      0088AA 2B                    3195 	.db #0x2b	; 43
      0088AB 29                    3196 	.db #0x29	; 41
      0088AC 26                    3197 	.db #0x26	; 38
      0088AD 29                    3198 	.db #0x29	; 41
      0088AE 29                    3199 	.db #0x29	; 41
      0088AF 17                    3200 	.db #0x17	; 23
      0088B0 02                    3201 	.db #0x02	; 2
      0088B1 00                    3202 	.db #0x00	; 0
      0088B2 00                    3203 	.db #0x00	; 0
      0088B3 00                    3204 	.db #0x00	; 0
      0088B4 00                    3205 	.db #0x00	; 0
      0088B5 02                    3206 	.db #0x02	; 2
      0088B6 35                    3207 	.db #0x35	; 53	'5'
      0088B7 26                    3208 	.db #0x26	; 38
      0088B8 38                    3209 	.db #0x38	; 56	'8'
      0088B9 28                    3210 	.db #0x28	; 40
      0088BA 2F                    3211 	.db #0x2f	; 47
      0088BB 29                    3212 	.db #0x29	; 41
      0088BC 26                    3213 	.db #0x26	; 38
      0088BD 35                    3214 	.db #0x35	; 53	'5'
      0088BE 2B                    3215 	.db #0x2b	; 43
      0088BF 2F                    3216 	.db #0x2f	; 47
      0088C0 2F                    3217 	.db #0x2f	; 47
      0088C1 2B                    3218 	.db #0x2b	; 43
      0088C2 35                    3219 	.db #0x35	; 53	'5'
      0088C3 26                    3220 	.db #0x26	; 38
      0088C4 29                    3221 	.db #0x29	; 41
      0088C5 2F                    3222 	.db #0x2f	; 47
      0088C6 28                    3223 	.db #0x28	; 40
      0088C7 38                    3224 	.db #0x38	; 56	'8'
      0088C8 26                    3225 	.db #0x26	; 38
      0088C9 35                    3226 	.db #0x35	; 53	'5'
      0088CA 02                    3227 	.db #0x02	; 2
      0088CB 00                    3228 	.db #0x00	; 0
      0088CC 00                    3229 	.db #0x00	; 0
      0088CD 00                    3230 	.db #0x00	; 0
      0088CE 00                    3231 	.db #0x00	; 0
      0088CF 00                    3232 	.db #0x00	; 0
      0088D0 35                    3233 	.db #0x35	; 53	'5'
      0088D1 36                    3234 	.db #0x36	; 54	'6'
      0088D2 36                    3235 	.db #0x36	; 54	'6'
      0088D3 29                    3236 	.db #0x29	; 41
      0088D4 2D                    3237 	.db #0x2d	; 45
      0088D5 26                    3238 	.db #0x26	; 38
      0088D6 36                    3239 	.db #0x36	; 54	'6'
      0088D7 26                    3240 	.db #0x26	; 38
      0088D8 29                    3241 	.db #0x29	; 41
      0088D9 1E                    3242 	.db #0x1e	; 30
      0088DA 1E                    3243 	.db #0x1e	; 30
      0088DB 29                    3244 	.db #0x29	; 41
      0088DC 26                    3245 	.db #0x26	; 38
      0088DD 36                    3246 	.db #0x36	; 54	'6'
      0088DE 26                    3247 	.db #0x26	; 38
      0088DF 2D                    3248 	.db #0x2d	; 45
      0088E0 29                    3249 	.db #0x29	; 41
      0088E1 36                    3250 	.db #0x36	; 54	'6'
      0088E2 36                    3251 	.db #0x36	; 54	'6'
      0088E3 35                    3252 	.db #0x35	; 53	'5'
      0088E4 00                    3253 	.db #0x00	; 0
      0088E5 00                    3254 	.db #0x00	; 0
      0088E6 00                    3255 	.db #0x00	; 0
      0088E7 00                    3256 	.db #0x00	; 0
      0088E8 00                    3257 	.db #0x00	; 0
      0088E9 00                    3258 	.db #0x00	; 0
      0088EA 35                    3259 	.db #0x35	; 53	'5'
      0088EB 26                    3260 	.db #0x26	; 38
      0088EC 05                    3261 	.db #0x05	; 5
      0088ED 2B                    3262 	.db #0x2b	; 43
      0088EE 2B                    3263 	.db #0x2b	; 43
      0088EF 26                    3264 	.db #0x26	; 38
      0088F0 08                    3265 	.db #0x08	; 8
      0088F1 0A                    3266 	.db #0x0a	; 10
      0088F2 26                    3267 	.db #0x26	; 38
      0088F3 2B                    3268 	.db #0x2b	; 43
      0088F4 2B                    3269 	.db #0x2b	; 43
      0088F5 26                    3270 	.db #0x26	; 38
      0088F6 0A                    3271 	.db #0x0a	; 10
      0088F7 08                    3272 	.db #0x08	; 8
      0088F8 26                    3273 	.db #0x26	; 38
      0088F9 2B                    3274 	.db #0x2b	; 43
      0088FA 2B                    3275 	.db #0x2b	; 43
      0088FB 05                    3276 	.db #0x05	; 5
      0088FC 26                    3277 	.db #0x26	; 38
      0088FD 35                    3278 	.db #0x35	; 53	'5'
      0088FE 00                    3279 	.db #0x00	; 0
      0088FF 00                    3280 	.db #0x00	; 0
      008900 00                    3281 	.db #0x00	; 0
      008901 00                    3282 	.db #0x00	; 0
      008902 00                    3283 	.db #0x00	; 0
      008903 00                    3284 	.db #0x00	; 0
      008904 02                    3285 	.db #0x02	; 2
      008905 39                    3286 	.db #0x39	; 57	'9'
      008906 36                    3287 	.db #0x36	; 54	'6'
      008907 29                    3288 	.db #0x29	; 41
      008908 2B                    3289 	.db #0x2b	; 43
      008909 35                    3290 	.db #0x35	; 53	'5'
      00890A 06                    3291 	.db #0x06	; 6
      00890B 39                    3292 	.db #0x39	; 57	'9'
      00890C 08                    3293 	.db #0x08	; 8
      00890D 06                    3294 	.db #0x06	; 6
      00890E 06                    3295 	.db #0x06	; 6
      00890F 08                    3296 	.db #0x08	; 8
      008910 39                    3297 	.db #0x39	; 57	'9'
      008911 06                    3298 	.db #0x06	; 6
      008912 35                    3299 	.db #0x35	; 53	'5'
      008913 2B                    3300 	.db #0x2b	; 43
      008914 29                    3301 	.db #0x29	; 41
      008915 36                    3302 	.db #0x36	; 54	'6'
      008916 39                    3303 	.db #0x39	; 57	'9'
      008917 02                    3304 	.db #0x02	; 2
      008918 00                    3305 	.db #0x00	; 0
      008919 00                    3306 	.db #0x00	; 0
      00891A 00                    3307 	.db #0x00	; 0
      00891B 00                    3308 	.db #0x00	; 0
      00891C 00                    3309 	.db #0x00	; 0
      00891D 00                    3310 	.db #0x00	; 0
      00891E 00                    3311 	.db #0x00	; 0
      00891F 38                    3312 	.db #0x38	; 56	'8'
      008920 26                    3313 	.db #0x26	; 38
      008921 39                    3314 	.db #0x39	; 57	'9'
      008922 29                    3315 	.db #0x29	; 41
      008923 02                    3316 	.db #0x02	; 2
      008924 16                    3317 	.db #0x16	; 22
      008925 21                    3318 	.db #0x21	; 33
      008926 10                    3319 	.db #0x10	; 16
      008927 1B                    3320 	.db #0x1b	; 27
      008928 1B                    3321 	.db #0x1b	; 27
      008929 10                    3322 	.db #0x10	; 16
      00892A 21                    3323 	.db #0x21	; 33
      00892B 16                    3324 	.db #0x16	; 22
      00892C 02                    3325 	.db #0x02	; 2
      00892D 29                    3326 	.db #0x29	; 41
      00892E 39                    3327 	.db #0x39	; 57	'9'
      00892F 26                    3328 	.db #0x26	; 38
      008930 38                    3329 	.db #0x38	; 56	'8'
      008931 00                    3330 	.db #0x00	; 0
      008932 00                    3331 	.db #0x00	; 0
      008933 00                    3332 	.db #0x00	; 0
      008934 00                    3333 	.db #0x00	; 0
      008935 00                    3334 	.db #0x00	; 0
      008936 00                    3335 	.db #0x00	; 0
      008937 00                    3336 	.db #0x00	; 0
      008938 00                    3337 	.db #0x00	; 0
      008939 17                    3338 	.db #0x17	; 23
      00893A 38                    3339 	.db #0x38	; 56	'8'
      00893B 39                    3340 	.db #0x39	; 57	'9'
      00893C 29                    3341 	.db #0x29	; 41
      00893D 35                    3342 	.db #0x35	; 53	'5'
      00893E 16                    3343 	.db #0x16	; 22
      00893F 1D                    3344 	.db #0x1d	; 29
      008940 31                    3345 	.db #0x31	; 49	'1'
      008941 32                    3346 	.db #0x32	; 50	'2'
      008942 32                    3347 	.db #0x32	; 50	'2'
      008943 31                    3348 	.db #0x31	; 49	'1'
      008944 1D                    3349 	.db #0x1d	; 29
      008945 16                    3350 	.db #0x16	; 22
      008946 35                    3351 	.db #0x35	; 53	'5'
      008947 29                    3352 	.db #0x29	; 41
      008948 39                    3353 	.db #0x39	; 57	'9'
      008949 38                    3354 	.db #0x38	; 56	'8'
      00894A 17                    3355 	.db #0x17	; 23
      00894B 00                    3356 	.db #0x00	; 0
      00894C 00                    3357 	.db #0x00	; 0
      00894D 00                    3358 	.db #0x00	; 0
      00894E 00                    3359 	.db #0x00	; 0
      00894F 00                    3360 	.db #0x00	; 0
      008950 00                    3361 	.db #0x00	; 0
      008951 00                    3362 	.db #0x00	; 0
      008952 00                    3363 	.db #0x00	; 0
      008953 00                    3364 	.db #0x00	; 0
      008954 36                    3365 	.db #0x36	; 54	'6'
      008955 06                    3366 	.db #0x06	; 6
      008956 39                    3367 	.db #0x39	; 57	'9'
      008957 26                    3368 	.db #0x26	; 38
      008958 39                    3369 	.db #0x39	; 57	'9'
      008959 29                    3370 	.db #0x29	; 41
      00895A 2D                    3371 	.db #0x2d	; 45
      00895B 2F                    3372 	.db #0x2f	; 47
      00895C 2F                    3373 	.db #0x2f	; 47
      00895D 2D                    3374 	.db #0x2d	; 45
      00895E 29                    3375 	.db #0x29	; 41
      00895F 39                    3376 	.db #0x39	; 57	'9'
      008960 26                    3377 	.db #0x26	; 38
      008961 39                    3378 	.db #0x39	; 57	'9'
      008962 06                    3379 	.db #0x06	; 6
      008963 36                    3380 	.db #0x36	; 54	'6'
      008964 00                    3381 	.db #0x00	; 0
      008965 00                    3382 	.db #0x00	; 0
      008966 00                    3383 	.db #0x00	; 0
      008967 00                    3384 	.db #0x00	; 0
      008968 00                    3385 	.db #0x00	; 0
      008969 00                    3386 	.db #0x00	; 0
      00896A 00                    3387 	.db #0x00	; 0
      00896B 00                    3388 	.db #0x00	; 0
      00896C 00                    3389 	.db #0x00	; 0
      00896D 00                    3390 	.db #0x00	; 0
      00896E 15                    3391 	.db #0x15	; 21
      00896F 05                    3392 	.db #0x05	; 5
      008970 08                    3393 	.db #0x08	; 8
      008971 26                    3394 	.db #0x26	; 38
      008972 36                    3395 	.db #0x36	; 54	'6'
      008973 36                    3396 	.db #0x36	; 54	'6'
      008974 36                    3397 	.db #0x36	; 54	'6'
      008975 03                    3398 	.db #0x03	; 3
      008976 03                    3399 	.db #0x03	; 3
      008977 36                    3400 	.db #0x36	; 54	'6'
      008978 36                    3401 	.db #0x36	; 54	'6'
      008979 36                    3402 	.db #0x36	; 54	'6'
      00897A 26                    3403 	.db #0x26	; 38
      00897B 08                    3404 	.db #0x08	; 8
      00897C 05                    3405 	.db #0x05	; 5
      00897D 15                    3406 	.db #0x15	; 21
      00897E 00                    3407 	.db #0x00	; 0
      00897F 00                    3408 	.db #0x00	; 0
      008980 00                    3409 	.db #0x00	; 0
      008981 00                    3410 	.db #0x00	; 0
      008982 00                    3411 	.db #0x00	; 0
      008983 00                    3412 	.db #0x00	; 0
      008984 00                    3413 	.db #0x00	; 0
      008985 00                    3414 	.db #0x00	; 0
      008986 00                    3415 	.db #0x00	; 0
      008987 00                    3416 	.db #0x00	; 0
      008988 00                    3417 	.db #0x00	; 0
      008989 15                    3418 	.db #0x15	; 21
      00898A 26                    3419 	.db #0x26	; 38
      00898B 08                    3420 	.db #0x08	; 8
      00898C 36                    3421 	.db #0x36	; 54	'6'
      00898D 26                    3422 	.db #0x26	; 38
      00898E 39                    3423 	.db #0x39	; 57	'9'
      00898F 2B                    3424 	.db #0x2b	; 43
      008990 2B                    3425 	.db #0x2b	; 43
      008991 39                    3426 	.db #0x39	; 57	'9'
      008992 26                    3427 	.db #0x26	; 38
      008993 36                    3428 	.db #0x36	; 54	'6'
      008994 08                    3429 	.db #0x08	; 8
      008995 26                    3430 	.db #0x26	; 38
      008996 15                    3431 	.db #0x15	; 21
      008997 00                    3432 	.db #0x00	; 0
      008998 00                    3433 	.db #0x00	; 0
      008999 00                    3434 	.db #0x00	; 0
      00899A 00                    3435 	.db #0x00	; 0
      00899B 00                    3436 	.db #0x00	; 0
      00899C 00                    3437 	.db #0x00	; 0
      00899D 00                    3438 	.db #0x00	; 0
      00899E 00                    3439 	.db #0x00	; 0
      00899F 00                    3440 	.db #0x00	; 0
      0089A0 00                    3441 	.db #0x00	; 0
      0089A1 00                    3442 	.db #0x00	; 0
      0089A2 00                    3443 	.db #0x00	; 0
      0089A3 00                    3444 	.db #0x00	; 0
      0089A4 34                    3445 	.db #0x34	; 52	'4'
      0089A5 26                    3446 	.db #0x26	; 38
      0089A6 06                    3447 	.db #0x06	; 6
      0089A7 29                    3448 	.db #0x29	; 41
      0089A8 2B                    3449 	.db #0x2b	; 43
      0089A9 3D                    3450 	.db #0x3d	; 61
      0089AA 3D                    3451 	.db #0x3d	; 61
      0089AB 2B                    3452 	.db #0x2b	; 43
      0089AC 29                    3453 	.db #0x29	; 41
      0089AD 06                    3454 	.db #0x06	; 6
      0089AE 26                    3455 	.db #0x26	; 38
      0089AF 34                    3456 	.db #0x34	; 52	'4'
      0089B0 00                    3457 	.db #0x00	; 0
      0089B1 00                    3458 	.db #0x00	; 0
      0089B2 00                    3459 	.db #0x00	; 0
      0089B3 00                    3460 	.db #0x00	; 0
      0089B4 00                    3461 	.db #0x00	; 0
      0089B5 00                    3462 	.db #0x00	; 0
      0089B6 00                    3463 	.db #0x00	; 0
      0089B7 00                    3464 	.db #0x00	; 0
      0089B8 00                    3465 	.db #0x00	; 0
      0089B9 00                    3466 	.db #0x00	; 0
      0089BA 00                    3467 	.db #0x00	; 0
      0089BB 00                    3468 	.db #0x00	; 0
      0089BC 00                    3469 	.db #0x00	; 0
      0089BD 00                    3470 	.db #0x00	; 0
      0089BE 00                    3471 	.db #0x00	; 0
      0089BF 00                    3472 	.db #0x00	; 0
      0089C0 36                    3473 	.db #0x36	; 54	'6'
      0089C1 06                    3474 	.db #0x06	; 6
      0089C2 06                    3475 	.db #0x06	; 6
      0089C3 06                    3476 	.db #0x06	; 6
      0089C4 06                    3477 	.db #0x06	; 6
      0089C5 06                    3478 	.db #0x06	; 6
      0089C6 06                    3479 	.db #0x06	; 6
      0089C7 36                    3480 	.db #0x36	; 54	'6'
      0089C8 00                    3481 	.db #0x00	; 0
      0089C9 00                    3482 	.db #0x00	; 0
      0089CA 00                    3483 	.db #0x00	; 0
      0089CB 00                    3484 	.db #0x00	; 0
      0089CC 00                    3485 	.db #0x00	; 0
      0089CD 00                    3486 	.db #0x00	; 0
      0089CE 00                    3487 	.db #0x00	; 0
      0089CF 00                    3488 	.db #0x00	; 0
      0089D0                       3489 _doom4_raw:
      0089D0 00                    3490 	.db #0x00	; 0
      0089D1 00                    3491 	.db #0x00	; 0
      0089D2 00                    3492 	.db #0x00	; 0
      0089D3 00                    3493 	.db #0x00	; 0
      0089D4 00                    3494 	.db #0x00	; 0
      0089D5 00                    3495 	.db #0x00	; 0
      0089D6 14                    3496 	.db #0x14	; 20
      0089D7 02                    3497 	.db #0x02	; 2
      0089D8 02                    3498 	.db #0x02	; 2
      0089D9 15                    3499 	.db #0x15	; 21
      0089DA 35                    3500 	.db #0x35	; 53	'5'
      0089DB 35                    3501 	.db #0x35	; 53	'5'
      0089DC 35                    3502 	.db #0x35	; 53	'5'
      0089DD 35                    3503 	.db #0x35	; 53	'5'
      0089DE 35                    3504 	.db #0x35	; 53	'5'
      0089DF 35                    3505 	.db #0x35	; 53	'5'
      0089E0 15                    3506 	.db #0x15	; 21
      0089E1 02                    3507 	.db #0x02	; 2
      0089E2 02                    3508 	.db #0x02	; 2
      0089E3 14                    3509 	.db #0x14	; 20
      0089E4 00                    3510 	.db #0x00	; 0
      0089E5 00                    3511 	.db #0x00	; 0
      0089E6 00                    3512 	.db #0x00	; 0
      0089E7 00                    3513 	.db #0x00	; 0
      0089E8 00                    3514 	.db #0x00	; 0
      0089E9 00                    3515 	.db #0x00	; 0
      0089EA 00                    3516 	.db #0x00	; 0
      0089EB 00                    3517 	.db #0x00	; 0
      0089EC 00                    3518 	.db #0x00	; 0
      0089ED 00                    3519 	.db #0x00	; 0
      0089EE 22                    3520 	.db #0x22	; 34
      0089EF 02                    3521 	.db #0x02	; 2
      0089F0 34                    3522 	.db #0x34	; 52	'4'
      0089F1 02                    3523 	.db #0x02	; 2
      0089F2 15                    3524 	.db #0x15	; 21
      0089F3 35                    3525 	.db #0x35	; 53	'5'
      0089F4 36                    3526 	.db #0x36	; 54	'6'
      0089F5 05                    3527 	.db #0x05	; 5
      0089F6 05                    3528 	.db #0x05	; 5
      0089F7 05                    3529 	.db #0x05	; 5
      0089F8 05                    3530 	.db #0x05	; 5
      0089F9 36                    3531 	.db #0x36	; 54	'6'
      0089FA 35                    3532 	.db #0x35	; 53	'5'
      0089FB 15                    3533 	.db #0x15	; 21
      0089FC 02                    3534 	.db #0x02	; 2
      0089FD 34                    3535 	.db #0x34	; 52	'4'
      0089FE 02                    3536 	.db #0x02	; 2
      0089FF 22                    3537 	.db #0x22	; 34
      008A00 00                    3538 	.db #0x00	; 0
      008A01 00                    3539 	.db #0x00	; 0
      008A02 00                    3540 	.db #0x00	; 0
      008A03 00                    3541 	.db #0x00	; 0
      008A04 00                    3542 	.db #0x00	; 0
      008A05 00                    3543 	.db #0x00	; 0
      008A06 00                    3544 	.db #0x00	; 0
      008A07 22                    3545 	.db #0x22	; 34
      008A08 14                    3546 	.db #0x14	; 20
      008A09 15                    3547 	.db #0x15	; 21
      008A0A 35                    3548 	.db #0x35	; 53	'5'
      008A0B 35                    3549 	.db #0x35	; 53	'5'
      008A0C 17                    3550 	.db #0x17	; 23
      008A0D 36                    3551 	.db #0x36	; 54	'6'
      008A0E 05                    3552 	.db #0x05	; 5
      008A0F 05                    3553 	.db #0x05	; 5
      008A10 05                    3554 	.db #0x05	; 5
      008A11 05                    3555 	.db #0x05	; 5
      008A12 05                    3556 	.db #0x05	; 5
      008A13 05                    3557 	.db #0x05	; 5
      008A14 36                    3558 	.db #0x36	; 54	'6'
      008A15 35                    3559 	.db #0x35	; 53	'5'
      008A16 35                    3560 	.db #0x35	; 53	'5'
      008A17 35                    3561 	.db #0x35	; 53	'5'
      008A18 15                    3562 	.db #0x15	; 21
      008A19 14                    3563 	.db #0x14	; 20
      008A1A 22                    3564 	.db #0x22	; 34
      008A1B 00                    3565 	.db #0x00	; 0
      008A1C 00                    3566 	.db #0x00	; 0
      008A1D 00                    3567 	.db #0x00	; 0
      008A1E 00                    3568 	.db #0x00	; 0
      008A1F 00                    3569 	.db #0x00	; 0
      008A20 00                    3570 	.db #0x00	; 0
      008A21 22                    3571 	.db #0x22	; 34
      008A22 14                    3572 	.db #0x14	; 20
      008A23 15                    3573 	.db #0x15	; 21
      008A24 17                    3574 	.db #0x17	; 23
      008A25 17                    3575 	.db #0x17	; 23
      008A26 17                    3576 	.db #0x17	; 23
      008A27 36                    3577 	.db #0x36	; 54	'6'
      008A28 05                    3578 	.db #0x05	; 5
      008A29 05                    3579 	.db #0x05	; 5
      008A2A 05                    3580 	.db #0x05	; 5
      008A2B 05                    3581 	.db #0x05	; 5
      008A2C 05                    3582 	.db #0x05	; 5
      008A2D 05                    3583 	.db #0x05	; 5
      008A2E 36                    3584 	.db #0x36	; 54	'6'
      008A2F 35                    3585 	.db #0x35	; 53	'5'
      008A30 35                    3586 	.db #0x35	; 53	'5'
      008A31 35                    3587 	.db #0x35	; 53	'5'
      008A32 15                    3588 	.db #0x15	; 21
      008A33 14                    3589 	.db #0x14	; 20
      008A34 01                    3590 	.db #0x01	; 1
      008A35 00                    3591 	.db #0x00	; 0
      008A36 00                    3592 	.db #0x00	; 0
      008A37 00                    3593 	.db #0x00	; 0
      008A38 00                    3594 	.db #0x00	; 0
      008A39 00                    3595 	.db #0x00	; 0
      008A3A 01                    3596 	.db #0x01	; 1
      008A3B 22                    3597 	.db #0x22	; 34
      008A3C 02                    3598 	.db #0x02	; 2
      008A3D 35                    3599 	.db #0x35	; 53	'5'
      008A3E 36                    3600 	.db #0x36	; 54	'6'
      008A3F 05                    3601 	.db #0x05	; 5
      008A40 05                    3602 	.db #0x05	; 5
      008A41 05                    3603 	.db #0x05	; 5
      008A42 05                    3604 	.db #0x05	; 5
      008A43 17                    3605 	.db #0x17	; 23
      008A44 05                    3606 	.db #0x05	; 5
      008A45 05                    3607 	.db #0x05	; 5
      008A46 05                    3608 	.db #0x05	; 5
      008A47 05                    3609 	.db #0x05	; 5
      008A48 36                    3610 	.db #0x36	; 54	'6'
      008A49 36                    3611 	.db #0x36	; 54	'6'
      008A4A 35                    3612 	.db #0x35	; 53	'5'
      008A4B 35                    3613 	.db #0x35	; 53	'5'
      008A4C 15                    3614 	.db #0x15	; 21
      008A4D 14                    3615 	.db #0x14	; 20
      008A4E 01                    3616 	.db #0x01	; 1
      008A4F 01                    3617 	.db #0x01	; 1
      008A50 00                    3618 	.db #0x00	; 0
      008A51 00                    3619 	.db #0x00	; 0
      008A52 00                    3620 	.db #0x00	; 0
      008A53 00                    3621 	.db #0x00	; 0
      008A54 01                    3622 	.db #0x01	; 1
      008A55 01                    3623 	.db #0x01	; 1
      008A56 35                    3624 	.db #0x35	; 53	'5'
      008A57 17                    3625 	.db #0x17	; 23
      008A58 35                    3626 	.db #0x35	; 53	'5'
      008A59 36                    3627 	.db #0x36	; 54	'6'
      008A5A 05                    3628 	.db #0x05	; 5
      008A5B 17                    3629 	.db #0x17	; 23
      008A5C 17                    3630 	.db #0x17	; 23
      008A5D 17                    3631 	.db #0x17	; 23
      008A5E 36                    3632 	.db #0x36	; 54	'6'
      008A5F 26                    3633 	.db #0x26	; 38
      008A60 35                    3634 	.db #0x35	; 53	'5'
      008A61 35                    3635 	.db #0x35	; 53	'5'
      008A62 35                    3636 	.db #0x35	; 53	'5'
      008A63 35                    3637 	.db #0x35	; 53	'5'
      008A64 02                    3638 	.db #0x02	; 2
      008A65 34                    3639 	.db #0x34	; 52	'4'
      008A66 02                    3640 	.db #0x02	; 2
      008A67 22                    3641 	.db #0x22	; 34
      008A68 22                    3642 	.db #0x22	; 34
      008A69 01                    3643 	.db #0x01	; 1
      008A6A 00                    3644 	.db #0x00	; 0
      008A6B 00                    3645 	.db #0x00	; 0
      008A6C 00                    3646 	.db #0x00	; 0
      008A6D 00                    3647 	.db #0x00	; 0
      008A6E 01                    3648 	.db #0x01	; 1
      008A6F 01                    3649 	.db #0x01	; 1
      008A70 02                    3650 	.db #0x02	; 2
      008A71 35                    3651 	.db #0x35	; 53	'5'
      008A72 02                    3652 	.db #0x02	; 2
      008A73 36                    3653 	.db #0x36	; 54	'6'
      008A74 05                    3654 	.db #0x05	; 5
      008A75 36                    3655 	.db #0x36	; 54	'6'
      008A76 36                    3656 	.db #0x36	; 54	'6'
      008A77 36                    3657 	.db #0x36	; 54	'6'
      008A78 36                    3658 	.db #0x36	; 54	'6'
      008A79 14                    3659 	.db #0x14	; 20
      008A7A 36                    3660 	.db #0x36	; 54	'6'
      008A7B 02                    3661 	.db #0x02	; 2
      008A7C 14                    3662 	.db #0x14	; 20
      008A7D 02                    3663 	.db #0x02	; 2
      008A7E 14                    3664 	.db #0x14	; 20
      008A7F 22                    3665 	.db #0x22	; 34
      008A80 14                    3666 	.db #0x14	; 20
      008A81 01                    3667 	.db #0x01	; 1
      008A82 22                    3668 	.db #0x22	; 34
      008A83 01                    3669 	.db #0x01	; 1
      008A84 00                    3670 	.db #0x00	; 0
      008A85 00                    3671 	.db #0x00	; 0
      008A86 00                    3672 	.db #0x00	; 0
      008A87 00                    3673 	.db #0x00	; 0
      008A88 01                    3674 	.db #0x01	; 1
      008A89 22                    3675 	.db #0x22	; 34
      008A8A 14                    3676 	.db #0x14	; 20
      008A8B 34                    3677 	.db #0x34	; 52	'4'
      008A8C 02                    3678 	.db #0x02	; 2
      008A8D 36                    3679 	.db #0x36	; 54	'6'
      008A8E 34                    3680 	.db #0x34	; 52	'4'
      008A8F 05                    3681 	.db #0x05	; 5
      008A90 15                    3682 	.db #0x15	; 21
      008A91 15                    3683 	.db #0x15	; 21
      008A92 36                    3684 	.db #0x36	; 54	'6'
      008A93 15                    3685 	.db #0x15	; 21
      008A94 14                    3686 	.db #0x14	; 20
      008A95 15                    3687 	.db #0x15	; 21
      008A96 14                    3688 	.db #0x14	; 20
      008A97 33                    3689 	.db #0x33	; 51	'3'
      008A98 02                    3690 	.db #0x02	; 2
      008A99 01                    3691 	.db #0x01	; 1
      008A9A 22                    3692 	.db #0x22	; 34
      008A9B 22                    3693 	.db #0x22	; 34
      008A9C 22                    3694 	.db #0x22	; 34
      008A9D 01                    3695 	.db #0x01	; 1
      008A9E 00                    3696 	.db #0x00	; 0
      008A9F 00                    3697 	.db #0x00	; 0
      008AA0 00                    3698 	.db #0x00	; 0
      008AA1 00                    3699 	.db #0x00	; 0
      008AA2 01                    3700 	.db #0x01	; 1
      008AA3 22                    3701 	.db #0x22	; 34
      008AA4 14                    3702 	.db #0x14	; 20
      008AA5 35                    3703 	.db #0x35	; 53	'5'
      008AA6 35                    3704 	.db #0x35	; 53	'5'
      008AA7 34                    3705 	.db #0x34	; 52	'4'
      008AA8 36                    3706 	.db #0x36	; 54	'6'
      008AA9 34                    3707 	.db #0x34	; 52	'4'
      008AAA 15                    3708 	.db #0x15	; 21
      008AAB 35                    3709 	.db #0x35	; 53	'5'
      008AAC 15                    3710 	.db #0x15	; 21
      008AAD 15                    3711 	.db #0x15	; 21
      008AAE 36                    3712 	.db #0x36	; 54	'6'
      008AAF 36                    3713 	.db #0x36	; 54	'6'
      008AB0 36                    3714 	.db #0x36	; 54	'6'
      008AB1 17                    3715 	.db #0x17	; 23
      008AB2 17                    3716 	.db #0x17	; 23
      008AB3 15                    3717 	.db #0x15	; 21
      008AB4 34                    3718 	.db #0x34	; 52	'4'
      008AB5 01                    3719 	.db #0x01	; 1
      008AB6 14                    3720 	.db #0x14	; 20
      008AB7 01                    3721 	.db #0x01	; 1
      008AB8 00                    3722 	.db #0x00	; 0
      008AB9 00                    3723 	.db #0x00	; 0
      008ABA 00                    3724 	.db #0x00	; 0
      008ABB 00                    3725 	.db #0x00	; 0
      008ABC 01                    3726 	.db #0x01	; 1
      008ABD 22                    3727 	.db #0x22	; 34
      008ABE 34                    3728 	.db #0x34	; 52	'4'
      008ABF 35                    3729 	.db #0x35	; 53	'5'
      008AC0 38                    3730 	.db #0x38	; 56	'8'
      008AC1 35                    3731 	.db #0x35	; 53	'5'
      008AC2 34                    3732 	.db #0x34	; 52	'4'
      008AC3 26                    3733 	.db #0x26	; 38
      008AC4 34                    3734 	.db #0x34	; 52	'4'
      008AC5 35                    3735 	.db #0x35	; 53	'5'
      008AC6 36                    3736 	.db #0x36	; 54	'6'
      008AC7 26                    3737 	.db #0x26	; 38
      008AC8 06                    3738 	.db #0x06	; 6
      008AC9 05                    3739 	.db #0x05	; 5
      008ACA 26                    3740 	.db #0x26	; 38
      008ACB 36                    3741 	.db #0x36	; 54	'6'
      008ACC 36                    3742 	.db #0x36	; 54	'6'
      008ACD 36                    3743 	.db #0x36	; 54	'6'
      008ACE 35                    3744 	.db #0x35	; 53	'5'
      008ACF 02                    3745 	.db #0x02	; 2
      008AD0 14                    3746 	.db #0x14	; 20
      008AD1 01                    3747 	.db #0x01	; 1
      008AD2 00                    3748 	.db #0x00	; 0
      008AD3 00                    3749 	.db #0x00	; 0
      008AD4 00                    3750 	.db #0x00	; 0
      008AD5 00                    3751 	.db #0x00	; 0
      008AD6 01                    3752 	.db #0x01	; 1
      008AD7 14                    3753 	.db #0x14	; 20
      008AD8 02                    3754 	.db #0x02	; 2
      008AD9 36                    3755 	.db #0x36	; 54	'6'
      008ADA 38                    3756 	.db #0x38	; 56	'8'
      008ADB 06                    3757 	.db #0x06	; 6
      008ADC 26                    3758 	.db #0x26	; 38
      008ADD 26                    3759 	.db #0x26	; 38
      008ADE 06                    3760 	.db #0x06	; 6
      008ADF 05                    3761 	.db #0x05	; 5
      008AE0 05                    3762 	.db #0x05	; 5
      008AE1 05                    3763 	.db #0x05	; 5
      008AE2 05                    3764 	.db #0x05	; 5
      008AE3 06                    3765 	.db #0x06	; 6
      008AE4 26                    3766 	.db #0x26	; 38
      008AE5 26                    3767 	.db #0x26	; 38
      008AE6 06                    3768 	.db #0x06	; 6
      008AE7 38                    3769 	.db #0x38	; 56	'8'
      008AE8 36                    3770 	.db #0x36	; 54	'6'
      008AE9 02                    3771 	.db #0x02	; 2
      008AEA 33                    3772 	.db #0x33	; 51	'3'
      008AEB 01                    3773 	.db #0x01	; 1
      008AEC 00                    3774 	.db #0x00	; 0
      008AED 00                    3775 	.db #0x00	; 0
      008AEE 00                    3776 	.db #0x00	; 0
      008AEF 00                    3777 	.db #0x00	; 0
      008AF0 01                    3778 	.db #0x01	; 1
      008AF1 14                    3779 	.db #0x14	; 20
      008AF2 35                    3780 	.db #0x35	; 53	'5'
      008AF3 05                    3781 	.db #0x05	; 5
      008AF4 08                    3782 	.db #0x08	; 8
      008AF5 08                    3783 	.db #0x08	; 8
      008AF6 08                    3784 	.db #0x08	; 8
      008AF7 26                    3785 	.db #0x26	; 38
      008AF8 05                    3786 	.db #0x05	; 5
      008AF9 35                    3787 	.db #0x35	; 53	'5'
      008AFA 17                    3788 	.db #0x17	; 23
      008AFB 17                    3789 	.db #0x17	; 23
      008AFC 35                    3790 	.db #0x35	; 53	'5'
      008AFD 05                    3791 	.db #0x05	; 5
      008AFE 26                    3792 	.db #0x26	; 38
      008AFF 08                    3793 	.db #0x08	; 8
      008B00 08                    3794 	.db #0x08	; 8
      008B01 08                    3795 	.db #0x08	; 8
      008B02 05                    3796 	.db #0x05	; 5
      008B03 35                    3797 	.db #0x35	; 53	'5'
      008B04 14                    3798 	.db #0x14	; 20
      008B05 01                    3799 	.db #0x01	; 1
      008B06 00                    3800 	.db #0x00	; 0
      008B07 00                    3801 	.db #0x00	; 0
      008B08 00                    3802 	.db #0x00	; 0
      008B09 06                    3803 	.db #0x06	; 6
      008B0A 00                    3804 	.db #0x00	; 0
      008B0B 14                    3805 	.db #0x14	; 20
      008B0C 35                    3806 	.db #0x35	; 53	'5'
      008B0D 05                    3807 	.db #0x05	; 5
      008B0E 08                    3808 	.db #0x08	; 8
      008B0F 0C                    3809 	.db #0x0c	; 12
      008B10 2B                    3810 	.db #0x2b	; 43
      008B11 08                    3811 	.db #0x08	; 8
      008B12 28                    3812 	.db #0x28	; 40
      008B13 26                    3813 	.db #0x26	; 38
      008B14 35                    3814 	.db #0x35	; 53	'5'
      008B15 35                    3815 	.db #0x35	; 53	'5'
      008B16 26                    3816 	.db #0x26	; 38
      008B17 28                    3817 	.db #0x28	; 40
      008B18 08                    3818 	.db #0x08	; 8
      008B19 2B                    3819 	.db #0x2b	; 43
      008B1A 0C                    3820 	.db #0x0c	; 12
      008B1B 08                    3821 	.db #0x08	; 8
      008B1C 05                    3822 	.db #0x05	; 5
      008B1D 35                    3823 	.db #0x35	; 53	'5'
      008B1E 14                    3824 	.db #0x14	; 20
      008B1F 00                    3825 	.db #0x00	; 0
      008B20 06                    3826 	.db #0x06	; 6
      008B21 00                    3827 	.db #0x00	; 0
      008B22 00                    3828 	.db #0x00	; 0
      008B23 06                    3829 	.db #0x06	; 6
      008B24 33                    3830 	.db #0x33	; 51	'3'
      008B25 14                    3831 	.db #0x14	; 20
      008B26 36                    3832 	.db #0x36	; 54	'6'
      008B27 06                    3833 	.db #0x06	; 6
      008B28 2B                    3834 	.db #0x2b	; 43
      008B29 2F                    3835 	.db #0x2f	; 47
      008B2A 2F                    3836 	.db #0x2f	; 47
      008B2B 0E                    3837 	.db #0x0e	; 14
      008B2C 2B                    3838 	.db #0x2b	; 43
      008B2D 08                    3839 	.db #0x08	; 8
      008B2E 26                    3840 	.db #0x26	; 38
      008B2F 26                    3841 	.db #0x26	; 38
      008B30 08                    3842 	.db #0x08	; 8
      008B31 2B                    3843 	.db #0x2b	; 43
      008B32 0E                    3844 	.db #0x0e	; 14
      008B33 2F                    3845 	.db #0x2f	; 47
      008B34 2F                    3846 	.db #0x2f	; 47
      008B35 2B                    3847 	.db #0x2b	; 43
      008B36 06                    3848 	.db #0x06	; 6
      008B37 36                    3849 	.db #0x36	; 54	'6'
      008B38 14                    3850 	.db #0x14	; 20
      008B39 33                    3851 	.db #0x33	; 51	'3'
      008B3A 06                    3852 	.db #0x06	; 6
      008B3B 00                    3853 	.db #0x00	; 0
      008B3C 00                    3854 	.db #0x00	; 0
      008B3D 36                    3855 	.db #0x36	; 54	'6'
      008B3E 33                    3856 	.db #0x33	; 51	'3'
      008B3F 14                    3857 	.db #0x14	; 20
      008B40 06                    3858 	.db #0x06	; 6
      008B41 34                    3859 	.db #0x34	; 52	'4'
      008B42 34                    3860 	.db #0x34	; 52	'4'
      008B43 34                    3861 	.db #0x34	; 52	'4'
      008B44 26                    3862 	.db #0x26	; 38
      008B45 0A                    3863 	.db #0x0a	; 10
      008B46 2F                    3864 	.db #0x2f	; 47
      008B47 06                    3865 	.db #0x06	; 6
      008B48 08                    3866 	.db #0x08	; 8
      008B49 0E                    3867 	.db #0x0e	; 14
      008B4A 06                    3868 	.db #0x06	; 6
      008B4B 2F                    3869 	.db #0x2f	; 47
      008B4C 0A                    3870 	.db #0x0a	; 10
      008B4D 26                    3871 	.db #0x26	; 38
      008B4E 34                    3872 	.db #0x34	; 52	'4'
      008B4F 34                    3873 	.db #0x34	; 52	'4'
      008B50 34                    3874 	.db #0x34	; 52	'4'
      008B51 06                    3875 	.db #0x06	; 6
      008B52 14                    3876 	.db #0x14	; 20
      008B53 33                    3877 	.db #0x33	; 51	'3'
      008B54 36                    3878 	.db #0x36	; 54	'6'
      008B55 00                    3879 	.db #0x00	; 0
      008B56 00                    3880 	.db #0x00	; 0
      008B57 15                    3881 	.db #0x15	; 21
      008B58 02                    3882 	.db #0x02	; 2
      008B59 17                    3883 	.db #0x17	; 23
      008B5A 36                    3884 	.db #0x36	; 54	'6'
      008B5B 33                    3885 	.db #0x33	; 51	'3'
      008B5C 33                    3886 	.db #0x33	; 51	'3'
      008B5D 33                    3887 	.db #0x33	; 51	'3'
      008B5E 15                    3888 	.db #0x15	; 21
      008B5F 06                    3889 	.db #0x06	; 6
      008B60 15                    3890 	.db #0x15	; 21
      008B61 14                    3891 	.db #0x14	; 20
      008B62 26                    3892 	.db #0x26	; 38
      008B63 26                    3893 	.db #0x26	; 38
      008B64 14                    3894 	.db #0x14	; 20
      008B65 15                    3895 	.db #0x15	; 21
      008B66 06                    3896 	.db #0x06	; 6
      008B67 15                    3897 	.db #0x15	; 21
      008B68 33                    3898 	.db #0x33	; 51	'3'
      008B69 33                    3899 	.db #0x33	; 51	'3'
      008B6A 33                    3900 	.db #0x33	; 51	'3'
      008B6B 36                    3901 	.db #0x36	; 54	'6'
      008B6C 17                    3902 	.db #0x17	; 23
      008B6D 02                    3903 	.db #0x02	; 2
      008B6E 15                    3904 	.db #0x15	; 21
      008B6F 00                    3905 	.db #0x00	; 0
      008B70 00                    3906 	.db #0x00	; 0
      008B71 17                    3907 	.db #0x17	; 23
      008B72 02                    3908 	.db #0x02	; 2
      008B73 05                    3909 	.db #0x05	; 5
      008B74 2B                    3910 	.db #0x2b	; 43
      008B75 35                    3911 	.db #0x35	; 53	'5'
      008B76 3B                    3912 	.db #0x3b	; 59
      008B77 0F                    3913 	.db #0x0f	; 15
      008B78 00                    3914 	.db #0x00	; 0
      008B79 19                    3915 	.db #0x19	; 25
      008B7A 00                    3916 	.db #0x00	; 0
      008B7B 14                    3917 	.db #0x14	; 20
      008B7C 34                    3918 	.db #0x34	; 52	'4'
      008B7D 34                    3919 	.db #0x34	; 52	'4'
      008B7E 14                    3920 	.db #0x14	; 20
      008B7F 00                    3921 	.db #0x00	; 0
      008B80 19                    3922 	.db #0x19	; 25
      008B81 00                    3923 	.db #0x00	; 0
      008B82 0F                    3924 	.db #0x0f	; 15
      008B83 3B                    3925 	.db #0x3b	; 59
      008B84 35                    3926 	.db #0x35	; 53	'5'
      008B85 2B                    3927 	.db #0x2b	; 43
      008B86 05                    3928 	.db #0x05	; 5
      008B87 02                    3929 	.db #0x02	; 2
      008B88 17                    3930 	.db #0x17	; 23
      008B89 00                    3931 	.db #0x00	; 0
      008B8A 00                    3932 	.db #0x00	; 0
      008B8B 36                    3933 	.db #0x36	; 54	'6'
      008B8C 02                    3934 	.db #0x02	; 2
      008B8D 39                    3935 	.db #0x39	; 57	'9'
      008B8E 2D                    3936 	.db #0x2d	; 45
      008B8F 2B                    3937 	.db #0x2b	; 43
      008B90 38                    3938 	.db #0x38	; 56	'8'
      008B91 0C                    3939 	.db #0x0c	; 12
      008B92 38                    3940 	.db #0x38	; 56	'8'
      008B93 05                    3941 	.db #0x05	; 5
      008B94 02                    3942 	.db #0x02	; 2
      008B95 15                    3943 	.db #0x15	; 21
      008B96 38                    3944 	.db #0x38	; 56	'8'
      008B97 38                    3945 	.db #0x38	; 56	'8'
      008B98 15                    3946 	.db #0x15	; 21
      008B99 02                    3947 	.db #0x02	; 2
      008B9A 05                    3948 	.db #0x05	; 5
      008B9B 38                    3949 	.db #0x38	; 56	'8'
      008B9C 0C                    3950 	.db #0x0c	; 12
      008B9D 38                    3951 	.db #0x38	; 56	'8'
      008B9E 2B                    3952 	.db #0x2b	; 43
      008B9F 2D                    3953 	.db #0x2d	; 45
      008BA0 39                    3954 	.db #0x39	; 57	'9'
      008BA1 02                    3955 	.db #0x02	; 2
      008BA2 36                    3956 	.db #0x36	; 54	'6'
      008BA3 00                    3957 	.db #0x00	; 0
      008BA4 00                    3958 	.db #0x00	; 0
      008BA5 00                    3959 	.db #0x00	; 0
      008BA6 02                    3960 	.db #0x02	; 2
      008BA7 39                    3961 	.db #0x39	; 57	'9'
      008BA8 2D                    3962 	.db #0x2d	; 45
      008BA9 2D                    3963 	.db #0x2d	; 45
      008BAA 2B                    3964 	.db #0x2b	; 43
      008BAB 2B                    3965 	.db #0x2b	; 43
      008BAC 2B                    3966 	.db #0x2b	; 43
      008BAD 2D                    3967 	.db #0x2d	; 45
      008BAE 29                    3968 	.db #0x29	; 41
      008BAF 38                    3969 	.db #0x38	; 56	'8'
      008BB0 2D                    3970 	.db #0x2d	; 45
      008BB1 2D                    3971 	.db #0x2d	; 45
      008BB2 38                    3972 	.db #0x38	; 56	'8'
      008BB3 29                    3973 	.db #0x29	; 41
      008BB4 2D                    3974 	.db #0x2d	; 45
      008BB5 2B                    3975 	.db #0x2b	; 43
      008BB6 2B                    3976 	.db #0x2b	; 43
      008BB7 2B                    3977 	.db #0x2b	; 43
      008BB8 2D                    3978 	.db #0x2d	; 45
      008BB9 2D                    3979 	.db #0x2d	; 45
      008BBA 39                    3980 	.db #0x39	; 57	'9'
      008BBB 02                    3981 	.db #0x02	; 2
      008BBC 00                    3982 	.db #0x00	; 0
      008BBD 00                    3983 	.db #0x00	; 0
      008BBE 00                    3984 	.db #0x00	; 0
      008BBF 00                    3985 	.db #0x00	; 0
      008BC0 17                    3986 	.db #0x17	; 23
      008BC1 28                    3987 	.db #0x28	; 40
      008BC2 29                    3988 	.db #0x29	; 41
      008BC3 2B                    3989 	.db #0x2b	; 43
      008BC4 08                    3990 	.db #0x08	; 8
      008BC5 28                    3991 	.db #0x28	; 40
      008BC6 36                    3992 	.db #0x36	; 54	'6'
      008BC7 02                    3993 	.db #0x02	; 2
      008BC8 38                    3994 	.db #0x38	; 56	'8'
      008BC9 29                    3995 	.db #0x29	; 41
      008BCA 1E                    3996 	.db #0x1e	; 30
      008BCB 1E                    3997 	.db #0x1e	; 30
      008BCC 29                    3998 	.db #0x29	; 41
      008BCD 38                    3999 	.db #0x38	; 56	'8'
      008BCE 02                    4000 	.db #0x02	; 2
      008BCF 36                    4001 	.db #0x36	; 54	'6'
      008BD0 28                    4002 	.db #0x28	; 40
      008BD1 08                    4003 	.db #0x08	; 8
      008BD2 2B                    4004 	.db #0x2b	; 43
      008BD3 29                    4005 	.db #0x29	; 41
      008BD4 28                    4006 	.db #0x28	; 40
      008BD5 17                    4007 	.db #0x17	; 23
      008BD6 00                    4008 	.db #0x00	; 0
      008BD7 00                    4009 	.db #0x00	; 0
      008BD8 00                    4010 	.db #0x00	; 0
      008BD9 00                    4011 	.db #0x00	; 0
      008BDA 17                    4012 	.db #0x17	; 23
      008BDB 38                    4013 	.db #0x38	; 56	'8'
      008BDC 39                    4014 	.db #0x39	; 57	'9'
      008BDD 2B                    4015 	.db #0x2b	; 43
      008BDE 26                    4016 	.db #0x26	; 38
      008BDF 27                    4017 	.db #0x27	; 39
      008BE0 15                    4018 	.db #0x15	; 21
      008BE1 02                    4019 	.db #0x02	; 2
      008BE2 35                    4020 	.db #0x35	; 53	'5'
      008BE3 26                    4021 	.db #0x26	; 38
      008BE4 2B                    4022 	.db #0x2b	; 43
      008BE5 2B                    4023 	.db #0x2b	; 43
      008BE6 26                    4024 	.db #0x26	; 38
      008BE7 35                    4025 	.db #0x35	; 53	'5'
      008BE8 02                    4026 	.db #0x02	; 2
      008BE9 15                    4027 	.db #0x15	; 21
      008BEA 27                    4028 	.db #0x27	; 39
      008BEB 26                    4029 	.db #0x26	; 38
      008BEC 2B                    4030 	.db #0x2b	; 43
      008BED 39                    4031 	.db #0x39	; 57	'9'
      008BEE 38                    4032 	.db #0x38	; 56	'8'
      008BEF 17                    4033 	.db #0x17	; 23
      008BF0 00                    4034 	.db #0x00	; 0
      008BF1 00                    4035 	.db #0x00	; 0
      008BF2 00                    4036 	.db #0x00	; 0
      008BF3 00                    4037 	.db #0x00	; 0
      008BF4 00                    4038 	.db #0x00	; 0
      008BF5 05                    4039 	.db #0x05	; 5
      008BF6 39                    4040 	.db #0x39	; 57	'9'
      008BF7 29                    4041 	.db #0x29	; 41
      008BF8 38                    4042 	.db #0x38	; 56	'8'
      008BF9 15                    4043 	.db #0x15	; 21
      008BFA 27                    4044 	.db #0x27	; 39
      008BFB 36                    4045 	.db #0x36	; 54	'6'
      008BFC 28                    4046 	.db #0x28	; 40
      008BFD 17                    4047 	.db #0x17	; 23
      008BFE 17                    4048 	.db #0x17	; 23
      008BFF 17                    4049 	.db #0x17	; 23
      008C00 17                    4050 	.db #0x17	; 23
      008C01 28                    4051 	.db #0x28	; 40
      008C02 36                    4052 	.db #0x36	; 54	'6'
      008C03 27                    4053 	.db #0x27	; 39
      008C04 15                    4054 	.db #0x15	; 21
      008C05 38                    4055 	.db #0x38	; 56	'8'
      008C06 29                    4056 	.db #0x29	; 41
      008C07 39                    4057 	.db #0x39	; 57	'9'
      008C08 05                    4058 	.db #0x05	; 5
      008C09 00                    4059 	.db #0x00	; 0
      008C0A 00                    4060 	.db #0x00	; 0
      008C0B 00                    4061 	.db #0x00	; 0
      008C0C 00                    4062 	.db #0x00	; 0
      008C0D 00                    4063 	.db #0x00	; 0
      008C0E 00                    4064 	.db #0x00	; 0
      008C0F 15                    4065 	.db #0x15	; 21
      008C10 39                    4066 	.db #0x39	; 57	'9'
      008C11 29                    4067 	.db #0x29	; 41
      008C12 39                    4068 	.db #0x39	; 57	'9'
      008C13 05                    4069 	.db #0x05	; 5
      008C14 10                    4070 	.db #0x10	; 16
      008C15 3A                    4071 	.db #0x3a	; 58
      008C16 1B                    4072 	.db #0x1b	; 27
      008C17 3B                    4073 	.db #0x3b	; 59
      008C18 3C                    4074 	.db #0x3c	; 60
      008C19 3C                    4075 	.db #0x3c	; 60
      008C1A 3B                    4076 	.db #0x3b	; 59
      008C1B 1B                    4077 	.db #0x1b	; 27
      008C1C 3A                    4078 	.db #0x3a	; 58
      008C1D 10                    4079 	.db #0x10	; 16
      008C1E 05                    4080 	.db #0x05	; 5
      008C1F 39                    4081 	.db #0x39	; 57	'9'
      008C20 29                    4082 	.db #0x29	; 41
      008C21 39                    4083 	.db #0x39	; 57	'9'
      008C22 15                    4084 	.db #0x15	; 21
      008C23 00                    4085 	.db #0x00	; 0
      008C24 00                    4086 	.db #0x00	; 0
      008C25 00                    4087 	.db #0x00	; 0
      008C26 00                    4088 	.db #0x00	; 0
      008C27 00                    4089 	.db #0x00	; 0
      008C28 00                    4090 	.db #0x00	; 0
      008C29 00                    4091 	.db #0x00	; 0
      008C2A 26                    4092 	.db #0x26	; 38
      008C2B 39                    4093 	.db #0x39	; 57	'9'
      008C2C 29                    4094 	.db #0x29	; 41
      008C2D 06                    4095 	.db #0x06	; 6
      008C2E 29                    4096 	.db #0x29	; 41
      008C2F 10                    4097 	.db #0x10	; 16
      008C30 10                    4098 	.db #0x10	; 16
      008C31 30                    4099 	.db #0x30	; 48	'0'
      008C32 32                    4100 	.db #0x32	; 50	'2'
      008C33 32                    4101 	.db #0x32	; 50	'2'
      008C34 30                    4102 	.db #0x30	; 48	'0'
      008C35 10                    4103 	.db #0x10	; 16
      008C36 10                    4104 	.db #0x10	; 16
      008C37 29                    4105 	.db #0x29	; 41
      008C38 06                    4106 	.db #0x06	; 6
      008C39 29                    4107 	.db #0x29	; 41
      008C3A 39                    4108 	.db #0x39	; 57	'9'
      008C3B 26                    4109 	.db #0x26	; 38
      008C3C 00                    4110 	.db #0x00	; 0
      008C3D 00                    4111 	.db #0x00	; 0
      008C3E 00                    4112 	.db #0x00	; 0
      008C3F 00                    4113 	.db #0x00	; 0
      008C40 00                    4114 	.db #0x00	; 0
      008C41 00                    4115 	.db #0x00	; 0
      008C42 00                    4116 	.db #0x00	; 0
      008C43 00                    4117 	.db #0x00	; 0
      008C44 15                    4118 	.db #0x15	; 21
      008C45 38                    4119 	.db #0x38	; 56	'8'
      008C46 39                    4120 	.db #0x39	; 57	'9'
      008C47 06                    4121 	.db #0x06	; 6
      008C48 38                    4122 	.db #0x38	; 56	'8'
      008C49 29                    4123 	.db #0x29	; 41
      008C4A 10                    4124 	.db #0x10	; 16
      008C4B 1B                    4125 	.db #0x1b	; 27
      008C4C 3B                    4126 	.db #0x3b	; 59
      008C4D 3B                    4127 	.db #0x3b	; 59
      008C4E 1B                    4128 	.db #0x1b	; 27
      008C4F 10                    4129 	.db #0x10	; 16
      008C50 29                    4130 	.db #0x29	; 41
      008C51 38                    4131 	.db #0x38	; 56	'8'
      008C52 06                    4132 	.db #0x06	; 6
      008C53 39                    4133 	.db #0x39	; 57	'9'
      008C54 38                    4134 	.db #0x38	; 56	'8'
      008C55 15                    4135 	.db #0x15	; 21
      008C56 00                    4136 	.db #0x00	; 0
      008C57 00                    4137 	.db #0x00	; 0
      008C58 00                    4138 	.db #0x00	; 0
      008C59 00                    4139 	.db #0x00	; 0
      008C5A 00                    4140 	.db #0x00	; 0
      008C5B 00                    4141 	.db #0x00	; 0
      008C5C 00                    4142 	.db #0x00	; 0
      008C5D 00                    4143 	.db #0x00	; 0
      008C5E 00                    4144 	.db #0x00	; 0
      008C5F 15                    4145 	.db #0x15	; 21
      008C60 38                    4146 	.db #0x38	; 56	'8'
      008C61 39                    4147 	.db #0x39	; 57	'9'
      008C62 39                    4148 	.db #0x39	; 57	'9'
      008C63 36                    4149 	.db #0x36	; 54	'6'
      008C64 06                    4150 	.db #0x06	; 6
      008C65 29                    4151 	.db #0x29	; 41
      008C66 2F                    4152 	.db #0x2f	; 47
      008C67 2F                    4153 	.db #0x2f	; 47
      008C68 29                    4154 	.db #0x29	; 41
      008C69 06                    4155 	.db #0x06	; 6
      008C6A 36                    4156 	.db #0x36	; 54	'6'
      008C6B 39                    4157 	.db #0x39	; 57	'9'
      008C6C 39                    4158 	.db #0x39	; 57	'9'
      008C6D 38                    4159 	.db #0x38	; 56	'8'
      008C6E 15                    4160 	.db #0x15	; 21
      008C6F 00                    4161 	.db #0x00	; 0
      008C70 00                    4162 	.db #0x00	; 0
      008C71 00                    4163 	.db #0x00	; 0
      008C72 00                    4164 	.db #0x00	; 0
      008C73 00                    4165 	.db #0x00	; 0
      008C74 00                    4166 	.db #0x00	; 0
      008C75 00                    4167 	.db #0x00	; 0
      008C76 00                    4168 	.db #0x00	; 0
      008C77 00                    4169 	.db #0x00	; 0
      008C78 00                    4170 	.db #0x00	; 0
      008C79 00                    4171 	.db #0x00	; 0
      008C7A 15                    4172 	.db #0x15	; 21
      008C7B 08                    4173 	.db #0x08	; 8
      008C7C 0A                    4174 	.db #0x0a	; 10
      008C7D 39                    4175 	.db #0x39	; 57	'9'
      008C7E 36                    4176 	.db #0x36	; 54	'6'
      008C7F 02                    4177 	.db #0x02	; 2
      008C80 33                    4178 	.db #0x33	; 51	'3'
      008C81 33                    4179 	.db #0x33	; 51	'3'
      008C82 02                    4180 	.db #0x02	; 2
      008C83 36                    4181 	.db #0x36	; 54	'6'
      008C84 39                    4182 	.db #0x39	; 57	'9'
      008C85 0A                    4183 	.db #0x0a	; 10
      008C86 08                    4184 	.db #0x08	; 8
      008C87 15                    4185 	.db #0x15	; 21
      008C88 00                    4186 	.db #0x00	; 0
      008C89 00                    4187 	.db #0x00	; 0
      008C8A 00                    4188 	.db #0x00	; 0
      008C8B 00                    4189 	.db #0x00	; 0
      008C8C 00                    4190 	.db #0x00	; 0
      008C8D 00                    4191 	.db #0x00	; 0
      008C8E 00                    4192 	.db #0x00	; 0
      008C8F 00                    4193 	.db #0x00	; 0
      008C90 00                    4194 	.db #0x00	; 0
      008C91 00                    4195 	.db #0x00	; 0
      008C92 00                    4196 	.db #0x00	; 0
      008C93 00                    4197 	.db #0x00	; 0
      008C94 00                    4198 	.db #0x00	; 0
      008C95 15                    4199 	.db #0x15	; 21
      008C96 38                    4200 	.db #0x38	; 56	'8'
      008C97 0A                    4201 	.db #0x0a	; 10
      008C98 39                    4202 	.db #0x39	; 57	'9'
      008C99 38                    4203 	.db #0x38	; 56	'8'
      008C9A 17                    4204 	.db #0x17	; 23
      008C9B 17                    4205 	.db #0x17	; 23
      008C9C 38                    4206 	.db #0x38	; 56	'8'
      008C9D 39                    4207 	.db #0x39	; 57	'9'
      008C9E 0A                    4208 	.db #0x0a	; 10
      008C9F 38                    4209 	.db #0x38	; 56	'8'
      008CA0 15                    4210 	.db #0x15	; 21
      008CA1 00                    4211 	.db #0x00	; 0
      008CA2 00                    4212 	.db #0x00	; 0
      008CA3 00                    4213 	.db #0x00	; 0
      008CA4 00                    4214 	.db #0x00	; 0
      008CA5 00                    4215 	.db #0x00	; 0
      008CA6 00                    4216 	.db #0x00	; 0
      008CA7 00                    4217 	.db #0x00	; 0
      008CA8 00                    4218 	.db #0x00	; 0
      008CA9 00                    4219 	.db #0x00	; 0
      008CAA 00                    4220 	.db #0x00	; 0
      008CAB 00                    4221 	.db #0x00	; 0
      008CAC 00                    4222 	.db #0x00	; 0
      008CAD 00                    4223 	.db #0x00	; 0
      008CAE 00                    4224 	.db #0x00	; 0
      008CAF 00                    4225 	.db #0x00	; 0
      008CB0 15                    4226 	.db #0x15	; 21
      008CB1 36                    4227 	.db #0x36	; 54	'6'
      008CB2 29                    4228 	.db #0x29	; 41
      008CB3 2B                    4229 	.db #0x2b	; 43
      008CB4 3D                    4230 	.db #0x3d	; 61
      008CB5 3D                    4231 	.db #0x3d	; 61
      008CB6 2B                    4232 	.db #0x2b	; 43
      008CB7 29                    4233 	.db #0x29	; 41
      008CB8 36                    4234 	.db #0x36	; 54	'6'
      008CB9 15                    4235 	.db #0x15	; 21
      008CBA 00                    4236 	.db #0x00	; 0
      008CBB 00                    4237 	.db #0x00	; 0
      008CBC 00                    4238 	.db #0x00	; 0
      008CBD 00                    4239 	.db #0x00	; 0
      008CBE 00                    4240 	.db #0x00	; 0
      008CBF 00                    4241 	.db #0x00	; 0
      008CC0 00                    4242 	.db #0x00	; 0
      008CC1 00                    4243 	.db #0x00	; 0
      008CC2 00                    4244 	.db #0x00	; 0
      008CC3 00                    4245 	.db #0x00	; 0
      008CC4 00                    4246 	.db #0x00	; 0
      008CC5 00                    4247 	.db #0x00	; 0
      008CC6 00                    4248 	.db #0x00	; 0
      008CC7 00                    4249 	.db #0x00	; 0
      008CC8 00                    4250 	.db #0x00	; 0
      008CC9 00                    4251 	.db #0x00	; 0
      008CCA 00                    4252 	.db #0x00	; 0
      008CCB 00                    4253 	.db #0x00	; 0
      008CCC 02                    4254 	.db #0x02	; 2
      008CCD 36                    4255 	.db #0x36	; 54	'6'
      008CCE 06                    4256 	.db #0x06	; 6
      008CCF 06                    4257 	.db #0x06	; 6
      008CD0 36                    4258 	.db #0x36	; 54	'6'
      008CD1 02                    4259 	.db #0x02	; 2
      008CD2 00                    4260 	.db #0x00	; 0
      008CD3 00                    4261 	.db #0x00	; 0
      008CD4 00                    4262 	.db #0x00	; 0
      008CD5 00                    4263 	.db #0x00	; 0
      008CD6 00                    4264 	.db #0x00	; 0
      008CD7 00                    4265 	.db #0x00	; 0
      008CD8 00                    4266 	.db #0x00	; 0
      008CD9 00                    4267 	.db #0x00	; 0
      008CDA 00                    4268 	.db #0x00	; 0
      008CDB                       4269 _doom5_raw:
      008CDB 00                    4270 	.db #0x00	; 0
      008CDC 00                    4271 	.db #0x00	; 0
      008CDD 00                    4272 	.db #0x00	; 0
      008CDE 00                    4273 	.db #0x00	; 0
      008CDF 00                    4274 	.db #0x00	; 0
      008CE0 00                    4275 	.db #0x00	; 0
      008CE1 14                    4276 	.db #0x14	; 20
      008CE2 02                    4277 	.db #0x02	; 2
      008CE3 02                    4278 	.db #0x02	; 2
      008CE4 02                    4279 	.db #0x02	; 2
      008CE5 15                    4280 	.db #0x15	; 21
      008CE6 35                    4281 	.db #0x35	; 53	'5'
      008CE7 35                    4282 	.db #0x35	; 53	'5'
      008CE8 35                    4283 	.db #0x35	; 53	'5'
      008CE9 35                    4284 	.db #0x35	; 53	'5'
      008CEA 35                    4285 	.db #0x35	; 53	'5'
      008CEB 15                    4286 	.db #0x15	; 21
      008CEC 02                    4287 	.db #0x02	; 2
      008CED 02                    4288 	.db #0x02	; 2
      008CEE 14                    4289 	.db #0x14	; 20
      008CEF 00                    4290 	.db #0x00	; 0
      008CF0 00                    4291 	.db #0x00	; 0
      008CF1 00                    4292 	.db #0x00	; 0
      008CF2 00                    4293 	.db #0x00	; 0
      008CF3 00                    4294 	.db #0x00	; 0
      008CF4 00                    4295 	.db #0x00	; 0
      008CF5 00                    4296 	.db #0x00	; 0
      008CF6 00                    4297 	.db #0x00	; 0
      008CF7 00                    4298 	.db #0x00	; 0
      008CF8 00                    4299 	.db #0x00	; 0
      008CF9 22                    4300 	.db #0x22	; 34
      008CFA 02                    4301 	.db #0x02	; 2
      008CFB 34                    4302 	.db #0x34	; 52	'4'
      008CFC 02                    4303 	.db #0x02	; 2
      008CFD 15                    4304 	.db #0x15	; 21
      008CFE 36                    4305 	.db #0x36	; 54	'6'
      008CFF 28                    4306 	.db #0x28	; 40
      008D00 06                    4307 	.db #0x06	; 6
      008D01 08                    4308 	.db #0x08	; 8
      008D02 08                    4309 	.db #0x08	; 8
      008D03 06                    4310 	.db #0x06	; 6
      008D04 38                    4311 	.db #0x38	; 56	'8'
      008D05 05                    4312 	.db #0x05	; 5
      008D06 35                    4313 	.db #0x35	; 53	'5'
      008D07 02                    4314 	.db #0x02	; 2
      008D08 34                    4315 	.db #0x34	; 52	'4'
      008D09 02                    4316 	.db #0x02	; 2
      008D0A 22                    4317 	.db #0x22	; 34
      008D0B 00                    4318 	.db #0x00	; 0
      008D0C 00                    4319 	.db #0x00	; 0
      008D0D 00                    4320 	.db #0x00	; 0
      008D0E 00                    4321 	.db #0x00	; 0
      008D0F 00                    4322 	.db #0x00	; 0
      008D10 00                    4323 	.db #0x00	; 0
      008D11 00                    4324 	.db #0x00	; 0
      008D12 22                    4325 	.db #0x22	; 34
      008D13 02                    4326 	.db #0x02	; 2
      008D14 35                    4327 	.db #0x35	; 53	'5'
      008D15 36                    4328 	.db #0x36	; 54	'6'
      008D16 05                    4329 	.db #0x05	; 5
      008D17 28                    4330 	.db #0x28	; 40
      008D18 39                    4331 	.db #0x39	; 57	'9'
      008D19 08                    4332 	.db #0x08	; 8
      008D1A 26                    4333 	.db #0x26	; 38
      008D1B 06                    4334 	.db #0x06	; 6
      008D1C 05                    4335 	.db #0x05	; 5
      008D1D 05                    4336 	.db #0x05	; 5
      008D1E 05                    4337 	.db #0x05	; 5
      008D1F 36                    4338 	.db #0x36	; 54	'6'
      008D20 36                    4339 	.db #0x36	; 54	'6'
      008D21 35                    4340 	.db #0x35	; 53	'5'
      008D22 35                    4341 	.db #0x35	; 53	'5'
      008D23 34                    4342 	.db #0x34	; 52	'4'
      008D24 14                    4343 	.db #0x14	; 20
      008D25 22                    4344 	.db #0x22	; 34
      008D26 00                    4345 	.db #0x00	; 0
      008D27 00                    4346 	.db #0x00	; 0
      008D28 00                    4347 	.db #0x00	; 0
      008D29 00                    4348 	.db #0x00	; 0
      008D2A 00                    4349 	.db #0x00	; 0
      008D2B 00                    4350 	.db #0x00	; 0
      008D2C 22                    4351 	.db #0x22	; 34
      008D2D 35                    4352 	.db #0x35	; 53	'5'
      008D2E 17                    4353 	.db #0x17	; 23
      008D2F 35                    4354 	.db #0x35	; 53	'5'
      008D30 36                    4355 	.db #0x36	; 54	'6'
      008D31 05                    4356 	.db #0x05	; 5
      008D32 06                    4357 	.db #0x06	; 6
      008D33 17                    4358 	.db #0x17	; 23
      008D34 38                    4359 	.db #0x38	; 56	'8'
      008D35 36                    4360 	.db #0x36	; 54	'6'
      008D36 26                    4361 	.db #0x26	; 38
      008D37 35                    4362 	.db #0x35	; 53	'5'
      008D38 35                    4363 	.db #0x35	; 53	'5'
      008D39 35                    4364 	.db #0x35	; 53	'5'
      008D3A 35                    4365 	.db #0x35	; 53	'5'
      008D3B 02                    4366 	.db #0x02	; 2
      008D3C 34                    4367 	.db #0x34	; 52	'4'
      008D3D 22                    4368 	.db #0x22	; 34
      008D3E 22                    4369 	.db #0x22	; 34
      008D3F 01                    4370 	.db #0x01	; 1
      008D40 00                    4371 	.db #0x00	; 0
      008D41 00                    4372 	.db #0x00	; 0
      008D42 00                    4373 	.db #0x00	; 0
      008D43 00                    4374 	.db #0x00	; 0
      008D44 00                    4375 	.db #0x00	; 0
      008D45 01                    4376 	.db #0x01	; 1
      008D46 33                    4377 	.db #0x33	; 51	'3'
      008D47 02                    4378 	.db #0x02	; 2
      008D48 35                    4379 	.db #0x35	; 53	'5'
      008D49 02                    4380 	.db #0x02	; 2
      008D4A 36                    4381 	.db #0x36	; 54	'6'
      008D4B 05                    4382 	.db #0x05	; 5
      008D4C 36                    4383 	.db #0x36	; 54	'6'
      008D4D 36                    4384 	.db #0x36	; 54	'6'
      008D4E 36                    4385 	.db #0x36	; 54	'6'
      008D4F 36                    4386 	.db #0x36	; 54	'6'
      008D50 14                    4387 	.db #0x14	; 20
      008D51 36                    4388 	.db #0x36	; 54	'6'
      008D52 02                    4389 	.db #0x02	; 2
      008D53 14                    4390 	.db #0x14	; 20
      008D54 02                    4391 	.db #0x02	; 2
      008D55 14                    4392 	.db #0x14	; 20
      008D56 22                    4393 	.db #0x22	; 34
      008D57 01                    4394 	.db #0x01	; 1
      008D58 01                    4395 	.db #0x01	; 1
      008D59 01                    4396 	.db #0x01	; 1
      008D5A 01                    4397 	.db #0x01	; 1
      008D5B 00                    4398 	.db #0x00	; 0
      008D5C 00                    4399 	.db #0x00	; 0
      008D5D 00                    4400 	.db #0x00	; 0
      008D5E 00                    4401 	.db #0x00	; 0
      008D5F 01                    4402 	.db #0x01	; 1
      008D60 33                    4403 	.db #0x33	; 51	'3'
      008D61 14                    4404 	.db #0x14	; 20
      008D62 34                    4405 	.db #0x34	; 52	'4'
      008D63 02                    4406 	.db #0x02	; 2
      008D64 36                    4407 	.db #0x36	; 54	'6'
      008D65 34                    4408 	.db #0x34	; 52	'4'
      008D66 05                    4409 	.db #0x05	; 5
      008D67 15                    4410 	.db #0x15	; 21
      008D68 15                    4411 	.db #0x15	; 21
      008D69 36                    4412 	.db #0x36	; 54	'6'
      008D6A 15                    4413 	.db #0x15	; 21
      008D6B 14                    4414 	.db #0x14	; 20
      008D6C 15                    4415 	.db #0x15	; 21
      008D6D 14                    4416 	.db #0x14	; 20
      008D6E 33                    4417 	.db #0x33	; 51	'3'
      008D6F 02                    4418 	.db #0x02	; 2
      008D70 01                    4419 	.db #0x01	; 1
      008D71 22                    4420 	.db #0x22	; 34
      008D72 22                    4421 	.db #0x22	; 34
      008D73 33                    4422 	.db #0x33	; 51	'3'
      008D74 01                    4423 	.db #0x01	; 1
      008D75 00                    4424 	.db #0x00	; 0
      008D76 00                    4425 	.db #0x00	; 0
      008D77 00                    4426 	.db #0x00	; 0
      008D78 00                    4427 	.db #0x00	; 0
      008D79 01                    4428 	.db #0x01	; 1
      008D7A 14                    4429 	.db #0x14	; 20
      008D7B 14                    4430 	.db #0x14	; 20
      008D7C 35                    4431 	.db #0x35	; 53	'5'
      008D7D 35                    4432 	.db #0x35	; 53	'5'
      008D7E 34                    4433 	.db #0x34	; 52	'4'
      008D7F 36                    4434 	.db #0x36	; 54	'6'
      008D80 34                    4435 	.db #0x34	; 52	'4'
      008D81 15                    4436 	.db #0x15	; 21
      008D82 35                    4437 	.db #0x35	; 53	'5'
      008D83 15                    4438 	.db #0x15	; 21
      008D84 15                    4439 	.db #0x15	; 21
      008D85 36                    4440 	.db #0x36	; 54	'6'
      008D86 36                    4441 	.db #0x36	; 54	'6'
      008D87 36                    4442 	.db #0x36	; 54	'6'
      008D88 17                    4443 	.db #0x17	; 23
      008D89 17                    4444 	.db #0x17	; 23
      008D8A 15                    4445 	.db #0x15	; 21
      008D8B 14                    4446 	.db #0x14	; 20
      008D8C 33                    4447 	.db #0x33	; 51	'3'
      008D8D 14                    4448 	.db #0x14	; 20
      008D8E 01                    4449 	.db #0x01	; 1
      008D8F 00                    4450 	.db #0x00	; 0
      008D90 00                    4451 	.db #0x00	; 0
      008D91 00                    4452 	.db #0x00	; 0
      008D92 00                    4453 	.db #0x00	; 0
      008D93 01                    4454 	.db #0x01	; 1
      008D94 14                    4455 	.db #0x14	; 20
      008D95 34                    4456 	.db #0x34	; 52	'4'
      008D96 35                    4457 	.db #0x35	; 53	'5'
      008D97 36                    4458 	.db #0x36	; 54	'6'
      008D98 35                    4459 	.db #0x35	; 53	'5'
      008D99 34                    4460 	.db #0x34	; 52	'4'
      008D9A 26                    4461 	.db #0x26	; 38
      008D9B 34                    4462 	.db #0x34	; 52	'4'
      008D9C 35                    4463 	.db #0x35	; 53	'5'
      008D9D 36                    4464 	.db #0x36	; 54	'6'
      008D9E 26                    4465 	.db #0x26	; 38
      008D9F 06                    4466 	.db #0x06	; 6
      008DA0 05                    4467 	.db #0x05	; 5
      008DA1 26                    4468 	.db #0x26	; 38
      008DA2 36                    4469 	.db #0x36	; 54	'6'
      008DA3 36                    4470 	.db #0x36	; 54	'6'
      008DA4 36                    4471 	.db #0x36	; 54	'6'
      008DA5 15                    4472 	.db #0x15	; 21
      008DA6 14                    4473 	.db #0x14	; 20
      008DA7 14                    4474 	.db #0x14	; 20
      008DA8 01                    4475 	.db #0x01	; 1
      008DA9 00                    4476 	.db #0x00	; 0
      008DAA 00                    4477 	.db #0x00	; 0
      008DAB 00                    4478 	.db #0x00	; 0
      008DAC 00                    4479 	.db #0x00	; 0
      008DAD 01                    4480 	.db #0x01	; 1
      008DAE 14                    4481 	.db #0x14	; 20
      008DAF 02                    4482 	.db #0x02	; 2
      008DB0 36                    4483 	.db #0x36	; 54	'6'
      008DB1 38                    4484 	.db #0x38	; 56	'8'
      008DB2 06                    4485 	.db #0x06	; 6
      008DB3 26                    4486 	.db #0x26	; 38
      008DB4 26                    4487 	.db #0x26	; 38
      008DB5 06                    4488 	.db #0x06	; 6
      008DB6 29                    4489 	.db #0x29	; 41
      008DB7 2B                    4490 	.db #0x2b	; 43
      008DB8 2B                    4491 	.db #0x2b	; 43
      008DB9 29                    4492 	.db #0x29	; 41
      008DBA 06                    4493 	.db #0x06	; 6
      008DBB 29                    4494 	.db #0x29	; 41
      008DBC 26                    4495 	.db #0x26	; 38
      008DBD 06                    4496 	.db #0x06	; 6
      008DBE 38                    4497 	.db #0x38	; 56	'8'
      008DBF 36                    4498 	.db #0x36	; 54	'6'
      008DC0 34                    4499 	.db #0x34	; 52	'4'
      008DC1 14                    4500 	.db #0x14	; 20
      008DC2 01                    4501 	.db #0x01	; 1
      008DC3 00                    4502 	.db #0x00	; 0
      008DC4 00                    4503 	.db #0x00	; 0
      008DC5 00                    4504 	.db #0x00	; 0
      008DC6 00                    4505 	.db #0x00	; 0
      008DC7 01                    4506 	.db #0x01	; 1
      008DC8 14                    4507 	.db #0x14	; 20
      008DC9 35                    4508 	.db #0x35	; 53	'5'
      008DCA 05                    4509 	.db #0x05	; 5
      008DCB 08                    4510 	.db #0x08	; 8
      008DCC 39                    4511 	.db #0x39	; 57	'9'
      008DCD 39                    4512 	.db #0x39	; 57	'9'
      008DCE 06                    4513 	.db #0x06	; 6
      008DCF 29                    4514 	.db #0x29	; 41
      008DD0 38                    4515 	.db #0x38	; 56	'8'
      008DD1 38                    4516 	.db #0x38	; 56	'8'
      008DD2 38                    4517 	.db #0x38	; 56	'8'
      008DD3 38                    4518 	.db #0x38	; 56	'8'
      008DD4 29                    4519 	.db #0x29	; 41
      008DD5 06                    4520 	.db #0x06	; 6
      008DD6 05                    4521 	.db #0x05	; 5
      008DD7 05                    4522 	.db #0x05	; 5
      008DD8 08                    4523 	.db #0x08	; 8
      008DD9 05                    4524 	.db #0x05	; 5
      008DDA 02                    4525 	.db #0x02	; 2
      008DDB 14                    4526 	.db #0x14	; 20
      008DDC 01                    4527 	.db #0x01	; 1
      008DDD 00                    4528 	.db #0x00	; 0
      008DDE 00                    4529 	.db #0x00	; 0
      008DDF 00                    4530 	.db #0x00	; 0
      008DE0 00                    4531 	.db #0x00	; 0
      008DE1 01                    4532 	.db #0x01	; 1
      008DE2 14                    4533 	.db #0x14	; 20
      008DE3 35                    4534 	.db #0x35	; 53	'5'
      008DE4 05                    4535 	.db #0x05	; 5
      008DE5 08                    4536 	.db #0x08	; 8
      008DE6 0C                    4537 	.db #0x0c	; 12
      008DE7 2B                    4538 	.db #0x2b	; 43
      008DE8 08                    4539 	.db #0x08	; 8
      008DE9 28                    4540 	.db #0x28	; 40
      008DEA 26                    4541 	.db #0x26	; 38
      008DEB 29                    4542 	.db #0x29	; 41
      008DEC 2B                    4543 	.db #0x2b	; 43
      008DED 26                    4544 	.db #0x26	; 38
      008DEE 28                    4545 	.db #0x28	; 40
      008DEF 05                    4546 	.db #0x05	; 5
      008DF0 2B                    4547 	.db #0x2b	; 43
      008DF1 0C                    4548 	.db #0x0c	; 12
      008DF2 08                    4549 	.db #0x08	; 8
      008DF3 05                    4550 	.db #0x05	; 5
      008DF4 35                    4551 	.db #0x35	; 53	'5'
      008DF5 14                    4552 	.db #0x14	; 20
      008DF6 01                    4553 	.db #0x01	; 1
      008DF7 00                    4554 	.db #0x00	; 0
      008DF8 00                    4555 	.db #0x00	; 0
      008DF9 00                    4556 	.db #0x00	; 0
      008DFA 00                    4557 	.db #0x00	; 0
      008DFB 01                    4558 	.db #0x01	; 1
      008DFC 14                    4559 	.db #0x14	; 20
      008DFD 35                    4560 	.db #0x35	; 53	'5'
      008DFE 06                    4561 	.db #0x06	; 6
      008DFF 2B                    4562 	.db #0x2b	; 43
      008E00 2F                    4563 	.db #0x2f	; 47
      008E01 2F                    4564 	.db #0x2f	; 47
      008E02 2B                    4565 	.db #0x2b	; 43
      008E03 29                    4566 	.db #0x29	; 41
      008E04 06                    4567 	.db #0x06	; 6
      008E05 29                    4568 	.db #0x29	; 41
      008E06 29                    4569 	.db #0x29	; 41
      008E07 38                    4570 	.db #0x38	; 56	'8'
      008E08 38                    4571 	.db #0x38	; 56	'8'
      008E09 3E                    4572 	.db #0x3e	; 62
      008E0A 0C                    4573 	.db #0x0c	; 12
      008E0B 2F                    4574 	.db #0x2f	; 47
      008E0C 2B                    4575 	.db #0x2b	; 43
      008E0D 06                    4576 	.db #0x06	; 6
      008E0E 35                    4577 	.db #0x35	; 53	'5'
      008E0F 14                    4578 	.db #0x14	; 20
      008E10 01                    4579 	.db #0x01	; 1
      008E11 00                    4580 	.db #0x00	; 0
      008E12 00                    4581 	.db #0x00	; 0
      008E13 00                    4582 	.db #0x00	; 0
      008E14 06                    4583 	.db #0x06	; 6
      008E15 15                    4584 	.db #0x15	; 21
      008E16 14                    4585 	.db #0x14	; 20
      008E17 36                    4586 	.db #0x36	; 54	'6'
      008E18 15                    4587 	.db #0x15	; 21
      008E19 15                    4588 	.db #0x15	; 21
      008E1A 17                    4589 	.db #0x17	; 23
      008E1B 08                    4590 	.db #0x08	; 8
      008E1C 0E                    4591 	.db #0x0e	; 14
      008E1D 3E                    4592 	.db #0x3e	; 62
      008E1E 29                    4593 	.db #0x29	; 41
      008E1F 06                    4594 	.db #0x06	; 6
      008E20 06                    4595 	.db #0x06	; 6
      008E21 08                    4596 	.db #0x08	; 8
      008E22 3E                    4597 	.db #0x3e	; 62
      008E23 0A                    4598 	.db #0x0a	; 10
      008E24 26                    4599 	.db #0x26	; 38
      008E25 34                    4600 	.db #0x34	; 52	'4'
      008E26 15                    4601 	.db #0x15	; 21
      008E27 15                    4602 	.db #0x15	; 21
      008E28 36                    4603 	.db #0x36	; 54	'6'
      008E29 14                    4604 	.db #0x14	; 20
      008E2A 15                    4605 	.db #0x15	; 21
      008E2B 06                    4606 	.db #0x06	; 6
      008E2C 00                    4607 	.db #0x00	; 0
      008E2D 00                    4608 	.db #0x00	; 0
      008E2E 06                    4609 	.db #0x06	; 6
      008E2F 15                    4610 	.db #0x15	; 21
      008E30 04                    4611 	.db #0x04	; 4
      008E31 35                    4612 	.db #0x35	; 53	'5'
      008E32 0A                    4613 	.db #0x0a	; 10
      008E33 38                    4614 	.db #0x38	; 56	'8'
      008E34 36                    4615 	.db #0x36	; 54	'6'
      008E35 33                    4616 	.db #0x33	; 51	'3'
      008E36 15                    4617 	.db #0x15	; 21
      008E37 17                    4618 	.db #0x17	; 23
      008E38 0A                    4619 	.db #0x0a	; 10
      008E39 2B                    4620 	.db #0x2b	; 43
      008E3A 08                    4621 	.db #0x08	; 8
      008E3B 2B                    4622 	.db #0x2b	; 43
      008E3C 06                    4623 	.db #0x06	; 6
      008E3D 15                    4624 	.db #0x15	; 21
      008E3E 33                    4625 	.db #0x33	; 51	'3'
      008E3F 36                    4626 	.db #0x36	; 54	'6'
      008E40 38                    4627 	.db #0x38	; 56	'8'
      008E41 0A                    4628 	.db #0x0a	; 10
      008E42 35                    4629 	.db #0x35	; 53	'5'
      008E43 04                    4630 	.db #0x04	; 4
      008E44 15                    4631 	.db #0x15	; 21
      008E45 06                    4632 	.db #0x06	; 6
      008E46 00                    4633 	.db #0x00	; 0
      008E47 00                    4634 	.db #0x00	; 0
      008E48 36                    4635 	.db #0x36	; 54	'6'
      008E49 15                    4636 	.db #0x15	; 21
      008E4A 17                    4637 	.db #0x17	; 23
      008E4B 15                    4638 	.db #0x15	; 21
      008E4C 36                    4639 	.db #0x36	; 54	'6'
      008E4D 00                    4640 	.db #0x00	; 0
      008E4E 1B                    4641 	.db #0x1b	; 27
      008E4F 1F                    4642 	.db #0x1f	; 31
      008E50 33                    4643 	.db #0x33	; 51	'3'
      008E51 14                    4644 	.db #0x14	; 20
      008E52 36                    4645 	.db #0x36	; 54	'6'
      008E53 0A                    4646 	.db #0x0a	; 10
      008E54 28                    4647 	.db #0x28	; 40
      008E55 36                    4648 	.db #0x36	; 54	'6'
      008E56 14                    4649 	.db #0x14	; 20
      008E57 33                    4650 	.db #0x33	; 51	'3'
      008E58 1B                    4651 	.db #0x1b	; 27
      008E59 1F                    4652 	.db #0x1f	; 31
      008E5A 00                    4653 	.db #0x00	; 0
      008E5B 36                    4654 	.db #0x36	; 54	'6'
      008E5C 15                    4655 	.db #0x15	; 21
      008E5D 17                    4656 	.db #0x17	; 23
      008E5E 15                    4657 	.db #0x15	; 21
      008E5F 36                    4658 	.db #0x36	; 54	'6'
      008E60 00                    4659 	.db #0x00	; 0
      008E61 00                    4660 	.db #0x00	; 0
      008E62 15                    4661 	.db #0x15	; 21
      008E63 02                    4662 	.db #0x02	; 2
      008E64 17                    4663 	.db #0x17	; 23
      008E65 17                    4664 	.db #0x17	; 23
      008E66 34                    4665 	.db #0x34	; 52	'4'
      008E67 1B                    4666 	.db #0x1b	; 27
      008E68 14                    4667 	.db #0x14	; 20
      008E69 00                    4668 	.db #0x00	; 0
      008E6A 1F                    4669 	.db #0x1f	; 31
      008E6B 00                    4670 	.db #0x00	; 0
      008E6C 34                    4671 	.db #0x34	; 52	'4'
      008E6D 26                    4672 	.db #0x26	; 38
      008E6E 2D                    4673 	.db #0x2d	; 45
      008E6F 34                    4674 	.db #0x34	; 52	'4'
      008E70 00                    4675 	.db #0x00	; 0
      008E71 1B                    4676 	.db #0x1b	; 27
      008E72 00                    4677 	.db #0x00	; 0
      008E73 14                    4678 	.db #0x14	; 20
      008E74 1F                    4679 	.db #0x1f	; 31
      008E75 34                    4680 	.db #0x34	; 52	'4'
      008E76 17                    4681 	.db #0x17	; 23
      008E77 17                    4682 	.db #0x17	; 23
      008E78 02                    4683 	.db #0x02	; 2
      008E79 15                    4684 	.db #0x15	; 21
      008E7A 00                    4685 	.db #0x00	; 0
      008E7B 00                    4686 	.db #0x00	; 0
      008E7C 17                    4687 	.db #0x17	; 23
      008E7D 02                    4688 	.db #0x02	; 2
      008E7E 17                    4689 	.db #0x17	; 23
      008E7F 08                    4690 	.db #0x08	; 8
      008E80 06                    4691 	.db #0x06	; 6
      008E81 02                    4692 	.db #0x02	; 2
      008E82 2A                    4693 	.db #0x2a	; 42
      008E83 2A                    4694 	.db #0x2a	; 42
      008E84 08                    4695 	.db #0x08	; 8
      008E85 2D                    4696 	.db #0x2d	; 45
      008E86 36                    4697 	.db #0x36	; 54	'6'
      008E87 28                    4698 	.db #0x28	; 40
      008E88 2B                    4699 	.db #0x2b	; 43
      008E89 36                    4700 	.db #0x36	; 54	'6'
      008E8A 2D                    4701 	.db #0x2d	; 45
      008E8B 08                    4702 	.db #0x08	; 8
      008E8C 2A                    4703 	.db #0x2a	; 42
      008E8D 2A                    4704 	.db #0x2a	; 42
      008E8E 02                    4705 	.db #0x02	; 2
      008E8F 06                    4706 	.db #0x06	; 6
      008E90 08                    4707 	.db #0x08	; 8
      008E91 17                    4708 	.db #0x17	; 23
      008E92 02                    4709 	.db #0x02	; 2
      008E93 17                    4710 	.db #0x17	; 23
      008E94 00                    4711 	.db #0x00	; 0
      008E95 00                    4712 	.db #0x00	; 0
      008E96 36                    4713 	.db #0x36	; 54	'6'
      008E97 02                    4714 	.db #0x02	; 2
      008E98 36                    4715 	.db #0x36	; 54	'6'
      008E99 08                    4716 	.db #0x08	; 8
      008E9A 2B                    4717 	.db #0x2b	; 43
      008E9B 06                    4718 	.db #0x06	; 6
      008E9C 02                    4719 	.db #0x02	; 2
      008E9D 17                    4720 	.db #0x17	; 23
      008E9E 08                    4721 	.db #0x08	; 8
      008E9F 2F                    4722 	.db #0x2f	; 47
      008EA0 29                    4723 	.db #0x29	; 41
      008EA1 08                    4724 	.db #0x08	; 8
      008EA2 0D                    4725 	.db #0x0d	; 13
      008EA3 29                    4726 	.db #0x29	; 41
      008EA4 2F                    4727 	.db #0x2f	; 47
      008EA5 08                    4728 	.db #0x08	; 8
      008EA6 17                    4729 	.db #0x17	; 23
      008EA7 02                    4730 	.db #0x02	; 2
      008EA8 06                    4731 	.db #0x06	; 6
      008EA9 2B                    4732 	.db #0x2b	; 43
      008EAA 08                    4733 	.db #0x08	; 8
      008EAB 36                    4734 	.db #0x36	; 54	'6'
      008EAC 02                    4735 	.db #0x02	; 2
      008EAD 36                    4736 	.db #0x36	; 54	'6'
      008EAE 00                    4737 	.db #0x00	; 0
      008EAF 00                    4738 	.db #0x00	; 0
      008EB0 00                    4739 	.db #0x00	; 0
      008EB1 02                    4740 	.db #0x02	; 2
      008EB2 36                    4741 	.db #0x36	; 54	'6'
      008EB3 28                    4742 	.db #0x28	; 40
      008EB4 2B                    4743 	.db #0x2b	; 43
      008EB5 2D                    4744 	.db #0x2d	; 45
      008EB6 2D                    4745 	.db #0x2d	; 45
      008EB7 2F                    4746 	.db #0x2f	; 47
      008EB8 0C                    4747 	.db #0x0c	; 12
      008EB9 2D                    4748 	.db #0x2d	; 45
      008EBA 29                    4749 	.db #0x29	; 41
      008EBB 0D                    4750 	.db #0x0d	; 13
      008EBC 20                    4751 	.db #0x20	; 32
      008EBD 29                    4752 	.db #0x29	; 41
      008EBE 2D                    4753 	.db #0x2d	; 45
      008EBF 2D                    4754 	.db #0x2d	; 45
      008EC0 0C                    4755 	.db #0x0c	; 12
      008EC1 2F                    4756 	.db #0x2f	; 47
      008EC2 2D                    4757 	.db #0x2d	; 45
      008EC3 2B                    4758 	.db #0x2b	; 43
      008EC4 28                    4759 	.db #0x28	; 40
      008EC5 36                    4760 	.db #0x36	; 54	'6'
      008EC6 02                    4761 	.db #0x02	; 2
      008EC7 00                    4762 	.db #0x00	; 0
      008EC8 00                    4763 	.db #0x00	; 0
      008EC9 00                    4764 	.db #0x00	; 0
      008ECA 00                    4765 	.db #0x00	; 0
      008ECB 02                    4766 	.db #0x02	; 2
      008ECC 36                    4767 	.db #0x36	; 54	'6'
      008ECD 36                    4768 	.db #0x36	; 54	'6'
      008ECE 06                    4769 	.db #0x06	; 6
      008ECF 38                    4770 	.db #0x38	; 56	'8'
      008ED0 2B                    4771 	.db #0x2b	; 43
      008ED1 08                    4772 	.db #0x08	; 8
      008ED2 36                    4773 	.db #0x36	; 54	'6'
      008ED3 38                    4774 	.db #0x38	; 56	'8'
      008ED4 05                    4775 	.db #0x05	; 5
      008ED5 0B                    4776 	.db #0x0b	; 11
      008ED6 0B                    4777 	.db #0x0b	; 11
      008ED7 05                    4778 	.db #0x05	; 5
      008ED8 38                    4779 	.db #0x38	; 56	'8'
      008ED9 36                    4780 	.db #0x36	; 54	'6'
      008EDA 08                    4781 	.db #0x08	; 8
      008EDB 2B                    4782 	.db #0x2b	; 43
      008EDC 38                    4783 	.db #0x38	; 56	'8'
      008EDD 28                    4784 	.db #0x28	; 40
      008EDE 36                    4785 	.db #0x36	; 54	'6'
      008EDF 36                    4786 	.db #0x36	; 54	'6'
      008EE0 02                    4787 	.db #0x02	; 2
      008EE1 00                    4788 	.db #0x00	; 0
      008EE2 00                    4789 	.db #0x00	; 0
      008EE3 00                    4790 	.db #0x00	; 0
      008EE4 00                    4791 	.db #0x00	; 0
      008EE5 02                    4792 	.db #0x02	; 2
      008EE6 26                    4793 	.db #0x26	; 38
      008EE7 03                    4794 	.db #0x03	; 3
      008EE8 03                    4795 	.db #0x03	; 3
      008EE9 26                    4796 	.db #0x26	; 38
      008EEA 2B                    4797 	.db #0x2b	; 43
      008EEB 36                    4798 	.db #0x36	; 54	'6'
      008EEC 17                    4799 	.db #0x17	; 23
      008EED 34                    4800 	.db #0x34	; 52	'4'
      008EEE 35                    4801 	.db #0x35	; 53	'5'
      008EEF 17                    4802 	.db #0x17	; 23
      008EF0 17                    4803 	.db #0x17	; 23
      008EF1 35                    4804 	.db #0x35	; 53	'5'
      008EF2 34                    4805 	.db #0x34	; 52	'4'
      008EF3 17                    4806 	.db #0x17	; 23
      008EF4 36                    4807 	.db #0x36	; 54	'6'
      008EF5 2B                    4808 	.db #0x2b	; 43
      008EF6 26                    4809 	.db #0x26	; 38
      008EF7 03                    4810 	.db #0x03	; 3
      008EF8 03                    4811 	.db #0x03	; 3
      008EF9 26                    4812 	.db #0x26	; 38
      008EFA 02                    4813 	.db #0x02	; 2
      008EFB 00                    4814 	.db #0x00	; 0
      008EFC 00                    4815 	.db #0x00	; 0
      008EFD 00                    4816 	.db #0x00	; 0
      008EFE 00                    4817 	.db #0x00	; 0
      008EFF 00                    4818 	.db #0x00	; 0
      008F00 36                    4819 	.db #0x36	; 54	'6'
      008F01 36                    4820 	.db #0x36	; 54	'6'
      008F02 17                    4821 	.db #0x17	; 23
      008F03 26                    4822 	.db #0x26	; 38
      008F04 29                    4823 	.db #0x29	; 41
      008F05 15                    4824 	.db #0x15	; 21
      008F06 06                    4825 	.db #0x06	; 6
      008F07 29                    4826 	.db #0x29	; 41
      008F08 05                    4827 	.db #0x05	; 5
      008F09 15                    4828 	.db #0x15	; 21
      008F0A 15                    4829 	.db #0x15	; 21
      008F0B 05                    4830 	.db #0x05	; 5
      008F0C 29                    4831 	.db #0x29	; 41
      008F0D 06                    4832 	.db #0x06	; 6
      008F0E 15                    4833 	.db #0x15	; 21
      008F0F 29                    4834 	.db #0x29	; 41
      008F10 26                    4835 	.db #0x26	; 38
      008F11 17                    4836 	.db #0x17	; 23
      008F12 26                    4837 	.db #0x26	; 38
      008F13 36                    4838 	.db #0x36	; 54	'6'
      008F14 00                    4839 	.db #0x00	; 0
      008F15 00                    4840 	.db #0x00	; 0
      008F16 00                    4841 	.db #0x00	; 0
      008F17 00                    4842 	.db #0x00	; 0
      008F18 00                    4843 	.db #0x00	; 0
      008F19 00                    4844 	.db #0x00	; 0
      008F1A 03                    4845 	.db #0x03	; 3
      008F1B 26                    4846 	.db #0x26	; 38
      008F1C 03                    4847 	.db #0x03	; 3
      008F1D 26                    4848 	.db #0x26	; 38
      008F1E 08                    4849 	.db #0x08	; 8
      008F1F 35                    4850 	.db #0x35	; 53	'5'
      008F20 06                    4851 	.db #0x06	; 6
      008F21 2D                    4852 	.db #0x2d	; 45
      008F22 29                    4853 	.db #0x29	; 41
      008F23 29                    4854 	.db #0x29	; 41
      008F24 29                    4855 	.db #0x29	; 41
      008F25 29                    4856 	.db #0x29	; 41
      008F26 2D                    4857 	.db #0x2d	; 45
      008F27 06                    4858 	.db #0x06	; 6
      008F28 35                    4859 	.db #0x35	; 53	'5'
      008F29 08                    4860 	.db #0x08	; 8
      008F2A 26                    4861 	.db #0x26	; 38
      008F2B 03                    4862 	.db #0x03	; 3
      008F2C 28                    4863 	.db #0x28	; 40
      008F2D 03                    4864 	.db #0x03	; 3
      008F2E 00                    4865 	.db #0x00	; 0
      008F2F 00                    4866 	.db #0x00	; 0
      008F30 00                    4867 	.db #0x00	; 0
      008F31 00                    4868 	.db #0x00	; 0
      008F32 00                    4869 	.db #0x00	; 0
      008F33 00                    4870 	.db #0x00	; 0
      008F34 00                    4871 	.db #0x00	; 0
      008F35 36                    4872 	.db #0x36	; 54	'6'
      008F36 03                    4873 	.db #0x03	; 3
      008F37 05                    4874 	.db #0x05	; 5
      008F38 28                    4875 	.db #0x28	; 40
      008F39 05                    4876 	.db #0x05	; 5
      008F3A 29                    4877 	.db #0x29	; 41
      008F3B 38                    4878 	.db #0x38	; 56	'8'
      008F3C 35                    4879 	.db #0x35	; 53	'5'
      008F3D 35                    4880 	.db #0x35	; 53	'5'
      008F3E 35                    4881 	.db #0x35	; 53	'5'
      008F3F 35                    4882 	.db #0x35	; 53	'5'
      008F40 38                    4883 	.db #0x38	; 56	'8'
      008F41 29                    4884 	.db #0x29	; 41
      008F42 05                    4885 	.db #0x05	; 5
      008F43 28                    4886 	.db #0x28	; 40
      008F44 05                    4887 	.db #0x05	; 5
      008F45 03                    4888 	.db #0x03	; 3
      008F46 26                    4889 	.db #0x26	; 38
      008F47 00                    4890 	.db #0x00	; 0
      008F48 00                    4891 	.db #0x00	; 0
      008F49 00                    4892 	.db #0x00	; 0
      008F4A 00                    4893 	.db #0x00	; 0
      008F4B 00                    4894 	.db #0x00	; 0
      008F4C 00                    4895 	.db #0x00	; 0
      008F4D 00                    4896 	.db #0x00	; 0
      008F4E 00                    4897 	.db #0x00	; 0
      008F4F 17                    4898 	.db #0x17	; 23
      008F50 03                    4899 	.db #0x03	; 3
      008F51 17                    4900 	.db #0x17	; 23
      008F52 28                    4901 	.db #0x28	; 40
      008F53 05                    4902 	.db #0x05	; 5
      008F54 06                    4903 	.db #0x06	; 6
      008F55 37                    4904 	.db #0x37	; 55	'7'
      008F56 2A                    4905 	.db #0x2a	; 42
      008F57 1B                    4906 	.db #0x1b	; 27
      008F58 1B                    4907 	.db #0x1b	; 27
      008F59 2A                    4908 	.db #0x2a	; 42
      008F5A 37                    4909 	.db #0x37	; 55	'7'
      008F5B 06                    4910 	.db #0x06	; 6
      008F5C 05                    4911 	.db #0x05	; 5
      008F5D 28                    4912 	.db #0x28	; 40
      008F5E 03                    4913 	.db #0x03	; 3
      008F5F 03                    4914 	.db #0x03	; 3
      008F60 17                    4915 	.db #0x17	; 23
      008F61 00                    4916 	.db #0x00	; 0
      008F62 00                    4917 	.db #0x00	; 0
      008F63 00                    4918 	.db #0x00	; 0
      008F64 00                    4919 	.db #0x00	; 0
      008F65 00                    4920 	.db #0x00	; 0
      008F66 00                    4921 	.db #0x00	; 0
      008F67 00                    4922 	.db #0x00	; 0
      008F68 00                    4923 	.db #0x00	; 0
      008F69 35                    4924 	.db #0x35	; 53	'5'
      008F6A 03                    4925 	.db #0x03	; 3
      008F6B 03                    4926 	.db #0x03	; 3
      008F6C 26                    4927 	.db #0x26	; 38
      008F6D 38                    4928 	.db #0x38	; 56	'8'
      008F6E 05                    4929 	.db #0x05	; 5
      008F6F 00                    4930 	.db #0x00	; 0
      008F70 00                    4931 	.db #0x00	; 0
      008F71 00                    4932 	.db #0x00	; 0
      008F72 00                    4933 	.db #0x00	; 0
      008F73 00                    4934 	.db #0x00	; 0
      008F74 00                    4935 	.db #0x00	; 0
      008F75 05                    4936 	.db #0x05	; 5
      008F76 38                    4937 	.db #0x38	; 56	'8'
      008F77 26                    4938 	.db #0x26	; 38
      008F78 35                    4939 	.db #0x35	; 53	'5'
      008F79 03                    4940 	.db #0x03	; 3
      008F7A 35                    4941 	.db #0x35	; 53	'5'
      008F7B 00                    4942 	.db #0x00	; 0
      008F7C 00                    4943 	.db #0x00	; 0
      008F7D 00                    4944 	.db #0x00	; 0
      008F7E 00                    4945 	.db #0x00	; 0
      008F7F 00                    4946 	.db #0x00	; 0
      008F80 00                    4947 	.db #0x00	; 0
      008F81 00                    4948 	.db #0x00	; 0
      008F82 00                    4949 	.db #0x00	; 0
      008F83 00                    4950 	.db #0x00	; 0
      008F84 03                    4951 	.db #0x03	; 3
      008F85 35                    4952 	.db #0x35	; 53	'5'
      008F86 36                    4953 	.db #0x36	; 54	'6'
      008F87 28                    4954 	.db #0x28	; 40
      008F88 17                    4955 	.db #0x17	; 23
      008F89 00                    4956 	.db #0x00	; 0
      008F8A 13                    4957 	.db #0x13	; 19
      008F8B 00                    4958 	.db #0x00	; 0
      008F8C 00                    4959 	.db #0x00	; 0
      008F8D 13                    4960 	.db #0x13	; 19
      008F8E 00                    4961 	.db #0x00	; 0
      008F8F 17                    4962 	.db #0x17	; 23
      008F90 28                    4963 	.db #0x28	; 40
      008F91 36                    4964 	.db #0x36	; 54	'6'
      008F92 35                    4965 	.db #0x35	; 53	'5'
      008F93 03                    4966 	.db #0x03	; 3
      008F94 00                    4967 	.db #0x00	; 0
      008F95 00                    4968 	.db #0x00	; 0
      008F96 00                    4969 	.db #0x00	; 0
      008F97 00                    4970 	.db #0x00	; 0
      008F98 00                    4971 	.db #0x00	; 0
      008F99 00                    4972 	.db #0x00	; 0
      008F9A 00                    4973 	.db #0x00	; 0
      008F9B 00                    4974 	.db #0x00	; 0
      008F9C 00                    4975 	.db #0x00	; 0
      008F9D 00                    4976 	.db #0x00	; 0
      008F9E 35                    4977 	.db #0x35	; 53	'5'
      008F9F 35                    4978 	.db #0x35	; 53	'5'
      008FA0 17                    4979 	.db #0x17	; 23
      008FA1 08                    4980 	.db #0x08	; 8
      008FA2 26                    4981 	.db #0x26	; 38
      008FA3 2A                    4982 	.db #0x2a	; 42
      008FA4 25                    4983 	.db #0x25	; 37
      008FA5 24                    4984 	.db #0x24	; 36
      008FA6 24                    4985 	.db #0x24	; 36
      008FA7 25                    4986 	.db #0x25	; 37
      008FA8 2A                    4987 	.db #0x2a	; 42
      008FA9 26                    4988 	.db #0x26	; 38
      008FAA 08                    4989 	.db #0x08	; 8
      008FAB 17                    4990 	.db #0x17	; 23
      008FAC 35                    4991 	.db #0x35	; 53	'5'
      008FAD 35                    4992 	.db #0x35	; 53	'5'
      008FAE 00                    4993 	.db #0x00	; 0
      008FAF 00                    4994 	.db #0x00	; 0
      008FB0 00                    4995 	.db #0x00	; 0
      008FB1 00                    4996 	.db #0x00	; 0
      008FB2 00                    4997 	.db #0x00	; 0
      008FB3 00                    4998 	.db #0x00	; 0
      008FB4 00                    4999 	.db #0x00	; 0
      008FB5 00                    5000 	.db #0x00	; 0
      008FB6 00                    5001 	.db #0x00	; 0
      008FB7 00                    5002 	.db #0x00	; 0
      008FB8 00                    5003 	.db #0x00	; 0
      008FB9 35                    5004 	.db #0x35	; 53	'5'
      008FBA 03                    5005 	.db #0x03	; 3
      008FBB 06                    5006 	.db #0x06	; 6
      008FBC 38                    5007 	.db #0x38	; 56	'8'
      008FBD 36                    5008 	.db #0x36	; 54	'6'
      008FBE 2A                    5009 	.db #0x2a	; 42
      008FBF 1B                    5010 	.db #0x1b	; 27
      008FC0 1B                    5011 	.db #0x1b	; 27
      008FC1 2A                    5012 	.db #0x2a	; 42
      008FC2 36                    5013 	.db #0x36	; 54	'6'
      008FC3 38                    5014 	.db #0x38	; 56	'8'
      008FC4 06                    5015 	.db #0x06	; 6
      008FC5 03                    5016 	.db #0x03	; 3
      008FC6 35                    5017 	.db #0x35	; 53	'5'
      008FC7 00                    5018 	.db #0x00	; 0
      008FC8 00                    5019 	.db #0x00	; 0
      008FC9 00                    5020 	.db #0x00	; 0
      008FCA 00                    5021 	.db #0x00	; 0
      008FCB 00                    5022 	.db #0x00	; 0
      008FCC 00                    5023 	.db #0x00	; 0
      008FCD 00                    5024 	.db #0x00	; 0
      008FCE 00                    5025 	.db #0x00	; 0
      008FCF 00                    5026 	.db #0x00	; 0
      008FD0 00                    5027 	.db #0x00	; 0
      008FD1 00                    5028 	.db #0x00	; 0
      008FD2 00                    5029 	.db #0x00	; 0
      008FD3 00                    5030 	.db #0x00	; 0
      008FD4 35                    5031 	.db #0x35	; 53	'5'
      008FD5 36                    5032 	.db #0x36	; 54	'6'
      008FD6 38                    5033 	.db #0x38	; 56	'8'
      008FD7 38                    5034 	.db #0x38	; 56	'8'
      008FD8 36                    5035 	.db #0x36	; 54	'6'
      008FD9 03                    5036 	.db #0x03	; 3
      008FDA 03                    5037 	.db #0x03	; 3
      008FDB 36                    5038 	.db #0x36	; 54	'6'
      008FDC 38                    5039 	.db #0x38	; 56	'8'
      008FDD 38                    5040 	.db #0x38	; 56	'8'
      008FDE 36                    5041 	.db #0x36	; 54	'6'
      008FDF 35                    5042 	.db #0x35	; 53	'5'
      008FE0 00                    5043 	.db #0x00	; 0
      008FE1 00                    5044 	.db #0x00	; 0
      008FE2 00                    5045 	.db #0x00	; 0
      008FE3 00                    5046 	.db #0x00	; 0
      008FE4 00                    5047 	.db #0x00	; 0
      008FE5 00                    5048 	.db #0x00	; 0
      008FE6 00                    5049 	.db #0x00	; 0
      008FE7 00                    5050 	.db #0x00	; 0
      008FE8 00                    5051 	.db #0x00	; 0
      008FE9 00                    5052 	.db #0x00	; 0
      008FEA 00                    5053 	.db #0x00	; 0
      008FEB 00                    5054 	.db #0x00	; 0
      008FEC 00                    5055 	.db #0x00	; 0
      008FED 00                    5056 	.db #0x00	; 0
      008FEE 00                    5057 	.db #0x00	; 0
      008FEF 35                    5058 	.db #0x35	; 53	'5'
      008FF0 05                    5059 	.db #0x05	; 5
      008FF1 39                    5060 	.db #0x39	; 57	'9'
      008FF2 0C                    5061 	.db #0x0c	; 12
      008FF3 3D                    5062 	.db #0x3d	; 61
      008FF4 3D                    5063 	.db #0x3d	; 61
      008FF5 0C                    5064 	.db #0x0c	; 12
      008FF6 39                    5065 	.db #0x39	; 57	'9'
      008FF7 05                    5066 	.db #0x05	; 5
      008FF8 35                    5067 	.db #0x35	; 53	'5'
      008FF9 00                    5068 	.db #0x00	; 0
      008FFA 00                    5069 	.db #0x00	; 0
      008FFB 00                    5070 	.db #0x00	; 0
      008FFC 00                    5071 	.db #0x00	; 0
      008FFD 00                    5072 	.db #0x00	; 0
      008FFE 00                    5073 	.db #0x00	; 0
      008FFF 00                    5074 	.db #0x00	; 0
      009000                       5075 _doom6_raw:
      009000 00                    5076 	.db #0x00	; 0
      009001 00                    5077 	.db #0x00	; 0
      009002 00                    5078 	.db #0x00	; 0
      009003 00                    5079 	.db #0x00	; 0
      009004 00                    5080 	.db #0x00	; 0
      009005 00                    5081 	.db #0x00	; 0
      009006 14                    5082 	.db #0x14	; 20
      009007 02                    5083 	.db #0x02	; 2
      009008 02                    5084 	.db #0x02	; 2
      009009 02                    5085 	.db #0x02	; 2
      00900A 15                    5086 	.db #0x15	; 21
      00900B 35                    5087 	.db #0x35	; 53	'5'
      00900C 35                    5088 	.db #0x35	; 53	'5'
      00900D 35                    5089 	.db #0x35	; 53	'5'
      00900E 35                    5090 	.db #0x35	; 53	'5'
      00900F 35                    5091 	.db #0x35	; 53	'5'
      009010 15                    5092 	.db #0x15	; 21
      009011 02                    5093 	.db #0x02	; 2
      009012 02                    5094 	.db #0x02	; 2
      009013 14                    5095 	.db #0x14	; 20
      009014 00                    5096 	.db #0x00	; 0
      009015 00                    5097 	.db #0x00	; 0
      009016 00                    5098 	.db #0x00	; 0
      009017 00                    5099 	.db #0x00	; 0
      009018 00                    5100 	.db #0x00	; 0
      009019 00                    5101 	.db #0x00	; 0
      00901A 00                    5102 	.db #0x00	; 0
      00901B 00                    5103 	.db #0x00	; 0
      00901C 00                    5104 	.db #0x00	; 0
      00901D 00                    5105 	.db #0x00	; 0
      00901E 22                    5106 	.db #0x22	; 34
      00901F 02                    5107 	.db #0x02	; 2
      009020 34                    5108 	.db #0x34	; 52	'4'
      009021 03                    5109 	.db #0x03	; 3
      009022 36                    5110 	.db #0x36	; 54	'6'
      009023 38                    5111 	.db #0x38	; 56	'8'
      009024 28                    5112 	.db #0x28	; 40
      009025 08                    5113 	.db #0x08	; 8
      009026 08                    5114 	.db #0x08	; 8
      009027 08                    5115 	.db #0x08	; 8
      009028 28                    5116 	.db #0x28	; 40
      009029 38                    5117 	.db #0x38	; 56	'8'
      00902A 05                    5118 	.db #0x05	; 5
      00902B 35                    5119 	.db #0x35	; 53	'5'
      00902C 02                    5120 	.db #0x02	; 2
      00902D 34                    5121 	.db #0x34	; 52	'4'
      00902E 02                    5122 	.db #0x02	; 2
      00902F 22                    5123 	.db #0x22	; 34
      009030 00                    5124 	.db #0x00	; 0
      009031 00                    5125 	.db #0x00	; 0
      009032 00                    5126 	.db #0x00	; 0
      009033 00                    5127 	.db #0x00	; 0
      009034 00                    5128 	.db #0x00	; 0
      009035 00                    5129 	.db #0x00	; 0
      009036 00                    5130 	.db #0x00	; 0
      009037 22                    5131 	.db #0x22	; 34
      009038 02                    5132 	.db #0x02	; 2
      009039 35                    5133 	.db #0x35	; 53	'5'
      00903A 36                    5134 	.db #0x36	; 54	'6'
      00903B 38                    5135 	.db #0x38	; 56	'8'
      00903C 28                    5136 	.db #0x28	; 40
      00903D 39                    5137 	.db #0x39	; 57	'9'
      00903E 08                    5138 	.db #0x08	; 8
      00903F 28                    5139 	.db #0x28	; 40
      009040 06                    5140 	.db #0x06	; 6
      009041 05                    5141 	.db #0x05	; 5
      009042 05                    5142 	.db #0x05	; 5
      009043 05                    5143 	.db #0x05	; 5
      009044 36                    5144 	.db #0x36	; 54	'6'
      009045 36                    5145 	.db #0x36	; 54	'6'
      009046 35                    5146 	.db #0x35	; 53	'5'
      009047 35                    5147 	.db #0x35	; 53	'5'
      009048 34                    5148 	.db #0x34	; 52	'4'
      009049 14                    5149 	.db #0x14	; 20
      00904A 22                    5150 	.db #0x22	; 34
      00904B 00                    5151 	.db #0x00	; 0
      00904C 00                    5152 	.db #0x00	; 0
      00904D 00                    5153 	.db #0x00	; 0
      00904E 00                    5154 	.db #0x00	; 0
      00904F 00                    5155 	.db #0x00	; 0
      009050 00                    5156 	.db #0x00	; 0
      009051 22                    5157 	.db #0x22	; 34
      009052 35                    5158 	.db #0x35	; 53	'5'
      009053 17                    5159 	.db #0x17	; 23
      009054 35                    5160 	.db #0x35	; 53	'5'
      009055 36                    5161 	.db #0x36	; 54	'6'
      009056 05                    5162 	.db #0x05	; 5
      009057 06                    5163 	.db #0x06	; 6
      009058 17                    5164 	.db #0x17	; 23
      009059 38                    5165 	.db #0x38	; 56	'8'
      00905A 36                    5166 	.db #0x36	; 54	'6'
      00905B 26                    5167 	.db #0x26	; 38
      00905C 35                    5168 	.db #0x35	; 53	'5'
      00905D 35                    5169 	.db #0x35	; 53	'5'
      00905E 35                    5170 	.db #0x35	; 53	'5'
      00905F 35                    5171 	.db #0x35	; 53	'5'
      009060 02                    5172 	.db #0x02	; 2
      009061 34                    5173 	.db #0x34	; 52	'4'
      009062 22                    5174 	.db #0x22	; 34
      009063 22                    5175 	.db #0x22	; 34
      009064 01                    5176 	.db #0x01	; 1
      009065 00                    5177 	.db #0x00	; 0
      009066 00                    5178 	.db #0x00	; 0
      009067 00                    5179 	.db #0x00	; 0
      009068 00                    5180 	.db #0x00	; 0
      009069 00                    5181 	.db #0x00	; 0
      00906A 01                    5182 	.db #0x01	; 1
      00906B 33                    5183 	.db #0x33	; 51	'3'
      00906C 02                    5184 	.db #0x02	; 2
      00906D 35                    5185 	.db #0x35	; 53	'5'
      00906E 02                    5186 	.db #0x02	; 2
      00906F 36                    5187 	.db #0x36	; 54	'6'
      009070 05                    5188 	.db #0x05	; 5
      009071 36                    5189 	.db #0x36	; 54	'6'
      009072 36                    5190 	.db #0x36	; 54	'6'
      009073 36                    5191 	.db #0x36	; 54	'6'
      009074 36                    5192 	.db #0x36	; 54	'6'
      009075 14                    5193 	.db #0x14	; 20
      009076 36                    5194 	.db #0x36	; 54	'6'
      009077 02                    5195 	.db #0x02	; 2
      009078 14                    5196 	.db #0x14	; 20
      009079 02                    5197 	.db #0x02	; 2
      00907A 14                    5198 	.db #0x14	; 20
      00907B 22                    5199 	.db #0x22	; 34
      00907C 01                    5200 	.db #0x01	; 1
      00907D 01                    5201 	.db #0x01	; 1
      00907E 01                    5202 	.db #0x01	; 1
      00907F 01                    5203 	.db #0x01	; 1
      009080 00                    5204 	.db #0x00	; 0
      009081 00                    5205 	.db #0x00	; 0
      009082 00                    5206 	.db #0x00	; 0
      009083 00                    5207 	.db #0x00	; 0
      009084 01                    5208 	.db #0x01	; 1
      009085 33                    5209 	.db #0x33	; 51	'3'
      009086 14                    5210 	.db #0x14	; 20
      009087 34                    5211 	.db #0x34	; 52	'4'
      009088 02                    5212 	.db #0x02	; 2
      009089 36                    5213 	.db #0x36	; 54	'6'
      00908A 34                    5214 	.db #0x34	; 52	'4'
      00908B 05                    5215 	.db #0x05	; 5
      00908C 15                    5216 	.db #0x15	; 21
      00908D 15                    5217 	.db #0x15	; 21
      00908E 36                    5218 	.db #0x36	; 54	'6'
      00908F 15                    5219 	.db #0x15	; 21
      009090 14                    5220 	.db #0x14	; 20
      009091 15                    5221 	.db #0x15	; 21
      009092 14                    5222 	.db #0x14	; 20
      009093 33                    5223 	.db #0x33	; 51	'3'
      009094 02                    5224 	.db #0x02	; 2
      009095 01                    5225 	.db #0x01	; 1
      009096 22                    5226 	.db #0x22	; 34
      009097 22                    5227 	.db #0x22	; 34
      009098 33                    5228 	.db #0x33	; 51	'3'
      009099 01                    5229 	.db #0x01	; 1
      00909A 00                    5230 	.db #0x00	; 0
      00909B 00                    5231 	.db #0x00	; 0
      00909C 00                    5232 	.db #0x00	; 0
      00909D 00                    5233 	.db #0x00	; 0
      00909E 01                    5234 	.db #0x01	; 1
      00909F 14                    5235 	.db #0x14	; 20
      0090A0 14                    5236 	.db #0x14	; 20
      0090A1 35                    5237 	.db #0x35	; 53	'5'
      0090A2 35                    5238 	.db #0x35	; 53	'5'
      0090A3 34                    5239 	.db #0x34	; 52	'4'
      0090A4 36                    5240 	.db #0x36	; 54	'6'
      0090A5 34                    5241 	.db #0x34	; 52	'4'
      0090A6 15                    5242 	.db #0x15	; 21
      0090A7 35                    5243 	.db #0x35	; 53	'5'
      0090A8 15                    5244 	.db #0x15	; 21
      0090A9 15                    5245 	.db #0x15	; 21
      0090AA 36                    5246 	.db #0x36	; 54	'6'
      0090AB 36                    5247 	.db #0x36	; 54	'6'
      0090AC 36                    5248 	.db #0x36	; 54	'6'
      0090AD 17                    5249 	.db #0x17	; 23
      0090AE 17                    5250 	.db #0x17	; 23
      0090AF 15                    5251 	.db #0x15	; 21
      0090B0 14                    5252 	.db #0x14	; 20
      0090B1 33                    5253 	.db #0x33	; 51	'3'
      0090B2 14                    5254 	.db #0x14	; 20
      0090B3 01                    5255 	.db #0x01	; 1
      0090B4 00                    5256 	.db #0x00	; 0
      0090B5 00                    5257 	.db #0x00	; 0
      0090B6 00                    5258 	.db #0x00	; 0
      0090B7 00                    5259 	.db #0x00	; 0
      0090B8 01                    5260 	.db #0x01	; 1
      0090B9 14                    5261 	.db #0x14	; 20
      0090BA 34                    5262 	.db #0x34	; 52	'4'
      0090BB 35                    5263 	.db #0x35	; 53	'5'
      0090BC 36                    5264 	.db #0x36	; 54	'6'
      0090BD 35                    5265 	.db #0x35	; 53	'5'
      0090BE 34                    5266 	.db #0x34	; 52	'4'
      0090BF 26                    5267 	.db #0x26	; 38
      0090C0 34                    5268 	.db #0x34	; 52	'4'
      0090C1 35                    5269 	.db #0x35	; 53	'5'
      0090C2 36                    5270 	.db #0x36	; 54	'6'
      0090C3 26                    5271 	.db #0x26	; 38
      0090C4 06                    5272 	.db #0x06	; 6
      0090C5 05                    5273 	.db #0x05	; 5
      0090C6 26                    5274 	.db #0x26	; 38
      0090C7 36                    5275 	.db #0x36	; 54	'6'
      0090C8 36                    5276 	.db #0x36	; 54	'6'
      0090C9 36                    5277 	.db #0x36	; 54	'6'
      0090CA 15                    5278 	.db #0x15	; 21
      0090CB 14                    5279 	.db #0x14	; 20
      0090CC 14                    5280 	.db #0x14	; 20
      0090CD 01                    5281 	.db #0x01	; 1
      0090CE 00                    5282 	.db #0x00	; 0
      0090CF 00                    5283 	.db #0x00	; 0
      0090D0 00                    5284 	.db #0x00	; 0
      0090D1 00                    5285 	.db #0x00	; 0
      0090D2 01                    5286 	.db #0x01	; 1
      0090D3 14                    5287 	.db #0x14	; 20
      0090D4 02                    5288 	.db #0x02	; 2
      0090D5 36                    5289 	.db #0x36	; 54	'6'
      0090D6 38                    5290 	.db #0x38	; 56	'8'
      0090D7 06                    5291 	.db #0x06	; 6
      0090D8 26                    5292 	.db #0x26	; 38
      0090D9 26                    5293 	.db #0x26	; 38
      0090DA 06                    5294 	.db #0x06	; 6
      0090DB 06                    5295 	.db #0x06	; 6
      0090DC 06                    5296 	.db #0x06	; 6
      0090DD 06                    5297 	.db #0x06	; 6
      0090DE 06                    5298 	.db #0x06	; 6
      0090DF 06                    5299 	.db #0x06	; 6
      0090E0 26                    5300 	.db #0x26	; 38
      0090E1 26                    5301 	.db #0x26	; 38
      0090E2 06                    5302 	.db #0x06	; 6
      0090E3 38                    5303 	.db #0x38	; 56	'8'
      0090E4 36                    5304 	.db #0x36	; 54	'6'
      0090E5 34                    5305 	.db #0x34	; 52	'4'
      0090E6 14                    5306 	.db #0x14	; 20
      0090E7 01                    5307 	.db #0x01	; 1
      0090E8 00                    5308 	.db #0x00	; 0
      0090E9 00                    5309 	.db #0x00	; 0
      0090EA 00                    5310 	.db #0x00	; 0
      0090EB 00                    5311 	.db #0x00	; 0
      0090EC 01                    5312 	.db #0x01	; 1
      0090ED 14                    5313 	.db #0x14	; 20
      0090EE 35                    5314 	.db #0x35	; 53	'5'
      0090EF 05                    5315 	.db #0x05	; 5
      0090F0 08                    5316 	.db #0x08	; 8
      0090F1 39                    5317 	.db #0x39	; 57	'9'
      0090F2 39                    5318 	.db #0x39	; 57	'9'
      0090F3 06                    5319 	.db #0x06	; 6
      0090F4 26                    5320 	.db #0x26	; 38
      0090F5 38                    5321 	.db #0x38	; 56	'8'
      0090F6 38                    5322 	.db #0x38	; 56	'8'
      0090F7 38                    5323 	.db #0x38	; 56	'8'
      0090F8 38                    5324 	.db #0x38	; 56	'8'
      0090F9 26                    5325 	.db #0x26	; 38
      0090FA 06                    5326 	.db #0x06	; 6
      0090FB 39                    5327 	.db #0x39	; 57	'9'
      0090FC 39                    5328 	.db #0x39	; 57	'9'
      0090FD 08                    5329 	.db #0x08	; 8
      0090FE 05                    5330 	.db #0x05	; 5
      0090FF 02                    5331 	.db #0x02	; 2
      009100 14                    5332 	.db #0x14	; 20
      009101 01                    5333 	.db #0x01	; 1
      009102 00                    5334 	.db #0x00	; 0
      009103 00                    5335 	.db #0x00	; 0
      009104 00                    5336 	.db #0x00	; 0
      009105 00                    5337 	.db #0x00	; 0
      009106 01                    5338 	.db #0x01	; 1
      009107 14                    5339 	.db #0x14	; 20
      009108 35                    5340 	.db #0x35	; 53	'5'
      009109 05                    5341 	.db #0x05	; 5
      00910A 08                    5342 	.db #0x08	; 8
      00910B 0C                    5343 	.db #0x0c	; 12
      00910C 2B                    5344 	.db #0x2b	; 43
      00910D 08                    5345 	.db #0x08	; 8
      00910E 28                    5346 	.db #0x28	; 40
      00910F 26                    5347 	.db #0x26	; 38
      009110 36                    5348 	.db #0x36	; 54	'6'
      009111 36                    5349 	.db #0x36	; 54	'6'
      009112 26                    5350 	.db #0x26	; 38
      009113 28                    5351 	.db #0x28	; 40
      009114 08                    5352 	.db #0x08	; 8
      009115 2B                    5353 	.db #0x2b	; 43
      009116 0C                    5354 	.db #0x0c	; 12
      009117 08                    5355 	.db #0x08	; 8
      009118 05                    5356 	.db #0x05	; 5
      009119 35                    5357 	.db #0x35	; 53	'5'
      00911A 14                    5358 	.db #0x14	; 20
      00911B 01                    5359 	.db #0x01	; 1
      00911C 00                    5360 	.db #0x00	; 0
      00911D 00                    5361 	.db #0x00	; 0
      00911E 00                    5362 	.db #0x00	; 0
      00911F 00                    5363 	.db #0x00	; 0
      009120 01                    5364 	.db #0x01	; 1
      009121 14                    5365 	.db #0x14	; 20
      009122 35                    5366 	.db #0x35	; 53	'5'
      009123 33                    5367 	.db #0x33	; 51	'3'
      009124 00                    5368 	.db #0x00	; 0
      009125 34                    5369 	.db #0x34	; 52	'4'
      009126 05                    5370 	.db #0x05	; 5
      009127 2B                    5371 	.db #0x2b	; 43
      009128 2B                    5372 	.db #0x2b	; 43
      009129 08                    5373 	.db #0x08	; 8
      00912A 29                    5374 	.db #0x29	; 41
      00912B 29                    5375 	.db #0x29	; 41
      00912C 08                    5376 	.db #0x08	; 8
      00912D 2B                    5377 	.db #0x2b	; 43
      00912E 2B                    5378 	.db #0x2b	; 43
      00912F 2F                    5379 	.db #0x2f	; 47
      009130 2F                    5380 	.db #0x2f	; 47
      009131 2B                    5381 	.db #0x2b	; 43
      009132 06                    5382 	.db #0x06	; 6
      009133 35                    5383 	.db #0x35	; 53	'5'
      009134 14                    5384 	.db #0x14	; 20
      009135 01                    5385 	.db #0x01	; 1
      009136 00                    5386 	.db #0x00	; 0
      009137 00                    5387 	.db #0x00	; 0
      009138 00                    5388 	.db #0x00	; 0
      009139 06                    5389 	.db #0x06	; 6
      00913A 15                    5390 	.db #0x15	; 21
      00913B 14                    5391 	.db #0x14	; 20
      00913C 35                    5392 	.db #0x35	; 53	'5'
      00913D 17                    5393 	.db #0x17	; 23
      00913E 35                    5394 	.db #0x35	; 53	'5'
      00913F 33                    5395 	.db #0x33	; 51	'3'
      009140 00                    5396 	.db #0x00	; 0
      009141 05                    5397 	.db #0x05	; 5
      009142 2F                    5398 	.db #0x2f	; 47
      009143 28                    5399 	.db #0x28	; 40
      009144 2D                    5400 	.db #0x2d	; 45
      009145 2D                    5401 	.db #0x2d	; 45
      009146 28                    5402 	.db #0x28	; 40
      009147 2F                    5403 	.db #0x2f	; 47
      009148 0A                    5404 	.db #0x0a	; 10
      009149 26                    5405 	.db #0x26	; 38
      00914A 34                    5406 	.db #0x34	; 52	'4'
      00914B 33                    5407 	.db #0x33	; 51	'3'
      00914C 33                    5408 	.db #0x33	; 51	'3'
      00914D 35                    5409 	.db #0x35	; 53	'5'
      00914E 14                    5410 	.db #0x14	; 20
      00914F 15                    5411 	.db #0x15	; 21
      009150 06                    5412 	.db #0x06	; 6
      009151 00                    5413 	.db #0x00	; 0
      009152 00                    5414 	.db #0x00	; 0
      009153 06                    5415 	.db #0x06	; 6
      009154 15                    5416 	.db #0x15	; 21
      009155 04                    5417 	.db #0x04	; 4
      009156 36                    5418 	.db #0x36	; 54	'6'
      009157 06                    5419 	.db #0x06	; 6
      009158 02                    5420 	.db #0x02	; 2
      009159 33                    5421 	.db #0x33	; 51	'3'
      00915A 00                    5422 	.db #0x00	; 0
      00915B 00                    5423 	.db #0x00	; 0
      00915C 00                    5424 	.db #0x00	; 0
      00915D 02                    5425 	.db #0x02	; 2
      00915E 38                    5426 	.db #0x38	; 56	'8'
      00915F 38                    5427 	.db #0x38	; 56	'8'
      009160 02                    5428 	.db #0x02	; 2
      009161 00                    5429 	.db #0x00	; 0
      009162 33                    5430 	.db #0x33	; 51	'3'
      009163 33                    5431 	.db #0x33	; 51	'3'
      009164 33                    5432 	.db #0x33	; 51	'3'
      009165 02                    5433 	.db #0x02	; 2
      009166 17                    5434 	.db #0x17	; 23
      009167 06                    5435 	.db #0x06	; 6
      009168 04                    5436 	.db #0x04	; 4
      009169 15                    5437 	.db #0x15	; 21
      00916A 06                    5438 	.db #0x06	; 6
      00916B 00                    5439 	.db #0x00	; 0
      00916C 00                    5440 	.db #0x00	; 0
      00916D 36                    5441 	.db #0x36	; 54	'6'
      00916E 15                    5442 	.db #0x15	; 21
      00916F 07                    5443 	.db #0x07	; 7
      009170 06                    5444 	.db #0x06	; 6
      009171 35                    5445 	.db #0x35	; 53	'5'
      009172 00                    5446 	.db #0x00	; 0
      009173 00                    5447 	.db #0x00	; 0
      009174 3C                    5448 	.db #0x3c	; 60
      009175 19                    5449 	.db #0x19	; 25
      009176 00                    5450 	.db #0x00	; 0
      009177 14                    5451 	.db #0x14	; 20
      009178 34                    5452 	.db #0x34	; 52	'4'
      009179 34                    5453 	.db #0x34	; 52	'4'
      00917A 14                    5454 	.db #0x14	; 20
      00917B 00                    5455 	.db #0x00	; 0
      00917C 00                    5456 	.db #0x00	; 0
      00917D 00                    5457 	.db #0x00	; 0
      00917E 3C                    5458 	.db #0x3c	; 60
      00917F 3B                    5459 	.db #0x3b	; 59
      009180 35                    5460 	.db #0x35	; 53	'5'
      009181 06                    5461 	.db #0x06	; 6
      009182 07                    5462 	.db #0x07	; 7
      009183 15                    5463 	.db #0x15	; 21
      009184 36                    5464 	.db #0x36	; 54	'6'
      009185 00                    5465 	.db #0x00	; 0
      009186 00                    5466 	.db #0x00	; 0
      009187 15                    5467 	.db #0x15	; 21
      009188 02                    5468 	.db #0x02	; 2
      009189 17                    5469 	.db #0x17	; 23
      00918A 06                    5470 	.db #0x06	; 6
      00918B 36                    5471 	.db #0x36	; 54	'6'
      00918C 38                    5472 	.db #0x38	; 56	'8'
      00918D 0C                    5473 	.db #0x0c	; 12
      00918E 38                    5474 	.db #0x38	; 56	'8'
      00918F 15                    5475 	.db #0x15	; 21
      009190 02                    5476 	.db #0x02	; 2
      009191 36                    5477 	.db #0x36	; 54	'6'
      009192 08                    5478 	.db #0x08	; 8
      009193 08                    5479 	.db #0x08	; 8
      009194 36                    5480 	.db #0x36	; 54	'6'
      009195 02                    5481 	.db #0x02	; 2
      009196 15                    5482 	.db #0x15	; 21
      009197 38                    5483 	.db #0x38	; 56	'8'
      009198 0C                    5484 	.db #0x0c	; 12
      009199 38                    5485 	.db #0x38	; 56	'8'
      00919A 36                    5486 	.db #0x36	; 54	'6'
      00919B 06                    5487 	.db #0x06	; 6
      00919C 17                    5488 	.db #0x17	; 23
      00919D 02                    5489 	.db #0x02	; 2
      00919E 15                    5490 	.db #0x15	; 21
      00919F 00                    5491 	.db #0x00	; 0
      0091A0 00                    5492 	.db #0x00	; 0
      0091A1 17                    5493 	.db #0x17	; 23
      0091A2 02                    5494 	.db #0x02	; 2
      0091A3 17                    5495 	.db #0x17	; 23
      0091A4 29                    5496 	.db #0x29	; 41
      0091A5 29                    5497 	.db #0x29	; 41
      0091A6 28                    5498 	.db #0x28	; 40
      0091A7 38                    5499 	.db #0x38	; 56	'8'
      0091A8 36                    5500 	.db #0x36	; 54	'6'
      0091A9 38                    5501 	.db #0x38	; 56	'8'
      0091AA 08                    5502 	.db #0x08	; 8
      0091AB 38                    5503 	.db #0x38	; 56	'8'
      0091AC 2D                    5504 	.db #0x2d	; 45
      0091AD 2D                    5505 	.db #0x2d	; 45
      0091AE 38                    5506 	.db #0x38	; 56	'8'
      0091AF 08                    5507 	.db #0x08	; 8
      0091B0 38                    5508 	.db #0x38	; 56	'8'
      0091B1 36                    5509 	.db #0x36	; 54	'6'
      0091B2 38                    5510 	.db #0x38	; 56	'8'
      0091B3 28                    5511 	.db #0x28	; 40
      0091B4 29                    5512 	.db #0x29	; 41
      0091B5 29                    5513 	.db #0x29	; 41
      0091B6 17                    5514 	.db #0x17	; 23
      0091B7 02                    5515 	.db #0x02	; 2
      0091B8 17                    5516 	.db #0x17	; 23
      0091B9 00                    5517 	.db #0x00	; 0
      0091BA 00                    5518 	.db #0x00	; 0
      0091BB 36                    5519 	.db #0x36	; 54	'6'
      0091BC 02                    5520 	.db #0x02	; 2
      0091BD 36                    5521 	.db #0x36	; 54	'6'
      0091BE 08                    5522 	.db #0x08	; 8
      0091BF 0A                    5523 	.db #0x0a	; 10
      0091C0 0C                    5524 	.db #0x0c	; 12
      0091C1 0A                    5525 	.db #0x0a	; 10
      0091C2 39                    5526 	.db #0x39	; 57	'9'
      0091C3 2B                    5527 	.db #0x2b	; 43
      0091C4 2F                    5528 	.db #0x2f	; 47
      0091C5 2B                    5529 	.db #0x2b	; 43
      0091C6 2F                    5530 	.db #0x2f	; 47
      0091C7 2F                    5531 	.db #0x2f	; 47
      0091C8 2B                    5532 	.db #0x2b	; 43
      0091C9 2F                    5533 	.db #0x2f	; 47
      0091CA 2B                    5534 	.db #0x2b	; 43
      0091CB 39                    5535 	.db #0x39	; 57	'9'
      0091CC 0A                    5536 	.db #0x0a	; 10
      0091CD 0C                    5537 	.db #0x0c	; 12
      0091CE 0A                    5538 	.db #0x0a	; 10
      0091CF 08                    5539 	.db #0x08	; 8
      0091D0 36                    5540 	.db #0x36	; 54	'6'
      0091D1 02                    5541 	.db #0x02	; 2
      0091D2 36                    5542 	.db #0x36	; 54	'6'
      0091D3 00                    5543 	.db #0x00	; 0
      0091D4 00                    5544 	.db #0x00	; 0
      0091D5 00                    5545 	.db #0x00	; 0
      0091D6 02                    5546 	.db #0x02	; 2
      0091D7 17                    5547 	.db #0x17	; 23
      0091D8 26                    5548 	.db #0x26	; 38
      0091D9 38                    5549 	.db #0x38	; 56	'8'
      0091DA 28                    5550 	.db #0x28	; 40
      0091DB 29                    5551 	.db #0x29	; 41
      0091DC 0C                    5552 	.db #0x0c	; 12
      0091DD 0E                    5553 	.db #0x0e	; 14
      0091DE 0A                    5554 	.db #0x0a	; 10
      0091DF 29                    5555 	.db #0x29	; 41
      0091E0 0D                    5556 	.db #0x0d	; 13
      0091E1 20                    5557 	.db #0x20	; 32
      0091E2 29                    5558 	.db #0x29	; 41
      0091E3 0A                    5559 	.db #0x0a	; 10
      0091E4 0E                    5560 	.db #0x0e	; 14
      0091E5 0C                    5561 	.db #0x0c	; 12
      0091E6 29                    5562 	.db #0x29	; 41
      0091E7 28                    5563 	.db #0x28	; 40
      0091E8 38                    5564 	.db #0x38	; 56	'8'
      0091E9 26                    5565 	.db #0x26	; 38
      0091EA 17                    5566 	.db #0x17	; 23
      0091EB 02                    5567 	.db #0x02	; 2
      0091EC 00                    5568 	.db #0x00	; 0
      0091ED 00                    5569 	.db #0x00	; 0
      0091EE 00                    5570 	.db #0x00	; 0
      0091EF 00                    5571 	.db #0x00	; 0
      0091F0 02                    5572 	.db #0x02	; 2
      0091F1 35                    5573 	.db #0x35	; 53	'5'
      0091F2 05                    5574 	.db #0x05	; 5
      0091F3 26                    5575 	.db #0x26	; 38
      0091F4 28                    5576 	.db #0x28	; 40
      0091F5 0C                    5577 	.db #0x0c	; 12
      0091F6 3D                    5578 	.db #0x3d	; 61
      0091F7 29                    5579 	.db #0x29	; 41
      0091F8 38                    5580 	.db #0x38	; 56	'8'
      0091F9 05                    5581 	.db #0x05	; 5
      0091FA 0B                    5582 	.db #0x0b	; 11
      0091FB 0B                    5583 	.db #0x0b	; 11
      0091FC 05                    5584 	.db #0x05	; 5
      0091FD 38                    5585 	.db #0x38	; 56	'8'
      0091FE 29                    5586 	.db #0x29	; 41
      0091FF 3D                    5587 	.db #0x3d	; 61
      009200 0C                    5588 	.db #0x0c	; 12
      009201 28                    5589 	.db #0x28	; 40
      009202 26                    5590 	.db #0x26	; 38
      009203 05                    5591 	.db #0x05	; 5
      009204 35                    5592 	.db #0x35	; 53	'5'
      009205 02                    5593 	.db #0x02	; 2
      009206 00                    5594 	.db #0x00	; 0
      009207 00                    5595 	.db #0x00	; 0
      009208 00                    5596 	.db #0x00	; 0
      009209 00                    5597 	.db #0x00	; 0
      00920A 00                    5598 	.db #0x00	; 0
      00920B 35                    5599 	.db #0x35	; 53	'5'
      00920C 06                    5600 	.db #0x06	; 6
      00920D 05                    5601 	.db #0x05	; 5
      00920E 29                    5602 	.db #0x29	; 41
      00920F 2F                    5603 	.db #0x2f	; 47
      009210 2B                    5604 	.db #0x2b	; 43
      009211 26                    5605 	.db #0x26	; 38
      009212 34                    5606 	.db #0x34	; 52	'4'
      009213 35                    5607 	.db #0x35	; 53	'5'
      009214 17                    5608 	.db #0x17	; 23
      009215 17                    5609 	.db #0x17	; 23
      009216 35                    5610 	.db #0x35	; 53	'5'
      009217 34                    5611 	.db #0x34	; 52	'4'
      009218 26                    5612 	.db #0x26	; 38
      009219 2B                    5613 	.db #0x2b	; 43
      00921A 2F                    5614 	.db #0x2f	; 47
      00921B 29                    5615 	.db #0x29	; 41
      00921C 05                    5616 	.db #0x05	; 5
      00921D 06                    5617 	.db #0x06	; 6
      00921E 35                    5618 	.db #0x35	; 53	'5'
      00921F 00                    5619 	.db #0x00	; 0
      009220 00                    5620 	.db #0x00	; 0
      009221 00                    5621 	.db #0x00	; 0
      009222 00                    5622 	.db #0x00	; 0
      009223 00                    5623 	.db #0x00	; 0
      009224 00                    5624 	.db #0x00	; 0
      009225 02                    5625 	.db #0x02	; 2
      009226 39                    5626 	.db #0x39	; 57	'9'
      009227 05                    5627 	.db #0x05	; 5
      009228 2B                    5628 	.db #0x2b	; 43
      009229 2D                    5629 	.db #0x2d	; 45
      00922A 28                    5630 	.db #0x28	; 40
      00922B 08                    5631 	.db #0x08	; 8
      00922C 0A                    5632 	.db #0x0a	; 10
      00922D 28                    5633 	.db #0x28	; 40
      00922E 26                    5634 	.db #0x26	; 38
      00922F 26                    5635 	.db #0x26	; 38
      009230 28                    5636 	.db #0x28	; 40
      009231 0A                    5637 	.db #0x0a	; 10
      009232 08                    5638 	.db #0x08	; 8
      009233 28                    5639 	.db #0x28	; 40
      009234 2D                    5640 	.db #0x2d	; 45
      009235 2B                    5641 	.db #0x2b	; 43
      009236 05                    5642 	.db #0x05	; 5
      009237 39                    5643 	.db #0x39	; 57	'9'
      009238 02                    5644 	.db #0x02	; 2
      009239 00                    5645 	.db #0x00	; 0
      00923A 00                    5646 	.db #0x00	; 0
      00923B 00                    5647 	.db #0x00	; 0
      00923C 00                    5648 	.db #0x00	; 0
      00923D 00                    5649 	.db #0x00	; 0
      00923E 00                    5650 	.db #0x00	; 0
      00923F 34                    5651 	.db #0x34	; 52	'4'
      009240 38                    5652 	.db #0x38	; 56	'8'
      009241 26                    5653 	.db #0x26	; 38
      009242 29                    5654 	.db #0x29	; 41
      009243 2B                    5655 	.db #0x2b	; 43
      009244 08                    5656 	.db #0x08	; 8
      009245 29                    5657 	.db #0x29	; 41
      009246 2D                    5658 	.db #0x2d	; 45
      009247 3D                    5659 	.db #0x3d	; 61
      009248 29                    5660 	.db #0x29	; 41
      009249 29                    5661 	.db #0x29	; 41
      00924A 3D                    5662 	.db #0x3d	; 61
      00924B 2D                    5663 	.db #0x2d	; 45
      00924C 29                    5664 	.db #0x29	; 41
      00924D 08                    5665 	.db #0x08	; 8
      00924E 2B                    5666 	.db #0x2b	; 43
      00924F 29                    5667 	.db #0x29	; 41
      009250 26                    5668 	.db #0x26	; 38
      009251 38                    5669 	.db #0x38	; 56	'8'
      009252 34                    5670 	.db #0x34	; 52	'4'
      009253 00                    5671 	.db #0x00	; 0
      009254 00                    5672 	.db #0x00	; 0
      009255 00                    5673 	.db #0x00	; 0
      009256 00                    5674 	.db #0x00	; 0
      009257 00                    5675 	.db #0x00	; 0
      009258 00                    5676 	.db #0x00	; 0
      009259 00                    5677 	.db #0x00	; 0
      00925A 17                    5678 	.db #0x17	; 23
      00925B 38                    5679 	.db #0x38	; 56	'8'
      00925C 39                    5680 	.db #0x39	; 57	'9'
      00925D 29                    5681 	.db #0x29	; 41
      00925E 36                    5682 	.db #0x36	; 54	'6'
      00925F 35                    5683 	.db #0x35	; 53	'5'
      009260 23                    5684 	.db #0x23	; 35
      009261 23                    5685 	.db #0x23	; 35
      009262 23                    5686 	.db #0x23	; 35
      009263 23                    5687 	.db #0x23	; 35
      009264 23                    5688 	.db #0x23	; 35
      009265 23                    5689 	.db #0x23	; 35
      009266 35                    5690 	.db #0x35	; 53	'5'
      009267 36                    5691 	.db #0x36	; 54	'6'
      009268 29                    5692 	.db #0x29	; 41
      009269 39                    5693 	.db #0x39	; 57	'9'
      00926A 38                    5694 	.db #0x38	; 56	'8'
      00926B 17                    5695 	.db #0x17	; 23
      00926C 00                    5696 	.db #0x00	; 0
      00926D 00                    5697 	.db #0x00	; 0
      00926E 00                    5698 	.db #0x00	; 0
      00926F 00                    5699 	.db #0x00	; 0
      009270 00                    5700 	.db #0x00	; 0
      009271 00                    5701 	.db #0x00	; 0
      009272 00                    5702 	.db #0x00	; 0
      009273 00                    5703 	.db #0x00	; 0
      009274 34                    5704 	.db #0x34	; 52	'4'
      009275 36                    5705 	.db #0x36	; 54	'6'
      009276 06                    5706 	.db #0x06	; 6
      009277 39                    5707 	.db #0x39	; 57	'9'
      009278 39                    5708 	.db #0x39	; 57	'9'
      009279 39                    5709 	.db #0x39	; 57	'9'
      00927A 29                    5710 	.db #0x29	; 41
      00927B 2B                    5711 	.db #0x2b	; 43
      00927C 09                    5712 	.db #0x09	; 9
      00927D 09                    5713 	.db #0x09	; 9
      00927E 2B                    5714 	.db #0x2b	; 43
      00927F 29                    5715 	.db #0x29	; 41
      009280 39                    5716 	.db #0x39	; 57	'9'
      009281 39                    5717 	.db #0x39	; 57	'9'
      009282 39                    5718 	.db #0x39	; 57	'9'
      009283 06                    5719 	.db #0x06	; 6
      009284 36                    5720 	.db #0x36	; 54	'6'
      009285 34                    5721 	.db #0x34	; 52	'4'
      009286 00                    5722 	.db #0x00	; 0
      009287 00                    5723 	.db #0x00	; 0
      009288 00                    5724 	.db #0x00	; 0
      009289 00                    5725 	.db #0x00	; 0
      00928A 00                    5726 	.db #0x00	; 0
      00928B 00                    5727 	.db #0x00	; 0
      00928C 00                    5728 	.db #0x00	; 0
      00928D 00                    5729 	.db #0x00	; 0
      00928E 00                    5730 	.db #0x00	; 0
      00928F 15                    5731 	.db #0x15	; 21
      009290 05                    5732 	.db #0x05	; 5
      009291 08                    5733 	.db #0x08	; 8
      009292 0A                    5734 	.db #0x0a	; 10
      009293 39                    5735 	.db #0x39	; 57	'9'
      009294 38                    5736 	.db #0x38	; 56	'8'
      009295 36                    5737 	.db #0x36	; 54	'6'
      009296 03                    5738 	.db #0x03	; 3
      009297 03                    5739 	.db #0x03	; 3
      009298 36                    5740 	.db #0x36	; 54	'6'
      009299 38                    5741 	.db #0x38	; 56	'8'
      00929A 39                    5742 	.db #0x39	; 57	'9'
      00929B 0A                    5743 	.db #0x0a	; 10
      00929C 08                    5744 	.db #0x08	; 8
      00929D 05                    5745 	.db #0x05	; 5
      00929E 15                    5746 	.db #0x15	; 21
      00929F 00                    5747 	.db #0x00	; 0
      0092A0 00                    5748 	.db #0x00	; 0
      0092A1 00                    5749 	.db #0x00	; 0
      0092A2 00                    5750 	.db #0x00	; 0
      0092A3 00                    5751 	.db #0x00	; 0
      0092A4 00                    5752 	.db #0x00	; 0
      0092A5 00                    5753 	.db #0x00	; 0
      0092A6 00                    5754 	.db #0x00	; 0
      0092A7 00                    5755 	.db #0x00	; 0
      0092A8 00                    5756 	.db #0x00	; 0
      0092A9 00                    5757 	.db #0x00	; 0
      0092AA 15                    5758 	.db #0x15	; 21
      0092AB 26                    5759 	.db #0x26	; 38
      0092AC 08                    5760 	.db #0x08	; 8
      0092AD 0A                    5761 	.db #0x0a	; 10
      0092AE 39                    5762 	.db #0x39	; 57	'9'
      0092AF 39                    5763 	.db #0x39	; 57	'9'
      0092B0 2B                    5764 	.db #0x2b	; 43
      0092B1 2B                    5765 	.db #0x2b	; 43
      0092B2 39                    5766 	.db #0x39	; 57	'9'
      0092B3 39                    5767 	.db #0x39	; 57	'9'
      0092B4 0A                    5768 	.db #0x0a	; 10
      0092B5 08                    5769 	.db #0x08	; 8
      0092B6 26                    5770 	.db #0x26	; 38
      0092B7 15                    5771 	.db #0x15	; 21
      0092B8 00                    5772 	.db #0x00	; 0
      0092B9 00                    5773 	.db #0x00	; 0
      0092BA 00                    5774 	.db #0x00	; 0
      0092BB 00                    5775 	.db #0x00	; 0
      0092BC 00                    5776 	.db #0x00	; 0
      0092BD 00                    5777 	.db #0x00	; 0
      0092BE 00                    5778 	.db #0x00	; 0
      0092BF 00                    5779 	.db #0x00	; 0
      0092C0 00                    5780 	.db #0x00	; 0
      0092C1 00                    5781 	.db #0x00	; 0
      0092C2 00                    5782 	.db #0x00	; 0
      0092C3 00                    5783 	.db #0x00	; 0
      0092C4 00                    5784 	.db #0x00	; 0
      0092C5 34                    5785 	.db #0x34	; 52	'4'
      0092C6 17                    5786 	.db #0x17	; 23
      0092C7 06                    5787 	.db #0x06	; 6
      0092C8 29                    5788 	.db #0x29	; 41
      0092C9 2B                    5789 	.db #0x2b	; 43
      0092CA 3D                    5790 	.db #0x3d	; 61
      0092CB 3D                    5791 	.db #0x3d	; 61
      0092CC 2B                    5792 	.db #0x2b	; 43
      0092CD 29                    5793 	.db #0x29	; 41
      0092CE 06                    5794 	.db #0x06	; 6
      0092CF 17                    5795 	.db #0x17	; 23
      0092D0 34                    5796 	.db #0x34	; 52	'4'
      0092D1 00                    5797 	.db #0x00	; 0
      0092D2 00                    5798 	.db #0x00	; 0
      0092D3 00                    5799 	.db #0x00	; 0
      0092D4 00                    5800 	.db #0x00	; 0
      0092D5 00                    5801 	.db #0x00	; 0
      0092D6 00                    5802 	.db #0x00	; 0
      0092D7 00                    5803 	.db #0x00	; 0
      0092D8 00                    5804 	.db #0x00	; 0
      0092D9 00                    5805 	.db #0x00	; 0
      0092DA 00                    5806 	.db #0x00	; 0
      0092DB 00                    5807 	.db #0x00	; 0
      0092DC 00                    5808 	.db #0x00	; 0
      0092DD 00                    5809 	.db #0x00	; 0
      0092DE 00                    5810 	.db #0x00	; 0
      0092DF 00                    5811 	.db #0x00	; 0
      0092E0 00                    5812 	.db #0x00	; 0
      0092E1 15                    5813 	.db #0x15	; 21
      0092E2 36                    5814 	.db #0x36	; 54	'6'
      0092E3 26                    5815 	.db #0x26	; 38
      0092E4 26                    5816 	.db #0x26	; 38
      0092E5 26                    5817 	.db #0x26	; 38
      0092E6 26                    5818 	.db #0x26	; 38
      0092E7 36                    5819 	.db #0x36	; 54	'6'
      0092E8 15                    5820 	.db #0x15	; 21
      0092E9 00                    5821 	.db #0x00	; 0
      0092EA 00                    5822 	.db #0x00	; 0
      0092EB 00                    5823 	.db #0x00	; 0
      0092EC 00                    5824 	.db #0x00	; 0
      0092ED 00                    5825 	.db #0x00	; 0
      0092EE 00                    5826 	.db #0x00	; 0
      0092EF 00                    5827 	.db #0x00	; 0
      0092F0 00                    5828 	.db #0x00	; 0
      0092F1 00                    5829 	.db #0x00	; 0
      0092F2 00                    5830 	.db #0x00	; 0
      0092F3 00                    5831 	.db #0x00	; 0
      0092F4 00                    5832 	.db #0x00	; 0
      0092F5 00                    5833 	.db #0x00	; 0
      0092F6 00                    5834 	.db #0x00	; 0
      0092F7 00                    5835 	.db #0x00	; 0
      0092F8 00                    5836 	.db #0x00	; 0
      0092F9 00                    5837 	.db #0x00	; 0
      0092FA 00                    5838 	.db #0x00	; 0
      0092FB 00                    5839 	.db #0x00	; 0
      0092FC 00                    5840 	.db #0x00	; 0
      0092FD 00                    5841 	.db #0x00	; 0
      0092FE 00                    5842 	.db #0x00	; 0
      0092FF 00                    5843 	.db #0x00	; 0
      009300 00                    5844 	.db #0x00	; 0
      009301 00                    5845 	.db #0x00	; 0
      009302 00                    5846 	.db #0x00	; 0
      009303 00                    5847 	.db #0x00	; 0
      009304 00                    5848 	.db #0x00	; 0
      009305 00                    5849 	.db #0x00	; 0
      009306 00                    5850 	.db #0x00	; 0
      009307 00                    5851 	.db #0x00	; 0
      009308 00                    5852 	.db #0x00	; 0
      009309 00                    5853 	.db #0x00	; 0
      00930A 00                    5854 	.db #0x00	; 0
      00930B                       5855 _doom7_raw:
      00930B 00                    5856 	.db #0x00	; 0
      00930C 00                    5857 	.db #0x00	; 0
      00930D 00                    5858 	.db #0x00	; 0
      00930E 00                    5859 	.db #0x00	; 0
      00930F 00                    5860 	.db #0x00	; 0
      009310 00                    5861 	.db #0x00	; 0
      009311 00                    5862 	.db #0x00	; 0
      009312 00                    5863 	.db #0x00	; 0
      009313 33                    5864 	.db #0x33	; 51	'3'
      009314 02                    5865 	.db #0x02	; 2
      009315 15                    5866 	.db #0x15	; 21
      009316 35                    5867 	.db #0x35	; 53	'5'
      009317 35                    5868 	.db #0x35	; 53	'5'
      009318 35                    5869 	.db #0x35	; 53	'5'
      009319 35                    5870 	.db #0x35	; 53	'5'
      00931A 35                    5871 	.db #0x35	; 53	'5'
      00931B 15                    5872 	.db #0x15	; 21
      00931C 33                    5873 	.db #0x33	; 51	'3'
      00931D 01                    5874 	.db #0x01	; 1
      00931E 00                    5875 	.db #0x00	; 0
      00931F 00                    5876 	.db #0x00	; 0
      009320 00                    5877 	.db #0x00	; 0
      009321 00                    5878 	.db #0x00	; 0
      009322 00                    5879 	.db #0x00	; 0
      009323 00                    5880 	.db #0x00	; 0
      009324 00                    5881 	.db #0x00	; 0
      009325 00                    5882 	.db #0x00	; 0
      009326 00                    5883 	.db #0x00	; 0
      009327 00                    5884 	.db #0x00	; 0
      009328 00                    5885 	.db #0x00	; 0
      009329 00                    5886 	.db #0x00	; 0
      00932A 14                    5887 	.db #0x14	; 20
      00932B 02                    5888 	.db #0x02	; 2
      00932C 15                    5889 	.db #0x15	; 21
      00932D 05                    5890 	.db #0x05	; 5
      00932E 05                    5891 	.db #0x05	; 5
      00932F 28                    5892 	.db #0x28	; 40
      009330 28                    5893 	.db #0x28	; 40
      009331 38                    5894 	.db #0x38	; 56	'8'
      009332 26                    5895 	.db #0x26	; 38
      009333 36                    5896 	.db #0x36	; 54	'6'
      009334 36                    5897 	.db #0x36	; 54	'6'
      009335 03                    5898 	.db #0x03	; 3
      009336 15                    5899 	.db #0x15	; 21
      009337 34                    5900 	.db #0x34	; 52	'4'
      009338 14                    5901 	.db #0x14	; 20
      009339 01                    5902 	.db #0x01	; 1
      00933A 00                    5903 	.db #0x00	; 0
      00933B 00                    5904 	.db #0x00	; 0
      00933C 00                    5905 	.db #0x00	; 0
      00933D 00                    5906 	.db #0x00	; 0
      00933E 00                    5907 	.db #0x00	; 0
      00933F 00                    5908 	.db #0x00	; 0
      009340 00                    5909 	.db #0x00	; 0
      009341 00                    5910 	.db #0x00	; 0
      009342 14                    5911 	.db #0x14	; 20
      009343 15                    5912 	.db #0x15	; 21
      009344 36                    5913 	.db #0x36	; 54	'6'
      009345 28                    5914 	.db #0x28	; 40
      009346 0A                    5915 	.db #0x0a	; 10
      009347 0C                    5916 	.db #0x0c	; 12
      009348 0E                    5917 	.db #0x0e	; 14
      009349 0E                    5918 	.db #0x0e	; 14
      00934A 0C                    5919 	.db #0x0c	; 12
      00934B 29                    5920 	.db #0x29	; 41
      00934C 08                    5921 	.db #0x08	; 8
      00934D 06                    5922 	.db #0x06	; 6
      00934E 26                    5923 	.db #0x26	; 38
      00934F 17                    5924 	.db #0x17	; 23
      009350 35                    5925 	.db #0x35	; 53	'5'
      009351 02                    5926 	.db #0x02	; 2
      009352 34                    5927 	.db #0x34	; 52	'4'
      009353 14                    5928 	.db #0x14	; 20
      009354 01                    5929 	.db #0x01	; 1
      009355 00                    5930 	.db #0x00	; 0
      009356 00                    5931 	.db #0x00	; 0
      009357 00                    5932 	.db #0x00	; 0
      009358 00                    5933 	.db #0x00	; 0
      009359 00                    5934 	.db #0x00	; 0
      00935A 00                    5935 	.db #0x00	; 0
      00935B 15                    5936 	.db #0x15	; 21
      00935C 06                    5937 	.db #0x06	; 6
      00935D 29                    5938 	.db #0x29	; 41
      00935E 08                    5939 	.db #0x08	; 8
      00935F 39                    5940 	.db #0x39	; 57	'9'
      009360 28                    5941 	.db #0x28	; 40
      009361 28                    5942 	.db #0x28	; 40
      009362 2B                    5943 	.db #0x2b	; 43
      009363 08                    5944 	.db #0x08	; 8
      009364 06                    5945 	.db #0x06	; 6
      009365 38                    5946 	.db #0x38	; 56	'8'
      009366 06                    5947 	.db #0x06	; 6
      009367 28                    5948 	.db #0x28	; 40
      009368 17                    5949 	.db #0x17	; 23
      009369 17                    5950 	.db #0x17	; 23
      00936A 17                    5951 	.db #0x17	; 23
      00936B 35                    5952 	.db #0x35	; 53	'5'
      00936C 34                    5953 	.db #0x34	; 52	'4'
      00936D 14                    5954 	.db #0x14	; 20
      00936E 33                    5955 	.db #0x33	; 51	'3'
      00936F 01                    5956 	.db #0x01	; 1
      009370 00                    5957 	.db #0x00	; 0
      009371 00                    5958 	.db #0x00	; 0
      009372 00                    5959 	.db #0x00	; 0
      009373 00                    5960 	.db #0x00	; 0
      009374 01                    5961 	.db #0x01	; 1
      009375 06                    5962 	.db #0x06	; 6
      009376 05                    5963 	.db #0x05	; 5
      009377 2B                    5964 	.db #0x2b	; 43
      009378 06                    5965 	.db #0x06	; 6
      009379 26                    5966 	.db #0x26	; 38
      00937A 35                    5967 	.db #0x35	; 53	'5'
      00937B 35                    5968 	.db #0x35	; 53	'5'
      00937C 05                    5969 	.db #0x05	; 5
      00937D 2B                    5970 	.db #0x2b	; 43
      00937E 15                    5971 	.db #0x15	; 21
      00937F 05                    5972 	.db #0x05	; 5
      009380 17                    5973 	.db #0x17	; 23
      009381 03                    5974 	.db #0x03	; 3
      009382 05                    5975 	.db #0x05	; 5
      009383 35                    5976 	.db #0x35	; 53	'5'
      009384 15                    5977 	.db #0x15	; 21
      009385 35                    5978 	.db #0x35	; 53	'5'
      009386 34                    5979 	.db #0x34	; 52	'4'
      009387 14                    5980 	.db #0x14	; 20
      009388 14                    5981 	.db #0x14	; 20
      009389 33                    5982 	.db #0x33	; 51	'3'
      00938A 01                    5983 	.db #0x01	; 1
      00938B 00                    5984 	.db #0x00	; 0
      00938C 00                    5985 	.db #0x00	; 0
      00938D 00                    5986 	.db #0x00	; 0
      00938E 22                    5987 	.db #0x22	; 34
      00938F 36                    5988 	.db #0x36	; 54	'6'
      009390 01                    5989 	.db #0x01	; 1
      009391 01                    5990 	.db #0x01	; 1
      009392 29                    5991 	.db #0x29	; 41
      009393 02                    5992 	.db #0x02	; 2
      009394 14                    5993 	.db #0x14	; 20
      009395 01                    5994 	.db #0x01	; 1
      009396 34                    5995 	.db #0x34	; 52	'4'
      009397 05                    5996 	.db #0x05	; 5
      009398 38                    5997 	.db #0x38	; 56	'8'
      009399 01                    5998 	.db #0x01	; 1
      00939A 14                    5999 	.db #0x14	; 20
      00939B 35                    6000 	.db #0x35	; 53	'5'
      00939C 15                    6001 	.db #0x15	; 21
      00939D 03                    6002 	.db #0x03	; 3
      00939E 02                    6003 	.db #0x02	; 2
      00939F 02                    6004 	.db #0x02	; 2
      0093A0 02                    6005 	.db #0x02	; 2
      0093A1 14                    6006 	.db #0x14	; 20
      0093A2 33                    6007 	.db #0x33	; 51	'3'
      0093A3 14                    6008 	.db #0x14	; 20
      0093A4 33                    6009 	.db #0x33	; 51	'3'
      0093A5 01                    6010 	.db #0x01	; 1
      0093A6 00                    6011 	.db #0x00	; 0
      0093A7 00                    6012 	.db #0x00	; 0
      0093A8 22                    6013 	.db #0x22	; 34
      0093A9 15                    6014 	.db #0x15	; 21
      0093AA 01                    6015 	.db #0x01	; 1
      0093AB 15                    6016 	.db #0x15	; 21
      0093AC 14                    6017 	.db #0x14	; 20
      0093AD 36                    6018 	.db #0x36	; 54	'6'
      0093AE 14                    6019 	.db #0x14	; 20
      0093AF 01                    6020 	.db #0x01	; 1
      0093B0 01                    6021 	.db #0x01	; 1
      0093B1 15                    6022 	.db #0x15	; 21
      0093B2 05                    6023 	.db #0x05	; 5
      0093B3 14                    6024 	.db #0x14	; 20
      0093B4 01                    6025 	.db #0x01	; 1
      0093B5 33                    6026 	.db #0x33	; 51	'3'
      0093B6 34                    6027 	.db #0x34	; 52	'4'
      0093B7 15                    6028 	.db #0x15	; 21
      0093B8 34                    6029 	.db #0x34	; 52	'4'
      0093B9 34                    6030 	.db #0x34	; 52	'4'
      0093BA 34                    6031 	.db #0x34	; 52	'4'
      0093BB 14                    6032 	.db #0x14	; 20
      0093BC 22                    6033 	.db #0x22	; 34
      0093BD 33                    6034 	.db #0x33	; 51	'3'
      0093BE 14                    6035 	.db #0x14	; 20
      0093BF 33                    6036 	.db #0x33	; 51	'3'
      0093C0 00                    6037 	.db #0x00	; 0
      0093C1 00                    6038 	.db #0x00	; 0
      0093C2 00                    6039 	.db #0x00	; 0
      0093C3 15                    6040 	.db #0x15	; 21
      0093C4 15                    6041 	.db #0x15	; 21
      0093C5 35                    6042 	.db #0x35	; 53	'5'
      0093C6 35                    6043 	.db #0x35	; 53	'5'
      0093C7 02                    6044 	.db #0x02	; 2
      0093C8 36                    6045 	.db #0x36	; 54	'6'
      0093C9 02                    6046 	.db #0x02	; 2
      0093CA 34                    6047 	.db #0x34	; 52	'4'
      0093CB 34                    6048 	.db #0x34	; 52	'4'
      0093CC 15                    6049 	.db #0x15	; 21
      0093CD 02                    6050 	.db #0x02	; 2
      0093CE 14                    6051 	.db #0x14	; 20
      0093CF 01                    6052 	.db #0x01	; 1
      0093D0 33                    6053 	.db #0x33	; 51	'3'
      0093D1 34                    6054 	.db #0x34	; 52	'4'
      0093D2 15                    6055 	.db #0x15	; 21
      0093D3 14                    6056 	.db #0x14	; 20
      0093D4 14                    6057 	.db #0x14	; 20
      0093D5 34                    6058 	.db #0x34	; 52	'4'
      0093D6 33                    6059 	.db #0x33	; 51	'3'
      0093D7 22                    6060 	.db #0x22	; 34
      0093D8 33                    6061 	.db #0x33	; 51	'3'
      0093D9 14                    6062 	.db #0x14	; 20
      0093DA 01                    6063 	.db #0x01	; 1
      0093DB 00                    6064 	.db #0x00	; 0
      0093DC 00                    6065 	.db #0x00	; 0
      0093DD 15                    6066 	.db #0x15	; 21
      0093DE 36                    6067 	.db #0x36	; 54	'6'
      0093DF 36                    6068 	.db #0x36	; 54	'6'
      0093E0 36                    6069 	.db #0x36	; 54	'6'
      0093E1 36                    6070 	.db #0x36	; 54	'6'
      0093E2 35                    6071 	.db #0x35	; 53	'5'
      0093E3 36                    6072 	.db #0x36	; 54	'6'
      0093E4 36                    6073 	.db #0x36	; 54	'6'
      0093E5 36                    6074 	.db #0x36	; 54	'6'
      0093E6 36                    6075 	.db #0x36	; 54	'6'
      0093E7 15                    6076 	.db #0x15	; 21
      0093E8 05                    6077 	.db #0x05	; 5
      0093E9 35                    6078 	.db #0x35	; 53	'5'
      0093EA 33                    6079 	.db #0x33	; 51	'3'
      0093EB 01                    6080 	.db #0x01	; 1
      0093EC 34                    6081 	.db #0x34	; 52	'4'
      0093ED 34                    6082 	.db #0x34	; 52	'4'
      0093EE 14                    6083 	.db #0x14	; 20
      0093EF 14                    6084 	.db #0x14	; 20
      0093F0 33                    6085 	.db #0x33	; 51	'3'
      0093F1 22                    6086 	.db #0x22	; 34
      0093F2 22                    6087 	.db #0x22	; 34
      0093F3 14                    6088 	.db #0x14	; 20
      0093F4 22                    6089 	.db #0x22	; 34
      0093F5 00                    6090 	.db #0x00	; 0
      0093F6 00                    6091 	.db #0x00	; 0
      0093F7 38                    6092 	.db #0x38	; 56	'8'
      0093F8 06                    6093 	.db #0x06	; 6
      0093F9 06                    6094 	.db #0x06	; 6
      0093FA 06                    6095 	.db #0x06	; 6
      0093FB 06                    6096 	.db #0x06	; 6
      0093FC 36                    6097 	.db #0x36	; 54	'6'
      0093FD 05                    6098 	.db #0x05	; 5
      0093FE 38                    6099 	.db #0x38	; 56	'8'
      0093FF 39                    6100 	.db #0x39	; 57	'9'
      009400 08                    6101 	.db #0x08	; 8
      009401 05                    6102 	.db #0x05	; 5
      009402 08                    6103 	.db #0x08	; 8
      009403 05                    6104 	.db #0x05	; 5
      009404 03                    6105 	.db #0x03	; 3
      009405 14                    6106 	.db #0x14	; 20
      009406 33                    6107 	.db #0x33	; 51	'3'
      009407 34                    6108 	.db #0x34	; 52	'4'
      009408 14                    6109 	.db #0x14	; 20
      009409 14                    6110 	.db #0x14	; 20
      00940A 33                    6111 	.db #0x33	; 51	'3'
      00940B 22                    6112 	.db #0x22	; 34
      00940C 22                    6113 	.db #0x22	; 34
      00940D 33                    6114 	.db #0x33	; 51	'3'
      00940E 33                    6115 	.db #0x33	; 51	'3'
      00940F 00                    6116 	.db #0x00	; 0
      009410 38                    6117 	.db #0x38	; 56	'8'
      009411 0C                    6118 	.db #0x0c	; 12
      009412 29                    6119 	.db #0x29	; 41
      009413 08                    6120 	.db #0x08	; 8
      009414 38                    6121 	.db #0x38	; 56	'8'
      009415 38                    6122 	.db #0x38	; 56	'8'
      009416 38                    6123 	.db #0x38	; 56	'8'
      009417 38                    6124 	.db #0x38	; 56	'8'
      009418 39                    6125 	.db #0x39	; 57	'9'
      009419 0A                    6126 	.db #0x0a	; 10
      00941A 0A                    6127 	.db #0x0a	; 10
      00941B 0A                    6128 	.db #0x0a	; 10
      00941C 08                    6129 	.db #0x08	; 8
      00941D 06                    6130 	.db #0x06	; 6
      00941E 05                    6131 	.db #0x05	; 5
      00941F 02                    6132 	.db #0x02	; 2
      009420 14                    6133 	.db #0x14	; 20
      009421 34                    6134 	.db #0x34	; 52	'4'
      009422 34                    6135 	.db #0x34	; 52	'4'
      009423 14                    6136 	.db #0x14	; 20
      009424 14                    6137 	.db #0x14	; 20
      009425 33                    6138 	.db #0x33	; 51	'3'
      009426 22                    6139 	.db #0x22	; 34
      009427 22                    6140 	.db #0x22	; 34
      009428 33                    6141 	.db #0x33	; 51	'3'
      009429 00                    6142 	.db #0x00	; 0
      00942A 29                    6143 	.db #0x29	; 41
      00942B 2F                    6144 	.db #0x2f	; 47
      00942C 0A                    6145 	.db #0x0a	; 10
      00942D 0A                    6146 	.db #0x0a	; 10
      00942E 06                    6147 	.db #0x06	; 6
      00942F 06                    6148 	.db #0x06	; 6
      009430 06                    6149 	.db #0x06	; 6
      009431 08                    6150 	.db #0x08	; 8
      009432 0A                    6151 	.db #0x0a	; 10
      009433 2F                    6152 	.db #0x2f	; 47
      009434 1E                    6153 	.db #0x1e	; 30
      009435 2F                    6154 	.db #0x2f	; 47
      009436 0A                    6155 	.db #0x0a	; 10
      009437 28                    6156 	.db #0x28	; 40
      009438 05                    6157 	.db #0x05	; 5
      009439 35                    6158 	.db #0x35	; 53	'5'
      00943A 02                    6159 	.db #0x02	; 2
      00943B 34                    6160 	.db #0x34	; 52	'4'
      00943C 34                    6161 	.db #0x34	; 52	'4'
      00943D 14                    6162 	.db #0x14	; 20
      00943E 14                    6163 	.db #0x14	; 20
      00943F 33                    6164 	.db #0x33	; 51	'3'
      009440 22                    6165 	.db #0x22	; 34
      009441 22                    6166 	.db #0x22	; 34
      009442 33                    6167 	.db #0x33	; 51	'3'
      009443 36                    6168 	.db #0x36	; 54	'6'
      009444 2B                    6169 	.db #0x2b	; 43
      009445 2F                    6170 	.db #0x2f	; 47
      009446 0C                    6171 	.db #0x0c	; 12
      009447 0A                    6172 	.db #0x0a	; 10
      009448 06                    6173 	.db #0x06	; 6
      009449 08                    6174 	.db #0x08	; 8
      00944A 0A                    6175 	.db #0x0a	; 10
      00944B 2D                    6176 	.db #0x2d	; 45
      00944C 2F                    6177 	.db #0x2f	; 47
      00944D 2D                    6178 	.db #0x2d	; 45
      00944E 2F                    6179 	.db #0x2f	; 47
      00944F 1E                    6180 	.db #0x1e	; 30
      009450 2D                    6181 	.db #0x2d	; 45
      009451 2D                    6182 	.db #0x2d	; 45
      009452 06                    6183 	.db #0x06	; 6
      009453 35                    6184 	.db #0x35	; 53	'5'
      009454 02                    6185 	.db #0x02	; 2
      009455 02                    6186 	.db #0x02	; 2
      009456 34                    6187 	.db #0x34	; 52	'4'
      009457 14                    6188 	.db #0x14	; 20
      009458 14                    6189 	.db #0x14	; 20
      009459 33                    6190 	.db #0x33	; 51	'3'
      00945A 22                    6191 	.db #0x22	; 34
      00945B 22                    6192 	.db #0x22	; 34
      00945C 22                    6193 	.db #0x22	; 34
      00945D 33                    6194 	.db #0x33	; 51	'3'
      00945E 33                    6195 	.db #0x33	; 51	'3'
      00945F 33                    6196 	.db #0x33	; 51	'3'
      009460 06                    6197 	.db #0x06	; 6
      009461 0C                    6198 	.db #0x0c	; 12
      009462 38                    6199 	.db #0x38	; 56	'8'
      009463 2F                    6200 	.db #0x2f	; 47
      009464 29                    6201 	.db #0x29	; 41
      009465 38                    6202 	.db #0x38	; 56	'8'
      009466 08                    6203 	.db #0x08	; 8
      009467 06                    6204 	.db #0x06	; 6
      009468 36                    6205 	.db #0x36	; 54	'6'
      009469 33                    6206 	.db #0x33	; 51	'3'
      00946A 34                    6207 	.db #0x34	; 52	'4'
      00946B 17                    6208 	.db #0x17	; 23
      00946C 29                    6209 	.db #0x29	; 41
      00946D 36                    6210 	.db #0x36	; 54	'6'
      00946E 35                    6211 	.db #0x35	; 53	'5'
      00946F 35                    6212 	.db #0x35	; 53	'5'
      009470 17                    6213 	.db #0x17	; 23
      009471 06                    6214 	.db #0x06	; 6
      009472 26                    6215 	.db #0x26	; 38
      009473 15                    6216 	.db #0x15	; 21
      009474 22                    6217 	.db #0x22	; 34
      009475 22                    6218 	.db #0x22	; 34
      009476 22                    6219 	.db #0x22	; 34
      009477 00                    6220 	.db #0x00	; 0
      009478 15                    6221 	.db #0x15	; 21
      009479 00                    6222 	.db #0x00	; 0
      00947A 1F                    6223 	.db #0x1f	; 31
      00947B 34                    6224 	.db #0x34	; 52	'4'
      00947C 35                    6225 	.db #0x35	; 53	'5'
      00947D 06                    6226 	.db #0x06	; 6
      00947E 06                    6227 	.db #0x06	; 6
      00947F 35                    6228 	.db #0x35	; 53	'5'
      009480 02                    6229 	.db #0x02	; 2
      009481 33                    6230 	.db #0x33	; 51	'3'
      009482 33                    6231 	.db #0x33	; 51	'3'
      009483 36                    6232 	.db #0x36	; 54	'6'
      009484 39                    6233 	.db #0x39	; 57	'9'
      009485 38                    6234 	.db #0x38	; 56	'8'
      009486 05                    6235 	.db #0x05	; 5
      009487 05                    6236 	.db #0x05	; 5
      009488 36                    6237 	.db #0x36	; 54	'6'
      009489 36                    6238 	.db #0x36	; 54	'6'
      00948A 06                    6239 	.db #0x06	; 6
      00948B 03                    6240 	.db #0x03	; 3
      00948C 02                    6241 	.db #0x02	; 2
      00948D 34                    6242 	.db #0x34	; 52	'4'
      00948E 17                    6243 	.db #0x17	; 23
      00948F 01                    6244 	.db #0x01	; 1
      009490 22                    6245 	.db #0x22	; 34
      009491 00                    6246 	.db #0x00	; 0
      009492 39                    6247 	.db #0x39	; 57	'9'
      009493 05                    6248 	.db #0x05	; 5
      009494 35                    6249 	.db #0x35	; 53	'5'
      009495 01                    6250 	.db #0x01	; 1
      009496 33                    6251 	.db #0x33	; 51	'3'
      009497 34                    6252 	.db #0x34	; 52	'4'
      009498 14                    6253 	.db #0x14	; 20
      009499 34                    6254 	.db #0x34	; 52	'4'
      00949A 15                    6255 	.db #0x15	; 21
      00949B 00                    6256 	.db #0x00	; 0
      00949C 2C                    6257 	.db #0x2c	; 44
      00949D 3F                    6258 	.db #0x3f	; 63
      00949E 15                    6259 	.db #0x15	; 21
      00949F 38                    6260 	.db #0x38	; 56	'8'
      0094A0 26                    6261 	.db #0x26	; 38
      0094A1 05                    6262 	.db #0x05	; 5
      0094A2 36                    6263 	.db #0x36	; 54	'6'
      0094A3 05                    6264 	.db #0x05	; 5
      0094A4 03                    6265 	.db #0x03	; 3
      0094A5 03                    6266 	.db #0x03	; 3
      0094A6 02                    6267 	.db #0x02	; 2
      0094A7 06                    6268 	.db #0x06	; 6
      0094A8 17                    6269 	.db #0x17	; 23
      0094A9 01                    6270 	.db #0x01	; 1
      0094AA 01                    6271 	.db #0x01	; 1
      0094AB 03                    6272 	.db #0x03	; 3
      0094AC 0A                    6273 	.db #0x0a	; 10
      0094AD 2D                    6274 	.db #0x2d	; 45
      0094AE 08                    6275 	.db #0x08	; 8
      0094AF 35                    6276 	.db #0x35	; 53	'5'
      0094B0 36                    6277 	.db #0x36	; 54	'6'
      0094B1 2D                    6278 	.db #0x2d	; 45
      0094B2 26                    6279 	.db #0x26	; 38
      0094B3 15                    6280 	.db #0x15	; 21
      0094B4 33                    6281 	.db #0x33	; 51	'3'
      0094B5 36                    6282 	.db #0x36	; 54	'6'
      0094B6 1A                    6283 	.db #0x1a	; 26
      0094B7 1C                    6284 	.db #0x1c	; 28
      0094B8 38                    6285 	.db #0x38	; 56	'8'
      0094B9 2B                    6286 	.db #0x2b	; 43
      0094BA 29                    6287 	.db #0x29	; 41
      0094BB 28                    6288 	.db #0x28	; 40
      0094BC 36                    6289 	.db #0x36	; 54	'6'
      0094BD 05                    6290 	.db #0x05	; 5
      0094BE 26                    6291 	.db #0x26	; 38
      0094BF 05                    6292 	.db #0x05	; 5
      0094C0 34                    6293 	.db #0x34	; 52	'4'
      0094C1 06                    6294 	.db #0x06	; 6
      0094C2 15                    6295 	.db #0x15	; 21
      0094C3 01                    6296 	.db #0x01	; 1
      0094C4 00                    6297 	.db #0x00	; 0
      0094C5 03                    6298 	.db #0x03	; 3
      0094C6 0E                    6299 	.db #0x0e	; 14
      0094C7 3D                    6300 	.db #0x3d	; 61
      0094C8 08                    6301 	.db #0x08	; 8
      0094C9 35                    6302 	.db #0x35	; 53	'5'
      0094CA 29                    6303 	.db #0x29	; 41
      0094CB 1E                    6304 	.db #0x1e	; 30
      0094CC 05                    6305 	.db #0x05	; 5
      0094CD 26                    6306 	.db #0x26	; 38
      0094CE 08                    6307 	.db #0x08	; 8
      0094CF 38                    6308 	.db #0x38	; 56	'8'
      0094D0 39                    6309 	.db #0x39	; 57	'9'
      0094D1 0A                    6310 	.db #0x0a	; 10
      0094D2 0A                    6311 	.db #0x0a	; 10
      0094D3 2D                    6312 	.db #0x2d	; 45
      0094D4 0A                    6313 	.db #0x0a	; 10
      0094D5 08                    6314 	.db #0x08	; 8
      0094D6 36                    6315 	.db #0x36	; 54	'6'
      0094D7 05                    6316 	.db #0x05	; 5
      0094D8 36                    6317 	.db #0x36	; 54	'6'
      0094D9 15                    6318 	.db #0x15	; 21
      0094DA 34                    6319 	.db #0x34	; 52	'4'
      0094DB 05                    6320 	.db #0x05	; 5
      0094DC 14                    6321 	.db #0x14	; 20
      0094DD 01                    6322 	.db #0x01	; 1
      0094DE 00                    6323 	.db #0x00	; 0
      0094DF 36                    6324 	.db #0x36	; 54	'6'
      0094E0 3E                    6325 	.db #0x3e	; 62
      0094E1 0E                    6326 	.db #0x0e	; 14
      0094E2 28                    6327 	.db #0x28	; 40
      0094E3 35                    6328 	.db #0x35	; 53	'5'
      0094E4 2F                    6329 	.db #0x2f	; 47
      0094E5 0A                    6330 	.db #0x0a	; 10
      0094E6 05                    6331 	.db #0x05	; 5
      0094E7 36                    6332 	.db #0x36	; 54	'6'
      0094E8 28                    6333 	.db #0x28	; 40
      0094E9 2D                    6334 	.db #0x2d	; 45
      0094EA 2B                    6335 	.db #0x2b	; 43
      0094EB 08                    6336 	.db #0x08	; 8
      0094EC 39                    6337 	.db #0x39	; 57	'9'
      0094ED 39                    6338 	.db #0x39	; 57	'9'
      0094EE 28                    6339 	.db #0x28	; 40
      0094EF 05                    6340 	.db #0x05	; 5
      0094F0 17                    6341 	.db #0x17	; 23
      0094F1 17                    6342 	.db #0x17	; 23
      0094F2 17                    6343 	.db #0x17	; 23
      0094F3 34                    6344 	.db #0x34	; 52	'4'
      0094F4 36                    6345 	.db #0x36	; 54	'6'
      0094F5 15                    6346 	.db #0x15	; 21
      0094F6 01                    6347 	.db #0x01	; 1
      0094F7 22                    6348 	.db #0x22	; 34
      0094F8 00                    6349 	.db #0x00	; 0
      0094F9 36                    6350 	.db #0x36	; 54	'6'
      0094FA 0C                    6351 	.db #0x0c	; 12
      0094FB 2B                    6352 	.db #0x2b	; 43
      0094FC 38                    6353 	.db #0x38	; 56	'8'
      0094FD 26                    6354 	.db #0x26	; 38
      0094FE 2B                    6355 	.db #0x2b	; 43
      0094FF 29                    6356 	.db #0x29	; 41
      009500 38                    6357 	.db #0x38	; 56	'8'
      009501 2B                    6358 	.db #0x2b	; 43
      009502 38                    6359 	.db #0x38	; 56	'8'
      009503 0A                    6360 	.db #0x0a	; 10
      009504 1E                    6361 	.db #0x1e	; 30
      009505 0A                    6362 	.db #0x0a	; 10
      009506 26                    6363 	.db #0x26	; 38
      009507 17                    6364 	.db #0x17	; 23
      009508 17                    6365 	.db #0x17	; 23
      009509 17                    6366 	.db #0x17	; 23
      00950A 17                    6367 	.db #0x17	; 23
      00950B 17                    6368 	.db #0x17	; 23
      00950C 17                    6369 	.db #0x17	; 23
      00950D 36                    6370 	.db #0x36	; 54	'6'
      00950E 06                    6371 	.db #0x06	; 6
      00950F 01                    6372 	.db #0x01	; 1
      009510 01                    6373 	.db #0x01	; 1
      009511 00                    6374 	.db #0x00	; 0
      009512 00                    6375 	.db #0x00	; 0
      009513 36                    6376 	.db #0x36	; 54	'6'
      009514 29                    6377 	.db #0x29	; 41
      009515 08                    6378 	.db #0x08	; 8
      009516 35                    6379 	.db #0x35	; 53	'5'
      009517 35                    6380 	.db #0x35	; 53	'5'
      009518 35                    6381 	.db #0x35	; 53	'5'
      009519 34                    6382 	.db #0x34	; 52	'4'
      00951A 34                    6383 	.db #0x34	; 52	'4'
      00951B 33                    6384 	.db #0x33	; 51	'3'
      00951C 15                    6385 	.db #0x15	; 21
      00951D 35                    6386 	.db #0x35	; 53	'5'
      00951E 0C                    6387 	.db #0x0c	; 12
      00951F 2F                    6388 	.db #0x2f	; 47
      009520 28                    6389 	.db #0x28	; 40
      009521 05                    6390 	.db #0x05	; 5
      009522 36                    6391 	.db #0x36	; 54	'6'
      009523 36                    6392 	.db #0x36	; 54	'6'
      009524 05                    6393 	.db #0x05	; 5
      009525 17                    6394 	.db #0x17	; 23
      009526 17                    6395 	.db #0x17	; 23
      009527 36                    6396 	.db #0x36	; 54	'6'
      009528 01                    6397 	.db #0x01	; 1
      009529 01                    6398 	.db #0x01	; 1
      00952A 22                    6399 	.db #0x22	; 34
      00952B 00                    6400 	.db #0x00	; 0
      00952C 00                    6401 	.db #0x00	; 0
      00952D 02                    6402 	.db #0x02	; 2
      00952E 06                    6403 	.db #0x06	; 6
      00952F 38                    6404 	.db #0x38	; 56	'8'
      009530 35                    6405 	.db #0x35	; 53	'5'
      009531 26                    6406 	.db #0x26	; 38
      009532 05                    6407 	.db #0x05	; 5
      009533 05                    6408 	.db #0x05	; 5
      009534 06                    6409 	.db #0x06	; 6
      009535 26                    6410 	.db #0x26	; 38
      009536 26                    6411 	.db #0x26	; 38
      009537 35                    6412 	.db #0x35	; 53	'5'
      009538 28                    6413 	.db #0x28	; 40
      009539 2D                    6414 	.db #0x2d	; 45
      00953A 29                    6415 	.db #0x29	; 41
      00953B 05                    6416 	.db #0x05	; 5
      00953C 38                    6417 	.db #0x38	; 56	'8'
      00953D 28                    6418 	.db #0x28	; 40
      00953E 38                    6419 	.db #0x38	; 56	'8'
      00953F 17                    6420 	.db #0x17	; 23
      009540 17                    6421 	.db #0x17	; 23
      009541 14                    6422 	.db #0x14	; 20
      009542 01                    6423 	.db #0x01	; 1
      009543 22                    6424 	.db #0x22	; 34
      009544 00                    6425 	.db #0x00	; 0
      009545 00                    6426 	.db #0x00	; 0
      009546 00                    6427 	.db #0x00	; 0
      009547 02                    6428 	.db #0x02	; 2
      009548 06                    6429 	.db #0x06	; 6
      009549 26                    6430 	.db #0x26	; 38
      00954A 02                    6431 	.db #0x02	; 2
      00954B 26                    6432 	.db #0x26	; 38
      00954C 2D                    6433 	.db #0x2d	; 45
      00954D 0A                    6434 	.db #0x0a	; 10
      00954E 08                    6435 	.db #0x08	; 8
      00954F 0C                    6436 	.db #0x0c	; 12
      009550 08                    6437 	.db #0x08	; 8
      009551 36                    6438 	.db #0x36	; 54	'6'
      009552 05                    6439 	.db #0x05	; 5
      009553 0A                    6440 	.db #0x0a	; 10
      009554 08                    6441 	.db #0x08	; 8
      009555 05                    6442 	.db #0x05	; 5
      009556 28                    6443 	.db #0x28	; 40
      009557 39                    6444 	.db #0x39	; 57	'9'
      009558 26                    6445 	.db #0x26	; 38
      009559 17                    6446 	.db #0x17	; 23
      00955A 17                    6447 	.db #0x17	; 23
      00955B 14                    6448 	.db #0x14	; 20
      00955C 22                    6449 	.db #0x22	; 34
      00955D 00                    6450 	.db #0x00	; 0
      00955E 00                    6451 	.db #0x00	; 0
      00955F 00                    6452 	.db #0x00	; 0
      009560 00                    6453 	.db #0x00	; 0
      009561 14                    6454 	.db #0x14	; 20
      009562 08                    6455 	.db #0x08	; 8
      009563 26                    6456 	.db #0x26	; 38
      009564 02                    6457 	.db #0x02	; 2
      009565 18                    6458 	.db #0x18	; 24
      009566 18                    6459 	.db #0x18	; 24
      009567 3B                    6460 	.db #0x3b	; 59
      009568 2C                    6461 	.db #0x2c	; 44
      009569 2A                    6462 	.db #0x2a	; 42
      00956A 18                    6463 	.db #0x18	; 24
      00956B 05                    6464 	.db #0x05	; 5
      00956C 17                    6465 	.db #0x17	; 23
      00956D 2B                    6466 	.db #0x2b	; 43
      00956E 28                    6467 	.db #0x28	; 40
      00956F 05                    6468 	.db #0x05	; 5
      009570 28                    6469 	.db #0x28	; 40
      009571 38                    6470 	.db #0x38	; 56	'8'
      009572 36                    6471 	.db #0x36	; 54	'6'
      009573 17                    6472 	.db #0x17	; 23
      009574 17                    6473 	.db #0x17	; 23
      009575 00                    6474 	.db #0x00	; 0
      009576 00                    6475 	.db #0x00	; 0
      009577 00                    6476 	.db #0x00	; 0
      009578 00                    6477 	.db #0x00	; 0
      009579 00                    6478 	.db #0x00	; 0
      00957A 00                    6479 	.db #0x00	; 0
      00957B 00                    6480 	.db #0x00	; 0
      00957C 0A                    6481 	.db #0x0a	; 10
      00957D 06                    6482 	.db #0x06	; 6
      00957E 02                    6483 	.db #0x02	; 2
      00957F 18                    6484 	.db #0x18	; 24
      009580 40                    6485 	.db #0x40	; 64
      009581 3F                    6486 	.db #0x3f	; 63
      009582 30                    6487 	.db #0x30	; 48	'0'
      009583 30                    6488 	.db #0x30	; 48	'0'
      009584 18                    6489 	.db #0x18	; 24
      009585 18                    6490 	.db #0x18	; 24
      009586 26                    6491 	.db #0x26	; 38
      009587 2B                    6492 	.db #0x2b	; 43
      009588 38                    6493 	.db #0x38	; 56	'8'
      009589 05                    6494 	.db #0x05	; 5
      00958A 38                    6495 	.db #0x38	; 56	'8'
      00958B 36                    6496 	.db #0x36	; 54	'6'
      00958C 17                    6497 	.db #0x17	; 23
      00958D 00                    6498 	.db #0x00	; 0
      00958E 00                    6499 	.db #0x00	; 0
      00958F 00                    6500 	.db #0x00	; 0
      009590 00                    6501 	.db #0x00	; 0
      009591 00                    6502 	.db #0x00	; 0
      009592 00                    6503 	.db #0x00	; 0
      009593 00                    6504 	.db #0x00	; 0
      009594 00                    6505 	.db #0x00	; 0
      009595 00                    6506 	.db #0x00	; 0
      009596 39                    6507 	.db #0x39	; 57	'9'
      009597 2B                    6508 	.db #0x2b	; 43
      009598 17                    6509 	.db #0x17	; 23
      009599 06                    6510 	.db #0x06	; 6
      00959A 09                    6511 	.db #0x09	; 9
      00959B 09                    6512 	.db #0x09	; 9
      00959C 09                    6513 	.db #0x09	; 9
      00959D 29                    6514 	.db #0x29	; 41
      00959E 36                    6515 	.db #0x36	; 54	'6'
      00959F 17                    6516 	.db #0x17	; 23
      0095A0 28                    6517 	.db #0x28	; 40
      0095A1 28                    6518 	.db #0x28	; 40
      0095A2 05                    6519 	.db #0x05	; 5
      0095A3 05                    6520 	.db #0x05	; 5
      0095A4 36                    6521 	.db #0x36	; 54	'6'
      0095A5 17                    6522 	.db #0x17	; 23
      0095A6 00                    6523 	.db #0x00	; 0
      0095A7 00                    6524 	.db #0x00	; 0
      0095A8 00                    6525 	.db #0x00	; 0
      0095A9 00                    6526 	.db #0x00	; 0
      0095AA 00                    6527 	.db #0x00	; 0
      0095AB 00                    6528 	.db #0x00	; 0
      0095AC 00                    6529 	.db #0x00	; 0
      0095AD 00                    6530 	.db #0x00	; 0
      0095AE 00                    6531 	.db #0x00	; 0
      0095AF 00                    6532 	.db #0x00	; 0
      0095B0 08                    6533 	.db #0x08	; 8
      0095B1 12                    6534 	.db #0x12	; 18
      0095B2 3D                    6535 	.db #0x3d	; 61
      0095B3 08                    6536 	.db #0x08	; 8
      0095B4 17                    6537 	.db #0x17	; 23
      0095B5 17                    6538 	.db #0x17	; 23
      0095B6 17                    6539 	.db #0x17	; 23
      0095B7 15                    6540 	.db #0x15	; 21
      0095B8 15                    6541 	.db #0x15	; 21
      0095B9 38                    6542 	.db #0x38	; 56	'8'
      0095BA 28                    6543 	.db #0x28	; 40
      0095BB 05                    6544 	.db #0x05	; 5
      0095BC 05                    6545 	.db #0x05	; 5
      0095BD 36                    6546 	.db #0x36	; 54	'6'
      0095BE 17                    6547 	.db #0x17	; 23
      0095BF 00                    6548 	.db #0x00	; 0
      0095C0 00                    6549 	.db #0x00	; 0
      0095C1 00                    6550 	.db #0x00	; 0
      0095C2 00                    6551 	.db #0x00	; 0
      0095C3 00                    6552 	.db #0x00	; 0
      0095C4 00                    6553 	.db #0x00	; 0
      0095C5 00                    6554 	.db #0x00	; 0
      0095C6 00                    6555 	.db #0x00	; 0
      0095C7 00                    6556 	.db #0x00	; 0
      0095C8 00                    6557 	.db #0x00	; 0
      0095C9 00                    6558 	.db #0x00	; 0
      0095CA 36                    6559 	.db #0x36	; 54	'6'
      0095CB 3D                    6560 	.db #0x3d	; 61
      0095CC 12                    6561 	.db #0x12	; 18
      0095CD 2D                    6562 	.db #0x2d	; 45
      0095CE 0C                    6563 	.db #0x0c	; 12
      0095CF 08                    6564 	.db #0x08	; 8
      0095D0 39                    6565 	.db #0x39	; 57	'9'
      0095D1 26                    6566 	.db #0x26	; 38
      0095D2 36                    6567 	.db #0x36	; 54	'6'
      0095D3 36                    6568 	.db #0x36	; 54	'6'
      0095D4 05                    6569 	.db #0x05	; 5
      0095D5 05                    6570 	.db #0x05	; 5
      0095D6 05                    6571 	.db #0x05	; 5
      0095D7 03                    6572 	.db #0x03	; 3
      0095D8 00                    6573 	.db #0x00	; 0
      0095D9 00                    6574 	.db #0x00	; 0
      0095DA 00                    6575 	.db #0x00	; 0
      0095DB 00                    6576 	.db #0x00	; 0
      0095DC 00                    6577 	.db #0x00	; 0
      0095DD 00                    6578 	.db #0x00	; 0
      0095DE 00                    6579 	.db #0x00	; 0
      0095DF 00                    6580 	.db #0x00	; 0
      0095E0 00                    6581 	.db #0x00	; 0
      0095E1 00                    6582 	.db #0x00	; 0
      0095E2 00                    6583 	.db #0x00	; 0
      0095E3 00                    6584 	.db #0x00	; 0
      0095E4 00                    6585 	.db #0x00	; 0
      0095E5 26                    6586 	.db #0x26	; 38
      0095E6 0C                    6587 	.db #0x0c	; 12
      0095E7 3D                    6588 	.db #0x3d	; 61
      0095E8 0C                    6589 	.db #0x0c	; 12
      0095E9 0A                    6590 	.db #0x0a	; 10
      0095EA 28                    6591 	.db #0x28	; 40
      0095EB 26                    6592 	.db #0x26	; 38
      0095EC 26                    6593 	.db #0x26	; 38
      0095ED 05                    6594 	.db #0x05	; 5
      0095EE 05                    6595 	.db #0x05	; 5
      0095EF 03                    6596 	.db #0x03	; 3
      0095F0 00                    6597 	.db #0x00	; 0
      0095F1 00                    6598 	.db #0x00	; 0
      0095F2 00                    6599 	.db #0x00	; 0
      0095F3 00                    6600 	.db #0x00	; 0
      0095F4 00                    6601 	.db #0x00	; 0
      0095F5 00                    6602 	.db #0x00	; 0
      0095F6 00                    6603 	.db #0x00	; 0
      0095F7 00                    6604 	.db #0x00	; 0
      0095F8 00                    6605 	.db #0x00	; 0
      0095F9 00                    6606 	.db #0x00	; 0
      0095FA 00                    6607 	.db #0x00	; 0
      0095FB 00                    6608 	.db #0x00	; 0
      0095FC 00                    6609 	.db #0x00	; 0
      0095FD 00                    6610 	.db #0x00	; 0
      0095FE 00                    6611 	.db #0x00	; 0
      0095FF 00                    6612 	.db #0x00	; 0
      009600 36                    6613 	.db #0x36	; 54	'6'
      009601 06                    6614 	.db #0x06	; 6
      009602 06                    6615 	.db #0x06	; 6
      009603 06                    6616 	.db #0x06	; 6
      009604 06                    6617 	.db #0x06	; 6
      009605 06                    6618 	.db #0x06	; 6
      009606 03                    6619 	.db #0x03	; 3
      009607 15                    6620 	.db #0x15	; 21
      009608 00                    6621 	.db #0x00	; 0
      009609 00                    6622 	.db #0x00	; 0
      00960A 00                    6623 	.db #0x00	; 0
      00960B 00                    6624 	.db #0x00	; 0
      00960C 00                    6625 	.db #0x00	; 0
      00960D 00                    6626 	.db #0x00	; 0
      00960E 00                    6627 	.db #0x00	; 0
      00960F 00                    6628 	.db #0x00	; 0
      009610 00                    6629 	.db #0x00	; 0
      009611 00                    6630 	.db #0x00	; 0
      009612 00                    6631 	.db #0x00	; 0
      009613 00                    6632 	.db #0x00	; 0
      009614 00                    6633 	.db #0x00	; 0
      009615 00                    6634 	.db #0x00	; 0
      009616                       6635 _doom8_raw:
      009616 00                    6636 	.db #0x00	; 0
      009617 00                    6637 	.db #0x00	; 0
      009618 00                    6638 	.db #0x00	; 0
      009619 00                    6639 	.db #0x00	; 0
      00961A 00                    6640 	.db #0x00	; 0
      00961B 00                    6641 	.db #0x00	; 0
      00961C 00                    6642 	.db #0x00	; 0
      00961D 01                    6643 	.db #0x01	; 1
      00961E 33                    6644 	.db #0x33	; 51	'3'
      00961F 15                    6645 	.db #0x15	; 21
      009620 35                    6646 	.db #0x35	; 53	'5'
      009621 35                    6647 	.db #0x35	; 53	'5'
      009622 35                    6648 	.db #0x35	; 53	'5'
      009623 35                    6649 	.db #0x35	; 53	'5'
      009624 35                    6650 	.db #0x35	; 53	'5'
      009625 15                    6651 	.db #0x15	; 21
      009626 02                    6652 	.db #0x02	; 2
      009627 02                    6653 	.db #0x02	; 2
      009628 00                    6654 	.db #0x00	; 0
      009629 00                    6655 	.db #0x00	; 0
      00962A 00                    6656 	.db #0x00	; 0
      00962B 00                    6657 	.db #0x00	; 0
      00962C 00                    6658 	.db #0x00	; 0
      00962D 00                    6659 	.db #0x00	; 0
      00962E 00                    6660 	.db #0x00	; 0
      00962F 00                    6661 	.db #0x00	; 0
      009630 00                    6662 	.db #0x00	; 0
      009631 00                    6663 	.db #0x00	; 0
      009632 00                    6664 	.db #0x00	; 0
      009633 00                    6665 	.db #0x00	; 0
      009634 00                    6666 	.db #0x00	; 0
      009635 01                    6667 	.db #0x01	; 1
      009636 14                    6668 	.db #0x14	; 20
      009637 34                    6669 	.db #0x34	; 52	'4'
      009638 15                    6670 	.db #0x15	; 21
      009639 03                    6671 	.db #0x03	; 3
      00963A 36                    6672 	.db #0x36	; 54	'6'
      00963B 36                    6673 	.db #0x36	; 54	'6'
      00963C 05                    6674 	.db #0x05	; 5
      00963D 38                    6675 	.db #0x38	; 56	'8'
      00963E 38                    6676 	.db #0x38	; 56	'8'
      00963F 26                    6677 	.db #0x26	; 38
      009640 05                    6678 	.db #0x05	; 5
      009641 35                    6679 	.db #0x35	; 53	'5'
      009642 15                    6680 	.db #0x15	; 21
      009643 02                    6681 	.db #0x02	; 2
      009644 14                    6682 	.db #0x14	; 20
      009645 00                    6683 	.db #0x00	; 0
      009646 00                    6684 	.db #0x00	; 0
      009647 00                    6685 	.db #0x00	; 0
      009648 00                    6686 	.db #0x00	; 0
      009649 00                    6687 	.db #0x00	; 0
      00964A 00                    6688 	.db #0x00	; 0
      00964B 00                    6689 	.db #0x00	; 0
      00964C 00                    6690 	.db #0x00	; 0
      00964D 00                    6691 	.db #0x00	; 0
      00964E 01                    6692 	.db #0x01	; 1
      00964F 14                    6693 	.db #0x14	; 20
      009650 34                    6694 	.db #0x34	; 52	'4'
      009651 02                    6695 	.db #0x02	; 2
      009652 35                    6696 	.db #0x35	; 53	'5'
      009653 17                    6697 	.db #0x17	; 23
      009654 36                    6698 	.db #0x36	; 54	'6'
      009655 05                    6699 	.db #0x05	; 5
      009656 38                    6700 	.db #0x38	; 56	'8'
      009657 28                    6701 	.db #0x28	; 40
      009658 39                    6702 	.db #0x39	; 57	'9'
      009659 08                    6703 	.db #0x08	; 8
      00965A 28                    6704 	.db #0x28	; 40
      00965B 26                    6705 	.db #0x26	; 38
      00965C 05                    6706 	.db #0x05	; 5
      00965D 36                    6707 	.db #0x36	; 54	'6'
      00965E 02                    6708 	.db #0x02	; 2
      00965F 14                    6709 	.db #0x14	; 20
      009660 14                    6710 	.db #0x14	; 20
      009661 00                    6711 	.db #0x00	; 0
      009662 00                    6712 	.db #0x00	; 0
      009663 00                    6713 	.db #0x00	; 0
      009664 00                    6714 	.db #0x00	; 0
      009665 00                    6715 	.db #0x00	; 0
      009666 00                    6716 	.db #0x00	; 0
      009667 01                    6717 	.db #0x01	; 1
      009668 33                    6718 	.db #0x33	; 51	'3'
      009669 14                    6719 	.db #0x14	; 20
      00966A 34                    6720 	.db #0x34	; 52	'4'
      00966B 15                    6721 	.db #0x15	; 21
      00966C 15                    6722 	.db #0x15	; 21
      00966D 17                    6723 	.db #0x17	; 23
      00966E 17                    6724 	.db #0x17	; 23
      00966F 36                    6725 	.db #0x36	; 54	'6'
      009670 36                    6726 	.db #0x36	; 54	'6'
      009671 38                    6727 	.db #0x38	; 56	'8'
      009672 28                    6728 	.db #0x28	; 40
      009673 08                    6729 	.db #0x08	; 8
      009674 08                    6730 	.db #0x08	; 8
      009675 08                    6731 	.db #0x08	; 8
      009676 28                    6732 	.db #0x28	; 40
      009677 26                    6733 	.db #0x26	; 38
      009678 36                    6734 	.db #0x36	; 54	'6'
      009679 02                    6735 	.db #0x02	; 2
      00967A 02                    6736 	.db #0x02	; 2
      00967B 02                    6737 	.db #0x02	; 2
      00967C 00                    6738 	.db #0x00	; 0
      00967D 00                    6739 	.db #0x00	; 0
      00967E 00                    6740 	.db #0x00	; 0
      00967F 00                    6741 	.db #0x00	; 0
      009680 01                    6742 	.db #0x01	; 1
      009681 33                    6743 	.db #0x33	; 51	'3'
      009682 14                    6744 	.db #0x14	; 20
      009683 14                    6745 	.db #0x14	; 20
      009684 34                    6746 	.db #0x34	; 52	'4'
      009685 15                    6747 	.db #0x15	; 21
      009686 15                    6748 	.db #0x15	; 21
      009687 35                    6749 	.db #0x35	; 53	'5'
      009688 36                    6750 	.db #0x36	; 54	'6'
      009689 17                    6751 	.db #0x17	; 23
      00968A 17                    6752 	.db #0x17	; 23
      00968B 36                    6753 	.db #0x36	; 54	'6'
      00968C 36                    6754 	.db #0x36	; 54	'6'
      00968D 06                    6755 	.db #0x06	; 6
      00968E 28                    6756 	.db #0x28	; 40
      00968F 06                    6757 	.db #0x06	; 6
      009690 06                    6758 	.db #0x06	; 6
      009691 28                    6759 	.db #0x28	; 40
      009692 26                    6760 	.db #0x26	; 38
      009693 36                    6761 	.db #0x36	; 54	'6'
      009694 17                    6762 	.db #0x17	; 23
      009695 01                    6763 	.db #0x01	; 1
      009696 01                    6764 	.db #0x01	; 1
      009697 00                    6765 	.db #0x00	; 0
      009698 00                    6766 	.db #0x00	; 0
      009699 01                    6767 	.db #0x01	; 1
      00969A 33                    6768 	.db #0x33	; 51	'3'
      00969B 14                    6769 	.db #0x14	; 20
      00969C 33                    6770 	.db #0x33	; 51	'3'
      00969D 14                    6771 	.db #0x14	; 20
      00969E 02                    6772 	.db #0x02	; 2
      00969F 02                    6773 	.db #0x02	; 2
      0096A0 02                    6774 	.db #0x02	; 2
      0096A1 03                    6775 	.db #0x03	; 3
      0096A2 15                    6776 	.db #0x15	; 21
      0096A3 02                    6777 	.db #0x02	; 2
      0096A4 02                    6778 	.db #0x02	; 2
      0096A5 17                    6779 	.db #0x17	; 23
      0096A6 36                    6780 	.db #0x36	; 54	'6'
      0096A7 05                    6781 	.db #0x05	; 5
      0096A8 06                    6782 	.db #0x06	; 6
      0096A9 36                    6783 	.db #0x36	; 54	'6'
      0096AA 36                    6784 	.db #0x36	; 54	'6'
      0096AB 06                    6785 	.db #0x06	; 6
      0096AC 14                    6786 	.db #0x14	; 20
      0096AD 36                    6787 	.db #0x36	; 54	'6'
      0096AE 22                    6788 	.db #0x22	; 34
      0096AF 14                    6789 	.db #0x14	; 20
      0096B0 33                    6790 	.db #0x33	; 51	'3'
      0096B1 00                    6791 	.db #0x00	; 0
      0096B2 00                    6792 	.db #0x00	; 0
      0096B3 33                    6793 	.db #0x33	; 51	'3'
      0096B4 14                    6794 	.db #0x14	; 20
      0096B5 33                    6795 	.db #0x33	; 51	'3'
      0096B6 22                    6796 	.db #0x22	; 34
      0096B7 14                    6797 	.db #0x14	; 20
      0096B8 34                    6798 	.db #0x34	; 52	'4'
      0096B9 34                    6799 	.db #0x34	; 52	'4'
      0096BA 34                    6800 	.db #0x34	; 52	'4'
      0096BB 15                    6801 	.db #0x15	; 21
      0096BC 34                    6802 	.db #0x34	; 52	'4'
      0096BD 34                    6803 	.db #0x34	; 52	'4'
      0096BE 01                    6804 	.db #0x01	; 1
      0096BF 02                    6805 	.db #0x02	; 2
      0096C0 36                    6806 	.db #0x36	; 54	'6'
      0096C1 34                    6807 	.db #0x34	; 52	'4'
      0096C2 05                    6808 	.db #0x05	; 5
      0096C3 15                    6809 	.db #0x15	; 21
      0096C4 15                    6810 	.db #0x15	; 21
      0096C5 36                    6811 	.db #0x36	; 54	'6'
      0096C6 15                    6812 	.db #0x15	; 21
      0096C7 14                    6813 	.db #0x14	; 20
      0096C8 22                    6814 	.db #0x22	; 34
      0096C9 33                    6815 	.db #0x33	; 51	'3'
      0096CA 01                    6816 	.db #0x01	; 1
      0096CB 00                    6817 	.db #0x00	; 0
      0096CC 01                    6818 	.db #0x01	; 1
      0096CD 14                    6819 	.db #0x14	; 20
      0096CE 33                    6820 	.db #0x33	; 51	'3'
      0096CF 22                    6821 	.db #0x22	; 34
      0096D0 33                    6822 	.db #0x33	; 51	'3'
      0096D1 34                    6823 	.db #0x34	; 52	'4'
      0096D2 14                    6824 	.db #0x14	; 20
      0096D3 14                    6825 	.db #0x14	; 20
      0096D4 15                    6826 	.db #0x15	; 21
      0096D5 34                    6827 	.db #0x34	; 52	'4'
      0096D6 33                    6828 	.db #0x33	; 51	'3'
      0096D7 33                    6829 	.db #0x33	; 51	'3'
      0096D8 17                    6830 	.db #0x17	; 23
      0096D9 35                    6831 	.db #0x35	; 53	'5'
      0096DA 34                    6832 	.db #0x34	; 52	'4'
      0096DB 36                    6833 	.db #0x36	; 54	'6'
      0096DC 34                    6834 	.db #0x34	; 52	'4'
      0096DD 15                    6835 	.db #0x15	; 21
      0096DE 35                    6836 	.db #0x35	; 53	'5'
      0096DF 15                    6837 	.db #0x15	; 21
      0096E0 36                    6838 	.db #0x36	; 54	'6'
      0096E1 36                    6839 	.db #0x36	; 54	'6'
      0096E2 03                    6840 	.db #0x03	; 3
      0096E3 34                    6841 	.db #0x34	; 52	'4'
      0096E4 22                    6842 	.db #0x22	; 34
      0096E5 00                    6843 	.db #0x00	; 0
      0096E6 22                    6844 	.db #0x22	; 34
      0096E7 14                    6845 	.db #0x14	; 20
      0096E8 22                    6846 	.db #0x22	; 34
      0096E9 22                    6847 	.db #0x22	; 34
      0096EA 33                    6848 	.db #0x33	; 51	'3'
      0096EB 14                    6849 	.db #0x14	; 20
      0096EC 14                    6850 	.db #0x14	; 20
      0096ED 34                    6851 	.db #0x34	; 52	'4'
      0096EE 34                    6852 	.db #0x34	; 52	'4'
      0096EF 01                    6853 	.db #0x01	; 1
      0096F0 33                    6854 	.db #0x33	; 51	'3'
      0096F1 36                    6855 	.db #0x36	; 54	'6'
      0096F2 38                    6856 	.db #0x38	; 56	'8'
      0096F3 36                    6857 	.db #0x36	; 54	'6'
      0096F4 35                    6858 	.db #0x35	; 53	'5'
      0096F5 34                    6859 	.db #0x34	; 52	'4'
      0096F6 26                    6860 	.db #0x26	; 38
      0096F7 34                    6861 	.db #0x34	; 52	'4'
      0096F8 35                    6862 	.db #0x35	; 53	'5'
      0096F9 36                    6863 	.db #0x36	; 54	'6'
      0096FA 26                    6864 	.db #0x26	; 38
      0096FB 06                    6865 	.db #0x06	; 6
      0096FC 29                    6866 	.db #0x29	; 41
      0096FD 03                    6867 	.db #0x03	; 3
      0096FE 15                    6868 	.db #0x15	; 21
      0096FF 00                    6869 	.db #0x00	; 0
      009700 33                    6870 	.db #0x33	; 51	'3'
      009701 33                    6871 	.db #0x33	; 51	'3'
      009702 22                    6872 	.db #0x22	; 34
      009703 22                    6873 	.db #0x22	; 34
      009704 33                    6874 	.db #0x33	; 51	'3'
      009705 14                    6875 	.db #0x14	; 20
      009706 14                    6876 	.db #0x14	; 20
      009707 34                    6877 	.db #0x34	; 52	'4'
      009708 33                    6878 	.db #0x33	; 51	'3'
      009709 14                    6879 	.db #0x14	; 20
      00970A 03                    6880 	.db #0x03	; 3
      00970B 38                    6881 	.db #0x38	; 56	'8'
      00970C 06                    6882 	.db #0x06	; 6
      00970D 38                    6883 	.db #0x38	; 56	'8'
      00970E 06                    6884 	.db #0x06	; 6
      00970F 26                    6885 	.db #0x26	; 38
      009710 26                    6886 	.db #0x26	; 38
      009711 06                    6887 	.db #0x06	; 6
      009712 06                    6888 	.db #0x06	; 6
      009713 06                    6889 	.db #0x06	; 6
      009714 06                    6890 	.db #0x06	; 6
      009715 06                    6891 	.db #0x06	; 6
      009716 29                    6892 	.db #0x29	; 41
      009717 29                    6893 	.db #0x29	; 41
      009718 05                    6894 	.db #0x05	; 5
      009719 00                    6895 	.db #0x00	; 0
      00971A 33                    6896 	.db #0x33	; 51	'3'
      00971B 22                    6897 	.db #0x22	; 34
      00971C 22                    6898 	.db #0x22	; 34
      00971D 33                    6899 	.db #0x33	; 51	'3'
      00971E 14                    6900 	.db #0x14	; 20
      00971F 14                    6901 	.db #0x14	; 20
      009720 34                    6902 	.db #0x34	; 52	'4'
      009721 34                    6903 	.db #0x34	; 52	'4'
      009722 14                    6904 	.db #0x14	; 20
      009723 02                    6905 	.db #0x02	; 2
      009724 05                    6906 	.db #0x05	; 5
      009725 06                    6907 	.db #0x06	; 6
      009726 08                    6908 	.db #0x08	; 8
      009727 29                    6909 	.db #0x29	; 41
      009728 29                    6910 	.db #0x29	; 41
      009729 29                    6911 	.db #0x29	; 41
      00972A 08                    6912 	.db #0x08	; 8
      00972B 38                    6913 	.db #0x38	; 56	'8'
      00972C 38                    6914 	.db #0x38	; 56	'8'
      00972D 38                    6915 	.db #0x38	; 56	'8'
      00972E 38                    6916 	.db #0x38	; 56	'8'
      00972F 06                    6917 	.db #0x06	; 6
      009730 29                    6918 	.db #0x29	; 41
      009731 0C                    6919 	.db #0x0c	; 12
      009732 29                    6920 	.db #0x29	; 41
      009733 14                    6921 	.db #0x14	; 20
      009734 33                    6922 	.db #0x33	; 51	'3'
      009735 22                    6923 	.db #0x22	; 34
      009736 22                    6924 	.db #0x22	; 34
      009737 33                    6925 	.db #0x33	; 51	'3'
      009738 14                    6926 	.db #0x14	; 20
      009739 14                    6927 	.db #0x14	; 20
      00973A 34                    6928 	.db #0x34	; 52	'4'
      00973B 34                    6929 	.db #0x34	; 52	'4'
      00973C 02                    6930 	.db #0x02	; 2
      00973D 35                    6931 	.db #0x35	; 53	'5'
      00973E 05                    6932 	.db #0x05	; 5
      00973F 28                    6933 	.db #0x28	; 40
      009740 0A                    6934 	.db #0x0a	; 10
      009741 2F                    6935 	.db #0x2f	; 47
      009742 1E                    6936 	.db #0x1e	; 30
      009743 2F                    6937 	.db #0x2f	; 47
      009744 0A                    6938 	.db #0x0a	; 10
      009745 08                    6939 	.db #0x08	; 8
      009746 06                    6940 	.db #0x06	; 6
      009747 06                    6941 	.db #0x06	; 6
      009748 06                    6942 	.db #0x06	; 6
      009749 08                    6943 	.db #0x08	; 8
      00974A 0A                    6944 	.db #0x0a	; 10
      00974B 2F                    6945 	.db #0x2f	; 47
      00974C 29                    6946 	.db #0x29	; 41
      00974D 02                    6947 	.db #0x02	; 2
      00974E 22                    6948 	.db #0x22	; 34
      00974F 22                    6949 	.db #0x22	; 34
      009750 22                    6950 	.db #0x22	; 34
      009751 33                    6951 	.db #0x33	; 51	'3'
      009752 14                    6952 	.db #0x14	; 20
      009753 14                    6953 	.db #0x14	; 20
      009754 34                    6954 	.db #0x34	; 52	'4'
      009755 02                    6955 	.db #0x02	; 2
      009756 02                    6956 	.db #0x02	; 2
      009757 35                    6957 	.db #0x35	; 53	'5'
      009758 06                    6958 	.db #0x06	; 6
      009759 29                    6959 	.db #0x29	; 41
      00975A 2D                    6960 	.db #0x2d	; 45
      00975B 1E                    6961 	.db #0x1e	; 30
      00975C 2F                    6962 	.db #0x2f	; 47
      00975D 2D                    6963 	.db #0x2d	; 45
      00975E 2F                    6964 	.db #0x2f	; 47
      00975F 2D                    6965 	.db #0x2d	; 45
      009760 0A                    6966 	.db #0x0a	; 10
      009761 08                    6967 	.db #0x08	; 8
      009762 06                    6968 	.db #0x06	; 6
      009763 0A                    6969 	.db #0x0a	; 10
      009764 0C                    6970 	.db #0x0c	; 12
      009765 2F                    6971 	.db #0x2f	; 47
      009766 2B                    6972 	.db #0x2b	; 43
      009767 36                    6973 	.db #0x36	; 54	'6'
      009768 22                    6974 	.db #0x22	; 34
      009769 22                    6975 	.db #0x22	; 34
      00976A 22                    6976 	.db #0x22	; 34
      00976B 15                    6977 	.db #0x15	; 21
      00976C 26                    6978 	.db #0x26	; 38
      00976D 36                    6979 	.db #0x36	; 54	'6'
      00976E 35                    6980 	.db #0x35	; 53	'5'
      00976F 35                    6981 	.db #0x35	; 53	'5'
      009770 36                    6982 	.db #0x36	; 54	'6'
      009771 36                    6983 	.db #0x36	; 54	'6'
      009772 06                    6984 	.db #0x06	; 6
      009773 17                    6985 	.db #0x17	; 23
      009774 34                    6986 	.db #0x34	; 52	'4'
      009775 33                    6987 	.db #0x33	; 51	'3'
      009776 36                    6988 	.db #0x36	; 54	'6'
      009777 06                    6989 	.db #0x06	; 6
      009778 08                    6990 	.db #0x08	; 8
      009779 2B                    6991 	.db #0x2b	; 43
      00977A 2B                    6992 	.db #0x2b	; 43
      00977B 2F                    6993 	.db #0x2f	; 47
      00977C 08                    6994 	.db #0x08	; 8
      00977D 0C                    6995 	.db #0x0c	; 12
      00977E 06                    6996 	.db #0x06	; 6
      00977F 33                    6997 	.db #0x33	; 51	'3'
      009780 33                    6998 	.db #0x33	; 51	'3'
      009781 33                    6999 	.db #0x33	; 51	'3'
      009782 22                    7000 	.db #0x22	; 34
      009783 22                    7001 	.db #0x22	; 34
      009784 17                    7002 	.db #0x17	; 23
      009785 34                    7003 	.db #0x34	; 52	'4'
      009786 02                    7004 	.db #0x02	; 2
      009787 03                    7005 	.db #0x03	; 3
      009788 06                    7006 	.db #0x06	; 6
      009789 36                    7007 	.db #0x36	; 54	'6'
      00978A 36                    7008 	.db #0x36	; 54	'6'
      00978B 05                    7009 	.db #0x05	; 5
      00978C 05                    7010 	.db #0x05	; 5
      00978D 38                    7011 	.db #0x38	; 56	'8'
      00978E 39                    7012 	.db #0x39	; 57	'9'
      00978F 36                    7013 	.db #0x36	; 54	'6'
      009790 33                    7014 	.db #0x33	; 51	'3'
      009791 33                    7015 	.db #0x33	; 51	'3'
      009792 02                    7016 	.db #0x02	; 2
      009793 35                    7017 	.db #0x35	; 53	'5'
      009794 06                    7018 	.db #0x06	; 6
      009795 06                    7019 	.db #0x06	; 6
      009796 35                    7020 	.db #0x35	; 53	'5'
      009797 34                    7021 	.db #0x34	; 52	'4'
      009798 1F                    7022 	.db #0x1f	; 31
      009799 00                    7023 	.db #0x00	; 0
      00979A 15                    7024 	.db #0x15	; 21
      00979B 00                    7025 	.db #0x00	; 0
      00979C 01                    7026 	.db #0x01	; 1
      00979D 22                    7027 	.db #0x22	; 34
      00979E 17                    7028 	.db #0x17	; 23
      00979F 06                    7029 	.db #0x06	; 6
      0097A0 02                    7030 	.db #0x02	; 2
      0097A1 03                    7031 	.db #0x03	; 3
      0097A2 03                    7032 	.db #0x03	; 3
      0097A3 05                    7033 	.db #0x05	; 5
      0097A4 36                    7034 	.db #0x36	; 54	'6'
      0097A5 05                    7035 	.db #0x05	; 5
      0097A6 26                    7036 	.db #0x26	; 38
      0097A7 38                    7037 	.db #0x38	; 56	'8'
      0097A8 15                    7038 	.db #0x15	; 21
      0097A9 3F                    7039 	.db #0x3f	; 63
      0097AA 2C                    7040 	.db #0x2c	; 44
      0097AB 00                    7041 	.db #0x00	; 0
      0097AC 15                    7042 	.db #0x15	; 21
      0097AD 34                    7043 	.db #0x34	; 52	'4'
      0097AE 14                    7044 	.db #0x14	; 20
      0097AF 34                    7045 	.db #0x34	; 52	'4'
      0097B0 00                    7046 	.db #0x00	; 0
      0097B1 01                    7047 	.db #0x01	; 1
      0097B2 35                    7048 	.db #0x35	; 53	'5'
      0097B3 05                    7049 	.db #0x05	; 5
      0097B4 39                    7050 	.db #0x39	; 57	'9'
      0097B5 00                    7051 	.db #0x00	; 0
      0097B6 00                    7052 	.db #0x00	; 0
      0097B7 22                    7053 	.db #0x22	; 34
      0097B8 15                    7054 	.db #0x15	; 21
      0097B9 06                    7055 	.db #0x06	; 6
      0097BA 34                    7056 	.db #0x34	; 52	'4'
      0097BB 05                    7057 	.db #0x05	; 5
      0097BC 26                    7058 	.db #0x26	; 38
      0097BD 05                    7059 	.db #0x05	; 5
      0097BE 36                    7060 	.db #0x36	; 54	'6'
      0097BF 28                    7061 	.db #0x28	; 40
      0097C0 29                    7062 	.db #0x29	; 41
      0097C1 2B                    7063 	.db #0x2b	; 43
      0097C2 38                    7064 	.db #0x38	; 56	'8'
      0097C3 1C                    7065 	.db #0x1c	; 28
      0097C4 1A                    7066 	.db #0x1a	; 26
      0097C5 36                    7067 	.db #0x36	; 54	'6'
      0097C6 33                    7068 	.db #0x33	; 51	'3'
      0097C7 15                    7069 	.db #0x15	; 21
      0097C8 26                    7070 	.db #0x26	; 38
      0097C9 2D                    7071 	.db #0x2d	; 45
      0097CA 36                    7072 	.db #0x36	; 54	'6'
      0097CB 35                    7073 	.db #0x35	; 53	'5'
      0097CC 08                    7074 	.db #0x08	; 8
      0097CD 2D                    7075 	.db #0x2d	; 45
      0097CE 0A                    7076 	.db #0x0a	; 10
      0097CF 03                    7077 	.db #0x03	; 3
      0097D0 00                    7078 	.db #0x00	; 0
      0097D1 22                    7079 	.db #0x22	; 34
      0097D2 22                    7080 	.db #0x22	; 34
      0097D3 05                    7081 	.db #0x05	; 5
      0097D4 34                    7082 	.db #0x34	; 52	'4'
      0097D5 15                    7083 	.db #0x15	; 21
      0097D6 36                    7084 	.db #0x36	; 54	'6'
      0097D7 05                    7085 	.db #0x05	; 5
      0097D8 36                    7086 	.db #0x36	; 54	'6'
      0097D9 08                    7087 	.db #0x08	; 8
      0097DA 0A                    7088 	.db #0x0a	; 10
      0097DB 2D                    7089 	.db #0x2d	; 45
      0097DC 0A                    7090 	.db #0x0a	; 10
      0097DD 0A                    7091 	.db #0x0a	; 10
      0097DE 39                    7092 	.db #0x39	; 57	'9'
      0097DF 38                    7093 	.db #0x38	; 56	'8'
      0097E0 08                    7094 	.db #0x08	; 8
      0097E1 26                    7095 	.db #0x26	; 38
      0097E2 05                    7096 	.db #0x05	; 5
      0097E3 1E                    7097 	.db #0x1e	; 30
      0097E4 29                    7098 	.db #0x29	; 41
      0097E5 35                    7099 	.db #0x35	; 53	'5'
      0097E6 08                    7100 	.db #0x08	; 8
      0097E7 3D                    7101 	.db #0x3d	; 61
      0097E8 0E                    7102 	.db #0x0e	; 14
      0097E9 03                    7103 	.db #0x03	; 3
      0097EA 00                    7104 	.db #0x00	; 0
      0097EB 22                    7105 	.db #0x22	; 34
      0097EC 22                    7106 	.db #0x22	; 34
      0097ED 15                    7107 	.db #0x15	; 21
      0097EE 36                    7108 	.db #0x36	; 54	'6'
      0097EF 34                    7109 	.db #0x34	; 52	'4'
      0097F0 17                    7110 	.db #0x17	; 23
      0097F1 17                    7111 	.db #0x17	; 23
      0097F2 17                    7112 	.db #0x17	; 23
      0097F3 05                    7113 	.db #0x05	; 5
      0097F4 28                    7114 	.db #0x28	; 40
      0097F5 39                    7115 	.db #0x39	; 57	'9'
      0097F6 39                    7116 	.db #0x39	; 57	'9'
      0097F7 08                    7117 	.db #0x08	; 8
      0097F8 2B                    7118 	.db #0x2b	; 43
      0097F9 2D                    7119 	.db #0x2d	; 45
      0097FA 28                    7120 	.db #0x28	; 40
      0097FB 36                    7121 	.db #0x36	; 54	'6'
      0097FC 05                    7122 	.db #0x05	; 5
      0097FD 0A                    7123 	.db #0x0a	; 10
      0097FE 2F                    7124 	.db #0x2f	; 47
      0097FF 35                    7125 	.db #0x35	; 53	'5'
      009800 28                    7126 	.db #0x28	; 40
      009801 0E                    7127 	.db #0x0e	; 14
      009802 3E                    7128 	.db #0x3e	; 62
      009803 36                    7129 	.db #0x36	; 54	'6'
      009804 00                    7130 	.db #0x00	; 0
      009805 00                    7131 	.db #0x00	; 0
      009806 22                    7132 	.db #0x22	; 34
      009807 22                    7133 	.db #0x22	; 34
      009808 06                    7134 	.db #0x06	; 6
      009809 36                    7135 	.db #0x36	; 54	'6'
      00980A 17                    7136 	.db #0x17	; 23
      00980B 17                    7137 	.db #0x17	; 23
      00980C 17                    7138 	.db #0x17	; 23
      00980D 17                    7139 	.db #0x17	; 23
      00980E 17                    7140 	.db #0x17	; 23
      00980F 17                    7141 	.db #0x17	; 23
      009810 26                    7142 	.db #0x26	; 38
      009811 0A                    7143 	.db #0x0a	; 10
      009812 1E                    7144 	.db #0x1e	; 30
      009813 0A                    7145 	.db #0x0a	; 10
      009814 38                    7146 	.db #0x38	; 56	'8'
      009815 2B                    7147 	.db #0x2b	; 43
      009816 38                    7148 	.db #0x38	; 56	'8'
      009817 29                    7149 	.db #0x29	; 41
      009818 2B                    7150 	.db #0x2b	; 43
      009819 26                    7151 	.db #0x26	; 38
      00981A 38                    7152 	.db #0x38	; 56	'8'
      00981B 2B                    7153 	.db #0x2b	; 43
      00981C 0C                    7154 	.db #0x0c	; 12
      00981D 36                    7155 	.db #0x36	; 54	'6'
      00981E 00                    7156 	.db #0x00	; 0
      00981F 00                    7157 	.db #0x00	; 0
      009820 22                    7158 	.db #0x22	; 34
      009821 22                    7159 	.db #0x22	; 34
      009822 36                    7160 	.db #0x36	; 54	'6'
      009823 36                    7161 	.db #0x36	; 54	'6'
      009824 17                    7162 	.db #0x17	; 23
      009825 17                    7163 	.db #0x17	; 23
      009826 05                    7164 	.db #0x05	; 5
      009827 36                    7165 	.db #0x36	; 54	'6'
      009828 36                    7166 	.db #0x36	; 54	'6'
      009829 05                    7167 	.db #0x05	; 5
      00982A 28                    7168 	.db #0x28	; 40
      00982B 2F                    7169 	.db #0x2f	; 47
      00982C 0C                    7170 	.db #0x0c	; 12
      00982D 35                    7171 	.db #0x35	; 53	'5'
      00982E 15                    7172 	.db #0x15	; 21
      00982F 33                    7173 	.db #0x33	; 51	'3'
      009830 34                    7174 	.db #0x34	; 52	'4'
      009831 34                    7175 	.db #0x34	; 52	'4'
      009832 35                    7176 	.db #0x35	; 53	'5'
      009833 35                    7177 	.db #0x35	; 53	'5'
      009834 35                    7178 	.db #0x35	; 53	'5'
      009835 08                    7179 	.db #0x08	; 8
      009836 29                    7180 	.db #0x29	; 41
      009837 36                    7181 	.db #0x36	; 54	'6'
      009838 00                    7182 	.db #0x00	; 0
      009839 00                    7183 	.db #0x00	; 0
      00983A 00                    7184 	.db #0x00	; 0
      00983B 22                    7185 	.db #0x22	; 34
      00983C 34                    7186 	.db #0x34	; 52	'4'
      00983D 36                    7187 	.db #0x36	; 54	'6'
      00983E 17                    7188 	.db #0x17	; 23
      00983F 17                    7189 	.db #0x17	; 23
      009840 38                    7190 	.db #0x38	; 56	'8'
      009841 28                    7191 	.db #0x28	; 40
      009842 38                    7192 	.db #0x38	; 56	'8'
      009843 05                    7193 	.db #0x05	; 5
      009844 29                    7194 	.db #0x29	; 41
      009845 2D                    7195 	.db #0x2d	; 45
      009846 28                    7196 	.db #0x28	; 40
      009847 35                    7197 	.db #0x35	; 53	'5'
      009848 26                    7198 	.db #0x26	; 38
      009849 26                    7199 	.db #0x26	; 38
      00984A 06                    7200 	.db #0x06	; 6
      00984B 05                    7201 	.db #0x05	; 5
      00984C 05                    7202 	.db #0x05	; 5
      00984D 26                    7203 	.db #0x26	; 38
      00984E 35                    7204 	.db #0x35	; 53	'5'
      00984F 38                    7205 	.db #0x38	; 56	'8'
      009850 06                    7206 	.db #0x06	; 6
      009851 02                    7207 	.db #0x02	; 2
      009852 00                    7208 	.db #0x00	; 0
      009853 00                    7209 	.db #0x00	; 0
      009854 00                    7210 	.db #0x00	; 0
      009855 00                    7211 	.db #0x00	; 0
      009856 00                    7212 	.db #0x00	; 0
      009857 36                    7213 	.db #0x36	; 54	'6'
      009858 17                    7214 	.db #0x17	; 23
      009859 17                    7215 	.db #0x17	; 23
      00985A 26                    7216 	.db #0x26	; 38
      00985B 39                    7217 	.db #0x39	; 57	'9'
      00985C 28                    7218 	.db #0x28	; 40
      00985D 05                    7219 	.db #0x05	; 5
      00985E 08                    7220 	.db #0x08	; 8
      00985F 0A                    7221 	.db #0x0a	; 10
      009860 05                    7222 	.db #0x05	; 5
      009861 36                    7223 	.db #0x36	; 54	'6'
      009862 08                    7224 	.db #0x08	; 8
      009863 0C                    7225 	.db #0x0c	; 12
      009864 08                    7226 	.db #0x08	; 8
      009865 0A                    7227 	.db #0x0a	; 10
      009866 2D                    7228 	.db #0x2d	; 45
      009867 26                    7229 	.db #0x26	; 38
      009868 02                    7230 	.db #0x02	; 2
      009869 26                    7231 	.db #0x26	; 38
      00986A 06                    7232 	.db #0x06	; 6
      00986B 02                    7233 	.db #0x02	; 2
      00986C 00                    7234 	.db #0x00	; 0
      00986D 00                    7235 	.db #0x00	; 0
      00986E 00                    7236 	.db #0x00	; 0
      00986F 00                    7237 	.db #0x00	; 0
      009870 00                    7238 	.db #0x00	; 0
      009871 00                    7239 	.db #0x00	; 0
      009872 00                    7240 	.db #0x00	; 0
      009873 17                    7241 	.db #0x17	; 23
      009874 36                    7242 	.db #0x36	; 54	'6'
      009875 38                    7243 	.db #0x38	; 56	'8'
      009876 28                    7244 	.db #0x28	; 40
      009877 05                    7245 	.db #0x05	; 5
      009878 28                    7246 	.db #0x28	; 40
      009879 2B                    7247 	.db #0x2b	; 43
      00987A 17                    7248 	.db #0x17	; 23
      00987B 05                    7249 	.db #0x05	; 5
      00987C 18                    7250 	.db #0x18	; 24
      00987D 2A                    7251 	.db #0x2a	; 42
      00987E 2C                    7252 	.db #0x2c	; 44
      00987F 3B                    7253 	.db #0x3b	; 59
      009880 18                    7254 	.db #0x18	; 24
      009881 18                    7255 	.db #0x18	; 24
      009882 02                    7256 	.db #0x02	; 2
      009883 26                    7257 	.db #0x26	; 38
      009884 08                    7258 	.db #0x08	; 8
      009885 14                    7259 	.db #0x14	; 20
      009886 00                    7260 	.db #0x00	; 0
      009887 00                    7261 	.db #0x00	; 0
      009888 00                    7262 	.db #0x00	; 0
      009889 00                    7263 	.db #0x00	; 0
      00988A 00                    7264 	.db #0x00	; 0
      00988B 00                    7265 	.db #0x00	; 0
      00988C 00                    7266 	.db #0x00	; 0
      00988D 00                    7267 	.db #0x00	; 0
      00988E 17                    7268 	.db #0x17	; 23
      00988F 36                    7269 	.db #0x36	; 54	'6'
      009890 38                    7270 	.db #0x38	; 56	'8'
      009891 05                    7271 	.db #0x05	; 5
      009892 38                    7272 	.db #0x38	; 56	'8'
      009893 2B                    7273 	.db #0x2b	; 43
      009894 26                    7274 	.db #0x26	; 38
      009895 18                    7275 	.db #0x18	; 24
      009896 18                    7276 	.db #0x18	; 24
      009897 30                    7277 	.db #0x30	; 48	'0'
      009898 30                    7278 	.db #0x30	; 48	'0'
      009899 3F                    7279 	.db #0x3f	; 63
      00989A 40                    7280 	.db #0x40	; 64
      00989B 18                    7281 	.db #0x18	; 24
      00989C 02                    7282 	.db #0x02	; 2
      00989D 06                    7283 	.db #0x06	; 6
      00989E 0A                    7284 	.db #0x0a	; 10
      00989F 00                    7285 	.db #0x00	; 0
      0098A0 00                    7286 	.db #0x00	; 0
      0098A1 00                    7287 	.db #0x00	; 0
      0098A2 00                    7288 	.db #0x00	; 0
      0098A3 00                    7289 	.db #0x00	; 0
      0098A4 00                    7290 	.db #0x00	; 0
      0098A5 00                    7291 	.db #0x00	; 0
      0098A6 00                    7292 	.db #0x00	; 0
      0098A7 00                    7293 	.db #0x00	; 0
      0098A8 00                    7294 	.db #0x00	; 0
      0098A9 17                    7295 	.db #0x17	; 23
      0098AA 36                    7296 	.db #0x36	; 54	'6'
      0098AB 05                    7297 	.db #0x05	; 5
      0098AC 05                    7298 	.db #0x05	; 5
      0098AD 28                    7299 	.db #0x28	; 40
      0098AE 28                    7300 	.db #0x28	; 40
      0098AF 17                    7301 	.db #0x17	; 23
      0098B0 36                    7302 	.db #0x36	; 54	'6'
      0098B1 29                    7303 	.db #0x29	; 41
      0098B2 09                    7304 	.db #0x09	; 9
      0098B3 09                    7305 	.db #0x09	; 9
      0098B4 09                    7306 	.db #0x09	; 9
      0098B5 06                    7307 	.db #0x06	; 6
      0098B6 17                    7308 	.db #0x17	; 23
      0098B7 2B                    7309 	.db #0x2b	; 43
      0098B8 39                    7310 	.db #0x39	; 57	'9'
      0098B9 00                    7311 	.db #0x00	; 0
      0098BA 00                    7312 	.db #0x00	; 0
      0098BB 00                    7313 	.db #0x00	; 0
      0098BC 00                    7314 	.db #0x00	; 0
      0098BD 00                    7315 	.db #0x00	; 0
      0098BE 00                    7316 	.db #0x00	; 0
      0098BF 00                    7317 	.db #0x00	; 0
      0098C0 00                    7318 	.db #0x00	; 0
      0098C1 00                    7319 	.db #0x00	; 0
      0098C2 00                    7320 	.db #0x00	; 0
      0098C3 00                    7321 	.db #0x00	; 0
      0098C4 17                    7322 	.db #0x17	; 23
      0098C5 36                    7323 	.db #0x36	; 54	'6'
      0098C6 05                    7324 	.db #0x05	; 5
      0098C7 05                    7325 	.db #0x05	; 5
      0098C8 28                    7326 	.db #0x28	; 40
      0098C9 38                    7327 	.db #0x38	; 56	'8'
      0098CA 15                    7328 	.db #0x15	; 21
      0098CB 15                    7329 	.db #0x15	; 21
      0098CC 17                    7330 	.db #0x17	; 23
      0098CD 17                    7331 	.db #0x17	; 23
      0098CE 17                    7332 	.db #0x17	; 23
      0098CF 08                    7333 	.db #0x08	; 8
      0098D0 3D                    7334 	.db #0x3d	; 61
      0098D1 12                    7335 	.db #0x12	; 18
      0098D2 08                    7336 	.db #0x08	; 8
      0098D3 00                    7337 	.db #0x00	; 0
      0098D4 00                    7338 	.db #0x00	; 0
      0098D5 00                    7339 	.db #0x00	; 0
      0098D6 00                    7340 	.db #0x00	; 0
      0098D7 00                    7341 	.db #0x00	; 0
      0098D8 00                    7342 	.db #0x00	; 0
      0098D9 00                    7343 	.db #0x00	; 0
      0098DA 00                    7344 	.db #0x00	; 0
      0098DB 00                    7345 	.db #0x00	; 0
      0098DC 00                    7346 	.db #0x00	; 0
      0098DD 00                    7347 	.db #0x00	; 0
      0098DE 00                    7348 	.db #0x00	; 0
      0098DF 03                    7349 	.db #0x03	; 3
      0098E0 05                    7350 	.db #0x05	; 5
      0098E1 05                    7351 	.db #0x05	; 5
      0098E2 05                    7352 	.db #0x05	; 5
      0098E3 36                    7353 	.db #0x36	; 54	'6'
      0098E4 36                    7354 	.db #0x36	; 54	'6'
      0098E5 26                    7355 	.db #0x26	; 38
      0098E6 39                    7356 	.db #0x39	; 57	'9'
      0098E7 08                    7357 	.db #0x08	; 8
      0098E8 0C                    7358 	.db #0x0c	; 12
      0098E9 2D                    7359 	.db #0x2d	; 45
      0098EA 12                    7360 	.db #0x12	; 18
      0098EB 3D                    7361 	.db #0x3d	; 61
      0098EC 36                    7362 	.db #0x36	; 54	'6'
      0098ED 00                    7363 	.db #0x00	; 0
      0098EE 00                    7364 	.db #0x00	; 0
      0098EF 00                    7365 	.db #0x00	; 0
      0098F0 00                    7366 	.db #0x00	; 0
      0098F1 00                    7367 	.db #0x00	; 0
      0098F2 00                    7368 	.db #0x00	; 0
      0098F3 00                    7369 	.db #0x00	; 0
      0098F4 00                    7370 	.db #0x00	; 0
      0098F5 00                    7371 	.db #0x00	; 0
      0098F6 00                    7372 	.db #0x00	; 0
      0098F7 00                    7373 	.db #0x00	; 0
      0098F8 00                    7374 	.db #0x00	; 0
      0098F9 00                    7375 	.db #0x00	; 0
      0098FA 00                    7376 	.db #0x00	; 0
      0098FB 03                    7377 	.db #0x03	; 3
      0098FC 05                    7378 	.db #0x05	; 5
      0098FD 05                    7379 	.db #0x05	; 5
      0098FE 26                    7380 	.db #0x26	; 38
      0098FF 26                    7381 	.db #0x26	; 38
      009900 28                    7382 	.db #0x28	; 40
      009901 0A                    7383 	.db #0x0a	; 10
      009902 0C                    7384 	.db #0x0c	; 12
      009903 3D                    7385 	.db #0x3d	; 61
      009904 0C                    7386 	.db #0x0c	; 12
      009905 26                    7387 	.db #0x26	; 38
      009906 00                    7388 	.db #0x00	; 0
      009907 00                    7389 	.db #0x00	; 0
      009908 00                    7390 	.db #0x00	; 0
      009909 00                    7391 	.db #0x00	; 0
      00990A 00                    7392 	.db #0x00	; 0
      00990B 00                    7393 	.db #0x00	; 0
      00990C 00                    7394 	.db #0x00	; 0
      00990D 00                    7395 	.db #0x00	; 0
      00990E 00                    7396 	.db #0x00	; 0
      00990F 00                    7397 	.db #0x00	; 0
      009910 00                    7398 	.db #0x00	; 0
      009911 00                    7399 	.db #0x00	; 0
      009912 00                    7400 	.db #0x00	; 0
      009913 00                    7401 	.db #0x00	; 0
      009914 00                    7402 	.db #0x00	; 0
      009915 00                    7403 	.db #0x00	; 0
      009916 00                    7404 	.db #0x00	; 0
      009917 15                    7405 	.db #0x15	; 21
      009918 03                    7406 	.db #0x03	; 3
      009919 06                    7407 	.db #0x06	; 6
      00991A 06                    7408 	.db #0x06	; 6
      00991B 06                    7409 	.db #0x06	; 6
      00991C 06                    7410 	.db #0x06	; 6
      00991D 06                    7411 	.db #0x06	; 6
      00991E 36                    7412 	.db #0x36	; 54	'6'
      00991F 00                    7413 	.db #0x00	; 0
      009920 00                    7414 	.db #0x00	; 0
                                   7415 	.area INITIALIZER
                                   7416 	.area CABS (ABS)
