extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00363930();
void FUN_003637c0(int arg0);
}

void FUN_003637c0(int arg0) {
    FUN_00363930();
    igMetaObject_CreateInstance(*(int *)0x5897D8, arg0);
}
