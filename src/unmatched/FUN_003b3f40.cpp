extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b4190();
void FUN_003b3f40(int arg0);
}

void FUN_003b3f40(int arg0) {
    FUN_003b4190();
    igMetaObject_CreateInstance(*(int *)0x58AB80, arg0);
}
