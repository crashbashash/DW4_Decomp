typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; int w[4]; void *p[4]; char b[80]; };
extern "C" {
int igObject_Destroy(S_ref *);
int igObject_InitHeader(char *);
extern int DAT_0053beb0[4];
extern int DAT_0053c070[4];
extern void * DAT_00586dc8[4];
int beSvUseCheckApi_GetVTable(void);
}
int beSvUseCheckApi_GetVTable(void) {
    union U u;
    int temp_s2;
    S_ref *qb;
    S_ref *qa;
    S_ref *qc;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_0053c070[0]);
    qa = (S_ref *)&u.b[48];
    *(int *)qa = 0;
    qb = (S_ref *)&u.b[52];
    *(int *)qb = 0;
    qc = (S_ref *)&u.b[56];
    *(int *)qc = 0;
    u.w[0] = (int)(&DAT_0053beb0[0]);
    temp_s2 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0053c070[0]);
    if (qc != 0) {
        qc = *(S_ref **)qc;
        if (qc != 0) {
            qc->f4 = (int)((int) (qc->f4 - 1));
            if (((unsigned long long) ((long long) qc->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(qc);
            }
        }
    }
    if (qb != 0) {
        qb = *(S_ref **)qb;
        if (qb != 0) {
            qb->f4 = (int)((int) (qb->f4 - 1));
            if (((unsigned long long) ((long long) qb->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(qb);
            }
        }
    }
    if (qa != 0) {
        qa = *(S_ref **)qa;
        if (qa != 0) {
            qa->f4 = (int)((int) (qa->f4 - 1));
            if (((unsigned long long) ((long long) qa->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(qa);
            }
        }
    }
    return temp_s2;
}
