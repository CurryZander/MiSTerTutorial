#ifndef __GERANIUM_H__
#define __GERANIUM_H__

//////////////////////////////////////////////////////////////////////////
// GENERAL INCLUDES														//
//////////////////////////////////////////////////////////////////////////

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

//////////////////////////////////////////////////////////////////////////
// CONSOLE INCLUDES														//
//////////////////////////////////////////////////////////////////////////

#include "CONSOLE/console.h"

//////////////////////////////////////////////////////////////////////////
// SD CARD FILE SYSTEM													//
//////////////////////////////////////////////////////////////////////////

#include "sys/pff.h"
#include "sys/diskio.h"

//////////////////////////////////////////////////////////////////////////
// GENERAL STUFF														//
//////////////////////////////////////////////////////////////////////////

#define CODE_ON										1
#define CODE_OFF									0

//////////////////////////////////////////////////////////////////////////
// IRQ STUFF															//
//////////////////////////////////////////////////////////////////////////

#define GERANIUM_IRQ_VIDEO_SWAP						0x00000008
#define GERANIUM_IRQ_KEYBOARD_INPUT					0x00000010
#define GERANIUM_IRQ_HARDWARE_ACK					0x00000020

//////////////////////////////////////////////////////////////////////////
// HARDWARE AND RAM REGISTER STUFF										//
//////////////////////////////////////////////////////////////////////////

#define GERANIUM_OTHER_ADDRESS						0xC0000000
#define GERANIUM_IO_ADDRESS							0x80000000
#define GERANIUM_SDRAM_ADDRESS						0x40000000
#define GERANIUM_DDRAM_ADDRESS						0x00000000

//////////////////////////////////////////////////////////////////////////
// CONSOLE STUFF														//
//////////////////////////////////////////////////////////////////////////

#define CHAR_HORIZONTAL_COUNT						80
#define CHAR_VERTICAL_COUNT							60
#define CHAR_TOTAL_COUNT							(CHAR_VERTICAL_COUNT*CHAR_HORIZONTAL_COUNT)

//////////////////////////////////////////////////////////////////////////
// IO HARDWARE REGISTER STUFF											//
//////////////////////////////////////////////////////////////////////////

#define CPU_IO_TEXT									0
#define CPU_IO_SD_LBA								1
#define CPU_IO_SD_CONTROL							2
#define CPU_IO_SD_DATA								3
#define CPU_IO_STATUS								4
#define CPU_IO_IMAGE_MOUNTED						5
#define CPU_IO_IMAGE_SIZE_HI						6
#define CPU_IO_IMAGE_SIZE_LO						7
#define CPU_IO_KEYBOARD_KEY							8

//////////////////////////////////////////////////////////////////////////
// SD CARD IO STUFF														//
//////////////////////////////////////////////////////////////////////////

#define CPU_IO_SD_CONTROL_RD						1
#define CPU_IO_SD_CONTROL_WR						2
#define CPU_IO_SD_CONTROL_ACK						4
#define CPU_IO_SD_CONTROL_DONE						8

//////////////////////////////////////////////////////////////////////////
// ERROR HANDLE STUFF													//
//////////////////////////////////////////////////////////////////////////

#define ERROR_GRNM_NONE								0
#define ERROR_GRNM_FILE_SYSTEM						1
#define ERROR_GRNM_FILE_IO							2
#define ERROR_GRNM_GRAPHICS_IO						3
#define ERROR_GRNM_MEMORY							4

//////////////////////////////////////////////////////////////////////////
// GENERAL MACROS														//
//////////////////////////////////////////////////////////////////////////

#define WRITECHAR(c)								(*(volatile uint32_t*)GERANIUM_IO_ADDRESS) = c
#define WRITECHAR_CLEAR_SCREEN()					(*(volatile uint32_t*)GERANIUM_IO_ADDRESS) = (0x080000000)
#define WRITECHAR_CLEAR_LINE()						(*(volatile uint32_t*)GERANIUM_IO_ADDRESS) = (0x040000000)
#define WRITECHAR_CONSOLE_ON()						(*(volatile uint32_t*)GERANIUM_IO_ADDRESS) = (0x020000000)
#define WRITECHAR_CONSOLE_OFF()						(*(volatile uint32_t*)GERANIUM_IO_ADDRESS) = (0x010000000)
#define WRITEIO(addr,c)								(*(volatile uint32_t*)(GERANIUM_IO_ADDRESS | ((addr) << 2))) = c
#define READIO(addr)								(*(volatile uint32_t*)(GERANIUM_IO_ADDRESS | ((addr) << 2)))
#define WRITEOTHER(addr,c)							(*(volatile uint32_t*)(GERANIUM_OTHER_ADDRESS | ((addr) << 2))) = c
#define READOTHER(addr)								(*(volatile uint32_t*)(GERANIUM_OTHER_ADDRESS | ((addr) << 2)))
#define WRITESDRAM(addr,c)							(*(volatile uint32_t*)(GERANIUM_SDRAM_ADDRESS | (addr) )) = c
#define READSDRAM(addr)								(*(volatile uint32_t*)(GERANIUM_SDRAM_ADDRESS | (addr)))
#define READKEY()									(*(volatile uint32_t*)(GERANIUM_IO_ADDRESS | (CPU_IO_KEYBOARD_KEY << 2)))
#define READ_FILE(f,s)								(pf_read(f, s, ((UINT*)&s)))
#define OPEN_FILE(filename)							(pf_open(filename))

//////////////////////////////////////////////////////////////////////////
// ERROR HANDLE STUFF													//
//////////////////////////////////////////////////////////////////////////

void seterrorno(uint32_t e);
uint32_t geterrorno(void);
void die(FRESULT rc);

//////////////////////////////////////////////////////////////////////////
// INTERUPT STUFF														//
//////////////////////////////////////////////////////////////////////////

uint32_t* irq(uint32_t* regs, uint32_t irqs);

//////////////////////////////////////////////////////////////////////////
// SYSTEM STUFF															//
//////////////////////////////////////////////////////////////////////////

uint32_t get_status(void);

//////////////////////////////////////////////////////////////////////////
// CONSOLE STUFF														//
//////////////////////////////////////////////////////////////////////////

void display_help_on_console(void);
void cmd_add_char(char ch);
void cmd_enter(void);
void outputstring(char* string_to_output, bool toend);
void outputchar(char c);
void cleartextbuffer(void);
void clear_line(void);
void print_bin_val(uint32_t val);
void print_hex_val(uint32_t val);
char* get_bin(uint32_t pos, uint32_t num);
uint32_t getcharcount(char* str);
void dir_to_screen(void);
void print_last_error(void);
void console_print_line(char* string_to_output);
void toggle_console(void);

//////////////////////////////////////////////////////////////////////////
// FILE SYSTEM STUFF													//
//////////////////////////////////////////////////////////////////////////

bool load_file_system(void);
bool open_dir(char* filedir);

//////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES														//
//////////////////////////////////////////////////////////////////////////

extern char buf[256];
extern uint32_t pos;
extern bool console_on;

extern bool image_data_valid;
extern size_t image_data_size;
extern void* image_data;

extern FATFS fatfs;
extern FRESULT rc;
extern uint32_t val;
extern DIR dir;
extern FILINFO fno;

extern bool restart_loop;

extern bool interupt_on;

//////////////////////////////////////////////////////////////////////////
// ENTRY POINT															//
//////////////////////////////////////////////////////////////////////////

int main(void);


#endif//__GERANIUM_H__