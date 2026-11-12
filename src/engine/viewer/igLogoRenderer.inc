void FUN_0045dbe0(int arg0) {
    FUN_0045dd20();
    igMetaObject_CreateInstance(*(int *)0x58CDF0, arg0);
}

SigLogoRenderer_GetMetaObject *igLogoRenderer_GetMetaObject(void) {
    if (((SigLogoRenderer_GetMetaObject *)g_igLogoRenderer_metaObject[0]) == 0 || !((SigLogoRenderer_GetMetaObject *)g_igLogoRenderer_metaObject[0])->ok()) FUN_0045dd20();
    return ((SigLogoRenderer_GetMetaObject *)g_igLogoRenderer_metaObject[0]);
}

int igLogoRenderer_GetVTable(void) {
    struct Obj_45dc70 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00542230[0];
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)g_objectSystem[0])) + 916));
    obj.vt = &DAT_00542230[0];
    FUN_0013bfe0(&obj.w8, -1);
    FUN_0019ab10(&obj.w7, -1);
    FUN_001353b0(&obj.w6, -1);
    FUN_00230f70(&obj, 0);
    return t;
}

void FUN_0045dd20(void)
{
    igMetaObject_RunStaticInit(igLogoRenderer_Register);
}

void igLogoRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLogoRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igLogoRenderer_GetMetaObject,
        igLogoRenderer_className,
        0x28, /* instance size */
        igLogoRenderer_GetVTable,
        &igLogoRenderer_InitFields,
        0, /* extra callback item */
        g_igLogoRenderer_callbackList /* callback list */
    );
}

void thunk_igLogoRenderer_GetMetaObject(void) {
    igLogoRenderer_GetMetaObject();
}

void igLogoRenderer_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_igLogoRenderer_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d18e0[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00137850();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00138f20();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0013af00();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d18f0[0], &DAT_004d1900[0], &DAT_004d1910[0], temp_s2);
}

