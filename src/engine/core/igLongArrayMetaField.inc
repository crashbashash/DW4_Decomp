igMetaObject *igLongArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igLongArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c1d90();
    return g_igLongArrayMetaField_metaObject[0];
}

int igLongArrayMetaField_GetVTable(void) {
    igLongArrayMetaField o;
    int r;
    char *p;
    int *hdr;
    int c;

    igMetaField_Init((igMetaField *)&o);
    o._vtable = (int)&DAT_0052fb50[0];
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        p = (char *)o._fieldName;
        if (p != 0) {
            hdr = (int *)(p - 8);
            c = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*hdr), (int)hdr);
            }
        }
    }
    return r;
}

void FUN_002c1d90(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igLongArrayMetaField_Register);
}

void igLongArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igLongArrayMetaField_metaObject),
        igLongMetaField_Register,
        igLongMetaField_GetPublishedMetaObject,
        thunk_igLongArrayMetaField_GetMetaObject,
        igLongArrayMetaField_className,
        0x38, /* instance size */
        igLongArrayMetaField_GetVTable,
        &igLongArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igLongArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igLongArrayMetaField_GetMetaObject(void) {
    igLongArrayMetaField_GetMetaObject();
}

igMetaObject *FUN_002c1e30(void) {
    return g_igLongMetaField_metaObject[0];
}

void igLongArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igLongArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igLongArrayMetaField_ctorTable[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igLongArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004c0500[0], &DAT_004c0508[0], temp_s1);
}

void FUN_002c1ed0(void) {
    igLongArrayMetaField *temp_s0;
    igLongArrayMetaField *p;

    if (g_igLongArrayMetaField_descriptor[0] == 0) {
        g_igLongArrayMetaField_descriptor[0] = ((igLongArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igLongArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        temp_s0 = g_igLongArrayMetaField_descriptor[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), (igObject *)temp_s0);
            p = g_igLongArrayMetaField_descriptor[0];
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            *(short *)((char *)(g_igLongArrayMetaField_descriptor[0]) + 18) = (short) (FUN_002fc250()->_count - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igLongArrayMetaField_descriptor[0]);
        }
    }
}

