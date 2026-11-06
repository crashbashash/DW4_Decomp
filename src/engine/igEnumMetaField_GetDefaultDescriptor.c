int igEnumMetaField_EnsureRegistered();
extern int DAT_005865a0[4];
int igEnumMetaField_GetDefaultDescriptor(void) {
    if (DAT_005865a0[0] == 0) {
        igEnumMetaField_EnsureRegistered();
    }
    return DAT_005865a0[0];
}
