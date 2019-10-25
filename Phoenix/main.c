#include <stdint.h>
#include <stdio.h>

#include "stm8s.h"

#define TSPAN	15
#define SINC	256
const uint16_t sin_tbl[] = {
266, 277, 287, 298, 310, 321, 333, 345, 357, 370, 382, 395, 408, 422, 435, 449, 463, 477, 491, 506, 520, 535, 550, 565, 580, 595, 610, 625, 640, 655, 670, 685, 700, 715, 729, 744, 758, 772, 786, 800, 813, 826, 839, 851, 863, 875, 886, 897, 907, 917, 926, 935, 943, 950, 957, 964, 969, 974, 979, 983, 986, 988, 990, 991, 991, 991, 990, 988, 986, 983, 979, 974, 969, 964, 957, 950, 943, 935, 926, 917, 907, 897, 886, 875, 863, 851, 839, 826, 813, 800, 786, 772, 758, 744, 729, 715, 700, 685, 670, 655, 640, 625, 610, 595, 580, 565, 550, 535, 520, 506, 491, 477, 463, 449, 435, 422, 408, 395, 382, 370, 357, 345, 333, 321, 310, 298, 287, 277, 266, 256, 246, 236, 227, 218, 209, 200, 191, 183, 175, 167, 160, 153, 146, 139, 132, 126, 119, 113, 108, 102, 97, 91, 86, 82, 77, 72, 68, 64, 60, 56, 52, 49, 45, 42, 39, 36, 33, 31, 28, 26, 23, 21, 19, 17, 15, 13, 12, 10, 9, 8, 6, 5, 4, 3, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 8, 9, 10, 12, 13, 15, 17, 19, 21, 23, 26, 28, 31, 33, 36, 39, 42, 45, 49, 52, 56, 60, 64, 68, 72, 77, 82, 86, 91, 97, 102, 108, 113, 119, 126, 132, 139, 146, 153, 160, 167, 175, 183, 191, 200, 209, 218, 227, 236, 246, 256,
};


#define SENSE_PIN (1<<1)
#define LOAD_PIN (1<<6)
#define I2C_SLAVE_ADDR	0x41


typedef enum {
    Idle,
    Ready,
    SentType,
    SendingSize,
    SentSize,
    SendingMessage,
    SentMessage,
} i2cState;

i2cState _is = Idle;

uint8_t i2c_idx=0;
const char disp2[] = "http://bit.ly/Stage2SC";

void opt_write() {
    /* new value for OPT5 (default is 0x00) */
    uint8_t opt2 = 0x01;
    /* unlock EEPROM */
    FLASH_DUKR = FLASH_DUKR_KEY1;
    FLASH_DUKR = FLASH_DUKR_KEY2;
    while (!(FLASH_IAPSR & (1 << FLASH_IAPSR_DUL)));
    /* unlock option bytes */
    FLASH_CR2 |= (1 << FLASH_CR2_OPT);
    FLASH_NCR2 &= ~(1 << FLASH_NCR2_NOPT);
    /* write option byte and it's complement */
    OPT2 = opt2;
    NOPT2 = ~opt2;
    /* wait until programming is finished */
    while (!(FLASH_IAPSR & (1 << FLASH_IAPSR_EOP)));
    /* lock EEPROM */
    FLASH_IAPSR &= ~(1 << FLASH_IAPSR_DUL);
}

unsigned int clock(void)
{
	unsigned char h = TIM1_CNTRH;
	unsigned char l = TIM1_CNTRL;
	return((unsigned int)(h) << 8 | l);
}

