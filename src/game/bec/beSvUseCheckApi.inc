igMetaObject *g_beSvUseCheckApi_metaObject;

void beSvUseCheckApi_Create(int allocator) {
    beSvUseCheckApi_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588268, allocator);
}

void *beSvUseCheckApi_GetMetaObject(void) {
    igMetaObject *g = g_beSvUseCheckApi_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvUseCheckApi_EnsureRegistered();
    }
    return g_beSvUseCheckApi_metaObject;
}

int beSvUseCheckApi_GetVTable(void) {
    union U_349680 u;
    int temp_s2;
    igObject *qb;
    igObject *qa;
    igObject *qc;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&g_beSaveApi_vtable[0]);
    qa = (igObject *)&u.b[48];
    *(int *)qa = 0;
    qb = (igObject *)&u.b[52];
    *(int *)qb = 0;
    qc = (igObject *)&u.b[56];
    *(int *)qc = 0;
    u.w[0] = (int)(&g_beSvUseCheckApi_vtable[0]);
    temp_s2 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beSaveApi_vtable[0]);
    if (qc != 0) {
        qc = *(igObject **)qc;
        if (qc != 0) {
            qc->_refCount = (int)qc->_refCount - 1;
            if (((unsigned long long) ((long long)(int)qc->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(qc);
            }
        }
    }
    if (qb != 0) {
        qb = *(igObject **)qb;
        if (qb != 0) {
            qb->_refCount = (int)qb->_refCount - 1;
            if (((unsigned long long) ((long long)(int)qb->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(qb);
            }
        }
    }
    if (qa != 0) {
        qa = *(igObject **)qa;
        if (qa != 0) {
            qa->_refCount = (int)qa->_refCount - 1;
            if (((unsigned long long) ((long long)(int)qa->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(qa);
            }
        }
    }
    return temp_s2;
}

void beSvUseCheckApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvUseCheckApi_Register);
}

void *beSvUseCheckApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvUseCheckApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvUseCheckApi_GetMetaObjectFunction,
        "beSvUseCheckApi",
        0x4c, /* instance size */
        beSvUseCheckApi_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvUseCheckApi_GetMetaObjectFunction(void)
{
    beSvUseCheckApi_GetMetaObject();
}

