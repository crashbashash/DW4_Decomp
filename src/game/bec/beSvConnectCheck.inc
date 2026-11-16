igMetaObject *g_beSvConnectCheck_metaObject;

void beSvConnectCheck_Create(int arg0) {
    beSvConnectCheck_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5881D8, arg0);
}

igMetaObject *beSvConnectCheck_GetOrCreateMetaObject(void) {
    if (g_beSvConnectCheck_metaObject == 0) {
        g_beSvConnectCheck_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSvConnectCheck_metaObject;
}

void *beSvConnectCheck_GetMetaObject(void) {
    igMetaObject *g = g_beSvConnectCheck_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvConnectCheck_EnsureRegistered();
    }
    return g_beSvConnectCheck_metaObject;
}

int beSvConnectCheck_GetVTable(void) {
    union U_348250 u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_beSaveApi_vtable[0];
    q2 = (S_ref *)&u.b[48];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[52];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[56];
    *(int *)q0 = 0;
    u.vt = (int)&g_beSvConnectCheck_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beSaveApi_vtable[0];
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
        arg0->f0 = &g_beSaveApi_vtable[0];
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
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

void **igSmartPointer_beSaveMemoryObj_Destruct(struct Ref **self, short flag) {
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

void beSvConnectCheck_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvConnectCheck_Register);
}

void *beSvConnectCheck_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvConnectCheck_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvConnectCheck_GetMetaObjectFunction,
        "beSvConnectCheck",
        0x90, /* instance size */
        beSvConnectCheck_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvConnectCheck_GetMetaObjectFunction(void)
{
    beSvConnectCheck_GetMetaObject();
}

igMetaObject *beSaveApi_GetPublishedMetaObject(void) {
    return g_beSaveApi_metaObject;
}

