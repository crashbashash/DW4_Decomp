extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c1de0();
void FUN_003c1ca0(int arg0);
}

void FUN_003c1ca0(int arg0) {
    FUN_003c1de0();
    igMetaObject_CreateInstance(*(int *)0x58B520, arg0);
}
