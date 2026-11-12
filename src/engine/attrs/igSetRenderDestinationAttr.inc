igMetaObject *FUN_00133b70(void) {
    if (g_igSetRenderDestinationAttr_metaObject[0] == 0) {
        g_igSetRenderDestinationAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igSetRenderDestinationAttr_metaObject[0];
}

igMetaObject *igSetRenderDestinationAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igSetRenderDestinationAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00133d20();
    return g_igSetRenderDestinationAttr_metaObject[0];
}

int igSetRenderDestinationAttr_GetVTable(void) {
    union U_133c10 u;
    void **q3;
    int temp_s0;
    void *temp_a0;

    igObject_InitHeader(u.b);
    q3 = &u.p[3];
    u.w[0] = (int)(&DAT_00522f50[0]);
    *q3 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00522f50[0]);
    if (q3 != 0) {
        temp_a0 = *q3;
        if (temp_a0 != 0) {
            *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_a0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

ObjectRefWord *FUN_00133ca0(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void FUN_00133d20(void)
{
    igMetaObject_RunStaticInit(igSetRenderDestinationAttr_Register);
}

void igSetRenderDestinationAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSetRenderDestinationAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igSetRenderDestinationAttr_GetMetaObject,
        igSetRenderDestinationAttr_className,
        0x10, /* instance size */
        igSetRenderDestinationAttr_GetVTable,
        &igSetRenderDestinationAttr_InitFields,
        0, /* extra callback item */
        g_igSetRenderDestinationAttr_callbackList /* callback list */
    );
}

void thunk_igSetRenderDestinationAttr_GetMetaObject(void) {
    igSetRenderDestinationAttr_GetMetaObject();
}

void igSetRenderDestinationAttr_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igSetRenderDestinationAttr_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485f40[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_001341f0();
    igMetaObject_NameFields(temp_s0, &DAT_00485f48[0], &DAT_00485f50[0], &DAT_00485f58[0], temp_s2);
}

