extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00363d60();
void FUN_00363c20(int arg0);
}

void FUN_00363c20(int arg0) {
    FUN_00363d60();
    igMetaObject_CreateInstance(*(int *)0x5897F8, arg0);
}
