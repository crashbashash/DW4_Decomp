void FUN_001d8ab0(void) {
    FUN_00199080();
    igSmartPointer<igObject> info((igObject *)FUN_00198cc0(Memory_GetAllocatorBySelector(DAT_00587038[0])));
    igNamedObject_SetName(info.p, &text_shaderInfo[0]);
    igSmartPointer<igObject> list = FUN_003087a0(g_globalContext[0], (const char *)text_system);
    FUN_002d8310(list.p, info.p);
}

void FUN_001d8b90(void) {
    igSmartPointer<igObject> list = FUN_003087a0(g_globalContext[0], (const char *)text_system);
    FUN_002d81f0(list.p, &text_shaderInfo[0]);
}

int Gap__Sg__igShaderInfo__vfunc_23(ShaderFieldTable *self, int arg1, ShaderFieldRecord *key) {
    igTDataList<ShaderFieldRecord *> *list = self->list;
    int idx = list->find(key);
    ShaderFieldRecord *e;
    int *name;
    if (idx == -1) {
        return 0;
    }
    e = self->list->_data[idx];
    if (e->kind == 2) {
        return 0;
    }
    name = e->name;
    name = name != 0 ? name : &emptyString[0];
    FUN_002e2d30(arg1, self, name, key, idx, list, self);
    return 1;
}

int Gap__Sg__igShaderInfo__vfunc_24(struct S1d *arg0, int *arg1) {
    int r = igProperty_FindByName(arg0->f20, g_propertyNameField[0], arg1);
    if (r != 0) {
        return r;
    }
    return igProperty_FindByName(arg0->f20, g_propertyNameField[0], &text_empty[0]);
}

