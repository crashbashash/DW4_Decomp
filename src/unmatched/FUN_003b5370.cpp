extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b5480();
void FUN_003b5370(int arg0);
}

void FUN_003b5370(int arg0) {
    FUN_003b5480();
    igMetaObject_CreateInstance(*(int *)0x58ABE0, arg0);
}
