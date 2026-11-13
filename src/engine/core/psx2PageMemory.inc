/* Deleting destructor. Sets the vtable to its own image, then calls __dl__FPv when the signed
 * low 16 bits of the delete flag are positive. __dl__FPv never returns (it ends in an endless
 * loop). */
igObject *FUN_00328e00(igObject *self, long long deleteFlags) {
    if (self != 0) {
        self->_vtable = (int)&g_vtable[0];
        if (((long long) (deleteFlags << 0x30) >> 0x30) > 0) {
            __dl__FPv();
        }
    }
    return self;
}

void FUN_00328e50(void **arg0) {
    /* matching construct: variant search — decl order [2, 1, 0]; the unit compiler assigns stack slots and registers in declaration order */
    unsigned int var_s1;
    int temp_a1;
    int *temp_s0;

    var_s1 = 0;
    do {
        temp_s0 = &DAT_00587220[var_s1];
        temp_a1 = *temp_s0;
        if (temp_a1 != 0) {
            ((DW4VC_180_1 *)(arg0))->vX((int)(temp_a1));
            *temp_s0 = 0;
        }
        var_s1 += 1;
    } while (var_s1 < 0x40U);
}

int FUN_00328ed0(void *arg0, int arg1) {
    int temp_v0;

    temp_v0 = malloc(arg1);
    if (temp_v0 == DAT_00587328[0]) {
        FUN_00304430(DAT_004ff590, DAT_00587328[0]);
        FUN_00304680();
    }
    return temp_v0;
}

int FUN_00328f20(int arg0, int arg1) {
    int temp_v0;

    temp_v0 = malloc(arg1);
    if (temp_v0 == DAT_00587328[0]) {
        FUN_00304430(DAT_004ff590, DAT_00587328[0]);
        FUN_00304680();
    }
    return temp_v0;
}

void FUN_00328f70(int unused, int a, int b) {
    calloc(a, b);
}

void FUN_00328f80(int arg0, int arg1, int arg2) {
    realloc(arg1, arg2);
}

int FUN_00328f90(void **arg0, int *arg1) {
    int *var_s1;
    int temp_v0;

    var_s1 = (int *)(arg1);
    if (var_s1 == 0) {
        var_s1 = (int *)(&DAT_004f7910[0]);
    }
    temp_v0 = ((DW4VC_16_1 *)(arg0))->vX((int)(strlen(var_s1) + 1));
    if (temp_v0 != 0) {
        strcpy(temp_v0, var_s1);
    }
    return temp_v0;
}

void FUN_00329000(int a0, int a1) {
    free(a1, a1);
}

void FUN_00329010(CrtHeapView *self, void *block)
{
    self->vfunc_15(0, block);
}

void FUN_00329030(void **arg0, int arg1, int arg2) {
    DW4SR4 sp1C;

    sp1C = ((DW4VCSR_72_2 *)(arg0))->vX((int)(arg1), (int)(arg2));
}

int FUN_00329070(void **arg0, int arg1, unsigned int arg2, unsigned int arg3) {
    DW4SR4 sp5C;
    DW4SR4 sp58;
    int temp_v0;

    if (arg2 < arg3) {
        sp5C = ((DW4VCSR_72_2 *)(arg0))->vX((int)(arg1 + arg2), (int)(arg3 - arg2));
        return arg1;
    }
    if (((DW4VC_68_2 *)(arg0))->vX((int)(arg1 + arg3), (int)(arg2 - arg3)) != -1) {
        return arg1;
    }
    temp_v0 = ((DW4VC_68_2 *)(arg0))->vX((int)(0), (int)(arg2));
    if (temp_v0 == -1) {
        return 0;
    }
    memcpy(temp_v0, arg1, arg3);
    sp58 = ((DW4VCSR_72_2 *)(arg0))->vX((int)(arg1), (int)(arg3));
    return temp_v0;
}

void FUN_00329170(CrtHeapView *self, void *block)
{
    self->vfunc_8(block);
}

