extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bbf60();
void FUN_003bbda0(int arg0);
}

void FUN_003bbda0(int arg0) {
    FUN_003bbf60();
    igMetaObject_CreateInstance(*(int *)0x58B060, arg0);
}
