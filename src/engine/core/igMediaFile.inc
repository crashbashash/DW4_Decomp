igMetaObject *igMediaFile_GetMetaObject(void)
{
    igMetaObject *g = g_igMediaFile_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMediaFile_EnsureRegistered();
    return g_igMediaFile_metaObject[0];
}

int igMediaFile_GetVTable(void) {
    igMediaFile file;
    int temp_s0;
    char *ps;
    igObject_InitHeader((igObject *)&file);
    file._name = 0;
    file._fileName = 0;
    file._completeFilename = 0;
    file._vtable = (int)&DAT_0052f9a0[0];
    ps = (char *)&file._media;
    *(int *)ps = 0;
    temp_s0 = *(int *)((char *)&file + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    file._vtable = (int)&DAT_0052f9a0[0];
    igSmartPointer_igMedia_Destruct((void **)ps, -1);
    igFile_Destroy((igFile *)&file, 0);
    return temp_s0;
}

void **igSmartPointer_igMedia_Destruct(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void igMediaFile_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMediaFile_Register);
}

void igMediaFile_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMediaFile_metaObject),
        igFile_Register,
        igFile_GetPublishedMetaObject,
        igMediaFile_GetMetaObjectFunction,
        igMediaFile_className,
        0x44, /* instance size */
        igMediaFile_GetVTable,
        &igMediaFile_InitFields,
        0, /* extra callback item */
        g_igMediaFile_callbackList /* callback list */
    );
}

void igMediaFile_GetMetaObjectFunction(void) {
    igMediaFile_GetMetaObject();
}

void igMediaFile_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igMediaFile_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igMediaFile_ctorTable[0], 9);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 7)));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 8)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igMedia_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igMediaFile_fieldTable[0], (igMetaField ***)&DAT_004c0440[0], &DAT_004c0470[0], temp_s2);
}

