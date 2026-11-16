int igCharMetaField_ValueFromString(void *self, char *value, int text) {
    int consumed;
    int parsed;
    int t;
    consumed = 0;
    parsed = 0;
    sscanf((const char *)text,"%d%n", &parsed, &consumed);
    t = parsed;
    *value = t;
    return consumed;
}

void igCharMetaField_ValueToString(int *out, int self, char *value) {
    char buffer[1024];
    int pool;
    int interned;

    sprintf(buffer, (const char *)&percent_d_7[0], *value);
    if (buffer == 0) {
        interned = 0;
    } else {
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = (StringPool *)pool;
        }
        interned = (int)StringPool_Intern((StringPool *)g_stringPool, (const char *)buffer);
    }
    *out = interned;
}

int **igCharMetaField_Construct(int **self, int source) {
    igMetaField_Construct((igMetaField *)self);
    *self = &g_igCharMetaField_vtable[0];
    if (self != 0) {
        igCharMetaField_Init(self);
    }
    return self;
}

int **igCharMetaField_Init(int **self) {
    igMetaField_Init((igMetaField *)self);
    *self = &g_igCharMetaField_vtable[0];
    return self;
}

int **igCharMetaField_CopyConstruct(int **self, int source) {
    igMetaField_CopyConstruct((igMetaField *)self, (igMetaField *)source);
    *self = &g_igCharMetaField_vtable[0];
    return self;
}

