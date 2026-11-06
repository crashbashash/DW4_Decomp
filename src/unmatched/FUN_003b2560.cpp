extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b2680();
void FUN_003b2560(int arg0);
}

void FUN_003b2560(int arg0) {
    FUN_003b2680();
    igMetaObject_CreateInstance(*(int *)0x58AAB8, arg0);
}
