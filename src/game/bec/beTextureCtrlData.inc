void *FUN_00342090(void) {
    struct G *g = DAT_00587ca8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003421c0();
    }
    return DAT_00587ca8[0];
}

int beTextureCtrlData_GetVTable(void) {
    beTextureCtrlData obj;
    char *o;
    int *a1;
    int v0;
    int t;

    igObject_InitHeader(&obj);
    obj._name = 0;
    *(int **)&obj._vtable = &DAT_00539560[0];
    obj._tex = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    *(int **)&obj._vtable = &DAT_00539560[0];
    if (&obj._tex != 0) {
        o = (char *)obj._tex;
        if (o != 0) {
            ((igObject *)o)->_refCount = ((igObject *)o)->_refCount - 1;
            if ((((igObject *)o)->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    *(int **)&obj._vtable = &DAT_00524950[0];
    if (&obj._name != 0) {
        o = (char *)obj._name;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void FUN_003421c0(void)
{
    igMetaObject_RunStaticInit(beTextureCtrlData_Register);
}

void *beTextureCtrlData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTextureCtrlData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beTextureCtrlData_GetMetaObject,
        beTextureCtrlData_className,
        0x10, /* instance size */
        beTextureCtrlData_GetVTable,
        beTextureCtrlData_InitFields,
        0, /* extra callback item */
        g_beTextureCtrlData_callbackList /* callback list */
    );
}

void beTextureCtrlData_GetMetaObject(void)
{
    FUN_00342090();
}

void beTextureCtrlData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00587ca8)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c34c0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00132ba0();
    igMetaObject_NameFields(temp_s0, &DAT_004c34c8[0], &DAT_004c34d0[0], &DAT_004c34d8[0], temp_s2);
}

