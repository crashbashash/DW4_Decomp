extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00357d10();
void FUN_003578d0(int arg0);
}

void FUN_003578d0(int arg0) {
    FUN_00357d10();
    igMetaObject_CreateInstance(*(int *)0x588F38, arg0);
}
