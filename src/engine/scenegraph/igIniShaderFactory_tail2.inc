#define REL(p) { IniHeldObject *o = (p); if(o){ --(o)->refs; if((((unsigned long long)(long long)(o)->refs)&0x7fffffULL)==0) igObject_Destroy((igObject *)o);}}
#define ADD(o) if(o){ ++(o)->refs; }
bool igIniShaderFactory_ConfigureShader(IniFactoryBinding *self, int a1, IniHeldObject *a2, int a3) {
    unsigned char ok = 1;
    if (FUN_001c6520((O_1c6520 *)self, 1) != 0) {
        IniHeldObject *n;
        ADD(a2);
        REL(self->r48);
        self->r48 = a2;
        n = (IniHeldObject *)((Gap::Core::igObject *)a1)->getMemoryPool();
        ADD(n);
        REL(self->r44);
        self->r44 = n;
        ok = !FUN_001cb340((ShaderProcessorView *)self, (ShaderTarget *)a1, a3);
    }
    if (ok) igShaderFactory_ConfigureShader(self, (VA_1d8980 *)a1, a2, a3);
    REL(self->r48);
    self->r48 = 0;
    REL(self->r44);
    self->r44 = 0;
    return !ok;
}
#undef REL
#undef ADD

void igIniShaderFactory_ResetFileCache(int a0) {
    igObjectStringMap_Clear((igObjectStringMap *)(*(int *)((char *)a0 + 56)));
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
                    if (igStringObj_HasFileExtension((igStringObj *)e->name, ".file") != 0) {
                        char *s = e->value->text;
                        s = (s == 0) ? g_stringObjEmptyText : s;
                        FUN_001cdbb0((IniFactoryView *)self, s);
                    }
                }
                break;
            }
            }
        }
    }
}

void igIniShaderFactory_PreloadFileCache(IniShaderFactoryFields *self) {
    if (self->f20 != 0) {
        FUN_001c6520((O_1c6520 *)self, 0);
        FUN_001c66c0((Node *)self, 0);
        IniStrRef name = FUN_001c6fa0((IniSectionNode *)self);
        if (name.p != 0) {
            SectionRef shader(0);
            shader = FUN_001cd9f0((IniShaderFactoryView *)self, name.p);
            if (shader.get() != 0) {
                IniNodeList *nodes = (IniNodeList *)igDriverDatabase_ParseDatabase((igDriverDatabase *)shader.get());
                FUN_001ccd10((IniShaderFactoryView *)self, nodes);
                igDriverDatabase_DeleteConfigNodeList(shader.get(), (igTDataList<ConfigNode *> *)nodes);
            }
        }
        for (int i = 0; i < ((Gap::Core::igRegistry *)self->f28)->getRawValueCount(); i++) {
            IniFactoryEntry *e = (IniFactoryEntry *)((Gap::Core::igRegistry *)self->f28)->getRawValue(i);
            if (e != 0 && e->f16 != 0 && e->f12 != 0 && igStringObj_HasFileExtension((igStringObj *)e->f16, ".file") != 0) {
                char *path;
                if (e->f12->name == 0) path = g_stringObjEmptyText; else path = e->f12->name;
                FUN_001cdbb0((IniFactoryView *)self, path);
            }
        }
    }
}

void igIniShaderFactory_UserPostLoad(igIniShaderFactory *self) {
    igObject_UserPostLoad();
    if (self->_fileCachingMode != 2) {
        ((DW4VC_104_0 *)(((char *)(self) + 0)))->vX();
    }
}

