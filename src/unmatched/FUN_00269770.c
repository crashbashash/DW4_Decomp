/* 0x00269770 — FUN_00269770 (104 bytes). Sets the 16-byte name at offset 727 of a header from name, the first time also flagging it at offset 726 and growing the size word at offset 72 by 36. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Header_269770 {
    char pad0[72];
    int size;           /* 0x48 */
    char pad76[650];
    char has_name;      /* 0x2d6 */
    char name[16];      /* 0x2d7 */
} Header_269770;

void *memset(void *dst, int value, unsigned int size);
char *strncpy(char *dst, const char *src, unsigned int size);

void FUN_00269770(Header_269770 *header, const char *name) {
    if (header->has_name != 1) {
        header->has_name = 1;
        header->size += 36;
    }
    memset(header->name, 0, 16);
    strncpy(header->name, name, 16);
}
