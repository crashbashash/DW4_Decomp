igMetaObject *g_igAnimationTransitionPoint_metaObject;
igMetaField *g_igAnimationTransitionPoint_transitionTimeMetaField;
igMetaField *g_igAnimationTransitionPoint_transitionParamsMetaField;

igMetaObject *igAnimationTransitionPoint_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTransitionPoint_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a9a80();
    return g_igAnimationTransitionPoint_metaObject;
}

int igAnimationTransitionPoint_GetVTable(void) {
     Obj_1a99f0 o;
     int r;
     Q *q;

     igObject_InitHeader(&o);
     o.vt = &DAT_00529960[0];
     o.s = 0;
     r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
     o.vt = &DAT_00529960[0];
     if (&o.s != 0) {
         q = o.s;
         if (q != 0) {
             q->f4 -= 1;
             if ((q->f4 & 0x7fffff) == 0) {
                 igObject_Destroy(q);
             }
         }
     }
     return r;
 }

void FUN_001a9a80(void)
{
    igMetaObject_RunStaticInit(igAnimationTransitionPoint_Register);
}

static igMetaObjectCallback g_igAnimationTransitionPoint_callbackList[] = { FUN_001a9c90, 0 };

void igAnimationTransitionPoint_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationTransitionPoint_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationTransitionPoint_GetMetaObject,
        "igAnimationTransitionPoint",
        0x18, /* instance size */
        igAnimationTransitionPoint_GetVTable,
        &igAnimationTransitionPoint_InitFields,
        0, /* extra callback item */
        g_igAnimationTransitionPoint_callbackList /* callback list */
    );
}

void thunk_igAnimationTransitionPoint_GetMetaObject(void) {
    igAnimationTransitionPoint_GetMetaObject();
}

static FieldFactory g_igAnimationTransitionPoint_ctorTable[] = {
    igLongMetaField_Create,
    igObjectRefMetaField_Create,
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
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationTransitionPoint_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igAnimationTransitionPoint_ctorTable, 2);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_001a9bb0();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igAnimationTransitionPoint_fieldTable, g_igAnimationTransitionPoint_fieldHandles, g_igAnimationTransitionPoint_fieldOffsets, temp_s2);
}

