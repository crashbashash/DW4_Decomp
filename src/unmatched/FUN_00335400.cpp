extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00335520();

void FUN_00335400(int arg0) {
    FUN_00335520();
    igMetaObject_CreateInstance(*(int *)0x587730, arg0);
}
}
