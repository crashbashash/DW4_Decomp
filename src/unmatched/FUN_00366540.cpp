struct SFUN_00366540 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_00366540 *DAT_00589998[4];
extern "C" void FUN_00366620(void);
extern "C" SFUN_00366540 *FUN_00366540(void) {
    if (DAT_00589998[0] == 0 || !DAT_00589998[0]->ok()) FUN_00366620();
    return DAT_00589998[0];
}
