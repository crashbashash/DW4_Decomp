extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00364170();
void FUN_00364050(int arg0);
}

void FUN_00364050(int arg0) {
    FUN_00364170();
    igMetaObject_CreateInstance(*(int *)0x589840, arg0);
}