void *FUN_00329180(CrtHeapView *self, void *block, unsigned int size)
{
    return self->vfunc_9(block, size);
}

void FUN_00329190(CrtHeapView *self)
{
    self->vfunc_10();
}

void FUN_003291a0(Stream_328e00 *self, int n) {
    if (n > 0) {
        if (self->Seek(self->Tell(), n) == -1) {
            self->Seek(0, n);
        }
    } else if (n < 0) {
        int pos = self->Tell();
        self->Move(pos + n, -n);
        self->Tell();
    } else {
        self->Tell();
    }
}

unsigned FUN_00329280(O_328e00 *self, unsigned a, int n) {
    unsigned r = -1;
    if (a == 0) {
        unsigned t = self->v27(n);
        r = t;
        if (t == (unsigned)-1) r = self->v40(n);
    } else if (self->v26() != 0) {
        r = a;
    } else {
        unsigned c = self->v17();
        if (c == a) {
            r = self->v40(n);
            if (r != a) {
                if (r != (unsigned)-1) {
                    self->v40(-n);
                    r = -1;
                }
            }
        } else {
            unsigned e = a + n;
            if (a <= c && c < e && self->v26(a, c - a) != 0) {
                int m = e - c;
                r = self->v40(m);
                if (r != a && r != (unsigned)-1) {
                    self->v40(-m);
                    r = -1;
                }
            }
        }
    }
    if (r != (unsigned)-1) {
        R_328e00 x = self->v44(r, n, 1);
        R_328e00 y = self->v25(3, r, n);
    }
    return r;
}

R460 FUN_00329460(C_328e00 *arg1, int arg2, int arg3) {
    int r17 = arg1->v17();
    if (r17 == arg2 + arg3) {
        int t = arg1->v40(-arg3);
        if (t != -1) {
            arg1->v25(0, t, arg3);
            return R460(g_resultSuccess.v);
        }
    } else {
        return arg1->v41(arg2, arg3);
    }
    return R460(g_resultFailure.v);
}

/* Result of the virtual call at vtable byte offset 168 (queried with 0), with a zero result mapped
 * to -1 (an index-style lookup that reports "not found" as -1). */
int FUN_00329540(igPsx2CallStackTracer *self) {
    int result;

    result = ((DW4VC_168_1 *)(self))->vX((int)(0));
    if (result == 0) {
        result = -1;
    }
    return result;
}

/* Lower bound of the address range the tracer pages over, or 0 while it still holds the all-ones
 * "unset" value. */
int FUN_00329570(void) {
    int start;

    start = g_rangeStart[0];
    if (start == -1) {
        start = 0;
    }
    return start;
}

int FUN_00329590(igPsx2CallStackTracer *self) {
    return TRACER_PAGE_SIZE;
}

int FUN_003295a0(igPsx2CallStackTracer *self) {
    return TRACER_BLOCK_SIZE;
}

int FUN_003295b0(void) {
    return g_rangeStart[0];
}

int FUN_003295c0(void) {
    return g_rangeEnd[0];
}

void FUN_003295d0(Tr *self, int *out) {
    S_328e00 s;
    unsigned int i;
    int v = self->v19();
    if (v == -1) {
        v = g_rangeEnd[0];
    }
    memset(&s, 0, 16);
    i = 0;
    do {
        int t = DAT_00587220[i];
        if (t != 0) {
            FUN_0032ae00(t, &s);
        }
        i += 1;
    } while (i < 64);
    memset(out, 255, 84);
    out[0] = -1;
    out[1] = v - g_rangeStart[0];
    out[2] = g_rangeEnd[0] - g_rangeStart[0];
    out[3] = s.d << 12;
    out[4] = s.b << 12;
    out[5] = -1;
}

int FUN_003296d0(igPsx2CallStackTracer *self) {
    return 0;
}

