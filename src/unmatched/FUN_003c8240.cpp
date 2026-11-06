extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c8310();

void FUN_003c8240(int arg0) {
    FUN_003c8310();
    igMetaObject_CreateInstance(*(int *)0x58BF20, arg0);
}
}
