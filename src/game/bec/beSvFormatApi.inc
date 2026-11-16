igMetaObject *g_beSvFormatApi_metaObject;

void beSvFormatApi_Create(int allocator) {
    beSvFormatApi_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588270, allocator);
}

void *beSvFormatApi_GetMetaObject(void) {
    igMetaObject *g = g_beSvFormatApi_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvFormatApi_EnsureRegistered();
    }
    return g_beSvFormatApi_metaObject;
}

int beSvFormatApi_GetVTable(void) {
    union U_349900 u;
    int r;
    int *tv1, *ta1;
    int tc1;
    igObject *q2;
    igObject *q1;
    igObject *q3;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_beSaveApi_vtable[0];
    q1 = (igObject *)&u.b[48];
    *(int *)q1 = 0;
    q2 = (igObject *)&u.b[52];
    *(int *)q2 = 0;
    q3 = (igObject *)&u.b[56];
    *(int *)q3 = 0;
    u.vt = (int)&g_beSvFormatApi_vtable[0];
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beSaveApi_vtable[0];
    if (q3 != 0) {
        q3 = *(igObject **)q3;
        if (q3 != 0) {
            q3->_refCount = (int)q3->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q3->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q3);
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
    if (q1 != 0) {
        q1 = *(igObject **)q1;
        if (q1 != 0) {
            q1->_refCount = (int)q1->_refCount - 1;
            if (((unsigned long long) ((long long)(int)q1->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return r;
}

void beSvFormatApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvFormatApi_Register);
}

void *beSvFormatApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvFormatApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvFormatApi_GetMetaObjectFunction,
        "beSvFormatApi",
        0x40, /* instance size */
        beSvFormatApi_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvFormatApi_GetMetaObjectFunction(void)
{
    beSvFormatApi_GetMetaObject();
}

