extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c4f00();
void FUN_003c4be0(int arg0);
}

void FUN_003c4be0(int arg0) {
    FUN_003c4f00();
    igMetaObject_CreateInstance(*(int *)0x58BB00, arg0);
}
