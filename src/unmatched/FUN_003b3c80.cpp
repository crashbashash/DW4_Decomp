extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b3d90();
void FUN_003b3c80(int arg0);
}

void FUN_003b3c80(int arg0) {
    FUN_003b3d90();
    igMetaObject_CreateInstance(*(int *)0x58AB70, arg0);
}
