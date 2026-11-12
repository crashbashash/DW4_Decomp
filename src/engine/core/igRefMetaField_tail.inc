int igRefMetaField_GetSize(void) {
    return 4;
}

void igRefMetaField_ZeroValue(igMetaField *field,void *object) {
    int destination=(int)object+field->_offset;
    memset(destination,0,((FieldSizeDispatchView *)field)->GetTypeSize() & 0xffff);
}

void igRefMetaField_ClearValue(igMetaField *field,void *object) {
    int destination=(int)object+field->_offset;
    memset(destination,0,((FieldSizeDispatchView *)field)->GetTypeSize() & 0xffff);
}

int igRefMetaField_ReadRawFieldMem(void *arg0, int a1, int *arg2, int arg3, int arg4) {
    DW4SR4 sp3C;
    int *arg1 = (int *)a1;
    int temp_v1;
    void **temp_v0;
    void *temp_v0_2;

    if ((arg3 != 0) && (temp_v1 = *arg2, (temp_v1 != -1))) {
        sp3C.w0 = temp_v1;
        if (arg4 != 0) {
            temp_v0 = (void **)(((void **)igIntMetaField_GetDefaultDescriptor()));
            ((DW4VCSR_208_1 *)(temp_v0))->vX(&sp3C.w0, 1);
        }
        temp_v0_2 = (void *)(FUN_002d7e90((int *)arg3, sp3C.w0));
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

int FUN_003057a0(void) {
    return ((int *)g_igRefMetaField_metaObject)[0];
}

char *FUN_003057b0(char *s, char ch) {
    char *r;
    while (*s != ch && *s != 0 && *s != -1) s++;
    r = s + 1;
    if (*s != ch) r = 0;
    return r;
}

int FUN_00305800(RecoveryString_305800 *arg0, void *arg1, int *arg2, int arg3, int arg4, char *arg5, int arg6) {
    char spC0[256];
    char spA0[32];
    Alloc_305800 *a;
    char *buf;
    char *w;
    int i;
    int v;

    if (arg5 == 0) arg5 = &GPR_00554c2c;
    if (arg6 == -1) arg6 = strlen(arg5) + 5;
    sprintf(spA0, DAT_004fb0c8, arg6);
    a = ((Alloc_305800 *)igObject_GetAllocator((int)arg1));
    a = GPR_00554c14 ? a : ((Alloc_305800 *)Memory_GetAllocatorBySelector(DAT_00587060[0]));
    buf = a->alloc(arg3 * (strlen(spA0) + 0x80));
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
            Rec *r = ((Rec *)FUN_002d7c50((O7c50 *)arg4, (unsigned)(*arg2)));
            if (r != 0) {
                sprintf(w, DAT_004fb0e0, r->name);
            } else {
                sprintf(w, DAT_004fb0f0);
            }
        } else {
            sprintf(w, DAT_004fb0f0);
        }
    }
    int *pi;
    if (buf == 0) {
        pi = 0;
    } else {
        if (g_stringPool[0] == 0) {
            v = ((int)FUN_002eb010(16));
            if (v != 0) v = ((int)StringPool_Construct((struct S_2eadf0 *)v));
            g_stringPool[0] = v;
        }
        pi = ((int *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)buf));
    }
    RecoveryString_305800 sp1CC(pi);
    a = ((Alloc_305800 *)igObject_GetAllocator((int)arg1));
    a = GPR_00554c14 ? a : ((Alloc_305800 *)Memory_GetAllocatorBySelector(DAT_00587060[0]));
    a->release(buf);
    int *src = sp1CC.p;
    arg0->p = src;
    if (arg0->p != 0) *(int *)((char *)arg0->p - 4) = *(int *)((char *)arg0->p - 4) + 1;
    return 0;
}

int FUN_00305aa0(int self, int str, int *out, int n, Lst_305aa0 *list) {
    int idx;
    int s = str;
    int *o = out;
    int i;
    for (i = 0; i < n; i++) {
        E_305aa0 *e;
        s = ((int)FUN_003057b0((char *)s, (char)0x7b));
        if (list != 0) {
            s = ((int)FUN_003057b0((char *)s, (char)0x5b));
            if (sscanf(s, &DAT_004f95c0[0], &idx) == 0) idx = -1;
            if (idx >= 0 && idx < list->n) {
                e = ((E_305aa0 *)FUN_002d7e90((int *)list, idx));
                if (e != 0) o[i] = e->v;
                else o[i] = 0;
            } else o[i] = 0;
        } else o[i] = 0;
    }
    return s - str;
}

int FUN_00305bd0(igRefMetaField *arg0, int arg1, int arg2) {
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

unsigned char igRefMetaField_IsConstruct(igRefMetaField *field) { return field->_construct; }

int FUN_00305ce0(void) {
    return 4;
}

int FUN_00305cf0(void)
{
    return 1;
}

