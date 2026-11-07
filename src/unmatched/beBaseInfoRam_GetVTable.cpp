typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; char b[48]; };
extern "C" {
int igObject_Destroy(S_ref *);
int igObject_InitHeader(char *);
extern int DAT_00539e90[4];
extern void * DAT_00586dc8[4];
int beBaseInfoRam_GetVTable(void);
}
int beBaseInfoRam_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *p;

    igObject_InitHeader(u.b);
    p = (S_ref *)&u.b[40];
    u.vt = (int)&DAT_00539e90[0];
    *(int *)p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00539e90[0];
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
