void Gap__Attrs__igDisplayListAttr__vfunc_24(S_13cc30 *arg0, int arg1) {
    L *temp_v1 = arg0->f12;
    VC_13cc30 **var_s1 = temp_v1->a;
    VC_13cc30 **temp_s0 = var_s1 + temp_v1->n;
    while (var_s1 < temp_s0) {
        (*var_s1)->vX(arg1);
        var_s1 += 1;
    }
}

void Gap__Attrs__igDisplayListAttr__vfunc_29(int *arg0, int arg1) {
    int *c = (int *)arg0[3];
    unsigned int s = c[4];
    unsigned int e = s + c[2] * 4;
    while (s < e) {
        ((VC_13cca0 *)*(int *)s)->vX(arg1);
        s += 4;
    }
}

void FUN_0013cd10(igAttrView *self)
{
    self->vfunc_22();
}

