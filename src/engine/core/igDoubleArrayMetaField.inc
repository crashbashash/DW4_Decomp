igMetaObject *igDoubleArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igDoubleArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDoubleArrayMetaField_EnsureRegistered();
    return g_igDoubleArrayMetaField_metaObject[0];
}

int igDoubleArrayMetaField_GetVTable(void) {
    igDoubleArrayMetaField o;
    int r;
    int *s;
    int *h;
    int c;
    igMetaField_Init((igMetaField *)&o);
    o._vtable = (int)&DAT_00530790[0];
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        s = (int *)o._fieldName;
        if (s != 0) {
            h = s - 2;
            c = s[-1] - 1;
            s[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader((StringChunk *)(*h), (int)h);
        }
    }
    return r;
}

void igDoubleArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDoubleArrayMetaField_Register);
}

void igDoubleArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igDoubleArrayMetaField_metaObject),
        igDoubleMetaField_Register,
        igDoubleMetaField_GetPublishedMetaObject,
        igDoubleArrayMetaField_GetMetaObjectFunction,
        igDoubleArrayMetaField_className,
        0x38, /* instance size */
        igDoubleArrayMetaField_GetVTable,
        &igDoubleArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igDoubleArrayMetaField_callbackList /* callback list */
    );
}

void igDoubleArrayMetaField_GetMetaObjectFunction(void) {
    igDoubleArrayMetaField_GetMetaObject();
}

igMetaObject *igDoubleMetaField_GetPublishedMetaObject(void) {
    return g_igDoubleMetaField_metaObject[0];
}

void igDoubleArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igDoubleArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igDoubleArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igDoubleArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004c10d8[0], &DAT_004c10e0[0], temp_s1);
}

void igDoubleArrayMetaField_CreateDefaultDescriptor(void) {
    igDoubleArrayMetaField *temp_s0;
    igDoubleArrayMetaField *p;
    int len;

    if (g_igDoubleArrayMetaField_descriptor[0] == 0) {
        g_igDoubleArrayMetaField_descriptor[0] = ((igDoubleArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igDoubleArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        temp_s0 = g_igDoubleArrayMetaField_descriptor[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)temp_s0);
            p = g_igDoubleArrayMetaField_descriptor[0];
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            len = igMetaField_GetMetaFieldList()->_count;
            g_igDoubleArrayMetaField_descriptor[0]->_internalIndex = len - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igDoubleArrayMetaField_descriptor[0]);
        }
    }
}

