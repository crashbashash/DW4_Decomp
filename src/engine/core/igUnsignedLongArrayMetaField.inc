igMetaObject *igUnsignedLongArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedLongArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b6b10();
    return g_igUnsignedLongArrayMetaField_metaObject[0];
}

int igUnsignedLongArrayMetaField_GetVTable(void) {
    igUnsignedLongArrayMetaField obj;
    char *o;
    int *a1;
    int v0;
    int t;
    FUN_0030eb80((int **)&obj);
    obj._vtable = (int)&DAT_0052e330[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj._vtable = (int)&g_igMetaField_vtable[0];
    if (&obj._fieldName != 0) {
        o = (char *)obj._fieldName;
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

void FUN_002b6b10(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedLongArrayMetaField_Register);
}

void igUnsignedLongArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedLongArrayMetaField_metaObject),
        igUnsignedLongMetaField_Register,
        igUnsignedLongMetaField_GetPublishedMetaObject,
        thunk_igUnsignedLongArrayMetaField_GetMetaObject,
        igUnsignedLongArrayMetaField_className,
        0x38, /* instance size */
        igUnsignedLongArrayMetaField_GetVTable,
        &igUnsignedLongArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igUnsignedLongArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igUnsignedLongArrayMetaField_GetMetaObject(void) {
    igUnsignedLongArrayMetaField_GetMetaObject();
}

igMetaObject *FUN_002b6bb0(void) {
    return g_igUnsignedLongMetaField_metaObject[0];
}

void igUnsignedLongArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igUnsignedLongArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igUnsignedLongArrayMetaField_ctorTable[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igUnsignedLongArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004bf2f8[0], &DAT_004bf300[0], temp_s1);
}

void FUN_002b6c50(void) {
    igUnsignedLongArrayMetaField *temp_s0;
    igUnsignedLongArrayMetaField *p;

    if (g_igUnsignedLongArrayMetaField_descriptor[0] == 0) {
        g_igUnsignedLongArrayMetaField_descriptor[0] = ((igUnsignedLongArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedLongArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        temp_s0 = g_igUnsignedLongArrayMetaField_descriptor[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), (igObject *)temp_s0);
            p = g_igUnsignedLongArrayMetaField_descriptor[0];
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long)(long long)p->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(p);
            }
            g_igUnsignedLongArrayMetaField_descriptor[0]->_internalIndex = FUN_002fc250()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igUnsignedLongArrayMetaField_descriptor[0]);
        }
    }
}

