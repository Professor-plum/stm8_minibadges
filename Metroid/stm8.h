#define F_CPU 2000000UL

#define PA_ODR  		*(volatile unsigned char *)0x5000
#define PA_IDR  		*(volatile unsigned char *)0x5001
#define PA_DDR 			*(volatile unsigned char *)0x5002
#define PA_CR1			*(volatile unsigned char *)0x5003
#define PA_CR2  		*(volatile unsigned char *)0x5004

#define PB_ODR  		*(volatile unsigned char *)0x5005
#define PB_IDR  		*(volatile unsigned char *)0x5006
#define PB_DDR  		*(volatile unsigned char *)0x5007
#define PB_CR1  		*(volatile unsigned char *)0x5008
#define PB_CR2  		*(volatile unsigned char *)0x5009

#define PC_ODR  		*(volatile unsigned char *)0x500a
#define PC_IDR  		*(volatile unsigned char *)0x500b
#define PC_DDR  		*(volatile unsigned char *)0x500c
#define PC_CR1  		*(volatile unsigned char *)0x500d
#define PC_CR2  		*(volatile unsigned char *)0x500e

#define PD_ODR  		*(volatile unsigned char *)0x500f
#define PD_IDR  		*(volatile unsigned char *)0x5010
#define PD_DDR  		*(volatile unsigned char *)0x5011
#define PD_CR1  		*(volatile unsigned char *)0x5012
#define PD_CR2  		*(volatile unsigned char *)0x5013

#define PE_ODR  		*(volatile unsigned char *)0x5014
#define PE_IDR  		*(volatile unsigned char *)0x5015
#define PE_DDR  		*(volatile unsigned char *)0x5016
#define PE_CR1  		*(volatile unsigned char *)0x5017
#define PE_CR2  		*(volatile unsigned char *)0x5018

#define PF_ODR  		*(volatile unsigned char *)0x5019
#define PF_IDR  		*(volatile unsigned char *)0x501a
#define PF_DDR  		*(volatile unsigned char *)0x501b
#define PF_CR1  		*(volatile unsigned char *)0x501c
#define PF_CR2  		*(volatile unsigned char *)0x501d

#define CLK_ICKR		*(volatile unsigned char *)0x50C0
#define CLK_ECKR		*(volatile unsigned char *)0x50C1
#define CLK_CMSR		*(volatile unsigned char *)0x50C3
#define CLK_SWR 		*(volatile unsigned char *)0x50C4
#define CLK_SWCR		*(volatile unsigned char *)0x50C5
#define CLK_CKDIVR		*(volatile unsigned char *)0x50C6
#define CLK_PCKENR1		*(volatile unsigned char *)0x50C7
#define CLK_CSSR		*(volatile unsigned char *)0x50C8
#define CLK_CCOR		*(volatile unsigned char *)0x50C9
#define CLK_PCKENR2		*(volatile unsigned char *)0x50CA
#define CLK_HSITRIMR	*(volatile unsigned char *)0x50CC
#define CLK_SWIMCCR		*(volatile unsigned char *)0x50CD


#define UART1_SR 		*(volatile unsigned char *)0x5230
#define UART1_DR 		*(volatile unsigned char *)0x5231
#define UART1_BRR1 		*(volatile unsigned char *)0x5232
#define UART1_BRR2 		*(volatile unsigned char *)0x5233
#define UART1_CR1 		*(volatile unsigned char *)0x5234
#define UART1_CR2 		*(volatile unsigned char *)0x5235
#define UART1_CR3 		*(volatile unsigned char *)0x5236
#define UART1_CR4 		*(volatile unsigned char *)0x5237
#define UART1_CR5 		*(volatile unsigned char *)0x5238
#define UART1_GTR 		*(volatile unsigned char *)0x5239
#define UART1_PSCR 		*(volatile unsigned char *)0x523A

#define UART_SR_TXE 	(1 << 7)
#define UART_SR_TC 		(1 << 6)
#define UART_SR_RXNE 	(1 << 5)
#define UART_SR_IDLE 	(1 << 4)
#define UART_SR_OR 		(1 << 3)
#define UART_SR_NF 		(1 << 2)
#define UART_SR_FE 		(1 << 1)
#define UART_SR_PE 		(1 << 0)

