bool FUN_0013e6e0(igGeometrySetAttr *arg0, int arg1) {
    bool ok;
    int t;
    Item **p;
    Item **end;
    t = Gap__Gfx__igPsx2VisualContext__vfunc_192(arg1);
    if (t < 0) {
        arg0->_renderListState = 0;
        return false;
    }
    Gap__Gfx__igPsx2VisualContext__vfunc_194(arg1, t);
    ok = true;
    p = (Item **)((igGeometryAttrList *)arg0->_geometryAttrList)->_data;
    end = p + ((igGeometryAttrList *)arg0->_geometryAttrList)->_count;
    for (; p < end; p++) {
        if (igObject_IsKindOf(*p, *(int *)g_igGeometryAttr_metaObject) == 0) {
            ok = false;
            break;
        }
        (*p)->v22(arg1);
    }
    if ((Gap__Gfx__igPsx2VisualContext__vfunc_195(arg1) & 0xFF) && ok) {
        ((Self *)arg0)->v30(arg1);
        arg0->_renderListHandle = t;
        if (arg0->_renderListState == 2) {
            igGeometryAttr **q = (igGeometryAttr **)((igGeometryAttrList *)arg0->_geometryAttrList)->_data;
            igGeometryAttr **qe = q + ((igGeometryAttrList *)arg0->_geometryAttrList)->_count;
            for (; q < qe; q++) {
                ((Ob *)(*q)->_vertexArray)->v10();
            }
        }
    } else {
        Gap__Gfx__igPsx2VisualContext__vfunc_193(arg1, t);
        arg0->_renderListState = 0;
    }
    return ok;
}

void Gap__Attrs__igGeometrySetAttr__vfunc_32(igGeometrySetAttr *self, igObject *newVc) {
    igObject *oldVc;
    if (newVc != 0) {
        newVc->_refCount = newVc->_refCount + 1;
    }
    oldVc = (igObject *)self->_vc;
    if (oldVc != 0) {
        oldVc->_refCount = oldVc->_refCount - 1;
        if ((oldVc->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(oldVc);
        }
    }
    self->_vc = (int)newVc;
}

void Gap__Attrs__igGeometrySetAttr__vfunc_24(T_13e8d0 *arg0, int arg1) {
    int r;
    EV **p;
    EV **e;
    r = 0;
    if (arg0->f24 != 0) {
        if (arg0->f16 == -1) {
            r = FUN_0013e6e0((igGeometrySetAttr *)arg0, arg1);
        }
        if (arg0->f16 >= 0 && arg0->f28 != 0) {
            r = Gap__Gfx__igPsx2VisualContext__vfunc_196(arg1, arg0->f16);
        }
    }
    if (r == 0 && arg0->f28 != 0) {
        p = arg0->f20->d;
        e = p + arg0->f20->n;
        for (; p < e; p++) {
            (*p)->vX(arg1);
        }
    }
}

void Gap__Attrs__igGeometrySetAttr__vfunc_29(igGeometrySetAttr *arg0, int arg1) {
    int t;
    if (arg0->_renderListState != 0) {
        t = arg0->_renderListHandle;
        if (t == -1) {
            FUN_0013e6e0(arg0, arg1);
        }
    }
}

void Gap__Attrs__igGeometrySetAttr__vfunc_12(void **arg0) {
    ((DW4VC_112_0 *)(arg0))->vX();
    Gap__Core__igObject__vfunc_10(arg0);
}

void Gap__Attrs__igGeometrySetAttr__vfunc_28(A_13ea20 *arg0) {
    int temp_a1;
    int i;
    H *h;

    if (arg0->f20 != 0) {
        for (i = 0; i < arg0->f20->n; i++) {
            arg0->f20->arr[i]->vX();
        }
    }
    temp_a1 = arg0->f16;
    if (temp_a1 != -1) {
        arg0->f12->vX(temp_a1);
    }
    arg0->f16 = -1;
    h = arg0->f12;
    if (h != 0) {
        h->references = h->references - 1;
        if (((unsigned long long)((long long)h->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(h);
        }
    }
    arg0->f12 = 0;
}

/* Empty leaf in igGeometrySetAttr vtable slot 26: a do-nothing base-class hook. The receiver and
 * arguments are not used. */
void Gap__Attrs__igGeometrySetAttr__vfunc_26(void) {

}

