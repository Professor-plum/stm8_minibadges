#include <stdint.h>
#include <stdio.h>

#include "stm8.h"
#include "st7735.h"
#include "pitfall.h"

#define RGB(r, g, b) ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | ((b) >> 3))


#define DC_PIN 3
#define RST_PIN 6

void ST7735_Init();
void ST7735_Draw(int16_t x, int16_t y, const uint8_t *data, uint8_t w, uint8_t h);
void ST7735_Clear(uint16_t color);
void ST7735_Fill(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color);
void ST7735_SetAddrWindow(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
void ST7735_Write16(uint16_t value);
void ST7735_DrawPixel(int16_t x, int16_t y, uint16_t color);
void ST7735_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

#define T_COUNT(x) ((( F_CPU * x / 1000000UL )-5)/5)
#define HIGH_NIB(x) (((x) >> 4) & 0xf)
#define LOW_NIB(x) ((x) & 0xf)

const uint8_t pool[16] = {0,0,0,16,64,96,112,128,128,112,96,64,16,0,0,0};


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

void drawscene(void) {
   
    ST7735_SetAddrWindow(0, 0, 160, 80);
    for (int i=0; i<480; ++i)
        ST7735_Write16(RGB(17,72,0));


    for (int j=0; j<2; ++j) {
        for (int i=0; i<48; ++i)
            ST7735_Write16(RGB(17,72,0));
        for (int i=0; i<16;++i)
            ST7735_Write16(RGB(95,144,47));
        for (int i=0; i<32; ++i)
            ST7735_Write16(RGB(17,72,0));
        for (int i=0; i<16;++i)
            ST7735_Write16(RGB(95,144,47));
        for (int i=0; i<48; ++i)
            ST7735_Write16(RGB(17,72,0));
    }
    for (int j=0; j<2; ++j) {
        for (int i=0; i<32; ++i)
            ST7735_Write16(RGB(17,72,0));
        for (int i=0; i<40;++i)
            ST7735_Write16(RGB(95,144,47));
        for (int i=0; i<16; ++i)
            ST7735_Write16(RGB(17,72,0));
        for (int i=0; i<40;++i)
            ST7735_Write16(RGB(95,144,47));
        for (int i=0; i<32; ++i)
            ST7735_Write16(RGB(17,72,0));
    }

    for (int j=0; j<2; ++j){
        for (int i=0; i<8; ++i)
            ST7735_Write16(RGB(17,72,0));
        for (int i=0; i<16; ++i)
            ST7735_Write16(RGB(17,72,0));
        for (int i=0; i<2;++i)
            ST7735_Write16(RGB(8,27,0));
        for (int i=0; i<2;++i)
            ST7735_Write16(j?RGB(95,144,47):RGB(8,27,0));
        for (int i=0; i<104;++i)
            ST7735_Write16(RGB(95,144,47));
        for (int i=0; i<2;++i)
            ST7735_Write16(j?RGB(95,144,47):RGB(8,27,0));
        for (int i=0; i<2;++i)
            ST7735_Write16(RGB(8,27,0));
        for (int i=0; i<16; ++i)
            ST7735_Write16(RGB(17,72,0));
        for (int i=0; i<8; ++i)
            ST7735_Write16(RGB(17,72,0));
        }

    for (int j=0; j<52; ++j) {
        for (int i=0; i<16;++i)
            ST7735_Write16(RGB(95,144,47));
        for (int i=0; i<8;++i)
            ST7735_Write16(RGB(8,27,0));
        for (int i=0; i<112;++i)
            ST7735_Write16(RGB(95,144,47));
        for (int i=0; i<8;++i)
            ST7735_Write16(RGB(8,27,0));
        for (int i=0; i<16;++i)
            ST7735_Write16(RGB(95,144,47));
    } 

    for (int j=0; j<16; ++j) {
        uint8_t r = pool[j];
        uint8_t t = 80-r/2;
        for (int i=0; i<t; ++i)
            ST7735_Write16(RGB(159,174,29));
        for (int i=0; i<r; ++i)
            ST7735_Write16(RGB(27,98,139));
        for (int i=0; i<t; ++i)
            ST7735_Write16(RGB(159,174,29));
    }
    for (int j=0; j<3; ++j) 
        for (int i=0; i<160; ++i)
            ST7735_Write16(RGB(88,104,0)); 
}

void drawHarry(int x, int y) {
    for (int j=0; j<15; ++j)
        for (int i=0; i<8; ++i) 
        {
            uint8_t d = harry_raw[j*8 + i];
            uint8_t b1 = HIGH_NIB(d);
            uint8_t b2 = LOW_NIB(d);
            if (b1 != 2)
                ST7735_DrawPixel(x+i*2,y+j, pallet[b1]);
            //if (b2 != 2)
            //    ST7735_DrawPixel(x+i*2+1,y+j, pallet[b2]);
        }
}

void clearHarry(int x, int y) {
    for (int j=0; j<15; ++j)
        for (int i=0; i<8; ++i) 
        {
            uint8_t d = harry_raw[j*8 + i];
            uint8_t b1 = HIGH_NIB(d);
            uint8_t b2 = LOW_NIB(d);
            uint16_t c = RGB(95,144,47);
            if (b1 != 2) {
                uint8_t cx = (x+2*i);
                if ((cx<23) || (cx>135))
                    c = RGB(8,27,0);
                ST7735_DrawPixel(cx,y+j, c);
            }
            /*if (b2 != 2) {
                uint8_t cx = (x+2*i+1);
                if ((cx<24) || (cx>135))
                    c = RGB(8,27,0);
                ST7735_DrawPixel(cx,y+j, c);
            }*/
        }
}

void drawGator(int x, int y, int id) {
    for (int j=0; j<8; ++j)
        for (int i=0; i<8; ++i) 
        {
            uint8_t d = id?gator1_raw[j*8 + i]:gator2_raw[j*8 + i];
            uint8_t b1 = HIGH_NIB(d);
            uint8_t b2 = LOW_NIB(d);
            if (b1 != 2)
                ST7735_DrawPixel(x+i*2,y+j, pallet[b1]);
            //if (b2 != 2)
            //    ST7735_DrawPixel(x+i*2+1,y+j, pallet[b2]);
        }
}

void main(void)
{
    const uint8_t sine[48] = {
        0x37,0x3e,0x45,0x4b,0x52,0x58,0x5d,0x62,0x66,0x69,0x6b,0x6d,0x6d,0x6d,0x6b,0x69,
        0x66,0x62,0x5d,0x58,0x52,0x4b,0x45,0x3e,0x37,0x2f,0x28,0x22,0x1b,0x15,0x10,0xb,
        0x7,0x4,0x2,0x0,0x0,0x0,0x2,0x4,0x7,0xb,0x10,0x15,0x1b,0x22,0x28,0x2f,
    };
    const uint8_t cos[48] = {
       13, 13, 13, 12, 11, 10, 9, 8, 6, 5, 3, 1, 0, 2, 3, 5, 7, 8, 9, 11, 12, 12, 13, 13,
       13, 13, 13, 12, 12, 11, 9, 8, 7, 5, 3, 2, 0, 1, 3, 5, 6, 8, 9, 10, 11, 12, 13, 13
    };
    
   delay_ms(3000);

   init_clock();
   ST7735_Init();

   __asm__ ("rim"); //enable interrupts


    //ST7735_Clear(RGB(95,144,47));
    //ST7735_Fill(0, 0, 160, 3, RGB(17,72,0));

    

	drawscene();
       
    uint32_t frame=0;
    uint8_t lx =80;
    uint8_t ly =20;
       
   while(1) {
       uint8_t x = 24 + sine[frame%48];
       uint8_t y = 36 + cos[frame%48];
       ST7735_DrawLine(80, 0, lx, ly, RGB(95,144,47));
       clearHarry(lx-8,ly-2);
       ST7735_Fill(30, 61, 100, 1, RGB(159,174,29));
       ST7735_Fill(23, 34, 1, 24, RGB(8,27,0));
       ST7735_Fill(136, 34, 1, 24, RGB(8,27,0));
       ST7735_DrawLine(80, 0, x, y, RGB(8,27,0));
       drawHarry(x-8,y-2);

       ST7735_SetAddrWindow(0, 63, 160, 4);
       for (int j=2; j<6; ++j) {
            uint8_t r = pool[j];
            uint8_t t = 80-r/2;
            for (int i=0; i<t; ++i)
                ST7735_Write16(RGB(159,174,29));
            for (int i=0; i<r; ++i)
                ST7735_Write16(RGB(27,98,139));
            for (int i=0; i<t; ++i)
                ST7735_Write16(RGB(159,174,29));
       }

       drawGator(40, 64, (frame%64)<32);
       drawGator(72, 64, (frame%64)<32);
       drawGator(104, 64, (frame%64)<32);
       frame++;
       lx = x;
       ly = y;

       
       delay_ms(200);

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

void ST7735_DrawPixel(int16_t x, int16_t y, uint16_t color) {
    ST7735_SetAddrWindow(x,y,2,1);
    ST7735_Write16(color);
    ST7735_Write16(color);
}

inline int abs(int x) {
    if (x<0)
        return -x;
    return x;
}

void ST7735_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    int dx = abs(x2-x1), sx = x1<x2?1:-1;
    int dy = abs(y2-y1), sy = y1<y2?1:-1;
    
    int err = (dx>dy?dx:-dy)/2, e2;
    int x=x1, y=y1;
    for(;;){
      ST7735_DrawPixel(x, y, (y<6)?RGB(17,72,0):color);
      if (x==x2 && y==y2) break;
      e2 = err;
      if (e2 >-dx) { err -= dy; x += sx; }
      if (e2 < dy) { err += dx; y += sy; }
    }
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
    ST7735_Write(ST7735_INVON, CMD);
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
            //ST7735_Write16(~pallet[HIGH_NIB(d)]);
            //ST7735_Write16(~pallet[LOW_NIB(d)]);
        }
}


void ST7735_Fill(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) {
    ST7735_SetAddrWindow(x, y, w, h);
    for (int i=0; i< w; ++i)
        for(int j=0; j< h; ++j)
            ST7735_Write16(color);
}


