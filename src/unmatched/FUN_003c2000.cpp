extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c2120();
void FUN_003c2000(int arg0);
}

void FUN_003c2000(int arg0) {
    FUN_003c2120();
    igMetaObject_CreateInstance(*(int *)0x58B530, arg0);
}
