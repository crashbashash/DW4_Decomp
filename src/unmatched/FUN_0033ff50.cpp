struct SFUN_0033ff50 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_0033ff50 *DAT_00587aa0[4];
extern "C" void FUN_0033ffe0(void);
extern "C" SFUN_0033ff50 *FUN_0033ff50(void) {
    if (DAT_00587aa0[0] == 0 || !DAT_00587aa0[0]->ok()) FUN_0033ffe0();
    return DAT_00587aa0[0];
}
