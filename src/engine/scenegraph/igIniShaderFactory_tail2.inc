#define REL(p) { IniHeldObject *o = (p); if(o){ --(o)->refs; if((((unsigned long long)(long long)(o)->refs)&0x7fffffULL)==0) igObject_Destroy(o);}}
#define ADD(o) if(o){ ++(o)->refs; }
bool Gap__Sg__igIniShaderFactory__vfunc_23(IniFactoryBinding *self, int a1, IniHeldObject *a2, int a3) {
    unsigned char ok = 1;
    if (FUN_001c6520((O_1c6520 *)self, 1) != 0) {
        IniHeldObject *n;
        ADD(a2);
        REL(self->r48);
        self->r48 = a2;
        n = (IniHeldObject *)igObject_GetAllocator(a1);
        ADD(n);
        REL(self->r44);
        self->r44 = n;
        ok = !FUN_001cb340((ShaderProcessorView *)self, (ShaderTarget *)a1, a3);
    }
    if (ok) Gap__Sg__igShaderFactory__vfunc_23(self, (VA_1d8980 *)a1, a2, a3);
    REL(self->r48);
    self->r48 = 0;
    REL(self->r44);
    self->r44 = 0;
    return !ok;
}
#undef REL
#undef ADD

void Gap__Sg__igIniShaderFactory__vfunc_26(int a0) {
    FUN_00303ed0(*(int *)((char *)a0 + 56));
}

void FUN_001ccd10(IniShaderFactoryView *self, IniNodeList *list) {
    int i;
    int j;
    if (list != 0) {
        for (i = 0; i < list->count; i++) {
            IniNode *node = list->data[i];
            switch (node->type) {
            case 0:
                FUN_001ccd10(self, node->children);
                break;
            case 1: {
                IniEntryList *entries = node->entries;
                for (j = 0; j < entries->count; j++) {
                    IniEntry *e = entries->data[j];
                    if (FUN_0030ba90(e->name, text_file) != 0) {
                        char *s = e->value->text;
                        s = (s == 0) ? g_stringObjEmptyText[0] : s;
                        FUN_001cdbb0((IniFactoryView *)self, s);
                    }
                }
                break;
            }
            }
        }
    }
}

void Gap__Sg__igIniShaderFactory__vfunc_27(IniShaderFactoryFields *self) {
    if (self->f20 != 0) {
        FUN_001c6520((O_1c6520 *)self, 0);
        FUN_001c66c0((Node *)self, 0);
        IniStrRef name = FUN_001c6fa0((IniSectionNode *)self);
        if (name.p != 0) {
            SectionRef shader(0);
            shader = FUN_001cd9f0((IniShaderFactoryView *)self, name.p);
            if (shader.get() != 0) {
                IniNodeList *nodes = FUN_002da780(shader.get());
                FUN_001ccd10((IniShaderFactoryView *)self, nodes);
                FUN_002da850(shader.get(), nodes);
            }
        }
        for (int i = 0; i < FUN_00307650(self->f28); i++) {
            IniFactoryEntry *e = FUN_00307630(self->f28, i);
            if (e != 0 && e->f16 != 0 && e->f12 != 0 && FUN_0030ba90(e->f16, &text_file[0]) != 0) {
                char *path;
                if (e->f12->name == 0) path = g_stringObjEmptyText[0]; else path = e->f12->name;
                FUN_001cdbb0((IniFactoryView *)self, path);
            }
        }
    }
}

void Gap__Sg__igIniShaderFactory__vfunc_17(void *arg0) {
    Gap__Core__igObject__vfunc_15();
    if (*(int *)((char *)(arg0) + 20) != 2) {
        ((DW4VC_104_0 *)(((char *)(arg0) + 0)))->vX();
    }
}

void Gap__Sg__igIniShaderFactory__vfunc_18(void *arg0) {
    int temp_a1;

    temp_a1 = *(int *)((char *)(arg0) + 20);
    if (temp_a1 != 2) {
        ((DW4VC_104_1 *)((int *)((char *)(arg0) + 0)))->vX((int)(temp_a1));
    }
}

