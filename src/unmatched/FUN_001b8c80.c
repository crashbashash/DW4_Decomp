int FUN_001b7f50();
int FUN_001b85c0();
int Matrix44_Copy();
extern void * DAT_00561928[4];
void FUN_001b8c80(void *self, int arg1) {
    int arg0 = (int)self;
    int temp_v0;
    temp_v0 = FUN_001b7f50(arg1, arg0);
    Matrix44_Copy(arg1 + *(int *)((char *)(DAT_00561928[0]) + 8), temp_v0);
    FUN_001b85c0(temp_v0, arg1, arg0);
}
