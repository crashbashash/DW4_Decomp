struct SFUN_0035fa20 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_0035fa20 *DAT_005894e8[4];
extern "C" void FUN_0035fab0(void);
extern "C" SFUN_0035fa20 *FUN_0035fa20(void) {
    if (DAT_005894e8[0] == 0 || !DAT_005894e8[0]->ok()) FUN_0035fab0();
    return DAT_005894e8[0];
}
