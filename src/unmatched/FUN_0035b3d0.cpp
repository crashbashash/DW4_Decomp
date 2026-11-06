struct SFUN_0035b3d0 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_0035b3d0 *DAT_005891e8[4];
extern "C" void FUN_0035b460(void);
extern "C" SFUN_0035b3d0 *FUN_0035b3d0(void) {
    if (DAT_005891e8[0] == 0 || !DAT_005891e8[0]->ok()) FUN_0035b460();
    return DAT_005891e8[0];
}
