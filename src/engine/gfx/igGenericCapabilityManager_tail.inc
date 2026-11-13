/* igGenericCapabilityManager vtable slot 23: always answers 1. The
 * igVisualContextCapabilityManager override forwards the same slot to its igVisualContext, so this
 * is a yes/no capability query where the generic manager says "yes". The receiver is not read. */
int Gap__Gfx__igGenericCapabilityManager__vfunc_23(void) {
    return 1;
}

int FUN_00155340(FieldTypeTable *table, unsigned int type) {
    FieldTypeList *list;

    if (type < 47) {
        switch (type) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
            return g_igVec4fMetaField_metaObject;
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
            return g_igMatrix44fMetaField_metaObject;
        default:
            return 0;
        }
    }
    list = table->extraTypes;
    if ((int)type < list->_count + 47) {
        int index = type - 47;
        igSmartPointer<FieldTypeEntry> entry(list->_data[index], kRetainReference);
        if (entry == 0) {
            return 0;
        }
        return entry->source->getMetaObject();
    }
    return 0;
}

int FUN_00155490(void) {
    return g_igMetaField_metaObject[0];
}

StringRef FUN_001554a0(int arg1) {
    int i;
    char *s;
    int r;
    igSmartPointer<Ref_1554a0> text(FUN_002b9500(Memory_GetAllocatorBySelector(DAT_00587048[0])));
    igStringObj_Set(text.get(), arg1);
    igStringObj_ToLower(text.get());
    for (i = text.get()->len - 1; i >= 0; i--) {
        if (text.get()->str[i] == 0x5F) {
            igStringObj_Erase(text.get(), i, 1);
        }
    }
    s = text.get()->str;
    if (s == 0) {
        s = (char *)g_stringObjEmptyText[0];
    }
    if (s == 0) {
        r = 0;
    } else {
        if (g_stringPool[0] == 0) {
            r = StringPool_Allocate(0x10);
            if (r != 0) {
                r = StringPool_Construct(r);
            }
            g_stringPool[0] = r;
        }
        r = (int)StringPool_Intern(g_stringPool[0], s);
    }
    return StringRef((char *)r);
}

void *igObject_GetMetaObject_Virtual(void){return (void *)g_igObject_metaObject[0];}

void FUN_00155c00(int *out, Owner *owner, int id) {
    int i;
    List *l = owner->a;
    if (id >= l->count || l->data[id] == 0) {
        *out = g_allocatorFailureStatus[0];
        return;
    }
    for (i = 0; i < owner->b->count; i++) {
        List *lb = owner->b;
        Obj_155c00 *o = lb->data[i];
        if (o && id == o->id) {
            REL(o);
            if (lb->count && i >= 0 && i < lb->count) lb->data[i] = 0;
        }
    }
    {
        List *la = owner->a;
        Obj_155c00 *o = la->data[id];
        REL(o);
        if (la->count && id >= 0 && id < la->count) la->data[id] = 0;
    }
    *out = g_statusSucceeded[0];
}

void FUN_00155db0(O_155db0 *arg0) {
    Ls *s2;
    int s1;
    int s0;
    int n2;
    int a1;
    Rc *o;
    s2 = arg0->f308;
    s1 = s2->cnt;
    for (s0 = 0; s0 < s1; s0++) {
        o = s2->data[s0];
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)(long long)o->refs & 0x7fffffULL) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    n2 = s2->cnt;
    for (a1 = 0; a1 < n2; a1++) {
        s2->data[a1] = 0;
    }
    s2->cnt = 0;
    s2 = arg0->f304;
    s1 = s2->cnt;
    for (s0 = 0; s0 < s1; s0++) {
        o = s2->data[s0];
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)(long long)o->refs & 0x7fffffULL) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    n2 = s2->cnt;
    for (a1 = 0; a1 < n2; a1++) {
        s2->data[a1] = 0;
    }
    s2->cnt = 0;
}

int FUN_00155f10(Table *table, int key) {
    StringRef name = FUN_001554a0(key);
    int i = 0;
    if (table->entries->count > 0) {
        for (; i < table->entries->count; i++) {
            igSmartPointer<Entry> entry(table->entries->data[i], kRetainReference);
            if (entry.p == 0) {
                continue;
            }
            if (entry.p->name == name.p) {
                return i;
            }
        }
    }
    return -1;
}

static inline const char *nameOf(const KeyedEntry *entry) {
    return entry->name ? entry->name : emptyString;
}

