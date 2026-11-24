int FUN_001c6520(O_1c6520 *arg0, int arg1) {
    Ob *document;
    Ob *a0;
    Ob *s0;
    int s0i;
    int v, old, s;
    int *hd;
    if (arg1 == 0 && arg0->f28 != 0) {
        return 1;
    }
    FUN_001cd150((IniDocument * *)((Ob **)&document), (IniFactoryState *)arg0, (char *)arg0->f24);
    if (document != arg0->f28) {
        a0 = arg0->f32;
        if (a0 != 0) {
            a0->refs = a0->refs - 1;
            if ((a0->refs & 0x7fffff) == 0) {
                igObject_Destroy((igObject *)a0);
            }
        }
        arg0->f32 = 0;
        if (g_stringPool == 0) {
            v = (int)StringPool_Allocate(16);
            if (v != 0) {
                v = (int)StringPool_Construct((StringPool *)v);
            }
            g_stringPool = (StringPool *)v;
        }
        s = (int)StringPool_Intern(g_stringPool, 0);
        old = arg0->f36;
        if (old != 0) {
            hd = (int *)(old - 8);
            v = *(int *)(old - 4) - 1;
            *(int *)(old - 4) = v;
            if (v == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
            }
        }
        arg0->f36 = s;
        arg0->f40 = -1;
        s0 = document;
        if (s0 != 0) {
            s0->refs = s0->refs + 1;
        }
        a0 = arg0->f28;
        if (a0 != 0) {
            a0->refs = a0->refs - 1;
            if ((a0->refs & 0x7fffff) == 0) {
                igObject_Destroy((igObject *)a0);
            }
        }
        arg0->f28 = s0;
    }
    s0i = arg0->f28 != 0;
    a0 = document;
    if (a0 != 0) {
        a0->refs = a0->refs - 1;
        if ((a0->refs & 0x7fffff) == 0) {
            igObject_Destroy((igObject *)a0);
        }
    }
    return s0i;
}

