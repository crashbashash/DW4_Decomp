igMetaObject *FUN_00194ef0(void)
{
    igMetaObject *g = ((igMetaObject * *)g_igTransformSequence1_5_metaObject)[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00195290();
    return ((igMetaObject * *)g_igTransformSequence1_5_metaObject)[0];
}

int igTransformSequence1_5_GetVTable(void) {
    struct Obj_194f40 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.vt = &DAT_005282c0[0];
    obj.w[13] = 0;
    obj.w[14] = 0;
    obj.w[15] = 0;
    obj.w[16] = 0;
    obj.w[23] = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_005282c0[0];
    FUN_00195210((ObjectRefWord *)&obj.w[23], -1);
    FUN_001374b0(&obj.w[16], -1);
    FUN_001374b0(&obj.w[15], -1);
    FUN_001374b0(&obj.w[14], -1);
    FUN_00195190((O *)&obj.w[13], -1);
    FUN_00195030((Obj_195030 *)((int *)&obj), 0);
    return t;
}

Obj_195030 *FUN_00195030(Obj_195030 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &DAT_005283e0[0];
        arg0->rel(&arg0->m20);
        arg0->rel(&arg0->m16);
        arg0->rel(&arg0->m12);
        arg0->rel(&arg0->m8);
        if (arg1 > 0) {
            thunk_Memory_FreeBuffer(arg0);
        }
    }
    return arg0;
}

O *FUN_00195190(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

ObjectRefWord *FUN_00195210(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void FUN_00195290(void)
{
    igMetaObject_RunStaticInit(igTransformSequence1_5_Register);
}

void igTransformSequence1_5_Register(void) {
    SceneGraphLibrary_MarkRegistered();  /* Shared set-once latch run before every registration of this family. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTransformSequence1_5_metaObject,
        igTransformSequence_Register,
        igTransformSequence_GetPublishedMetaObject,
        thunk_FUN_00194ef0,
        igTransformSequence1_5_className,
        sizeof(igTransformSequence1_5),                      /* Instance size. */
        igTransformSequence1_5_GetVTable,
        &igTransformSequence1_5_InitFields,
        thunk_FUN_001ddfd0, /* extra callback item */
        g_igTransformSequence1_5_callbackList /* callback list */
    );
}

void thunk_FUN_00194ef0(void) {
    FUN_00194ef0();
}

