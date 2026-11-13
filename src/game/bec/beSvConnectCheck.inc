void FUN_00348170(int arg0) {
    FUN_00348530();
    igMetaObject_CreateInstance(*(int *)0x5881D8, arg0);
}

igMetaObject *FUN_003481b0(void) {
    if (g_beSvConnectCheck_metaObject[0] == 0) {
        g_beSvConnectCheck_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSvConnectCheck_metaObject[0];
}

void *FUN_00348200(void) {
    igMetaObject *g = g_beSvConnectCheck_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00348530();
    }
    return g_beSvConnectCheck_metaObject[0];
}

int beSvConnectCheck_GetVTable(void) {
    union U_348250 u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053c070[0];
    q2 = (S_ref *)&u.b[48];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[52];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[56];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_0053bc10[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053c070[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
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
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    return temp_s0;
}

void *FUN_00348390(struct S_348390 *arg0, short arg1) {
    struct R_348390 *p;

    if (arg0 != 0) {
        arg0->f0 = &DAT_0053c070[0];
        if (&arg0->f56) {
            p = arg0->f56;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f52) {
            p = arg0->f52;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f48) {
            p = arg0->f48;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void **FUN_003484b0(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void FUN_00348530(void)
{
    igMetaObject_RunStaticInit(beSvConnectCheck_Register);
}

void *beSvConnectCheck_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvConnectCheck_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvConnectCheck_GetMetaObject,
        beSvConnectCheck_className,
        0x90, /* instance size */
        beSvConnectCheck_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvConnectCheck_GetMetaObject(void)
{
    FUN_00348200();
}

igMetaObject *FUN_003485e0(void) {
    return g_beSaveApi_metaObject[0];
}

