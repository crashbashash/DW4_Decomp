int igMetaObject_CreateInstance(int, int);
int igFieldSynchronizer_EnsureRegistered();

void FUN_004509c0(int arg0) {
    igFieldSynchronizer_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x58C538, arg0);
}
