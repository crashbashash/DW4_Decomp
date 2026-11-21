namespace Gap {
namespace Core {

int igCharMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    int consumed;
    int parsed;

    consumed = 0;
    parsed = 0;
    sscanf(strVal, "%d%n", &parsed, &consumed);
    *(char *)dstMem = parsed;
    return consumed;
}

igStringRef igCharMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    char buffer[1024];

    sprintf(buffer, (const char *)&percent_d_7[0], *(const char *)srcMem);
    return igStringRef(buffer);
}

igCharMetaField::igCharMetaField(bool boot) : igMetaField(boot)
{
    new (this, 0) igCharMetaField;
}

igCharMetaField::igCharMetaField()
{
}

igCharMetaField::igCharMetaField(const igCharMetaField &other) : igMetaField(other)
{
}

void igCharMetaField::__bootstrapDestruct()
{
    igMetaField::__bootstrapDestruct();
}

unsigned short igCharMetaField::computeSize() {
    return 1;
}

void igCharMetaField::setDefault(char def)
{
    setDefaultMemory(&def);
}

/* igMetaField slot 27 (+0x6c) for a char array: returns 1, the alignment of a single char element.
 * The receiver is not read. */
int igCharMetaField::computeRequiredAlignment() {
    return 1;
}

int igCompoundMetaField::computeTypeSize()
{
    return getSize();
}

int igCompoundMetaField::computeRequiredAlignment()
{
    int alignment = 0;
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        int fieldAlignment = ((igMetaField **)_fieldList->_data)[i]->computeRequiredAlignment();

        if (alignment < fieldAlignment) {
            alignment = fieldAlignment;
        }
    }
    return alignment;
}

void igCompoundMetaField::resetByValue(igObject *src)
{
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        ((igMetaField **)_fieldList->_data)[i]->resetByValue(src);
    }
}

void igCompoundMetaField::resetByReference(igObject *src)
{
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        ((igMetaField **)_fieldList->_data)[i]->resetByReference(src);
    }
}

void igCompoundMetaField::construct(igObject *src)
{
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        ((igMetaField **)_fieldList->_data)[i]->construct(src);
    }
}

void igCompoundMetaField::destruct(igObject *src)
{
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        ((igMetaField **)_fieldList->_data)[i]->destruct(src);
    }
}

void igCompoundMetaField::commission(igObject *src)
{
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        ((igMetaField **)_fieldList->_data)[i]->commission(src);
    }
}

void igCompoundMetaField::decommission(igObject *src)
{
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        ((igMetaField **)_fieldList->_data)[i]->decommission(src);
    }
}

void igCompoundMetaField::copyByValue(igObject *dst, const igObject *src)
{
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        ((igMetaField **)_fieldList->_data)[i]->copyByValue(dst, src);
    }
}

void igCompoundMetaField::copyByReference(igObject *dst, const igObject *src)
{
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        ((igMetaField **)_fieldList->_data)[i]->copyByReference(dst, src);
    }
}

void igCompoundMetaField::copyByReset(igObject *dst, const igObject *src)
{
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        ((igMetaField **)_fieldList->_data)[i]->copyByReset(dst, src);
    }
}

void igCompoundMetaField::copyByNoCopy(igObject *dst, const igObject *src)
{
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        ((igMetaField **)_fieldList->_data)[i]->copyByNoCopy(dst, src);
    }
}

void igCompoundMetaField::print(const igObject *src, unsigned int deep, const char *indent)
{
    unsigned int count = _fieldList->_count;
    unsigned int i;

    for (i = 0; i < count; i++) {
        ((igMetaField **)_fieldList->_data)[i]->print(src, deep, indent);
    }
}

void igCompoundMetaField::traverse(igObject *obj, void *visitFunc, void *traversalData)
{
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        ((igMetaField **)_fieldList->_data)[i]->traverse(obj, visitFunc, traversalData);
    }
}

int igCompoundMetaField::addToDirectory(igObject *obj, igDirectory *dir)
{
    int count = 0;
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        count += ((igMetaField **)_fieldList->_data)[i]->addToDirectory(obj, dir);
    }
    return count;
}

int igCompoundMetaField::compare(const igObject *obj1, const igObject *obj2) const
{
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        if (((igMetaField **)_fieldList->_data)[i]->compare(obj1, obj2) != 0) {
            return -1;
        }
    }
    return 0;
}

bool igCompoundMetaField::isAlikeCompareExactly(const igObject *obj1, const igObject *obj2) const
{
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        if (!((igMetaField **)_fieldList->_data)[i]->isAlikeCompareExactly(obj1, obj2)) {
            return false;
        }
    }
    return true;
}

bool igCompoundMetaField::isAlikeCompareDeep(const igObject *obj1, const igObject *obj2) const
{
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        if (!((igMetaField **)_fieldList->_data)[i]->isAlikeCompareDeep(obj1, obj2)) {
            return false;
        }
    }
    return true;
}

bool igCompoundMetaField::isAlikeCompareShallow(const igObject *obj1, const igObject *obj2) const
{
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        if (!((igMetaField **)_fieldList->_data)[i]->isAlikeCompareShallow(obj1, obj2)) {
            return false;
        }
    }
    return true;
}

bool igCompoundMetaField::isAlikeCompareNoCompare(const igObject *obj1, const igObject *obj2) const
{
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        if (!((igMetaField **)_fieldList->_data)[i]->isAlikeCompareNoCompare(obj1, obj2)) {
            return false;
        }
    }
    return true;
}

int igCompoundMetaField::getIoSize(const igObject *obj) const
{
    int size = 0;
    int padding = 0;
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        size += ((igMetaField **)_fieldList->_data)[i]->getIoSize(obj) + padding;
    }
    return size;
}

