extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c0c90();
void FUN_003c0b50(int arg0);
}

void FUN_003c0b50(int arg0) {
    FUN_003c0c90();
    igMetaObject_CreateInstance(*(int *)0x58B490, arg0);
}
