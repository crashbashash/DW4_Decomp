void beNDMWShinkaObject_CreateInstance(int arg0) {
    FUN_003c9ac0();
    igMetaObject_CreateInstance(*(int *)0x58BFF0, arg0);
}

igMetaObject *beNDMWShinkaObject_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWShinkaObject_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_003c9ac0();
    return g_beNDMWShinkaObject_metaObject[0];
}

int beNDMWShinkaObject_GetVTable(void) {
    struct Obj_3c9a30 obj;
    char *o;
    int *a1;
    int v0;
    int t;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053c5b0[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053c5b0[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void FUN_003c9ac0(void)
{
    igMetaObject_RunStaticInit(beNDMWShinkaObject_Register);
}

void *beNDMWShinkaObject_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShinkaObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWShinkaObject_GetMetaObject,
        beNDMWShinkaObject_className,
        0x54, /* instance size */
        beNDMWShinkaObject_GetVTable,
        beNDMWShinkaObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShinkaObject_GetMetaObject(void)
{
    beNDMWShinkaObject_ResolveMetaObject();
}

void beNDMWShinkaObject_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWShinkaObject_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc210[0], 0x13);
    igMetaObject_NameFields(temp_s0, &DAT_004cc260[0], &DAT_004cc2b0[0], &DAT_004cc300[0], temp_s1);
}

