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
                    if (FUN_0030ba90(e->name, DAT_004e46e0) != 0) {
                        char *s = e->value->text;
                        IniObjectRef *ref;
                        s = (s == 0) ? DAT_004c22f0[0] : s;
                        FUN_001cdbb0((IniSectionText * *)&ref, (IniFactoryView *)self, s);
                        IG_OBJECT_RELEASE(ref);
                    }
                }
                break;
            }
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
            IniSourceList *source = (IniSourceList *)FUN_00309a60(((void *)DAT_00586dd0[0]), DAT_004fb3a8, DAT_004e1b58, 0);
            IniFieldEntry *entry;
            if (source == 0 || igObject_IsKindOf(source, ((void * *)DAT_00561500)[0]) == 0) {
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
        if (found != 0 && igObject_IsKindOf(found, DAT_00585a08[0]) != 0) {
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
            text = (text == 0) ? DAT_004c22f0[0] : text;
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
        { IniSectionText *a_ = *out; ADD(a_); } \
    } while (0)
int FUN_001cdbb0(IniSectionText **out, IniFactoryView *self, char *name) {
    IniSectionText *result;
    IniNamedObject *cache;
    IniSectionText *path;
    IniFileHandle *file;
    int size;
    SLOT(IniSectionText, result) = 0;
    { IniSectionText *a_ = result; ADD(a_); }
    SLOT(IniNamedObject, cache) = 0;
    { IniNamedObject *a_ = cache; ADD(a_); }
    if (name == 0) {
        SET_OUT(0);
        DROP(IniNamedObject, cache);
        DROP(IniSectionText, result);
        return 0;
    }
    if (self->mode != 0) {
        IniNamedObject *held;
        IniSectionText *found;
        if (self->mode == 3) {
            IniSourceList *source = (IniSourceList *)FUN_00309a60(((void *)DAT_00586dd0[0]), DAT_004fb3a8, DAT_004e1b58, 0);
            IniFieldEntry_1cdbb0 *entry;
            if (source == 0 || igObject_IsKindOf(source, ((void * *)DAT_00561500)[0]) == 0) {
                SET_OUT(0);
                DROP(IniNamedObject, cache);
                DROP(IniSectionText, result);
                return 0;
            }
            entry = ((IniFieldEntry_1cdbb0 *)FUN_003022c0(source->entries, DAT_005619b0[0], name));
            if (entry != 0) {
                held = entry->cache;
                ADD(held);
                DROP(IniNamedObject, cache);
                SLOT(IniNamedObject, cache) = held;
            } else {
                held = self->cache;
                ADD(held);
                DROP(IniNamedObject, cache);
                SLOT(IniNamedObject, cache) = held;
            }
        } else {
            held = self->cache;
            ADD(held);
            DROP(IniNamedObject, cache);
            SLOT(IniNamedObject, cache) = held;
        }
        found = ((IniSectionText *)FUN_00303d70(cache, name));
        if (found != 0 && igObject_IsKindOf(found, DAT_005858f0[0]) != 0) {
            ADD(found);
            DROP(IniSectionText, result);
            SLOT(IniSectionText, result) = found;
        }
    }
    if (result == 0) {
        FUN_001ce400((IniStringObject * *)&path, name);
        if (path == 0) {
            SET_OUT(0);
            DROP(IniSectionText, path);
            DROP(IniNamedObject, cache);
            DROP(IniSectionText, result);
            return 0;
        }
        {
            void *allocator = ((void *)igObject_GetAllocator(self));
            char *text;
            char *buffer;
            IniFileHandle *opening;
            DROP(IniSectionText, result);
            SLOT(IniSectionText, result) = ((IniSectionText *)FUN_002b9500(allocator));
            SLOT(IniFileHandle, file) = ((IniFileHandle *)FUN_002c4ca0(((void *)igObject_GetAllocator(self))));
            text = path->text;
            opening = file;
            text = (text == 0) ? DAT_004c22f0[0] : text;
            if (opening->open(text, DAT_004e47a8) == 0) {
                SET_OUT(0);
                DROP(IniFileHandle, file);
                DROP(IniSectionText, path);
                DROP(IniNamedObject, cache);
                DROP(IniSectionText, result);
                return 0;
            }
            file->seek(0, 2);
            size = file->tell();
            file->seek(0, 0);
            buffer = FUN_00300d70(self, size + 1);
            file->read(buffer, size, 1);
            file->close();
            buffer[size] = 0;
            FUN_0030b3c0(result, buffer);
            FUN_00300f50(self, buffer);
            if (self->mode != 0) {
                FUN_00303cd0(cache, name, result);
            }
            DROP(IniFileHandle, file);
            DROP(IniSectionText, path);
        }
    }
    SET_OUT(result);
    DROP(IniNamedObject, cache);
    DROP(IniSectionText, result);
    return 0;
}
#undef SLOT
#undef ADD
#undef DROP
#undef SET_OUT

struct R **FUN_001ce350(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

