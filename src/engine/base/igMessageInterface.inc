igMetaObject *FUN_002260d0(void) {
    if (g_igMessageInterface_metaObject[0] == 0) {
        g_igMessageInterface_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igMessageInterface_metaObject[0];
}

igMetaObject *igMessageInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageInterface_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00226200();
    return g_igMessageInterface_metaObject[0];
}

int igMessageInterface_GetVTable(void) {
    struct W o;
    int r;
    struct Ref *p;
    igObject_InitHeader(&o);
    o.vt = DAT_0052bf30;
    *(int *)((char *)&o + 32) = 0;
    r = *(int *)((char *)&o + *(int *)(g_objectSystem[0] + 916));
    o.vt = DAT_0052bf30;
    if (&*(int *)((char *)&o + 32) != 0) { p = *(struct Ref **)((char *)&o + 32); if (p != 0) { p->u.w = p->u.w - 1; if (p->u.b.cnt == 0) igObject_Destroy(p); } }
    return r;
}

void FUN_00226200(void)
{
    igMetaObject_RunStaticInit(igMessageInterface_Register);
}

void igMessageInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageInterface_metaObject,
        igInterface_Register,
        igInterface_GetPublishedMetaObject,
        thunk_igMessageInterface_GetMetaObject,
        igMessageInterface_className,
        0x24, /* instance size */
        igMessageInterface_GetVTable,
        &igMessageInterface_InitFields,
        0, /* extra callback item */
        g_igMessageInterface_callbackList /* callback list */
    );
}

void thunk_igMessageInterface_GetMetaObject(void) {
    igMessageInterface_GetMetaObject();
}

void igMessageInterface_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igMessageInterface_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igMessageInterface_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00226340();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_igMessageInterface_fieldTable[0], &DAT_00497c48[0], &DAT_00497c50[0], temp_s2);
}

