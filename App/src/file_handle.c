/*
 * file_handle.c
 *
 *  Created on: 10 de jul. de 2026
 *      Author: rinaldo.santos
 */
#include "main.h"
#include <../App/src/file_handle.h>
#include <../App/src/log_cdc.h>
#include "fatfs.h"
#include "stdio.h"
#include "string.h"

extern uint8_t retSD;    /* Return value for SD */
extern FATFS SDFatFS;    /* File system object for USER logical drive */
extern FIL SDFile;

FATFS *pfs;
char line[512]; /* Line buffer */
FRESULT fr;     /* FatFs return code */
DWORD fre_clust;
uint32_t totalSpace, freeSpace, SpaceUsed;
uint32_t duracao = 0;
uint32_t size = 0;
unsigned int ByteRead = 0;

char version_flash[32] = {0};

void Mount_FATFS(void)
{
	// Mount FileSystem
	MX_FATFS_Init();
	if(retSD != 0) {
		logI("FatFs - ERROR...[%d]\n\r", retSD);
	}
	else {
		logI("FatFs - OK...[%d]\n\r", retSD);
	}
	// Mount
	fr = f_mount(&SDFatFS, (TCHAR const*)SDPath, 0);
	if(fr != FR_OK) {
		logI("FatFs - Mount Drive ERROR...[%d]\n\r", fr);
	}
	else {
		logI("FatFs - Mount Drive...\n\r");
	}
	// Check freeSpace space
	fr = f_getfree("", &fre_clust, &pfs);
	if(fr != FR_OK){
		logI("FatFs - GetFree ERROR...\n\r");
	}
	else {
		logI("FatFs - GetFree OK...\n\r");
		totalSpace = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
		freeSpace = (uint32_t)(fre_clust * pfs->csize * 0.5);
		SpaceUsed = totalSpace - freeSpace;
		logI("FatFs - Total Space = %ld Free Space = %ld SpaceUsed: %ld\n\r",totalSpace , freeSpace, SpaceUsed);
	}

	// Test Open config.txt
	fr = f_open(&SDFile, "/Version.txt", FA_READ);
	if(fr != FR_OK) {
		logI("FatFs - Version.txt Error...Result: %d\n\r", fr);
	}
	else {
		fr = f_sync(&SDFile);
		size = f_size(&SDFile);
		logI("FatFs - Open File Version.txt... Result: %d Size: %d\n\r", fr, size);
		fr = f_read(&SDFile, line , size, &ByteRead);
		if(fr == FR_OK) {
			memcpy(version_flash, line, size);
			logI("FatFs ReadFile...line: %s\n\r", line);
		}
		else {
			logI("ReadFile...Error:  Result: %d \n\r", fr);
		}
		f_close(&SDFile);
	}
	// Test Open File AUDIO.bin
	duracao = HAL_GetTick();
	fr = f_open(&SDFile, "/AUDIO.bin", FA_READ);
	if(fr != FR_OK) {
		logI("FatFs - AUDIO.bin Error...Result: %d\n\r", fr);
	}
	else {
		duracao = HAL_GetTick() - duracao;
		size = f_size(&SDFile);
		logI("FatFs - Open File AUDIO.bin... Result: %d  Size:%d Duracao: %d\n\r", fr, size, duracao);
		fr = f_read(&SDFile, line , 512, &ByteRead);
		if(fr == FR_OK) {
			logI("FatFs ReadFile...line: %s\n\r", line);
		}
		else {
			logI("FatFs ReadFile...Error:  Result: %d \n\r", fr);
		}
		f_close(&SDFile);
	}
}
