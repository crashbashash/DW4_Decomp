void FUN_004576d0(igContext *context, ContextHandler *handler) {
    int s[4];
    igTDataList<ContextHandler *> *list;
    int index;
    index = (list = (igTDataList<ContextHandler *> *)context->_pExtList)->find(0);
    if (index < 0) {
        int n = list->_count;
        if (n < list->_capacity) {
            list->_count = list->count() + 1;
        } else {
            ((Gap::Core::igDataList *)list)->resizeAndSetCount(n + 1, 4);
        }
        list->_data[n] = handler;
    } else if (list->count() != 0 && index >= 0 && index < list->count()) {
        list->_data[index] = handler;
    }
    s[0] = 0;
    s[1] = 0;
    s[2] = 0;
    handler->vX(s);
}

void FUN_004577f0(igModel *arg0, OV *arg1) {
    Flags f;
    igObjectList *l;
    int i;
    int n;
    f.b = 0;
    f.c = 0;
    f.a = 1;
    arg1->vX(&f);
    K_4577f0 key(arg1);
    l = (igObjectList *)arg0->_views;
    i = Finder_4577f0::Find(l, key);
    if (i >= 0) {
        n = *(int *)&l->_count;
        if (n != 0 && i >= 0 && i < n) {
            ((void **)l->_data)[i] = 0;
        }
    }
}

void igModel_NotifyViews(igModel *model, ModelChange *change) {
    int i;
    ModelViewDispatch *view;
    for (i = 0; i < ((igObjectList *)model->_views)->_count; i++) {
        view = ((ModelViewDispatch **)((igObjectList *)model->_views)->_data)[i];
        if (view != 0 && view != change->source) {
            view->onModelChange(change);
        }
    }
}

void igModel_userDestruct(struct O_457950 *arg0) {
    int n;
    int i;
    int p;

    n = arg0->l->n;
    for (i = 0; i < n; i++) {
        p = arg0->l->arr[i];
        if (p != 0) {
            igView_SetModel((igView *)p, 0);
        }
    }
}

