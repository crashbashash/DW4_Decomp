void igInsightCore_AddInfo(igInsightCore *self, int info) {
    unsigned int index;
    igObjectList *managers;

    for (index = 0; managers = (igObjectList *)((igSerialScheduler *)self->_managerList)->_managerList, index < (unsigned int)managers->_count; index++) {
        int byteOffset = index * 4;
        DW4VC *manager = (DW4VC *)*(int *)(managers->_data + byteOffset);
        if (manager->vX(info) != 0) {
            break;
        }
    }
    ObjectList_AppendRetained(self->_infoList, info);
}

void FUN_002370c0(igInsightCore *arg0) {
    igObjectList *l;
    int n2;
    int j;
    int n;
    igObjectList *a;
    igObject *p;
    unsigned int k;
    int i;

    for (k = 0; k < (unsigned int)((igObjectList *)((igInfoManagerOrderedList *)arg0->_managerList)->_objectList)->_count; k++) {
        a = (igObjectList *)((igInfoManagerOrderedList *)arg0->_managerList)->_objectList;
        (*(VC112 ***)&a->_data)[k]->vX();
    }
    l = (igObjectList *)arg0->_infoList;
    n = l->_count;
    for (i = 0; i < n; i++) {
        p = (*(igObject ***)&l->_data)[i];
        if (p != 0) {
            *(int *)&p->_refCount = *(int *)&p->_refCount - 1;
            if (((unsigned long long)((long long)*(int *)&p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    n2 = l->_count;
    for (j = 0; j < n2; j++) {
        (*(igObject ***)&l->_data)[j] = 0;
    }
    l->_count = 0;
    if (!(0 < ((igObjectList *)arg0->_infoList)->_count)) {
        List_Reserve(arg0->_infoList, 0, 4);
    }
}

void FUN_002371f0(S_2371f0 *arg0) {
    unsigned int i;

    arg0->f64 = 0;
    arg0->f56 = 0;
    for (i = 0; i < arg0->m->l->cnt; i++) {
        arg0->m->l->arr[i]->vX();
    }
    arg0->f48->vY();
}

void FUN_00237280(int *arg0) {
    unsigned int i;
    struct Q *q;

    ((A_237280 *)arg0[12])->vX();
    for (i = 0; i < (unsigned int)(q = *(struct Q **)(arg0[2] + 8))->count; i++) {
        q->data[i]->vX();
    }
}

void Gap__Insight__igInsightCore__vfunc_13(struct A_237300 *arg0) {
    Gap__Core__igObject__vfunc_11();
    StringRef_237300 first(&text_Clear_done[0]);
    StringRef_237300 second(&text_Scenes_done[0]);
    StringRef_237300 third(&text_Overlays_done[0]);
    FUN_002d78e0(arg0->f28, first.p);
    FUN_002d78e0(arg0->f28, second.p);
    FUN_002d78e0(arg0->f28, third.p);
    FUN_002d7090(arg0->f28, first.p, second.p);
    FUN_002d7090(arg0->f28, second.p, third.p);
    FUN_002d7090(arg0->f28, arg0->f44, first.p);
    igRendererOrderedList_Append(arg0->f28, arg0->f44, 0);
    arg0->f72 = 0x40000;
    *(struct A_237300 **)(arg0->f36 + 8) = arg0;
    igEventDispatcher_AddReceiver(arg0->f32, arg0->f36);
}

void FUN_00237530(OO *arg0) {
    int temp_s1;
    int var_s0;
    R_237530 *t;
    R_237530 *s0;

    if (arg0->f20 == 0) {
        igSmartPointer<igWindowView> display = Viewer_CreateDisplay(0);
        s0 = (R_237530 *)display.p;
        if (s0 != 0) {
            s0->rc = s0->rc + 1;
        }
        t = (R_237530 *)arg0->f20;
        if (t != 0) {
            t->rc = t->rc - 1;
            if ((t->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
        arg0->f20 = (DW4VC_152 *)s0;
    }
    s0 = arg0->f20->vX();
    if (s0 != 0) {
        s0->rc = s0->rc + 1;
    }
    t = arg0->f24;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->f24 = s0;
    FUN_004541f0(arg0->f32, arg0->f20);
    temp_s1 = arg0->f28->f8->n;
    var_s0 = 0;
    while (var_s0 < temp_s1) {
        FUN_00457ca0(arg0->f28->f8->items[var_s0], arg0->f24);
        var_s0 += 1;
    }
}

void FUN_002376b0(struct H *arg0) {
    int n;
    int i;

    n = arg0->m->list->count;
    for (i = 0; i < n; i++) {
        FUN_00457ca0(arg0->m->list->items[i], 0);
    }
    FUN_0013c110();
}

void FUN_00237730(S_237730 *arg0) {
    long long t = arg0->f48->vX();
    arg0->f64 = t - arg0->f56;
    arg0->f56 = t;
    arg0->f80 = arg0->f80 + (__muldi3(arg0->f64, arg0->f72) >> 18);
    arg0->f32->vX();
    arg0->f12->vX();
}

void FUN_002377c0(ProfilerState *t) {
    int n;
    int i;
    long long s2;
    long long s1;
    int j;
    long long s0;
    if (t->a->v34() == 0) {
        t->cnt = t->cnt + 1;
        n = t->m->l->cnt;
        s2 = t->b->v24();
        for (i = 0; i < n; i++) t->m->l->arr[i]->v23();
        if (t->a->v171() != 0) {
            s1 = t->b->v24();
            for (j = 0; j < n; j++) t->m->l->arr[j]->v24();
            s0 = t->b->v24();
            t->a->v172();
            t->d1 = s1 - s2;
            t->d2 = s0 - s1;
        }
    }
}

