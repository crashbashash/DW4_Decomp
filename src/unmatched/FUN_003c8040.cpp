extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c8110();

void FUN_003c8040(int arg0) {
    FUN_003c8110();
    igMetaObject_CreateInstance(*(int *)0x58BF10, arg0);
}
}
