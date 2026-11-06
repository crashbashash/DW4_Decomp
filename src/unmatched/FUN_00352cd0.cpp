struct SFUN_00352cd0 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_00352cd0 *DAT_00588ba0[4];
extern "C" void FUN_00352da0(void);
extern "C" SFUN_00352cd0 *FUN_00352cd0(void) {
    if (DAT_00588ba0[0] == 0 || !DAT_00588ba0[0]->ok()) FUN_00352da0();
    return DAT_00588ba0[0];
}
