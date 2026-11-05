/* 0x003b1c30 - FUN_003b1c30. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SFUN_003b1c30 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_003b1c30 *DAT_0058a9a8[4];
extern "C" void FUN_003b1cc0(void);
extern "C" SFUN_003b1c30 *FUN_003b1c30(void) {
    if (DAT_0058a9a8[0] == 0 || !DAT_0058a9a8[0]->ok()) FUN_003b1cc0();
    return DAT_0058a9a8[0];
}
