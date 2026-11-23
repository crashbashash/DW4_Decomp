void Gap__Gui__igDefaultAspect__vfunc_25(igDefaultAspect *arg0) {
    int i;
    void *l;

    for (i = 0; l = (void *)arg0->_elementList, i < *(int *)((char *)l + 8); i++) {
        ((Gap::Sg::igGroup *)arg0->_node)->appendChild((Gap::Sg::igNode *)(*(int *)((char *)((*(int *)(*(int *)((char *)l + 16) + (i * 4)))) + 16)));
    }
    FUN_004540d0((S_4540d0 *)arg0);
    igDefaultAspect_UpdateMinimumSize(arg0);
}

/* matching construct: hand variant — comparing through pointers makes the compiler reload the
 * first component for the store, as retail does. */
static inline void raiseTo(float *max, const float *v) {
    if (*max < *v) *max = *v;
}

/* Grows the aspect's minimum size to the largest element and notifies the model. */
void igDefaultAspect_UpdateMinimumSize(igDefaultAspect *self) {
    float maxX, maxY, maxZ;
    int i;
    T_453f70 *model;

    maxZ = maxY = maxX = 0.0f;
    for (i = 0; i < ((igDefaultAspectElementList *)self->_elementList)->_count; i++) {
        igVec3f size = FUN_00453b90(((A **)((igDefaultAspectElementList *)self->_elementList)->_data)[i]);
        raiseTo(&maxX, size.vec);
        raiseTo(&maxY, &size.vec[1]);
        raiseTo(&maxZ, &size.vec[2]);
    }
    self->_minSize[0] = maxX;
    self->_minSize[1] = maxY;
    self->_minSize[2] = maxZ;
    model = (T_453f70 *)self->_model;
    model->f16 = maxX;
    model->f20 = maxY;
    model->f24 = maxZ;
    igNotifyEvent msg((Gap::Core::igMetaField *)Gap::Gui::igGuiComponentModel::k_size);
    ((Gap::Gui::igModel *)self->_model)->notifyAllViews(msg);
}

void Gap__Gui__igDefaultAspect__vfunc_26(A_453f70 *arg0) {
    int var_s0;
    T_453f70 *temp_v1;

    var_s0 = arg0->f40->count - 1;
    while (var_s0 >= 0) {
        ((Gap::Sg::igGroup *)arg0->f12)->removeChild(var_s0);
        var_s0 -= 1;
    }
    temp_v1 = arg0->f8;
    temp_v1->f16 = g_vec3Zero[0];
    temp_v1->f20 = DAT_004e105c[0];
    temp_v1->f24 = DAT_004e1060[0];
    igNotifyEvent sp30((Gap::Core::igMetaField *)Gap::Gui::igGuiComponentModel::k_size);
    ((Gap::Gui::igModel *)arg0->f8)->notifyAllViews(sp30);
}

void Gap__Gui__igDefaultAspect__vfunc_27(void *arg0, struct S_454050 *arg1) {
    int temp_a1;

    temp_a1 = arg1->f8;
    if ((temp_a1 == (int)Gap::Gui::igGuiComponentModel::k_hasFocus) || (temp_a1 == (int)Gap::Gui::igGuiComponentModel::k_pushed) || (temp_a1 == (int)Gap::Gui::igOnOffModel::k_value) || (temp_a1 == (int)Gap::Gui::igGuiComponentModel::k_enabled)) {
        FUN_004540d0((S_4540d0 *)arg0);
        return;
    }
    if (temp_a1 == (int)Gap::Gui::igGuiComponentModel::k_size) {
        FUN_00454180(arg0);
    }
}

void FUN_004540d0(S_4540d0 *arg0) {
    int i;
    E *e;
    float *v;
    V96 *o;

    for (i = 0; i < arg0->f40->count; i++) {
        e = arg0->f40->data[i];
        v = e->f12->vX(arg0->f8);
        o = e->f8;
        o->f24 = v[0];
        o->f28 = v[1];
        o->f32 = v[2];
        o->f36 = v[3];
        o->vX();
    }
}

void FUN_00454180(void *arg0) {
    int i;
    int *t;
    i = 0;
    while (t = *(int **)((char *)arg0 + 40), i < t[2]) {
        igDefaultAspectElement_PlaceGeometry(((igDefaultAspectElement **)t[4])[i], (const igVec3f *)(*(int *)((char *)(arg0) + 8) + 0x10));
        i += 1;
    }
}

void FUN_004541f0(int *arg0, int *arg1) {
    int sp3C;
    int sp38;
    ((C22 *)arg0[4])->vX(arg1);
    ((C22 *)arg0)->vX((int *)arg0[4]);
    ((C22 *)arg0)->vX(arg1);
    ((C30 *)arg1)->vX(&sp3C, &sp38);
    ((C28 *)arg0)->vX(arg1, sp3C, sp38);
}

void igEventDispatcher_AddReceiver(igEventDispatcher *dispatcher, igObject *receiver) {
    igRendererOrderedList_Append((igDependencyOrderedList *)dispatcher->_receivers, receiver, 0);
}

void igEventDispatcher_RemoveReceiver(igEventDispatcher *dispatcher, igObject *receiver) {
    igObjectList_RemoveRetained((igDependencyOrderedList *)dispatcher->_receivers, receiver);
}

void igEventDispatcher_AddReceiverOrder(igEventDispatcher *dispatcher, igObject *first, igObject *second)
{
    igDependencyOrderedList_AddDependency((igDependencyOrderedList *)dispatcher->_receivers, first, second);
}

void igEventDispatcher_RemoveReceiverOrder(igEventDispatcher *dispatcher, igObject *first, igObject *second) {
    igDependencyOrderedList_RemoveDependency((igDependencyOrderedList *)dispatcher->_receivers, first, second);
}

