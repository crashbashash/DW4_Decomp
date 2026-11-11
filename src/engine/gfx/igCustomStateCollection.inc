void FUN_0014efb0(int arg0) {
    FUN_0014f0c0();
    igMetaObject_CreateInstance(*(int *)0x55FE70, arg0);
}

igMetaObject *igCustomStateCollection_GetMetaObject(void)
{
    igMetaObject *g = g_igCustomStateCollection_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014f0c0();
    return g_igCustomStateCollection_metaObject[0];
}

int igCustomStateCollection_GetVTable(void) {
    struct W o;
    int r;
    int *p; int *a1; int t;
    igObject_InitHeader(&o);
    o.vt = DAT_00526d10;
    *(int *)((char *)&o + 20) = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = DAT_00526d10;
    if (&*(int *)((char *)&o + 20) != 0) { p = *(int **)((char *)&o + 20); if (p != 0) { a1 = p - 2; t = p[-1] - 1; p[-1] = t; if (t == 0) StringChunk_ReleaseHeader(*a1, a1); } }
    return r;
}

void FUN_0014f0c0(void)
{
    igMetaObject_RunStaticInit(igCustomStateCollection_Register);
}

void igCustomStateCollection_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCustomStateCollection_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCustomStateCollection_GetMetaObject,
        igCustomStateCollection_className,
        0x1C, /* instance size */
        igCustomStateCollection_GetVTable,
        &igCustomStateCollection_InitFields,
        0, /* extra callback item */
        g_igCustomStateCollection_callbackList /* callback list */
    );
}

void thunk_igCustomStateCollection_GetMetaObject(void) {
    igCustomStateCollection_GetMetaObject();
}

void igCustomStateCollection_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055fe70[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00489050[0], 2);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1), &DAT_004dc870[0]);
    igMetaObject_NameFields(temp_s0, &DAT_00489058[0], &DAT_00489060[0], &DAT_00489068[0], temp_s1);
}

