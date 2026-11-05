/* Initialises the 1000-byte state block at D_004bec28 (field +4 = 8), then runs the three follow-up steps; the last is a tail call. */
extern void *memset(void *, int, unsigned int);
extern int D_004bec28[];
extern void FUN_002b3b78(int);
extern void FUN_00283058(void);
extern void FUN_002830f0(void);
void FUN_002b3808(void)
{
    memset(D_004bec28, 0, 1000);
    D_004bec28[1] = 8;
    FUN_002b3b78(1);
    FUN_00283058();
    FUN_002830f0();
}
