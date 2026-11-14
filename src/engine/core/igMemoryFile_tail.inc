void FUN_002efa20(int arg0, int arg1, int arg2) {
    FUN_002c0890();
    if (arg1 != 0) {
        Ref_2efa20 sp4C;
        sp4C.p = (Rc_2efa20 *)FUN_002c0b60(((int)igObject_GetAllocator(((int *)DAT_00586f48)[0])));
        igNamedObject_SetName((igNamedObject *)sp4C.p, arg0);
        sp4C.p->f16 = arg2;
        sp4C.p->f12 = arg1;
        ObjectList_AppendRetained((igObjectList *)(((int *)DAT_00586f48)[0]), (igObject *)sp4C.p);
    }
}

void FUN_002efae0(int arg0, int *arg1, int *arg2) {
    int temp_a0;
    void *temp_v0;

    *arg1 = 0;
    *arg2 = 0;
    temp_a0 = *(int *)0x586F48;
    if (temp_a0 != 0) {
        temp_v0 = ((void *)igProperty_FindByName((igObjectList *)temp_a0, (igMetaField *)(*(int *)0x585BE0), arg0));
        if (temp_v0 != 0) {
            *arg1 = *(int *)((char *)temp_v0 + 12);
            *arg2 = *(int *)((char *)temp_v0 + 16);
        }
    }
}

void Gap__Core__igMemoryFile__vfunc_23(int *arg0, struct MemoryFileHead *arg1, unsigned int arg2) {
    int sp3C;
    int sp38;

    if (arg1->open != 0) {
        *arg0 = g_resultSuccess.v;
        return;
    }
    if (arg2 == 8) {
        arg2 = arg1->f20;
    }
    switch (arg2) {
    case 1:
    case 2:
    case 3:
    case 5:
    case 6:
        *arg0 = g_resultFailure.v;
        return;
    default:
        *arg0 = g_resultFailure.v;
        return;
    case 0:
    case 4:
        FUN_002efae0(arg1->f12, &sp3C, &sp38);
        if (sp3C == 0) {
            *arg0 = g_resultFailure.v;
            return;
        }
        arg1->pos = 0;
        arg1->data = sp3C;
        arg1->size = sp38;
        arg1->open = 1;
        arg1->f24 = sp3C;
        *arg0 = g_resultSuccess.v;
        return;
    }
}

void Gap__Core__igMemoryFile__vfunc_24(void *arg0) {
    *(char *)((char *)(arg0) + 44) = 0;
}

MF_2efc50 *Gap__Core__igMemoryFile__vfunc_25(MF_2efc50 *arg0, const char *fileName, int arg2) {
    int ok;
    FUN_002e30b0((int *)arg0, fileName);
    if (strcmp(arg2, &DAT_004f96a8[0]) == 0) {
        ok = arg0->vX(0).Ok();
    } else if (strcmp(arg2, &((int *)DAT_004f9c48)[0]) == 0) {
        ok = arg0->vX(4).Ok();
    } else {
        return 0;
    }
    return ok ? arg0 : 0;
}

void Gap__Core__igMemoryFile__vfunc_26(igMemoryFileView *self)
{
    self->vfunc_22();
}

int Gap__Core__igMemoryFile__vfunc_27(struct MemoryFileBody *arg0, void *arg1, int arg2, int arg3) {
    int n; 
    int pos; 
    int left; 

    if (arg0->open == 0) {
        return -1;
    }
    pos = arg0->pos;
    n = arg2 * arg3;
    left = arg0->size - pos;
    if (left < n) {
        n = left;
    }
    if (n <= 0) {
        return 0;
    }
    memcpy(arg1, arg0->data + pos, n);
    arg0->pos += n;
    return n / arg2;
}

/* Vtable slot 29 of igMemoryFile: an unsupported-operation stub returning -1, the error value
 * vfunc_33 (read one byte) returns at end of buffer. The receiver is not touched, hence no
 * parameters. */
int Gap__Core__igMemoryFile__vfunc_29(void) {
    return -1;
}

int Gap__Core__igMemoryFile__vfunc_30(void *arg0, int arg1, ...) {
    return -1;
}

int Gap__Core__igMemoryFile__vfunc_31(int a, int b, ...) {
    return -1;
}

/* Vtable slot 32 of igMemoryFile: a stub returning 0 (success, nothing to do) for an operation a
 * buffer-backed file does not need. The receiver is not touched, hence no parameters. */
int Gap__Core__igMemoryFile__vfunc_32(void) {
    return 0;
}

char Gap__Core__igMemoryFile__vfunc_33(S_2efe60 *arg0) {
    int temp_a1;
    char r;

    if (arg0->f2C == 0) {
        return -1;
    }
    temp_a1 = arg0->f38;
    if ((arg0->f34 - temp_a1) <= 0) {
        return -1;
    }
    r = *(char *)(temp_a1 + arg0->f30);
    arg0->f38 = temp_a1 + 1;
    return r;
}

/* Vtable slot 35 of igMemoryFile: an unsupported-operation stub returning -1, the error value
 * vfunc_33 (read one byte) returns at end of buffer. The receiver is not touched, hence no
 * parameters. */
int Gap__Core__igMemoryFile__vfunc_35(void) {
    return -1;
}

/* Vtable slot 36 of igMemoryFile: a stub returning 0 (success, nothing to do) for an operation a
 * buffer-backed file does not need. The receiver is not touched, hence no parameters. */
int Gap__Core__igMemoryFile__vfunc_36(void) {
    return 0;
}

/* Vtable slot 37 of igMemoryFile: an unsupported-operation stub returning -1, the error value
 * vfunc_33 (read one byte) returns at end of buffer. The receiver is not touched, hence no
 * parameters. */
int Gap__Core__igMemoryFile__vfunc_37(void) {
    return -1;
}

int Gap__Core__igMemoryFile__vfunc_38(int *arg0, int arg1, int arg2) {
    int t;
    switch (arg2) {
    case 0:
        arg0[14] = arg1;
        break;
    case 1:
        arg0[14] = arg0[14] + arg1;
        break;
    case 2:
        arg0[14] = arg0[13] + arg1;
        break;
    }
    t = arg0[14];
    if (t < 0) return -1;
    return -(arg0[13] < t);
}

/* Accessor: the current read/seek offset into the file's memory buffer (`_iSeekPosition`, +56). */

int Gap__Core__igMemoryFile__vfunc_39(igMemoryFile *self) {
    return self->_iSeekPosition;
}

/* Vtable slot 34 of igMemoryFile: an unsupported-operation stub returning -1, the error value
 * vfunc_33 (read one byte) returns at end of buffer. The receiver is not touched, hence no
 * parameters. */
int Gap__Core__igMemoryFile__vfunc_34(void) {
    return -1;
}

