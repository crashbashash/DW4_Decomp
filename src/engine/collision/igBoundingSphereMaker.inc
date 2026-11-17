igMetaObject *g_igBoundingSphereMaker_metaObject;
igMetaField *g_igBoundingSphereMaker_sphereMetaField;

igObject *FUN_0023a9d0(int arg0) {
    FUN_0023aaf0();
    return igMetaObject_CreateInstance(g_igBoundingSphereMaker_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igBoundingSphereMaker_GetMetaObject(void)
{
    igMetaObject *g = g_igBoundingSphereMaker_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0023aaf0();
    return g_igBoundingSphereMaker_metaObject;
}

int igBoundingSphereMaker_GetVTable(void) {
    union U_23aa60 u;
    int temp_s0;
    S_ref *p;

    igObject_InitHeader((igObject *)u.b);
    p = (S_ref *)&u.b[8];
    u.vt = (int)&g_igBoundingSphereMaker_vtable[0];
    *(int *)p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem) + 916)];
    u.vt = (int)&g_igBoundingSphereMaker_vtable[0];
    if (p != 0) {
        p = *(S_ref **)p;
        if (p != 0) {
            p->f4 = (int)((int) (p->f4 - 1));
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)p);
            }
        }
    }
    return temp_s0;
}

void FUN_0023aaf0(void)
{
    igMetaObject_RunStaticInit(igBoundingSphereMaker_Register);
}

static igMetaObjectCallback g_igBoundingSphereMaker_callbackList[] = { FUN_00187f30, 0 };

CallbackArray *igBoundingSphereMaker_Register(void) {
    CollisionLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBoundingSphereMaker_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igBoundingSphereMaker_GetMetaObject,
        "igBoundingSphereMaker",
        0xC, /* instance size */
        igBoundingSphereMaker_GetVTable,
        &igBoundingSphereMaker_InitFields,
        0, /* extra callback item */
        g_igBoundingSphereMaker_callbackList /* callback list */
    );
}

void thunk_igBoundingSphereMaker_GetMetaObject(void) {
    igBoundingSphereMaker_GetMetaObject();
}

static FieldFactory g_igBoundingSphereMaker_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igBoundingSphereMaker_fieldTable[] = {
    "_sphere",
};
static igMetaField **g_igBoundingSphereMaker_fieldHandles[] = {
    &g_igBoundingSphereMaker_sphereMetaField,
};
static int g_igBoundingSphereMaker_fieldOffsets[] = {
    8,
};

void igBoundingSphereMaker_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igBoundingSphereMaker_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igBoundingSphereMaker_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00187e50();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igBoundingSphereMaker_fieldTable, g_igBoundingSphereMaker_fieldHandles, g_igBoundingSphereMaker_fieldOffsets, temp_s2);
}

void FUN_0023b110(void *arg0, void *arg1) {
    if (*(int *)((char *)(arg1) + 96) == 0) {
        FUN_0018d630(*(int *)((char *)(arg0) + 8), (char *)arg1 + 0x20);
    }
}

void FUN_0023b140(struct R *arg0, struct Q *arg1) {
    S1 *sp5C;
    S1 *t;
    unsigned int var_s1;
    unsigned int var_s0;
    struct Ls *temp_v0;

    if (igObject_IsKindOf((igObject *)arg1, g_igGroup_metaObject) != 0) {
        temp_v0 = arg1->f28;
        var_s1 = 0;
        if (temp_v0 != 0) {
            var_s1 = temp_v0->n;
        }
        var_s0 = 0;
        while (var_s0 < var_s1) {
            FUN_0023b140(arg0, arg1->f28->a[var_s0]);
            var_s0 += 1;
        }
    }
    if (igObject_IsKindOf((igObject *)arg1, g_igGeometry_metaObject) != 0) {
        FUN_0023ac20(&sp5C, arg0, arg1);
        FUN_0018de10(arg0->f8, sp5C);
        t = sp5C;
        if (t != 0) {
            t->f4 = (int)((int) (t->f4 - 1));
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
    } else if (igObject_IsKindOf((igObject *)arg1, g_igTransform_metaObject) != 0) {
        FUN_0023b110(arg0, arg1);
    }
}

igSmartPointer<igObject> FUN_0023b270(ObjectSlotOwner *owner, int value) {
    igSmartPointer<igObject> object(FUN_00187e10(0), AdoptReference());
    owner->setSlot(object);
    FUN_0023b140((R *)owner, (Q *)value);
    owner->clearSlot();
    return object;
}

void FUN_0023b3b0(RetainedList *list, RefCounted *object) {
    int at = list->_count;
    void *words = list->_words;
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
    List_InsertWords((igDataList *)words, at, 1, (const void *)&object);
    list->_count = list->_count + 1;
}

void FUN_0023b410(int *arg0, int arg1, int arg2, int arg3) {
    arg0[4] = arg1; arg0[5] = arg2; arg0[6] = arg3;
    FUN_00301ee0(arg0[2], arg1 * arg2 * arg3);
}

