extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003ba850();
void FUN_003ba760(int arg0);
}

void FUN_003ba760(int arg0) {
    FUN_003ba850();
    igMetaObject_CreateInstance(*(int *)0x58AF20, arg0);
}
