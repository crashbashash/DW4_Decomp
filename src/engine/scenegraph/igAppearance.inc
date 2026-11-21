igMetaObject *g_igAppearance_metaObject;
igMetaField *g_igAppearance_skinMetaField;
igMetaField *g_igAppearance_attachedSkinsMetaField;
igMetaField *g_igAppearance_attachedGraphsMetaField;
igMetaField *g_igAppearance_segmentOverrideNameListMetaField;
igMetaField *g_igAppearance_segmentOverrideGraphListMetaField;

igMetaObject *igAppearance_GetOrCreateMetaObject(void) {
    if (g_igAppearance_metaObject == 0) {
        g_igAppearance_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAppearance_metaObject;
}

igMetaObject *igAppearance_GetMetaObject(void)
{
    igMetaObject *g = g_igAppearance_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAppearance_EnsureRegistered();
    return g_igAppearance_metaObject;
}

int igAppearance_GetVTable(void) {
    struct Obj_1a61f0 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w2 = 0;
    obj.vt = &g_igAppearance_vtable[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igAppearance_vtable[0];
    igSmartPointer_igNodeList_Destruct((igSmartPointer<igObject> *)&obj.w7, -1);
    igSmartPointer_igStringObjList_Destruct((igSmartPointer<igObject> *)&obj.w6, -1);
    igSmartPointer_igModelViewMatrixBoneSelectList_Destruct((void * *)&obj.w5, -1);
    igSmartPointer_igSkinList_Destruct((struct Ref * *)&obj.w4, -1);
    igSmartPointer_igSkin_Destruct((void * *)&obj.w3, -1);
    igNamedObject_Destroy((igNamedObject *)&obj, 0);
    return t;
}

void **igSmartPointer_igSkin_Destruct(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void **igSmartPointer_igSkinList_Destruct(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy((igObject *)p);
        }
        if (flag > 0) operator delete(self);
    }
    return (void **)self;
}

void **igSmartPointer_igModelViewMatrixBoneSelectList_Destruct(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void igAppearance_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAppearance_Register);
}

static igMetaObjectCallback g_igAppearance_callbackList[] = { igSkin_EnsureRegistered, igSkinList_EnsureRegistered, igModelViewMatrixBoneSelectListSg_EnsureRegistered, igStringObjList_EnsureRegistered, igNodeList_EnsureRegistered, 0 };

CallbackArray *igAppearance_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAppearance_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        igNamedObject_GetPublishedMetaObject,
        igAppearance_GetMetaObjectFunction,
        "igAppearance",
        0x20, /* instance size */
        igAppearance_GetVTable,
        &igAppearance_InitFields,
        0, /* extra callback item */
        g_igAppearance_callbackList /* callback list */
    );
}

void igAppearance_GetMetaObjectFunction(void) {
    igAppearance_GetMetaObject();
}

static FieldFactory g_igAppearance_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igAppearance_fieldTable[] = {
    "_skin",
    "_attachedSkins",
    "_attachedGraphs",
    "_segmentOverrideNameList",
    "_segmentOverrideGraphList",
};
static igMetaField **g_igAppearance_fieldHandles[] = {
    &g_igAppearance_skinMetaField,
    &g_igAppearance_attachedSkinsMetaField,
    &g_igAppearance_attachedGraphsMetaField,
    &g_igAppearance_segmentOverrideNameListMetaField,
    &g_igAppearance_segmentOverrideGraphListMetaField,
};
static int g_igAppearance_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
};

void igAppearance_InitFields(void) {
    int base;
    void *skinField;
    void *attachedSkinsField;
    void *attachedGraphsField;
    void *segmentOverrideNameListField;
    void *segmentOverrideGraphListField;
    void *meta;

    meta = (void *)g_igAppearance_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igAppearance_ctorTable, 5);
    skinField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)skinField)->_metaObject = (int)igSkin_GetOrCreateMetaObject();
    attachedSkinsField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)attachedSkinsField)->_metaObject = (int)igSkinList_GetOrCreateMetaObject();
    ((igRefMetaField *)attachedSkinsField)->_construct = 1;
    attachedGraphsField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)attachedGraphsField)->_metaObject = (int)igModelViewMatrixBoneSelectListSg_GetOrCreateMetaObject();
    ((igRefMetaField *)attachedGraphsField)->_construct = 1;
    segmentOverrideNameListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igObjectRefMetaField *)segmentOverrideNameListField)->_metaObject = (int)igStringObjList_GetOrCreateMetaObject();
    ((igRefMetaField *)segmentOverrideNameListField)->_construct = 1;
    segmentOverrideGraphListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4)));
    ((igObjectRefMetaField *)segmentOverrideGraphListField)->_metaObject = (int)igNodeList_GetOrCreateMetaObject();
    ((igRefMetaField *)segmentOverrideGraphListField)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igAppearance_fieldTable, g_igAppearance_fieldHandles, g_igAppearance_fieldOffsets, base);
}

