igMetaObject *FUN_0014bde0(void)
{
    unsigned char ready;
    if (g_igPrimLengthArray1_1_metaObject[0] != 0) {
        ready = (g_igPrimLengthArray1_1_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_0014be70();
done:
    return g_igPrimLengthArray1_1_metaObject[0];
}

int igPrimLengthArray1_1_GetVTable(void) {
    struct Obj_14be30 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00526590[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0014be70(void)
{
    igMetaObject_RunStaticInit(igPrimLengthArray1_1_Register);
}

void igPrimLengthArray1_1_Register(void) {
    FUN_00149bc0();  /* Set-once guard that first runs the sibling registrars it chains to. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPrimLengthArray1_1_metaObject,
        igPrimLengthArray_Register,
        igPrimLengthArray_GetPublishedMetaObject,
        thunk_FUN_0014bde0,
        igPrimLengthArray1_1_className,
        0x14, /* instance size */
        igPrimLengthArray1_1_GetVTable,
        &igPrimLengthArray1_1_InitFields,
        0,                                                 /* static-initializer callback item (appended on fresh configuration) */
        0                                                  /* 0-terminated dependency-callback list */
    );
}

void thunk_FUN_0014bde0(void) {
    FUN_0014bde0();
}

igMetaObject *FUN_0014bf00(void) {
    return g_igPrimLengthArray_metaObject[0];
}

void igPrimLengthArray1_1_InitFields(void) {
    void **temp_v0;
    T_14bf10 *temp_s0;
    int temp_s2;
    void *temp_s1;

    temp_s1 = (void *)(g_igPrimLengthArray1_1_metaObject[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_004dbec8[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = ((DW4VC_84_1 *)(temp_v0))->vX(1);
    temp_s0->f60 = igUnsignedIntMetaField_GetDefaultDescriptor();
    temp_s0->f56 = 0;
    igMemoryRefMetaField_SetDefaultWord(temp_s0, 0);
    temp_s0->f53 = 1;
    temp_s0->f64 = 1;
    temp_s0->f65 = 1;
    temp_s0->f28 = (int)(&DAT_0055fb08[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    temp_s0->ref -= 1;
    if ((temp_s0->ref & 0x7fffff) == 0) {
        igObject_Destroy(temp_s0);
    }
}