int igCompoundMetaField::writeRawFieldMemory(const void *fieldMem, void *dstMem, igDirectory *dir, bool endianSwap) const
{
    int size = 0;
    int count;
    int base;
    int i;

    base = _offset;
    count = _fieldList->_count;

    for (i = 0; i < count; i++) {
        igMetaField *field = ((igMetaField **)_fieldList->_data)[i];
        int offset = field->_offset;

        size += field->writeRawFieldMemory((const char *)fieldMem + offset - base, (char *)dstMem + offset - base,
                                           dir, endianSwap);
    }
    return size;
}

int igCompoundMetaField::readRawFieldMemory(void *fieldMem, const void *srcMem, igDirectory *dir, bool endianSwap) const
{
    int size = 0;
    int count;
    int base;
    int i;

    base = _offset;
    count = _fieldList->_count;

    for (i = 0; i < count; i++) {
        igMetaField *field = ((igMetaField **)_fieldList->_data)[i];
        int offset = field->_offset;

        size += field->readRawFieldMemory((char *)fieldMem + offset - base, (const char *)srcMem + offset - base,
                                          dir, endianSwap);
    }
    return size;
}

void igCompoundMetaField::endianSwapMemory(void *fieldMem, int nFieldElts) const
{
    char *element = (char *)fieldMem;
    igMetaFieldList *fieldList = ((igCompoundMetaField *)getGenericMetaField())->_fieldList;
    int i;
    int j;

    for (i = 0; i < nFieldElts; i++) {
        for (j = 0; j < fieldList->_count; j++) {
            igMetaField *field = ((igMetaField **)fieldList->_data)[j];

            field->endianSwapMemory(element + field->_offset, 1);
        }
        element += _size;
    }
}

void igCompoundMetaField::endianSwap(igObject *obj) const
{
    int i;

    for (i = 0; i < _fieldList->_count; i++) {
        ((igMetaField **)_fieldList->_data)[i]->endianSwap(obj);
    }
}

int igCompoundMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    int closeLength;
    int openLength = 0;
    igMetaFieldList *fieldList;
    int i;

    sscanf(strVal, "{%n", &openLength);
    fieldList = ((igCompoundMetaField *)getGenericMetaField())->_fieldList;
    for (i = 0; i < fieldList->_count; i++) {
        igMetaField *field = ((igMetaField **)fieldList->_data)[i];

        field->setMemoryByString((char *)dstMem + field->_offset, strVal + openLength, dir);
    }
    sscanf(strVal, "}%n", &closeLength);
    return openLength + closeLength;
}

igStringRef igCompoundMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    const char *open = " { ";
    const char *close = " } ";
    igMetaFieldList *fieldList = ((igCompoundMetaField *)getGenericMetaField())->_fieldList;
    int count = fieldList->_count;
    igStringRef *strings = (igStringRef *)calloc(count, sizeof(igStringRef));
    int length = 9;
    int i;

    for (i = 0; i < count; i++) {
        igMetaField *field = ((igMetaField **)fieldList->_data)[i];

        strings[i] = field->getStringFromMemory((const char *)srcMem + field->_offset, dir);
        length += strlen(strings[i].p) + 1;
    }
    char *buffer = (char *)malloc(length);
    strcpy(buffer, open);
    char *cursor = buffer + 4;
    buffer[3] = ' ';
    for (i = 0; i < count; i++) {
        strcpy(cursor, strings[i].p);
        cursor += strlen(strings[i].p);
        *cursor = ' ';
        cursor++;
    }
    strcpy(cursor, close);
    igStringRef result(buffer);
    free(buffer);
    return result;
}
}
}

void igContextExt_MakeCurrent(void) {

}

int igContextExt_IsCurrent(void) {
    return 1;
}

void igContext_BuildExtensionInfoList(igContext *self) {
    if (self->_pExtList == 0) {
        igContextExtInfoList *list;
        int meta;
        int i;
        list = ((igContextExtInfoList *)igContextExtInfoList_Create(((int)((Gap::Core::igObject *)self)->getMemoryPool())));
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
        if (self->_iNumExts >= ((igContextExtInfoList *)self->_pExtList)->_count) ((Gap::Core::igDataList *)((igContextExtInfoList *)self->_pExtList))->setCapacity(self->_iNumExts, 4);
        ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)((igContextExtInfoList *)self->_pExtList)))->setCount(self->_iNumExts);
        for (i = 0; i < self->_iNumExts; i++) {
            int name;
            igMetaObject *node;
            igContextExtInfo *info;
            igContextExtInfoList *infoList;
            node = ((igMetaObject *)igMetaObject_GetTreeNode((igMetaObject *)meta, i + 1));
            info = ((igContextExtInfo *)igContextExtInfo_Create(((int)((Gap::Core::igObject *)self)->getMemoryPool())));
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
        extension = (igObject *)(((void *)igMetaObject_CreateInstance((igMetaObject *)meta, (igMemoryPoolView *)(((int)((Gap::Core::igObject *)self)->getMemoryPool())))));
        if (extension != 0) {
            if (((igContextExtView *)extension)->IsSupported(self) == 0) {
                extension->_refCount = extension->_refCount - 1;
                if ((extension->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(extension);
                }
                extension = (igObject *)(0);
            } else {
                ((Gap::Core::igObjectList *)self->_pExtInstances)->append((Gap::Core::igObject *)extension);
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
        if (((Gap::Core::igObject *)(((int *)((igObjectList *)self->_pExtInstances)->_data)[i]))->isOfType((igMetaObject *)meta) != 0) {
            return ((int *)((igObjectList *)self->_pExtInstances)->_data)[i];
        }
    }
    return 0;
}

