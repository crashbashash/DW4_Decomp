int igRefMetaField_GetSize(void) {
    return 4;
}

void igRefMetaField_ZeroValue(igMetaField *field,void *object) {
    int destination=(int)object+field->_offset;
    memset(destination,0,((igMetaFieldView *)field)->GetSize() & 0xffff);
}

void igRefMetaField_ClearValue(igMetaField *field,void *object) {
    int destination=(int)object+field->_offset;
    memset(destination,0,((igMetaFieldView *)field)->GetSize() & 0xffff);
}

int igRefMetaField_ReadRawFieldMem(void *self, int destination, int *source, int directory, int swap) {
    int index;
    int *object = (int *)destination;
    int stored;
    void **indexField;
    igDirEntry *entry;

    if ((directory != 0) && (stored = *source, (stored != -1))) {
        index = stored;
        if (swap != 0) {
            indexField = (void **)(((void **)igIntMetaField_GetDefaultDescriptor()));
            ((igMetaFieldView *)(indexField))->SwapBytes(&index, 1);
        }
        entry = (igDirEntry *)(igDirectory_GetEntry((int *)directory, index));
        if (entry != 0) {
            *object = entry->_ref;
        } else {
            *object = 0;
        }
    } else {
        *object = 0;
    }
    return 4;
}

/* Writes the directory index of the referenced object, or -1 for none. A reference to an object
 * the directory does not hold is reported once per kind of field. */
int igMemoryRefMetaField_WriteRawFieldMem(igMetaFieldView *self, int *source, void *dest, int directory, int swap) {
    int *index = (int *)dest;
    igDirEntryView *entry;
    if (directory != 0 && *source != 0) {
        entry = (igDirEntryView *)igDirectory_GetEntryByRef((igDirectoryView *)directory, *source);
        if (*source != 0 && entry == 0) {
            if (self->_parentMetaObject != 0) {
                if (!g_igMemoryRefMetaField_unresolvedFieldRefWarned) {
                    igMetaObject *meta = ((igObjectDispatchView *)self)->GetMeta();
                    int answer = igReportError(text_s_s_s_writeRawFieldMem_0x_x_0_0x, ((igMetaObject *)self->_parentMetaObject)->_name, self->_fieldName, meta->_name, source, (unsigned int)*source);
                    if (answer != 1 && answer == 2) g_igMemoryRefMetaField_unresolvedFieldRefWarned = 1;
                }
            } else {
                if (!g_igMemoryRefMetaField_unresolvedRefWarned) {
                    igMetaObject *meta = ((igObjectDispatchView *)self)->GetMeta();
                    int answer = igReportError(text_s_writeRawFieldMem_0x_x_0_0x_x_Not, meta->_name, source, (unsigned int)*source);
                    if (answer != 1 && answer == 2) g_igMemoryRefMetaField_unresolvedRefWarned = 1;
                }
            }
        }
        if (entry != 0) {
            *index = entry->_index;
        } else {
            *index = -1;
        }
    } else {
        *index = -1;
    }
    if (swap != 0) {
        self->SwapBytes(index, 1);
    }
    return 4;
}

int igRefMetaField_GetMeta(void) {
    return ((int *)g_igRefMetaField_metaObject)[0];
}

char *igRefMetaField_SkipPastChar(char *s, char ch) {
    char *r;
    while (*s != ch && *s != 0 && *s != -1) s++;
    r = s + 1;
    if (*s != ch) r = 0;
    return r;
}

