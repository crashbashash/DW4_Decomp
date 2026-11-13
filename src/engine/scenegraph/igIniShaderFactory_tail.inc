int FUN_001c6520(O_1c6520 *arg0, int arg1) {
    Ob *sp3C;
    Ob *a0;
    Ob *s0;
    int s0i;
    int v, old, s;
    int *hd;
    if (arg1 == 0 && arg0->f28 != 0) {
        return 1;
    }
    FUN_001cd150((IniDocument * *)((Ob **)&sp3C), (IniFactoryState *)arg0, (char *)arg0->f24);
    if (sp3C != arg0->f28) {
        a0 = arg0->f32;
        if (a0 != 0) {
            a0->refs = a0->refs - 1;
            if ((a0->refs & 0x7fffff) == 0) {
                igObject_Destroy(a0);
            }
        }
        arg0->f32 = 0;
        if (g_stringPool[0] == 0) {
            v = StringPool_Allocate(16);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            g_stringPool[0] = v;
        }
        s = StringPool_Intern(g_stringPool[0], 0);
        old = arg0->f36;
        if (old != 0) {
            hd = (int *)(old - 8);
            v = *(int *)(old - 4) - 1;
            *(int *)(old - 4) = v;
            if (v == 0) {
                StringChunk_ReleaseHeader(*hd, hd);
            }
        }
        arg0->f36 = s;
        arg0->f40 = -1;
        s0 = sp3C;
        if (s0 != 0) {
            s0->refs = s0->refs + 1;
        }
        a0 = arg0->f28;
        if (a0 != 0) {
            a0->refs = a0->refs - 1;
            if ((a0->refs & 0x7fffff) == 0) {
                igObject_Destroy(a0);
            }
        }
        arg0->f28 = s0;
    }
    s0i = arg0->f28 != 0;
    a0 = sp3C;
    if (a0 != 0) {
        a0->refs = a0->refs - 1;
        if ((a0->refs & 0x7fffff) == 0) {
            igObject_Destroy(a0);
        }
    }
    return s0i;
}

#define REL_OBJ(o) { Obj_1c66c0 *t_ = (o); if (t_ != 0) { t_->u.w = t_->u.w - 1; if (t_->u.b.cnt == 0) igObject_Destroy(t_); } }
#define RET_OBJ(o) { Obj_1c66c0 *t_ = (o); if (t_ != 0) t_->u.w = t_->u.w + 1; }
#define REL_TMP(o) { if (o != 0) { o->u.w = o->u.w - 1; if (o->u.b.cnt == 0) igObject_Destroy(o); } }
#define REL_STR(s) { char *t_ = (s); if (t_ != 0) { int *hd_ = (int *)t_ - 2; int c_ = ((int *)t_)[-1] - 1; ((int *)t_)[-1] = c_; if (c_ == 0) StringChunk_ReleaseHeader(*hd_, hd_); } }
#define REL_ALL() { REL_OBJ(sp40.p) REL_OBJ(sp44.p) REL_STR(sp48) REL_STR(sp4C) }
int FUN_001c66c0(Node *self, int force)
{
    char *sp4C;
    char *sp48;
    RP sp44;
    RP sp40;
    Obj_1c66c0 *sp3C;
    Obj_1c66c0 *sp38;
    Obj_1c66c0 *sp34;
    int idx;
    char *s;
    char *t;
    const char *a;
    const char *b;

    if (force == 0 && self->f32 != 0) {
        return 1;
    }
    if (FUN_001c6520((O_1c6520 *)self, force) == 0) {
        return 0;
    }
    REL_OBJ(self->f32)
    self->f32 = 0;
    if (g_stringPool[0] == 0) {
        int pool = StringPool_Allocate(16);
        if (pool != 0) pool = StringPool_Construct(pool);
        g_stringPool[0] = pool;
    }
    s = ((char *)StringPool_Intern(g_stringPool[0], 0));
    REL_STR(self->f36)
    self->f36 = s;
    self->f40 = -1;
    idx = FUN_00306360(self->f28, (char *)&text_Interface[0], 0);
    if (idx < 0) {
        return 0;
    }
    sp4C = 0;
    sp48 = 0;
    {
        unsigned char found = FUN_00306910(self->f28, idx, &text_fileName[0], &sp4C, &DAT_004e4660[0], 0);
        sp44.p = 0;
        RET_OBJ(sp44.p)
        sp40.p = 0;
        RET_OBJ(sp40.p)
        if (!found) {
            t = self->f24;
            if (t != 0) ((int *)t)[-1] = ((int *)t)[-1] + 1;
            REL_STR(sp4C)
            sp4C = self->f24;
        }
    }
    if (!(FUN_00306910(self->f28, idx, &text_section[0], &sp48, &DAT_004e4660[0], 0) & 0xFF)) {
        REL_ALL()
        return 0;
    }
    FUN_001ce400((IniStringObject * *)&sp3C, self->f24);
    {
        Obj_1c66c0 *n = sp3C;
        if (n != 0) n->u.w = n->u.w + 1;
        REL_OBJ(sp40.p)
        sp40.p = n;
    }
    REL_TMP(sp3C)
    FUN_001ce400((IniStringObject * *)&sp38, sp4C);
    {
        Obj_1c66c0 *n = sp38;
        if (n != 0) n->u.w = n->u.w + 1;
        REL_OBJ(sp44.p)
        sp44.p = n;
    }
    REL_TMP(sp38)
    if (sp44.p == 0) {
        REL_ALL()
        return 0;
    }
    {
        Obj_1c66c0 *o40 = sp40.p;
        a = sp44.p->f8;
        if (a == 0) a = g_stringObjEmptyText[0];
        b = o40->f8;
        if (b == 0) b = g_stringObjEmptyText[0];
    }
    if (thunk_strcasecmp(a, b) == 0) {
        Obj_1c66c0 *par = self->f28;
        if (par != 0) par->u.w = par->u.w + 1;
        REL_OBJ(self->f32)
        self->f32 = par;
    } else {
        FUN_001cd150((IniDocument * *)&sp34, (IniFactoryState *)self, sp4C);
        {
            Obj_1c66c0 *n = sp34;
            if (n != 0) n->u.w = n->u.w + 1;
            REL_OBJ(self->f32)
            self->f32 = n;
        }
        REL_TMP(sp34)
        if (self->f32 == 0) {
            REL_ALL()
            return 0;
        }
    }
    self->f40 = FUN_00306360(self->f32, sp48, 0);
    if (self->f40 == -1) {
        REL_OBJ(self->f32)
        self->f32 = 0;
        REL_ALL()
        return 0;
    }
    t = sp4C;
    if (t != 0) ((int *)t)[-1] = ((int *)t)[-1] + 1;
    REL_STR(self->f36)
    self->f36 = sp4C;
    REL_ALL()
    return 1;
}
#undef REL_OBJ
#undef RET_OBJ
#undef REL_TMP
#undef REL_STR
#undef REL_ALL

