extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c3680();
void FUN_003c3560(int arg0);
}

void FUN_003c3560(int arg0) {
    FUN_003c3680();
    igMetaObject_CreateInstance(*(int *)0x58B890, arg0);
}
