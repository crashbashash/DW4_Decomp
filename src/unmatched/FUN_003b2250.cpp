extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b2370();
void FUN_003b2250(int arg0);
}

void FUN_003b2250(int arg0) {
    FUN_003b2370();
    igMetaObject_CreateInstance(*(int *)0x58AA58, arg0);
}
