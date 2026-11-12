void *FUN_002279d0(int arg0) {
    FUN_00227af0();
    return igMetaObject_CreateInstance(*(int *)0x56D980, arg0);
}

igMetaObject *igIterateDerived_GetMetaObject(void)
{
    igMetaObject *g = g_igIterateDerived_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00227af0();
    return g_igIterateDerived_metaObject[0];
}

int igIterateDerived_GetVTable(void) {
    struct F f;
    int **pr;
    int temp_s0;
    int *o;

    igObject_InitHeader(&f);
    f.vt = &DAT_0052c3a0[0];
    pr = &f.ref;
    *pr = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_0052c3a0[0];
    if (pr != 0) {
        if (*pr != 0) {
            o = *pr;
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return temp_s0;
}

void FUN_00227af0(void)
{
    igMetaObject_RunStaticInit(igIterateDerived_Register);
}

void igIterateDerived_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIterateDerived_metaObject,
        igIterator_Register,
        igIterator_GetPublishedMetaObject,
        thunk_igIterateDerived_GetMetaObject,
        igIterateDerived_className,
        0x10, /* instance size */
        igIterateDerived_GetVTable,
        &igIterateDerived_InitFields,
        0, /* extra callback item */
        g_igIterateDerived_callbackList /* callback list */
    );
}

void thunk_igIterateDerived_GetMetaObject(void) {
    igIterateDerived_GetMetaObject();
}

void igIterateDerived_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056d980[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00497db0[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be610();
    igMetaObject_NameFields(temp_s0, &DAT_00497db8[0], &DAT_00497dc0[0], &DAT_00497dc8[0], temp_s2);
}

