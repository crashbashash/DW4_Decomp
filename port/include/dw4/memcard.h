/* Host memory card: the native stand-in for retail's SAVEUTILITY receiver (beNDMWMcUtilCtrl) and
 * the slot scan of beNDMWSaveCtrl (update 407120). A card is a directory holding one
 * BASLUS-20836savedata image of four character slots. It never creates the directory and never
 * writes outside it. */
#ifndef DW4_MEMCARD_H
#define DW4_MEMCARD_H
#include "dw4/saveimage.h"
#include "dw4/database.h"
typedef struct dw4_memcard dw4_memcard;
#define DW4_MEMCARD_FILE "BASLUS-20836savedata"
dw4_memcard *dw4_memcard_open(const char *directory);
void dw4_memcard_close(dw4_memcard *);
/* SAVEUTILITY ISRDY: the directory exists and can be written. */
int dw4_memcard_ready(const dw4_memcard *);
/* SaveCtrl phase 1/3 scan: present[slot] is the slot's ISUSE byte. A card without a save file scans as empty (0); an
 * unreadable or corrupt file returns -1 with a reason in error and leaves present untouched. Returns the count of
 * used slots through *used (may be NULL). */
int dw4_memcard_scan(const dw4_memcard *,int present[DW4_SAVE_SLOTS],int *used,char *error,size_t cap);
/* Write the records of player_for_slot[slot] (-1 skips the slot) into the card's image, creating it when absent. The
 * existing image must verify: a damaged file is refused, never overwritten. The write is atomic and read back. */
int dw4_memcard_save(dw4_memcard *,dw4_playerrecords *,const int32_t player_for_slot[DW4_SAVE_SLOTS],char *error,size_t cap);
/* Load one slot into a player (see dw4_saveimage_load for what the caller must rebuild). */
int dw4_memcard_load(const dw4_memcard *,dw4_playerrecords *,int32_t player,int32_t slot,char *error,size_t cap);
/* Title "Call Digimon": make player a live character from a card slot (fresh record of the saved species, stored keys
 * loaded over it, stats recalculated). The record is replaced only when every step succeeds. */
int dw4_memcard_restore(const dw4_memcard *,dw4_playerrecords *,const dw4_databases *,int32_t player,int32_t slot,
    char *error,size_t cap);
/* SAVEUTILITY GETFREESIZE: bytes of the image still unused by the card (0 when the file exists, else its size). */
size_t dw4_memcard_needed(const dw4_memcard *);
/* SAVEUTILITY REQUEST_FILEMAKE: create an empty, valid save image when the card has none (an existing valid file is
 * left as it is). A damaged file is refused. */
int dw4_memcard_make(dw4_memcard *,char *error,size_t cap);
/* The leading summary of a character record (retail deliver struct +0x00..+0x58): what the data-select screen shows. */
typedef struct {
    uint8_t used;int32_t unique;char model[33];uint16_t name[9];
    int32_t level,hp,mhp,mp,mmp;
} dw4_memcard_summary;
/* SAVEUTILITY REQUEST_READ_MEDIA: the four slots' summaries (all unused when the card has no file). */
int dw4_memcard_summaries(const dw4_memcard *,dw4_memcard_summary out[DW4_SAVE_SLOTS],char *error,size_t cap);
/* The native save library directory (decision recorded in the technical spec): $XDG_DATA_HOME/dw4/saves, else
 * ~/.local/share/dw4/saves. create makes the directories. The previous file is kept as <file>.bak by every write. */
int dw4_memcard_default_directory(char *out,size_t cap,int create);
/* The SaveCtrl exit rule lives in dw4/savectrl.h (dw4_savectrl_exit_stage). */
#endif
