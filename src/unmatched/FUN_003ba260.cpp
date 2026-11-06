extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003ba6a0();
void FUN_003ba260(int arg0);
}

void FUN_003ba260(int arg0) {
    FUN_003ba6a0();
    igMetaObject_CreateInstance(*(int *)0x58AF18, arg0);
}
