void Gap__Gui__igEventDispatcher__vfunc_26(Owner *o, int unused, Cur *c) {
    int n = o->m2->m->count;
    int i = 0;
    while (i < n) {
        Item *it = o->m2->m->items[i];
        float x = c->GetX();
        float y = c->GetY();
        if (it->hit(x, y) & 0xFF) break;
        i++;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_27(S_4544d0 *arg0, int arg1, int arg2, int arg3) {
    int n = arg0->m->list->cnt;
    int i;
    for (i = 0; i < n; i++) {
        if (arg0->m->list->arr[i]->vX(arg3, 1) & 0xFF) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_28(S_454570 *arg0, int a1, int a2, int arg3) {
    int n = arg0->m->list->count;
    int i;
    for (i = 0; i < n; i++) {
        if (arg0->m->list->data[i]->vX(arg3, 0) != 0) {
            break;
        }
    }
}

void Gap__Gui__igEventDispatcher__vfunc_29(O_454610 *arg0, int arg1, int arg2, int arg3) {
    int n = arg0->m->list->count;
    int i;
    for (i = 0; i < n; i++) {
        if (arg0->m->list->items[i]->vX(arg2, arg3) & 0xFF) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_30(T_4546c0 *arg0, int arg1, int arg2, int arg3) {
    int temp_s1;
    int var_s0;

    temp_s1 = arg0->f12->f8->f8;
    for (var_s0 = 0; var_s0 < temp_s1; var_s0++) {
        if (arg0->f12->f8->f16[var_s0]->vX(arg2, arg3) & 0xFF) {
            break;
        }
    }
}

void Gap__Gui__igEventDispatcher__vfunc_31(O_454770 *arg0, V104 *arg1) {
    int n = arg0->m->list->count;
    int found = 0;
    int i = 0;
    for (; i < n; i++) {
        found = 0xFF & arg0->m->list->items[i]->vX();
        if (found != 0) break;
    }
    if (!found) arg1->vY();
}

/* matching construct: _receivers/_controllerManager/_objectList/_controllers/_data are 4-byte reference fields in the reflected structs; the casts give the typed views (no layout effect) */
void Gap__Gui__igEventDispatcher__vfunc_32(igEventDispatcher *arg0, int arg1, int arg2, int arg3, float f0, float f1) {
    igDataList *l1 = (igDataList *)((igControllerManager *)arg0->_controllerManager)->_controllers;
    K_454820 key(arg2);
    int idx = Finder::Find(l1, key);
    int n2 = ((igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList)->_count;
    int j = 0;
    for (; j < n2; j++) {
        Elem *o = ((Elem **)((igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList)->_data)[j];
        if (o->vX(idx, arg3, f0, f1) & 0xFF) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_33(igEventDispatcher *arg0, int arg1, int arg2, int arg3) {
    igDataList *l1 = (igDataList *)((igControllerManager *)arg0->_controllerManager)->_controllers;
    K_454930 key(arg2);
    int idx = Finder_454930::Find(l1, key);
    int n2 = ((igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList)->_count;
    int j = 0;
    for (; j < n2; j++) {
        Lis *o = ((Lis **)((igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList)->_data)[j];
        if (o->v108(idx, arg3, 1) & 0xFF) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_34(EventDispatcherView *self, int, DispatchKey *key, int arg3) {
    int idx;
    int cnt;
    int i;
    igTDataList<DispatchKey *> *l;
    l = self->keys->list;
    idx = l->find(key);
    cnt = self->receivers->list->_count;
    for (i = 0; i < cnt; i++) {
        if (self->receivers->list->_data[i]->onKeyEvent(idx, arg3, 0) & 0xFF) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_35(igEventDispatcher *arg0, int arg1, int arg2, int arg3, float f) {
    IList *l1 = ((Hold *)arg0->_controllerManager)->l;
    K_454b30 key(arg2);
    int idx = Finder_454b30::Find(l1, key);
    int n2 = ((Hold2 *)arg0->_receivers)->l->n;
    int j = 0;
    for (; j < n2; j++) {
        Lis_454b30 *o = ((Hold2 *)arg0->_receivers)->l->data[j];
        if (o->v112(idx, arg3, f) & 0xFF) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_39(igEventDispatcher *arg0, int arg1, int arg2, int arg3, float f) {
    igControllerList *l1 = (igControllerList *)((igControllerManager *)arg0->_controllerManager)->_controllers;
    K_454c30 key(arg2);
    int idx = Finder_454c30::Find(l1, key);
    int n2 = ((igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList)->_count;
    int j = 0;
    for (; j < n2; j++) {
        Lis_454c30 *o = ((Lis_454c30 **)((igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList)->_data)[j];
        if (o->v120(idx, arg3, f) & 0xFF) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_38(EventDispatcherView *self, int, DispatchKey *key, int arg3, float f) {
    igTDataList<DispatchKey *> *l = self->keys->list;
    int idx = l->find(key);
    int n = self->receivers->list->_count;
    for (int i = 0; i < n; i++) {
        unsigned char r = self->receivers->list->_data[i]->onAxisEvent(idx, arg3, f);
        if (r) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_36(igEventDispatcher *arg0, int arg1, int arg2) {
    igControllerList *l1 = (igControllerList *)((igControllerManager *)arg0->_controllerManager)->_controllers;
    K_454e30 key(arg2);
    int idx = Finder_454e30::Find(l1, key);
    igObjectList *recv = (igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList;
    int n2 = recv->_count;
    int j = 0;
    for (; j < n2; j++) {
        Lis_454e30 *o = ((Lis_454e30 **)((igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList)->_data)[j];
        if (o->v124(idx, 1) & 0xFF) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_37(EventDispatcherView *self, int, DispatchKey *key) {
    igTDataList<DispatchKey *> *l = self->keys->list;
    int idx = l->find(key);
    int n = self->receivers->list->_count;
    for (int i = 0; i < n; i++) {
        unsigned char r = self->receivers->list->_data[i]->onButtonEvent(idx, 0);
        if (r) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_40(O_455010 *arg0, int arg1, int arg2) {
    int n;
    int i;
    E_455010 *e;
    n = arg0->f12->l2->n;
    i = 0;
    while (i < n) {
        e = arg0->f12->l2->arr[i];
        if (e->vX(arg2, 1) & 0xFF) break;
        i += 1;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_41(int *arg0, int arg1, int arg2) {
    int temp_s1;
    int var_s0;
    A_4550b0 *temp_a0;
    temp_s1 = *(int *)(*(int *)((char *)(arg0[3]) + 8) + 8);
    for (var_s0 = 0; var_s0 < temp_s1; var_s0++) {
        temp_a0 = (A_4550b0 *)(*(int *)(*(int *)(*(int *)((char *)(arg0[3]) + 8) + 16) + (var_s0 * 4)));
        if (temp_a0->vX(arg2, 0) & 0xFF) {
            break;
        }
    }
}

