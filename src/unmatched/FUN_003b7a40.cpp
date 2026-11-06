extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b7b50();
void FUN_003b7a40(int arg0);
}

void FUN_003b7a40(int arg0) {
    FUN_003b7b50();
    igMetaObject_CreateInstance(*(int *)0x58AD80, arg0);
}