R460 FUN_003296e0(DW4VC_176_1 *self, int state, unsigned int addr, int len) {
    unsigned int lo0, hi0;
    /* matching construct: declaration order — end declared before startPage takes s3, startPage s2 */
    unsigned int end = addr + len;
    unsigned int startPage = addr >> 26;
    unsigned int endPage = end >> 26;
    unsigned int page = startPage;
    lo0 = (addr & 0x3FFFFFF) >> 12;
    hi0 = (end & 0x3FFFFFF) >> 12;
    while (page <= endPage) {
        int *slot = &DAT_00587220[page];
        int table = *slot;
        unsigned int lo, hi;
        if (table == 0) {
            table = self->vX(0x1000);
            memset(table, 0, 0x1000);
            *slot = table;
        }
        if (startPage < page) lo = 0; else lo = lo0;
        if (page < endPage) hi = 0x4000; else hi = hi0;
        FUN_0032ace0(table, lo, hi - lo, state);
        page++;
    }
    if (addr < g_rangeStart[0]) g_rangeStart[0] = addr;
    if (g_rangeEnd[0] < end) g_rangeEnd[0] = end;
    return R460(g_resultSuccess.v);
}

int FUN_00329860(void *self, unsigned int addr, unsigned int len) {
    unsigned int end, s5, s4, i, lo, hi, t, loB, hiB;
    int p, r;
    end = addr + len;
    s5 = addr >> 26;
    s4 = end >> 26;
    loB = (addr & 0x3FFFFFF) >> 12;
    hiB = (end & 0x3FFFFFF) >> 12;
    i = s5;
    if (len == 0) return 0;
    {
        while (i <= s4) {
            p = DAT_00587220[i];
            if (p != 0) {
                lo = loB;
                if (i > s5) lo = 0;
                hi = hiB;
                if (i < s4) hi = 0x4000;
                r = FUN_0032ac70(p, lo);
                if (r != 1) break;
                t = FUN_0032ad50(p, lo, len, hi - lo, r);
                if (t >= len) return 1;
                len -= t;
            }
            i++;
        }
    }
    return 0;
}

unsigned int FUN_00329980(void *self, int size) {
    unsigned int base;
    unsigned int s5;
    unsigned int s4;
    unsigned int s3;
    unsigned int s2;
    unsigned int s1;
    int p;
    unsigned int v;
    unsigned int s6;
    unsigned int s7;
    int r;
    unsigned int s8;
    s4 = (unsigned int)(size + 0xFFF) >> 12;
    s1 = 0;
    s5 = g_rangeStart[0];
    s6 = s5 >> 26;
    s3 = s6;
    s7 = g_rangeEnd[0] >> 26;
    while (s3 <= s7) {
        s2 = 0;
        if (s3 == s6) {
            s2 = (g_rangeStart[0] & 0x3FFFFFF) >> 12;
        }
        base = s3 << 26;
        if (s3 == s7) {
            s8 = (g_rangeEnd[0] & 0x3FFFFFF) >> 12;
        } else {
            s8 = 0x4000;
        }
        p = DAT_00587220[s3];
        if (p != 0) {
            while (s2 < s8) {
                r = FUN_0032ac70(p, s2);
                if (r == 1) {
                    v = FUN_0032ad50(p, s2, s4, r, 3);
                    if (s1 == 0) {
                        s5 = base + (s2 << 12);
                    }
                    s1 += v;
                    if (s1 >= s4) {
                        return s5;
                    }
                } else {
                    v = FUN_0032ad50(p, s2, 0x4000, r, 3);
                    s1 = 0;
                }
                s2 += v;
            }
        }
        s3++;
    }
    return -1;
}

int FUN_00329b00(void) {
    return -1;
}

int FUN_00329b10(void) {
    return -1;
}

void FUN_00329b20(void *arg0, int *arg1, int *arg2, int *arg3) {
    *arg1 = -1;
    *arg2 = -1;
    *arg3 = -1;
}

int FUN_00329b40(void *arg0, void *arg1, int *arg2, int *arg3) {
    *arg2 = -1;
    *arg3 = -1;
    return 1;
}

