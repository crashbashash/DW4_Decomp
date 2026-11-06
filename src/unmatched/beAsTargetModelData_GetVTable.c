int igObject_InitHeader();
int igObject_Destroy();
int StringChunk_ReleaseHeader();
extern int DAT_00524950[4];
extern int DAT_00534540[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[16]; };
int beAsTargetModelData_GetVTable(void) {
    union U u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;
    int *q8;
    int *q12;
    igObject_InitHeader(u.b);
    q8 = (int *)&u.b[8];
    *q8 = 0;
    u.vt = (int)&DAT_00534540[0];
    q12 = (int *)&u.b[12];
    *q12 = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00534540[0];
    if (q12 != 0) {
        o = (char *)*q12;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    u.vt = (int)&DAT_00524950[0];
    if (q8 != 0) {
        temp_v1 = (int *)*q8;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return t;
}
