int igCharMetaField_ValueFromString(void *arg0, char *arg1, int arg2) {
    int sp2C;
    int sp28;
    int t;
    sp2C = 0;
    sp28 = 0;
    sscanf(arg2, DAT_004f9588, &sp28, &sp2C);
    t = sp28;
    *arg1 = t;
    return sp2C;
}

void igCharMetaField_ValueToString(int *arg0, int arg1, char *arg2) {
    char sp20[1024];
    int var_v0;
    int var_v1;

    sprintf(sp20, &DAT_004f95c0[0], *arg2);
    if (sp20 == 0) {
        var_v1 = 0;
    } else {
        if (g_stringPool[0] == 0) {
            var_v0 = ((int)StringPool_Allocate(0x10));
            if (var_v0 != 0) {
                var_v0 = ((int)StringPool_Construct((StringPool *)var_v0));
            }
            g_stringPool[0] = var_v0;
        }
        var_v1 = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)sp20);
    }
    *arg0 = var_v1;
}

int **igCharMetaField_Construct(int **arg0, int extra1) {
    igMetaField_Construct((igMetaField *)arg0);
    *arg0 = &DAT_00531640[0];
    if (arg0 != 0) {
        igCharMetaField_Init(arg0);
    }
    return arg0;
}

int **igCharMetaField_Init(int **arg0) {
    igMetaField_Init((igMetaField *)arg0);
    *arg0 = &DAT_00531640[0];
    return arg0;
}

int **igCharMetaField_CopyConstruct(int **arg0, int extra1) {
    igMetaField_CopyConstruct((igMetaField *)arg0, (igMetaField *)extra1);
    *arg0 = &DAT_00531640[0];
    return arg0;
}

