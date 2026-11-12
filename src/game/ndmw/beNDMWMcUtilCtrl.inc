void FUN_003c51c0(int arg0) {
    FUN_003c5380();
    igMetaObject_CreateInstance(*(int *)0x58BB80, arg0);
}

int FUN_003c5200(void) {
    if (((int *)DAT_0058bb80)[0] == 0) {
        ((int *)DAT_0058bb80)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058bb80)[0];
}

void *beNDMWMcUtilCtrl_ResolveMetaObject(void) {
    struct G *g = DAT_0058bb80[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c5380();
    }
    return DAT_0058bb80[0];
}

int beNDMWMcUtilCtrl_GetVTable(void) {
    beNDMWMcUtilCtrl obj;
    igObject *o;
    int t;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &DAT_0053cda0[0];
    obj._svData = 0;
    obj._slot = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    *(int **)&obj._vtable = &DAT_0053cda0[0];
    if (&obj._slot != 0) {
        o = (igObject *)obj._slot;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    if (&obj._svData != 0) {
        o = (igObject *)obj._svData;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

void FUN_003c5380(void)
{
    igMetaObject_RunStaticInit(beNDMWMcUtilCtrl_Register);
}

void *beNDMWMcUtilCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMcUtilCtrl_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWMcUtilCtrl_GetMetaObject,
        beNDMWMcUtilCtrl_className,
        0x40, /* instance size */
        beNDMWMcUtilCtrl_GetVTable,
        beNDMWMcUtilCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWMcUtilCtrl_callbackList /* callback list */
    );
}

void beNDMWMcUtilCtrl_GetMetaObject(void)
{
    beNDMWMcUtilCtrl_ResolveMetaObject();
}

void beNDMWMcUtilCtrl_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058bb80)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cb910[0], 0x11);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xB));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0034aeb0();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_003c5910();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004cb960[0], &DAT_004cb9b0[0], &DAT_004cba00[0], temp_s2);
}

