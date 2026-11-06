struct SFUN_00346810 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_00346810 *DAT_00587ff8[4];
extern "C" void FUN_00346950(void);
extern "C" SFUN_00346810 *FUN_00346810(void) {
    if (DAT_00587ff8[0] == 0 || !DAT_00587ff8[0]->ok()) FUN_00346950();
    return DAT_00587ff8[0];
}
