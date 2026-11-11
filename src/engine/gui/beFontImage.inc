int FUN_00453370(unsigned short *arg0, unsigned short *arg1) {
    return *arg0 - *arg1;
}

int Gap__Bec__beFontImage__vfunc_23(beFontImage *arg0, int arg1) {
    if (FUN_00453830(arg0, arg1) < 0) {
        return 0;
    }
    return 2;
}

float Gap__Bec__beFontImage__vfunc_24(beFontImage *arg0, int arg1) {
    int temp_v0;
    igCharMetricsList *metrics;
    temp_v0 = FUN_00453830(arg0, arg1);
    if (temp_v0 < 0) {
        return 0.0f;
    }
    metrics = (igCharMetricsList *)arg0->_charMetricsList;
    return *(float *)((char *)((metrics->_data + (temp_v0 * 0x28))) + 4);
}

void Gap__Bec__beFontImage__vfunc_21(beFontImage *arg0, struct GlyphVertexBuffer *arg1, char *arg2) {
    struct GlyphPos p;
    int len;
    int i;
    int idx;
    char *s;
    struct GlyphMetricsRecord *rec;
    i = 0;
    p.y = arg0->_baseLine;
    p.x = 0.0f;
    len = arg1->f12;
    s = arg2;
    for (; *s != 0; s++) {
        idx = FUN_00453830(arg0, *s);
        if (idx >= 0) {
            if (i + 6 > len) {
                break;
            }
            rec = (struct GlyphMetricsRecord *)(((struct GlyphMetricsList *)arg0->_charMetricsList)->f16 + idx * 40);
            FUN_004535d0(arg0, (DW4VC_116_2 *)arg1, i, (P *)&p, (R_4535d0 *)rec);
            i += 6;
            p.x += rec->f4;
        }
    }
}

void Gap__Bec__beFontImage__vfunc_22(beFontImage *arg0, struct TextLayoutBuffer *arg1, unsigned short *arg2) {
    struct V2 p;
    int len;
    int i;
    int idx;
    int c;
    unsigned short *s;
    struct GlyphMetricsRecord *rec;
    i = 0;
    p.y = arg0->_baseLine;
    p.x = 0.0f;
    len = arg1->f12;
    s = arg2;
    for (; (c = *s) != 0; s++) {
        idx = FUN_00453830(arg0, c);
        if (idx >= 0) {
            if (i + 6 >= len) {
                break;
            }
            rec = (struct GlyphMetricsRecord *)((char *)((igCharMetricsList *)arg0->_charMetricsList)->_data + idx * 40);
            FUN_004535d0(arg0, (DW4VC_116_2 *)arg1, i, (P *)&p, (R_4535d0 *)rec);
            i += 6;
            p.x += rec->f4;
        }
    }
}

void FUN_004535d0(beFontImage *arg0, DW4VC_116_2 *arg1, int arg2, P *arg3, R_4535d0 *arg4) {
    V a, b, c, d, e, f;
    P g, h;
    float x0, y0, x1, y1, ta, tb;
    int i1, i2, i3, i4, i5;
    x0 = arg3->x;
    y0 = arg3->y;
    x0 = x0 + arg4->f8;
    y0 = y0 + arg4->f12;
    x1 = x0 + arg4->f16;
    y1 = y0 + arg4->f20;
    a.z = 0; a.x = x0; a.y = y0;
    arg1->vX(arg2, &a);
    b.x = x1; b.z = 0; b.y = y1;
    i1 = arg2 + 1;
    arg1->vX(i1, &b);
    c.x = x1; c.z = 0; c.y = y0;
    i2 = arg2 + 2;
    arg1->vX(i2, &c);
    d.y = y0; d.z = 0; d.x = x0;
    i3 = arg2 + 3;
    arg1->vX(i3, &d);
    e.x = x0; e.z = 0; e.y = y1;
    i4 = arg2 + 4;
    arg1->vX(i4, &e);
    f.x = x1; f.z = 0; f.y = y1;
    i5 = arg2 + 5;
    arg1->vX(i5, &f);
    ((DW4VC_200_3 *)arg1)->vX(0, arg2, &arg4->f24);
    ((DW4VC_200_3 *)arg1)->vX(0, i1, &arg4->f32);
    ta = arg4->f28; tb = arg4->f32; g.x = tb; g.y = ta;
    ((DW4VC_200_3 *)arg1)->vX(0, i2, &g);
    ((DW4VC_200_3 *)arg1)->vX(0, i3, &arg4->f24);
    ta = arg4->f36; tb = arg4->f24; h.x = tb; h.y = ta;
    ((DW4VC_200_3 *)arg1)->vX(0, i4, &h);
    ((DW4VC_200_3 *)arg1)->vX(0, i5, &arg4->f32);
}

int FUN_00453830(beFontImage *arg0, int arg1) {
    struct K k;
    k.key = arg1;
    return List_BinarySearch(arg0->_charMetricsList, &k, FUN_00453370, 0x28);
}

void Gap__Bec__beFontImage__vfunc_11(FontImage *self, int enable) {
    Gap__Core__igObject__vfunc_11(self);
    if (enable != 0) {
        ObjectList_AppendRetained((unsigned)self->layers, (void *)self->base);
        igSmartPointer<FillLayer> first((FillLayer *)FUN_00139600(igObject_GetAllocator(self)));
        first.get()->setEnabled(1);
        ObjectList_AppendRetained((unsigned)self->layers, first.get());
        igSmartPointer<OutlineLayer> second((OutlineLayer *)FUN_00131390(igObject_GetAllocator(self)));
        second.get()->setEnabled(1);
        ObjectList_AppendRetained((unsigned)self->layers, second.get());
        self->state = 0x10001;
    }
}

void FUN_00453980(int arg0, int arg1) {
    FUN_00453990((struct FontLayers_453990 *)arg0, *(int *)((char *)(*(int *)((char *)(arg0) + 36)) + 8), (struct FontLayerItem_453990 *)arg1);
}

struct InsertRef_453990 { struct FontLayerItem_453990 *p; };
struct FontLayerItem_453990 { char pad[4]; int refCount; char pad2[16]; int order; };
struct FontLayers_453990 { char pad[32]; int order; int list; };
void FUN_00453990(struct FontLayers_453990 *self, int index, struct FontLayerItem_453990 *item) {
    struct InsertRef_453990 r;
    int list;
    int msg[4];
    item->order = self->order;
    r.p = item;
    list = self->list;
    if (r.p != 0) r.p->refCount = r.p->refCount + 1;
    List_InsertWords(list, index, 1, &r);
    msg[0] = 3;
    msg[1] = 0;
    msg[2] = DAT_0058c618[0];
    msg[3] = index;
    FUN_004578c0((S_4578c0 *)self, (S_4578c0 *)msg);
}

void FUN_00453a20(void *arg0, int arg1) {
    FUN_00453980(*(int *)((char *)arg0 + 16), arg1);
}

