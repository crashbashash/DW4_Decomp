struct SFUN_0036cb00 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_0036cb00 *DAT_00589f78[4];
extern "C" void FUN_0036cc80(void);
extern "C" SFUN_0036cb00 *FUN_0036cb00(void) {
    if (DAT_00589f78[0] == 0 || !DAT_00589f78[0]->ok()) FUN_0036cc80();
    return DAT_00589f78[0];
}
