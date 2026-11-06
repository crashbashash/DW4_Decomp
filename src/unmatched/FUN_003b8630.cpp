extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b8740();
void FUN_003b8630(int arg0);
}

void FUN_003b8630(int arg0) {
    FUN_003b8740();
    igMetaObject_CreateInstance(*(int *)0x58ADF8, arg0);
}
