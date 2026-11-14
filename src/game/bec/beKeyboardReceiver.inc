igMetaObject *FUN_0035d070(void) {
    if (g_beKeyboardReceiver_metaObject[0] == 0) {
        g_beKeyboardReceiver_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beKeyboardReceiver_metaObject[0];
}

igMetaObject *FUN_0035d0c0(void) {
    igMetaObject *g = g_beKeyboardReceiver_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_0035d1a0();
    return g_beKeyboardReceiver_metaObject[0];
}

int beKeyboardReceiver_GetVTable(void) {
    struct W_35d110 o;
    int r;
    struct Ref *p;

    igObject_InitHeader(&o);
    o.vt = DAT_0053a8b0;
    *(int *)((char *)&o + 8) = 0;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = DAT_0053a8b0;
    if (&*(int *)((char *)&o + 8) != 0) { p = *(struct Ref **)((char *)&o + 8); if (p != 0) { p->u.w = p->u.w - 1; if (p->u.b.cnt == 0) igObject_Destroy(p); } }
    return r;
}

void FUN_0035d1a0(void)
{
    igMetaObject_RunStaticInit(beKeyboardReceiver_Register);
}

void *beKeyboardReceiver_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beKeyboardReceiver_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        beKeyboardReceiver_GetMetaObject,
        beKeyboardReceiver_className,
        0xc, /* instance size */
        beKeyboardReceiver_GetVTable,
        beKeyboardReceiver_InitFields,
        0, /* extra callback item */
        g_beKeyboardReceiver_callbackList /* callback list */
    );
}

void beKeyboardReceiver_GetMetaObject(void)
{
    FUN_0035d0c0();
}

void beKeyboardReceiver_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beKeyboardReceiver_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beKeyboardReceiver_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igBoolList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beKeyboardReceiver_fieldTable[0], &DAT_004c6540[0], &DAT_004c6548[0], temp_s2);
}

