extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00335c10();

void FUN_00335b40(int arg0) {
    FUN_00335c10();
    igMetaObject_CreateInstance(*(int *)0x587760, arg0);
}
}
