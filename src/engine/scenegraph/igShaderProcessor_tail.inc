igMetaObject *Gap__Sg__igShaderProcessor__vfunc_22(void) {
    return g_igShaderProcessor_metaObject[0];
}

int FUN_001cafc0(struct L_1cafc0 *arg0, IniStrRef name, int arg2) {
    int n = arg0->n;
    int i = arg2;
    int r;
    while (i < n) {
        if ((int)name.p == arg0->items[i]) { r = i; goto done; }
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
    igSmartPointer<IniValueObject> text(((IniValueObject *)igStringObj_Create(((void *)igObject_GetAllocator(self)))));
    for (i = 0; i < FUN_00303e50(list); i++) {
        value = FUN_00303e60(list, i);
        if (igObject_IsKindOf(value, FUN_001e4e30()) != 0) {
            FUN_0030b720(text.p, value->value.i, DAT_004e4710);
            s = text.p->value.s;
            s = (s == 0) ? g_stringObjEmptyText[0] : s;
            FUN_002d9740(target, 10, FUN_00303e80(list, i), s);
        } else if (igObject_IsKindOf(value, FUN_001e4fc0()) != 0) {
            FUN_0030b730(text.p, DAT_004e4718, value->value.f);
            s = text.p->value.s;
            s = (s == 0) ? g_stringObjEmptyText[0] : s;
            FUN_002d9740(target, 11, FUN_00303e80(list, i), s);
        } else if (igObject_IsKindOf(value, FUN_001e5c50()) != 0) {
            FUN_0030b770(text.p, value->value.b, 0);
            s = text.p->value.s;
            s = (s == 0) ? g_stringObjEmptyText[0] : s;
            FUN_002d9740(target, 12, FUN_00303e80(list, i), s);
        }
    }
}

void FUN_001cb1f0(void *self, char *name, int ini, int section, DW4VC_96_1 *target, IniValueList *values) {
    SectionRef found = FUN_001cd9f0((IniShaderFactoryView *)self, name);
    if (found.get() != 0) {
        target->vX((int)(found.get()));
        FUN_001cb010(self, (IniValueTarget *)found.get(), values);
        FUN_002da990(found.get(), ini, section, 1);
    }
}

void FUN_001cb2d0(void *self, void *types, void *key, void *target) {
    int index;

    index = FUN_00303dc0(types, key);
    if (index != -1) {
        FUN_00304030(types, index);
    }
    FUN_00303cd0(types, key, *(int *)((char *)(target) + 28));
}

static inline ShaderObject_1ca6c0 *asMaterial(ShaderObject_1ca6c0 *o) {
    if (o != 0 && igObject_IsKindOf(o, g_igAttrList_metaObject[0]) != 0) {
        return o;
    }
    return 0;
}

static inline ShaderObject_1ca6c0 *asTexture(ShaderObject_1ca6c0 *o) {
    if (o != 0 && igObject_IsKindOf(o, g_igNodeList_metaObject[0]) != 0) {
        return o;
    }
    return 0;
}

static inline char *textOf(ShaderStringObject *o) {
    char *t = o->text;
    return (t == 0) ? g_stringObjEmptyText[0] : t;
}

/* Drops the first string of the list: one release balances the copy, the other drops the list's
 * own reference before the slot is removed. */
static inline void removeFirst(ShaderNameList *list) {
    RetainedString removed = StringList_CopyRetained((igStringRefList *)list, 0);
    releaseString(removed.p);
    releaseString(removed.p);
    List_RemoveWordAt(list, 0);
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
    section = FUN_00306360(self->ini, (char *)text_configuration, 0);
    if (section == -1) {
        return 0;
    }
    IniStrRef baseName = FUN_001c6fa0((IniSectionNode *)self);
    if (baseName.p != 0) {
        FUN_001cb1f0(self, baseName.p, self->ini, section, (DW4VC_96_1 *)arg, (IniValueList *)self->info->types);
    }
    FUN_001cb2d0(self, self->info->types, text_shader_childList, target);
    IniStrRef defaultName((char *)0);
    if (FUN_00306910(self->ini, section, text_implementation, &defaultName.p, DAT_004e4660, 0) == 0) {
        return 0;
    }
    section = FUN_00306360(self->ini, defaultName.p, 0);
    if (section == -1) {
        return 0;
    }
    igSmartPointer<ShaderNameList> names(igStringRefList_Create((void *)igObject_GetAllocator(self)));
    if (FUN_00306aa0(self->ini, section, text_passes, names.p, 0) == 0) {
        return 0;
    }
    IniStrRef infoName((char *)0);
    igSmartPointer<ShaderObject_1ca6c0> info;
    igSmartPointer<ShaderNameList> keys(igStringRefList_Create((void *)igObject_GetAllocator(self)));
    igSmartPointer<ShaderNameList> values(igStringRefList_Create((void *)igObject_GetAllocator(self)));
    count = names.p->count;
    if (FUN_00306910(self->ini, section, text_processor, &infoName.p, DAT_004e4660, 0) != 0) {
        infoSection = FUN_00306360(self->ini, infoName.p, 0);
        info = igSmartPointer<ShaderObject_1ca6c0>(FUN_001ca6c0(self, infoName.p, 1));
        igSmartPointer<ShaderNameList> pending(igStringRefList_Create((void *)igObject_GetAllocator(self)));
        FUN_00306aa0(self->ini, infoSection, text_fields, pending.p, 0);
        igSmartPointer<ShaderStringObject> value((ShaderStringObject *)igStringObj_Create((void *)igObject_GetAllocator(self)));
        igSmartPointer<ShaderStringObject> key((ShaderStringObject *)igStringObj_Create((void *)igObject_GetAllocator(self)));
        while (pending.p->count != 0) {
            int ok;
            igStringObj_Set(key.p, FUN_001ccb20((igStringRefList *)pending.p).p);
            {
                ShaderStringObject *k = key.p;
                int length = k->length;
                igStringObj_Insert(k, text_value, length, strlen(text_value));
            }
            igStringObj_Set(value.p, DAT_004e4660);
            {
                char *t = key.p->text;
                int ini = self->ini;
                t = (t == 0) ? g_stringObjEmptyText[0] : t;
                ok = FUN_00306770(ini, infoSection, t, &value, DAT_004e4660, 0);
            }
            if (ok == 0) {
                igStringObj_Set(key.p, FUN_001ccb20((igStringRefList *)pending.p).p);
                {
                    ShaderStringObject *k = key.p;
                    int length = k->length;
                    igStringObj_Insert(k, text_function, length, strlen(text_function));
                }
                igStringObj_Set(value.p, DAT_004e4660);
                {
                    char *t = key.p->text;
                    int ini = self->ini;
                    t = (t == 0) ? g_stringObjEmptyText[0] : t;
                    ok = FUN_00306770(ini, infoSection, t, &value, DAT_004e4660, 0);
                }
            }
            if (ok != 0) {
                char *text = textOf(value.p);
                char *interned;
                if (text == 0) {
                    interned = 0;
                } else {
                    if (g_stringPool[0] == 0) {
                        int pool = StringPool_Allocate(16);
                        if (pool != 0) {
                            pool = StringPool_Construct(pool);
                        }
                        g_stringPool[0] = pool;
                    }
                    interned = (char *)StringPool_Intern(g_stringPool[0], text);
                }
                StringList_AppendRetained((igStringRefList *)keys.p, IniStrRef(interned));
                StringList_AppendRetained((igStringRefList *)values.p, FUN_001ccb20((igStringRefList *)pending.p));
            }
            removeFirst(pending.p);
        }
    }
    if (info.p == 0) {
        int owner = self->allocatorKey;
        info.release();
        info.p = (ShaderObject_1ca6c0 *)FUN_00198b60(owner);
    }
    flag = 0;
    if (FUN_00306e50(self->ini, section, text_useRenderPackage, &flag, 0, 0) != 0) {
        target->setFlag(flag);
    }
    target->setInfo(info.p);
    passes->setCount(count);
    igSmartPointer<ShaderNameList> shared(igStringRefList_Create((void *)igObject_GetAllocator(self)));
    for (i = 0; i < count; i++) {
        FUN_001d9090((SkeletonBitOwnerView *)target, i, 1);
        passName = StringList_CopyRetained((igStringRefList *)names.p, i).p;
        releaseString(passName);
        pass = FUN_00306360(self->ini, passName, 0);
        if (pass == -1) {
            return 0;
        }
        igSmartPointer<ShaderObject_1ca6c0> primary((ShaderObject_1ca6c0 *)0, kRetainReference);
        igSmartPointer<ShaderObject_1ca6c0> second((ShaderObject_1ca6c0 *)0, kRetainReference);
        igSmartPointer<ShaderObject_1ca6c0> third((ShaderObject_1ca6c0 *)0, kRetainReference);
        igSmartPointer<igObject> found((igObject *)0, kRetainReference);
        found = FUN_001c8c80(self, pass, text_pushAttrs, g_igAttrList_metaObject[0], shared.p);
        held = (ShaderObject_1ca6c0 *)found.p;
        if (held != 0) {
            primary = asMaterial(held);
            FUN_001cade0(self, (IniFieldTarget *)info.p, (IniItemList *)primary.p, shared.p, keys.p, values.p);
            found = FUN_001c8c80(self, pass, text_popAttrs, g_igAttrList_metaObject[0], shared.p);
            held = (ShaderObject_1ca6c0 *)found.get();
            if (held == 0) {
                return 0;
            }
            second = asMaterial(held);
            FUN_001cade0(self, (IniFieldTarget *)info.p, (IniItemList *)second.p, shared.p, keys.p, values.p);
        } else {
            found = FUN_001c8c80(self, pass, text_attrs, g_igAttrList_metaObject[0], shared.p);
            held = (ShaderObject_1ca6c0 *)found.get();
            if (held == 0) {
                return 0;
            }
            primary = asMaterial(held);
            second = primary.p;
            FUN_001cade0(self, (IniFieldTarget *)info.p, (IniItemList *)primary.p, shared.p, keys.p, values.p);
        }
        found = FUN_001c8c80(self, pass, text_childNodes, (void *)g_igNodeList_metaObject[0], shared.p);
        held = (ShaderObject_1ca6c0 *)found.p;
        if (held != 0) {
            third = asTexture(held);
            FUN_001cade0(self, (IniFieldTarget *)info.p, (IniItemList *)third.p, shared.p, keys.p, values.p);
        }
        FUN_001d86f0((S_1d86f0 *)passes, i, primary.p);
        FUN_001d87b0((igTransformSequence *)passes, i, second.p);
        FUN_001d8870((A_1d8870 *)passes, i, third.p);
    }
    return 1;
}

IniStrRef FUN_001ccb20(igStringRefList *list) {
    return ((IniStrRef *)list->_data)[0];
}

