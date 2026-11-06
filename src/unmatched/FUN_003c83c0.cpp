extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c8490();

void FUN_003c83c0(int arg0) {
    FUN_003c8490();
    igMetaObject_CreateInstance(*(int *)0x58BF28, arg0);
}
}
