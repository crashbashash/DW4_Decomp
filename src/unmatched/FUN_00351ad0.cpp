extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00351c60();
void FUN_00351ad0(int arg0);
}

void FUN_00351ad0(int arg0) {
    FUN_00351c60();
    igMetaObject_CreateInstance(*(int *)0x588A90, arg0);
}
