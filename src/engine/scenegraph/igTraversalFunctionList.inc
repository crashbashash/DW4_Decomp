int FUN_0019a6e0(int arg0) {
    FUN_0019a800();
    return igMetaObject_CreateInstance(*(int *)0x5615C8, arg0);
}

igMetaObject *FUN_0019a720(void) {
    if (g_igTraversalFunctionList_metaObject[0] == 0) {
        g_igTraversalFunctionList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igTraversalFunctionList_metaObject[0];
}

igMetaObject *igTraversalFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igTraversalFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019a800();
    return g_igTraversalFunctionList_metaObject[0];
}

int igTraversalFunctionList_GetVTable(void) {
    struct Obj_19a7c0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052adb0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0019a800(void)
{
    igMetaObject_RunStaticInit(igTraversalFunctionList_Register);
}

void igTraversalFunctionList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igTraversalFunctionList_metaObject),
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igTraversalFunctionList_GetMetaObject,
        igTraversalFunctionList_className,
        0x14, /* instance size */
        igTraversalFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTraversalFunctionList_GetMetaObject(void) {
    igTraversalFunctionList_GetMetaObject();
}

ObjectRefWord *FUN_0019a890(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void **FUN_0019a910(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_0019a990(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_0019aa10(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) FUN_00100610(self);
    }
    return (void **)self;
}

void **FUN_0019aa90(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

O *FUN_0019ab10(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

ObjectRefWord *FUN_0019ab90(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

int *FUN_0019ac10(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019ac20(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019ac30(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019ac40(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019ac50(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019ac60(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019ac70(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019ac80(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019ac90(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019aca0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019acb0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019acc0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019acd0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int FUN_0019ace0(int a0)
{
    return a0;
}

void *FUN_0019acf0(igGroup *arg0) {
    igObject_InitHeader();
    arg0->_vtable = (int)(&g_igNamedObject_vtable[0]);
    arg0->_name = 0;
    arg0->_vtable = (int)(&DAT_00528a90[0]);
    arg0->_bound = 0;
    arg0->_parentList = 0;
    arg0->_vtable = (int)(&DAT_00528dd0[0]);
    arg0->_childList = 0;
    return arg0;
}

