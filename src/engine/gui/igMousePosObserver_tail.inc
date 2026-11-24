static inline int count_of(const ObserverIntListView *list) { return list->cnt; }

static inline void setEvent(MousePosObserverView *self, const igSmartPointer<ObserverEventView> &event) {
    igObject *retained = event.get();
    ObserverModelView *model = self->m;
    igObject *previous;
    igObject::ref(retained);
    previous = model->ref;
    igObject::release(previous);
    model->ref = retained;
}

void igMousePosObserver_resetFields(MousePosObserverView *self, int flags) {
    ObserverEventView *created;
    ObserverIntListView *list;
    int top;
    Gap__Core__igObject__resetFields((igObject *)self, flags);
    igSmartPointer<ObserverEventView> event((ObserverEventView *)Gap::Sg::igProbe::_instantiateFromPool(((Gap::Core::igObject *)self)->getMemoryPool()));
    created = event.get();
    ((Gap::Core::igObjectList *)created->a)->append((Gap::Core::igObject *)self->f20);
    list = created->list;
    top = count_of(list);
    if (top < list->cap) {
        list->cnt = list->cnt + 1;
    } else {
        ((Gap::Core::igDataList *)list)->resizeAndSetCount(top + 1, 4);
    }
    list->data[top] = 2;
    setEvent(self, event);
    self->m->flags = 0;
    self->m->flags = self->m->flags | 4;
    self->m->fn = (int)&FUN_00455ad0;
}

struct GuiMessage_455d80 { int handled; int f4; int type; };
void igMousePosObserver_OnModelChange(igMousePosObserver *self, struct GuiMessage_455d80 *msg) {
    igGuiSystemModel *model;
    int type;
    model = (igGuiSystemModel *)self->_model;
    type = msg->type;
    if (type == (int)Gap::Gui::igGuiSystemModel::k_mousePosition) {
        igVec3f v(model->_mousePosition[0], model->_mousePosition[1], 0.0f);
        igVec3f p;
        Vec3f_TransformProjective((float *)&v, (const float *)&v, self->_inverseProjectionMatrix);
        p = v;
        FUN_00456b80((int *)self->_guiSystem, &p.vec[0]);
        FUN_00456050(self, model);
    } else if (type == (int)Gap::Gui::igGuiSystemModel::k_projectionMatrix) {
        igMatrix44f_Invert(self->_inverseProjectionMatrix, model->_projectionMatrix);
    } else if (type == (int)Gap::Gui::igGuiSystemModel::k_mousePressed) {
        igObject *under;
        under = (igObject *)model->_componentUnderMouse;
        if ((igObject *)model->_focusedComponent != under) {
            ((Gap::Gui::igGuiSystemModel *)model)->setFocusedComponent((igGuiComponent *)under);
        }
        if (model->_mousePressed) {
            igObject::ref(under);
            igObject::release((igObject *)model->_pushedComponent);
            model->_pushedComponent = (int)under;
        } else {
            igObject::release((igObject *)model->_pushedComponent);
            model->_pushedComponent = 0;
        }
        igNotifyEvent m((Gap::Core::igMetaField *)Gap::Gui::igGuiSystemModel::k_pushedComponent);
        ((Gap::Gui::igModel *)model)->notifyAllViews(m);
    } else if (msg->handled == 0) {
        igMatrix44f_Invert(self->_inverseProjectionMatrix, model->_projectionMatrix);
    }
}

static inline void setPick(Z *z, const igSmartPointer<Obj_455f50> &value) {
    Obj_455f50 *held = value.get();
    Obj_455f50 *old;
    if (held != 0) held->_refCount = held->_refCount + 1;
    old = z->f32;
    igObject::release(old);
    z->f32 = held;
}

void FUN_00455f50(Z *arg0, Y *arg1) {
    int s1 = arg1->f8;
    if (arg1->f20 <= arg0->f24) {
        arg0->f28 = 1;
        arg0->f24 = arg1->f20;
        setPick(arg0, igSmartPointer<Obj_455f50>((Obj_455f50 *)Gap::Sg::igGraphPath::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool())));
        ((Gap::Sg::igGraphPath *)arg0->f32)->configure((Gap::Sg::igNodeList *)s1);
    }
}

/* matching construct: the *Ref fields are 4-byte arena handles in the reflected structs; the casts give the typed views (no layout effect) */
void FUN_00456050(igMousePosObserver *a, igGuiSystemModel *b) {
    float v2[3];
    float v1[3];
    igObject *s0 = 0;
    if (b->_rootComponent != 0) {
        float x, y;
        igObject *t;
        ((Gap::Sg::igIntersectTraversal *)((void *)a->_intersectTraversal))->reset();
        x = b->_mousePosition[0];
        y = b->_mousePosition[1];
        v2[0] = x; v2[1] = y; v2[2] = -10.0f;
        v1[0] = x; v1[1] = y; v1[2] = 10.0f;
        igRay_SetFromPoints((igRay *)a->_ray, v2, v1);
        igRay_Transform((igRay *)a->_ray, (const float *)&a->_inverseProjectionMatrix);
        a->_impactLength = ((igRay *)a->_ray)->_len;
        a->_hit = 0;
        t = (igObject *)a->_hitPath;
        igObject::release(t);
        a->_hitPath = 0;
        g_activeMousePosObserver = (int)a;
        ((IntersectTraversalCalls *)a->_intersectTraversal)->v23(((igGuiComponent *)b->_rootComponent)->_node);
        g_activeMousePosObserver = 0;
        if (a->_hit != 0) {
            s0 = (igObject *)FUN_00455510((A_455510 *)((void *)a->_hitPath));
        }
    }
    igObject::ref(s0);
    {
        igObject *t = (igObject *)b->_componentUnderMouse;
        igObject::release(t);
    }
    b->_componentUnderMouse = (int)s0;
    igNotifyEvent sp((Gap::Core::igMetaField *)Gap::Gui::igGuiSystemModel::k_componentUnderMouse, (Gap::Gui::igView *)(int)a);
    ((Gap::Gui::igModel *)b)->notifyAllViews(sp);
}

