igMetaObject *igMetaFieldInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaFieldInfo_metaObject_00585cb8[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bebb0();
    return g_igMetaFieldInfo_metaObject_00585cb8[0];
}

int igMetaFieldInfo_GetVTable(void) {
    igMetaFieldInfo u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;
    igObject_InitHeader((igObject *)&u);
    ps = (char *)&u._name;
    *(int *)ps = 0;
    u._vtable = (int)&g_igNamedObject_vtable[0];
    u._vtable = (int)&DAT_0052f1c0[0];
    s0 = *(int *)((char *)&u + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    u._vtable = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*a1), (int)a1);
            }
        }
    }
    return s0;
}

void FUN_002bebb0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMetaFieldInfo_Register);
}

void igMetaFieldInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMetaFieldInfo_metaObject_00585cb8),
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igMetaFieldInfo_GetMetaObject,
        igMetaFieldInfo_className,
        0x14, /* instance size */
        igMetaFieldInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMetaFieldInfo_GetMetaObject(void) {
    igMetaFieldInfo_GetMetaObject();
}

int FUN_002bec40(void) {
    if (DAT_00585cc0[0] == 0) {
        DAT_00585cc0[0] = ((int)igMetaEnum_Create((char *)&text_ResetType[0], (char **)&DAT_004bfdd0[0], &DAT_004bfde0[0], 4));
    }
    return DAT_00585cc0[0];
}

