int igStringRefList_IndexOf(igStringRefList *list, char *const *key, int arg2) {
    struct L_1cafc0 *arg0 = (struct L_1cafc0 *)list;
    int n = arg0->n;
    int i = arg2;
    int r;
    while (i < n) {
        if ((int)*key == arg0->items[i]) { r = i; goto done; }
        i++;
    }
    r = -1;
done:
    return r;
}

void FUN_001cb010(void *self, IniValueTarget *target, IniValueList *list) {
    int i;
    IniValueObject *value;
    char *s;
    igSmartPointer<IniValueObject> text(((IniValueObject *)igStringObj_Create((int)(((void *)((Gap::Core::igObject *)self)->getMemoryPool())))));
    for (i = 0; i < igObjectStringMap_GetCount(list); i++) {
        value = (IniValueObject *)igObjectStringMap_GetObjectAt(list, i);
        if (((Gap::Core::igObject *)value)->isOfType(igIntObject_GetMetaObject()) != 0) {
            igStringObj_SetInt((int)text.p, value->value.i, "%d");
            s = text.p->value.s;
            s = (s == 0) ? g_stringObjEmptyText : s;
            igDriverDatabase_SetSubPropertyValue((igDriverDatabase *)target, 10, (const char *)igObjectStringMap_GetNameAt(list, i), s);
        } else if (((Gap::Core::igObject *)value)->isOfType(igFloatObject_GetMetaObject()) != 0) {
            igStringObj_SetFloat((int)text.p, "%f", value->value.f);
            s = text.p->value.s;
            s = (s == 0) ? g_stringObjEmptyText : s;
            igDriverDatabase_SetSubPropertyValue((igDriverDatabase *)target, 11, (const char *)igObjectStringMap_GetNameAt(list, i), s);
        } else if (((Gap::Core::igObject *)value)->isOfType(igBoolObject_GetMetaObject()) != 0) {
            igStringObj_SetBool((int)text.p, value->value.b, 0);
            s = text.p->value.s;
            s = (s == 0) ? g_stringObjEmptyText : s;
            igDriverDatabase_SetSubPropertyValue((igDriverDatabase *)target, 12, (const char *)igObjectStringMap_GetNameAt(list, i), s);
        }
    }
}

void FUN_001cb1f0(void *self, char *name, int ini, int section, DW4VC_96_1 *target, IniValueList *values) {
    SectionRef found = FUN_001cd9f0((IniShaderFactoryView *)self, name);
    if (found.get() != 0) {
        target->vX((int)(found.get()));
        FUN_001cb010(self, (IniValueTarget *)found.get(), values);
        igDriverDatabase_ApplyToRegistry((igDriverDatabase *)(found.get()), ini, section, 1);
    }
}

void FUN_001cb2d0(void *self, void *types, const char *key, void *target) {
    int index;

    index = igObjectStringMap_GetIndexByName((igObjectStringMap *)types, (const char *)key);
    if (index != -1) {
        igObjectStringMap_RemoveAt((igObjectStringMap *)types, index);
    }
    igObjectStringMap_Add((igObjectStringMap *)types, (const char *)key, (void *)(*(int *)((char *)(target) + 28)));
}

static inline ShaderObject_1ca6c0 *asMaterial(ShaderObject_1ca6c0 *o) {
    if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(Gap::Attrs::igAttrList::getClassMeta()) != 0) {
        return o;
    }
    return 0;
}

static inline ShaderObject_1ca6c0 *asTexture(ShaderObject_1ca6c0 *o) {
    if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(Gap::Sg::igNodeList::getClassMeta()) != 0) {
        return o;
    }
    return 0;
}

static inline char *textOf(ShaderStringObject *o) {
    char *t = o->text;
    return (t == 0) ? g_stringObjEmptyText : t;
}

/* Drops the first string of the list: one release balances the copy, the other drops the list's
 * own reference before the slot is removed. */
static inline void removeFirst(ShaderNameList *list) {
    {
        igStringRef removed = StringList_CopyRetained((igStringRefList *)list, 0);
        releaseString(removed.p);
    }
    List_RemoveWordAt((igDataList *)list, 0);
    list->data[list->count] = 0;
}

