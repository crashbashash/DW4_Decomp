igMetaObject *FUN_0033ff50(void) {
    if (g_igModelViewMatrixBoneSelectList_metaObject_00587aa0[0] == 0 || !isValid(g_igModelViewMatrixBoneSelectList_metaObject_00587aa0[0])) FUN_0033ffe0();
    return g_igModelViewMatrixBoneSelectList_metaObject_00587aa0[0];
}

int igModelViewMatrixBoneSelectList_587aa0_GetVTable(void) {
    struct Obj_33ffa0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00539ad0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0033ffe0(void)
{
    igMetaObject_RunStaticInit(igModelViewMatrixBoneSelectList_587aa0_Register);
}

void *igModelViewMatrixBoneSelectList_587aa0_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igModelViewMatrixBoneSelectList_metaObject_00587aa0,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igModelViewMatrixBoneSelectList_587aa0_GetMetaObject,
        igModelViewMatrixBoneSelectList_className_2,
        0x14, /* instance size */
        igModelViewMatrixBoneSelectList_587aa0_GetVTable,
        0,
        0, /* extra callback item */
        g_igModelViewMatrixBoneSelectList_587aa0_callbackList /* callback list */
    );
}

void igModelViewMatrixBoneSelectList_587aa0_GetMetaObject(void)
{
    FUN_0033ff50();
}

