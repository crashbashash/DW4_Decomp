void FUN_0023a9d0(int arg0) {
    FUN_0023aaf0();
    igMetaObject_CreateInstance(*(int *)0x56DE00, arg0);
}

igMetaObject *igBoundingSphereMaker_GetMetaObject(void)
{
    igMetaObject *g = g_igBoundingSphereMaker_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0023aaf0();
    return g_igBoundingSphereMaker_metaObject[0];
}

int igBoundingSphereMaker_GetVTable(void) {
    union U_23aa60 u;
    int temp_s0;
    S_ref *p;

    igObject_InitHeader(u.b);
    p = (S_ref *)&u.b[8];
    u.vt = (int)&DAT_0052d230[0];
    *(int *)p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052d230[0];
    if (p != 0) {
        p = *(S_ref **)p;
        if (p != 0) {
            p->f4 = (int)((int) (p->f4 - 1));
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    return temp_s0;
}

void FUN_0023aaf0(void)
{
    igMetaObject_RunStaticInit(igBoundingSphereMaker_Register);
}

void igBoundingSphereMaker_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBoundingSphereMaker_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igBoundingSphereMaker_GetMetaObject,
        igBoundingSphereMaker_className,
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

void igBoundingSphereMaker_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056de00[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498620[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00187e50();
    igMetaObject_NameFields(temp_s0, &DAT_00498628[0], &DAT_00498630[0], &DAT_00498638[0], temp_s2);
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

    if (igObject_IsKindOf(arg1, DAT_005619f8[0]) != 0) {
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
    if (igObject_IsKindOf(arg1, DAT_00561a38[0]) != 0) {
        FUN_0023ac20(&sp5C, arg0, arg1);
        FUN_0018de10(arg0->f8, sp5C);
        t = sp5C;
        if (t != 0) {
            t->f4 = (int)((int) (t->f4 - 1));
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    } else if (igObject_IsKindOf(arg1, DAT_005612b0[0]) != 0) {
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
    List_InsertWords(words, at, 1, &object);
    list->_count = list->_count + 1;
}

void FUN_0023b410(int *arg0, int arg1, int arg2, int arg3) {
    arg0[4] = arg1; arg0[5] = arg2; arg0[6] = arg3;
    FUN_00301ee0(arg0[2], arg1 * arg2 * arg3);
}

