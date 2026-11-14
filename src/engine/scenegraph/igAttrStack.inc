int FUN_001a5a70(int arg0) {
    FUN_001a5b90();
    return igMetaObject_CreateInstance(*(int *)0x562030, arg0);
}

igMetaObject *igAttrStack_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrStack_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a5b90();
    return g_igAttrStack_metaObject[0];
}

int igAttrStack_GetVTable(void) {
    union U_1a5b00 u;
    void **q5;
    int temp_s0;
    void *temp_a0;

    igObject_InitHeader(u.b);
    q5 = &u.p[5];
    u.w[0] = (int)(&DAT_0052a160[0]);
    *q5 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_0052a160[0]);
    if (q5 != 0) {
        temp_a0 = *q5;
        if (temp_a0 != 0) {
            *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_a0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
    }
    return temp_s0;
}

void FUN_001a5b90(void)
{
    igMetaObject_RunStaticInit(igAttrStack_Register);
}

void igAttrStack_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAttrStack_metaObject),
        igNonRefCountedObjectStack_Register,
        igNonRefCountedObjectStack_GetPublishedMetaObject,
        thunk_igAttrStack_GetMetaObject,
        igAttrStack_className,
        0x34, /* instance size */
        igAttrStack_GetVTable,
        &igAttrStack_InitFields,
        0, /* extra callback item */
        g_igAttrStack_callbackList /* callback list */
    );
}

void thunk_igAttrStack_GetMetaObject(void) {
    igAttrStack_GetMetaObject();
}

void igAttrStack_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAttrStack_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igAttrStack_ctorTable[0], 8);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0013b070();
    igIntMetaField_SetDefault(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)), -1);
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0013b070();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6)));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0013b070();
    ((igObjectRefMetaField *)temp_s1_3)->_refCounted = 0;
    temp_s1_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7)));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = (int)FUN_00197af0();
    ((igObjectRefMetaField *)temp_s1_4)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &g_igAttrStack_fieldTable[0], &DAT_0048cdd0[0], &DAT_0048cdf0[0], temp_s2);
}

