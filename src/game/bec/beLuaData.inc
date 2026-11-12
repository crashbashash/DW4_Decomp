igMetaObject *FUN_0035b150(void) {
    igMetaObject *g = g_beLuaData_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_0035b280();
done:
    return g_beLuaData_metaObject[0];
}

int beLuaData_GetVTable(void) {
    struct Obj_35b1a0 obj;
    char *o;
    igObject *io;
    int *a1;
    int v0;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00536890[0];
    obj.w3 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00536890[0];
    if (&obj.w3 != 0) {
        io = obj.w3;
        if (io != 0) {
            io->_refCount = io->_refCount - 1;
            if ((io->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(io);
            }
        }
    }
    obj.vt = &DAT_00524950[0];
    if (&obj.w2 != 0) {
        o = obj.w2;
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

void FUN_0035b280(void)
{
    igMetaObject_RunStaticInit(beLuaData_Register);
}

void *beLuaData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLuaData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beLuaData_GetMetaObject,
        beLuaData_className,
        0x10, /* instance size */
        beLuaData_GetVTable,
        beLuaData_InitFields,
        0, /* extra callback item */
        g_beLuaData_callbackList /* callback list */
    );
}

void beLuaData_GetMetaObject(void)
{
    FUN_0035b150();
}

void beLuaData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beLuaData_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6290[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0035b510();
    igMetaObject_NameFields(temp_s0, &DAT_004c6298[0], &DAT_004c62a0[0], &DAT_004c62a8[0], temp_s2);
}

