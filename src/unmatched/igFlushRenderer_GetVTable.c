typedef struct S_ref { char pad4[4]; int f4; } S_ref;
int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_0052ca80[4];
extern int DAT_0052d060[4];
extern void * DAT_00586dc8[4];
union U { int vt; int w[3]; char b[12]; };
int igFlushRenderer_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q1;
    
    
    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_0052d060[0]);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&DAT_0052ca80[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0052d060[0]);
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s0;
}