void igCharMetaField_Destruct(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

int igCharMetaField_GetSize(void) {
    return 1;
}

void igCharMetaField_SetDefaultValue(void **arg0, char arg1) {
    char sp1F;

    sp1F = arg1;
    ((igMetaFieldView *)(arg0))->SetDefault(&sp1F);
}

/* igMetaField slot 27 (+0x6c) for a char array: returns 1, the alignment of a single char element.
 * The receiver is not read. */
int igCharMetaField_GetAlignment(void) {
    return 1;
}

unsigned short igCompoundMetaField_GetElementSize(void *arg0) {
    return *(int *)((char *)(arg0) + 20);
}

int igCompoundMetaField_GetAlignment(igCompoundMetaField *arg0) {
    int mx = 0;
    int i = 0;
    while (i < ((igMetaFieldList *)arg0->_fieldList)->_count) {
        int r = ((igMetaFieldView **)((igMetaFieldList *)arg0->_fieldList)->_data)[i]->vfunc_27();
        if (mx < r) mx = r;
        i++;
    }
    return mx;
}

void igCompoundMetaField_SetToDefault(void *arg0, int arg1) {
    int var_s0;
    int *temp_a0;
    void *temp_a0_2;

    for (var_s0 = 0; temp_a0 = (int *)*(int *)((char *)(arg0) + 52), var_s0 < temp_a0[2]; var_s0++) {
        temp_a0_2 = (void *)(*(int *)(temp_a0[4] + (var_s0 * 4)));
        ((igMetaFieldView *)temp_a0_2)->SetToDefault(arg1);
    }
}

void igCompoundMetaField_CopyDefaultToValue(void *arg0, int arg1) {
    int i;
    int lst;
    for (i = 0; lst = *(int *)((char *)arg0 + 52), i < *(int *)(lst + 8); i++) {
        ((igMetaFieldView *)(*(int *)(*(int *)(lst + 16) + i * 4)))->CopyDefaultToValue(arg1);
    }
}

void igCompoundMetaField_ConstructValue(igCompoundMetaField *arg0, int arg1) {
    int i;
    igMetaFieldList *l;
    i = 0;
    while (l = (igMetaFieldList *)arg0->_fieldList, i < l->_count) {
        ((igMetaFieldView **)l->_data)[i]->ConstructValue(arg1);
        i++;
    }
}

void igCompoundMetaField_DestructValue(igCompoundMetaField *arg0, int arg1) {
    int i;
    igMetaFieldView *o;
    for (i = 0; i < ((igMetaFieldList *)arg0->_fieldList)->_count; i++) {
        o = ((igMetaFieldView **)((igMetaFieldList *)arg0->_fieldList)->_data)[i];
        o->DestructValue(arg1);
    }
}

void igCompoundMetaField_ZeroValue(igCompoundMetaField *a, int x) {
    int i;
    for (i = 0; i < ((igMetaFieldList *)a->_fieldList)->_count; i++) {
        ((igMetaFieldView **)((igMetaFieldList *)a->_fieldList)->_data)[i]->ZeroValue(x);
    }
}

void igCompoundMetaField_ClearValue(igCompoundMetaField *arg0, int arg1) {
    int i = 0;
    while (i < ((igMetaFieldList *)arg0->_fieldList)->_count) {
        ((igMetaFieldView **)((igMetaFieldList *)arg0->_fieldList)->_data)[i]->ClearValue(arg1);
        i++;
    }
}

void igCompoundMetaField_DeepCopy(void *arg0, int arg1, int arg2) {
    int i;
    for (i = 0; i < ((igMetaFieldList *)((igCompoundMetaField *)arg0)->_fieldList)->_count; i++) {
        ((igMetaFieldView **)((igMetaFieldList *)((igCompoundMetaField *)arg0)->_fieldList)->_data)[i]->DeepCopy(arg1, arg2);
    }
}

void igCompoundMetaField_CopyReference(void *arg0, int arg1, int arg2) {
    int i;
    for (i = 0; i < ((igMetaFieldList *)((igCompoundMetaField *)arg0)->_fieldList)->_count; i++) {
        igMetaFieldView *o = ((igMetaFieldView **)((igMetaFieldList *)((igCompoundMetaField *)arg0)->_fieldList)->_data)[i];
        o->vfunc_37(arg1, arg2);
    }
}

void igCompoundMetaField_ResetValue(igCompoundMetaField *arg0, int arg1, int arg2) {
    int i;
    igMetaFieldView *o;
    for (i = 0; i < ((igMetaFieldList *)arg0->_fieldList)->_count; i++) {
        o = ((igMetaFieldView **)((igMetaFieldList *)arg0->_fieldList)->_data)[i];
        o->vfunc_39(arg1, arg2);
    }
}

void igCompoundMetaField_IgnoreCopy(igCompoundMetaField *arg0, int arg1, int arg2) {
    int i = 0;
    while (i < ((igMetaFieldList *)arg0->_fieldList)->_count) {
        ((igMetaFieldView **)((igMetaFieldList *)arg0->_fieldList)->_data)[i]->vfunc_40(arg1, arg2);
        i++;
    }
}

void igCompoundMetaField_Print(igCompoundMetaField *arg0, int arg1, int arg2, int arg3) {
    unsigned int temp_s1;
    unsigned int i;

    temp_s1 = ((igMetaFieldList *)arg0->_fieldList)->_count;
    for (i = 0; i < temp_s1; i++) {
        ((igMetaFieldView **)((igMetaFieldList *)arg0->_fieldList)->_data)[i]->Print(arg1, arg2, arg3);
    }
}

void igCompoundMetaField_ReleaseElements(igCompoundMetaField *arg0, int arg1, int arg2, int arg3) {
    int i;

    for (i = 0; i < ((igMetaFieldList *)arg0->_fieldList)->_count; i++) {
        ((igMetaFieldView **)((igMetaFieldList *)arg0->_fieldList)->_data)[i]->ReleaseElements(arg1, arg2, arg3);
    }
}

int igCompoundMetaField_Write(igCompoundMetaField *arg0, int arg1, int arg2) {
    int sum = 0;
    int i;
    for (i = 0; i < ((igMetaFieldList *)arg0->_fieldList)->_count; i++) {
        sum += ((igMetaFieldView **)((igMetaFieldList *)arg0->_fieldList)->_data)[i]->Write(arg1, arg2);
    }
    return sum;
}

int igCompoundMetaField_Compare(igCompoundMetaField *arg0, int arg1, int arg2) {
    int i;
    igMetaFieldView *o;

    for (i = 0; i < ((igMetaFieldList *)arg0->_fieldList)->_count; i++) {
        o = ((igMetaFieldView **)((igMetaFieldList *)arg0->_fieldList)->_data)[i];
        if (o->vfunc_44(arg1, arg2) != 0) {
            return -1;
        }
    }
    return 0;
}

int igCompoundMetaField_IsAlikeExactly(igCompoundMetaField *arg0, int arg1, int arg2) {
    int i;
    for (i = 0; i < ((igMetaFieldList *)arg0->_fieldList)->_count; i++) {
        if (((igMetaFieldView **)((igMetaFieldList *)arg0->_fieldList)->_data)[i]->vfunc_45(arg1, arg2) == 0) {
            return 0;
        }
    }
    return 1;
}

int igCompoundMetaField_IsAlikeDeep(igCompoundMetaField *arg0, int arg1, int arg2) {
    int var_s0;

    for (var_s0 = 0; var_s0 < ((igMetaFieldList *)arg0->_fieldList)->_count; var_s0++) {
        if (((igMetaFieldView **)((igMetaFieldList *)arg0->_fieldList)->_data)[var_s0]->IsAlikeDeep(arg1, arg2) == 0) {
            return 0;
        }
    }
    return 1;
}

int igCompoundMetaField_IsAlikeShallow(igCompoundMetaField *arg0, int arg1, int arg2) {
    int i;

    for (i = 0; i < ((igMetaFieldList *)arg0->_fieldList)->_count; i++) {
        if (((igMetaFieldView **)((igMetaFieldList *)arg0->_fieldList)->_data)[i]->IsAlikeShallow(arg1, arg2) == 0) {
            return 0;
        }
    }
    return 1;
}

int igCompoundMetaField_IsAlikeIgnore(igCompoundMetaField *arg0, int arg1, int arg2) {
    int i;
    for (i = 0; i < ((igMetaFieldList *)arg0->_fieldList)->_count; i++) {
        if (((igMetaFieldView **)((igMetaFieldList *)arg0->_fieldList)->_data)[i]->vfunc_48(arg1, arg2) == 0) {
            return 0;
        }
    }
    return 1;
}

int igCompoundMetaField_WriteRawFieldMem(igCompoundMetaField *arg0, int arg1, int arg2, int arg3, unsigned char arg4) {
    int sum = 0;
    int n;
    int base;
    int i;
    base = arg0->_offset;
    n = ((igMetaFieldList *)arg0->_fieldList)->_count;
    for (i = 0; i < n; i++) {
        igMetaFieldView *e = ((igMetaFieldView **)((igMetaFieldList *)arg0->_fieldList)->_data)[i];
        int o = ((igMetaField *)e)->_offset;
        sum += e->WriteRawFieldMem((arg1 + o) - base, (arg2 + o) - base, arg3, arg4);
    }
    return sum;
}

int igCompoundMetaField_ReadRawFieldMem(igCompoundMetaField *arg0, int arg1, int arg2, int arg3, unsigned char arg4) {
    igMetaFieldView *temp_a0;
    int var_s7;
    int temp_v0;
    int temp_s6;
    int temp_s5;
    int var_s4;

    var_s7 = 0;
    var_s4 = 0;
    temp_s5 = arg0->_offset;
    temp_s6 = ((igMetaFieldList *)arg0->_fieldList)->_count;
    for (; var_s4 < temp_s6; var_s4++) {
        temp_a0 = ((igMetaFieldView **)((igMetaFieldList *)arg0->_fieldList)->_data)[var_s4];
        temp_v0 = ((igMetaField *)temp_a0)->_offset;
        var_s7 += temp_a0->ReadRawFieldMem((arg1 + temp_v0) - temp_s5, (arg2 + temp_v0) - temp_s5, arg3, arg4);
    }
    return var_s7;
}

void igCompoundMetaField_SwapBytes(igMetaFieldView *arg0, int arg1, int arg2) {
    int var_s3;
    igMetaFieldList *temp_s2;
    igMetaFieldView *temp_a0;
    int var_s1;
    int var_s0;

    var_s3 = arg1;
    temp_s2 = (igMetaFieldList *)arg0->vfunc_23()->_fieldList;
    for (var_s1 = 0; var_s1 < arg2; var_s1++) {
        for (var_s0 = 0; var_s0 < temp_s2->_count; var_s0++) {
            temp_a0 = ((igMetaFieldView **)temp_s2->_data)[var_s0];
            temp_a0->SwapBytes((void *)(var_s3 + ((igMetaField *)temp_a0)->_offset), 1);
        }
        var_s3 += ((igCompoundMetaField *)arg0)->_size;
    }
}

int igCompoundMetaField_GetDescriptor(void) {
    return ((int *)DAT_00586920)[0];
}

void igCompoundMetaField_SwapValue(void *arg0, int arg1) {
    int i;
    int *t;
    igMetaFieldView *o;
    i = 0;
    while (t = *(int **)((char *)arg0 + 52), i < t[2]) {
        o = (igMetaFieldView *)(*(int *)(t[4] + (i * 4)));
        o->SwapValue(arg1);
        i += 1;
    }
}

int igCompoundMetaField_ValueFromString(int *arg0, int arg1, int arg2, int arg3) {
    int b;
    int a;
    igMetaFieldList *q;
    int i;

    a = 0;
    sscanf(arg2, &DAT_004f95e8[0], &a);
    q = (igMetaFieldList *)((igMetaFieldView *)arg0)->vfunc_23()->_fieldList;
    for (i = 0; i < q->_count; i++) {
        igMetaFieldView *o = ((igMetaFieldView **)q->_data)[i];
        o->vfunc_56(arg1 + ((igMetaField *)o)->_offset, arg2 + a, arg3);
    }
    sscanf(arg2, &DAT_004f95f0[0], &b);
    return a + b;
}

int igCompoundMetaField_ValueToString(igStringRef *out, igMetaFieldView *ctx, int a2, int a3) {
    char *sepA = (char *)&DAT_004f95f8[0];
    char *sepB = (char *)&DAT_004f9600[0];
    igMetaFieldList *list = (igMetaFieldList *)ctx->vfunc_23()->_fieldList;
    int n = list->_count;
    igStringRef *arr = (igStringRef *)((void *)igObject_Callocate((int)ctx, n, 4));
    int total = 9;
    int i;
    for (i = 0; i < n; i++) {
        int off = i * 4;
        igMetaFieldView *e = ((igMetaFieldView **)list->_data)[i];
        *(igStringRef *)((char *)arr + off) = e->vfunc_57(a2 + ((igMetaField *)e)->_offset, a3);
        total += strlen(((igStringRef *)((char *)arr + off))->p) + 1;
    }
    char *buf = ((char *)igObject_AllocateStorage((int)ctx, total));
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
    igObject_FreeMemory((int)ctx, (int)buf);
    out->p = res.p;
    if (out->p != 0) *(int *)(out->p - 4) = *(int *)(out->p - 4) + 1;
    return 0;
}

void FUN_002d6090(void) {

}

int FUN_002d60a0(void) {
    return 1;
}

void igContext_BuildExtensionInfoList(igContext *arg0) {
    if (arg0->_pExtList == 0) {
        igContextExtInfoList *l;
        int meta;
        int i;
        l = ((igContextExtInfoList *)igContextExtInfoList_Create(((int)igObject_GetAllocator((int)arg0))));
        if (l != 0) ++l->_refCount;
        igRelease((igObject *)arg0->_pExtList);
        arg0->_pExtList = (int)l;
        {
            igContextExtInfoList *o = (igContextExtInfoList *)arg0->_pExtList;
            --o->_refCount;
            if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy((void *)((igObject *)o));
        }
        ((igObjectDispatchView *)arg0)->getMeta();
        meta = igObjectSystem_FindMetaByNameDefault(igContextExt_className);
        arg0->_iNumExts = igMetaObject_CountTree((igMetaObject *)meta) - 1;
        if (arg0->_iNumExts >= ((igContextExtInfoList *)arg0->_pExtList)->_count) List_Reserve((igDataList *)((igContextExtInfoList *)arg0->_pExtList), arg0->_iNumExts, 4);
        ObjectList_ResizeRetained((igTDataList<igObject *> *)((igContextExtInfoList *)arg0->_pExtList), arg0->_iNumExts);
        for (i = 0; i < arg0->_iNumExts; i++) {
            int nm;
            igMetaObject *nd;
            igContextExtInfo *it;
            igContextExtInfoList *lst;
            nd = ((igMetaObject *)igMetaObject_GetTreeNode((igMetaObject *)meta, i + 1));
            it = ((igContextExtInfo *)igContextExtInfo_Create(((int)igObject_GetAllocator((int)arg0))));
            if (nd != 0) ++nd->_refCount;
            igRelease((igObject *)it->_pMeta);
            it->_pMeta = (int)nd;
            nm = nd->_name;
            if (g_stringPool[0] == 0) {
                int al = ((int)StringPool_Allocate(16));
                if (al != 0) al = ((int)StringPool_Construct((StringPool *)al));
                g_stringPool[0] = al;
            }
            {
                int sv = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)nm);
                int old = it->_pName;
                if (old != 0) {
                    int *h = (int *)(old - 8);
                    int c = *(int *)(old - 4) - 1;
                    *(int *)(old - 4) = c;
                    if (c == 0) StringChunk_ReleaseHeader((StringChunk *)(*h), (int)h);
                }
                it->_pName = sv;
            }
            it->_pVendorName = 0;
            lst = (igContextExtInfoList *)arg0->_pExtList;
            if (it != 0) ++it->_refCount;
            igRelease(((igObject **)lst->_data)[i]);
            if (lst->_count != 0 && i >= 0 && i < lst->_count) ((igContextExtInfo **)lst->_data)[i] = it;
            --it->_refCount;
            if ((it->_refCount & 0x7fffff) == 0) igObject_Destroy((void *)((igObject *)it));
        }
    }
}

