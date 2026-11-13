void Gap__Gui__igGuiComponent__vfunc_13(void *arg0) {
    Gap__Core__igObject__resetFields();
    *(int *)((char *)(*(int *)((char *)(arg0) + 28)) + 32) = (int)(arg0);
}

void FUN_00455470(A_455470 *arg0) {
    C *temp_a0;

    if (arg0->f20 != 0) {
        temp_a0 = arg0->f14;
        if (temp_a0 != 0) {
            igView_SetModel((S0_457e90 *)temp_a0, 0);
            arg0->f14->f0c = 0;
        }
        igView_SetModel((S0_457e90 *)arg0->f0c, 0);
        arg0->f10->f20 = 0;
        arg0->f20 = 0;
    }
}

void Gap__Gui__igGuiComponent__vfunc_10(void *arg0) {
    Gap__Core__igObject__userDestruct();
    if (*(unsigned char *)((char *)(arg0) + 32) != 0) {
        FUN_00455470((A_455470 *)arg0);
    }
}

int FUN_00455510(A_455510 *arg0) {
    int n = FUN_001c59e0();
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
    FUN_004558b0((S_4558b0 *)*(int *)((char *)p + 16), value);
}

void FUN_00455600(int *p, unsigned char value)
{
    FUN_00455900((S_455900 *)*(int *)((char *)p + 16), value);
}

void FUN_00455610(int *p, unsigned char value)
{
    FUN_00455950((S_455950 *)*(int *)((char *)p + 16), value);
}

unsigned char FUN_00455620(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 16)) + 15);
}

