extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003ba140();
void FUN_003ba030(int arg0);
}

void FUN_003ba030(int arg0) {
    FUN_003ba140();
    igMetaObject_CreateInstance(*(int *)0x58AF08, arg0);
}