int igRefMetaField_ArrayToString(igStringRef *out, void *owner, int *refs, int count, int directory, char *prefix, int width) {
    char item[256];
    char itemFormat[32];
    igMemoryPoolView *a;
    char *buf;
    char *w;
    int i;

    if (prefix == 0) prefix = &g_igRefMetaField_defaultArrayPrefix;
    if (width == -1) width = strlen(prefix) + 5;
    sprintf(itemFormat, percent_percent_minus_percent_ds, width);
    a = ((igMemoryPoolView *)igObject_GetAllocator((int)owner));
    a = g_useOwnerAllocator ? a : ((igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary));
    buf = (char *)a->Allocate(count * (strlen(itemFormat) + 0x80));
    w = buf;
    for (i = 0; i < count; i++) {
        sprintf(item, itemFormat, prefix);
        if (i == 0) {
            if (count > 1) {
                sprintf(w, percent_s_open_brace_open_brace_space, item);
            } else {
                goto block12;
            }
        } else {
block12:
            sprintf(w, percent_s_open_brace_space, item);
        }
        w = buf + strlen(buf);
        if (directory != 0) {
            igDirEntryView *r = ((igDirEntryView *)igDirectory_GetEntryByRef((igDirectoryView *)directory, (unsigned)(*refs)));
            if (r != 0) {
                sprintf(w, text_Reference_d, r->_index);
            } else {
                sprintf(w, text_Reference_1);
            }
        } else {
            sprintf(w, text_Reference_1);
        }
    }
    igStringRef text(buf);
    a = ((igMemoryPoolView *)igObject_GetAllocator((int)owner));
    a = g_useOwnerAllocator ? a : ((igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary));
    a->Free(buf);
    char *src = text.p;
    out->p = src;
    if (out->p != 0) *(int *)(out->p - 4) = *(int *)(out->p - 4) + 1;
    return 0;
}

int igRefMetaField_ArrayFromString(int self, int str, int *out, int n, igDirectory *list) {
    int idx;
    int s = str;
    int *o = out;
    int i;
    for (i = 0; i < n; i++) {
        igDirEntry *e;
        s = ((int)igRefMetaField_SkipPastChar((char *)s, (char)0x7b));
        if (list != 0) {
            s = ((int)igRefMetaField_SkipPastChar((char *)s, (char)0x5b));
            if (sscanf(s, &percent_d_7[0], &idx) == 0) idx = -1;
            if (idx >= 0 && idx < list->_count) {
                e = ((igDirEntry *)igDirectory_GetEntry((int *)list, idx));
                if (e != 0) o[i] = e->_ref;
                else o[i] = 0;
            } else o[i] = 0;
        } else o[i] = 0;
    }
    return s - str;
}

int igRefMetaField_Compare(igRefMetaField *self, int a, int b) {
    int offset;

    offset = self->_offset;
    return *(int *)(a + offset) - *(int *)(b + offset);
}

void *igRefMetaField_Construct(igRefMetaField *self) {
    igMetaField_Construct((igMetaField *)self);
    self->_vtable = (int)g_igRefMetaField_vtable;
    if (self) {
        igRefMetaField_Init(self);
    }
    return self;
}

void *igRefMetaField_Init(igRefMetaField *self) {
    igMetaField_Init((igMetaField *)self);
    self->_vtable = (int)g_igRefMetaField_vtable;
    self->_construct = 0;
    self->_destruct = 0;
    return self;
}

/* Copy the base metadata field, stamp the reference-field vtable and copy the construct/destruct
 * flags. */
igRefMetaField *igRefMetaField_CopyConstruct(igRefMetaField *self, igRefMetaField *source) {
    igMetaField_CopyConstruct((igMetaField *)self, (igMetaField *)source);
    self->_vtable = (int)g_igRefMetaField_vtable;
    self->_construct = source->_construct;
    self->_destruct = source->_destruct;
    return self;
}

/* The reference field adds no teardown of its own to the igMetaField base. */
void igRefMetaField_Destruct(igRefMetaField *self) {
    igMetaField_Destruct((igMetaField *)self);
}

unsigned char igRefMetaField_IsConstruct(igRefMetaField *field) { return field->_construct; }

int igRefMetaField_GetAlignment(void) {
    return 4;
}

int igRegistry_IsLoadingEnabled(void)
{
    return 1;
}

