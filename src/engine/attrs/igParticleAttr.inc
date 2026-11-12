igMetaObject *igParticleAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igParticleAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00134e50();
    return g_igParticleAttr_metaObject[0];
}

int igParticleAttr_GetVTable(void) {
     Obj_134dc0 o;
     int r;
     Q *q;

     igObject_InitHeader(&o);
     o.vt = &DAT_00523280[0];
     o.s = 0;
     r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
     o.vt = &DAT_00523280[0];
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

void FUN_00134e50(void)
{
    igMetaObject_RunStaticInit(igParticleAttr_Register);
}

void igParticleAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igParticleAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igParticleAttr_GetMetaObject,
        igParticleAttr_className,
        0x30, /* instance size */
        igParticleAttr_GetVTable,
        &igParticleAttr_InitFields,
        0, /* extra callback item */
        g_igParticleAttr_callbackList /* callback list */
    );
}

void thunk_igParticleAttr_GetMetaObject(void) {
    igParticleAttr_GetMetaObject();
}

void igParticleAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igParticleAttr_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486160[0], 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0014c980();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    FUN_002ebc00(temp_v0, -1);
    ((igLongMetaField *)temp_v0)->_persistent = 0;
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5)) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00486180[0], &DAT_004861a0[0], &DAT_004861c0[0], temp_s2);
}

