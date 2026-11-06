extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00345010();

void FUN_00344e40(int arg0) {
    FUN_00345010();
    igMetaObject_CreateInstance(*(int *)0x587F10, arg0);
}
}
