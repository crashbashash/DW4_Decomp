extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b6f80();
void FUN_003b6e60(int arg0);
}

void FUN_003b6e60(int arg0) {
    FUN_003b6f80();
    igMetaObject_CreateInstance(*(int *)0x58ACE0, arg0);
}
