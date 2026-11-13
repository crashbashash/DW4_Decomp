void bePlaySE_CreateInstance(int arg0) {
    FUN_00344890();
    igMetaObject_CreateInstance(*(int *)0x587ED0, arg0);
}

void *FUN_00344800(void) {
    igMetaObject *g = g_bePlaySE_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00344890();
    }
    return g_bePlaySE_metaObject[0];
}

int bePlaySE_GetVTable(void) {
    int tmp[8];
    int off;

    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_00539220[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_00344890(void)
{
    igMetaObject_RunStaticInit(bePlaySE_Register);
}

void *bePlaySE_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_bePlaySE_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        bePlaySE_GetMetaObject,
        bePlaySE_className,
        0x18, /* instance size */
        bePlaySE_GetVTable,
        bePlaySE_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void bePlaySE_GetMetaObject(void)
{
    FUN_00344800();
}

void bePlaySE_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_bePlaySE_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_bePlaySE_ctorTable[0], 2);
    igMetaObject_NameFields(temp_s0, &g_bePlaySE_fieldTable[0], &DAT_004c39d8[0], &DAT_004c39e0[0], temp_s1);
}