void FUN_00329e70(Obj_328e00 *arg0) {
    int buf[21];
    arg0->vf(buf);
    FUN_00304430(DAT_004ff5e0);
    FUN_00304680();
    FUN_00304430(DAT_004ff600, buf[0], buf[0]);
    FUN_00304680();
    FUN_00304430(DAT_004ff630, buf[1], buf[1]);
    FUN_00304680();
    FUN_00304430(DAT_004ff660, buf[2], buf[2]);
    FUN_00304680();
    FUN_00304430(DAT_004ff690, buf[3], buf[3]);
    FUN_00304680();
    FUN_00304430(DAT_004ff6c0, buf[4], buf[4]);
    FUN_00304680();
    FUN_00304430(DAT_004ff6f0, buf[5], buf[5]);
    FUN_00304680();
    FUN_00304430(DAT_004ff720, buf[6], buf[6]);
    FUN_00304680();
    FUN_00304430(DAT_004ff750, buf[7], buf[7]);
    FUN_00304680();
    FUN_00304430(DAT_004ff780, buf[8], buf[8]);
    FUN_00304680();
    FUN_00304430(DAT_004ff7b0, buf[9], buf[9]);
    FUN_00304680();
    FUN_00304430(DAT_004ff7e0, buf[10], buf[10]);
    FUN_00304680();
    FUN_00304430(DAT_004ff810, buf[11], buf[11]);
    FUN_00304680();
    FUN_00304430(DAT_004ff840, buf[12], buf[12]);
    FUN_00304680();
    FUN_00304430(DAT_004ff870, buf[13], buf[13]);
    FUN_00304680();
    FUN_00304430(DAT_004ff8a0, buf[14], buf[14]);
    FUN_00304680();
    FUN_00304430(DAT_004ff8d0, buf[15], buf[15]);
    FUN_00304680();
    FUN_00304430(DAT_004ff900, buf[16], buf[16]);
    FUN_00304680();
    FUN_00304430(DAT_004ff930, buf[17], buf[17]);
    FUN_00304680();
    FUN_00304430(DAT_004ff960, buf[18], buf[18]);
    FUN_00304680();
    FUN_00304430(DAT_004ff990, buf[19], buf[19]);
    FUN_00304680();
    FUN_00304430(DAT_004ff9c0, buf[20], buf[20]);
    FUN_00304680();
}

Ent_328e00 *FUN_0032a100(Ent_328e00 *arg0) {
    memset(arg0, 0, 0xA8);
    return arg0;
}

int FUN_0032a130(int arg0, long long arg1) {
    if (arg0 != 0) {
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            FUN_0032a220(arg0);
        }
    }
    return arg0;
}

void FUN_0032a180(char *arg0, int *arg1) {
    strncpy(arg0 + 8, arg1, 0x4F);
    arg0[87] = 0;
}

int FUN_0032a1b0(char *arg0, int *arg1) {
    strncpy(arg0 + 0x58, arg1, 0x4F);
    arg0[167] = 0;
}

Ent_328e00 *FUN_0032a1e0(int arg0) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)Memory_GetAllocatorBySelector(g_memoryContextNonTracked)));
    return (Ent_328e00 *)((DW4VC_216_1 *)(temp_v0))->vX((int)(arg0));
}

void FUN_0032a220(int arg0) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)Memory_GetAllocatorBySelector(g_memoryContextNonTracked)));
    ((DW4VC_264_1 *)(temp_v0))->vX((int)(arg0));
}

int FUN_0032a260(int **arg0, int **arg1) {
    return **arg0 - **arg1;
}

void FUN_0032a5f0(int extra0)
{
}

