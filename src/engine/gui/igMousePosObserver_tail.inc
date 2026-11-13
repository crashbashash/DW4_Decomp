static inline int count_of(const ObserverIntListView *list) { return list->cnt; }

static inline void setEvent(MousePosObserverView *self, const igSmartPointer<ObserverEventView> &event) {
    igObject *retained = event.get();
    ObserverModelView *model = self->m;
    igObject *previous;
    if (retained != 0) {
        retained->_refCount = retained->_refCount + 1;
    }
    previous = model->ref;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    model->ref = retained;
}

void Gap__Gui__igMousePosObserver__vfunc_13(MousePosObserverView *self) {
    ObserverEventView *created;
    ObserverIntListView *list;
    int top;
    Gap__Core__igObject__resetFields(self);
    igSmartPointer<ObserverEventView> event(igProbe_Create(igObject_GetAllocator(self)));
    created = event.get();
    ObjectList_AppendRetained(created->a, self->f20);
    list = created->list;
    top = count_of(list);
    if (top < list->cap) {
        list->cnt = list->cnt + 1;
    } else {
        List_Resize(list, top + 1, 4);
    }
    list->data[top] = 2;
    setEvent(self, event);
    self->m->flags = 0;
    self->m->flags = self->m->flags | 4;
    self->m->fn = (int)&FUN_00455ad0;
}

struct Vec3f_455d80 { float x; float y; float z; Vec3f_455d80() {} Vec3f_455d80(float a, float b, float c) : x(a), y(b), z(c) {} };
struct GuiMessage_455d80 { int handled; int f4; int type; };
void Gap__Gui__igMousePosObserver__vfunc_24(igMousePosObserver *self, struct GuiMessage_455d80 *msg) {
    igGuiSystemModel *model;
    int type;
    model = (igGuiSystemModel *)self->_model;
    type = msg->type;
    if (type == g_igGuiSystemModelMousePositionField[0]) {
        Vec3f_455d80 v(model->_mousePosition[0], model->_mousePosition[1], 0.0f);
        Vec3f_455d80 p;
        Vec3f_TransformProjective(&v, &v, self->_inverseProjectionMatrix);
        p = v;
        FUN_00456b80((int *)self->_guiSystem, &p.x);
        FUN_00456050(self, model);
    } else if (type == DAT_0058c3f0[0]) {
        int result;
        Matrix44_Invert(&result, self->_inverseProjectionMatrix, model->_projectionMatrix);
    } else if (type == DAT_0058c3e0[0]) {
        igObject *under;
        int m[4];
        under = (igObject *)model->_componentUnderMouse;
        if ((igObject *)model->_focusedComponent != under) {
            FUN_00456c20(model, (igGuiComponent *)under);
        }
        if (model->_mousePressed) {
            if (under != 0) {
                under->_refCount = under->_refCount + 1;
            }
            igRelease((igObject *)model->_pushedComponent);
            model->_pushedComponent = (int)under;
        } else {
            igRelease((igObject *)model->_pushedComponent);
            model->_pushedComponent = 0;
        }
        m[0] = 2;
        m[1] = 0;
        m[2] = DAT_0058c418[0];
        igModel_NotifyViews((S_4578c0 *)model, (S_4578c0 *)m);
    } else if (msg->handled == 0) {
        int result;
        Matrix44_Invert(&result, self->_inverseProjectionMatrix, model->_projectionMatrix);
    }
}

static inline void setPick(Z *z, const igSmartPointer<Obj_455f50> &value) {
    Obj_455f50 *held = value.get();
    Obj_455f50 *old;
    if (held != 0) held->_refCount = held->_refCount + 1;
    old = z->f32;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    z->f32 = held;
}

void FUN_00455f50(Z *arg0, Y *arg1) {
    int s1 = arg1->f8;
    if (arg1->f20 <= arg0->f24) {
        arg0->f28 = 1;
        arg0->f24 = arg1->f20;
        setPick(arg0, igSmartPointer<Obj_455f50>(igGraphPath_Create(igObject_GetAllocator(arg0))));
        igGraphPath_SetNodes(arg0->f32, s1);
    }
}

/* matching construct: the *Ref fields are 4-byte arena handles in the reflected structs; the casts give the typed views (no layout effect) */
void FUN_00456050(igMousePosObserver *a, igGuiSystemModel *b) {
    float v2[3];
    float v1[3];
    int sp[3];
    igObject *s0 = 0;
    if (b->_rootComponent != 0) {
        float x, y;
        igObject *t;
        igIntersectTraversal_ResetStacks((void *)a->_intersectTraversal);
        x = ((float *)b->_mousePosition)[0];
        y = ((float *)b->_mousePosition)[1];
        v2[0] = x; v2[1] = y; v2[2] = -10.0f;
        v1[0] = x; v1[1] = y; v1[2] = 10.0f;
        igRay_SetFromPoints((void *)a->_ray, v2, v1);
        igRay_Transform((void *)a->_ray, &a->_inverseProjectionMatrix);
        a->_impactLength = ((igRay *)a->_ray)->_len;
        a->_hit = 0;
        t = (igObject *)a->_hitPath;
        if (t != 0) {
            t->_refCount = t->_refCount - 1;
            if (((unsigned long long)((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        a->_hitPath = 0;
        DAT_0058c678[0] = (int)a;
        ((IntersectTraversalCalls *)a->_intersectTraversal)->v23(((igGuiComponent *)b->_rootComponent)->_node);
        DAT_0058c678[0] = 0;
        if (a->_hit != 0) {
            s0 = (igObject *)FUN_00455510((A_455510 *)((void *)a->_hitPath));
        }
    }
    if (s0 != 0) {
        s0->_refCount = s0->_refCount + 1;
    }
    {
        igObject *t = (igObject *)b->_componentUnderMouse;
        if (t != 0) {
            t->_refCount = t->_refCount - 1;
            if (((unsigned long long)((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    b->_componentUnderMouse = (int)s0;
    sp[0] = 2;
    sp[1] = (int)a;
    sp[2] = DAT_0058c410[0];
    igModel_NotifyViews((S_4578c0 *)b, (S_4578c0 *)sp);
}

