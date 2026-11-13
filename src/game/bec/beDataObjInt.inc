void beDataObjInt_Create(int arg0) {
    FUN_00365680();
    igMetaObject_CreateInstance(*(int *)0x5898B8, arg0);
}

igMetaObject *FUN_00365550(void) {
    if (g_beDataObjInt_metaObject[0] == 0) {
        g_beDataObjInt_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beDataObjInt_metaObject[0];
}

void *FUN_003655a0(void) {
    igMetaObject *g = g_beDataObjInt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00365680();
    }
    return g_beDataObjInt_metaObject[0];
}

int beDataObjInt_GetVTable(void) {
    union U_3655f0 u;
    int temp_s0;
    int temp_v0;
    int *temp_a1;
    int *temp_v1;
    char *q0;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_igNamedObject_vtable[0];
    q0 = &u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00535230[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q0 != 0) {
        temp_v1 = *(int **)q0;
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

void FUN_00365680(void)
{
    igMetaObject_RunStaticInit(beDataObjInt_Register);
}

void *beDataObjInt_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjInt_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjInt_GetMetaObject,
        beDataObjInt_className,
        0x10, /* instance size */
        beDataObjInt_GetVTable,
        beDataObjInt_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beDataObjInt_GetMetaObject(void)
{
    FUN_003655a0();
}

void beDataObjInt_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beDataObjInt_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beDataObjInt_ctorTable[0], 1);
    igMetaObject_NameFields(temp_s0, &g_beDataObjInt_fieldTable[0], &DAT_004c7228[0], &DAT_004c7230[0], temp_s1);
}