void FUN_0032a600(A600 *arg0, int arg1) {
    Ent_328e00 *spDC;
    Out600 out;
    int *s1;
    arg0->v23(&out);
    s1 = &out.a0;
    if (*s1 != -1) {
        Ent_328e00 *e = FUN_0032a1e0(168);
        if (e != 0) e = FUN_0032a100(e);
        spDC = e;
        e->w0 = *s1;
        spDC->w4 = out.b0;
        FUN_0032a180((char *)spDC, &text_Section_Code[0]);
        FUN_0032a1b0((char *)spDC, &text_Program[0]);
        List_InsertWords((igDataList *)arg1, FUN_002d6e60((L_2d6e60 *)arg1, &spDC, (Cmp)FUN_0032a260), 1, &spDC);
    }
    s1 = &out.a1;
    if (*s1 != -1) {
        Ent_328e00 *e = FUN_0032a1e0(168);
        if (e != 0) e = FUN_0032a100(e);
        spDC = e;
        e->w0 = *s1;
        spDC->w4 = out.b1;
        FUN_0032a180((char *)spDC, &text_Section_Data[0]);
        FUN_0032a1b0((char *)spDC, &text_Program[0]);
        List_InsertWords((igDataList *)arg1, FUN_002d6e60((L_2d6e60 *)arg1, &spDC, (Cmp)FUN_0032a260), 1, &spDC);
    }
    s1 = &out.a2;
    if (*s1 != -1) {
        Ent_328e00 *e = FUN_0032a1e0(168);
        if (e != 0) e = FUN_0032a100(e);
        spDC = e;
        e->w0 = *s1;
        spDC->w4 = out.b2;
        FUN_0032a180((char *)spDC, &text_Section_Initialized_Data[0]);
        FUN_0032a1b0((char *)spDC, &text_Program[0]);
        List_InsertWords((igDataList *)arg1, FUN_002d6e60((L_2d6e60 *)arg1, &spDC, (Cmp)FUN_0032a260), 1, &spDC);
    }
    s1 = &out.a3;
    if (*s1 != -1) {
        Ent_328e00 *e = FUN_0032a1e0(168);
        if (e != 0) e = FUN_0032a100(e);
        spDC = e;
        e->w0 = *s1;
        spDC->w4 = out.b3;
        FUN_0032a180((char *)spDC, &text_Section_Uninitialized_Data[0]);
        FUN_0032a1b0((char *)spDC, &text_Program[0]);
        List_InsertWords((igDataList *)arg1, FUN_002d6e60((L_2d6e60 *)arg1, &spDC, (Cmp)FUN_0032a260), 1, &spDC);
    }
    s1 = &out.a4;
    if (*s1 != -1) {
        Ent_328e00 *e = FUN_0032a1e0(168);
        if (e != 0) e = FUN_0032a100(e);
        spDC = e;
        e->w0 = *s1;
        spDC->w4 = out.b4;
        FUN_0032a180((char *)spDC, &text_Section_Stack_Data[0]);
        FUN_0032a1b0((char *)spDC, &text_Program[0]);
        List_InsertWords((igDataList *)arg1, FUN_002d6e60((L_2d6e60 *)arg1, &spDC, (Cmp)FUN_0032a260), 1, &spDC);
    }
}

