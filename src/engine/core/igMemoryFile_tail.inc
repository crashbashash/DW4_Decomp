void FUN_002efa20(int arg0, int arg1, int arg2) {
    FUN_002c0890();
    if (arg1 != 0) {
        igSmartPointer<igMemoryFileEntry> entry((igMemoryFileEntry *)FUN_002c0b60(((int)igObject_GetAllocator(((int *)DAT_00586f48)[0]))));
        igNamedObject_SetName((igNamedObject *)entry.p, arg0);
        entry->_size = arg2;
        entry->_buffer = arg1;
        ObjectList_AppendRetained((igObjectList *)(((int *)DAT_00586f48)[0]), (igObject *)entry.p);
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

void Gap__Core__igMemoryFile__vfunc_23(int *arg0, igMemoryFileView *self, unsigned int mode) {
    int buffer;
    int size;

    if (self->_bIsOpen != 0) {
        *arg0 = g_resultSuccess.v;
        return;
    }
    if (mode == 8) {
        mode = self->_openMode;
    }
    switch (mode) {
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
        FUN_002efae0((int)self->_fileName, &buffer, &size);
        if (buffer == 0) {
            *arg0 = g_resultFailure.v;
            return;
        }
        self->_iSeekPosition = 0;
        self->_buffer = (char *)buffer;
        self->_iBufferSize = size;
        self->_bIsOpen = 1;
        self->_fileHandle = buffer;
        *arg0 = g_resultSuccess.v;
        return;
    }
}

void Gap__Core__igMemoryFile__vfunc_24(igMemoryFileView *self) {
    self->_bIsOpen = 0;
}

igFileView *Gap__Core__igMemoryFile__vfunc_25(igFileView *arg0, const char *fileName, int arg2) {
    int ok;
    FUN_002e30b0((int *)arg0, fileName);
    if (strcmp(arg2, &DAT_004f96a8[0]) == 0) {
        ok = arg0->vfunc_23(0) == g_resultSuccess;
    } else if (strcmp(arg2, &((int *)DAT_004f9c48)[0]) == 0) {
        ok = arg0->vfunc_23(4) == g_resultSuccess;
    } else {
        return 0;
    }
    return ok ? arg0 : 0;
}

void Gap__Core__igMemoryFile__vfunc_26(igMemoryFileView *self)
{
    self->vfunc_24();
}

int Gap__Core__igMemoryFile__vfunc_27(igMemoryFileView *self, void *buffer, int size, int count) {
    int n;
    int pos;
    int left;

    if (self->_bIsOpen == 0) {
        return -1;
    }
    pos = self->_iSeekPosition;
    n = size * count;
    left = self->_iBufferSize - pos;
    if (left < n) {
        n = left;
    }
    if (n <= 0) {
        return 0;
    }
    memcpy(buffer, self->_buffer + pos, n);
    self->_iSeekPosition += n;
    return n / size;
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

char Gap__Core__igMemoryFile__vfunc_33(igMemoryFileView *self) {
    int temp_a1;
    char r;

    if (self->_bIsOpen == 0) {
        return -1;
    }
    temp_a1 = self->_iSeekPosition;
    if ((self->_iBufferSize - temp_a1) <= 0) {
        return -1;
    }
    r = *(char *)(temp_a1 + (int)self->_buffer);
    self->_iSeekPosition = temp_a1 + 1;
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

int Gap__Core__igMemoryFile__vfunc_38(igMemoryFileView *self, int offset, int whence) {
    int t;
    switch (whence) {
    case 0:
        self->_iSeekPosition = offset;
        break;
    case 1:
        self->_iSeekPosition = self->_iSeekPosition + offset;
        break;
    case 2:
        self->_iSeekPosition = self->_iBufferSize + offset;
        break;
    }
    t = self->_iSeekPosition;
    if (t < 0) return -1;
    return -(self->_iBufferSize < t);
}

/* Accessor: the current read/seek offset into the file's memory buffer (`_iSeekPosition`, +56). */

int Gap__Core__igMemoryFile__vfunc_39(igMemoryFileView *self) {
    return self->_iSeekPosition;
}

/* Vtable slot 34 of igMemoryFile: an unsupported-operation stub returning -1, the error value
 * vfunc_33 (read one byte) returns at end of buffer. The receiver is not touched, hence no
 * parameters. */
int Gap__Core__igMemoryFile__vfunc_34(void) {
    return -1;
}

