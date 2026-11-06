extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00362170();
void FUN_00361e50(int arg0);
}

void FUN_00361e50(int arg0) {
    FUN_00362170();
    igMetaObject_CreateInstance(*(int *)0x589678, arg0);
}
