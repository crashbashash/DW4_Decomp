struct SFUN_003618e0 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_003618e0 *DAT_00589658[4];
extern "C" void FUN_00361c70(void);
extern "C" SFUN_003618e0 *FUN_003618e0(void) {
    if (DAT_00589658[0] == 0 || !DAT_00589658[0]->ok()) FUN_00361c70();
    return DAT_00589658[0];
}
