#ifndef MMU_H
#define MMU_H

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #define debugger emscripten_debugger();
    #define export EMSCRIPTEN_KEEPALIVE
#else
    #define export
    #define debugger
#endif


// Memory map
#define ROM_BASE            ((unsigned short)0x0000) /*!< 32kB Cartrigbe ROM base address */
#define VRAM_BASE           ((unsigned short)0x8000) /*!< 8kB Video RAM base address */
#define ERAM_BASE           ((unsigned short)0xA000) /*!< External RAM (8kB switchable RAM bank) base address */
#define RAM_BASE            ((unsigned short)0xC000) /*!< 8kB Internal RAM base address */
#define OAM_RAM_BASE        ((unsigned short)0xFE00) /*!< Sprite Attrib Memory (OAM) base address, OAM is 160 bytes, remaining bytes read as 0 */
#define IO_BASE             ((unsigned short)0xFF00) /*!< I/O ports base address */
#define HRAM_BASE           ((unsigned short)0xFF80) /*!< HRAM base address */
#define TOP_ADDR            ((unsigned short)0xFFFF)

#define BANK_SIZE           ((VRAM_BASE-ROM_BASE)/2)

#define _MEM(addr, pc)      (*mmu((addr), 0, (pc)))
#define _wMEM(addr, pc)     (*mmu((addr), 1, (pc)))

typedef struct {
    unsigned char P1;
    unsigned char SB;
    unsigned char SC;
    unsigned char x03;
    unsigned char DIV;
    unsigned char TIMA;
    unsigned char TMA;
    unsigned char TAC;
    unsigned char x08[7];  // 0x08 ~ 0x0E
    unsigned char IF;
    unsigned char NR10;
    unsigned char NR11;
    unsigned char NR12;
    unsigned char NR13;
    unsigned char NR14;
    unsigned char x15;
    unsigned char NR21;
    unsigned char NR22;
    unsigned char NR23;
    unsigned char NR24;
    unsigned char NR30;
    unsigned char NR31;
    unsigned char NR32;
    unsigned char NR33;
    unsigned char NR34;
    unsigned char x1F;
    unsigned char NR41;
    unsigned char NR42;
    unsigned char NR43;
    unsigned char NR44;
    unsigned char NR50;
    unsigned char NR51;
    unsigned char NR52;
    unsigned char x27[9];   // 0x27 ~ 0x2F
    unsigned char WAV[16];
    unsigned char LCDC;
    unsigned char STAT;
    unsigned char SCY;
    unsigned char SCX;
    unsigned char LY;
    unsigned char LYC;
    unsigned char DMA;
    unsigned char BGP;
    unsigned char OBP0;
    unsigned char OBP1;
    unsigned char WY;
    unsigned char WX;
    unsigned char x4C;
    unsigned char KEY1;
    unsigned char x4E;
    unsigned char VBK;
    unsigned char BOOT;
    unsigned char HDMA1;
    unsigned char HDMA2;
    unsigned char HDMA3;
    unsigned char HDMA4;
    unsigned char HDMA5;
    unsigned char RP;
    unsigned char x57[17];
    unsigned char BCPS;
    unsigned char BCPD;
    unsigned char OCPS;
    unsigned char OCPD;
    unsigned char x6C[4];   // 0x6C ~ 0x6F
    unsigned char SVBK;
    unsigned char x71[5];   // 0x71 ~ 0x75
    unsigned char PCM12;
    unsigned char PCM34;
    unsigned char x78[8];  // 0x78 ~ 0x7F
    unsigned char HRAM[0x7F]; // 0x80 ~ 0xFE
    unsigned char IE;
} REG_TypeDef;


/*******************  Bit definition for P1 register  ********************/
#define P1_IN_P10_RA        ((unsigned char)0x01)     /*!< Right / A */
#define P1_IN_P11_LB        ((unsigned char)0x02)     /*!< Left / B */
#define P1_IN_P12_USL       ((unsigned char)0x04)     /*!< Up / Select */
#define P1_IN_P13_DST       ((unsigned char)0x08)     /*!< Down / Start */
#define P1_OUT_P14_DIR      ((unsigned char)0x10)     /*!< Direction Joy Pad */
#define P1_OUT_P15_BTN      ((unsigned char)0x20)     /*!< A, B, Select, Start */


/*******************  Bit definition for STAT register  ********************/
#define STAT_LCD_MODE       ((unsigned char)0x03)     /*!< Mode[1:0] Flag */
#define STAT_LYC_STAT       ((unsigned char)0x04)     /*!< Coincidence Flag */
#define STAT_INTR_M0        ((unsigned char)0x08)     /*!< H-Blank Interrupt Selection */
#define STAT_INTR_M1        ((unsigned char)0x10)     /*!< V-Blank Interrupt Selection */
#define STAT_INTR_M2        ((unsigned char)0x20)     /*!< OAM Interrupt Selection */
#define STAT_INTR_LYC       ((unsigned char)0x40)     /*!< LYC Interrupt Selection */