int FUN_002d6380(void) {
    return ((int *)g_igContext_metaObject)[0];
}

int igContext_GetExtensionInfoList(igContext *arg0) {
    if (arg0->_pExtList == 0) {
        igContext_BuildExtensionInfoList(arg0);
    }
    if (arg0->_iNumExts <= 0) {
        return 0;
    }
    return arg0->_pExtList;
}

int igContext_FindExtensionMeta(igContext *arg0, int arg1) {
    int i;
    bool found;
    igContextExtInfo *e;

    e = 0;
    if (arg0->_pExtList == 0) {
        igContext_BuildExtensionInfoList(arg0);
    }
    i = 0;
    if (arg0->_iNumExts <= 0) {
        return 0;
    }
    found = true;
    while (i < arg0->_iNumExts && found) {
        e = ((igContextExtInfo **)((igContextExtInfoList *)arg0->_pExtList)->_data)[i];
        if (strcmp(e->_pName, arg1) == 0) {
            found = false;
        } else {
            i += 1;
        }
    }
    if ((found & 0xFF) == 1) {
        return 0;
    }
    return e->_pMeta;
}

void *igContext_GetExtension(igVisualContext *arg0, int extra1) {
    int temp_v0;
    igObject *var_s0;

    temp_v0 = igContext_FindExtensionMeta((igContext *)arg0, extra1);
    if (temp_v0 == 0) {
        return 0;
    }
    var_s0 = (igObject *)(((void *)igContext_FindExtensionInstance((igContext *)arg0, temp_v0)));
    if (var_s0 == 0) {
        var_s0 = (igObject *)(((void *)igMetaObject_CreateInstance((igMetaObject *)temp_v0, (igMemoryPoolView *)(((int)igObject_GetAllocator((int)arg0))))));
        if (var_s0 != 0) {
            if (((igContextExtView *)var_s0)->vfunc_28(arg0) == 0) {
                var_s0->_refCount = var_s0->_refCount - 1;
                if ((var_s0->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(var_s0);
                }
                var_s0 = (igObject *)(0);
            } else {
                ObjectList_AppendRetained((igObjectList *)arg0->_pExtInstances, var_s0);
                var_s0->_refCount = var_s0->_refCount - 1;
                if ((var_s0->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(var_s0);
                }
                ((igContextExtView *)var_s0)->vfunc_29(arg0);
            }
        }
    }
    return var_s0;
}

int igContext_FindExtensionInstance(igContext *arg0, int arg1) {
    int i;
    for (i = 0; i < ((igObjectList *)arg0->_pExtInstances)->_count; i++) {
        if (igObject_IsKindOf((void *)((int *)((igObjectList *)arg0->_pExtInstances)->_data)[i], (igMetaObject *)arg1) != 0) {
            return ((int *)((igObjectList *)arg0->_pExtInstances)->_data)[i];
        }
    }
    return 0;
}

