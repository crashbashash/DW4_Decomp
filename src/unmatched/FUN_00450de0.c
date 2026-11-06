int igMetaObject_CreateInstance(int, int);
int igFieldChangeView_EnsureRegistered();

void FUN_00450de0(int arg0) {
    igFieldChangeView_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x58C550, arg0);
}
