extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b9680();
void FUN_003b9560(int arg0);
}

void FUN_003b9560(int arg0) {
    FUN_003b9680();
    igMetaObject_CreateInstance(*(int *)0x58AE88, arg0);
}
