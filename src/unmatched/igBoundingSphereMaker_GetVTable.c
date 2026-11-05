typedef struct S_ref { char pad4[4]; int f4; } S_ref;
int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_0052d230[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[16]; };
int igBoundingSphereMaker_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *p;

    igObject_InitHeader(u.b);
    p = (S_ref *)&u.b[8];
    u.vt = (int)&DAT_0052d230[0];
    *(int *)p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052d230[0];
    if (p != 0) {
        p = *(S_ref **)p;
        if (p != 0) {
            p->f4 = (int)((int) (p->f4 - 1));
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    return temp_s0;
}
