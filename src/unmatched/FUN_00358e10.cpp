/* 0x00358e10 - FUN_00358e10. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct SFUN_00358e10 { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern SFUN_00358e10 *DAT_00589038[4];
extern "C" void beMessengerArgData_EnsureRegistered(void);
extern "C" SFUN_00358e10 *FUN_00358e10(void) {
    if (DAT_00589038[0] == 0 || !DAT_00589038[0]->ok()) beMessengerArgData_EnsureRegistered();
    return DAT_00589038[0];
}