#define UART_CR2_TIEN 	(1 << 7)
#define UART_CR2_TCIEN 	(1 << 6)
#define UART_CR2_RIEN 	(1 << 5)
#define UART_CR2_ILIEN 	(1 << 4)
#define UART_CR2_TEN 	(1 << 3)
#define UART_CR2_REN 	(1 << 2)
#define UART_CR2_RWU 	(1 << 1)
#define UART_CR2_SBK 	(1 << 0)

#define UART_CR2_TIEN 	(1 << 7)
#define UART_CR2_TCIEN 	(1 << 6)
#define UART_CR2_RIEN 	(1 << 5)
#define UART_CR2_ILIEN 	(1 << 4)
#define UART_CR2_TEN 	(1 << 3)
#define UART_CR2_REN 	(1 << 2)
#define UART_CR2_RWU 	(1 << 1)
#define UART_CR2_SBK 	(1 << 0)

#define UART_CR3_LINEN 	(1 << 6)
#define UART_CR3_STOP2 	(1 << 5)
#define UART_CR3_STOP1 	(1 << 4)
#define UART_CR3_CLKEN 	(1 << 3)
#define UART_CR3_CPOL 	(1 << 2)
#define UART_CR3_CPHA 	(1 << 1)
#define UART_CR3_LBCL 	(1 << 0)

#define TIM1_CR1 		*(volatile unsigned char *)0x5250
#define TIM1_CR2 		*(volatile unsigned char *)0x5251
#define TIM1_SMCR 		*(volatile unsigned char *)0x5252
#define TIM1_ETR 		*(volatile unsigned char *)0x5253
#define TIM1_IER 		*(volatile unsigned char *)0x5254
#define TIM1_SR1 		*(volatile unsigned char *)0x5255
#define TIM1_SR2 		*(volatile unsigned char *)0x5256
#define TIM1_EGR 		*(volatile unsigned char *)0x5257
#define TIM1_CCMR1 		*(volatile unsigned char *)0x5258
#define TIM1_CCMR2 		*(volatile unsigned char *)0x5259
#define TIM1_CCMR3 		*(volatile unsigned char *)0x525A
#define TIM1_CCMR4 		*(volatile unsigned char *)0x525B
#define TIM1_CCER1 		*(volatile unsigned char *)0x525C
#define TIM1_CCER2 		*(volatile unsigned char *)0x525D
#define TIM1_CNTRH 		*(volatile unsigned char *)0x525E
#define TIM1_CNTRL 		*(volatile unsigned char *)0x525F
#define TIM1_PSCRH 		*(volatile unsigned char *)0x5260
#define TIM1_PSCRL 		*(volatile unsigned char *)0x5261
#define TIM1_ARRH 		*(volatile unsigned char *)0x5262
#define TIM1_ARRL 		*(volatile unsigned char *)0x5263
#define TIM1_RCR 		*(volatile unsigned char *)0x5264
#define TIM1_CCR1H 		*(volatile unsigned char *)0x5265
#define TIM1_CCR1L 		*(volatile unsigned char *)0x5266
#define TIM1_CCR2H 		*(volatile unsigned char *)0x5267
#define TIM1_CCR2L 		*(volatile unsigned char *)0x5268
#define TIM1_CCR3H 		*(volatile unsigned char *)0x5269
#define TIM1_CCR3L 		*(volatile unsigned char *)0x526A
#define TIM1_CCR4H 		*(volatile unsigned char *)0x526B
#define TIM1_CCR4L 		*(volatile unsigned char *)0x526C
#define TIM1_BKR 		*(volatile unsigned char *)0x526D
#define TIM1_DTR 		*(volatile unsigned char *)0x526E
#define TIM1_OISR 		*(volatile unsigned char *)0x526F

