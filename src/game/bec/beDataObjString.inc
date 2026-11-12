void FUN_00364a90(int arg0) {
    FUN_00364bf0();
    igMetaObject_CreateInstance(*(int *)0x589878, arg0);
}

void *FUN_00364ad0(void) {
    igMetaObject *g = g_beDataObjString_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00364bf0();
    }
    return g_beDataObjString_metaObject[0];
}

int beDataObjString_GetVTable(void) {
    beDataObjString obj;
    int temp_s1;
    int *q2;
    int *q3;
    int *temp_a1;
    int *temp_a1_2;
    int temp_v0;
    int temp_v0_2;
    void *temp_v1;
    void *temp_v1_2;

    igObject_InitHeader(&obj);
    q2 = &obj._name;
    *q2 = 0;
    obj._vtable = (int)(&DAT_005353b0[0]);
    q3 = &obj._data;
    *q3 = 0;
    temp_s1 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)(&DAT_005353b0[0]);
    if (q3 != 0) {
        temp_v1 = (void *)*q3;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    obj._vtable = (int)(&DAT_00524950[0]);
    if (q2 != 0) {
        temp_v1_2 = (void *)*q2;
        if (temp_v1_2 != 0) {
            temp_a1_2 = (int *)((char *)temp_v1_2 - 8);
            temp_v0_2 = *(int *)((char *)(temp_v1_2) - 4) - 1;
            *(int *)((char *)(temp_v1_2) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
            }
        }
    }
    return temp_s1;
}

void FUN_00364bf0(void)
{
    igMetaObject_RunStaticInit(beDataObjString_Register);
}

void *beDataObjString_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjString_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjString_GetMetaObject,
        beDataObjString_className,
        0x10, /* instance size */
        beDataObjString_GetVTable,
        beDataObjString_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beDataObjString_GetMetaObject(void)
{
    FUN_00364ad0();
}

void beDataObjString_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beDataObjString_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7188[0], 1);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1)), 0);
    igMetaObject_NameFields(temp_s0, &DAT_004c7190[0], &DAT_004c7198[0], &DAT_004c71a0[0], temp_s1);
}