void igCharMetaField_Destruct(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

int igCharMetaField_GetSize(void) {
    return 1;
}

void igCharMetaField_SetDefaultValue(void **self, char value) {
    char defaultValue;

    defaultValue = value;
    ((igMetaFieldView *)(self))->SetDefault(&defaultValue);
}

/* igMetaField slot 27 (+0x6c) for a char array: returns 1, the alignment of a single char element.
 * The receiver is not read. */
int igCharMetaField_GetAlignment(void) {
    return 1;
}

unsigned short igCompoundMetaField_GetElementSize(void *self) {
    return *(int *)&((igCompoundMetaField *)self)->_size;
}

int igCompoundMetaField_GetAlignment(igCompoundMetaField *self) {
    int alignment = 0;
    int i = 0;
    while (i < ((igMetaFieldList *)self->_fieldList)->_count) {
        int fieldAlignment = ((igMetaFieldView **)((igMetaFieldList *)self->_fieldList)->_data)[i]->GetAlignment();
        if (alignment < fieldAlignment) alignment = fieldAlignment;
        i++;
    }
    return alignment;
}

void igCompoundMetaField_SetToDefault(void *self, int object) {
    int i;
    igMetaFieldList *fields;
    void *field;

    for (i = 0; fields = (igMetaFieldList *)((igCompoundMetaField *)self)->_fieldList, i < fields->_count; i++) {
        field = (void *)(((int *)fields->_data)[i]);
        ((igMetaFieldView *)field)->SetToDefault(object);
    }
}

void igCompoundMetaField_CopyDefaultToValue(void *self, int object) {
    int i;
    igMetaFieldList *fields;
    for (i = 0; fields = (igMetaFieldList *)((igCompoundMetaField *)self)->_fieldList, i < fields->_count; i++) {
        ((igMetaFieldView *)(((int *)fields->_data)[i]))->CopyDefaultToValue(object);
    }
}

void igCompoundMetaField_ConstructValue(igCompoundMetaField *self, int object) {
    int i;
    igMetaFieldList *fields;
    i = 0;
    while (fields = (igMetaFieldList *)self->_fieldList, i < fields->_count) {
        ((igMetaFieldView **)fields->_data)[i]->ConstructValue(object);
        i++;
    }
}

void igCompoundMetaField_DestructValue(igCompoundMetaField *self, int object) {
    int i;
    igMetaFieldView *field;
    for (i = 0; i < ((igMetaFieldList *)self->_fieldList)->_count; i++) {
        field = ((igMetaFieldView **)((igMetaFieldList *)self->_fieldList)->_data)[i];
        field->DestructValue(object);
    }
}

void igCompoundMetaField_ZeroValue(igCompoundMetaField *a, int x) {
    int i;
    for (i = 0; i < ((igMetaFieldList *)a->_fieldList)->_count; i++) {
        ((igMetaFieldView **)((igMetaFieldList *)a->_fieldList)->_data)[i]->ZeroValue(x);
    }
}

void igCompoundMetaField_ClearValue(igCompoundMetaField *self, int object) {
    int i = 0;
    while (i < ((igMetaFieldList *)self->_fieldList)->_count) {
        ((igMetaFieldView **)((igMetaFieldList *)self->_fieldList)->_data)[i]->ClearValue(object);
        i++;
    }
}

void igCompoundMetaField_DeepCopy(void *self, int dest, int source) {
    int i;
    for (i = 0; i < ((igMetaFieldList *)((igCompoundMetaField *)self)->_fieldList)->_count; i++) {
        ((igMetaFieldView **)((igMetaFieldList *)((igCompoundMetaField *)self)->_fieldList)->_data)[i]->DeepCopy(dest, source);
    }
}

void igCompoundMetaField_CopyReference(void *self, int dest, int source) {
    int i;
    for (i = 0; i < ((igMetaFieldList *)((igCompoundMetaField *)self)->_fieldList)->_count; i++) {
        igMetaFieldView *field = ((igMetaFieldView **)((igMetaFieldList *)((igCompoundMetaField *)self)->_fieldList)->_data)[i];
        field->CopyReference(dest, source);
    }
}

void igCompoundMetaField_ResetValue(igCompoundMetaField *self, int dest, int source) {
    int i;
    igMetaFieldView *field;
    for (i = 0; i < ((igMetaFieldList *)self->_fieldList)->_count; i++) {
        field = ((igMetaFieldView **)((igMetaFieldList *)self->_fieldList)->_data)[i];
        field->ResetValue(dest, source);
    }
}

void igCompoundMetaField_IgnoreCopy(igCompoundMetaField *self, int dest, int source) {
    int i = 0;
    while (i < ((igMetaFieldList *)self->_fieldList)->_count) {
        ((igMetaFieldView **)((igMetaFieldList *)self->_fieldList)->_data)[i]->IgnoreCopy(dest, source);
        i++;
    }
}

void igCompoundMetaField_Print(igCompoundMetaField *self, int object, int a2, int a3) {
    unsigned int count;
    unsigned int i;

    count = ((igMetaFieldList *)self->_fieldList)->_count;
    for (i = 0; i < count; i++) {
        ((igMetaFieldView **)((igMetaFieldList *)self->_fieldList)->_data)[i]->Print(object, a2, a3);
    }
}

void igCompoundMetaField_ReleaseElements(igCompoundMetaField *self, int object, int a2, int a3) {
    int i;

    for (i = 0; i < ((igMetaFieldList *)self->_fieldList)->_count; i++) {
        ((igMetaFieldView **)((igMetaFieldList *)self->_fieldList)->_data)[i]->ReleaseElements(object, a2, a3);
    }
}

int igCompoundMetaField_Write(igCompoundMetaField *self, int object, int file) {
    int sum = 0;
    int i;
    for (i = 0; i < ((igMetaFieldList *)self->_fieldList)->_count; i++) {
        sum += ((igMetaFieldView **)((igMetaFieldList *)self->_fieldList)->_data)[i]->Write(object, file);
    }
    return sum;
}

int igCompoundMetaField_Compare(igCompoundMetaField *self, int object, int other) {
    int i;
    igMetaFieldView *field;

    for (i = 0; i < ((igMetaFieldList *)self->_fieldList)->_count; i++) {
        field = ((igMetaFieldView **)((igMetaFieldList *)self->_fieldList)->_data)[i];
        if (field->Compare(object, other) != 0) {
            return -1;
        }
    }
    return 0;
}

int igCompoundMetaField_IsAlikeExactly(igCompoundMetaField *self, int object, int other) {
    int i;
    for (i = 0; i < ((igMetaFieldList *)self->_fieldList)->_count; i++) {
        if (((igMetaFieldView **)((igMetaFieldList *)self->_fieldList)->_data)[i]->IsAlikeExactly(object, other) == 0) {
            return 0;
        }
    }
    return 1;
}

int igCompoundMetaField_IsAlikeDeep(igCompoundMetaField *self, int object, int other) {
    int i;

    for (i = 0; i < ((igMetaFieldList *)self->_fieldList)->_count; i++) {
        if (((igMetaFieldView **)((igMetaFieldList *)self->_fieldList)->_data)[i]->IsAlikeDeep(object, other) == 0) {
            return 0;
        }
    }
    return 1;
}

int igCompoundMetaField_IsAlikeShallow(igCompoundMetaField *self, int object, int other) {
    int i;

    for (i = 0; i < ((igMetaFieldList *)self->_fieldList)->_count; i++) {
        if (((igMetaFieldView **)((igMetaFieldList *)self->_fieldList)->_data)[i]->IsAlikeShallow(object, other) == 0) {
            return 0;
        }
    }
    return 1;
}

int igCompoundMetaField_IsAlikeIgnore(igCompoundMetaField *self, int object, int other) {
    int i;
    for (i = 0; i < ((igMetaFieldList *)self->_fieldList)->_count; i++) {
        if (((igMetaFieldView **)((igMetaFieldList *)self->_fieldList)->_data)[i]->IsAlikeIgnore(object, other) == 0) {
            return 0;
        }
    }
    return 1;
}

int igCompoundMetaField_GetRawFieldMemSize(igCompoundMetaField *self, int object) {
    int size = 0;
    int padding = 0;
    int i;
    for (i = 0; i < ((igMetaFieldList *)self->_fieldList)->_count; i++) {
        size += ((igMetaFieldView **)((igMetaFieldList *)self->_fieldList)->_data)[i]->GetRawFieldMemSize(object) + padding;
    }
    return size;
}

int igCompoundMetaField_WriteRawFieldMem(igCompoundMetaField *self, int dest, int source, int a3, unsigned char swap) {
    int sum = 0;
    int count;
    int base;
    int i;
    base = self->_offset;
    count = ((igMetaFieldList *)self->_fieldList)->_count;
    for (i = 0; i < count; i++) {
        igMetaFieldView *field = ((igMetaFieldView **)((igMetaFieldList *)self->_fieldList)->_data)[i];
        int offset = ((igMetaField *)field)->_offset;
        sum += field->WriteRawFieldMem((dest + offset) - base, (source + offset) - base, a3, swap);
    }
    return sum;
}

int igCompoundMetaField_ReadRawFieldMem(igCompoundMetaField *self, int dest, int source, int a3, unsigned char swap) {
    igMetaFieldView *field;
    int sum;
    int offset;
    int count;
    int base;
    int i;

    sum = 0;
    i = 0;
    base = self->_offset;
    count = ((igMetaFieldList *)self->_fieldList)->_count;
    for (; i < count; i++) {
        field = ((igMetaFieldView **)((igMetaFieldList *)self->_fieldList)->_data)[i];
        offset = ((igMetaField *)field)->_offset;
        sum += field->ReadRawFieldMem((dest + offset) - base, (source + offset) - base, a3, swap);
    }
    return sum;
}

void igCompoundMetaField_SwapBytes(igMetaFieldView *self, int buffer, int count) {
    int element;
    igMetaFieldList *fields;
    igMetaFieldView *field;
    int i;
    int j;

    element = buffer;
    fields = (igMetaFieldList *)self->GetDescriptor()->_fieldList;
    for (i = 0; i < count; i++) {
        for (j = 0; j < fields->_count; j++) {
            field = ((igMetaFieldView **)fields->_data)[j];
            field->SwapBytes((void *)(element + ((igMetaField *)field)->_offset), 1);
        }
        element += ((igCompoundMetaField *)self)->_size;
    }
}

int igCompoundMetaField_GetDescriptor(void) {
    return (*(int *)&g_igCompoundMetaField_descriptor);
}

void igCompoundMetaField_SwapValue(void *self, int object) {
    int i;
    igMetaFieldList *fields;
    igMetaFieldView *field;
    i = 0;
    while (fields = (igMetaFieldList *)((igCompoundMetaField *)self)->_fieldList, i < fields->_count) {
        field = (igMetaFieldView *)(((int *)fields->_data)[i]);
        field->SwapValue(object);
        i += 1;
    }
}

int igCompoundMetaField_ValueFromString(int *self, int object, int text, int directory) {
    int closeLength;
    int openLength;
    igMetaFieldList *fields;
    int i;

    openLength = 0;
    sscanf((const char *)text, "{%n", &openLength);
    fields = (igMetaFieldList *)((igMetaFieldView *)self)->GetDescriptor()->_fieldList;
    for (i = 0; i < fields->_count; i++) {
        igMetaFieldView *field = ((igMetaFieldView **)fields->_data)[i];
        field->ValueFromString(object + ((igMetaField *)field)->_offset, text + openLength, directory);
    }
    sscanf((const char *)text, "}%n", &closeLength);
    return openLength + closeLength;
}

int igCompoundMetaField_ValueToString(igStringRef *out, igMetaFieldView *ctx, int a2, int a3) {
    char *sepA = (char *)" { ";
    char *sepB = (char *)" } ";
    igMetaFieldList *list = (igMetaFieldList *)ctx->GetDescriptor()->_fieldList;
    int n = list->_count;
    igStringRef *arr = (igStringRef *)((void *)igObject_Callocate((igObject *)ctx, n, 4));
    int total = 9;
    int i;
    for (i = 0; i < n; i++) {
        int off = i * 4;
        igMetaFieldView *e = ((igMetaFieldView **)list->_data)[i];
        *(igStringRef *)((char *)arr + off) = e->ValueToString(a2 + ((igMetaField *)e)->_offset, a3);
        total += strlen(((igStringRef *)((char *)arr + off))->p) + 1;
    }
    char *buf = ((char *)igObject_AllocateStorage((igObject *)ctx, total));
    strcpy(buf, sepA);
    char *p = buf + 4;
    buf[3] = 0x20;
    for (i = 0; i < n; i++) {
        strcpy(p, arr[i].p);
        p += strlen(arr[i].p);
        *p = 0x20;
        p++;
    }
    strcpy(p, sepB);
    igStringRef res(buf);
    igObject_FreeMemory((igObject *)ctx, (void *)buf);
    out->p = res.p;
    if (out->p != 0) *(int *)(out->p - 4) = *(int *)(out->p - 4) + 1;
    return 0;
}

void FUN_002d6090(void) {

}

int FUN_002d60a0(void) {
    return 1;
}

void igContext_BuildExtensionInfoList(igContext *self) {
    if (self->_pExtList == 0) {
        igContextExtInfoList *list;
        int meta;
        int i;
        list = ((igContextExtInfoList *)igContextExtInfoList_Create(((int)igObject_GetAllocator((igObject *)self))));
        if (list != 0) ++list->_refCount;
        igRelease((igObject *)self->_pExtList);
        self->_pExtList = (int)list;
        {
            igContextExtInfoList *o = (igContextExtInfoList *)self->_pExtList;
            --o->_refCount;
            if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy((igObject *)((igObject *)o));
        }
        ((igObjectDispatchView *)self)->GetMeta();
        meta = igObjectSystem_FindMetaByNameDefault("igContextExt");
        self->_iNumExts = igMetaObject_CountTree((igMetaObject *)meta) - 1;
        if (self->_iNumExts >= ((igContextExtInfoList *)self->_pExtList)->_count) List_Reserve((igDataList *)((igContextExtInfoList *)self->_pExtList), self->_iNumExts, 4);
        ObjectList_ResizeRetained((igTDataList<igObject *> *)((igContextExtInfoList *)self->_pExtList), self->_iNumExts);
        for (i = 0; i < self->_iNumExts; i++) {
            int name;
            igMetaObject *node;
            igContextExtInfo *info;
            igContextExtInfoList *infoList;
            node = ((igMetaObject *)igMetaObject_GetTreeNode((igMetaObject *)meta, i + 1));
            info = ((igContextExtInfo *)igContextExtInfo_Create(((int)igObject_GetAllocator((igObject *)self))));
            if (node != 0) ++node->_refCount;
            igRelease((igObject *)info->_pMeta);
            info->_pMeta = (int)node;
            name = node->_name;
            if (g_stringPool == 0) {
                int pool = ((int)StringPool_Allocate(16));
                if (pool != 0) pool = ((int)StringPool_Construct((StringPool *)pool));
                g_stringPool = (StringPool *)pool;
            }
            {
                int interned = (int)StringPool_Intern((StringPool *)g_stringPool, (const char *)name);
                int old = info->_pName;
                if (old != 0) {
                    int *header = (int *)(old - 8);
                    int refs = *(int *)(old - 4) - 1;
                    *(int *)(old - 4) = refs;
                    if (refs == 0) StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
                }
                info->_pName = interned;
            }
            info->_pVendorName = 0;
            infoList = (igContextExtInfoList *)self->_pExtList;
            if (info != 0) ++info->_refCount;
            igRelease(((igObject **)infoList->_data)[i]);
            if (infoList->_count != 0 && i >= 0 && i < infoList->_count) ((igContextExtInfo **)infoList->_data)[i] = info;
            --info->_refCount;
            if ((info->_refCount & 0x7fffff) == 0) igObject_Destroy((igObject *)((igObject *)info));
        }
    }
}

int igContext_GetMeta(void) {
    return (int)g_igContext_metaObject;
}

int igContext_GetExtensionInfoList(igContext *self) {
    if (self->_pExtList == 0) {
        igContext_BuildExtensionInfoList(self);
    }
    if (self->_iNumExts <= 0) {
        return 0;
    }
    return self->_pExtList;
}

int igContext_FindExtensionMeta(igContext *self, int name) {
    int i;
    bool found;
    igContextExtInfo *info;

    info = 0;
    if (self->_pExtList == 0) {
        igContext_BuildExtensionInfoList(self);
    }
    i = 0;
    if (self->_iNumExts <= 0) {
        return 0;
    }
    found = true;
    while (i < self->_iNumExts && found) {
        info = ((igContextExtInfo **)((igContextExtInfoList *)self->_pExtList)->_data)[i];
        if (strcmp((const char *)info->_pName, (const char *)name) == 0) {
            found = false;
        } else {
            i += 1;
        }
    }
    if ((found & 0xFF) == 1) {
        return 0;
    }
    return info->_pMeta;
}

void *igContext_GetExtension(igVisualContext *self, int name) {
    int meta;
    igObject *extension;

    meta = igContext_FindExtensionMeta((igContext *)self, name);
    if (meta == 0) {
        return 0;
    }
    extension = (igObject *)(((void *)igContext_FindExtensionInstance((igContext *)self, meta)));
    if (extension == 0) {
        extension = (igObject *)(((void *)igMetaObject_CreateInstance((igMetaObject *)meta, (igMemoryPoolView *)(((int)igObject_GetAllocator((igObject *)self))))));
        if (extension != 0) {
            if (((igContextExtView *)extension)->IsSupported(self) == 0) {
                extension->_refCount = extension->_refCount - 1;
                if ((extension->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(extension);
                }
                extension = (igObject *)(0);
            } else {
                ObjectList_AppendRetained((igObjectList *)self->_pExtInstances, extension);
                extension->_refCount = extension->_refCount - 1;
                if ((extension->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(extension);
                }
                ((igContextExtView *)extension)->SetContext(self);
            }
        }
    }
    return extension;
}

int igContext_FindExtensionInstance(igContext *self, int meta) {
    int i;
    for (i = 0; i < ((igObjectList *)self->_pExtInstances)->_count; i++) {
        if (igObject_IsKindOf((igObject *)((int *)((igObjectList *)self->_pExtInstances)->_data)[i], (igMetaObject *)meta) != 0) {
            return ((int *)((igObjectList *)self->_pExtInstances)->_data)[i];
        }
    }
    return 0;
}

