extern int D_004ba484;          /* init count */
extern char D_004ba720[2256];   /* EE work buffer */
extern int D_004ba71c;          /* work length */
extern unsigned D_004ba488;     /* 64-byte aligned EE work */
extern int D_004ba48c;          /* IOP heap block */
extern unsigned D_004ba490;     /* 64-byte aligned IOP work */
extern void *D_004ba718;        /* DTX server */
extern const char D_004f24c8[], D_004f24f8[];
extern void memset(void *, int, unsigned);
extern void FUN_002736b8(void);
extern int FUN_00112170(int);
extern void FUN_002659a0(const char *, ...);
extern void *FUN_00273338(unsigned, unsigned, unsigned, int);
extern void FUN_00273538(void *, void (*)(void), int);
extern void FUN_00273548(void *, void (*)(void), int);
extern void FUN_00273820(int, int, int, int, int);
extern void FUN_0027dba8(void);
extern void FUN_0027dc48(void);

void FUN_0027dd70(void)
{
    if (D_004ba484 == 0) {
        memset(D_004ba720, 0, 2256);
        FUN_002736b8();
        D_004ba71c = 2176;
        D_004ba488 = ((unsigned)D_004ba720 + 64) & -64;
        if (D_004ba48c == 0) {
            D_004ba48c = FUN_00112170(2256);
            if (D_004ba48c == 0) {
                FUN_002659a0(D_004f24c8);
                for (;;)
                    ;
            }
        }
        D_004ba490 = (D_004ba48c + 64) & -64;
        D_004ba718 = FUN_00273338(0, D_004ba488, D_004ba490, D_004ba71c);
        if (D_004ba718 == 0) {
            FUN_002659a0(D_004f24f8);
            for (;;)
                ;
        }
        FUN_00273538(D_004ba718, FUN_0027dba8, 0);
        FUN_00273548(D_004ba718, FUN_0027dc48, 0);
        FUN_00273820(3, 0, 0, 0, 0);
    }
    D_004ba484++;
}
