struct SFUN_003492b0 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_003492b0 *DAT_00588238[4];
extern "C" void FUN_00349430(void);
extern "C" SFUN_003492b0 *FUN_003492b0(void) {
    if (DAT_00588238[0] == 0 || !DAT_00588238[0]->ok()) FUN_00349430();
    return DAT_00588238[0];
}
