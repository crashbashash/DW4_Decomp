void igMemoryFile_AddMemoryFileEntry(int name, int buffer, int size) {
    igMemoryFile_EnsureRegistered();
    if (buffer != 0) {
        igSmartPointer<igMemoryFileEntry> entry((igMemoryFileEntry *)igMemoryFileEntry_Create(((int)igObject_GetAllocator((*(int *)&g_memoryFileEntries)))));
        igNamedObject_SetName((igNamedObject *)entry.p, name);
        entry->_size = size;
        entry->_buffer = buffer;
        ObjectList_AppendRetained((igObjectList *)((*(int *)&g_memoryFileEntries)), (igObject *)entry.p);
    }
}

void igMemoryFile_LookupMemoryBuffer(int name, int *buffer, int *size) {
    int entries;
    igMemoryFileEntry *entry;

    *buffer = 0;
    *size = 0;
    entries = (*(int *)&g_memoryFileEntries);
    if (entries != 0) {
        entry = ((igMemoryFileEntry *)igProperty_FindByName((igObjectList *)entries, (igMetaField *)g_propertyNameField, name));
        if (entry != 0) {
            *buffer = entry->_buffer;
            *size = entry->_size;
        }
    }
}

void igMemoryFile_OpenWithMode(int *result, igMemoryFileView *self, unsigned int mode) {
    int buffer;
    int size;

    if (self->_bIsOpen != 0) {
        *result = g_resultSuccess.v;
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
        *result = g_resultFailure.v;
        return;
    default:
        *result = g_resultFailure.v;
        return;
    case 0:
    case 4:
        igMemoryFile_LookupMemoryBuffer((int)self->_fileName, &buffer, &size);
        if (buffer == 0) {
            *result = g_resultFailure.v;
            return;
        }
        self->_iSeekPosition = 0;
        self->_buffer = (char *)buffer;
        self->_iBufferSize = size;
        self->_bIsOpen = 1;
        self->_fileHandle = buffer;
        *result = g_resultSuccess.v;
        return;
    }
}

void igMemoryFile_Close(igMemoryFileView *self) {
    self->_bIsOpen = 0;
}

igFileView *igMemoryFile_OpenFile(igFileView *self, const char *fileName, int mode) {
    int ok;
    igFile_SetFileName((int *)self, fileName);
    if (strcmp(mode, "r") == 0) {
        ok = self->OpenWithMode(0) == g_resultSuccess;
    } else if (strcmp(mode, &((int *)"rb")[0]) == 0) {
        ok = self->OpenWithMode(4) == g_resultSuccess;
    } else {
        return 0;
    }
    return ok ? self : 0;
}

void igMemoryFile_CloseFile(igMemoryFileView *self)
{
    self->CloseHandle();
}

int igMemoryFile_Read(igMemoryFileView *self, void *buffer, int size, int count) {
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
int igMemoryFile_Write(void) {
    return -1;
}

int igMemoryFile_Scanf(void *self, int format, ...) {
    return -1;
}

int igMemoryFile_Printf(int a, int b, ...) {
    return -1;
}

/* Vtable slot 32 of igMemoryFile: a stub returning 0 (success, nothing to do) for an operation a
 * buffer-backed file does not need. The receiver is not touched, hence no parameters. */
int igMemoryFile_Flush(void) {
    return 0;
}

char igMemoryFile_GetChar(igMemoryFileView *self) {
    int position;
    char r;

    if (self->_bIsOpen == 0) {
        return -1;
    }
    position = self->_iSeekPosition;
    if ((self->_iBufferSize - position) <= 0) {
        return -1;
    }
    r = *(char *)(position + (int)self->_buffer);
    self->_iSeekPosition = position + 1;
    return r;
}

/* Vtable slot 35 of igMemoryFile: an unsupported-operation stub returning -1, the error value
 * vfunc_33 (read one byte) returns at end of buffer. The receiver is not touched, hence no
 * parameters. */
int igMemoryFile_PutChar(void) {
    return -1;
}

/* Vtable slot 36 of igMemoryFile: a stub returning 0 (success, nothing to do) for an operation a
 * buffer-backed file does not need. The receiver is not touched, hence no parameters. */
int igMemoryFile_GetString(void) {
    return 0;
}

/* Vtable slot 37 of igMemoryFile: an unsupported-operation stub returning -1, the error value
 * vfunc_33 (read one byte) returns at end of buffer. The receiver is not touched, hence no
 * parameters. */
int igMemoryFile_PutString(void) {
    return -1;
}

int igMemoryFile_Seek(igMemoryFileView *self, int offset, int whence) {
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

int igMemoryFile_Tell(igMemoryFileView *self) {
    return self->_iSeekPosition;
}

/* Vtable slot 34 of igMemoryFile: an unsupported-operation stub returning -1, the error value
 * vfunc_33 (read one byte) returns at end of buffer. The receiver is not touched, hence no
 * parameters. */
int igMemoryFile_UngetChar(void) {
    return -1;
}

