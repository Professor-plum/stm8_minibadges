#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "stm8.h"
#include "st7735.h"
#include "doom.h"

#define RGB(r, g, b) ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | ((b) >> 3))


#define DC_PIN 3
#define RST_PIN 6

void ST7735_Init(void);
void ST7735_Clear(uint16_t color);
void ST7735_SetAddrWindow(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
void ST7735_Write16(uint16_t value);

#define T_COUNT(x) ((( F_CPU * x / 2000000UL )-5)/5)
#define HIGH_NIB(x) (((x) >> 4) & 0xf)
#define LOW_NIB(x) ((x) & 0xf)


static inline void delay_ms(uint16_t ms) {
    uint32_t i;
    for (i = 0; i < ((F_CPU / 1000UL) * ms); i++)
        __asm__("nop");
}

unsigned int clock(void)
{
	unsigned char h = TIM1_CNTRH;
	unsigned char l = TIM1_CNTRL;
	return((unsigned int)(h) << 8 | l);
}

void init_clock(void) {
    CLK_CKDIVR = 0;//0x18; // Set the frequency to 2 MHz
	CLK_PCKENR1 = 0x02; //SPI
	CLK_PCKENR2 = 0x73; //off
	//CLK_PCKENR1 = 0xFF; // Enable all peripherals
}

void drawFace(const uint8_t *face) { //face is a pointer to a 26x30 array of index pixels
   
    ST7735_SetAddrWindow(41, 2, 78, 80);

    for (int y=0; y<80; ++y) {

        for (int i=0; i<26; ++i) {
            int idx = face[(3+(y/3))*26+i];
            uint16_t c = pallet[idx];
            ST7735_Write16(c);
            ST7735_Write16(c);
            ST7735_Write16(c);
        }

    }
}

void main(void)
{   
   const uint8_t* frames[7] = {doom1_raw, doom3_raw, doom4_raw, doom5_raw, doom6_raw, doom7_raw, doom8_raw};

   init_clock();
   delay_ms(3000);
   ST7735_Init();

   __asm__ ("rim"); //enable interrupts


    ST7735_Clear(RGB(0,0,0));
       
   while(1) {
       
       drawFace(doom2_raw);
       delay_ms(2000); //000 + (rand() % 2000));
       drawFace(frames[rand()%7]);
       delay_ms(750);
   }

}

/*
 * SPI pinout:
 * SCK  -> PC5
 * MOSI -> PC6
 * no CS PIN
 */
void SPI_init(void) {
    // SPI port setup: MISO is pullup in, MOSI & SCK are push-pull out
    PC_DDR |= (1<<5) | (1<<6); // clock and MOSI
    PC_CR1 |= (1<<5) | (1<<6) | (1<<7);
   /* Initialize CS pin */
    
    /* Initialize SPI master at 500kHz  */
    SPI_CR2 = SPI_CR2_SSM | SPI_CR2_SSI;
    SPI_CR1 = SPI_CR1_MSTR;// | SPI_CR1_BR(3);
    SPI_CR1 |= SPI_CR1_SPE;
}

void SPI_write(uint8_t data) {
    SPI_DR = data;
    while (!(SPI_SR & SPI_SR_TXE));
}


#define CMD 0
#define DAT 1

void ST7735_Write(uint8_t val, uint8_t cmd) {
   if (cmd==CMD)
     PA_ODR &= ~(1 << DC_PIN);
   else
     PA_ODR |= (1 << DC_PIN);
   SPI_write(val);

   //while ((SPI_SR & SPI_SR_BSY));
   PA_ODR |= (1 << DC_PIN);
}

inline void ST7735_WriteData(uint8_t val) {
   PA_ODR |= (1 << DC_PIN);
   SPI_write(val);

   //while ((SPI_SR & SPI_SR_BSY));
   PA_ODR |= (1 << DC_PIN);
}

void ST7735_Write16(uint16_t value) {
    ST7735_WriteData(((value & 0xFF00) >> 0x08));
    ST7735_WriteData((value & 0x00FF));
}

void ST7735_SetAddrWindow(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    y += 0x18;
    w += x -1;
    h += y -1;
    ST7735_Write(ST7735_CASET, CMD);
    ST7735_Write(0x00, DAT);
    ST7735_Write(x, DAT);
    ST7735_Write(0x00, DAT);
    ST7735_Write(w, DAT);
    ST7735_Write(ST7735_RASET, CMD);
    ST7735_Write(0x00, DAT);
    ST7735_Write(y, DAT);
    ST7735_Write(0x00, DAT);
    ST7735_Write(h, DAT);
    ST7735_Write(ST7735_RAMWR, CMD);
}

void ST7735_Init(void) {
    /* DC init */
    PA_DDR |= (1 << DC_PIN);
    PA_CR1 |= (1 << DC_PIN);
    PA_ODR |= (1 << DC_PIN);
    
    PD_DDR |= (1 << RST_PIN);
    PD_CR1 |= (1 << RST_PIN);
    PD_ODR &= ~(1 << RST_PIN);

    SPI_init();
    delay_ms(100);

    PD_ODR |= (1 << RST_PIN);
    delay_ms(100);
    
    ST7735_Write(ST7735_SWRESET, CMD);
    delay_ms(150);
    ST7735_Write(ST7735_SLPOUT, CMD);
    delay_ms(500);
    ST7735_Write(ST7735_FRMCTR1, CMD);
    ST7735_Write(0x01, DAT);
    ST7735_Write(0x2C, DAT);
    ST7735_Write(0x2D, DAT);
    ST7735_Write(ST7735_FRMCTR2, CMD);
    ST7735_Write(0x01, DAT);
    ST7735_Write(0x2C, DAT);
    ST7735_Write(0x2D, DAT);
    ST7735_Write(ST7735_FRMCTR3, CMD);
    ST7735_Write(0x01, DAT);
    ST7735_Write(0x2C, DAT);
    ST7735_Write(0x2D, DAT);
    ST7735_Write(0x01, DAT);
    ST7735_Write(0x2C, DAT);
    ST7735_Write(0x2D, DAT);
    ST7735_Write(ST7735_INVCTR, CMD);
    ST7735_Write(0x07, DAT);
    ST7735_Write(ST7735_PWCTR1, CMD);
    ST7735_Write(0xA2, DAT);
    ST7735_Write(0x02, DAT);
    ST7735_Write(0x84, DAT);
    ST7735_Write(ST7735_PWCTR2, CMD);
    ST7735_Write(0xC5, DAT);
    ST7735_Write(ST7735_PWCTR3, CMD);
    ST7735_Write(0x0A, DAT);
    ST7735_Write(0x00, DAT);
    ST7735_Write(ST7735_PWCTR4, CMD);
    ST7735_Write(0x8A, DAT);
    ST7735_Write(0x2A, DAT);
    ST7735_Write(ST7735_PWCTR5, CMD);
    ST7735_Write(0x8A, DAT);
    ST7735_Write(0xEE, DAT);
    ST7735_Write(ST7735_VMCTR1, CMD);
    ST7735_Write(0x0E, DAT);
    ST7735_Write(ST7735_INVOFF, CMD);
    ST7735_Write(ST7735_MADCTL, CMD);
    ST7735_Write(0xC8, DAT);
    ST7735_Write(ST7735_COLMOD, CMD);
    ST7735_Write(0x05, DAT);
    

    //ST7735_RAM_Address_Set();
    ST7735_Write(ST7735_CASET, CMD);
    ST7735_Write(0x00, DAT);
    ST7735_Write(0x00, DAT);
    ST7735_Write(0x00, DAT);
    ST7735_Write(0x4F, DAT);
    ST7735_Write(ST7735_RASET, CMD);
    ST7735_Write(0x00, DAT);
    ST7735_Write(0x00, DAT);
    ST7735_Write(0x00, DAT);
    ST7735_Write(0x9F, DAT);
    


    ST7735_Write(ST7735_GMCTRP1, CMD);
    ST7735_Write(0x02, DAT);
    ST7735_Write(0x1C, DAT);
    ST7735_Write(0x07, DAT);
    ST7735_Write(0x12, DAT);
    ST7735_Write(0x37, DAT);
    ST7735_Write(0x32, DAT);
    ST7735_Write(0x29, DAT);
    ST7735_Write(0x2D, DAT);
    ST7735_Write(0x29, DAT);
    ST7735_Write(0x25, DAT);
    ST7735_Write(0x2B, DAT);
    ST7735_Write(0x39, DAT);
    ST7735_Write(0x00, DAT);
    ST7735_Write(0x01, DAT);
    ST7735_Write(0x03, DAT);
    ST7735_Write(0x10, DAT);
    ST7735_Write(ST7735_GMCTRN1, CMD);
    ST7735_Write(0x03, DAT);
    ST7735_Write(0x1D, DAT);
    ST7735_Write(0x07, DAT);
    ST7735_Write(0x06, DAT);
    ST7735_Write(0x2E, DAT);
    ST7735_Write(0x2C, DAT);
    ST7735_Write(0x29, DAT);
    ST7735_Write(0x2D, DAT);
    ST7735_Write(0x2E, DAT);
    ST7735_Write(0x2E, DAT);
    ST7735_Write(0x37, DAT);
    ST7735_Write(0x3F, DAT);
    ST7735_Write(0x00, DAT);
    ST7735_Write(0x00, DAT);
    ST7735_Write(0x02, DAT);
    ST7735_Write(0x10, DAT);
    ST7735_Write(ST7735_NORON, CMD);
    delay_ms(10);
    ST7735_Write(ST7735_DISPON, CMD);
    delay_ms(100);
    
    ST7735_Write(ST7735_MADCTL, CMD);
    ST7735_Write(MADCTL_MX | MADCTL_MV | MADCTL_RGB, DAT);
    delay_ms(10);
}


void ST7735_Clear(uint16_t color) {
    ST7735_SetAddrWindow(0,0,ST7735_TFTLENGTH+3,ST7735_TFTWIDTH+3);
    for (int i=0; i< ST7735_TFTWIDTH+3; ++i)
        for(int j=0; j< ST7735_TFTLENGTH+3; ++j)
            ST7735_Write16(color);
}