#define REL_OBJ(o) { Obj_1c66c0 *t_ = (o); if (t_ != 0) { t_->u.w = t_->u.w - 1; if (t_->u.b.cnt == 0) igObject_Destroy((igObject *)t_); } }
#define RET_OBJ(o) { Obj_1c66c0 *t_ = (o); if (t_ != 0) t_->u.w = t_->u.w + 1; }
#define REL_TMP(o) { if (o != 0) { o->u.w = o->u.w - 1; if (o->u.b.cnt == 0) igObject_Destroy((igObject *)o); } }
#define REL_STR(s) { char *t_ = (s); if (t_ != 0) { int *hd_ = (int *)t_ - 2; int c_ = ((int *)t_)[-1] - 1; ((int *)t_)[-1] = c_; if (c_ == 0) StringChunk_ReleaseHeader((StringChunk *)*hd_, (StringTokenHeader *)hd_); } }
#define REL_ALL() { REL_OBJ(ownDoc.p) REL_OBJ(fileDoc.p) REL_STR(sectionName) REL_STR(fileName) }
int FUN_001c66c0(Node *self, int force)
{
    char *fileName;
    char *sectionName;
    RP fileDoc;
    RP ownDoc;
    Obj_1c66c0 *ownDocTemp;
    Obj_1c66c0 *fileDocTemp;
    Obj_1c66c0 *loadedDocTemp;
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
    if (g_stringPool == 0) {
        int pool = (int)StringPool_Allocate(16);
        if (pool != 0) pool = (int)StringPool_Construct((StringPool *)pool);
        g_stringPool = (StringPool *)pool;
    }
    s = ((char *)StringPool_Intern(g_stringPool, 0));
    REL_STR(self->f36)
    self->f36 = s;
    self->f40 = -1;
    idx = ((Gap::Core::igRegistry *)self->f28)->findSection((char *)"Interface", 0);
    if (idx < 0) {
        return 0;
    }
    fileName = 0;
    sectionName = 0;
    {
        unsigned char found = ((Gap::Core::igRegistry *)self->f28)->getValue(idx, "fileName", *(igStringRef *)&fileName, "", 0);
        fileDoc.p = 0;
        RET_OBJ(fileDoc.p)
        ownDoc.p = 0;
        RET_OBJ(ownDoc.p)
        if (!found) {
            t = self->f24;
            if (t != 0) ((int *)t)[-1] = ((int *)t)[-1] + 1;
            REL_STR(fileName)
            fileName = self->f24;
        }
    }
    if (!(((Gap::Core::igRegistry *)self->f28)->getValue(idx, "section", *(igStringRef *)&sectionName, "", 0) & 0xFF)) {
        REL_ALL()
        return 0;
    }
    FUN_001ce400((IniStringObject * *)&ownDocTemp, self->f24);
    {
        Obj_1c66c0 *n = ownDocTemp;
        if (n != 0) n->u.w = n->u.w + 1;
        REL_OBJ(ownDoc.p)
        ownDoc.p = n;
    }
    REL_TMP(ownDocTemp)
    FUN_001ce400((IniStringObject * *)&fileDocTemp, fileName);
    {
        Obj_1c66c0 *n = fileDocTemp;
        if (n != 0) n->u.w = n->u.w + 1;
        REL_OBJ(fileDoc.p)
        fileDoc.p = n;
    }
    REL_TMP(fileDocTemp)
    if (fileDoc.p == 0) {
        REL_ALL()
        return 0;
    }
    {
        Obj_1c66c0 *o40 = ownDoc.p;
        a = fileDoc.p->f8;
        if (a == 0) a = g_stringObjEmptyText;
        b = o40->f8;
        if (b == 0) b = g_stringObjEmptyText;
    }
    if (igStrcasecmp(a, b) == 0) {
        Obj_1c66c0 *par = self->f28;
        if (par != 0) par->u.w = par->u.w + 1;
        REL_OBJ(self->f32)
        self->f32 = par;
    } else {
        FUN_001cd150((IniDocument * *)&loadedDocTemp, (IniFactoryState *)self, fileName);
        {
            Obj_1c66c0 *n = loadedDocTemp;
            if (n != 0) n->u.w = n->u.w + 1;
            REL_OBJ(self->f32)
            self->f32 = n;
        }
        REL_TMP(loadedDocTemp)
        if (self->f32 == 0) {
            REL_ALL()
            return 0;
        }
    }
    self->f40 = ((Gap::Core::igRegistry *)self->f32)->findSection(sectionName, 0);
    if (self->f40 == -1) {
        REL_OBJ(self->f32)
        self->f32 = 0;
        REL_ALL()
        return 0;
    }
    t = fileName;
    if (t != 0) ((int *)t)[-1] = ((int *)t)[-1] + 1;
    REL_STR(self->f36)
    self->f36 = fileName;
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
    index = ((Gap::Core::igRegistry *)node->_parent)->findSection("configuration", 0);
    if (index == -1) {
        return IniStrRef(0);
    }
    IniStrRef text(0);
    if ((unsigned char)((Gap::Core::igRegistry *)node->_parent)->getValue(index, "fileName", *(igStringRef *)(&text.p), "", 0) == 0) {
        return IniStrRef(0);
    }
    return text;
}

namespace Gap {
namespace Sg {

igSmartPointer<igStringObj> igIniShaderFactory::getInterfaceParameterString(const char *name) {
    igStringObjRef shader(0, kRetainReference);
    if (FUN_001c66c0((Node *)this, 0) == 0) {
        return igStringObjRef(0, kRetainReference);
    }
    if (!((Gap::Core::igRegistry *)((Factory *)this)->f32)->getValue(((Factory *)this)->f40, name, shader, "", 0)) {
        return igStringObjRef(0, kRetainReference);
    }
    return shader;
}
}
}

igSmartPointer<igObject> *igSmartPointer_igDataPumpInterface_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

/* The kit's inline Gap::Core::igStringMetaField::set(igObject *, igStringRef) left out of line; this unit's copy
 * is the one retail keeps (core's is a duplicate of it). It stays a C definition until its caller here,
 * FUN_001c7680, is decompiled and emits it. */
void igStringMetaField_AssignRetainedToken(igStringMetaField *arg0, void *object, char **arg2) {
    int *temp_a1;
    int temp_v1;
    void **temp_s0;
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = (void *)(*arg2);
    temp_s0 = (void **)((char *)object + arg0->_offset);
    if (temp_a0 != 0) {
        *(int *)((char *)(temp_a0) - 4) = (int)((int) (*(int *)((char *)(temp_a0) - 4) + 1));
    }
    temp_a0_2 = (void *)(*temp_s0);
    if (temp_a0_2 != 0) {
        temp_a1 = (int *)((char *)temp_a0_2 - 8);
        temp_v1 = *(int *)((char *)(temp_a0_2) - 4) - 1;
        *(int *)((char *)(temp_a0_2) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*temp_a1, (StringTokenHeader *)temp_a1);
        }
    }
    *temp_s0 = *arg2;
}

