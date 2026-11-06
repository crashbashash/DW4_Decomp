extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003b3850();
void FUN_003b36f0(int arg0);
}

void FUN_003b36f0(int arg0) {
    FUN_003b3850();
    igMetaObject_CreateInstance(*(int *)0x58AB58, arg0);
}
