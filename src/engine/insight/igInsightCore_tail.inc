void igInsightCore_AddInfo(igInsightCore *self, igObject *info) {
    unsigned int index;
    igObjectList *managers;

    for (index = 0; managers = (igObjectList *)((igSerialScheduler *)self->_managerList)->_managerList, index < (unsigned int)managers->_count; index++) {
        int byteOffset = index * 4;
        DW4VC *manager = (DW4VC *)*(int *)(managers->_data + byteOffset);
        if (manager->vX((int)info) != 0) {
            break;
        }
    }
    ((Gap::Core::igObjectList *)self->_infoList)->append((Gap::Core::igObject *)info);
}

void igInsightCore_RemoveAllInfos(igInsightCore *arg0) {
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
        ((Gap::Core::igDataList *)arg0->_infoList)->setCapacity(0, 4);
    }
}

void igInsightCore_Begin(igInsightCore *core) {
    S_2371f0 *arg0 = (S_2371f0 *)core;
    unsigned int i;

    arg0->f64 = 0;
    arg0->f56 = 0;
    for (i = 0; i < arg0->m->l->cnt; i++) {
        arg0->m->l->arr[i]->vX();
    }
    arg0->f48->vY();
}

void igInsightCore_End(igInsightCore *self) {
    unsigned int i;
    struct Q *q;

    ((A_237280 *)self->_timer)->vX();
    for (i = 0; i < (unsigned int)(q = *(struct Q **)(self->_managerList + 8))->count; i++) {
        q->data[i]->vX();
    }
}

void igInsightCore_resetFields(igInsightCore *self, int flags) {
    Gap__Core__igObject__resetFields((igObject *)self, flags);
    StringRef_237300 first("Clear done");
    StringRef_237300 second("Scenes done");
    StringRef_237300 third("Overlays done");
    ((Gap::Core::igDependencyOrderedList *)self->_rendererList)->appendCheckPoint((const char *)first.p);
    ((Gap::Core::igDependencyOrderedList *)self->_rendererList)->appendCheckPoint((const char *)second.p);
    ((Gap::Core::igDependencyOrderedList *)self->_rendererList)->appendCheckPoint((const char *)third.p);
    ((Gap::Core::igDependencyOrderedList *)self->_rendererList)->appendDependency(first.p, second.p);
    ((Gap::Core::igDependencyOrderedList *)self->_rendererList)->appendDependency(second.p, third.p);
    ((Gap::Core::igDependencyOrderedList *)self->_rendererList)->appendDependency((igObject *)self->_clearRenderer, first.p);
    ((Gap::Core::igDependencyOrderedList *)self->_rendererList)->append((Gap::Core::igObject *)self->_clearRenderer);
    self->_currentToWorldTimeFactor = 0x40000;
    *(igInsightCore **)(self->_windowResizeReceiver + 8) = self;
    igEventDispatcher_AddReceiver((igEventDispatcher *)self->_dispatcher, (igObject *)self->_windowResizeReceiver);
}

void igInsightCore_InitializeDrawing(igInsightCore *core) {
    OO *arg0 = (OO *)core;
    int temp_s1;
    int var_s0;
    R_237530 *t;
    R_237530 *s0;

    if (arg0->f20 == 0) {
        igSmartPointer<igWindow> display = igInsightCore_CreateWindow(0);
        s0 = (R_237530 *)display.p;
        if (s0 != 0) {
            s0->rc = s0->rc + 1;
        }
        t = (R_237530 *)arg0->f20;
        if (t != 0) {
            t->rc = t->rc - 1;
            if ((t->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)t);
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
            igObject_Destroy((igObject *)t);
        }
    }
    arg0->f24 = s0;
    FUN_004541f0((int *)arg0->f32, (int *)arg0->f20);
    temp_s1 = arg0->f28->f8->n;
    var_s0 = 0;
    while (var_s0 < temp_s1) {
        ((Gap::Gui::igRenderer *)arg0->f28->f8->items[var_s0])->setVisualContext((Gap::Gfx::igVisualContext *)arg0->f24);
        var_s0 += 1;
    }
}

void igInsightCore_TerminateDrawing(igInsightCore *core) {
    struct H *arg0 = (struct H *)core;
    int n;
    int i;

    n = arg0->m->list->count;
    for (i = 0; i < n; i++) {
        ((Gap::Gui::igRenderer *)arg0->m->list->items[i])->setVisualContext(0);
    }
    Gap::Attrs::igAttrPool::userUnregister();
}

void igInsightCore_HandleEvents(igInsightCore *core) {
    S_237730 *arg0 = (S_237730 *)core;
    long long t = arg0->f48->vX();
    arg0->f64 = t - arg0->f56;
    arg0->f56 = t;
    arg0->f80 = arg0->f80 + ((arg0->f64 * arg0->f72) >> 18);
    arg0->f32->vX();
    arg0->f12->vX();
}

void igInsightCore_DrawFrame(igInsightCore *core) {
    ProfilerState *t = (ProfilerState *)core;
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

