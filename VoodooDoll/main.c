#include <stdint.h>
#include <stdio.h>

#include "stm8.h"

#define TSPAN	15
#define SINC	256
#define MORSEC	32
const uint16_t sin_tbl[] = {
266, 277, 287, 298, 310, 321, 333, 345, 357, 370, 382, 395, 408, 422, 435, 449, 463, 477, 491, 506, 520, 535, 550, 565, 580, 595, 610, 625, 640, 655, 670, 685, 700, 715, 729, 744, 758, 772, 786, 800, 813, 826, 839, 851, 863, 875, 886, 897, 907, 917, 926, 935, 943, 950, 957, 964, 969, 974, 979, 983, 986, 988, 990, 991, 991, 991, 990, 988, 986, 983, 979, 974, 969, 964, 957, 950, 943, 935, 926, 917, 907, 897, 886, 875, 863, 851, 839, 826, 813, 800, 786, 772, 758, 744, 729, 715, 700, 685, 670, 655, 640, 625, 610, 595, 580, 565, 550, 535, 520, 506, 491, 477, 463, 449, 435, 422, 408, 395, 382, 370, 357, 345, 333, 321, 310, 298, 287, 277, 266, 256, 246, 236, 227, 218, 209, 200, 191, 183, 175, 167, 160, 153, 146, 139, 132, 126, 119, 113, 108, 102, 97, 91, 86, 82, 77, 72, 68, 64, 60, 56, 52, 49, 45, 42, 39, 36, 33, 31, 28, 26, 23, 21, 19, 17, 15, 13, 12, 10, 9, 8, 6, 5, 4, 3, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 8, 9, 10, 12, 13, 15, 17, 19, 21, 23, 26, 28, 31, 33, 36, 39, 42, 45, 49, 52, 56, 60, 64, 68, 72, 77, 82, 86, 91, 97, 102, 108, 113, 119, 126, 132, 139, 146, 153, 160, 167, 175, 183, 191, 200, 209, 218, 227, 236, 246, 256,
//734, 723, 713, 702, 690, 679, 667, 655, 643, 630, 618, 605, 592, 578, 565, 551, 537, 523, 509, 494, 480, 465, 450, 435, 420, 405, 390, 375, 360, 345, 330, 315, 300, 285, 271, 256, 242, 228, 214, 200, 187, 174, 161, 149, 137, 125, 114, 103, 93, 83, 74, 65, 57, 50, 43, 36, 31, 26, 21, 17, 14, 12, 10, 9, 9, 9, 10, 12, 14, 17, 21, 26, 31, 36, 43, 50, 57, 65, 74, 83, 93, 103, 114, 125, 137, 149, 161, 174, 187, 200, 214, 228, 242, 256, 271, 285, 300, 315, 330, 345, 360, 375, 390, 405, 420, 435, 450, 465, 480, 494, 509, 523, 537, 551, 565, 578, 592, 605, 618, 630, 643, 655, 667, 679, 690, 702, 713, 723, 734, 744, 754, 764, 773, 782, 791, 800, 809, 817, 825, 833, 840, 847, 854, 861, 868, 874, 881, 887, 892, 898, 903, 909, 914, 918, 923, 928, 932, 936, 940, 944, 948, 951, 955, 958, 961, 964, 967, 969, 972, 974, 977, 979, 981, 983, 985, 987, 988, 990, 991, 992, 994, 995, 996, 997, 997, 998, 999, 999, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 999, 999, 998, 997, 997, 996, 995, 994, 992, 991, 990, 988, 987, 985, 983, 981, 979, 977, 974, 972, 969, 967, 964, 961, 958, 955, 951, 948, 944, 940, 936, 932, 928, 923, 918, 914, 909, 903, 898, 892, 887, 881, 874, 868, 861, 854, 847, 840, 833, 825, 817, 809, 800, 791, 782, 773, 764, 754, 744, 
//500,525,549,573,598,621,645,668,691,714,736,757,778,798,817,836,854,870,887,902,916,929,941,952,962,971,978,985,990,995,998,999,1000,999,998,995,990,985,978,971,962,952,941,929,916,902,887,870,854,836,817,798,778,757,736,714,691,668,645,621,598,573,549,525,500,475,451,427,402,379,355,332,309,286,264,243,222,202,183,164,146,130,113,98,84,71,59,48,38,29,22,15,10,5,2,1,0,1,2,5,10,15,22,29,38,48,59,71,84,98,113,130,146,164,183,202,222,243,264,286,309,332,355,379,402,427,451,475,500,

};

const uint16_t morse_tbl[] = {
	1000, 0, 1000, 0, 1000, 0, 0, 0,  //S
	1000, 0, 1000, 0, 1000, 1000, 1000, 0, 1000, 1000, 1000, 0, 1000, 1000, 1000, 0, 0, 0, // 2
	0, 0, 0, 0, 0, 0 //space
};

