typedef struct S_ref { char pad4[4]; int f4; } S_ref;
int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_00529a30[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[32]; };
int igAnimationTransitionDefinition_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *p1;
    S_ref *p2;
    S_ref *t1;
    S_ref *t2;

    igObject_InitHeader(u.b);
    p1 = (S_ref *)&u.b[16];
    p2 = (S_ref *)&u.b[12];
    u.vt = (int)&DAT_00529a30[0];
    *(int *)p2 = 0;
    *(int *)p1 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00529a30[0];
    if (p1 != 0) {
        t1 = *(S_ref **)p1;
        if (t1 != 0) {
            t1->f4 = (int)((int) (t1->f4 - 1));
            if (((unsigned long long) ((long long) t1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t1);
            }
        }
    }
    if (p2 != 0) {
        t2 = *(S_ref **)p2;
        if (t2 != 0) {
            t2->f4 = (int)((int) (t2->f4 - 1));
            if (((unsigned long long) ((long long) t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t2);
            }
        }
    }
    return temp_s0;
}
