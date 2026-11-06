extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b7200();
void FUN_003b70e0(int arg0);
}

void FUN_003b70e0(int arg0) {
    FUN_003b7200();
    igMetaObject_CreateInstance(*(int *)0x58AD10, arg0);
}