void StringList_AppendRetained(igStringRefList *arg0, char *const *value) {
    int *temp_a1_2;
    int temp_s0;
    int temp_v1;
    void **temp_s0_2;
    void *temp_a0;
    void *temp_a1;

    temp_s0 = arg0->_count;
    StringList_Resize((igTDataList<char *> *)arg0, temp_s0 + 1);
    temp_a1 = (void *)*value;
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
            StringChunk_ReleaseHeader((StringChunk *)*temp_a1_2, (StringTokenHeader *)temp_a1_2);
        }
    }
    *temp_s0_2 = *value;
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
    section = ((Gap::Core::igRegistry *)self->ini)->findSection(name, 0);
    if (section == -1) {
        return igSmartPointer<ShaderObject_1ca6c0>(0, kRetainReference);
    }
    IniStrRef text(0);
    if ((unsigned char)((Gap::Core::igRegistry *)self->ini)->getValue(section, "type", *(igStringRef *)(&text.p), "", 0) == 0) {
        return igSmartPointer<ShaderObject_1ca6c0>(0, kRetainReference);
    }
    meta = (ShaderMetaView *)igObjectSystem_FindMetaByNameDefault(text.p);
    if (meta == 0) {
        return igSmartPointer<ShaderObject_1ca6c0>(0, kRetainReference);
    }
    igSmartPointer<igObject> object = igMetaObject_CreateInstanceRef((igMetaObject *)meta, (igMemoryPoolView *)self->allocatorKey);
    if (object.p == 0) {
        return igSmartPointer<ShaderObject_1ca6c0>(0, kRetainReference);
    }
    igSmartPointer<ShaderNameList> names((ShaderNameList *)igStringRefList_Create((int)(((void *)((Gap::Core::igObject *)self)->getMemoryPool()))));
    ((Gap::Core::igRegistry *)self->ini)->getValue(section, "fields", (igStringRefList *)names.p, 0);
    count = names.p->count;
    for (i = 0; i < count; i++) {
        field = StringList_CopyRetained((igStringRefList *)names.p, i).p;
        info = igMetaObject_FindFieldByName((igMetaObject *)meta, field);
        if (info == 0) {
            return igSmartPointer<ShaderObject_1ca6c0>(0, kRetainReference);
        }
        if (FUN_001c7680(self, section, field, (ShaderObject_1ca6c0 *)object.p, info, &flag) == 0) {
            return igSmartPointer<ShaderObject_1ca6c0>(0, kRetainReference);
        }
    }
    {
        bool initial = !(bool)flag;
        cached = initial;
        ((Gap::Core::igRegistry *)self->ini)->getValue(section, "const", cached, initial, 0);
    }
    if (cached != 0) {
        ShaderCacheView *cache = ((ShaderCacheView *)FUN_001ca6b0((int *)self, self->kind));
        ShaderObject_1ca6c0 *existing = ((ShaderObject_1ca6c0 *)igObjectStringMap_GetObject(cache, (const char *)name));
        if (existing != 0) {
            if (((Gap::Core::igObject *)existing)->isAlikeShallow((Gap::Core::igObject *)object.p)) {
                return igSmartPointer<ShaderObject_1ca6c0>(existing, kRetainReference);
            }
            return object;
        }
        igObjectStringMap_Add((igObjectStringMap *)cache, (const char *)name, object.p);
    }
    return object;
}

void FUN_001cade0(void *self, IniFieldTarget *target, IniItemList *items, void *names, void *lookup, void *fieldNames) {
    int i;
    for (i = 0; i < items->count; i++) {
        void *item = itemAt(items, i);
        igStringRef name = StringList_CopyRetained((igStringRefList *)names, i);
        int index;
        index = igStringRefList_IndexOf((igStringRefList *)lookup, IniStrRef(name).ref(), 0);
        if (index != -1) {
            igStringRef fieldName = StringList_CopyRetained((igStringRefList *)fieldNames, index);
            IniFieldView *field;
            field = asObjectRefField((IniFieldView *)igMetaObject_FindFieldByName((igMetaObject *)(target->getMeta()), fieldName.p));
            if (field != 0 && ((Gap::Core::igObject *)item)->isOfType((igMetaObject *)field->refMeta) != 0) {
                ((Gap::Core::igObjectRefMetaField *)field)->set((Gap::Core::igObject *)target, (Gap::Core::igObject *)item);
            }
        }
    }
}
