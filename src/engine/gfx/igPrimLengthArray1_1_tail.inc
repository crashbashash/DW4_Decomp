/* IgPrimLengthArray1_1 slot 20, an empty override (`jr ra; nop`). The slot does nothing for this
 * class. */

void Gap__Gfx__igPrimLengthArray1_1__vfunc_20(igPrimLengthArray1_1 *self) {
}

void *igVertexArrayLock_Init(void *arg0) {
    *(int *)((char *)arg0 + 0) = 0;
    *(int *)((char *)arg0 + 4) = 0;
    *(int *)((char *)arg0 + 8) = 0;
    *(int *)((char *)arg0 + 12) = 0;
    *(int *)((char *)arg0 + 16) = 0;
    *(int *)((char *)arg0 + 20) = 0;
    *(int *)((char *)arg0 + 24) = 0;
    return arg0;
}

void FUN_0015df80(S0_15df80 *arg0) {
    S_temp_a0 *temp_a0;
    S_temp_v0 *temp_v0;
    Gap__Core__igObject__resetFields();
    temp_v0 = (S_temp_v0 *)((void *)(igObject_GetAllocator(arg0)));
    if (temp_v0 != 0) {
        temp_v0->f4 = (int)((int) (temp_v0->f4 + 1));
    }
    temp_a0 = (S_temp_a0 *)((void *)(arg0->f18));
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f18 = (int)(temp_v0);
}

void FUN_0015e010(void) {
    igResource_AddAlignment(g_globalContext[0], &text_VertexArrayData[0], 0x10);
    igMemoryRefMetaField_SetAlignmentType(DAT_0055faa0[0], &text_VertexArrayData[0]);
}

void FUN_0015e050(struct S_arg0_15e050 *arg0) {
    int temp_a0;
    int temp_v0;
    int temp_s0;
    struct S_temp_v0_2 *temp_a0_2;
    struct S_temp_v0_2 *temp_v0_2;

    temp_a0 = arg0->f8;
    if (temp_a0 != 0) {
        temp_v0 = Memory_GetBufferSize(temp_a0);
        temp_s0 = 0x50 - temp_v0;
        if (temp_s0 > 0) {
            arg0->f8 = igObject_Reallocate(arg0, arg0->f8, 0x50);
            memset(arg0->f8 + temp_v0, 0, temp_s0);
        }
    }
    if (arg0->f24 == 0) {
        temp_v0_2 = (struct S_temp_v0_2 *)(igObject_GetAllocator(arg0));
        if (temp_v0_2 != 0) {
            temp_v0_2->f4 = (int)((int) (temp_v0_2->f4 + 1));
        }
        temp_a0_2 = (struct S_temp_v0_2 *)(arg0->f24);
        if (temp_a0_2 != 0) {
            temp_a0_2->f4 = temp_a0_2->f4 - 1;
            if ((temp_a0_2->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0_2);
            }
        }
        arg0->f24 = (int)(temp_v0_2);
    }
}

/* Population count. */
int FUN_0015e130(unsigned int v)
{
    int n = 0;
    while (v) {
        if (v & 1)
            n++;
        v >>= 1;
    }
    return n;
}

void FUN_0015e160(unsigned int *arg0, unsigned int arg1) {
    unsigned int v;
    unsigned int t;
    v = 0;
    if (arg1 & 3) {
        v |= 1;
    } else {
        v &= ~1;
    }
    if (arg1 & 0xC) {
        v |= 2;
    } else {
        v &= ~2;
    }
    if (arg1 & 0xF0) {
        v |= 4;
    } else {
        v &= ~4;
    }
    t = FUN_0015e130(arg1 & 0xF0000);
    t &= 0xFF;
    t <<= 16;
    v &= 0xFFF0FFFF;
    v |= t;
    t = FUN_0015e130(arg1 & 0xF00);
    t &= 0xFF;
    t <<= 4;
    v &= ~0xF0;
    v |= t;
    t = FUN_0015e130(arg1 & 0xF000);
    t &= 0xFF;
    t <<= 8;
    v &= ~0xF00;
    v |= t;
    *arg0 = v;
}

void FUN_0015e240(void **arg0, int arg1, int arg2, int arg3, int arg4) {
    int sp5C;
    FUN_0015e160((unsigned int *)&sp5C, arg1);
    ((DW4VC_96_4 *)arg0)->vX(&sp5C, arg2, arg3, arg4);
}

