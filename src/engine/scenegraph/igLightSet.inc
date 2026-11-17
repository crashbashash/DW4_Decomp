igMetaObject *g_igLightSet_metaObject;
igMetaField *g_igLightSet_lightsMetaField;

igMetaObject *FUN_0019dbb0(void) {
    if (g_igLightSet_metaObject == 0) {
        g_igLightSet_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igLightSet_metaObject;
}

igMetaObject *igLightSet_GetMetaObject(void)
{
    igMetaObject *g = g_igLightSet_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLightSet_EnsureRegistered();
    return g_igLightSet_metaObject;
}

int igLightSet_GetVTable(void) {
    struct Obj_19dc50 o;
    int r;
    igObject_InitHeader((igObject *)&o);
    o.f8 = 0;
    o.f12 = 0;
    o.f16 = 0;
    o.vt = &g_igLightSet_vtable[0];
    o.f28 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)g_objectSystem + 916));
    o.vt = &g_igLightSet_vtable[0];
    FUN_0019c1a0((ObjectRefWord *)&o.f28, -1);
    igNode_Destroy((igNode *)&o, 0);
    return r;
}

void igLightSet_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLightSet_Register);
}

static igMetaObjectCallback g_igLightSet_callbackList[] = { igLightList_EnsureRegistered, 0 };

CallbackArray *igLightSet_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLightSet_metaObject,
        igNode_Register,
        igNode_GetPublishedMetaObject,
        thunk_igLightSet_GetMetaObject,
        "igLightSet",
        0x20, /* instance size */
        igLightSet_GetVTable,
        &igLightSet_InitFields,
        0, /* extra callback item */
        g_igLightSet_callbackList /* callback list */
    );
}

void thunk_igLightSet_GetMetaObject(void) {
    igLightSet_GetMetaObject();
}

igMetaObject *FUN_0019dd70(void) {
    return g_igNode_metaObject;
}

static FieldFactory g_igLightSet_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igLightSet_fieldTable[] = {
    "_lights",
};
static igMetaField **g_igLightSet_fieldHandles[] = {
    &g_igLightSet_lightsMetaField,
};
static int g_igLightSet_fieldOffsets[] = {
    28,
};

void igLightSet_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igLightSet_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igLightSet_ctorTable, 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001365e0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igMetaField *)temp_s1)->_deepCopyMethod = 0;
    ((igMetaField *)temp_s1)->_shallowCopyMethod = 2;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igLightSet_fieldTable, g_igLightSet_fieldHandles, g_igLightSet_fieldOffsets, temp_s2);
}

igMetaObject *FUN_0019de30(void) {
    return g_igTransform_metaObject;
}

igMetaObject *g_igAnimationSequence_metaObject;

igMetaObject *FUN_0019de40(void) {
    return g_igAnimationSequence_metaObject;
}

void **FUN_0019de50(struct Ref **self, short flag) {
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

void **FUN_0019ded0(void **arg0, long long arg1) {
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

O *FUN_0019df50(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
        if (arg1 > 0) operator delete(arg0);
    }
    return arg0;
}

