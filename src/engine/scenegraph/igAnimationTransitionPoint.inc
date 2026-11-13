igMetaObject *igAnimationTransitionPoint_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTransitionPoint_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a9a80();
    return g_igAnimationTransitionPoint_metaObject[0];
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

void igAnimationTransitionPoint_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationTransitionPoint_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationTransitionPoint_GetMetaObject,
        igAnimationTransitionPoint_className,
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

void igAnimationTransitionPoint_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationTransitionPoint_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igAnimationTransitionPoint_ctorTable[0], 2);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_001a9bb0();
    igMetaObject_NameFields(temp_s0, &g_igAnimationTransitionPoint_fieldTable[0], &DAT_0048d610[0], &DAT_0048d618[0], temp_s2);
}

