int igMemoryRefMetaField_EnsureRegistered();
extern int DAT_00585d88[4];
int FUN_002bfa60(void) {
    if (DAT_00585d88[0] == 0) {
        igMemoryRefMetaField_EnsureRegistered();
    }
    return DAT_00585d88[0];
}
