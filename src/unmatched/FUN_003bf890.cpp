extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bfae0();
void FUN_003bf890(int arg0);
}

void FUN_003bf890(int arg0) {
    FUN_003bfae0();
    igMetaObject_CreateInstance(*(int *)0x58B3A8, arg0);
}
