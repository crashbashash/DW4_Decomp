int igRawRefMetaField_EnsureRegistered();
extern int DAT_00585a88[4];
int igRawRefMetaField_GetDefaultDescriptor(void) {
    if (DAT_00585a88[0] == 0) {
        igRawRefMetaField_EnsureRegistered();
    }
    return DAT_00585a88[0];
}