void init_clock(void) {
	CLK_CKDIVR = 0x00; // Set the frequency to 2 MHz
	CLK_PCKENR1 = 0xb9; // Enable Timers 1, 2, 4, i2c
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

void init_tim2(void) {
	TIM2_PSCR = 0x05; //Prescaler 32
	TIM2_ARRH = 0x03; //Autoreload 1000
	TIM2_ARRL = 0xe8;

	TIM2_CCER1 = 0x03; //Enable Channel 1 output | Compare low
	TIM2_CCMR1 = 0x60; // Compare mode PWM1 (changed from 0x78)
	TIM2_EGR |= 0x01;
	TIM2_CR1 = 0x81; //Enable timer2
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
    UART1_CR3 &= ~(UART_CR3_STOP1 | UART_CR3_STOP0);
    /* 9600 baud, 16MHz, Error:0.08%   */
    UART1_BRR2 = 0x03;
    UART1_BRR1 = 0x68;
}

void tim2_pwm1(uint16_t val) {
	TIM2_CCR1H = val >> 8;
	TIM2_CCR1L = val & 0xff;

}

#define CAP_TIMEOUT	256 //should be muchlower now

long readCapTouch() {
	//long i;
	PD_ODR |= LOAD_PIN; //send high
	PD_ODR &= ~SENSE_PIN; //low
	PD_DDR |= SENSE_PIN; //output
	PD_CR1 |= SENSE_PIN; //push/pull
	//for (i=0; i<100; ++i)
	//	__asm__ ("nop"); 
	
	PD_CR1 &= ~SENSE_PIN; //float
	PD_DDR &= ~SENSE_PIN; //recv input

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
	while ((PD_IDR & SENSE_PIN)==0) {
		count++;
		if (count > CAP_TIMEOUT){
			break;
		}
	}

	PD_ODR |= SENSE_PIN; //high
	PD_DDR |= SENSE_PIN; //output
	PD_CR1 |= SENSE_PIN; //push/pull
	PD_ODR &= ~LOAD_PIN; //send low
	
	//for (i=0; i<100; ++i)
	//	__asm__ ("nop"); 
	
	PD_CR1 &= ~SENSE_PIN; //float
	PD_DDR &= ~SENSE_PIN; //recv input

	/*//PC_ODR |= (1<<4); //recv high
	PC_DDR |= (1<<3) | (1<<4) | (1<<5); //recv ouput
	PC_ODR |= (1<<4); //recv high
	for (i=0; i<1000; ++i)
		__asm__ ("nop"); 
	PC_DDR &= ~((1<<3) | (1<<4) | (1<<5)); //PC3,4,5 input
	PB_ODR &= ~(1<<4); //send low
	PB_CR1 &= ~(1<<4);*/
	
	long count2=0;
	while ((PD_IDR & SENSE_PIN)) {
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

/**
 * Initialize I2C at 100KHz standard mode.
 */
void i2c_init() {
    /* Disable I2C */
    I2C_CR1 &= ~I2C_CR1_PE;
    //I2C_CR1 |= I2C_CR1_ENGC;
    I2C_FREQR = 0x16;
    
    /* Configure I2C clock */
    I2C_CCRH = 0;
    I2C_CCRL = 0x50;
    I2C_TRISER = 17;

    /* Must always be written as 1 */
    I2C_OARH = I2C_OARH_ADDCONF;
    /* 7-bit slave address */
    I2C_OARL = (I2C_SLAVE_ADDR << 1) ;
    //I2C_OARH &= ~I2C_OARH_ADDMODE;

    /* Enable I2C interrupts */
    I2C_ITR |= (I2C_ITR_ITBUFEN|I2C_ITR_ITEVTEN|I2C_ITR_ITERREN);
    /* Configuration ready, re-enable I2C */
    
    I2C_CR1 |= I2C_CR1_PE;
    I2C_CR2 |= I2C_CR2_ACK;
    
}

void flipLed() {
    if ((clock()%100) >= 50) {
        //(clock()%2). ((m%10) >4)
        tim2_pwm1(999);
    } else {
        tim2_pwm1(0);
    }
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
    opt_write();
    init_tim2();
    init_tim1();
	
    //port_init();
    //uart_init();
    i2c_init();
	
    // Set LED ports for output
    PC_DDR |= 0x20; //PA1 & PA3 output
    PC_CR1 |= 0x20; //PA1 & PA3 push-pull
    PC_ODR &= ~0x20; //PA1 & PA3 lights off
    //PD_DDR &= ~(1<<6); // input for PD6

	
    //load init low
    PD_ODR &= ~LOAD_PIN; //low
    PD_DDR |= LOAD_PIN; //output
    PD_CR1 |= LOAD_PIN; //push-pull

    PD_CR1 |= SENSE_PIN; //push-pull
    PD_ODR &= ~SENSE_PIN; //low
    PD_DDR |= SENSE_PIN; //output
    
    __asm__ ("rim"); //enable interrupts
    int touch=0;
    
    while(1) {
        
        int at = (clock()/TSPAN)%SINC;
        
        long cap = rawCapSample(30);
        if (cap > 1000) {
            if (!touch) {
                //CLK_PCKENR1 &= ~0x10; //disables timer 4
                tim2_pwm1(0);
                touch = 1;
                if (_is == Idle)
                    _is = Ready;
            }
            if ((clock()%100) >= 50) {
                //(clock()%2). ((m%10) >4)
                tim2_pwm1(999);
            } else {
                tim2_pwm1(0);
            }
        } else if (touch) {
            touch = 0;
            PC_ODR |= 0x38; //PA1 high (off)
            //CLK_PCKENR1 |= 0x10; //re-enable timer 4
        }
        else
            tim2_pwm1(sin_tbl[at]);
    }

}


const uint8_t disp1[33] = {3, 0xFF, 0xFF, 0xFC, 0xF0, 0xC0, 0, 0, 0x7E, 0x50, 0x50, 0, 0x7E, 2, 2, 0, 0x7C, 2, 2, 0x7C, 0, 0x7E, 0x20, 0x10, 0x20, 0x7E, 0, 0, 0xC0, 0xF0, 0xFC, 0xFF};


/* I2C interrupt service routine for master transfer */

void i2c_isr(void) __interrupt(INT_I2C) {
    uint8_t r= I2C_SR1;
    if (r & I2C_SR1_ADDR) {
        /* Address matched, */
        switch(_is) {
            case Ready:
                break;
            default:
                break;
        }
        r = I2C_SR3;
    } else if (r & I2C_SR1_STOPF) {
        I2C_CR2 |= I2C_CR2_ACK;
    } else if (r & I2C_SR1_TXE) {
        /* Data reg empty, send more */
        /* Write byte to data register */
        switch(_is) {
            case Ready:
		if (i2c_idx == 0)
                	I2C_DR = 2;
		else if (i2c_idx == 1)
			I2C_DR = sizeof(disp2)-1;
		else if (i2c_idx < sizeof(disp2)+1)
			I2C_DR = disp2[i2c_idx-2];
		else
			I2C_DR = 0;
		i2c_idx++;
                break;
            case SentType:
            case SendingSize:
                I2C_DR = sizeof(disp2)-1;
                break;
            case SentSize:
            case SendingMessage:
                if (i2c_idx < sizeof(disp2)) {
                    I2C_DR = disp2[i2c_idx++];
                }
                else {
                    I2C_DR=0;
                }
                break;
            default:
                I2C_DR=0;
        }
    } else if (r & I2C_SR1_BTF) {
    } else if (r & I2C_SR1_RXNE) {
        /* Receive a byte */
        // we never actually use this....
        I2C_CR2 |= I2C_CR2_STOP;
        //_is = Ready;
        char rr = I2C_DR;
    } else if (I2C_SR2 & I2C_SR2_AF) {
        switch (_is) {
	case Ready:
		_is=SentType;
		break;
	case SentType:
		_is = SentSize;
		i2c_idx=0;
		break;
	case SentSize:
		_is = SendingMessage;
		break;
	case SendingMessage:
		_is = Idle;
		i2c_idx=0;
		break;
	}
         /* send complete; */
        I2C_SR2 &= ~I2C_SR2_AF;
    } else {
        I2C_SR2 = 0;
        /* handle any errors */
    }
}
