extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b7470();
void FUN_003b7360(int arg0);
}

void FUN_003b7360(int arg0) {
    FUN_003b7470();
    igMetaObject_CreateInstance(*(int *)0x58AD20, arg0);
}
