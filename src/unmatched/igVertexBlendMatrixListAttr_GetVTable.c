int igMatrix44f_SetIdentity();
int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_00522640[4];
extern int DAT_00522630[8];
extern void * DAT_00586dc8[4];
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; char b[160]; };
int igVertexBlendMatrixListAttr_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    int pi = (int)u.b;
    igObject_InitHeader(pi);
    u.vt = (int)&DAT_00522640[0];
    q0 = (S_ref *)&u.b[24];
    *(int *)q0 = 0;
    igMatrix44f_SetIdentity(&u.b[28]);
    igMatrix44f_SetIdentity(pi + 92);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00522630[4];
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
