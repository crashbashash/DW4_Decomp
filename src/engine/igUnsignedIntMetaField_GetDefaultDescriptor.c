int igUnsignedIntMetaField_EnsureRegistered();
extern int DAT_00585740[4];
int igUnsignedIntMetaField_GetDefaultDescriptor(void) {
    if (DAT_00585740[0] == 0) {
        igUnsignedIntMetaField_EnsureRegistered();
    }
    return DAT_00585740[0];
}