#define TIM2_CR1 		*(volatile unsigned char *)0x5300
#define TIM2_CR2 		*(volatile unsigned char *)0x5301
#define TIM2_SMCR 		*(volatile unsigned char *)0x5302
#define TIM2_IER 		*(volatile unsigned char *)0x5303
#define TIM2_SR1 		*(volatile unsigned char *)0x5304
#define TIM2_SR2 		*(volatile unsigned char *)0x5305
#define TIM2_EGR 		*(volatile unsigned char *)0x5306
#define TIM2_CCMR1 		*(volatile unsigned char *)0x5307
#define TIM2_CCMR2 		*(volatile unsigned char *)0x5308
#define TIM2_CCMR3 		*(volatile unsigned char *)0x5309
#define TIM2_CCER1 		*(volatile unsigned char *)0x530A
#define TIM2_CCER2 		*(volatile unsigned char *)0x530B
#define TIM2_CNTRH 		*(volatile unsigned char *)0x530C
#define TIM2_CNTRL 		*(volatile unsigned char *)0x530D
#define TIM2_PSCR 		*(volatile unsigned char *)0x530E
#define TIM2_ARRH 		*(volatile unsigned char *)0x530F
#define TIM2_ARRL 		*(volatile unsigned char *)0x5310
#define TIM2_CCR1H 		*(volatile unsigned char *)0x5311
#define TIM2_CCR1L 		*(volatile unsigned char *)0x5312
#define TIM2_CCR2H 		*(volatile unsigned char *)0x5313
#define TIM2_CCR2L 		*(volatile unsigned char *)0x5314
#define TIM2_CCR3H 		*(volatile unsigned char *)0x5315
#define TIM2_CCR3L 		*(volatile unsigned char *)0x5316

#define TIM4_CR1 		*(volatile unsigned char *)0x5340
#define TIM4_CR2 		*(volatile unsigned char *)0x5341
#define TIM4_SMCR 		*(volatile unsigned char *)0x5342
#define TIM4_IER 		*(volatile unsigned char *)0x5343
#define TIM4_SR1 		*(volatile unsigned char *)0x5344
#define TIM4_EGR 		*(volatile unsigned char *)0x5345
#define TIM4_CNTR 		*(volatile unsigned char *)0x5346
#define TIM4_PSCR 		*(volatile unsigned char *)0x5347
#define TIM4_ARR 		*(volatile unsigned char *)0x5348

/* SPI */
#define SPI_CR1 *(volatile unsigned char *)0x5200
#define SPI_CR2 *(volatile unsigned char *)0x5201
#define SPI_ICR *(volatile unsigned char *)0x5202
#define SPI_SR *(volatile unsigned char *)0x5203
#define SPI_DR *(volatile unsigned char *)0x5204
#define SPI_CRCPR *(volatile unsigned char *)0x5205
#define SPI_RXCRCR *(volatile unsigned char *)0x5206
#define SPI_TXCRCR *(volatile unsigned char *)0x5207

#define SPI_CR1_LSBFIRST (1 << 7)
#define SPI_CR1_SPE (1 << 6)
#define SPI_CR1_BR(br) ((br) << 3)
#define SPI_CR1_MSTR (1 << 2)
#define SPI_CR1_CPOL (1 << 1)
#define SPI_CR1_CPHA (1 << 0)

#define SPI_CR2_BDM (1 << 7)
#define SPI_CR2_BDOE (1 << 6)
#define SPI_CR2_CRCEN (1 << 5)
#define SPI_CR2_CRCNEXT (1 << 4)
#define SPI_CR2_RXONLY (1 << 2)
#define SPI_CR2_SSM (1 << 1)
#define SPI_CR2_SSI (1 << 0)

#define SPI_ICR_TXIE (1 << 7)
#define SPI_ICR_RXIE (1 << 6)
#define SPI_ICR_ERRIE (1 << 5)
#define SPI_ICR_WKIE (1 << 4)

#define SPI_SR_BSY (1 << 7)
#define SPI_SR_OVR (1 << 6)
#define SPI_SR_MODF (1 << 5)
#define SPI_SR_CRCERR (1 << 4)
#define SPI_SR_WKUP (1 << 3)
#define SPI_SR_TXE (1 << 1)
#define SPI_SR_RxNE (1 << 0)

/* I2C */
#define I2C_CR1 *(volatile unsigned char *)0x5210
#define I2C_CR2 *(volatile unsigned char *)0x5211
#define I2C_FREQR *(volatile unsigned char *)0x5212
#define I2C_OARL *(volatile unsigned char *)0x5213
#define I2C_OARH *(volatile unsigned char *)0x5214
#define I2C_DR *(volatile unsigned char *)0x5216
#define I2C_SR1 *(volatile unsigned char *)0x5217
#define I2C_SR2 *(volatile unsigned char *)0x5218
#define I2C_SR3 *(volatile unsigned char *)0x5219
#define I2C_ITR *(volatile unsigned char *)0x521A
#define I2C_CCRL *(volatile unsigned char *)0x521B
#define I2C_CCRH *(volatile unsigned char *)0x521C
#define I2C_TRISER *(volatile unsigned char *)0x521D
#define I2C_PECR *(volatile unsigned char *)0x521E
