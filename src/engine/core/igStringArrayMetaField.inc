igMetaObject *g_igStringArrayMetaField_metaObject;
int *g_igStringArrayMetaField_descriptor;
igMetaField *g_igStringArrayMetaField_numMetaField;

igMetaObject *igStringArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igStringArrayMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igStringArrayMetaField_EnsureRegistered();
    return g_igStringArrayMetaField_metaObject;
}

int igStringArrayMetaField_GetVTable(void) {
    igStringArrayMetaField o;
    int r;
    char *p;
    int *hdr;
    int c;

    igStringMetaField_Init((igStringMetaField *)&o);
    o._vtable = (int)&g_igStringArrayMetaField_vtable[0];
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        p = (char *)o._fieldName;
        if (p != 0) {
            hdr = (int *)(p - 8);
            c = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*hdr), (StringTokenHeader *)hdr);
            }
        }
    }
    return r;
}

void igStringArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igStringArrayMetaField_Register);
}

static igMetaObjectCallback g_igStringArrayMetaField_callbackList[] = { igStringArrayMetaField_CreateDefaultDescriptor, 0 };

CallbackArray *igStringArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igStringArrayMetaField_metaObject,
        igStringMetaField_Register,
        igStringMetaField_GetPublishedMetaObject,
        igStringArrayMetaField_GetMetaObjectFunction,
        "igStringArrayMetaField",
        0x40,
        igStringArrayMetaField_GetVTable,
        igStringArrayMetaField_InitFields,
        0,
        g_igStringArrayMetaField_callbackList
    );
}

void igStringArrayMetaField_GetMetaObjectFunction(void) {
    igStringArrayMetaField_GetMetaObject();
}

igMetaObject *igStringMetaField_GetPublishedMetaObject(void) {
    return g_igStringMetaField_metaObject;
}

static FieldFactory g_igStringArrayMetaField_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igStringArrayMetaField_fieldTable[] = {
    "_num",
};
static igMetaField **g_igStringArrayMetaField_fieldDescriptors[] = {
    &g_igStringArrayMetaField_numMetaField,
};
static int g_igStringArrayMetaField_fieldOffsets[] = {
    60,
};

void igStringArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igStringArrayMetaField_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igStringArrayMetaField_ctorTable, 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igStringArrayMetaField_fieldTable, g_igStringArrayMetaField_fieldDescriptors, g_igStringArrayMetaField_fieldOffsets, base);
}


void igStringArrayMetaField_CreateDefaultDescriptor(void) {
    int *s0;
    int *g;

    if (g_igStringArrayMetaField_descriptor == 0) {
        g_igStringArrayMetaField_descriptor = ((int *)igMetaObject_CreateInstance((igMetaObject *)g_igStringArrayMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        s0 = g_igStringArrayMetaField_descriptor;
        if (s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)s0);
            g = g_igStringArrayMetaField_descriptor;
            g[1] = g[1] - 1;
            if ((g[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(g);
            }
            *(short *)((char *)g_igStringArrayMetaField_descriptor + 18) = (short)(((int *)igMetaField_GetMetaFieldList())[3] - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igStringArrayMetaField_descriptor);
        }
    }
}

