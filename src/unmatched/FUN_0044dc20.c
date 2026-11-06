int igMetaObject_CreateInstance(int, int);
int igHotKeyBinding_RunStaticInit();

void FUN_0044dc20(int arg0) {
    igHotKeyBinding_RunStaticInit();
    igMetaObject_CreateInstance(*(int *)0x58C2C0, arg0);
}
