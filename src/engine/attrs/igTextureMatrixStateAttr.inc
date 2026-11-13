void FUN_001315d0(int arg0) {
    FUN_001316a0();
    igMetaObject_CreateInstance(*(int *)0x55ECC0, arg0);
}

igMetaObject *igTextureMatrixStateAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureMatrixStateAttr_metaObject[0] != 0) {
        ready = (g_igTextureMatrixStateAttr_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_001316a0();
done:
    return g_igTextureMatrixStateAttr_metaObject[0];
}

int igTextureMatrixStateAttr_GetVTable(void) {
    struct Obj_131660 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005228f0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001316a0(void)
{
    igMetaObject_RunStaticInit(igTextureMatrixStateAttr_Register);
}

void igTextureMatrixStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureMatrixStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureMatrixStateAttr_GetMetaObject,
        igTextureMatrixStateAttr_className,
        0x14, /* instance size */
        igTextureMatrixStateAttr_GetVTable,
        &igTextureMatrixStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTextureMatrixStateAttr_GetMetaObject(void) {
    igTextureMatrixStateAttr_GetMetaObject();
}

void igTextureMatrixStateAttr_InitFields(void) {
    igMetaObject *temp_s0;
    int temp_s1;
    struct F *f;

    temp_s0 = g_igTextureMatrixStateAttr_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igTextureMatrixStateAttr_ctorTable[0], 2);
    f = (struct F *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    f->f48 = (int *)FUN_00141620;
    igMetaObject_NameFields(temp_s0, &g_igTextureMatrixStateAttr_fieldTable[0], &DAT_00485b08[0], &DAT_00485b10[0], temp_s1);
}

