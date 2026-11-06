struct SFUN_0035d4a0 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_0035d4a0 *DAT_00589320[4];
extern "C" void FUN_0035d5a0(void);
extern "C" SFUN_0035d4a0 *FUN_0035d4a0(void) {
    if (DAT_00589320[0] == 0 || !DAT_00589320[0]->ok()) FUN_0035d5a0();
    return DAT_00589320[0];
}
