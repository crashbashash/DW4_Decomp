/* Runs FUN_0026f160 on each of the 16 60-byte entries of DAT_004a8eb8 whose first word is 1. */
typedef struct Entry_26f258 {
    int used;           /* 0x00 */
    char rest[56];
} Entry_26f258;

extern Entry_26f258 DAT_004a8eb8[16];
void FUN_0026f160(Entry_26f258 *entry);

void FUN_0026f258(void) {
    int i;

    for (i = 0; i < 16; i++) {
        if (DAT_004a8eb8[i].used == 1) {
            FUN_0026f160(&DAT_004a8eb8[i]);
        }
    }
}
