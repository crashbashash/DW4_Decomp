struct Obj { int *vt; char pad4[4]; void *s; char pad12[52]; };
extern "C" {
int StringChunk_ReleaseHeader(int, int *);
int igObject_InitHeader(struct Obj *);
extern int DAT_00524950[4];
extern int DAT_00534830[4];
extern void * DAT_00586dc8[4];
int beBaseInfoRamTimer_GetVTable(void);
}
int beBaseInfoRamTimer_GetVTable(void) {
    struct Obj o;
    int temp_s0;
    void **q;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    igObject_InitHeader(&o);
    q = &o.s;
    *q = 0;
    o.vt = &DAT_00524950[0];
    o.vt = &DAT_00534830[0];
    temp_s0 = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00524950[0];
    if (q != 0) {
        temp_v1 = *q;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}
