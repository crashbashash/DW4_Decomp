int igNode_GetMeta(void) {
    return ((int)g_igNode_metaObject);
}

void igGraphPath_GetTransform(igGraphPath *path, igMatrix44f *matrix, long long time) {
    FUN_001c59f0((OO *)path, igGraphPath_GetCount(path), (int)matrix, time);
}

void igGroup_UserPostLoad(SgLinkNode *o) {
    int n;
    int i;
    SgLinkNode *c;
    int have;
    int j;
    SgChildList *l;
    int want;
    int t;
    SgChildList *m;
    int k;
    igNode_UserPostLoad((igNode *)o);
    n = 0;
    if (o->_children != 0) n = o->_children->_count;
    for (i = 0; i < n; i++) {
        c = o->_children->_data[i];
        if (c != 0) {
            have = 0;
            l = o->_children;
            j = 0;
            goto guardHave;
        nextHave:
            if (l->_data[j] == c) have++;
            j++;
        testHave:
            if (j < n) goto nextHave;
        doneHave:
            m = c->_parents;
            want = 0;
            t = m->_count;
            k = 0;
            goto guardWant;
        nextWant:
            if (m->_data[k] == o) want++;
            k++;
        testWant:
            if (k < t) goto nextWant;
        doneWant:
            for (j = want; j < have; j++) c->attach(o);
            for (; have < want; have++) c->detach(o);
        }
    }
    return;
guardWant:
    if (0 < t) goto testWant;
    goto doneWant;
guardHave:
    if (0 < n) goto testHave;
    goto doneHave;
}

int igGroup_AppendChild(igGroup *group, igNode *child) {
    int var_s0;
    void *temp_v0;

    temp_v0 = (void *)(*(int *)((char *)(group) + 28));
    if (temp_v0 != 0) {
        var_s0 = *(int *)((char *)(temp_v0) + 8);
    } else {
        var_s0 = 0;
    }
    if (((DW4VC_140_2 *)(((char *)(group) + 0)))->vX((int)(var_s0), (int)(child)) != 0) {
        return var_s0 + 1;
    }
    return -1;
}

int igGroup_InsertChild(T_1c5d70 *self, int a1, O_1c5d70 *a2) {
    if (a2 == 0) return 0;
    if (a2->vX(self) != 0) {
        R_1c5d70 r;
        int f;
        r.p = a2;
        f = self->f28;
        if (r.p != 0) r.p->f4 = r.p->f4 + 1;
        List_InsertWords((igDataList *)f, a1, 1, &r);
        FUN_001d32f0((S_1d32f0 *)self, a2->f20);
        return 1;
    } else {
        return 0;
    }
}

void igGroup_userDestruct(T_1c5e20 *arg0) {
    unsigned int var_s0;
    unsigned int var_s2;
    L_1c5e20 *temp_v0;

    temp_v0 = arg0->f28;
    if (temp_v0 != 0) {
        var_s0 = temp_v0->f8;
    } else {
        var_s0 = 0;
    }
    for (var_s2 = 0; var_s2 < var_s0; var_s2++) {
        arg0->f28->f16[var_s2]->vX(arg0);
    }
    igNode_userDestruct((igObject *)arg0);
}

igSmartPointer<igNode> igGroup_RemoveChildAt(igGroup *group, int idx) {
    List_1c5eb0 *l0 = ((S_1c5eb0 *)group)->getList();
    int n = l0 ? l0->n : 0;
    if (idx < n) {
        igSmartPointer<igNode> obj((igNode *)((S_1c5eb0 *)group)->list->data[idx], kRetainReference);
        ((Obj_1c5eb0 *)obj.p)->vX((S_1c5eb0 *)group);
        List_1c5eb0 *l = (List_1c5eb0 *)group->_childList;
        Obj_1c5eb0 *e = l->data[idx];
        if (e) {
            --e->refs;
            if (((unsigned long long)(long long)e->refs & 0x7fffffULL) == 0) igObject_Destroy((igObject *)e);
        }
        List_RemoveWordAt((igDataList *)l, idx);
        l->data[l->n] = 0;
        FUN_001c6110((O_1c6110 *)group, ((Obj_1c5eb0 *)obj.p)->f20);
        return obj;
    }
    return igSmartPointer<igNode>(0, kRetainReference);
}

unsigned int igGroup_RemoveChild(igGroup *group, igNode *node) {
    S_1c5eb0 *host = (S_1c5eb0 *)group;
    Obj_1c5eb0 *child = (Obj_1c5eb0 *)node;
    List_1c5eb0 *l;
    unsigned int n;
    unsigned int i;
    bool found;
    l = host->getList();
    n = 0;
    if (l != 0) {
        n = l->n;
    }
    found = false;
    for (i = 0; i < n; i++) {
        if (host->list->data[i] == child) {
            found = true;
            break;
        }
    }
    if (found) {
        igGroup_RemoveChildAt(group, i);
        return i;
    }
    return -1U;
}

void FUN_001c6110(O_1c6110 *arg0, int arg1) {
    int t1, i;
    Lst_1c6110 *a3;
    int a2, m, s2;
    a2 = ~arg0->v120();
    m = DAT_0048da58[0];
    arg1 = a2 & (arg1 & m);
    if (arg1 != 0) {
        a3 = arg0->f28;
        t1 = 0;
        i = 0;
        while (i < (a3 != 0 ? a3->cnt : 0)) {
            t1 |= a3->arr[i]->f20;
            i++;
        }
        s2 = a2 & (m & (arg1 & ~t1));
        if (s2 != 0) {
            arg0->v112(s2, 0);
            arg1 = 0;
            while (arg1 < arg0->v92()) {
                FUN_001c6110((O_1c6110 *)arg0->v96(arg1), s2);
                arg1++;
            }
        }
    }
}

void igNode_EnableFlags(struct S_1c6230 *arg0, int arg1, int arg2) {
    if (arg2 != 0) {
        arg0->f = arg0->f | arg1;
    } else {
        arg0->f = arg0->f & ~arg1;
    }
}

