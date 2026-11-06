extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c6520();
void FUN_003c6360(int arg0);
}

void FUN_003c6360(int arg0) {
    FUN_003c6520();
    igMetaObject_CreateInstance(*(int *)0x58BD00, arg0);
}