#define SLOT(T, x) (*(T **)&(x))
#define ADD(o) do { if (o != 0) { o->_refCount = o->_refCount + 1; } } while (0)
#define DROP(T, x) \
    do { \
        T *o_ = (x); \
        if (o_ != 0) { \
            o_->_refCount = o_->_refCount - 1; \
            if (((unsigned long long)((long long)(int)o_->_refCount << 0x29) >> 0x29) == 0) { \
                igObject_Destroy(o_); \
            } \
        } \
    } while (0)
#define SET_OUT(v) \
    do { \
        *out = (v); \
        { IniDocument *a_ = *out; ADD(a_); } \
    } while (0)
#define FINISH() \
    do { \
        DROP(IniCacheTable, cache); \
        DROP(IniDocument, parsed); \
        DROP(IniDocument, result); \
        return 0; \
    } while (0)
#define USE_CACHE(source) \
    do { \
        held = (source); \
        ADD(held); \
        DROP(IniCacheTable, cache); \
        SLOT(IniCacheTable, cache) = held; \
    } while (0)
int FUN_001cd150(IniDocument **out, IniFactoryState *self, char *name) {
    IniDocument *result;
    IniDocument *parsed;
    IniCacheTable *cache;
    IniDocument *found;
    IniDocument *path;
    IniCacheTable *held;
    SLOT(IniDocument, result) = 0;
    { IniDocument *a_ = result; ADD(a_); }
    SLOT(IniDocument, parsed) = 0;
    { IniDocument *a_ = parsed; ADD(a_); }
    SLOT(IniCacheTable, cache) = 0;
    { IniCacheTable *a_ = cache; ADD(a_); }
    if (name == 0) {
        SET_OUT(0);
        FINISH();
    }
    if (self->mode != 0) {
        if (self->mode == 3) {
            IniSourceList *source = (IniSourceList *)FUN_00309a60(((void *)g_globalContext[0]), text_system, igShaderInfo_className, 0);
            IniFieldEntry *entry;
            if (source == 0 || igObject_IsKindOf(source, ((void * *)g_igShaderInfo_metaObject)[0]) == 0) {
                SET_OUT(result);
                FINISH();
            }
            entry = ((IniFieldEntry *)FUN_003022c0(source->entries, DAT_005619b0[0], name));
            if (entry != 0) {
                USE_CACHE(entry->cache);
            } else {
                USE_CACHE(self->cache);
            }
        } else {
            USE_CACHE(self->cache);
        }
        SLOT(IniDocument, found) = ((IniDocument *)FUN_00303d70(cache, name));
        { IniDocument *a_ = found; ADD(a_); }
        if (found != 0 && igObject_IsKindOf(found, g_igRegistry_metaObject[0]) != 0) {
            IniDocument *keep = found;
            ADD(keep);
            DROP(IniDocument, parsed);
            SLOT(IniDocument, parsed) = keep;
        }
        DROP(IniDocument, found);
    }
    if (parsed == 0) {
        FUN_001ce400((IniStringObject * *)&path, name);
        if (path == 0) {
            SET_OUT(0);
            DROP(IniDocument, path);
            FINISH();
        }
        {
            void *allocator = ((void *)igObject_GetAllocator(self));
            char *text;
            IniDocument *loading;
            DROP(IniDocument, parsed);
            SLOT(IniDocument, parsed) = FUN_002baff0(allocator);
            loading = parsed;
            text = path->text;
            text = (text == 0) ? g_stringObjEmptyText[0] : text;
            if (FUN_00305d30(loading, text, DAT_004e4660) == 0) {
                SET_OUT(0);
                DROP(IniDocument, path);
                FINISH();
            }
            if (self->mode != 0) {
                FUN_00303cd0(cache, name, parsed);
            }
            DROP(IniDocument, path);
        }
    }
    if (self->mode == 0) {
        IniDocument *keep = parsed;
        ADD(keep);
        DROP(IniDocument, result);
        SLOT(IniDocument, result) = keep;
    } else {
        void *allocator = ((void *)igObject_GetAllocator(self));
        DROP(IniDocument, result);
        SLOT(IniDocument, result) = FUN_002baff0(allocator);
        FUN_003061c0(result, parsed, 1);
    }
    SET_OUT(result);
    FINISH();
}
#undef SLOT
#undef ADD
#undef DROP
#undef SET_OUT
#undef FINISH
#undef USE_CACHE

