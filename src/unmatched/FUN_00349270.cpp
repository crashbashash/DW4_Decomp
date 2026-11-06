extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00349430();
void FUN_00349270(int arg0);
}

void FUN_00349270(int arg0) {
    FUN_00349430();
    igMetaObject_CreateInstance(*(int *)0x588238, arg0);
}