void igIniShaderFactory_TrimCapacity(igIniShaderFactory *self) {
    int temp_a1;

    temp_a1 = self->_fileCachingMode;
    if (temp_a1 != 2) {
        ((DW4VC_104_1 *)((int *)((char *)(self) + 0)))->vX((int)(temp_a1));
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
                igObject_Destroy((igObject *)o_); \
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
            IniSourceList *source = (IniSourceList *)igDirectory_GetNthObjectOfType((igResource *)g_globalContext, (const char *)text_system, "igShaderInfo", 0);
            IniFieldEntry *entry;
            if (source == 0 || ((Gap::Core::igObject *)source)->isOfType(g_igShaderInfo_metaObject) == 0) {
                SET_OUT(result);
                FINISH();
            }
            entry = ((IniFieldEntry *)((Gap::Core::igObjectList *)source->entries)->search((Gap::Core::igStringMetaField *)g_igIniShaderFactory_implementationNameMetaField, name));
            if (entry != 0) {
                USE_CACHE(entry->cache);
            } else {
                USE_CACHE(self->cache);
            }
        } else {
            USE_CACHE(self->cache);
        }
        SLOT(IniDocument, found) = ((IniDocument *)igObjectStringMap_GetObject(cache, (const char *)name));
        { IniDocument *a_ = found; ADD(a_); }
        if (found != 0 && ((Gap::Core::igObject *)found)->isOfType(Gap::Core::igRegistry::getClassMeta()) != 0) {
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
            void *allocator = ((void *)((Gap::Core::igObject *)self)->getMemoryPool());
            char *text;
            IniDocument *loading;
            DROP(IniDocument, parsed);
            SLOT(IniDocument, parsed) = (IniDocument *)Gap::Core::igRegistry::_instantiateFromPool((igMemoryPoolView *)allocator);
            loading = parsed;
            text = path->text;
            text = (text == 0) ? g_stringObjEmptyText : text;
            if (!((Gap::Core::igRegistry *)loading)->load(text, "")) {
                SET_OUT(0);
                DROP(IniDocument, path);
                FINISH();
            }
            if (self->mode != 0) {
                igObjectStringMap_Add((igObjectStringMap *)cache, (const char *)name, parsed);
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
        void *allocator = ((void *)((Gap::Core::igObject *)self)->getMemoryPool());
        DROP(IniDocument, result);
        SLOT(IniDocument, result) = (IniDocument *)Gap::Core::igRegistry::_instantiateFromPool((igMemoryPoolView *)allocator);
        ((Gap::Core::igRegistry *)result)->merge((Gap::Core::igRegistry *)parsed, 1);
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
        void *allocator = (void *)((Gap::Core::igObject *)self)->getMemoryPool();
        char *text;
        result.release();
        result.p = (IniSectionObject *)igDriverDatabase_Create((int)allocator);
        ((Gap::Core::igObject *)(result.get()))->copyDeep((Gap::Core::igObject *)(((IniTypeTable *)g_objectSystem)->meta));
        IniSectionObject *created = result.get();
        text = section.get()->text;
        text = (text == 0) ? g_stringObjEmptyText : text;
        if (igDriverDatabase_LoadFromFile(created, (int)text, (int)name) == 0) {
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
            IniSourceList *source = (IniSourceList *)igDirectory_GetNthObjectOfType((igResource *)g_globalContext, (const char *)text_system, "igShaderInfo", 0);
            IniFieldEntry_1cdbb0 *entry;
            if (source == 0 || ((Gap::Core::igObject *)source)->isOfType(g_igShaderInfo_metaObject) == 0) {
                return igSmartPointer<IniSectionText>((IniSectionText *)0, kRetainReference);
            }
            entry = ((IniFieldEntry_1cdbb0 *)((Gap::Core::igObjectList *)source->entries)->search((Gap::Core::igStringMetaField *)g_igIniShaderFactory_implementationNameMetaField, name));
            if (entry != 0) {
                cache = entry->cache;
            } else {
                cache = self->cache;
            }
        } else {
            cache = self->cache;
        }
        found = ((IniSectionText *)igObjectStringMap_GetObject(cache.p, (const char *)name));
        if (found != 0 && ((Gap::Core::igObject *)found)->isOfType(g_igStringObj_metaObject) != 0) {
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
            void *allocator = ((void *)((Gap::Core::igObject *)self)->getMemoryPool());
            char *text;
            char *buffer;
            IniFileHandle *opening;
            result.release();
            result.p = ((IniSectionText *)igStringObj_Create((int)allocator));
            igSmartPointer<IniFileHandle> file((IniFileHandle *)igFile_Create((int)((Gap::Core::igObject *)self)->getMemoryPool()));
            text = path.p->text;
            opening = file.p;
            text = (text == 0) ? g_stringObjEmptyText : text;
            if (opening->open(text, "rb") == 0) {
                return igSmartPointer<IniSectionText>((IniSectionText *)0, kRetainReference);
            }
            file.p->seek(0, 2);
            size = file.p->tell();
            file.p->seek(0, 0);
            buffer = (char *)((Gap::Core::igObject *)self)->malloc(size + 1);
            file.p->read(buffer, size, 1);
            file.p->close();
            buffer[size] = 0;
            igStringObj_Set((igStringObj *)result.p, buffer);
            ((Gap::Core::igObject *)self)->free(buffer);
            if (self->mode != 0) {
                igObjectStringMap_Add((igObjectStringMap *)cache.p, (const char *)name, result.p);
            }
        }
    }
    return result;
}