int FUN_001cb340(ShaderProcessorView *self, ShaderTarget *target, int arg) {
    unsigned char flag;
    ShaderPassList *passes;
    int i;
    int infoSection;
    int count;
    char *passName;
    int pass;
    ShaderObject_1ca6c0 *held;
    int section;
    passes = target->passes;
    passes->prepare();
    target->clear();
    section = ((Gap::Core::igRegistry *)self->ini)->findSection((char *)"configuration", 0);
    if (section == -1) {
        return 0;
    }
    IniStrRef baseName = FUN_001c6fa0((IniSectionNode *)self);
    if (baseName.p != 0) {
        FUN_001cb1f0(self, baseName.p, self->ini, section, (DW4VC_96_1 *)arg, (IniValueList *)self->info->types);
    }
    FUN_001cb2d0(self, self->info->types, "shader_childList", target);
    IniStrRef defaultName((char *)0);
    if ((unsigned char)((Gap::Core::igRegistry *)self->ini)->getValue(section, "implementation", *(igStringRef *)(&defaultName.p), "", 0) == 0) {
        return 0;
    }
    section = ((Gap::Core::igRegistry *)self->ini)->findSection(defaultName.p, 0);
    if (section == -1) {
        return 0;
    }
    igSmartPointer<ShaderNameList> names((ShaderNameList *)igStringRefList_Create((int)((void *)((Gap::Core::igObject *)self)->getMemoryPool())));
    if (((Gap::Core::igRegistry *)self->ini)->getValue(section, "passes", (igStringRefList *)names.p, 0) == 0) {
        return 0;
    }
    IniStrRef infoName((char *)0);
    igSmartPointer<ShaderObject_1ca6c0> info;
    igSmartPointer<ShaderNameList> keys((ShaderNameList *)igStringRefList_Create((int)((void *)((Gap::Core::igObject *)self)->getMemoryPool())));
    igSmartPointer<ShaderNameList> values((ShaderNameList *)igStringRefList_Create((int)((void *)((Gap::Core::igObject *)self)->getMemoryPool())));
    count = names.p->count;
    if ((unsigned char)((Gap::Core::igRegistry *)self->ini)->getValue(section, "processor", *(igStringRef *)(&infoName.p), "", 0) != 0) {
        infoSection = ((Gap::Core::igRegistry *)self->ini)->findSection(infoName.p, 0);
        info = igSmartPointer<ShaderObject_1ca6c0>(FUN_001ca6c0(self, infoName.p, 1));
        igSmartPointer<ShaderNameList> pending((ShaderNameList *)igStringRefList_Create((int)((void *)((Gap::Core::igObject *)self)->getMemoryPool())));
        ((Gap::Core::igRegistry *)self->ini)->getValue(infoSection, "fields", (igStringRefList *)pending.p, 0);
        igSmartPointer<ShaderStringObject> value((ShaderStringObject *)igStringObj_Create((int)((void *)((Gap::Core::igObject *)self)->getMemoryPool())));
        igSmartPointer<ShaderStringObject> key((ShaderStringObject *)igStringObj_Create((int)((void *)((Gap::Core::igObject *)self)->getMemoryPool())));
        while (pending.p->count != 0) {
            int ok;
            igStringObj_Set((igStringObj *)key.p, FUN_001ccb20((igStringRefList *)pending.p).p);
            {
                ShaderStringObject *k = key.p;
                int length = k->length;
                igStringObj_Insert((igStringObj *)k, ".value", length, strlen(".value"));
            }
            igStringObj_Set((igStringObj *)value.p, "");
            {
                char *t = key.p->text;
                int ini = self->ini;
                t = (t == 0) ? g_stringObjEmptyText : t;
                ok = (unsigned char)((Gap::Core::igRegistry *)ini)->getValue(infoSection, t, *(igStringObjRef *)&value, "", 0);
            }
            if (ok == 0) {
                igStringObj_Set((igStringObj *)key.p, FUN_001ccb20((igStringRefList *)pending.p).p);
                {
                    ShaderStringObject *k = key.p;
                    int length = k->length;
                    igStringObj_Insert((igStringObj *)k, ".function", length, strlen(".function"));
                }
                igStringObj_Set((igStringObj *)value.p, "");
                {
                    char *t = key.p->text;
                    int ini = self->ini;
                    t = (t == 0) ? g_stringObjEmptyText : t;
                    ok = (unsigned char)((Gap::Core::igRegistry *)ini)->getValue(infoSection, t, *(igStringObjRef *)&value, "", 0);
                }
            }
            if (ok != 0) {
                char *text = textOf(value.p);
                char *interned;
                if (text == 0) {
                    interned = 0;
                } else {
                    if (g_stringPool == 0) {
                        int pool = (int)StringPool_Allocate(16);
                        if (pool != 0) {
                            pool = (int)StringPool_Construct((StringPool *)pool);
                        }
                        g_stringPool = (StringPool *)pool;
                    }
                    interned = (char *)StringPool_Intern(g_stringPool, text);
                }
                StringList_AppendRetained((igStringRefList *)keys.p, IniStrRef(interned).ref());
                StringList_AppendRetained((igStringRefList *)values.p, FUN_001ccb20((igStringRefList *)pending.p).ref());
            }
            removeFirst(pending.p);
        }
    }
    if (info.p == 0) {
        int owner = self->allocatorKey;
        info.release();
        info.p = (ShaderObject_1ca6c0 *)Gap::Sg::igShaderProcessor::_instantiateFromPool((igMemoryPoolView *)owner);
    }
    flag = 0;
    if (((Gap::Core::igRegistry *)self->ini)->getValue(section, "useRenderPackage", flag, 0, 0)) {
        target->setFlag(flag);
    }
    target->setInfo(info.p);
    passes->setCount(count);
    igSmartPointer<ShaderNameList> shared((ShaderNameList *)igStringRefList_Create((int)((void *)((Gap::Core::igObject *)self)->getMemoryPool())));
    for (i = 0; i < count; i++) {
        FUN_001d9090((SkeletonBitOwnerView *)target, i, 1);
        passName = StringList_CopyRetained((igStringRefList *)names.p, i).p;
        pass = ((Gap::Core::igRegistry *)self->ini)->findSection(passName, 0);
        if (pass == -1) {
            return 0;
        }
        igSmartPointer<ShaderObject_1ca6c0> primary((ShaderObject_1ca6c0 *)0, kRetainReference);
        igSmartPointer<ShaderObject_1ca6c0> second((ShaderObject_1ca6c0 *)0, kRetainReference);
        igSmartPointer<ShaderObject_1ca6c0> third((ShaderObject_1ca6c0 *)0, kRetainReference);
        igSmartPointer<igObject> found((igObject *)0, kRetainReference);
        found = FUN_001c8c80(self, pass, "pushAttrs", Gap::Attrs::igAttrList::getClassMeta(), shared.p);
        held = (ShaderObject_1ca6c0 *)found.p;
        if (held != 0) {
            primary = asMaterial(held);
            FUN_001cade0(self, (IniFieldTarget *)info.p, (IniItemList *)primary.p, shared.p, keys.p, values.p);
            found = FUN_001c8c80(self, pass, "popAttrs", Gap::Attrs::igAttrList::getClassMeta(), shared.p);
            held = (ShaderObject_1ca6c0 *)found.get();
            if (held == 0) {
                return 0;
            }
            second = asMaterial(held);
            FUN_001cade0(self, (IniFieldTarget *)info.p, (IniItemList *)second.p, shared.p, keys.p, values.p);
        } else {
            found = FUN_001c8c80(self, pass, "attrs", Gap::Attrs::igAttrList::getClassMeta(), shared.p);
            held = (ShaderObject_1ca6c0 *)found.get();
            if (held == 0) {
                return 0;
            }
            primary = asMaterial(held);
            second = primary.p;
            FUN_001cade0(self, (IniFieldTarget *)info.p, (IniItemList *)primary.p, shared.p, keys.p, values.p);
        }
        found = FUN_001c8c80(self, pass, "childNodes", (void *)Gap::Sg::igNodeList::getClassMeta(), shared.p);
        held = (ShaderObject_1ca6c0 *)found.p;
        if (held != 0) {
            third = asTexture(held);
            FUN_001cade0(self, (IniFieldTarget *)info.p, (IniItemList *)third.p, shared.p, keys.p, values.p);
        }
        ((Gap::Sg::igShaderData *)passes)->setPushList(i, (Gap::Attrs::igAttrList *)primary.p);
        ((Gap::Sg::igShaderData *)passes)->setPopList(i, (Gap::Attrs::igAttrList *)second.p);
        ((Gap::Sg::igShaderData *)passes)->setChildList(i, (Gap::Sg::igNodeList *)third.p);
    }
    return 1;
}

IniStrRef FUN_001ccb20(igStringRefList *list) {
    return ((IniStrRef *)list->_data)[0];
}

