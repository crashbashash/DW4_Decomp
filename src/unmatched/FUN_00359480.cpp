extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00359640();
void FUN_00359480(int arg0);
}

void FUN_00359480(int arg0) {
    FUN_00359640();
    igMetaObject_CreateInstance(*(int *)0x5890C0, arg0);
}
