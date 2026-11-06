extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003497c0();
void FUN_003495f0(int arg0);
}

void FUN_003495f0(int arg0) {
    FUN_003497c0();
    igMetaObject_CreateInstance(*(int *)0x588268, arg0);
}
