extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c3300();
void FUN_003c31e0(int arg0);
}

void FUN_003c31e0(int arg0) {
    FUN_003c3300();
    igMetaObject_CreateInstance(*(int *)0x58B800, arg0);
}
