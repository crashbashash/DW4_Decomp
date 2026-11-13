void FUN_001361b0(int arg0) {
    FUN_00136470();
    igMetaObject_CreateInstance(*(int *)0x55F060, arg0);
}

igMetaObject *FUN_001361f0(void) {
    if (g_igLightStateAttr_metaObject[0] == 0) {
        g_igLightStateAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igLightStateAttr_metaObject[0];
}

igMetaObject *igLightStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igLightStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00136470();
    return g_igLightStateAttr_metaObject[0];
}

int igLightStateAttr_GetVTable(void) {
    union U_136290 u;
    int t;
    char *o;
    int *a1;
    int v0;
    S_ref *p0, *p1;
    igObject_InitHeader(u.b);
    p0 = (S_ref *)&u.b[12];
    p1 = (S_ref *)&u.b[16];
    u.vt = (int)&DAT_00523670[0];
    *(int *)p0 = 0;
    *(int *)p1 = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00523670[0];
    if (p1 != 0) {
        p1 = *(S_ref **)p1;
        if (p1 != 0) {
            p1->f4 = (int)((int) (p1->f4 - 1));
            if (((unsigned long long) ((long long) p1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p1);
            }
        }
    }
    if (p0 != 0) {
        p0 = *(S_ref **)p0;
        if (p0 != 0) {
            p0->f4 = (int)((int) (p0->f4 - 1));
            if (((unsigned long long) ((long long) p0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p0);
            }
        }
    }
    return t;
}

ObjectRefWord *FUN_00136370(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

ObjectRefWord *ObjectRef_Destruct_001363f0(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void FUN_00136470(void)
{
    igMetaObject_RunStaticInit(igLightStateAttr_Register);
}

void igLightStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLightStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igLightStateAttr_GetMetaObject,
        igLightStateAttr_className,
        0x18, /* instance size */
        igLightStateAttr_GetVTable,
        &igLightStateAttr_InitFields,
        0, /* extra callback item */
        g_igLightStateAttr_callbackList /* callback list */
    );
}

void thunk_igLightStateAttr_GetMetaObject(void) {
    igLightStateAttr_GetMetaObject();
}

void igLightStateAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igLightStateAttr_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igLightStateAttr_ctorTable[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00136750();
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_v0)->_metaObject = (int)((int) g_igObject_metaObject[0]);
    ((igMetaField *)temp_v0)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &g_igLightStateAttr_fieldTable[0], &DAT_00486340[0], &DAT_00486350[0], temp_s2);
}

