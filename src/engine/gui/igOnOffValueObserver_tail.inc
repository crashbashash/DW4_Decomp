void igOnOffValueObserver_OnModelChange(igOnOffValueObserver *self, void *arg1) {
    if ((*(int *)((char *)arg1 + 8) == (int)g_igOnOffModel_valueMetaField) || (*(int *)((char *)arg1 + 0) == 0)) {
        FUN_00457ab0((igRadioGroup *)(self->_group), (igRadioGroupSelectedObserver *)self, (int)self);
    }
}

void FUN_00457c40(struct S_457c40 *arg0, unsigned char arg1) {
    int sp[3];
    unsigned char temp_a2;
    struct T_457c40 *temp_v1;
    unsigned char *pb;

    temp_v1 = arg0->t;
    if (temp_v1 != 0) {
        temp_a2 = temp_v1->b;
        pb = &temp_v1->b;
        if (temp_a2 != arg1) {
            *pb = arg1;
            sp[0] = 2;
            sp[1] = 0;
            sp[2] = (int)g_igOnOffModel_valueMetaField;
            igModel_NotifyViews((igModel *)arg0->t, (ModelChange *)sp);
        }
    }
}

void igRenderer_SetVisualContext(igRendererDispatchView *renderer, igVisualContext *context) {
    igVisualContext *old;
    igVisualContext *released;

    old = renderer->_visualContext;
    if (old != context) {
        if (old != 0) {
            renderer->terminateDrawing();
        }
        if (context != 0) {
            context->_refCount = context->_refCount + 1;
        }
        released = renderer->_visualContext;
        if (released != 0) {
            released->_refCount = released->_refCount - 1;
            if ((released->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(released);
            }
        }
        renderer->_visualContext = context;
        if (renderer->_visualContext != 0) {
            renderer->initializeDrawing();
        }
    }
}

