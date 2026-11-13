void FUN_003c13f0(int arg0) {
    FUN_003c15b0();
    igMetaObject_CreateInstance(*(int *)0x58B4C0, arg0);
}

igMetaObject *beNDMWMdlItemInfoWork_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlItemInfoWork_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_003c15b0();
done:
    return g_beNDMWMdlItemInfoWork_metaObject[0];
}

int beNDMWMdlItemInfoWork_GetVTable(void) {
    ItemInfoWork work;
    return *(int *)((char *)&work + *(int *)((char *)g_objectSystem[0] + 916));
}

void **FUN_003c1520(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

int *FUN_003c15a0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void FUN_003c15b0(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlItemInfoWork_Register);
}

void *beNDMWMdlItemInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlItemInfoWork_metaObject,
        beModelCtrlInfoWork_Register,
        beModelCtrlInfoWork_GetPublishedMetaObject,
        beNDMWMdlItemInfoWork_GetMetaObject,
        beNDMWMdlItemInfoWork_className,
        0x10c, /* instance size */
        beNDMWMdlItemInfoWork_GetVTable,
        beNDMWMdlItemInfoWork_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlItemInfoWork_callbackList /* callback list */
    );
}

void beNDMWMdlItemInfoWork_GetMetaObject(void)
{
    beNDMWMdlItemInfoWork_GetReadyMetaObject();
}

void beNDMWMdlItemInfoWork_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWMdlItemInfoWork_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNDMWMdlItemInfoWork_ctorTable[0], 8);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003c92c0();
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), -1);
    igMetaObject_NameFields(temp_s0, &g_beNDMWMdlItemInfoWork_fieldTable[0], &DAT_004cabc0[0], &DAT_004cabe0[0], temp_s2);
}

