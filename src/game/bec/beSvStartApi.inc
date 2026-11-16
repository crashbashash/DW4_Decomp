igMetaObject *g_beSvStartApi_metaObject;
int g_beSvStartApi_orderTypeStorage;

void beSvStartApi_Create(int allocator) {
    beSvStartApi_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5881F0, allocator);
}

igMetaObject *beSvStartApi_GetMetaObject(void)
{
    igMetaObject *g = g_beSvStartApi_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beSvStartApi_EnsureRegistered();
    return g_beSvStartApi_metaObject;
}

int beSvStartApi_GetVTable(void) {
    union U_3489c0 u;
    int r;

    int *v1; int *a1; int v0; int *a0;
    char *pc; char *pb; char *pa;
    igObject_InitHeader(u.b);
    u.vt = (int)&g_beSaveApi_vtable[0];
    pa = &u.b[48];
    *(int *)pa = 0;
    pb = &u.b[52];
    *(int *)pb = 0;
    pc = &u.b[56];
    *(int *)pc = 0;
    u.vt = (int)&g_beSvStartApi_vtable[0];
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beSaveApi_vtable[0];
    if (pc != 0) {
        a0 = *(int **)pc;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    if (pb != 0) {
        a0 = *(int **)pb;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    if (pa != 0) {
        a0 = *(int **)pa;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    return r;
}

void beSvStartApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvStartApi_Register);
}

void *beSvStartApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvStartApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvStartApi_GetMetaObjectFunction,
        "beSvStartApi",
        0x40, /* instance size */
        beSvStartApi_GetVTable,
        beSvStartApi_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvStartApi_GetMetaObjectFunction(void)
{
    beSvStartApi_GetMetaObject();
}

void beSvStartApi_InitFields(void) {
    int index;
    void *meta;
    void **found;
    igIntMetaField *clone;

    meta = (void *)g_beSvStartApi_metaObject;
    found = (void **)(igMetaObject_FindFieldByName(meta, "_orderType"));
    index = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, found);
    clone = (igIntMetaField *)(((DW4VC_84_1 *)(found))->vX((int)(1)));
    igIntMetaField_SetDefault(clone, 0xA);
    clone->_externalEnumStorage = (int)(&g_beSvStartApi_orderTypeStorage);
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
}

