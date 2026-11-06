int igStringMetaField_EnsureRegistered();
extern int DAT_00585910[4];
int FUN_002b9c60(void) {
    if (DAT_00585910[0] == 0) {
        igStringMetaField_EnsureRegistered();
    }
    return DAT_00585910[0];
}
