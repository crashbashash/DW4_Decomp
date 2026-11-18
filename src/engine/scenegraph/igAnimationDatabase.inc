igMetaObject *g_igAnimationDatabase_metaObject;
igMetaField *g_igAnimationDatabase_skeletonListMetaField;
igMetaField *g_igAnimationDatabase_animationListMetaField;
igMetaField *g_igAnimationDatabase_skinListMetaField;
igMetaField *g_igAnimationDatabase_appearanceListMetaField;
igMetaField *g_igAnimationDatabase_combinerListMetaField;

igMetaObject *igAnimationDatabase_GetOrCreateMetaObject(void) {
    if (g_igAnimationDatabase_metaObject == 0) {
        g_igAnimationDatabase_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAnimationDatabase_metaObject;
}

igMetaObject *igAnimationDatabase_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationDatabase_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationDatabase_EnsureRegistered();
    return g_igAnimationDatabase_metaObject;
}

int igAnimationDatabase_GetVTable(void) {
    struct W_1a7820 o;
    int *p19;
    int *p18;
    int *p17;
    int *p16;
    int r;
    igObject_InitHeader((igObject *)&o);
    o.f[1] = 0;
    o.vt = &g_igAnimationDatabase_vtable[0];
    p16 = &o.f[4];
    *p16 = 0;
    p17 = &o.f[5];
    *p17 = 0;
    p18 = &o.f[6];
    *p18 = 0;
    p19 = &o.f[7];
    *p19 = 0;
    o.f[8] = 0;
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = &g_igAnimationDatabase_vtable[0];
    igSmartPointer_igAnimationCombinerList_Destruct((void * *)&o.f[8], -1);
    igSmartPointer_igAppearanceList_Destruct((igSmartPointer<igObject> *)p19, -1);
    igSmartPointer_igSkinList_Destruct((struct Ref * *)p18, -1);
    igSmartPointer_igAnimationList_Destruct((void * *)p17, -1);
    igSmartPointer_igSkeletonList_Destruct((ObjectRefWord *)p16, -1);
    igInfo_Destroy((igInfo *)&o, 0);
    return r;
}

ObjectRefWord *igSmartPointer_igSkeletonList_Destruct(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

void **igSmartPointer_igAnimationList_Destruct(void **arg0, short arg1) {
    S_temp_a0_1a7980 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_1a7980 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

igSmartPointer<igObject> *igSmartPointer_igAppearanceList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

void **igSmartPointer_igAnimationCombinerList_Destruct(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy((igObject *)r);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void igAnimationDatabase_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationDatabase_Register);
}

static igMetaObjectCallback g_igAnimationDatabase_callbackList[] = { igSkeletonList_EnsureRegistered, igAnimationList_EnsureRegistered, igSkinList_EnsureRegistered, igAppearanceList_EnsureRegistered, igAnimationCombinerList_EnsureRegistered, 0 };

CallbackArray *igAnimationDatabase_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationDatabase_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        igAnimationDatabase_GetMetaObjectFunction,
        "igAnimationDatabase",
        0x28, /* instance size */
        igAnimationDatabase_GetVTable,
        &igAnimationDatabase_InitFields,
        0, /* extra callback item */
        g_igAnimationDatabase_callbackList /* callback list */
    );
}

void igAnimationDatabase_GetMetaObjectFunction(void) {
    igAnimationDatabase_GetMetaObject();
}

static FieldFactory g_igAnimationDatabase_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igAnimationDatabase_fieldTable[] = {
    "_skeletonList",
    "_animationList",
    "_skinList",
    "_appearanceList",
    "_combinerList",
};
static igMetaField **g_igAnimationDatabase_fieldHandles[] = {
    &g_igAnimationDatabase_skeletonListMetaField,
    &g_igAnimationDatabase_animationListMetaField,
    &g_igAnimationDatabase_skinListMetaField,
    &g_igAnimationDatabase_appearanceListMetaField,
    &g_igAnimationDatabase_combinerListMetaField,
};
static int g_igAnimationDatabase_fieldOffsets[] = {
    20,
    24,
    28,
    32,
    36,
};

void igAnimationDatabase_InitFields(void) {
    int base;
    void *skeletonListField;
    void *animationListField;
    void *skinListField;
    void *appearanceListField;
    void *combinerListField;
    void *meta;

    meta = (void *)g_igAnimationDatabase_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igAnimationDatabase_ctorTable, 5);
    skeletonListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)skeletonListField)->_metaObject = (int)igSkeletonList_GetOrCreateMetaObject();
    ((igRefMetaField *)skeletonListField)->_construct = 1;
    animationListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)animationListField)->_metaObject = (int)igAnimationList_GetOrCreateMetaObject();
    ((igRefMetaField *)animationListField)->_construct = 1;
    skinListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)skinListField)->_metaObject = (int)igSkinList_GetOrCreateMetaObject();
    ((igRefMetaField *)skinListField)->_construct = 1;
    appearanceListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igObjectRefMetaField *)appearanceListField)->_metaObject = (int)igAppearanceList_GetOrCreateMetaObject();
    ((igRefMetaField *)appearanceListField)->_construct = 1;
    combinerListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4)));
    ((igObjectRefMetaField *)combinerListField)->_metaObject = (int)igAnimationCombinerList_GetOrCreateMetaObject();
    ((igRefMetaField *)combinerListField)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igAnimationDatabase_fieldTable, g_igAnimationDatabase_fieldHandles, g_igAnimationDatabase_fieldOffsets, base);
}