IniStrRef FUN_001c6fa0(IniSectionNode *node) {
    int index;
    if (FUN_001c6520((O_1c6520 *)node, 0) == 0) {
        return IniStrRef(0);
    }
    index = FUN_00306360(node->_parent, text_configuration, 0);
    if (index == -1) {
        return IniStrRef(0);
    }
    IniStrRef text(0);
    if (FUN_00306910(node->_parent, index, text_fileName, &text.p, DAT_004e4660, 0) == 0) {
        return IniStrRef(0);
    }
    return text;
}

igSmartPointer<ShaderObject> Gap__Sg__igIniShaderFactory__vfunc_24(Factory *self, const char *name) {
    igSmartPointer<ShaderObject> shader(0, kRetainReference);
    if (FUN_001c66c0((Node *)self, 0) == 0) {
        return igSmartPointer<ShaderObject>(0, kRetainReference);
    }
    if (!FUN_00306770(self->f32, self->f40, name, &shader.p, &DAT_004e4660[0], 0)) {
        return igSmartPointer<ShaderObject>(0, kRetainReference);
    }
    return shader;
}

ObjectRefWord *FUN_001c7600(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void igStringMetaField_AssignRetainedToken(igStringMetaField *arg0, int arg1, void **arg2) {
    int *temp_a1;
    int temp_v1;
    void **temp_s0;
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = (void *)(*arg2);
    temp_s0 = (void **)(arg1 + arg0->_offset);
    if (temp_a0 != 0) {
        *(int *)((char *)(temp_a0) - 4) = (int)((int) (*(int *)((char *)(temp_a0) - 4) + 1));
    }
    temp_a0_2 = (void *)(*temp_s0);
    if (temp_a0_2 != 0) {
        temp_a1 = (int *)((char *)temp_a0_2 - 8);
        temp_v1 = *(int *)((char *)(temp_a0_2) - 4) - 1;
        *(int *)((char *)(temp_a0_2) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    *temp_s0 = *arg2;
}

void StringList_AppendRetained(igStringRefList *arg0, const IniStrRef &value) {
    int *temp_a1_2;
    int temp_s0;
    int temp_v1;
    void **temp_s0_2;
    void *temp_a0;
    void *temp_a1;

    temp_s0 = arg0->_count;
    StringList_Resize(arg0, temp_s0 + 1);
    temp_a1 = (void *)value.p;
    temp_s0_2 = (void **)(arg0->_data + (temp_s0 * 4));
    if (temp_a1 != 0) {
        *(int *)((char *)(temp_a1) - 4) = (int)((int) (*(int *)((char *)(temp_a1) - 4) + 1));
    }
    temp_a0 = (void *)(*temp_s0_2);
    if (temp_a0 != 0) {
        temp_a1_2 = (int *)((char *)temp_a0 - 8);
        temp_v1 = *(int *)((char *)(temp_a0) - 4) - 1;
        *(int *)((char *)(temp_a0) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
        }
    }
    *temp_s0_2 = value.p;
}

int FUN_001ca6b0(int *p, int)
{
    return *(int *)((char *)p + 52);
}

igSmartPointer<ShaderObject_1ca6c0> FUN_001ca6c0(ShaderProcessorView *self, char *name, unsigned char flag) {
    int section;
    ShaderMetaView *meta;
    int count;
    int i;
    char *field;
    void *info;
    unsigned char cached;
    section = FUN_00306360(self->ini, name, 0);
    if (section == -1) {
        return igSmartPointer<ShaderObject_1ca6c0>(0, kRetainReference);
    }
    IniStrRef text(0);
    if (FUN_00306910(self->ini, section, text_type, &text.p, DAT_004e4660, 0) == 0) {
        return igSmartPointer<ShaderObject_1ca6c0>(0, kRetainReference);
    }
    meta = FUN_002fe460(text.p);
    if (meta == 0) {
        return igSmartPointer<ShaderObject_1ca6c0>(0, kRetainReference);
    }
    igSmartPointer<ShaderObject_1ca6c0> object = FUN_002fd6e0(meta, self->allocatorKey);
    if (object.p == 0) {
        return igSmartPointer<ShaderObject_1ca6c0>(0, kRetainReference);
    }
    igSmartPointer<ShaderNameList> names(igStringRefList_Create(((void *)igObject_GetAllocator(self))));
    FUN_00306aa0(self->ini, section, text_fields, names.p, 0);
    count = names.p->count;
    for (i = 0; i < count; i++) {
        field = StringList_CopyRetained((igStringRefList *)names.p, i).p;
        releaseString(field);
        info = FUN_002fdf20(meta, field);
        if (info == 0) {
            return igSmartPointer<ShaderObject_1ca6c0>(0, kRetainReference);
        }
        if (FUN_001c7680(self, section, field, object.p, info, &flag) == 0) {
            return igSmartPointer<ShaderObject_1ca6c0>(0, kRetainReference);
        }
    }
    {
        bool initial = !(bool)flag;
        cached = initial;
        FUN_00306e50(self->ini, section, text_const, &cached, initial, 0);
    }
    if (cached != 0) {
        ShaderCacheView *cache = ((ShaderCacheView *)FUN_001ca6b0((int *)self, self->kind));
        ShaderObject_1ca6c0 *existing = ((ShaderObject_1ca6c0 *)FUN_00303d70(cache, name));
        if (existing != 0) {
            if (FUN_00300920(existing, object.p) != 0) {
                return igSmartPointer<ShaderObject_1ca6c0>(existing, kRetainReference);
            }
            return object;
        }
        FUN_00303cd0(cache, name, object.p);
    }
    return object;
}

void FUN_001cade0(void *self, IniFieldTarget *target, IniItemList *items, void *names, void *lookup, void *fieldNames) {
    int i;
    for (i = 0; i < items->count; i++) {
        void *item = itemAt(items, i);
        RetainedString name = StringList_CopyRetained((igStringRefList *)names, i);
        int index;
        index = FUN_001cafc0((struct L_1cafc0 *)lookup, name, 0);
        if (index != -1) {
            RetainedString fieldName = StringList_CopyRetained((igStringRefList *)fieldNames, index);
            IniFieldView *field;
            field = asObjectRefField((IniFieldView *)igMetaObject_FindFieldByName(target->getMeta(), fieldName.p));
            if (field != 0 && igObject_IsKindOf(item, field->refMeta) != 0) {
                igObjectRefMetaField_Assign(field, target, item);
            }
            releaseString(fieldName.p);
        }
        releaseString(name.p);
    }
}
