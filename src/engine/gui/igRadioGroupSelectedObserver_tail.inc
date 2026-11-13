void FUN_00457a10(struct RadioGroupView *s) {
    struct RadioButtonListView *b;
    int idx;
    int c;
    idx = s->a->sel;
    if (s->cur != idx) {
        b = s->b;
        if (idx < b->n) {
            if (idx >= 0) {
                FUN_00457c40((S_457c40 *)b->arr[idx], 1);
            }
            c = s->cur;
            if (c >= 0) {
                FUN_00457c40((S_457c40 *)s->b->arr[c], 0);
            }
            s->cur = s->a->sel;
        }
    }
}

void FUN_00457ab0(igRadioGroup *arg0, igRadioGroupSelectedObserver *arg1, int arg2) {
    int idx;
    int flag;
    igObjectList *l;
    igRadioGroupModel *s;
    int *pf;
    l = (igObjectList *)arg0->_observerList;
    flag = ((igOnOffModel *)arg1->_model)->_value;
    K_457ab0 key(arg1);
    idx = Finder_457ab0::Find(l, key);
    if (flag != 0) {
        s = (igRadioGroupModel *)arg0->_model;
        pf = &s->_selected;
        if (idx != s->_selected) {
            *pf = idx;
            Msg m;
            m.a = 2;
            m.b = 0;
            m.c = DAT_0058c280[0];
            igModel_NotifyViews((S_4578c0 *)((void *)arg0->_model), (S_4578c0 *)&m);
        }
    } else {
        s = (igRadioGroupModel *)arg0->_model;
        pf = &s->_selected;
        if (idx == s->_selected) {
            if (arg0->_alwaysSelected != 0) {
                FUN_00457c40((S_457c40 *)arg1, 1);
                return;
            }
            *pf = -1;
            Msg m2;
            m2.a = 2;
            m2.b = 0;
            m2.c = DAT_0058c280[0];
            igModel_NotifyViews((S_4578c0 *)((void *)arg0->_model), (S_4578c0 *)&m2);
        }
    }
}

void Gap__Gui__igRadioGroupSelectedObserver__vfunc_24(void *arg0, void *arg1) {
    int temp_a1;

    temp_a1 = *(int *)((char *)arg1 + 8);
    if (temp_a1 == *(int *)0x58C280) {
        FUN_00457a10((RadioGroupView *)*(int *)((char *)arg0 + 12));
    }
}

