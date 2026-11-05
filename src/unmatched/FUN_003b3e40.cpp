/* 0x003b3e40 - FUN_003b3e40. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SFUN_003b3e40 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_003b3e40 *DAT_0058ab78[4];
extern "C" void FUN_003b3e90(void);
extern "C" SFUN_003b3e40 *FUN_003b3e40(void) {
    if (DAT_0058ab78[0] == 0 || !DAT_0058ab78[0]->ok()) FUN_003b3e90();
    return DAT_0058ab78[0];
}
