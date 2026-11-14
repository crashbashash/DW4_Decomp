igMetaObject *igProgramFile_GetMetaObject(void)
{
    igMetaObject *g = g_igProgramFile_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igProgramFile_EnsureRegistered();
    return g_igProgramFile_metaObject[0];
}

int igProgramFile_GetVTable(void) {
    igProgramFile obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igObject_InitHeader((igObject *)&obj);
    *(int **)&obj._vtable = &DAT_0052e010[0];
    obj._fileName = 0;
    obj._file = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj._vtable = (int)&DAT_0052e010[0];
    if (&obj._file != 0) {
        o = (char *)obj._file;
        if (o != 0) {
            ((igObject *)o)->_refCount = ((igObject *)o)->_refCount - 1;
            if ((((igObject *)o)->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    if (&obj._fileName != 0) {
        o = (char *)obj._fileName;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*a1), (int)a1);
            }
        }
    }
    return t;
}

void igProgramFile_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igProgramFile_Register);
}

void igProgramFile_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igProgramFile_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igProgramFile_GetMetaObjectFunction,
        igProgramFile_className,
        0x10, /* instance size */
        igProgramFile_GetVTable,
        &igProgramFile_InitFields,
        0, /* extra callback item */
        g_igProgramFile_callbackList /* callback list */
    );
}

void igProgramFile_GetMetaObjectFunction(void) {
    igProgramFile_GetMetaObject();
}

void igProgramFile_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    ((igMetaObject *)(g_igProgramFile_metaObject[0]))->_persistent = 0;
    temp_s0 = (void *)(g_igProgramFile_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igProgramFile_ctorTable[0], 2);
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2))))->_persistent = 0;
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igFile_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_construct = 0;
    ((igObjectRefMetaField *)temp_s1)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igProgramFile_fieldTable[0], (igMetaField ***)&DAT_004c1b18[0], &DAT_004c1b20[0], temp_s2);
    ((igMetaObject *)(g_igProgramFile_metaObject[0]))->_abstractProxy = (int)igElfFile_GetMetaObjectFunction;
}

