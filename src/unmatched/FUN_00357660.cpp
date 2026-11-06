extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00357820();
void FUN_00357660(int arg0);
}

void FUN_00357660(int arg0) {
    FUN_00357820();
    igMetaObject_CreateInstance(*(int *)0x588F30, arg0);
}
