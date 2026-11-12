void FUN_0036dfa0(int arg0) {
    FUN_0036e160();
    igMetaObject_CreateInstance(*(int *)0x58A030, arg0);
}

int FUN_0036dfe0(void) {
    if (((int *)DAT_0058a030)[0] == 0) {
        ((int *)DAT_0058a030)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058a030)[0];
}

void *FUN_0036e030(void) {
    struct G *g = DAT_0058a030[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036e160();
    }
    return DAT_0058a030[0];
}

int be_GetVTable(void) {
    Obj_36e080 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.s = 0;
    obj.vt = &DAT_00539f10[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00539f10[0];
    obj.releaseRef();
    obj.vt = &DAT_00524950[0];
    obj.releaseStr();
    return r;
}

void FUN_0036e160(void)
{
    igMetaObject_RunStaticInit(be_Register);
}

void *be_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_be_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        be_GetMetaObject,
        be_className,
        0x14, /* instance size */
        be_GetVTable,
        be_InitFields,
        0, /* extra callback item */
        g_be_callbackList /* callback list */
    );
}

void be_GetMetaObject(void)
{
    FUN_0036e030();
}

void be_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058a030)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c8238[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002b9120();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c8240[0], &DAT_004c8248[0], &DAT_004c8250[0], temp_s2);
}

