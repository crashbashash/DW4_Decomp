int igIntList_EnsureRegistered();
int igMetaObject_CreateInstance(int, int);

void FUN_002caa70(int arg0) {
    igIntList_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x586880, arg0);
}