#define SENSE_PIN (1<<4)
#define LOAD_PIN ((1<<3) | (1<<4) | (1<<5))


unsigned int clock(void)
{
	unsigned char h = TIM1_CNTRH;
	unsigned char l = TIM1_CNTRL;
	return((unsigned int)(h) << 8 | l);
}

void init_clock(void) {
	CLK_CKDIVR = 0x03; // Set the frequency to 2 MHz
	CLK_PCKENR1 = 0xb8; // Enable Timers 1, 2, 4, usart 
	CLK_PCKENR2 = 0x73; //off
	//CLK_PCKENR1 = 0xFF; // Enable all peripherals
}

void init_tim1(void) {
	// Configure timer
	TIM1_PSCRH = 0x3e; // 1000 ticks per second 1Khz
	TIM1_PSCRL = 0x80;
	TIM1_CR1 = 0x01; // Enable timer
	

	//TIM1_CNTRH = 0; //reset counter
	//TIM1_CNTRL = 0;
}

// 16000000 / 128 ~ 125 Khz
// overflow ~ 2 ms
void init_tim4(void) {
	TIM4_PSCR = 0x07; //Prescaler 128
	TIM4_ARR = 0xff;
	TIM4_IER = 1; //Enable interrupt
	TIM4_SR1 &= ~1; //Reset interrupt
	TIM4_CR1 = 1; //Enable Timer4
}



void init_tim2(void) {
	TIM2_PSCR = 0x05; //Prescaler 32
	TIM2_ARRH = 0x03; //Autoreload 1000
	TIM2_ARRL = 0xe8;

	TIM2_CCER2 = 0x03; //Enable Channel 3 output | Compare low
	TIM2_CCMR3 = 0x60; // Compare mode PWM1 (changed from 0x78) 
	//TIM2_EGR |= 0x01;
	TIM2_CR1 = 0x81; //Enable timer2
}

void uart_init() {
    /* Configure RX and TX pins */
    //PD_DDR = 0xBF;
    //PD_CR1 = 0xFF;
    PD_DDR |= (1<<5); //PD5 output
	PD_CR1 |= (1<<5); //PD5 push-pull

    /* Enable TX */
    UART1_CR2 = UART_CR2_TEN;
    /* 1 stop bit */
    UART1_CR3 &= ~(UART_CR3_STOP1 | UART_CR3_STOP2);
    /* 9600 baud, 16MHz, Error:0.08%   */
    UART1_BRR2 = 0x03; 
    UART1_BRR1 = 0x68;
}

inline void port_init() {
    PA_DDR |= 0x4; // PA2
	PA_CR1 |= 0x4;
	PA_ODR &= ~0x4;

	PB_DDR |= 0xcf; //PB1, PB2, PB3, PB6, PB7
	PB_CR1 |= 0xcf;
	PB_ODR &= ~0xcf;

	PC_DDR |= 0x86; //PC1, PC2, PC7
	PC_CR1 |= 0x86;
	PC_ODR &= ~0x86;

	PD_DDR |= 0x95; //PD0, PD2, PD4, PD7
	PD_CR1 |= 0x95;
	PD_ODR &= ~0x95;

	PE_DDR |= 0x40; //PE5
	PE_CR1 |= 0x40;
	PE_ODR &= ~0x40;

	PF_DDR |= 0x80; //PF7
	PF_CR1 |= 0x80;
	PF_ODR &= ~0x80;

	/*PA_ODR = 0x00;
    PA_DDR = 0xFF;
    PA_CR1 = 0xFF;
    PA_CR2 = 0x00;

    PB_ODR = 0x00;
    PB_DDR = 0xFF;
    PB_CR1 = 0xFF;
    PB_CR2 = 0x00;

    PC_ODR = 0x00;
    PC_DDR = 0xFF;
    PC_CR1 = 0xFF;
    PC_CR2 = 0x00;

    PD_ODR = 0x00;
    PD_DDR = 0xFF;
    PD_CR1 = 0xFF;
    PD_CR2 = 0x00;*/
}

void tim2_pwm3(uint16_t val) {
	TIM2_CCR3H = val >> 8;
	TIM2_CCR3L = val & 0xff;

}

static uint16_t idx=0;
void tim4_isr(void) __interrupt(23)
{
	TIM4_SR1 &= ~1; //reset interrupt
	if (((++idx)%4)==0) {
		int val = sin_tbl[(idx/4)%SINC];
		//int val = morse_tbl[(idx/32)%MORSEC];
		TIM2_CCR3H = val >> 8; //update PWM value
		TIM2_CCR3L = val & 0xff;
	}
     
}

#define CAP_TIMEOUT	256 //should be muchlower now

