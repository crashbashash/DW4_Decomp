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
            List_Resize(list, n + 1, 4);
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

void FUN_004578c0(S_4578c0 *arg0, S_4578c0 *arg1) {
    int var_s0;
    VC_4578c0 *o;
    for (var_s0 = 0; var_s0 < arg0->f8->n; var_s0++) {
        o = arg0->f8->arr[var_s0];
        if (o != 0 && o != arg1->f4) {
            o->vX(arg1);
        }
    }
}

void Gap__Gui__igModel__vfunc_10(struct O_457950 *arg0) {
    int n;
    int i;
    int p;

    n = arg0->l->n;
    for (i = 0; i < n; i++) {
        p = arg0->l->arr[i];
        if (p != 0) {
            FUN_00457e90((S0_457e90 *)p, 0);
        }
    }
}

