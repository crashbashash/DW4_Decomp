extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c2f80();
void FUN_003c2e60(int arg0);
}

void FUN_003c2e60(int arg0) {
    FUN_003c2f80();
    igMetaObject_CreateInstance(*(int *)0x58B740, arg0);
}
