void beUnicodeObj_Create(int arg0) {
    FUN_00361610();
    igMetaObject_CreateInstance(*(int *)0x589640, arg0);
}

igMetaObject *FUN_00361530(void) {
    igMetaObject *g = g_beUnicodeObj_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_00361610();
    return g_beUnicodeObj_metaObject[0];
}

int beUnicodeObj_GetVTable(void) {
    union U_361580 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_0053a560[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
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

void FUN_00361610(void)
{
    igMetaObject_RunStaticInit(beUnicodeObj_Register);
}

void *beUnicodeObj_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beUnicodeObj_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beUnicodeObj_GetMetaObject,
        beUnicodeObj_className,
        0x10, /* instance size */
        beUnicodeObj_GetVTable,
        beUnicodeObj_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beUnicodeObj_GetMetaObject(void)
{
    FUN_00361530();
}

void beUnicodeObj_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beUnicodeObj_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beUnicodeObj_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igMemoryRefMetaField *)temp_s1)->_memType = FUN_002b6330();
    igMetaObject_NameFields(temp_s0, &g_beUnicodeObj_fieldTable[0], &DAT_004c6c88[0], &DAT_004c6c90[0], temp_s2);
}

