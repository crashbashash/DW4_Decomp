struct SFUN_00344680 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_00344680 *DAT_00587ec8[4];
extern "C" void FUN_00344710(void);
extern "C" SFUN_00344680 *FUN_00344680(void) {
    if (DAT_00587ec8[0] == 0 || !DAT_00587ec8[0]->ok()) FUN_00344710();
    return DAT_00587ec8[0];
}
