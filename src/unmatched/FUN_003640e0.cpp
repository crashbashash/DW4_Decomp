struct SFUN_003640e0 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_003640e0 *DAT_00589840[4];
extern "C" void FUN_00364170(void);
extern "C" SFUN_003640e0 *FUN_003640e0(void) {
    if (DAT_00589840[0] == 0 || !DAT_00589840[0]->ok()) FUN_00364170();
    return DAT_00589840[0];
}