int FUN_001560b0(KeyedEntryOwner *table, int key) {
    StringRef name = FUN_001554a0(key);
    int i = 0;
    if (table->entries->count > 0) {
        for (i = 0; i < table->entries->count; i++) {
            igSmartPointer<KeyedEntry> entry(table->entries->data[i], kRetainReference);
            if (entry.p && nameOf(entry.p) == name.p) {
                return i + 47;
            }
        }
    }
    for (i = 0; i < 47; i++) {
        if (strcmp(DAT_0048a260[i].name, name.p) == 0) {
            return DAT_0048a260[i].value;
        }
    }
    return -1;
}

int FUN_001562b0(void) {
    return -1;
}

int FUN_001562c0(void) {
    return -1;
}

int FUN_001562d0(struct A_1562d0 *arg0, int arg1) {
    if (arg1 >= 0x2F) {
        return (*(struct C **)((char *)arg0->b->tab + arg1 * 4 - 188))->fc;
    }
    return -1;
}

void FUN_00156300(void) {
    FUN_00308860(g_globalContext[0], &text_ImageData[0], 0x10);
    igMemoryRefMetaField_SetAlignmentType(DAT_0055fde0[0], &text_ImageData[0]);
}

void FUN_00156340(S0_156340 *arg0, void **arg1) {
    int *temp_a1;
    int temp_v1;
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = (void *)(*arg1);
    if (temp_a0 != 0) {
        *(int *)((char *)(temp_a0) - 4) = (int)((int) (*(int *)((char *)(temp_a0) - 4) + 1));
    }
    temp_a0_2 = (void *)(arg0->f58);
    if (temp_a0_2 != 0) {
        temp_a1 = (int *)((char *)temp_a0_2 - 8);
        temp_v1 = *(int *)((char *)(temp_a0_2) - 4) - 1;
        *(int *)((char *)(temp_a0_2) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->f58 = (int)((int) *arg1);
}

static inline void release(T_1566c0 *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}

void FUN_001566c0(S_1566c0 *arg0, S_1566c0 *arg1, int arg2, int arg3, int arg4, int arg5) {
    igSmartPointer<T_1566c0> converted(0);
    igSmartPointer<T_1566c0> spare((T_1566c0 *)FUN_0014db20(igObject_GetAllocator(arg0)));
    int spA4;
    int spA0;
    int sp9C;
    S_1566c0 *src;
    char *var_s5;
    int var_s4;
    int var_s3;
    if ((arg1->f84 + (arg1->f64 + (arg1->f72 + (arg1->f40 + (arg1->f36 + (arg1->f28 + arg1->f32)))))) & 7) {
        void **a = (void **)igObject_GetAllocator(arg0);
        release(converted.p);
        converted.p = (T_1566c0 *)FUN_0014df70((int)a);
        T_1566c0 *created = converted.p;
        if (!(FUN_00157200(created, FUN_0015ac10(arg1->f44), arg1) & 0xFF)) {
            return;
        }
        ((V92a *)arg0)->vX(converted.p, 0);
    } else {
        ((V92a *)arg0)->vX(arg1, 0);
    }
    {
        T_1566c0 *x = converted.p;
        src = arg1;
        if (x != 0) src = (S_1566c0 *)x;
    }
    arg0->f8 = arg4;
    arg0->f12 = arg5;
    FUN_00159320(arg0, arg0->f44, arg0->f8, arg0->f12, &spA4, &sp9C, &spA0);
    arg0->f48 = spA4;
    arg0->f16 = sp9C;
    arg0->f76 = spA0;
    {
        void **alloc = (void **)igObject_GetAllocator(arg0);
        void **v;
        if (g_useOwnerAllocator != 0) {
            v = alloc;
        } else {
            v = (void **)Memory_GetAllocatorBySelector(DAT_005870e8[0]);
        }
        arg0->f52 = (int)((VA *)v)->vX(arg0->f48, 0x80);
    }
    arg0->f60 = 1;
    var_s3 = 0;
    var_s5 = (char *)arg0->f52;
    var_s4 = src->f52 + arg3 * src->f76 + arg2 * ((src->f84 + (src->f64 + (src->f72 + (src->f40 + (src->f36 + (src->f28 + src->f32)))))) >> 3);
    while (var_s3 < arg5) {
        memcpy(var_s5, var_s4, arg0->f76);
        var_s3 += 1;
        var_s4 += src->f76;
        var_s5 += arg0->f76;
    }
    if (arg1->f68 != 0) {
        void **a2 = (void **)igObject_GetAllocator(arg0);
        release(arg0->f68);
        arg0->f68 = (T_1566c0 *)FUN_0014fa50((int)a2);
        FUN_00154c90((igClut *)arg0->f68, (igClut *)arg1->f68, 1);
    }
    if ((arg1->f84 + (arg1->f64 + (arg1->f72 + (arg1->f40 + (arg1->f36 + (arg1->f28 + arg1->f32)))))) & 7) {
        FUN_00157200(arg0, arg1->f44, arg0);
    }
}

int FUN_00156ae0(int arg0, int arg1, float fparg0) {
    int var_v0;

    var_v0 = (int)((int) (0.5f + ((float) arg0 * fparg0)));
    if (var_v0 >= arg1) {
        var_v0 = arg1 - 1;
    }
    return var_v0;
}

void FUN_00156b20(S0_156b20 *arg0, S1_156b20 *arg1) {
    S_temp_a0 *temp_a0;
    if (arg1 != 0) {
        arg1->f4 = (int)((int) (arg1->f4 + 1));
    }
    temp_a0 = (S_temp_a0 *)((void *)(arg0->f44));
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f44 = (int)(arg1);
}

bool FUN_00157140(O_157140 *arg0, int arg1, V_157140 **arg2) {
    bool r = false;
    if (arg1 == arg0->f44) {
        return true;
    }
    if ((*arg2)->vm(arg0->f24, arg0->f44, arg1, arg0->f8, arg0->f12) != 0) {
        r = true;
        if (arg0->f44 == 0x10000 && arg1 == 0x10001) {
            P *p = arg0->f68;
            if (p == 0) {
                r = false;
            } else if (16 < p->f12) {
                r = false;
            }
        }
    }
    return r;
}

/* igFileImagePng vtable slot 42: constant-zero leaf. Slots 40 and 41 also return 0 and slot 45
 * returns 1. The receiver is not read. */
int FUN_00157980(void) {
    return 0;
}

void FUN_00157990(S_arg0 *arg0, int arg1) {
    int sp4C;
    int sp48;
    int sp44;
    int sp40;
    int sp3C;
    int sp38;
    int sp34;
    int sp30;
    int sp2C;
    int sp28;

    arg0->f44 = arg1;
    if (FUN_0015a270(arg0->f44) == 0) {
        FUN_00159a80(arg0->f44, &sp44, &sp40, &sp3C, &sp38, &sp34, &sp30, &sp2C);
        arg0->f64 = sp44;
        arg0->f72 = sp40;
        arg0->f28 = sp3C;
        arg0->f32 = sp38;
        arg0->f36 = sp34;
        arg0->f40 = sp30;
        arg0->f84 = sp2C;
        FUN_00159320(arg0, arg0->f44, arg0->f8, arg0->f12, &sp4C, &sp28, &sp48);
        arg0->f16 = sp28;
    }
}

void FUN_00157a50(void **arg0, void **arg1) {
    void **var_s0;

    var_s0 = (void **)(arg1);
    if (var_s0 == 0) {
        var_s0 = (void **)(arg0);
    }
    if (FUN_00159f70(*(int *)((char *)(var_s0) + 44)) != 0) {
        ((DW4VC_152_2 *)(arg0))->vX((int)(var_s0), (int)(1));
        return;
    }
    ((DW4VC_152_2 *)(arg0))->vX((int)(var_s0), (int)(0));
}

void FUN_00158400(S0_158400 *arg0, int arg1, int arg2) {
    int temp_a0;

    temp_a0 = arg0->f34;
    if ((temp_a0 != 0) && (arg0->f3C != 0)) {
        Memory_FreeBuffer(temp_a0);
    }
    arg0->f34 = arg1;
    arg0->f3C = 0U;
    FUN_00158480((igImage *)arg0);
    arg0->f30 = arg2;
}

void FUN_00158470(void *arg0) {
    *(int *)((char *)arg0 + 24) = 0x66;
}

void FUN_00158480(igImage *arg0) {
    unsigned int sp5C;
    int sp58;
    int sp54;
    int sp50;
    int sp4C;
    int sp48;
    int sp44;
    int sp40;
    int sp3C;
    int sp38;
    int temp_s1;
    int temp_v1;
    unsigned int temp_a0;

    if (FUN_0015a270(arg0->_pfmt) == 0) {
        if (arg0->_pfmt < 0) {
            temp_a0 = arg0->_pz;
            if ((temp_a0 != 0) && (temp_a0 < 5U)) {
                arg0->_pfmt = FUN_00159f00(temp_a0);
            }
        }
        temp_v1 = arg0->_pfmt;
        switch (temp_v1) {
        case 34:
        case 13:
        case 14:
        case 15:
        case 16:
            arg0->_compressed = 1;
            break;
        }
        temp_s1 = arg0->_pfmt;
        FUN_00159320(arg0, temp_s1, arg0->_px, arg0->_py, &sp58, &sp5C, &sp54);
        arg0->_imageSize = sp58;
        arg0->_bytesPerRow = sp54;
        FUN_00159a80(temp_s1, &sp50, &sp4C, &sp48, &sp44, &sp40, &sp3C, &sp38);
        arg0->_bitsInt = sp50;
        arg0->_bitsIdx = sp4C;
        arg0->_bitsRed = sp48;
        arg0->_bitsGrn = sp44;
        arg0->_bitsBlu = sp40;
        arg0->_bitsAlpha = sp3C;
        arg0->_bitsDepth = sp38;
        arg0->_pz = sp5C;
    }
}

void FUN_001585d0(S_1585d0 *arg0) {
    int temp_a0;
    void **var_v0;

    temp_a0 = arg0->f34;
    if ((temp_a0 != 0) && (arg0->f3c != 0)) {
        Memory_FreeBuffer(temp_a0);
        arg0->f34 = 0;
    }
    FUN_00158480((igImage *)arg0);
    var_v0 = (void **)(igObject_GetAllocator(arg0));
    var_v0 = (g_useOwnerAllocator != 0) ? var_v0 : (void **)(Memory_GetAllocatorBySelector(DAT_005870e8[0]));
    arg0->f34 = ((DW4VC_220_2 *)(var_v0))->vX((int)(arg0->f30), (int)(0x80));
    arg0->f3c = 1;
}

void FUN_00158670(ImageView *img, int x, int y, const void *src) {
    int bpp = (img->f84 + (img->f64 + (img->f72 + (img->aBits + (img->bBits + (img->rBits + img->gBits)))))) >> 3;
    memcpy(img->pixels + (y * img->stride + bpp * x), src, bpp);
}

int FUN_00158cc0(S_158cc0 *arg0, void **arg1) {
    unsigned int sp5C;
    unsigned int sp58;
    int sp54, sp50, sp4C, sp48, sp44, sp40, sp3C, sp38, sp34, sp30;
    int temp_s0;
    void **var_v0;
    VStream *st = (VStream *)arg1;

    if (!(((VObj *)arg0)->v38() & 0xFF)) {
        st->v25((char *)arg0 + 48, 4, 1);
        st->v25((char *)arg0 + 8, 4, 1);
        st->v25((char *)arg0 + 12, 4, 1);
        st->v25((char *)arg0 + 16, 4, 1);
        st->v25((char *)arg0 + 20, 4, 1);
        st->v25(&sp58, 4, 1);
        arg0->f28 = (sp58 >> 24) & 0xFF;
        arg0->f32 = (sp58 >> 16) & 0xFF;
        arg0->f36 = (sp58 >> 8) & 0xFF;
        arg0->f40 = (unsigned char)sp58;
        arg0->f84 = 0;
        arg0->f72 = 0;
        arg0->f64 = 0;
        st->v25(&sp5C, 4, 1);
        st->v25(&sp5C, 4, 1);
        var_v0 = (void **)igObject_GetAllocator(arg0);
        var_v0 = (g_useOwnerAllocator != 0) ? var_v0 : Memory_GetAllocatorBySelector(DAT_005870e8[0]);
        arg0->f52 = ((VAlloc *)var_v0)->v53(arg0->f48, 0x80);
        arg0->f60 = 1;
        st->v25(arg0->f52, 1, arg0->f48);
        st->v24();
        arg0->f44 = FUN_00159f00(arg0->f16);
    }
    temp_s0 = arg0->f44;
    FUN_00159320(arg0, temp_s0, arg0->f8, arg0->f12, &sp54, &sp50, &sp4C);
    arg0->f76 = sp4C;
    FUN_00159a80(temp_s0, &sp48, &sp44, &sp40, &sp3C, &sp38, &sp34, &sp30);
    arg0->f64 = sp48;
    arg0->f72 = sp44;
    arg0->f28 = sp40;
    arg0->f32 = sp3C;
    arg0->f36 = sp38;
    arg0->f40 = sp34;
    arg0->f84 = sp30;
    arg0->f24 = 0x64;
    return 1;
}

/* Constant leaf in the igFileImagePng vtable (slot 40): ignores the image object and returns 0,
 * like the adjacent slots 39 and 41. */
int FUN_00158f40(void) {
    return 0;
}

int FUN_00158f50(S_158f50 *arg0, int arg1) {
    int sp5C, sp58, sp54, sp50, sp4C, sp48, sp44;
    int r;
    if (arg0->f52 != 0 && arg0->f60 != 0) Memory_FreeBuffer(arg0->f52);
    arg0->f52 = 0;
    arg0->f64 = 0;
    arg0->f72 = 0;
    arg0->f28 = 0;
    arg0->f32 = 0;
    arg0->f36 = 0;
    arg0->f40 = 0;
    arg0->f84 = 0;
    FUN_00156340((S0_156340 *)arg0, (void **)&ImageName(arg1).text);
    if ((arg0->v37(arg1) & 0xFF) == 1) {
        if (arg0->f44 < 0) {
            arg0->f44 = FUN_00159f00(arg0->f16);
            FUN_00159a80(arg0->f44, &sp5C, &sp58, &sp54, &sp50, &sp4C, &sp48, &sp44);
            arg0->f64 = sp5C;
            arg0->f72 = sp58;
            arg0->f28 = sp54;
            arg0->f32 = sp50;
            arg0->f36 = sp4C;
            arg0->f40 = sp48;
            arg0->f84 = sp44;
        }
        return 1;
    }
    igSmartPointer<VStream_158f50> sp40((VStream_158f50 *)igFile_Create(igObject_GetAllocator(arg0)));
    int sp3C;
    if (sp40.p->v23(arg1, &DAT_004de6c0[0]) == 0) {
        return 0;
    }
    sp40.p->v25(&sp3C, 4, 1);
    switch (sp3C) {
    case 0x1F295FF4:
    case 0xF45F291F:
        r = arg0->v42(sp40.p) & 0xFF;
        return r;
    case 0x312A57F2:
    case 0xF2572A31:
        r = FUN_00158cc0((S_158cc0 *)arg0, (void **)sp40.p) & 0xFF;
        return r;
    default:
        sp40.p->v24();
        return 0;
    }
}

/* Constant leaf in the igFileImagePng vtable (slot 39): ignores the image object and returns 0,
 * like the adjacent slots 40 and 41. */
int FUN_001592a0(void) {
    return 0;
}

/* igFileImagePng vtable slot 41: constant-zero leaf. Slots 40 and 42 also return 0 and slot 45
 * returns 1. The receiver is not read. */
int FUN_001592b0(void) {
    return 0;
}

void FUN_001592c0(LongListStorageView *self) {
    int storage;
    int buffer;

    storage = self->storage;
    if (storage != 0) {
        FUN_00300f50(self, storage);
    }
    buffer = self->buffer;
    if ((buffer != 0) && (self->ownsBuffer != 0)) {
        Memory_FreeBuffer(buffer);
        self->buffer = 0;
    }
}

void FUN_00159a70(void) {

}

int FUN_00159f00(int a) {
    int r;
    switch (a) {
    case 1: r = 0; break;
    case 2: r = 3; break;
    case 3: r = 5; break;
    case 4: r = 7; break;
    default: r = -1; break;
    }
    return r;
}

int FUN_00159f70(int arg0) {
    return (unsigned int) ((arg0 - 0x8000) - 0x8000) < 3U;
}

bool FUN_00159f80(int arg0) {
    bool r = true;
    if (FUN_0015a010(arg0) == 0) {
        bool b = true;
        bool a = false;
        unsigned int t = arg0 - 2;
        if (t < 0x18U && ((1 << t) & 0x987FD5)) {
            a = true;
        }
        if (!a && 1U < (unsigned int)(arg0 - 0x22)) {
            b = false;
        }
        if (!b) {
            r = false;
        }
    }
    return r;
}

int FUN_0015a010(int arg0) {
    return arg0 == 0x10001;
}

void FUN_0015a030(struct A_15a030 *arg0) {
    int *a1;
    int v1;
    int var_v0;
    int *old;
    int *s0;
    int tmp;

    Gap__Core__igObject__vfunc_15(arg0);
    tmp = arg0->f56;
    if (tmp != 0) {
        if (g_stringPool[0] == 0) {
            var_v0 = StringPool_Allocate(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            g_stringPool[0] = var_v0;
        }
        s0 = (int *)StringPool_Intern(g_stringPool[0], tmp);
        old = arg0->f88;
        if (old != 0) {
            a1 = old - 2;
            v1 = old[-1] - 1;
            old[-1] = v1;
            if (v1 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
        arg0->f88 = s0;
        FUN_00300f50(arg0, arg0->f56);
        arg0->f56 = 0;
    }
    FUN_0015a100((S_15a100 *)arg0);
}

void FUN_0015a0f0(void) {
    Gap__Core__igObject__vfunc_14();
}

void FUN_0015a100(S_15a100 *arg0) {
    int n;
    int j;
    unsigned i;
    unsigned char *src;
    unsigned char *dst;
    unsigned char *buf;
    A_15a100 *al;
    int v = arg0->f76;
    if (v > 0) {
        n = v;
    } else {
        n = (unsigned)arg0->f48 / arg0->f12;
    }
    FUN_00158480((igImage *)arg0);
    if (arg0->f52 != 0 && n != arg0->f76) {
        al = (A_15a100 *)igObject_GetAllocator(arg0);
        al = (g_useOwnerAllocator != 0) ? al : (A_15a100 *)Memory_GetAllocatorBySelector(DAT_005870e8[0]);
        buf = al->vX(arg0->f48, 0x80);
        src = arg0->f52;
        dst = buf;
        for (i = 0; i < arg0->f12; i++) {
            for (j = 0; j < n; j++) {
                *dst = *src;
                src++;
                dst++;
            }
            dst += arg0->f76 - n;
        }
        Memory_FreeBuffer(arg0->f52);
        arg0->f52 = buf;
    }
}

unsigned char FUN_0015a220(int arg0) { unsigned char r = 0; long long one = 1; unsigned int t = arg0 - 1; if (t < 35) { if ((one << t) & 0x401900DE7LL) { r = one; } } return r; }

int FUN_0015a270(int arg0) {
    return arg0 == 0x8000;
}

void FUN_0015a280(unsigned char *arg0, int arg1, int arg2) {
    int i;
    switch (arg2) {
    case 7:
        for (i = 0; i < arg1; i++) {
            unsigned char t = arg0[3];
            arg0[3] = (t >> 1) + (t & 1);
            arg0 += 4;
        }
        break;
    case 1:
    case 3:
    case 2:
    case 8:
    case 9:
        break;
    }
}

void FUN_0015a300(u8 *p, int n, int k) { int i; int v; int c; switch (k) { case 7: for (i = 0; i < n; i++) { c = p[3]; if (c & 0x80) v = ~(c & 0xff) << 1; else v = c << 1; p[3] = v; p += 4; } break; case 1: case 3: case 8: case 9: default: break; } }

int FUN_0015a380(S_15a380 *arg0) {
    if (!FUN_0015a220(arg0->f44) && (FUN_00159f70(arg0->f44) == 0)) {
        return 1;
    }
    if (arg0->f52 != 0) {
        FUN_0015a300((unsigned char *)arg0->f52, arg0->f8 * arg0->f12, arg0->f44);
    }
    if (FUN_00159f70(arg0->f44) != 0 && arg0->f68 != 0) {
        return FUN_00154b40((Obj_154b40 *)arg0->f68);
    }
    return 1;
}

void FUN_0015a420(C_15a420 *o, int a1, int a2, int a3, int a4, int a5) {
    o->v28(a2); o->v26(a4); o->v27(a5); o->v30(a3);
    if (a1 != o->f52) { o->v29(); int y = o->f48; int x = o->f52; memcpy(x, a1, y); } else { o->f60 = 1; FUN_00158480((igImage *)o); }
}

void FUN_0015a500(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 24) = arg1;
}

void FUN_0015a510(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 12) = (int) (arg1 & 0xFFFF);
}

void FUN_0015a520(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 8) = (int) (arg1 & 0xFFFF);
}

int FUN_0015a600(T_15a600 *arg0) {
    int t;
    if (!FUN_0015a220(arg0->f2c) && (FUN_00159f70(arg0->f2c) == 0)) {
        return 1;
    }
    t = arg0->f34;
    if (t != 0) {
        FUN_0015a280((unsigned char *)t, arg0->f8 * arg0->fc, arg0->f2c);
    }
    if (FUN_00159f70(arg0->f2c) != 0) {
        t = arg0->f44;
        if (t != 0) {
            return FUN_00154d40((Obj_154d40 *)t);
        }
    }
    return 1;
}

void FUN_0015a6a0(Img *arg0, E *out) {
    int w;
    int h;
    E *r0;
    E *r1;
    int x;
    int y;
    long long t;
    long long u;
    w = arg0->w >> 2;
    h = arg0->h >> 2;
    r0 = arg0->data;
    r1 = r0 + w;
    for (y = 0; y < h; y += 2) {
        for (x = 0; x < w; x += 2) {
            /* matching construct: spelling grid — field-wise copies through two shared temporaries keep the ld/ld/sd/sd pairs */
            t = r0[0].a; u = r0[0].b; out[0].a = t; out[0].b = u;
            t = r0[1].a; u = r0[1].b; out[1].a = t; out[1].b = u;
            t = r1[0].b; u = r1[0].a; out[2].a = u; out[2].b = t;
            t = r1[1].b; u = r1[1].a; out[3].a = u; out[3].b = t;
            r0 += 2;
            r1 += 2;
            out += 4;
        }
        r0 += w;
        r1 += w;
    }
}

void FUN_0015aaf0(unsigned char *dst, unsigned char *src, int count)
{
    int i;
    unsigned int packed;

    for (i = 0; i < count - 1; i += 2) {
        packed = src[0] & 0xF;
        packed |= src[1] << 4;
        *dst++ = packed;
        src += 2;
    }
    if (i < count)
        *dst = (*src & 0xF) << 4;
}

void FUN_0015ab50(int arg0, int arg1) {
    if (arg0 != arg1) {
        memmove();
    }
}

void FUN_0015ab70(int arg0, int arg1) {
    if (arg0 != arg1) {
        memmove();
    }
}

/* matching construct: 24-variant sweep — statement and declaration order */
void FUN_0015ab90(unsigned char *dst, unsigned char *src, int count)
{
    int i;
    unsigned int packed;

    dst = dst + count - 1;
    src = src + ((count + 1) >> 1) - 1;
    i = 0;
    if (count & 1) {
        *dst = ((unsigned int)*src >> 4) & 0xF;
        i++;
        src--;
        dst--;
    }
    for (; i < count; i += 2) {
        packed = *src;
        dst[0] = (packed >> 4) & 0xF;
        dst[-1] = packed & 0xF;
        src--;
        dst -= 2;
    }
}

int FUN_0015ac10(int x) {
    switch (x) {
    default:
        switch (x) {
        case 2: return 3;
        case 4: return 5;
        case 6: return 7;
        case 8:
        case 12: return 7;
        case 0x10001: return 0x10000;
        }
        break;
    case 10: return 5;
    case 9: return 7;
    case 11: return 7;
    }
    if (FUN_00159f80(x)) x = -1;
    return x;
}

void FUN_0015ad20(int a0, int a1, int a2)
{
    *(int *)((char *)a1 + 52) = a2;
}

void FUN_0015ad30(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {
    FUN_00159320(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

int FUN_0015ad50(char *arg0) {
    int n = strlen();

    while (n > 0) {
        n--;
        if (arg0[n] == 0x2E) {
            return (int)arg0 + n;
        }
    }
    return 0;
}

int FUN_0015adb0(S0_15adb0 *arg0, int arg1, int arg2, int arg3) {
    int var_s1;
    Rc_15adb0 *temp_a0;
    V_15adb0 *temp_a0_2;
    Rc_15adb0 *temp_v0;

    if (arg0->f12 != 0) {
        return 0;
    }
    arg0->f16 = arg1;
    arg0->f20 = arg3;
    arg0->f24 = arg2;
    if (arg3 == 0) {
        var_s1 = arg0->f16 * 2;
    } else {
        var_s1 = arg0->f16 * 4;
    }
    if (arg0->f8 == 0) {
        temp_v0 = (Rc_15adb0 *)igObject_GetAllocator(arg0);
        if (temp_v0 != 0) {
            temp_v0->rc = temp_v0->rc + 1;
        }
        temp_a0 = (Rc_15adb0 *)arg0->f8;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->f8 = (V_15adb0 *)temp_v0;
    }
    temp_a0_2 = arg0->f8;
    arg0->f12 = temp_a0_2->vX(var_s1);
    return var_s1;
}

int FUN_0015aea0(O_15aea0 *arg0, unsigned int arg1, int arg2, int arg3, int arg4) {
    unsigned int n;
    int *s1;
    unsigned short *s0;
    int ret;
    unsigned int i;
    int *d4;
    short *d2;

    n = arg0->f10;
    n = (n < arg1) ? n : arg1;
    s1 = 0;
    s0 = 0;
    arg0->v33();
    if (arg3 == 0) {
        s0 = (unsigned short *)arg0->f0c;
    } else {
        s1 = (int *)arg0->f0c;
    }
    arg0->f0c = 0;
    arg0->f10 = 0;
    ret = arg0->v21(arg1, arg2, arg3, arg4);
    if (s0 != 0) {
        if (arg3 == 0) {
            memcpy(arg0->f0c, s0, n * 2);
        } else {
            d4 = (int *)arg0->f0c;
            for (i = 0; i < n; i++) {
                d4[i] = s0[i];
            }
        }
        Memory_FreeBuffer(s0);
    } else {
        if (arg3 == 1) {
            memcpy(arg0->f0c, s1, n * 4);
        } else {
            d2 = (short *)arg0->f0c;
            for (i = 0; i < n; i++) {
                d2[i] = s1[i];
            }
        }
        Memory_FreeBuffer(s1);
    }
    arg0->v34();
    return ret;
}

/* Empty override (a bare return) in vtable slot 36 of Gap::Core::igPsx2IndexArray, next to slot
 * 35, which is also empty. */
void FUN_0015b050(void) {
}

void FUN_0015b060(void *arg0, int arg1, int arg2) {
    *(short *)(*(int *)((char *)(arg0) + 12) + (arg1 * 2)) = arg2;
}

void FUN_0015b080(void *arg0, int arg1, int arg2) {
    *(int *)(*(int *)((char *)(arg0) + 12) + (arg1 * 4)) = arg2;
}

void FUN_0015b0a0(void *a0, int arg1, int arg2) {
 O_15b0a0 *arg0=(O_15b0a0*)a0;
switch (arg0->f14) {
 case 1: ((VC_120 *)arg0)->vX(); break;
 case 0: ((VC_116 *)arg0)->vX(arg1 & 0xFFFF, arg2 & 0xFFFF); break;
 }
}

unsigned short FUN_0015b100(void *arg0, int arg1) {
    return *(int *)(*(int *)((char *)(arg0) + 12) + (arg1 * 2));
}

int FUN_0015b120(void *arg0, int arg1) {
    return *(int *)(*(int *)((char *)(arg0) + 12) + (arg1 * 4));
}

int FUN_0015b140(igPsx2IndexArray *self, int index) {
    int dataSize;

    dataSize = self->_dataSize;
    switch (dataSize) {
    case 1:
        return ((IndexArrayWideReadSlot *)(self))->ReadWide(index);
    case 0:
        return ((IndexArrayNarrowReadSlot *)(self))->ReadNarrow((int)(index & 0xFFFF)) & 0xFFFF;
    default:
        return 0;
    }
}

/* arg1 is unused but must stay: the value arrives in the third parameter (a2), and a two-parameter
 * spelling would put it in a1. */
int FUN_0015b1a0(int arg0, int arg1, int arg2) {
    return *(int *)((char *)(arg0) + 12) + (arg2 * 2);
}

int FUN_0015b1b0(int arg0, int arg1, int arg2) {
    return *(int *)((char *)(arg0) + 12) + (arg2 * 4);
}

void FUN_0015b1c0(void) {

}

void FUN_0015b1d0(void) {

}

void FUN_0015b1e0(void *arg0) {
    *(int *)((char *)arg0 + 0) = 0;
    *(int *)((char *)arg0 + 4) = 0;
    *(int *)((char *)arg0 + 8) = 0;
    *(int *)((char *)arg0 + 12) = 0;
    *(int *)((char *)arg0 + 16) = 0;
    *(int *)((char *)arg0 + 20) = 0;
    *(int *)((char *)arg0 + 24) = 0;
    *(int *)((char *)arg0 + 28) = 0;
    *(int *)((char *)arg0 + 32) = 0;
    *(int *)((char *)arg0 + 36) = 0;
    *(int *)((char *)arg0 + 40) = 0;
    *(int *)((char *)arg0 + 44) = 0;
    *(int *)((char *)arg0 + 48) = 0;
    *(int *)((char *)arg0 + 52) = 0;
    *(int *)((char *)arg0 + 56) = 0;
    *(int *)((char *)arg0 + 60) = 0;
    *(int *)((char *)arg0 + 64) = 0;
    *(int *)((char *)arg0 + 68) = 0;
    *(int *)((char *)arg0 + 72) = 0;
    *(int *)((char *)arg0 + 76) = 0;
    *(int *)((char *)arg0 + 80) = 0;
    *(int *)((char *)arg0 + 84) = 0;
    *(int *)((char *)arg0 + 88) = 0;
    *(int *)((char *)arg0 + 92) = 0;
    *(int *)((char *)arg0 + 96) = 0;
    *(int *)((char *)arg0 + 100) = 0;
    *(int *)((char *)arg0 + 104) = 0;
    *(int *)((char *)arg0 + 108) = 0;
    *(int *)((char *)arg0 + 112) = 0;
    *(int *)((char *)arg0 + 116) = 0x3F800000;
    *(int *)((char *)arg0 + 120) = 0x3F800000;
    *(int *)((char *)arg0 + 124) = 0;
    *(int *)((char *)arg0 + 128) = 0;
    *(int *)((char *)arg0 + 132) = 0;
    *(int *)((char *)arg0 + 136) = 0;
    *(int *)((char *)arg0 + 140) = 0;
}

