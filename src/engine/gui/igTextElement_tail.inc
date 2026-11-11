void Gap__Gui__igTextElement__vfunc_23(igTextElement *self) {
}

void Gap__Gui__igTextElement__vfunc_24(O_457e10 *arg0) {
    int n;
    int i;
    struct Q_457e10 *q = (struct Q_457e10 *)arg0->m->obj;
    if (q != 0) {
        n = q->count;
        for (i = 0; i < n; i++) {
            arg0->m->obj->vX(i, arg0->buf);
        }
    }
}

void FUN_00457e90(S0_457e90 *arg0, int arg1) {
    int temp_a0;
    int temp_a0_2;

    temp_a0 = arg0->f8;
    if (temp_a0 != 0) {
        FUN_004577f0((igModel *)temp_a0, (OV *)arg0);
    }
    arg0->f8 = arg1;
    temp_a0_2 = arg0->f8;
    if (temp_a0_2 != 0) {
        FUN_004576d0((igContext *)temp_a0_2, (ContextHandler *)arg0);
    }
}