void FUN_0015e2b0(igVertexArray1_1 *arg0, int arg1) {
    /* matching construct: declaration-order sweep — unsigned int count with an unsigned char cast, and this order, give the first loop count s5 and off s2 */
    unsigned int count;
    unsigned int i;
    int *src;
    unsigned int n;
    int **vdata;
    unsigned int fmt;
    unsigned int j;
    int off;
    FUN_0015e160(&fmt, arg0->_vtype);
    arg0->_vertexFormat = fmt;
    arg0->_vtype = 0;
    if (arg0->_memPool == 0) {
        igObject *v0 = (igObject *)igObject_GetAllocator(arg0);
        if (v0 != 0) v0->_refCount = v0->_refCount + 1;
        {
            igObject *a = (igObject *)arg0->_memPool;
            if (a != 0) {
                a->_refCount = a->_refCount - 1;
                if (((unsigned long long)((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(a);
            }
        }
        arg0->_memPool = (int)v0;
    }
    count = (unsigned char)((fmt & 0xF0) >> 4);
    n = arg0->_numVerts;
    if (count != 0) {
        Alloc *al = (Alloc *)arg0->_memPool;
        arg0->_blendWeights = (int)al->v53(n * (count * 4), 0x10);
        /* matching construct: docs loop-invariant shape — b52 hoists &_vdata out of a for loop; retail recomputes it per pass */
        i = 0;
        goto test1;
    top1:
        vdata = (int **)&arg0->_vdata;
        off = (i + 3) * 4;
        src = *(int **)((char *)arg0->_vdata + off);
        for (j = 0; j < n; j++) {
            (*(float **)&arg0->_blendWeights)[i + count * j] = ((float *)src)[j];
        }
        Memory_FreeBuffer(src);
        *(int *)((char *)*vdata + off) = 0;
        i++;
    test1:
        if (i < count) goto top1;
    }
    count = (unsigned char)((fmt & 0xF00) >> 8);
    if (count != 0) {
        Alloc *al = (Alloc *)arg0->_memPool;
        arg0->_blendIndices = (int)al->v53(count * n, 0x10);
        i = 0;
        goto test2;
    top2:
        vdata = (int **)&arg0->_vdata;
        off = (i + 7) * 4;
        src = *(int **)((char *)arg0->_vdata + off);
        for (j = 0; j < n; j++) {
            (*(unsigned char **)&arg0->_blendIndices)[i + count * j] = *((unsigned char *)src + j);
        }
        Memory_FreeBuffer(src);
        *(int *)((char *)*vdata + off) = 0;
        i++;
    test2:
        if (i < count) goto top2;
    }
}

/* igPsx2VertexArray1_1 vtable slot 61. Empty virtual slot: returns immediately. */
void FUN_0015e4d0(void) {

}

int FUN_0015e4e0(VA_15e4e0 *arg0) {
//DECL
    igObject *v0;
    int s2;
    unsigned int *s1;
    int sz;
    unsigned int i;
    int s4;
//ENDDECL
    s2 = 0;
    s1 = arg0->v23();
    if (arg0->f24 == 0) {
        v0 = (igObject *)igObject_GetAllocator(arg0);
        if (v0 != 0) v0->_refCount = v0->_refCount + 1;
        {
            igObject *a = (igObject *)arg0->f24;
            if (a != 0) {
                a->_refCount = a->_refCount - 1;
                if (((unsigned long long)((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(a);
            }
        }
        arg0->f24 = (Alloc_15e4e0 *)v0;
    }
    if (*s1 & 1) {
        sz = arg0->f12 * 0xC;
        *(int *)(arg0->f8 + 0) = arg0->f24->v52(sz);
        s2 += sz;
    }
    {
    unsigned int f = *s1;
    if (f & 2) {
        int a0 = arg0->f12;
        sz = a0 * 0xC;
        if ((f & 0x400000) || (f & 0x800000)) sz += a0 * 0x18;
        *(int *)(arg0->f8 + 4) = arg0->f24->v52(sz);
        s2 += sz;
    }
    }
    if (*s1 & 4) {
        sz = arg0->f12 * 4;
        *(int *)(arg0->f8 + 8) = arg0->f24->v52(sz);
        s2 += sz;
    }
    {
        unsigned char c = (*s1 & 0xF0) >> 4;
        if (c != 0) {
            int a1 = arg0->f12 * c * 4;
            s2 += a1;
            if (arg0->f32 == 0) arg0->f32 = arg0->f24->v53(a1, 0x10);
        }
    }
    {
        unsigned char c = (*s1 & 0xF00) >> 8;
        i = 0;
        if (c != 0) {
            int a1 = arg0->f12 * c;
            s2 += a1;
            if (arg0->f36 == 0) arg0->f36 = arg0->f24->v53(a1, 0x10);
            i = 0;
        }
        unsigned int fv = *s1;
        while (i < (unsigned char)((fv & 0xF0000) >> 16)) {
            s4 = arg0->f12 * 8;
            int a0 = arg0->f24->v52(s4);
            int off = (i + 11) * 4;
            i++;
            s2 += s4;
            *(int *)(arg0->f8 + off) = a0;
            fv = *s1;
        }
    }
    s2 += arg0->v62();
    s2 += arg0->v63();
    return s2;
}

int FUN_0015e7a0(int arg0) {
    return arg0 + 0x1C;
}

void FUN_0015e7b0(VertexBufferOwner *o) {
unsigned i;
int **p;
int b;
int a;
VertexFormatInfo *info;
int **q;
int off;
info = o->getInfo();
if (info->flags & 1) { p = &o->arr; a = (*p)[0]; if (a != 0) { Memory_FreeBuffer(a); (*p)[0] = 0; } }
if (info->flags & 2) { p = &o->arr; a = (*p)[1]; if (a != 0) { Memory_FreeBuffer(a); (*p)[1] = 0; } }
if (info->flags & 4) { p = &o->arr; a = (*p)[2]; if (a != 0) { Memory_FreeBuffer(a); (*p)[2] = 0; } }

    if (o->f32 != 0) { Memory_FreeBuffer(o->f32); o->f32 = 0; }
    if (o->f36 != 0) { Memory_FreeBuffer(o->f36); o->f36 = 0; }
    i = 0;
    goto test;
top:
    off = (i + 11) * 4;
    q = &o->arr;
    b = *(int *)((char *)*q + off);
    if (b != 0) { Memory_FreeBuffer(b); *(int *)((char *)*q + off) = 0; }
    i++;
test:
    if (i < (unsigned char)((info->flags & 0xF0000) >> 16)) goto top;
    o->f60();
    o->f61();
}

void FUN_0015e940(S_15e940 *arg0, int arg1, int arg2, float fparg0) {
    float *temp_s0 = arg0->f32;
    temp_s0[arg1 + arg2 * ((((*arg0->vX()) & 0xF0) >> 4) & 0xFF)] = fparg0;
}

float FUN_0015e9c0(S_15e9c0 *arg0, int arg1, int arg2) {
    float *temp_s0 = arg0->f32;
    return temp_s0[arg1 + arg2 * ((((*arg0->vX()) & 0xF0) >> 4) & 0xFF)];
}

void FUN_0015ea30(int *arg0) {
    unsigned int n;
    int base;
    unsigned int i;
    unsigned int j;
    unsigned int off;
    float sum;
    float r;
    int *p = ((VC_15ea30 *)arg0)->vX();
    n = ((unsigned int)(*p & 0xF0) >> 4) & 0xFF;
    if (n != 0) {
        base = arg0[8];
        for (i = 0; i < (unsigned int)arg0[3]; i++) {
            off = i * n;
            sum = 0.0f;
            for (j = 0; j + 1 < n; j++) {
                sum += ((float *)base)[j + off];
            }
            r = 1.0f - sum;
            if (r < 0.0f) {
                r = 0.0f;
            }
            ((float *)base)[n + off - 1] = r;
        }
    }
}

void FUN_0015eaf0(int *arg0, int arg1, int arg2, char arg3) {
    int s1 = arg0[9];
    int *p = ((VC_15eaf0 *)arg0)->vX();
    unsigned int m = (unsigned int)(*p & 0xF0) >> 4;
    *(char *)(s1 + arg1 + arg2 * (m & 0xFF)) = arg3;
}

unsigned char FUN_0015eb60(int *arg0, int arg1, int arg2) {
    int s0 = arg0[9];
    int *p = ((VC_15eb60 *)arg0)->vX();
    unsigned int m = (unsigned int)(*p & 0xF0) >> 4;
    return *(unsigned char *)(s0 + arg1 + arg2 * (m & 0xFF));
}

void FUN_0015ebd0(igPsx2VertexArray1_1 *arg0, int arg1, float fparg0) {
    *(float *)(*(int *)((char *)(arg0->_vdata) + 60) + (arg1 * 4)) = 0.5f * fparg0;
}

float FUN_0015ec00(igPsx2VertexArray1_1 *arg0, int arg1) {
    int a, idx, c;
    a = arg0->_vdata;
    idx = arg1 * 4;
    c = *(int *)(a + 60);
    return 2.0f * *(float *)(c + idx);
}

void FUN_0015ec30(A_15ec30 *arg0, int arg1, float *arg2) {
    float x = arg2[0];
    float y = arg2[1];
    float *dst;
    x = x * 0.5f;
    y = y * 0.5f;
    dst = (float *)(arg0->b->data + arg1 * 8);
    dst[0] = x;
    dst[1] = y;
}

void FUN_0015ec70(igPsx2VertexArray1_1 *arg0, int arg1, float *arg2) {
    float *p;
    float k = 2.0f;
    p = (float *)(*(int *)((char *)(arg0->_vdata) + 60) + (arg1 * 8));
    arg2[0] = p[0];
    arg2[1] = p[1];
    arg2[0] = arg2[0] * k;
    arg2[1] = arg2[1] * k;
}

void FUN_0015ecc0(void *arg0, int arg1, float fparg0) {
    ((float *)*(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 76))[arg1] = fparg0;
}

float FUN_0015ece0(void *arg0, int arg1) {
    int a, idx, c;
    a = *(int *)((char *)arg0 + 8);
    idx = arg1 * 4;
    c = *(int *)(a + 76);
    return *(float *)(c + idx);
}

int FUN_0015ed00(V_15ed00 *arg0, int arg1, unsigned int arg2, int arg3, int arg4) {
    igSmartPointer<V_15ed00> resized((V_15ed00 *)FUN_0014b680(igObject_GetAllocator()));
    unsigned int n;
    int sp88;
    int r;
    unsigned int i;
    resized.p->f24 = arg0->f24;
    r = resized.p->v22(arg1, arg2, arg3, arg4);
    n = arg0->f12;
    n = (n < arg2) ? n : arg2;
    FUN_00164e90(&sp88, arg1, arg0->v23());
    for (i = 0; i < n; i++) {
        FUN_0015dbc0(resized.p, i, arg0, i, &sp88);
    }
    resized.p->v45();
    resized.p->v17((int)g_igVertexArray1_1_metaObject[0]);
    arg0->v17((int)g_igVertexArray1_1_metaObject[0]);
    FUN_0015e7b0((VertexBufferOwner *)arg0);
    Memory_FreeBuffer(arg0->f8);
    arg0->f12 = arg2;
    arg0->f8 = resized.p->f8;
    arg0->f32 = resized.p->f32;
    arg0->f36 = resized.p->f36;
    arg0->f40 = resized.p->f40;
    arg0->f28 = resized.p->f28;
    arg0->f24 = resized.p->f24;
    resized.p->f12 = 0;
    resized.p->f8 = 0;
    resized.p->f32 = 0;
    resized.p->f36 = 0;
    resized.p->f40 = 0;
    resized.p->f28 = 0;
    arg0->v18((int)g_igVertexArray1_1_metaObject[0]);
    arg0->v59();
    return r;
}

/* Write the position of vertex `index` from `in` (3 floats). Counterpart of FUN_0015f010: does nothing
 * unless the vertex format has the position bit set, and stores into the position stream at _vdata
 * + 68, 12 bytes per vertex. */




void FUN_0015efc0(igPsx2VertexArray1_1 *self, int index, float *in) {
    float *position;

    if (self->_vertexFormat & VERTEX_FORMAT_POSITIONS) {
        position = (float *)(*(int *)((char *)(self->_vdata) + VDATA_POSITION_STREAM) + (index * POSITION_STRIDE));
        position[0] = in[0];
        position[1] = in[1];
        position[2] = in[2];
    }
}

/* Read the position of vertex `index` into `out` (3 floats). Does nothing unless the vertex format
 * has the position bit set. _vdata is the runtime table of stream pointers; the position stream is
 * at +68, 12 bytes per vertex. */




void FUN_0015f010(igPsx2VertexArray1_1 *self, int index, float *out) {
    float *position;

    if (self->_vertexFormat & VERTEX_FORMAT_POSITIONS) {
        position = (float *)(*(int *)((char *)(self->_vdata) + VDATA_POSITION_STREAM) + (index * POSITION_STRIDE));
        out[0] = position[0];
        out[1] = position[1];
        out[2] = position[2];
    }
}

int FUN_0015f060(igPsx2VertexArray1_1 *arg0, int arg1) {
    if (arg0->_vertexFormat & 0x400000) {
        return *(int *)((char *)(arg0->_vdata) + 68) + (arg1 * 0xC);
    }
    return 0;
}

/* Write the normal of vertex `index` from `in` (3 floats). Does nothing unless the vertex format
 * has the normal bit set; stores into the normal stream at _vdata + 72, 12 bytes per vertex
 *. */




void FUN_0015f0a0(igPsx2VertexArray1_1 *self, int index, float *in) {
    float *normal;

    if (self->_vertexFormat & VERTEX_FORMAT_NORMALS) {
        normal = (float *)(*(int *)((char *)(self->_vdata) + VDATA_NORMAL_STREAM) + (index * NORMAL_STRIDE));
        normal[0] = in[0];
        normal[1] = in[1];
        normal[2] = in[2];
    }
}

/* Read the normal of vertex `index` into `out` (3 floats). Counterpart of FUN_0015f0a0: does nothing
 * unless the vertex format has the normal bit set. The normal stream is at _vdata + 72, 12 bytes
 * per vertex. */




void FUN_0015f0f0(igPsx2VertexArray1_1 *self, int index, float *out) {
    float *normal;

    if (self->_vertexFormat & VERTEX_FORMAT_NORMALS) {
        normal = (float *)(*(int *)((char *)(self->_vdata) + VDATA_NORMAL_STREAM) + (index * NORMAL_STRIDE));
        out[0] = normal[0];
        out[1] = normal[1];
        out[2] = normal[2];
    }
}

int FUN_0015f140(igPsx2VertexArray1_1 *arg0, int arg1) {
    if (arg0->_vertexFormat & 0x800000) {
        return *(int *)((char *)(arg0->_vdata) + 72) + (arg1 * 0xC);
    }
    return 0;
}

void FUN_0015f180(void *arg0) {
    int temp_a0;
    int temp_a0_2;
    int temp_a0_3;

    temp_a0 = *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 64);
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
        *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 64) = 0;
    }
    temp_a0_2 = *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 60);
    if (temp_a0_2 != 0) {
        Memory_FreeBuffer(temp_a0_2);
        *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 60) = 0;
    }
    temp_a0_3 = *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 76);
    if (temp_a0_3 != 0) {
        Memory_FreeBuffer(temp_a0_3);
        *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 76) = 0;
    }
}

int FUN_0015f200(A_15f200 *arg0) {
    int size;
    unsigned flags;
    int n;
    unsigned char t;
    void **dst;
    B_15f200 **pf;
    flags = *(unsigned *)arg0->getFlags();
    t = ((flags & 0x300000) >> 20) & 0xFF;
    size = 0;
    if (t != 0) {
        n = arg0->f12 * ((t & 0xFF) * 4);
        dst = &arg0->f8->f60;
        *dst = arg0->f24->alloc(n);
        size += n;
    }
    pf = &arg0->f8;
    (*pf)->f64 = 0;
    if (flags & 0x1000000) {
        n = arg0->f12 * 4;
        dst = &(*pf)->f76;
        *dst = arg0->f24->alloc(n);
        size += n;
    }
    return size;
}

void FUN_0015f2f0(void *arg0) {
    int temp_a0;
    int temp_a0_2;

    temp_a0 = *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 68);
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
        *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 68) = 0;
    }
    temp_a0_2 = *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 72);
    if (temp_a0_2 != 0) {
        Memory_FreeBuffer(temp_a0_2);
        *(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 72) = 0;
    }
}

