igMetaObject *FUN_0019c6a0(void) {
    if (g_igOverrideAttrSet_metaObject[0] == 0) {
        g_igOverrideAttrSet_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igOverrideAttrSet_metaObject[0];
}

igMetaObject *igOverrideAttrSet_GetMetaObject(void)
{
    igMetaObject *g = g_igOverrideAttrSet_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019c7b0();
    return g_igOverrideAttrSet_metaObject[0];
}

int igOverrideAttrSet_GetVTable(void) {
    struct F f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[1] = 0;
    f.w[2] = 0;
    f.w[3] = 0;
    f.w[6] = 0;
    f.w[7] = 0;
    f.vt = &DAT_0052ac70[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.vt = &DAT_0052ac70[0];
    FUN_0019c0e0((struct S_19c0e0 *)&f, 0);
    return temp_s0;
}

void FUN_0019c7b0(void)
{
    igMetaObject_RunStaticInit(igOverrideAttrSet_Register);
}

void igOverrideAttrSet_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igOverrideAttrSet_metaObject),
        igAttrSet_Register,
        igAttrSet_GetPublishedMetaObject,
        thunk_igOverrideAttrSet_GetMetaObject,
        igOverrideAttrSet_className,
        0x28, /* instance size */
        igOverrideAttrSet_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igOverrideAttrSet_GetMetaObject(void) {
    igOverrideAttrSet_GetMetaObject();
}

struct R **FUN_0019c840(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

