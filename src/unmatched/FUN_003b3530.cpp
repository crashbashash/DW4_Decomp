extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b3640();
void FUN_003b3530(int arg0);
}

void FUN_003b3530(int arg0) {
    FUN_003b3640();
    igMetaObject_CreateInstance(*(int *)0x58AB50, arg0);
}
