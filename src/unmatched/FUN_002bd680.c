int igObjectList_EnsureRegistered();
int igMetaObject_CreateInstance(int, int);

void FUN_002bd680(int arg0) {
    igObjectList_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x585B60, arg0);
}