SectionRef FUN_001cd9f0(IniShaderFactoryView *self, char *name) {
    SectionRef result(0);
    igSmartPointer<IniSectionText> section = FUN_001cdbb0((IniFactoryView *)self, name);
    if (section.get() != 0) {
        void *allocator = (void *)igObject_GetAllocator(self);
        char *text;
        result.release();
        result.p = FUN_002c6750(allocator);
        FUN_003006a0(result.get(), ((IniTypeTable *)g_objectSystem[0])->meta);
        IniSectionObject *created = result.get();
        text = section.get()->text;
        text = (text == 0) ? g_stringObjEmptyText[0] : text;
        if (FUN_002da710(created, text, name) == 0) {
            result.release();
            result.p = 0;
        }
    }
    return result;
}

igSmartPointer<IniSectionText> FUN_001cdbb0(IniFactoryView *self, char *name) {
    igSmartPointer<IniSectionText> result((IniSectionText *)0, kRetainReference);
    igSmartPointer<IniNamedObject> cache((IniNamedObject *)0, kRetainReference);
    int size;
    if (name == 0) {
        return igSmartPointer<IniSectionText>((IniSectionText *)0, kRetainReference);
    }
    if (self->mode != 0) {
        IniSectionText *found;
        if (self->mode == 3) {
            IniSourceList *source = (IniSourceList *)FUN_00309a60(((void *)g_globalContext[0]), text_system, igShaderInfo_className, 0);
            IniFieldEntry_1cdbb0 *entry;
            if (source == 0 || igObject_IsKindOf(source, ((void * *)g_igShaderInfo_metaObject)[0]) == 0) {
                return igSmartPointer<IniSectionText>((IniSectionText *)0, kRetainReference);
            }
            entry = ((IniFieldEntry_1cdbb0 *)FUN_003022c0(source->entries, DAT_005619b0[0], name));
            if (entry != 0) {
                cache = entry->cache;
            } else {
                cache = self->cache;
            }
        } else {
            cache = self->cache;
        }
        found = ((IniSectionText *)FUN_00303d70(cache.p, name));
        if (found != 0 && igObject_IsKindOf(found, g_igStringObj_metaObject[0]) != 0) {
            result = found;
        }
    }
    if (result.p == 0) {
        IniStringRef path;
        FUN_001ce400(&path.p, name);
        if (path.p == 0) {
            return igSmartPointer<IniSectionText>((IniSectionText *)0, kRetainReference);
        }
        {
            void *allocator = ((void *)igObject_GetAllocator(self));
            char *text;
            char *buffer;
            IniFileHandle *opening;
            result.release();
            result.p = ((IniSectionText *)igStringObj_Create(allocator));
            igSmartPointer<IniFileHandle> file((IniFileHandle *)igFile_Create(((void *)igObject_GetAllocator(self))));
            text = path.p->text;
            opening = file.p;
            text = (text == 0) ? g_stringObjEmptyText[0] : text;
            if (opening->open(text, DAT_004e47a8) == 0) {
                return igSmartPointer<IniSectionText>((IniSectionText *)0, kRetainReference);
            }
            file.p->seek(0, 2);
            size = file.p->tell();
            file.p->seek(0, 0);
            buffer = FUN_00300d70(self, size + 1);
            file.p->read(buffer, size, 1);
            file.p->close();
            buffer[size] = 0;
            igStringObj_Set(result.p, buffer);
            FUN_00300f50(self, buffer);
            if (self->mode != 0) {
                FUN_00303cd0(cache.p, name, result.p);
            }
        }
    }
    return result;
}

