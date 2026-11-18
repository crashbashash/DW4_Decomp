igMetaObject *g_igAnimationTransitionPoint_metaObject;
igMetaField *g_igAnimationTransitionPoint_transitionTimeMetaField;
igMetaField *g_igAnimationTransitionPoint_transitionParamsMetaField;

igMetaObject *igAnimationTransitionPoint_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTransitionPoint_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationTransitionPoint_EnsureRegistered();
    return g_igAnimationTransitionPoint_metaObject;
}

int igAnimationTransitionPoint_GetVTable(void) {
     Obj_1a99f0 o;
     int r;
     Q *q;

     igObject_InitHeader((igObject *)&o);
     o.vt = &g_igAnimationTransitionPoint_vtable[0];
     o.s = 0;
     r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
     o.vt = &g_igAnimationTransitionPoint_vtable[0];
     if (&o.s != 0) {
         q = o.s;
         if (q != 0) {
             q->f4 -= 1;
             if ((q->f4 & 0x7fffff) == 0) {
                 igObject_Destroy((igObject *)q);
             }
         }
     }
     return r;
 }

void igAnimationTransitionPoint_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationTransitionPoint_Register);
}

static igMetaObjectCallback g_igAnimationTransitionPoint_callbackList[] = { igAnimationTransitionParams_EnsureRegistered, 0 };

CallbackArray *igAnimationTransitionPoint_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationTransitionPoint_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igAnimationTransitionPoint_GetMetaObjectFunction,
        "igAnimationTransitionPoint",
        0x18, /* instance size */
        igAnimationTransitionPoint_GetVTable,
        &igAnimationTransitionPoint_InitFields,
        0, /* extra callback item */
        g_igAnimationTransitionPoint_callbackList /* callback list */
    );
}

void igAnimationTransitionPoint_GetMetaObjectFunction(void) {
    igAnimationTransitionPoint_GetMetaObject();
}

static FieldFactory g_igAnimationTransitionPoint_ctorTable[] = {
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igAnimationTransitionPoint_fieldTable[] = {
    "_transitionTime",
    "_transitionParams",
};
static igMetaField **g_igAnimationTransitionPoint_fieldHandles[] = {
    &g_igAnimationTransitionPoint_transitionTimeMetaField,
    &g_igAnimationTransitionPoint_transitionParamsMetaField,
};
static int g_igAnimationTransitionPoint_fieldOffsets[] = {
    8,
    16,
};

void igAnimationTransitionPoint_InitFields(void) {
    int base;
    void *transitionParamsField;
    void *meta;

    meta = (void *)g_igAnimationTransitionPoint_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igAnimationTransitionPoint_ctorTable, 2);
    transitionParamsField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)transitionParamsField)->_metaObject = (int)igAnimationTransitionParams_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_igAnimationTransitionPoint_fieldTable, g_igAnimationTransitionPoint_fieldHandles, g_igAnimationTransitionPoint_fieldOffsets, base);
}