long readCapTouch() {
	//long i;
	PC_ODR |= LOAD_PIN; //send high
	PB_ODR &= ~SENSE_PIN; //low
	PB_DDR |= SENSE_PIN; //output
	PB_CR1 |= SENSE_PIN; //push/pull
	//for (i=0; i<100; ++i)
	//	__asm__ ("nop"); 
	
	PB_CR1 &= ~SENSE_PIN; //float
	PB_DDR &= ~SENSE_PIN; //recv input

	/*//PB_ODR &= ~(1<<4); //send low
	//PC_DDR &= ~((1<<3) | (1<<4) | (1<<5)); //PC3,4,5 input
	PC_DDR |= (1<<3) | (1<<4) | (1<<5); //recv ouput
	PC_ODR &= ~(1<<4); //recv low
	PC_DDR &= ~((1<<3) | (1<<4) | (1<<5)); //PC3,4,5 input
	for (i=0; i<1000; ++i)
		__asm__ ("nop"); 
	PB_ODR |= (1<<4); //send high
	PB_CR1 |= (1<<4);*/

	long count=0;
	while ((PB_IDR & SENSE_PIN)==0) {
		count++;
		if (count > CAP_TIMEOUT){
			break;
		}
	}

	PB_ODR |= SENSE_PIN; //high
	PB_DDR |= SENSE_PIN; //output
	PB_CR1 |= SENSE_PIN; //push/pull
	PC_ODR &= ~LOAD_PIN; //send low
	
	//for (i=0; i<100; ++i)
	//	__asm__ ("nop"); 
	
	PB_CR1 &= ~SENSE_PIN; //float
	PB_DDR &= ~SENSE_PIN; //recv input

	/*//PC_ODR |= (1<<4); //recv high
	PC_DDR |= (1<<3) | (1<<4) | (1<<5); //recv ouput
	PC_ODR |= (1<<4); //recv high
	for (i=0; i<1000; ++i)
		__asm__ ("nop"); 
	PC_DDR &= ~((1<<3) | (1<<4) | (1<<5)); //PC3,4,5 input
	PB_ODR &= ~(1<<4); //send low
	PB_CR1 &= ~(1<<4);*/
	
	long count2=0;
	while ((PB_IDR & SENSE_PIN)) {
		count2++;
		if (count2 > CAP_TIMEOUT)
			break;
	}
	//printf("Measure %ld + %ld\r\n", count, count2);
	return count+count2;
}

long rawCapSample(int count) {
	long total = 0;
	for (int i=0; i< count; ++i) {
		long t = readCapTouch();
		total += t;
	}
	return total;
}


int putchar(int c)
{
	while(!(UART1_SR & UART_SR_TXE));

	UART1_DR = c;
	return c;
}

void main(void)
{
	unsigned long i = 0;
    unsigned long j = 0;

    //for(i = 0; i < 3; i++)
        for(j = 0; j< 147456; j++); // Sleep for reset

	init_clock();
	init_tim2();
	init_tim4();
	init_tim1();
	
	port_init();
	uart_init();

	
	// Set LED ports for output
	PA_DDR |= 0xA; //PA1 & PA3 output
	PA_CR1 |= 0xA; //PA1 & PA3 push-pull
	PA_ODR |= 0xA; //PA1 & PA3 lights off
	PD_DDR &= ~(1<<6); // input for PD6

	
	//load init low
	PC_ODR &= ~LOAD_PIN; //low
	PC_DDR |= LOAD_PIN; //output
	PC_CR1 |= LOAD_PIN; //push-pull

	PB_CR1 |= SENSE_PIN; //push-pull
	PB_ODR &= ~SENSE_PIN; //low
	PB_DDR |= SENSE_PIN; //output


	//PC_DDR &= ~((1<<3) | (1<<4) | (1<<5)); //PC3,4,5 input
	//PC_CR1 &= ~((1<<3) | (1<<4) | (1<<5)); //PC3,4,5 floating

	__asm__ ("rim"); //enable interrupts
	int touch=0;
	
	while(1) {
		int cnt = 0xff;
		//int at = (clock()/TSPAN)%SINC;
		//tim2_pwm3(sin_tbl[at]);
		long cap = rawCapSample(30);
		if (cap > 400)
			cnt = 0x10;
		else if (cap > 300)
			cnt = 0x80;
		else if (cap > 200)
			cnt = 0xC0;

		if (cap > 300) {
			if (!touch) {
				CLK_PCKENR1 &= ~0x10; //disables timer 4
				tim2_pwm3(0);
				touch = 1;
				puts("TOUCH");
			}
			if ((clock()%100) >= 50) { //(clock()%2). ((m%10) >4)
				PA_ODR |= 0x2; //PA1 high
			}
			else {
				PA_ODR &= ~0x2; //PA1 low
			}
		}
		else if (touch) {
			touch = 0;
			PA_ODR |= 0x2; //PA1 high (off)
			CLK_PCKENR1 |= 0x10; //re-enable timer 4
		}

		//printf("%x %ld\r\n", cnt, cap);
		//TIM4_ARR = cnt;
		//for(i = 0; i < 147456; i++); // Sleep
	}

}

