int igShortMetaField_EnsureRegistered();
extern int DAT_00585950[4];
int igShortMetaField_GetDefaultDescriptor(void) {
    if (DAT_00585950[0] == 0) {
        igShortMetaField_EnsureRegistered();
    }
    return DAT_00585950[0];
}
