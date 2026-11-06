struct SFUN_00336000 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_00336000 *DAT_00587798[4];
extern "C" void FUN_00336090(void);
extern "C" SFUN_00336000 *FUN_00336000(void) {
    if (DAT_00587798[0] == 0 || !DAT_00587798[0]->ok()) FUN_00336090();
    return DAT_00587798[0];
}
