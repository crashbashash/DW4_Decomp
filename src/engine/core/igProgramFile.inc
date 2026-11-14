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
    *(int **)&obj._vtable = &g_igProgramFile_vtable[0];
    obj._fileName = 0;
    obj._file = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj._vtable = (int)&g_igProgramFile_vtable[0];
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
        0,
        g_igProgramFile_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igProgramFile_GetMetaObjectFunction,
        igProgramFile_className,
        0x10,
        igProgramFile_GetVTable,
        igProgramFile_InitFields,
        0,
        (igMetaObjectCallback *)g_igProgramFile_callbackList
    );
}

void igProgramFile_GetMetaObjectFunction(void) {
    igProgramFile_GetMetaObject();
}

void igProgramFile_InitFields(void) {
    int base;
    void *fileField;
    void *meta;

    ((igMetaObject *)(g_igProgramFile_metaObject[0]))->_persistent = 0;
    meta = (void *)(g_igProgramFile_metaObject[0]);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igProgramFile_ctorTable[0], 2);
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base))))->_persistent = 0;
    fileField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)fileField)->_metaObject = (int)igFile_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)fileField)->_construct = 0;
    ((igObjectRefMetaField *)fileField)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igProgramFile_fieldTable[0], (igMetaField ***)&g_igProgramFile_fieldDescriptors[0], &g_igProgramFile_fieldOffsets[0], base);
    ((igMetaObject *)(g_igProgramFile_metaObject[0]))->_abstractProxy = (int)igElfFile_GetMetaObjectFunction;
}

