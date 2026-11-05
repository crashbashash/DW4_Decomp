typedef struct S_ref { char pad4[4]; int f4; } S_ref;
int igObject_Destroy();
int StringChunk_ReleaseHeader();
int igObject_InitHeader();
extern int DAT_00523670[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[32]; };
int igLightStateAttr_GetVTable(void) {
    union U u;
    int t;
    char *o;
    int *a1;
    int v0;
    S_ref *p0, *p1;
    igObject_InitHeader(u.b);
    p0 = (S_ref *)&u.b[12];
    p1 = (S_ref *)&u.b[16];
    u.vt = (int)&DAT_00523670[0];
    *(int *)p0 = 0;
    *(int *)p1 = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00523670[0];
    if (p1 != 0) {
        p1 = *(S_ref **)p1;
        if (p1 != 0) {
            p1->f4 = (int)((int) (p1->f4 - 1));
            if (((unsigned long long) ((long long) p1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p1);
            }
        }
    }
    if (p0 != 0) {
        p0 = *(S_ref **)p0;
        if (p0 != 0) {
            p0->f4 = (int)((int) (p0->f4 - 1));
            if (((unsigned long long) ((long long) p0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p0);
            }
        }
    }
    return t;
}
