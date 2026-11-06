extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b9ed0();
void FUN_003b9db0(int arg0);
}

void FUN_003b9db0(int arg0) {
    FUN_003b9ed0();
    igMetaObject_CreateInstance(*(int *)0x58AEF8, arg0);
}
