void FUN_00308e00(PairOwnerView *arg0) {
    PairCallStatus sp3C, sp38;
    PairCountedObject *q;
    PairSourceView *x;
    if (arg0->f28 != 0) {
        arg0->f28 = 0;
        sp3C = arg0->f32->m104(0, 1);
        PairQueryTarget *z;
        q = arg0->f36;
        z = ((PairQueryHost * *)DAT_005871d0)[0]->m92();
        sp38 = z->m96(q);
        FUN_00305000((H_305000 *)arg0->f32);
        x = arg0->f32;
        if (x != 0) {
            ((PairCountedRef *)x)->f4 = ((PairCountedRef *)x)->f4 - 1;
            if (((unsigned long long) ((long long) ((PairCountedRef *)x)->f4 << 0x29) >> 0x29) == 0) igObject_Destroy(x);
        }
        arg0->f32 = 0;
        q = arg0->f36;
        if (q != 0) {
            q->f4 = q->f4 - 1;
            if (((unsigned long long) ((long long) q->f4 << 0x29) >> 0x29) == 0) igObject_Destroy(q);
        }
        arg0->f36 = 0;
    }
}

void Gap__Core__igResource__vfunc_12(T_308f00 *arg0) {
    S_ref *temp_a0;
    S_ref *temp_a0_2;

    if (arg0->f28 == 1) {
        FUN_00308e00((PairOwnerView *)arg0);
    }
    temp_a0 = arg0->f44;
    if (temp_a0 != 0) {
        temp_a0->f4 = temp_a0->f4 - 1;
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f44 = 0;
    temp_a0_2 = arg0->f48;
    if (temp_a0_2 != 0) {
        temp_a0_2->f4 = temp_a0_2->f4 - 1;
        if (((unsigned long long) ((long long) temp_a0_2->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0_2);
        }
    }
    arg0->f48 = 0;
    Gap__Core__igObject__vfunc_10((int)arg0);
}

void *FUN_003092f0(Item_3092f0 *arg0, int arg1) {
    Mem_3092f0 sp5C;
    Obj_3092f0 *sp58;
    R4_3092f0 sp54;
    Obj_3092f0 *r;
    int v;
    Obj_3092f0 *s3;
    int *old;
    int *hd;
    int c;
    Out_3092f0 *o;
    void *res;
    Obj_3092f0 *t;
    FUN_003087a0((R_3087a0 **)&sp58, (void *)arg0, arg1);
    r = sp58;
    if (r != 0) {
        r->refs = r->refs - 1;
        if (((unsigned long long)(long long)sp58->refs & 0x7fffffULL) == 0) igObject_Destroy(sp58);
    }
    if (r != 0) {
        FUN_002d9130((int *)r);
        return r;
    }
    sp5C.p = (Obj_3092f0 *)FUN_002c37e0((int)arg0->f56);
    ((Out_3092f0 *)sp5C.p)->f36 = arg0->f68;
    ((Out_3092f0 *)sp5C.p)->f164 = arg0->f72;
    ((Out_3092f0 *)sp5C.p)->f65 = arg0->f8;
    s3 = arg0->f56;
    if (s3 != 0) { ASSIGN_O(o, f280, s3) }
    s3 = arg0->f60;
    if (s3 != 0) { ASSIGN_O(o, f284, s3) }
    s3 = arg0->f64;
    if (s3 != 0) { ASSIGN_O(o, f288, s3) }
    if (arg0->f28 == 1) {
        ((Out_3092f0 *)sp5C.p)->f277 = arg0->f52;
        FUN_002d9330((DriverOwner *)sp5C.p);
    }
    ((Out_3092f0 *)sp5C.p)->f49 = 0;
    ((Out_3092f0 *)sp5C.p)->f48 = 1;
    o = (Out_3092f0 *)sp5C.p;
    if (DAT_00586f20[0] == 0) {
        v = ((int)FUN_002eb010(16));
        if (v != 0) v = ((int)StringPool_Construct((S_2eadf0 *)v));
        DAT_00586f20[0] = v;
    }
    v = StringPool_Intern((StringPool *)DAT_00586f20[0], (const char *)arg1);
    old = o->f20;
    if (old != 0) {
        hd = old - 2;
        c = old[-1] - 1;
        old[-1] = c;
        if (c == 0) StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hd), (int)hd);
    }
    o->f20 = (int *)v;
    ((Out_3092f0 *)sp5C.p)->f32 = arg0;
    FUN_002d9130((int *)sp5C.p);
    FUN_00308850((int *)arg0, (int)sp5C.p);
    if (arg0->f28 == 0) {
        res = ((void *)FUN_00309640((P_309640 *)arg0, (P_309640 *)sp5C.p));
        REL_O(sp5C.p)
        return res;
    }
    FUN_002d9130((int *)sp5C.p);
    sp54 = arg0->f32->v24(sp5C.p, 1);
    res = sp5C.p;
    REL_O(((Obj_3092f0 *)sp5C.p))
    return res;
}

P_309640 *FUN_00309640(P_309640 *arg0, P_309640 *arg1) {
    char buf[2048];
    int r;
    if (arg1 == 0) return 0;
    r = 0;
    if (arg0->f20 != 0 && strlen(arg0->f20) != 0) {
        sprintf(buf, &DAT_004f9a78[0], arg0->f20, arg1->f20);
        r = arg1->v116(buf) > 0;
    }
    if (r == 0) {
        if (arg0->f24 != 0 && strlen(arg0->f24) != 0) {
            sprintf(buf, &DAT_004f9a78[0], arg0->f24, arg1->f20);
            r = arg1->v116(buf) > 0;
        }
    }
    if (r == 0) {
        arg1->v116(arg1->f20);
    }
    return arg1;
}

