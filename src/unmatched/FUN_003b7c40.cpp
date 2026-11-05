/* 0x003b7c40 - FUN_003b7c40. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SFUN_003b7c40 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_003b7c40 *DAT_0058ad88[4];
extern "C" void FUN_003b7d30(void);
extern "C" SFUN_003b7c40 *FUN_003b7c40(void) {
    if (DAT_0058ad88[0] == 0 || !DAT_0058ad88[0]->ok()) FUN_003b7d30();
    return DAT_0058ad88[0];
}
