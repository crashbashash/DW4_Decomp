igMetaObject *g_beSvConnectCheck_metaObject;

void beSvConnectCheck_Create(int allocator) {
    beSvConnectCheck_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5881D8, allocator);
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
    igObject *q0;
    igObject *q1;
    igObject *q2;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_beSaveApi_vtable[0];
    q2 = (igObject *)&u.b[48];
    *(int *)q2 = 0;
    q1 = (igObject *)&u.b[52];
    *(int *)q1 = 0;
    q0 = (igObject *)&u.b[56];
    *(int *)q0 = 0;
    u.vt = (int)&g_beSvConnectCheck_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beSaveApi_vtable[0];
    if (q0 != 0) {
        q0 = *(igObject **)q0;
        if (q0 != 0) {
            q0->_refCount = (int)q0->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(igObject **)q1;
        if (q1 != 0) {
            q1->_refCount = (int)q1->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q1->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(igObject **)q2;
        if (q2 != 0) {
            q2->_refCount = (int)q2->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q2->_refCount << 0x29) >> 0x29) == 0) {
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

igSmartPointer<igObject> *igSmartPointer_beSaveMemoryObj_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
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

