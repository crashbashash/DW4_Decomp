int igUnsignedCharMetaField_EnsureRegistered();
int igMetaObject_CreateInstance(int, int);

void FUN_002b73e0(int arg0) {
    igUnsignedCharMetaField_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x585760, arg0);
}
