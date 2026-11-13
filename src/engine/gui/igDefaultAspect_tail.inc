void Gap__Gui__igDefaultAspect__vfunc_25(igDefaultAspect *arg0) {
    int i;
    void *l;

    for (i = 0; l = (void *)arg0->_elementList, i < *(int *)((char *)l + 8); i++) {
        igGroup_AppendChild(arg0->_node, *(int *)((char *)((*(int *)(*(int *)((char *)l + 16) + (i * 4)))) + 16));
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
        raiseTo(&maxX, &size.x);
        raiseTo(&maxY, &size.y);
        raiseTo(&maxZ, &size.z);
    }
    self->_minSize[0] = maxX;
    self->_minSize[1] = maxY;
    self->_minSize[2] = maxZ;
    model = (T_453f70 *)self->_model;
    model->f16 = maxX;
    model->f20 = maxY;
    model->f24 = maxZ;
    int msg[3];
    msg[0] = 2;
    msg[1] = 0;
    msg[2] = DAT_0058c468[0];
    igModel_NotifyViews((S_4578c0 *)self->_model, (S_4578c0 *)msg);
}

void Gap__Gui__igDefaultAspect__vfunc_26(A_453f70 *arg0) {
    R_453f70 *sp4C;
    int sp30[7];
    int var_s0;
    T_453f70 *temp_v1;

    var_s0 = arg0->f40->count - 1;
    while (var_s0 >= 0) {
        igGroup_RemoveChildAt(&sp4C, arg0->f12, var_s0);
        if (sp4C != 0) {
            sp4C->refs = sp4C->refs - 1;
            if (((unsigned long long)((long long)sp4C->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(sp4C);
            }
        }
        var_s0 -= 1;
    }
    temp_v1 = arg0->f8;
    temp_v1->f16 = g_vec3Zero[0];
    temp_v1->f20 = DAT_004e105c[0];
    temp_v1->f24 = DAT_004e1060[0];
    sp30[0] = 2;
    sp30[1] = 0;
    sp30[2] = DAT_0058c468[0];
    igModel_NotifyViews((S_4578c0 *)arg0->f8, (S_4578c0 *)&sp30[0]);
}

void Gap__Gui__igDefaultAspect__vfunc_27(void *arg0, struct S_454050 *arg1) {
    int temp_a1;

    temp_a1 = arg1->f8;
    if ((temp_a1 == DAT_0058c450[0]) || (temp_a1 == DAT_0058c460[0]) || (temp_a1 == DAT_0058c290[0]) || (temp_a1 == DAT_0058c448[0])) {
        FUN_004540d0((S_4540d0 *)arg0);
        return;
    }
    if (temp_a1 == DAT_0058c468[0]) {
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

void igEventDispatcher_AddReceiver(void *arg0, int arg1) {
    igRendererOrderedList_Append(*(int *)((char *)(arg0) + 12), arg1, 0);
}

void igEventDispatcher_RemoveReceiver(Obj_4542a0 *arg0, int arg1) {
    int sp1C;
    FUN_002d7750(&sp1C, arg0->f12, arg1);
}

int igEventDispatcher_AddReceiverOrder(int *p)
{
    return FUN_002d7090(*(int *)((char *)p + 12));
}

void FUN_004542e0(S0 *arg0, int arg1, int arg2) {
    int sp1C;

    FUN_002d7760(&sp1C, arg0->fC, arg1, arg2);
}

