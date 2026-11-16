igMetaObject *g_igLightStateAttr_metaObject;
igMetaField *g_igLightStateAttr_lightMetaField;
igMetaField *g_igLightStateAttr_enabledMetaField;
igMetaField *g_igLightStateAttr_internalMetaField;

void FUN_001361b0(int arg0) {
    igLightStateAttr_EnsureRegistered();
    igMetaObject_CreateInstance(*(igMetaObject * *)0x55F060, (igMemoryPoolView *)arg0);
}

igMetaObject *FUN_001361f0(void) {
    if (g_igLightStateAttr_metaObject == 0) {
        g_igLightStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igLightStateAttr_metaObject;
}

igMetaObject *igLightStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igLightStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLightStateAttr_EnsureRegistered();
    return g_igLightStateAttr_metaObject;
}

int igLightStateAttr_GetVTable(void) {
    union U_136290 u;
    int t;
    char *o;
    int *a1;
    int v0;
    S_ref *p0, *p1;
    igObject_InitHeader((igObject *)u.b);
    p0 = (S_ref *)&u.b[12];
    p1 = (S_ref *)&u.b[16];
    u.vt = (int)&g_igLightStateAttr_vtable[0];
    *(int *)p0 = 0;
    *(int *)p1 = 0;
    t = *(int *)&u.b[*(int *)((char *)g_objectSystem + 916)];
    u.vt = (int)&g_igLightStateAttr_vtable[0];
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

ObjectRefWord *igSmartPointer_igObject_Destruct(ObjectRefWord *self,int delete_storage) {
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

void igLightStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLightStateAttr_Register);
}

static igMetaObjectCallback g_igLightStateAttr_callbackList[] = { igLightAttr_EnsureRegistered, igObject_EnsureRegistered, 0 };

CallbackArray *igLightStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLightStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igLightStateAttr_GetMetaObject,
        "igLightStateAttr",
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

static FieldFactory g_igLightStateAttr_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igLightStateAttr_fieldTable[] = {
    "_light",
    "_enabled",
    "_internal",
};
static igMetaField **g_igLightStateAttr_fieldHandles[] = {
    &g_igLightStateAttr_lightMetaField,
    &g_igLightStateAttr_enabledMetaField,
    &g_igLightStateAttr_internalMetaField,
};
static int g_igLightStateAttr_fieldOffsets[] = {
    16,
    20,
    12,
};

void igLightStateAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igLightStateAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igLightStateAttr_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00136750();
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_v0)->_metaObject = (int)((int) g_igObject_metaObject[0]);
    ((igMetaField *)temp_v0)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, g_igLightStateAttr_fieldTable, g_igLightStateAttr_fieldHandles, g_igLightStateAttr_fieldOffsets, temp_s2);
}

