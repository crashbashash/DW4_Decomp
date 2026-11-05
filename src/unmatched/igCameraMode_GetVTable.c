typedef struct S_ref { char pad4[4]; int f4; } S_ref;
int igMatrix44f_SetIdentity();
int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_005428d0[4];
extern int DAT_00542960[4];
extern void * DAT_00586dc8[4];
union U { int vt; int w[21]; char b[84]; };
int igCameraMode_GetVTable(void) {
    union U u;
    int temp_s1;
    S_ref *q1;
    S_ref *q2;
    
    
    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00542960[0]);
    igMatrix44f_SetIdentity(&u.w[3]);
    u.w[0] = (int)(&DAT_005428d0[0]);
    q1 = (S_ref *)&u.b[76];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[80];
    *(int *)q2 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_005428d0[0]);
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s1;
}
