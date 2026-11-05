/* 0x00277918 — FUN_00277918 (188 bytes). Library shutdown: counts the init reference 0x004abc68 down and,
   when it reaches zero, destroys every live object (state 1) of the 32-entry table at 0x004abc70 through
   FUN_00276fb8, clears the table, and runs FUN_00277890 and FUN_002777d0(0, 0).
   Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Entry568 {          /* 568-byte table entry; only the state byte is read here */
    signed char state;     /* 1 = live */
    char rest[567];
};

extern void FUN_00276fb8(struct Entry568 *entry);
extern void *memset(void *dest, int value, unsigned int size);
extern void FUN_00277890(void);
extern void FUN_002777d0(int a, int b);
extern int DAT_004abc68;
extern struct Entry568 DAT_004abc70[32];

void FUN_00277918(void) {
    struct Entry568 *entry;
    int i;

    if (--DAT_004abc68 == 0) {
        entry = DAT_004abc70;
        for (i = 0; i < 32; i++, entry++) {
            if (entry->state == 1) {
                FUN_00276fb8(entry);
            }
        }
        memset(DAT_004abc70, 0, sizeof(DAT_004abc70));
        FUN_00277890();
        FUN_002777d0(0, 0);
    }
}
