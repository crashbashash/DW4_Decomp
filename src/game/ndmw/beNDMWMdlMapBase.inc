void FUN_003c0f30(int arg0) {
    FUN_003c1070();
    igMetaObject_CreateInstance(*(int *)0x58B4A0, arg0);
}

int FUN_003c0f70(void) {
    if (((int *)DAT_0058b4a0)[0] == 0) {
        ((int *)DAT_0058b4a0)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058b4a0)[0];
}

igMetaObject *beNDMWMdlMapBase_GetReadyMetaObject(void)
{
    igMetaObject *g = DAT_0058b4a0[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003c1070();
    return DAT_0058b4a0[0];
}

int beNDMWMdlMapBase_GetVTable(void) {
    struct Obj_3c1010 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f18 = 0;
    obj.vt = (&DAT_00540a70[0]);
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_00540a70[0]);
    FUN_003bf2f0((struct NamedRefObject *)&obj, (long long)0);
    return temp_s0;
}

void FUN_003c1070(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlMapBase_Register);
}

void *beNDMWMdlMapBase_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlMapBase_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlMapBase_GetMetaObject,
        beNDMWMdlMapBase_className,
        0x2c, /* instance size */
        beNDMWMdlMapBase_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlMapBase_GetMetaObject(void)
{
    beNDMWMdlMapBase_GetReadyMetaObject();
}

