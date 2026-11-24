void igGuiComponent_resetFields(igGuiComponent *self, int flags) {
    Gap__Core__igObject__resetFields((igObject *)self, flags);
    *(int *)((char *)(self->_node) + 32) = (int)(self);
}

void FUN_00455470(A_455470 *arg0) {
    C *temp_a0;

    if (arg0->f20 != 0) {
        temp_a0 = arg0->f14;
        if (temp_a0 != 0) {
            ((Gap::Gui::igView *)temp_a0)->setModel(0);
            arg0->f14->f0c = 0;
        }
        ((Gap::Gui::igView *)arg0->f0c)->setModel(0);
        arg0->f10->f20 = 0;
        arg0->f20 = 0;
    }
}

void igGuiComponent_userDestruct(igGuiComponent *self) {
    Gap__Core__igObject__userDestruct((igObject *)self);
    if (self->_linked != 0) {
        FUN_00455470((A_455470 *)self);
    }
}

int FUN_00455510(A_455510 *arg0) {
    int n = ((Gap::Sg::igGraphPath *)arg0)->getDepth();
    int i;
    O_455510 *o;
    if (n <= 0) return 0;
    i = n - 1;
    while (i >= 0) {
        o = O_455510::cast(arg0->b->arr[i]);
        if (o != 0) return o->v;
        i--;
    }
    return 0;
}

void *FUN_004555c0(igGuiComponentView *self, void *component, void *context)
{
    return self->_controller->vfunc_23(component, context);
}

int FUN_004555e0(void *arg0) {
    return *(unsigned char *)((char *)(*(int *)((char *)(arg0) + 16)) + 12);
}

void FUN_004555f0(int *p, unsigned char value)
{
    ((Gap::Gui::igGuiComponentModel *)(*(int *)((char *)p + 16)))->setHasFocus(value);
}

void FUN_00455600(int *p, unsigned char value)
{
    ((Gap::Gui::igGuiComponentModel *)(*(int *)((char *)p + 16)))->setMouseOver(value);
}

void FUN_00455610(int *p, unsigned char value)
{
    ((Gap::Gui::igGuiComponentModel *)(*(int *)((char *)p + 16)))->setPushed(value);
}

unsigned char FUN_00455620(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 16)) + 15);
}

