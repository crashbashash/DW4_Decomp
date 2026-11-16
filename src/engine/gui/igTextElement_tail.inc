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

void igView_SetModel(igView *view, igModel *model) {
    int old;
    int current;

    old = view->_model;
    if (old != 0) {
        FUN_004577f0((igModel *)old, (OV *)view);
    }
    view->_model = (int)model;
    current = view->_model;
    if (current != 0) {
        FUN_004576d0((igContext *)current, (ContextHandler *)view);
    }
}

