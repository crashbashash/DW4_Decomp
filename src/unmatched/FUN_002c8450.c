int igDataList_EnsureRegistered();
int igMetaObject_CreateInstance(int, int);

void FUN_002c8450(int arg0) {
    igDataList_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x586788, arg0);
}
