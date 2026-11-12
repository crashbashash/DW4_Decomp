void FUN_003495f0(int arg0) {
    FUN_003497c0();
    igMetaObject_CreateInstance(*(int *)0x588268, arg0);
}

void *FUN_00349630(void) {
    struct G *g = DAT_00588268[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003497c0();
    }
    return DAT_00588268[0];
}

int beSvUseCheckApi_GetVTable(void) {
    union U_349680 u;
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

void FUN_003497c0(void)
{
    igMetaObject_RunStaticInit(beSvUseCheckApi_Register);
}

void *beSvUseCheckApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvUseCheckApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvUseCheckApi_GetMetaObject,
        beSvUseCheckApi_className,
        0x4c, /* instance size */
        beSvUseCheckApi_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvUseCheckApi_GetMetaObject(void)
{
    FUN_00349630();
}

