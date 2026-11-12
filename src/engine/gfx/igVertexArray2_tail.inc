igVertexData *igVertexArray2__FindVertexData(A_15f430 *arg0, int arg1, int arg2) {
    void *res;
    int i;
    O_15f430 *o;
    int n;
    res = 0;
    n = arg0->l->n;
    for (i = 0; i < n; i++) {
        o = (O_15f430 *)dw4_cast_or_null((char *)arg0->l->data[i], (int *)g_igVertexData_metaObject);
        if (arg1 == o->k0 && arg2 == o->k1) {
            res = o;
            break;
        }
    }
    return (igVertexData *)res;
}

void FUN_0015f660(igVertexArray2 *arg0, igSmartPointer<Rc_17f2b0> list) {
    int i;
    void *x;
    void *r;
    ObjectList_ResizeRetained((int)list.p, 0);
    for (i = 0; i < *(int *)(*(int *)((char *)arg0 + 16) + 8); i++) {
        x = (void *)*(int *)(*(int *)(*(int *)((char *)arg0 + 16) + 16) + i * 4);
        if (x != 0 && igObject_IsKindOf(x, g_igVertexData_metaObject[0]) != 0) {
            r = x;
        } else {
            r = 0;
        }
        if (r != 0 && FUN_00164d60((int)arg0, (A_164d60 *)r) != 0) {
            ObjectList_AppendRetained(list.p, r);
        }
    }
}

/* matching construct: _data is a 4-byte reference field; the casts give the typed views (no layout effect) */
int Gap__Gfx__igVertexArray2__vfunc_25(int arg0, int arg1) {
    igVertexData *h = (igVertexData *)igVertexArray2__FindVertexData((A_15f430 *)arg0, 1, arg1);
    if (h != 0) {
        int t = g_igVec3fList_metaObject[0];
        if (t == ((C_15f730 *)h->_data)->v20()) {
            return ((igDataList *)h->_data)->_count;
        }
        t = DAT_005610a8[0];
        if (t == ((C_15f730 *)h->_data)->v20()) {
            return ((igDataList *)h->_data)->_count;
        }
    }
    return 0;
}