int FUN_0015f350(ArraySizeOwner *arg0) {
    int total;
    int *dst;
    unsigned int flags;
    int n;
    flags = *arg0->vX();
    total = 0;
    if (flags & 0x400000) { dst = (int *)(arg0->f8 + 0x44); n = arg0->f12 * 12; *dst = arg0->f24->vX(n); total += n; }
    if (flags & 0x800000) { dst = (int *)(arg0->f8 + 0x48); n = arg0->f12 * 12; *dst = arg0->f24->vX(n); total += n; }
    return total;
}

static int FUN_0015f430(void *arg0, int arg1, int arg2, int arg3) { if (arg1 == *(int *)((char *)(arg0) + 16)) { if (arg2 == *(int *)((char *)(arg0) + 20)) { return 1; } } return 0; }

static int FUN_0015f460(void *arg0, int arg1, int arg2, int arg3)
{
  if (arg1 == (*((int *) (((char *) arg0) + 16))))
  {
    if ((arg3 == (*((int *) (((char *) arg0) + 28)))) && (arg2 == (*((int *) (((char *) arg0) + 20)))))
    {
      return 1;
      return 0;
    }
  }
  return 0;
}

int *FUN_0015f4a0(struct S_15f430 *s, int a1, int a2) {
    int *found = 0;
    int i;
    for (i = 0; i < s->count; i++) {
        int *item = s->items[i];
        if (FUN_0015f430(item, a1, a2, 0) != 0) { found = item; break; }
    }
    return found;
}

void *FUN_0015f510(L *l, int a1, int a2, int a3) {
  void *r = 0; int i; void *e;
  for (i = 0; i < l->n; i++) { e = (void*)l->data[i]; if (FUN_0015f460(e, a1, a3, a2)) { r = e; break; } }
  return r; }

