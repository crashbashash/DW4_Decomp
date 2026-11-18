void FUN_001d8ab0(void) {
    igShaderFactoryList_EnsureRegistered();
    igSmartPointer<igObject> info((igObject *)FUN_00198cc0((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)));
    igNamedObject_SetName((igNamedObject *)info.p, "shaderInfo");
    igSmartPointer<igObject> list = igResource_GetDirectory(g_globalContext, (const char *)text_system);
    igDirectory_AddInfo(list.p, info.p);
}

void FUN_001d8b90(void) {
    igSmartPointer<igObject> list = igResource_GetDirectory(g_globalContext, (const char *)text_system);
    igDirectory_RemoveInfoByName(list.p, (int)("shaderInfo"));
}

int igShaderInfo_FindObjectReference(ShaderFieldTable *self, int arg1, ShaderFieldRecord *key) {
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
    name = name != 0 ? name : (int *)emptyString;
    igDirectory_AddExternalInfoRef((igDirectoryView *)arg1, (igInfoView *)self, (char *)name, (igObject *)key);
    return 1;
}

int Gap__Sg__igShaderInfo__vfunc_24(struct S1d *arg0, int *arg1) {
    int r = igProperty_FindByName((igObjectList *)arg0->f20, g_propertyNameField, (const char *)arg1);
    if (r != 0) {
        return r;
    }
    return igProperty_FindByName((igObjectList *)arg0->f20, g_propertyNameField, "empty");
}

