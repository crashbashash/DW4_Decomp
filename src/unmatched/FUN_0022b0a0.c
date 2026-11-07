int igMatrix44f_SetIdentity();
int FUN_001904f0();
int igObject_IsKindOf();
int Matrix44_Copy();
extern int DAT_005612b0[4];
struct TransformObjectList { char pad[8]; int n; int pad2; int **data; };
void FUN_0022b0a0(int arg0, int *arg1) {
    int sp60[16];
    unsigned int n, i;
    int *o;
    struct TransformObjectList *l;
    igMatrix44f_SetIdentity(sp60);
    n = *(int *)(arg1[3] + 8);
    for (i = 0; i < n; i++) {
        o = ((struct TransformObjectList *)arg1[3])->data[i];
        if (igObject_IsKindOf(o, DAT_005612b0[0]) != 0) {
            FUN_001904f0(sp60, (int)o + 0x20, sp60);
        }
    }
    Matrix44_Copy(arg0, sp60);
}
