/* Library initialisation under the FUN_00277798/FUN_002777b8 lock: the first call clears the
 * 0x4700-byte work area DAT_004abc70 and runs FUN_00277888 and FUN_002777d0(0, 0); every call
 * counts in DAT_004abc68. */
typedef struct Lock_277898 {
    int words[4];
} Lock_277898;

/* Points at the "LSC/PS2EE Ver.2.18" build string (0x4f0bc8); read and discarded so the string stays linked. */
extern char *volatile DAT_004abc50;
extern int DAT_004abc68;
extern char DAT_004abc70[];
void FUN_00277798(Lock_277898 *lock);
void FUN_002777b8(Lock_277898 *lock);
void FUN_00277888(void);
void FUN_002777d0(int a, int b);
void *memset(void *dst, int value, unsigned int n);

void FUN_00277898(void) {
    Lock_277898 lock;

    (void)DAT_004abc50;
    FUN_00277798(&lock);
    if (DAT_004abc68 == 0) {
        memset(DAT_004abc70, 0, 0x4700);
        FUN_00277888();
        FUN_002777d0(0, 0);
    }
    DAT_004abc68++;
    FUN_002777b8(&lock);
}

