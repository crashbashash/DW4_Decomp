typedef struct S_ref { char pad4[4]; int f4; } S_ref;
int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_0052d060[4];
extern int DAT_00540c80[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[16]; };
int igClearRenderer_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;

    igObject_InitHeader(u.b);
    q0 = (S_ref *)&u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_0052d060[0];
    u.vt = (int)&DAT_00540c80[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052d060[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s0;
}