// STAT_LCD_MODE[1:0]
#define LCD_MODE_HBLANK     ((unsigned char)0x00)   // 00: During H-Blank
#define LCD_MODE_VBLANK     ((unsigned char)0x01)   // 01: During V-Blank
#define LCD_MODE_OAM        ((unsigned char)0x02)   // 10: During Searching OAM-RAM
#define LCD_MODE_TRANS      ((unsigned char)0x03)   // 11: During Transfering Data to LCD Driver

/*******************  Bit definition for LCDC register  ********************/
#define LCDC_BG_EN          ((unsigned char)0x01)     /*!< BG & Window Display Enable */
#define LCDC_OBJ_EN         ((unsigned char)0x02)     /*!< OBJ (Sprite) Display Enable */
#define LCDC_OBJ_SIZE       ((unsigned char)0x04)     /*!< OBJ (Sprite) Size (8*8 or 8*16) */
#define LCDC_BG_MAP         ((unsigned char)0x08)     /*!< BG Tile Map Address Select */
#define LCDC_TILE_SEL       ((unsigned char)0x10)     /*!< BG & Window Tile Data Select */
#define LCDC_WIN_EN         ((unsigned char)0x20)     /*!< Window Display Enable */
#define LCDC_WIN_MAP        ((unsigned char)0x40)     /*!< Window Tile Map Address Select */
#define LCDC_LCD_EN         ((unsigned char)0x80)     /*!< LCD Control Operation */

/*******************  Bit definition for IE and IF register  ********************/
#define IE_VBLANK           ((unsigned char)0x01)     /*!< V-Blank */
#define IE_STAT             ((unsigned char)0x02)     /*!< LCDC Status */
#define IE_TIMER            ((unsigned char)0x04)     /*!< Timer Overflow */
#define IE_SERIAL           ((unsigned char)0x08)     /*!< Serial Transfer Completion */
#define IE_JOYPAD           ((unsigned char)0x10)     /*!< Joypad */

/*******************  Bit definition for TAC register  ********************/
#define TAC_CLK             ((unsigned char)0x03)     /*!< Input Clock Select */
#define TAC_EN              ((unsigned char)0x04)     /*!< Timer Enable */

typedef struct {
    unsigned char RST_00[8];
    unsigned char RST_08[8];
    unsigned char RST_10[8];
    unsigned char RST_18[8];
    unsigned char RST_20[8];
    unsigned char RST_28[8];
    unsigned char RST_30[8];
    unsigned char RST_38[8];
    unsigned char RST_40[8];
    unsigned char RST_48[8];
    unsigned char RST_50[8];
    unsigned char RST_58[8];
    unsigned char RST_60[8];
    unsigned char x68[0x98];

    unsigned char ENTRY[4];
    unsigned char LOGO[48];
    unsigned char TITLE[15];    // Title of the game in UPPER CASE ASCII.
    unsigned char COLOR_FLAG;   // $80 = Color GB, $00 or other = not Color GB
    unsigned char LICENS[2];    // licensee code
    unsigned char MODEL;        // GB/SGB Indicator (00 = GameBoy, 03 = Super GameBoy functions) (Super GameBoy functions won't work if <> $03.)
    unsigned char CART_TYPE;
    unsigned char ROM_SIZE;
    unsigned char RAM_SIZE;
    unsigned char DEST_CODE;
    unsigned char LICENS_OLD;
    unsigned char ROM_VERSION;
    unsigned char HEADER_SUM;
    unsigned char GLOBAL_SUM[2];
} ROM_HEADER_TypeDef;


extern unsigned char _bios[0x100];
extern unsigned char _rom[BANK_SIZE * 128];
extern unsigned char _vram[ERAM_BASE-VRAM_BASE];
extern unsigned char _eram[RAM_BASE-ERAM_BASE];
extern unsigned char _ram[OAM_RAM_BASE-RAM_BASE];
extern unsigned char _oam[IO_BASE-OAM_RAM_BASE];
extern unsigned char _io[TOP_ADDR-IO_BASE];

extern unsigned char _mbc[VRAM_BASE-ROM_BASE];
extern unsigned char dma_trigger;

#define IO_Reg      ((REG_TypeDef *) _io)
#define ROM_Header  ((ROM_HEADER_TypeDef *) _rom)

export extern unsigned char *mmu(unsigned short addr, unsigned char W, unsigned short PC);

#endif