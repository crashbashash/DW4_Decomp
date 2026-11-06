extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b5640();
void FUN_003b5530(int arg0);
}

void FUN_003b5530(int arg0) {
    FUN_003b5640();
    igMetaObject_CreateInstance(*(int *)0x58ABE8, arg0);
}
