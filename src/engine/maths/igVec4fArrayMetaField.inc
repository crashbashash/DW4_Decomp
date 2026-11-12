void FUN_00187560(int arg0) {
    FUN_00187680();
    igMetaObject_CreateInstance(*(int *)0x560F48, arg0);
}

igMetaObject *igVec4fArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igVec4fArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00187680();
    return g_igVec4fArrayMetaField_metaObject[0];
}

int igVec4fArrayMetaField_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igMetaField_Init(u.b);
    u.vt = (int)&DAT_005273e0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052f230[0];
    ps = &u.b[12];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_00187680(void)
{
    igMetaObject_RunStaticInit(igVec4fArrayMetaField_Register);
}

void igVec4fArrayMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVec4fArrayMetaField_metaObject,
        igVec4fMetaField_Register,
        igVec4fMetaField_GetPublishedMetaObject,
        thunk_igVec4fArrayMetaField_GetMetaObject,
        igVec4fArrayMetaField_className,
        0x38, /* instance size */
        igVec4fArrayMetaField_GetVTable,
        &igVec4fArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igVec4fArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igVec4fArrayMetaField_GetMetaObject(void) {
    igVec4fArrayMetaField_GetMetaObject();
}

int FUN_00187720(void) {
    return DAT_00560f38[0];
}

void igVec4fArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00560f48[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048ad70[0], 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048ad78[0], &DAT_0048ad80[0], &DAT_0048ad88[0], temp_s1);
}

void FUN_001877c0(void) {
    M *temp_s0;
    M *o;
    int t;

    if (DAT_00560f50[0] == 0) {
        DAT_00560f50[0] = igMetaObject_CreateInstance(DAT_00560f48[0], Memory_GetAllocatorBySelector(DAT_00587040[0]));
        temp_s0 = DAT_00560f50[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            o = DAT_00560f50[0];
            o->f4 = o->f4 - 1;
            if ((o->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
            t = FUN_002fc250()->f12 - 1;
            DAT_00560f50[0]->f18 = t;
            igMetaField_FinalizeDescriptor(DAT_00560f50[0]);
        }
    }
}

