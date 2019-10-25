#include <stdint.h>
#include <stdio.h>

#include "stm8.h"
#include "st7735.h"
//#include "sprites.h"
#include "metroid.h"

const uint8_t * bricks[3] = {brick2_raw, brick3_raw, brick4_raw};
const uint8_t * samus[3] = {samus1_raw, samus2_raw, samus3_raw};
const int8_t wavey[6] = {-9, -16, -9, 1, 8, 1};
const int8_t bid[11] = {0,0,1,0,2,0,0,2,2,0,1};

#define DC_PIN 3
#define RST_PIN 6

void ST7735_Init();
void ST7735_Draw(int16_t x, int16_t y, const uint8_t *data, uint8_t w, uint8_t h);
void ST7735_Clear(uint16_t color);
void ST7735_Fill(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color);

#define T_COUNT(x) ((( F_CPU * x / 1000000UL )-5)/5)
#define HIGH_NIB(x) (((x) >> 4) & 0xf)
#define LOW_NIB(x) ((x) & 0xf)

static inline void delay_ms(uint16_t ms) {
    uint32_t i;
    for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
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

void main(void)
{

   delay_ms(1000);

   init_clock();
   ST7735_Init();

   __asm__ ("rim"); //enable interrupts
	
    ST7735_Clear(BLACK);
    uint32_t frame=0;
   while(1) {
       const uint16_t *sprite = samus[frame/2 % 3];
       if (frame%2)
           ST7735_Draw(64, 32, sprite, 26, 32);
       
       if ((frame%2)==0)
           for (int i=0; i< 11; ++i) {
               ST7735_Draw(i*16 - 3*(frame%5), 64, bricks[bid[(i+(frame/5))%11]], 16, 16);
               //ST7735_Draw(i*16 - 3*(frame%6), 64, brick2_raw, 16, 16);
           }
       //ST7735_Fill(92, 28, 68, 32, BLACK);
       for (int i=0; i< 3; ++i) {
           ST7735_Fill(92 + i*24 + 4*((frame-1) % 6), 44 + wavey[(frame-1)%6], 8, 8, BLACK);
       }
       for (int i=0; i< 3; ++i) {
           ST7735_Draw(92 + i*24 + 4*(frame % 6), 44 + wavey[frame%6], bullet_raw, 8, 8);
       }
       
       frame++;
       
       delay_ms(100);

   }

}

/*
 * SPI pinout:
 * SCK  -> PC5
 * MOSI -> PC6
 * no CS PIN
 */
void SPI_init() {
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

void SPI_transfer(uint8_t *data, size_t len) {
    for (size_t i=0; i< len; ++i) {
        SPI_write(data[i]);
    }
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

void ST7735_Write16(uint16_t value) {
    ST7735_Write(((value & 0xFF00) >> 0x08), DAT);
    ST7735_Write((value & 0x00FF), DAT);
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

void ST7735_Init() {
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
            ST7735_Write16(~color);
}

void ST7735_Draw(int16_t x, int16_t y, const uint8_t *data, uint8_t w, uint8_t h) {
    uint8_t xoff=0, yoff=0, wend=w, hend=h;
    if (x < 0)
        xoff = 0 - x;
    if ((x+w) > ST7735_TFTLENGTH)
        wend = ST7735_TFTLENGTH-x;
    if (y<0)
        yoff = 0 - y;
    if ((y+h) > ST7735_TFTWIDTH)
        hend = ST7735_TFTWIDTH-y;
    ST7735_SetAddrWindow(x+xoff,y+yoff,wend,hend);
    for (int j=yoff; j<hend/2; ++j)
        for (int i=xoff; i<wend; ++i) {
            uint16_t d = data[j*w + i];
            //ST7735_Write16(d);
            ST7735_Write16(~pallet[HIGH_NIB(d)]);
            ST7735_Write16(~pallet[LOW_NIB(d)]);
        }
}


void ST7735_Fill(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) {
    ST7735_SetAddrWindow(x, y, w, h);
    for (int i=0; i< w; ++i)
        for(int j=0; j< h; ++j)
            ST7735_Write16(~color);
}
