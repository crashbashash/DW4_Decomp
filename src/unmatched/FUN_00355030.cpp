/* 0x00355030 - FUN_00355030. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SFUN_00355030 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_00355030 *DAT_00588d68[4];
extern "C" void FUN_00355110(void);
extern "C" SFUN_00355030 *FUN_00355030(void) {
    if (DAT_00588d68[0] == 0 || !DAT_00588d68[0]->ok()) FUN_00355110();
    return DAT_00588d68[0];
}
