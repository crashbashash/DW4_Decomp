igMetaObject *igPlane_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igPlane_metaObject[0] != 0) {
        ready = (g_igPlane_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00188520();
done:
    return g_igPlane_metaObject[0];
}

int igPlane_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00527eb0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00188520(void)
{
    igMetaObject_RunStaticInit(igPlane_Register);
}

void igPlane_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPlane_metaObject,
        igVolume_Register,
        igVolume_GetPublishedMetaObject,
        thunk_igPlane_GetMetaObject,
        igPlane_className,
        0x1C, /* instance size */
        igPlane_GetVTable,
        &igPlane_InitFields,
        thunk_FUN_0018c660, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igPlane_GetMetaObject(void) {
    igPlane_GetMetaObject();
}

void igPlane_InitFields(void) {
    int temp_s0;
    int temp_s1;
    void *f;

    temp_s0 = DAT_00560fe0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048ae08[0], 3);
    f = (void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2);
    *(int *)((char *)f + 52) = (int)(&FUN_001869e0);
    igMetaObject_NameFields(temp_s0, &DAT_0048ae18[0], &DAT_0048ae28[0], &DAT_0048ae38[0], temp_s1);
}

void thunk_FUN_0018c660(void) {
    FUN_0018c660();
}