void FUN_0032a900(A900 *arg0, int arg1) {
    Ent_328e00 *spDC;
    Out900 out;
    unsigned i;
    unsigned j;
    int s2; int s1; int s0;
    arg0->v23(&out);
    for (i = 0; i < 0x40U; i++) {
        s0 = DAT_00587220[i];
        if (s0 != 0) for (j = 0; j < 0x4000U; j += s1) {
            s2 = FUN_0032ac70(s0, j);
            s1 = FUN_0032ad50(s0, j, 0x4000 - j, s2, 3);
            Ent_328e00 *e = FUN_0032a1e0(168);
            if (e != 0) e = FUN_0032a100(e);
            spDC = e;
            e->w0 = (i << 26) + (j << 12);
            spDC->w4 = s1 << 12;
            switch (s2) {
            case 0: FUN_0032a180((char *)spDC, &text_Heap_Unknown[0]); FUN_0032a1b0((char *)spDC, &text_SystemHeap[0]); break;
            case 1: FUN_0032a180((char *)spDC, &text_Heap_Free[0]); FUN_0032a1b0((char *)spDC, &text_SystemHeap[0]); break;
            case 2: FUN_0032a180((char *)spDC, &text_Heap_Blocked[0]); FUN_0032a1b0((char *)spDC, &text_SystemHeap[0]); break;
            case 3: FUN_0032a180((char *)spDC, &text_Heap_Allocated[0]); FUN_0032a1b0((char *)spDC, &text_SystemHeap[0]); break;
            }
            List_InsertWords((igDataList *)arg1, FUN_002d6e60((L_2d6e60 *)arg1, &spDC, (Cmp)FUN_0032a260), 1, &spDC);
        }
    }
    if (out.b != -1 && out.a != -1) {
        Ent_328e00 *e = FUN_0032a1e0(168);
        if (e != 0) e = FUN_0032a100(e);
        spDC = e;
        e->w0 = out.b;
        spDC->w4 = out.a;
        FUN_0032a180((char *)spDC, &text_Heap_Free_from_top[0]);
        FUN_0032a1b0((char *)spDC, &text_SystemHeap[0]);
        List_InsertWords((igDataList *)arg1, FUN_002d6e60((L_2d6e60 *)arg1, &spDC, (Cmp)FUN_0032a260), 1, &spDC);
    }
}

void FUN_0032ab90(int a0, int a1) {
    FUN_002f0760(a1, a1);
}

int FUN_0032aba0(void) {
    return -1;
}

void FUN_0032abb0(int *arg0, void **arg1, int arg2, int arg3) {DW4SR4 a = ((DW4VCSR_108_3 *)(arg1))->vX(1, arg2, arg3); DW4SR4 b = ((DW4VCSR_184_3 *)(arg1))->vX(arg2, arg3, 0);*arg0 = g_resultSuccess.v;}

void *FUN_0032ac40(CrtHeapView *self, unsigned int size)
{
    return self->vfunc_2(size);
}

void FUN_0032ac50(CrtHeapView *self, void *block)
{
    self->vfunc_7(block);
}

void FUN_0032ac60(int *arg0) {
    *arg0 = g_resultSuccess.v;
}

int FUN_0032ac70(int arg0, unsigned int arg1) {
    return (((unsigned int *)arg0)[arg1 >> 4] >> ((arg1 & 0xF) * 2)) & 3;
}

void FUN_0032aca0(int arg0, unsigned int arg1, int arg2) {
    int *temp_a2;
    int temp_a3;

    temp_a3 = (arg1 & 0xF) * 2;
    temp_a2 = (int *)(arg0 + ((arg1 >> 4) * 4));
    *temp_a2 = (~(3 << temp_a3) & *temp_a2) | (arg2 << temp_a3);
}

void FUN_0032ace0(int arg0, int arg1, int arg2, int arg3) {
    while (arg2-- != 0) {
        FUN_0032aca0(arg0, arg1, arg3);
        arg1++;
    }
}

int FUN_0032ad50(int arg0, unsigned int arg1, int arg2, int arg3, int arg4) {
    int n = 0;
    for (; arg1 < 0x4000U; arg1++) {
        if (arg2-- == 0) return n;
        if (arg3 != (arg4 & FUN_0032ac70(arg0, arg1))) return n;
        n++;
    }
    return n;
}

void FUN_0032ae00(int arg0, void *arg1) {
    int *temp_a1;
    int temp_v1;
    int var_s2;

    var_s2 = 0;
    do {
        temp_v1 = FUN_0032ac70(arg0, var_s2) * 4;
        var_s2 += 1;
        temp_a1 = (int *)((char *)arg1 + temp_v1);
        *temp_a1 += 1;
    } while (var_s2 < 0x4000);
}

void FUN_0032ae70(void) {
    if (*(int *)0x587218 == 0) {
        FUN_0032f300();
    }
}

void FUN_0032aea0(void) {
    if (*(int *)0x587218 != 0) {
        FUN_0032f330();
    }
}

