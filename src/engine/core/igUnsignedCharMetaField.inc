void FUN_002b73e0(int arg0) {
    igUnsignedCharMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585760), (MemoryPool *)arg0);
}

igMetaObject *igUnsignedCharMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedCharMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedCharMetaField_EnsureRegistered();
    return g_igUnsignedCharMetaField_metaObject[0];
}

int igUnsignedCharMetaField_GetVTable(void) {
    struct Obj_2b7470 obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igMetaField_Init((igMetaField *)&obj);
    obj.vt = &DAT_0052e530[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
    obj.vt = &DAT_0052f230[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*a1), (int)a1);
            }
        }
    }
    return t;
}

void igUnsignedCharMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedCharMetaField_Register);
}

void igUnsignedCharMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedCharMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igUnsignedCharMetaField_GetMetaObject,
        igUnsignedCharMetaField_className,
        0x34, /* instance size */
        igUnsignedCharMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igUnsignedCharMetaField_callbackList /* callback list */
    );
}

void thunk_igUnsignedCharMetaField_GetMetaObject(void) {
    igUnsignedCharMetaField_GetMetaObject();
}

void FUN_002b7590(void) {
    void *temp_s0;

    if (DAT_00585768[0] == 0) {
        DAT_00585768[0] = (void *)(((void *)igMetaObject_CreateInstance((CreateMeta *)DAT_00585760[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))))));
        temp_s0 = (void *)(DAT_00585768[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((void *)FUN_002fc250())), (RefHeader *)temp_s0);
            {
                void *held = (void *)DAT_00585768[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_00585768[0]) + 18) = (short) (*(int *)((char *)(((void *)FUN_002fc250())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00585768[0]);
        }
    }
}

int igUnsignedCharMetaField_GetDefaultDescriptor(void) {
    if (g_igUnsignedCharMetaField_descriptor[0] == 0) {
        igUnsignedCharMetaField_EnsureRegistered();
    }
    return g_igUnsignedCharMetaField_descriptor[0];
}

