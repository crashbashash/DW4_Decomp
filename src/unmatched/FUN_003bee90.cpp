extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bf050();
void FUN_003bee90(int arg0);
}

void FUN_003bee90(int arg0) {
    FUN_003bf050();
    igMetaObject_CreateInstance(*(int *)0x58B358, arg0);
}
