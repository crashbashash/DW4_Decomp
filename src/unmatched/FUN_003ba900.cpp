extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003ba9f0();
void FUN_003ba900(int arg0);
}

void FUN_003ba900(int arg0) {
    FUN_003ba9f0();
    igMetaObject_CreateInstance(*(int *)0x58AF28, arg0);
}