void FUN_00309750(W_309750 *arg0, int arg1) {
    S1_309750 *sp3C;
    int temp_v0;
    bool var_s1;
    S1_309750 *temp_a0;
    S1_309750 *t;

    FUN_003087a0((R_3087a0 **)&sp3C, (void *)arg0, arg1);
    t = sp3C;
    if (t == 0) {
        if (t != 0) {
            t->f4 = (int)((int) (t->f4 - 1));
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    } else {
        var_s1 = 0;
        if (t == arg0->f12) {
            var_s1 = 1;
        }
        if (t->f32 == 0) {
            t->f32 = (S1_309750 *)arg0;
        }
        temp_v0 = FUN_002d91c0((RefCountedHandle *)sp3C);
        if (var_s1 && (temp_v0 <= 0)) {
            temp_a0 = arg0->f12;
            if (temp_a0 != 0) {
                temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0);
                }
            }
            arg0->f12 = 0;
        }
        t = sp3C;
        if (t != 0) {
            t->f4 = (int)((int) (t->f4 - 1));
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    }
}

void FUN_00309870(Ob_309870 *arg0) {
    int m;
    int j;
    Lst_309870 *l;
    int n;
    int i;
    R_309870 *p;
    R_309870 *q;

    l = arg0->f16;
    n = l->n;
    for (i = 0; i < n; i++) {
        p = l->data[i];
        if (p != 0) {
            p->refs = p->refs - 1;
            if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    m = l->n;
    for (j = 0; j < m; j++) {
        l->data[j] = 0;
    }
    l->n = 0;
    q = arg0->f12;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(q);
        }
    }
    arg0->f12 = 0;
}

void FUN_00309970(S_309970 *self) {
    int i;
    L_309970 *l;
    int off;
    Ob_309970 *o;
    for (i = self->list->count - 1; i >= 0; i--) {
        off = i * 4;
        if (igObject_IsKindOf((void *)(*(Ob_309970 **)((char *)self->list->data + off)), (igMetaObject *)(((int *)DAT_00586140)[0])) != 0) {
            l = self->list;
            o = *(Ob_309970 **)((char *)l->data + off);
            if (o != 0) {
                o->rc = o->rc - 1;
                if ((o->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy((void *)o);
                }
            }
            List_RemoveWordAt((L_2d6cf0 *)l, i);
            *(Ob_309970 **)((char *)l->data + l->count * 4) = 0;
        }
    }
}

int FUN_00309a50(void) {
    return *(int *)((char *)((*(void **)0x586DC8)) + 64);
}

void FUN_00309fe0(int arg0) {
    C1_309fe0 c;
    int s0m, s1m;
    void *s1;
    Rc_309fe0 *sp5C;
    if (arg0 != 0) {
        s0m = igObjectSystem_FindMetaByNameDefault((const char *)&DAT_004fb3b0[0]);
        if (s0m != 0) {
            s1 = ((void *)FUN_002d8eb0(arg0, (int)&DAT_004f9a50[0]));
            if (s1 != 0 && igObject_IsKindOf(s1, (igMetaObject *)s0m) != 0) {
                s1m = igObjectSystem_FindMetaByNameDefault((const char *)&DAT_004fb3b8[0]);
                if (s1m != 0) {
                    Rc_309fe0 *t;
                    Fld_309fe0 *f1, *f2, *f3;
                    void *l;
                    sp5C = (Rc_309fe0 *)igMetaObject_CreateInstanceDefault((void *)s1m);
                    t = *(Rc_309fe0 **)&sp5C;
                    if (t) t->refs = t->refs + 1;
                    {
                        Rc_309fe0 *u = sp5C;
                        u->refs = u->refs - 1;
                        if (((unsigned long long)(long long)u->refs & 0x7fffffULL) == 0) igObject_Destroy(u);
                    }
                    f1 = c.Cast(igMetaObject_FindFieldByName((igMetaObject *)(((V88_309fe0 *)sp5C)->vX()), (const char *)&DAT_004fb3c8[0]));
                    igObjectRefMetaField_Assign((igObjectRefMetaField *)f1, (void *)sp5C, (igObject *)s1);
                    f2 = c.Cast(igMetaObject_FindFieldByName((igMetaObject *)(((V88_309fe0 *)sp5C)->vX()), (const char *)&DAT_004fb3d8[0]));
                    f3 = c.Cast(igMetaObject_FindFieldByName((igMetaObject *)(((V88_309fe0 *)sp5C)->vX()), (const char *)&DAT_004fb3f0[0]));
                    l = c.CastL(*(void **)((char *)sp5C + f3->off));
                    if (l != 0) ObjectList_AppendUniqueRetained((igTDataList<igObject *> *)l, (igObject *)s1);
                    igObjectRefMetaField_Assign((igObjectRefMetaField *)f2, (void *)sp5C, (igObject *)0);
                    FUN_002d8310((void *)arg0, (void *)sp5C);
                    {
                        Rc_309fe0 *u = sp5C;
                        if (u != 0) {
                            u->refs = u->refs - 1;
                            if (((unsigned long long)(long long)u->refs & 0x7fffffULL) == 0) igObject_Destroy(u);
                        }
                    }
                }
            }
        }
    }
}

