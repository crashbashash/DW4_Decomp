/* PS2 save-file translation: the 81,920-byte BASLUS-20836savedata image (two mirrored 0xA000 blocks) and one
 * player's GAMERAM records. Serializer 3ee6d0 (records -> deliver struct) and loader 3ef5d0 (struct -> records),
 * item ids from the beNDMWItem* vfunc_23/24 pairs. Layout and evidence: port/docs/save-image.md. */
#ifndef DW4_SAVEIMAGE_H
#define DW4_SAVEIMAGE_H
#include "dw4/playerrecords.h"
#include <stddef.h>
#include <stdint.h>
#define DW4_SAVE_IMAGE_SIZE 81920u
#define DW4_SAVE_BLOCK_SIZE 0xA000u
#define DW4_SAVE_VERSION 4u
/* A block holds four character records, one per player slot, 0x2000 bytes apart from file offset 8. */
#define DW4_SAVE_SLOTS 4
#define DW4_SAVE_SLOT_STRIDE 0x2000u
/* Item id (retail records <-> 32-bit words). Empty (kind<0) is 0xFFFFFFFF; kinds 0..4 are weapon, blue armor,
 * yellow armor, ability chip and disk; any other kind or an unrepresentable field is refused (-1). Decode maps
 * an id whose kind nibble is above 4 (including 0xFFFFFFFF) to an empty record, as 3ef1e0 stores NULL. */
int dw4_saveimage_item_encode(const dw4_item_record *,uint32_t *);
int dw4_saveimage_item_decode(uint32_t,dw4_item_record *);
/* Both blocks must have version 4, a correct sum of the u32 words after the checksum word, and be identical
 * (the second block mirrors the first). Returns 0, or -1 with a short reason in *why (may be NULL). */
int dw4_saveimage_verify(const uint8_t *,size_t,const char **why);
/* An empty save: zeroes with valid version and checksums in both blocks. */
void dw4_saveimage_init(uint8_t image[DW4_SAVE_IMAGE_SIZE]);
/* Nonzero when the slot's ISUSE byte is set. */
int dw4_saveimage_slot_used(const uint8_t *image,int32_t slot);
/* Serialize player's records into slot of a valid image (both mirrored blocks, checksums refreshed); the other slots
 * are untouched. The record must hold every saved key with its retail shape (as dw4_playerrecords_create builds
 * it); equipment references must index DEVICEFOLDER or be -1. The image is unchanged on failure. */
int dw4_saveimage_store(dw4_playerrecords *,int32_t player,int32_t slot,uint8_t image[DW4_SAVE_IMAGE_SIZE]);
/* Replace the saved keys of player from a slot of a verified image, atomically (a private copy is committed only
 * when every key decodes). Species (DIGIMONNO), the current stats derived from BASE_*, the equipped weapon model
 * (POWERSOCKETNAME) and every recalculated stat are not stored in a save: the caller must rebuild them, as
 * retail does after 3ef5d0 (finding #106). Equipment lists are re-projected from the stored references. */
int dw4_saveimage_load(dw4_playerrecords *,int32_t player,int32_t slot,const uint8_t *,size_t);
/* Whole-file helpers. write replaces the destination atomically (temporary file in the same directory, flush,
 * rename) so a failed write leaves the previous valid file untouched; it verifies what it wrote. */
int dw4_savefile_write(const char *path,const uint8_t image[DW4_SAVE_IMAGE_SIZE]);
int dw4_savefile_read(const char *path,uint8_t image[DW4_SAVE_IMAGE_SIZE]);
#endif
