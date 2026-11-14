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

int igRefMetaField_ReadRawFieldMem(void *arg0, int a1, int *arg2, int arg3, int arg4) {
    int sp3C;
    int *arg1 = (int *)a1;
    int temp_v1;
    void **temp_v0;
    void *temp_v0_2;

    if ((arg3 != 0) && (temp_v1 = *arg2, (temp_v1 != -1))) {
        sp3C = temp_v1;
        if (arg4 != 0) {
            temp_v0 = (void **)(((void **)igIntMetaField_GetDefaultDescriptor()));
            ((igMetaFieldView *)(temp_v0))->SwapBytes(&sp3C, 1);
        }
        temp_v0_2 = (void *)(igDirectory_GetEntry((int *)arg3, sp3C));
        if (temp_v0_2 != 0) {
            *arg1 = *(int *)((char *)(temp_v0_2) + 24);
        } else {
            *arg1 = 0;
        }
    } else {
        *arg1 = 0;
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
                if (!GPR_00554c20) {
                    igMetaObject *meta = ((igObjectDispatchView *)self)->getMeta();
                    int answer = igReportError(text_s_s_s_writeRawFieldMem_0x_x_0_0x, ((igMetaObject *)self->_parentMetaObject)->_name, self->_fieldName, meta->_name, source, (unsigned int)*source);
                    if (answer != 1 && answer == 2) GPR_00554c20 = 1;
                }
            } else {
                if (!GPR_00554c24) {
                    igMetaObject *meta = ((igObjectDispatchView *)self)->getMeta();
                    int answer = igReportError(text_s_writeRawFieldMem_0x_x_0_0x_x_Not, meta->_name, source, (unsigned int)*source);
                    if (answer != 1 && answer == 2) GPR_00554c24 = 1;
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

int igRefMetaField_ArrayToString(igStringRef *arg0, void *arg1, int *arg2, int arg3, int arg4, char *arg5, int arg6) {
    char spC0[256];
    char spA0[32];
    igMemoryPoolView *a;
    char *buf;
    char *w;
    int i;

    if (arg5 == 0) arg5 = &GPR_00554c2c;
    if (arg6 == -1) arg6 = strlen(arg5) + 5;
    sprintf(spA0, DAT_004fb0c8, arg6);
    a = ((igMemoryPoolView *)igObject_GetAllocator((int)arg1));
    a = g_useOwnerAllocator ? a : ((igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary));
    buf = (char *)a->Allocate(arg3 * (strlen(spA0) + 0x80));
    w = buf;
    for (i = 0; i < arg3; i++) {
        sprintf(spC0, spA0, arg5);
        if (i == 0) {
            if (arg3 > 1) {
                sprintf(w, DAT_004fb0d0, spC0);
            } else {
                goto block12;
            }
        } else {
block12:
            sprintf(w, DAT_004fb0d8, spC0);
        }
        w = buf + strlen(buf);
        if (arg4 != 0) {
            igDirEntryView *r = ((igDirEntryView *)igDirectory_GetEntryByRef((igDirectoryView *)arg4, (unsigned)(*arg2)));
            if (r != 0) {
                sprintf(w, text_Reference_d, r->_index);
            } else {
                sprintf(w, text_Reference_1);
            }
        } else {
            sprintf(w, text_Reference_1);
        }
    }
    igStringRef sp1CC(buf);
    a = ((igMemoryPoolView *)igObject_GetAllocator((int)arg1));
    a = g_useOwnerAllocator ? a : ((igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary));
    a->Free(buf);
    char *src = sp1CC.p;
    arg0->p = src;
    if (arg0->p != 0) *(int *)(arg0->p - 4) = *(int *)(arg0->p - 4) + 1;
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
            if (sscanf(s, &DAT_004f95c0[0], &idx) == 0) idx = -1;
            if (idx >= 0 && idx < list->_count) {
                e = ((igDirEntry *)igDirectory_GetEntry((int *)list, idx));
                if (e != 0) o[i] = e->_ref;
                else o[i] = 0;
            } else o[i] = 0;
        } else o[i] = 0;
    }
    return s - str;
}

int igRefMetaField_Compare(igRefMetaField *arg0, int arg1, int arg2) {
    int temp_v0;

    temp_v0 = arg0->_offset;
    return *(int *)(arg1 + temp_v0) - *(int *)(arg2 + temp_v0);
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

int FUN_00305cf0(void)
{
    return 1;
}

