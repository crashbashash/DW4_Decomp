void igProgramFile_Reset(igProgramFile *self) {
    int *header;
    int count;
    int pool;
    char *oldName;
    igFileView *file;
    char *name;

    if (g_stringPool == 0) {
        pool = ((int)StringPool_Allocate(0x10));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool = (StringPool *)pool;
    }
    name = (char *)StringPool_Intern((StringPool *)g_stringPool, (const char *)0);
    oldName = (char *)self->_fileName;
    if (oldName != 0) {
        header = (int *)(oldName - 8);
        count = *(int *)(oldName - 4) - 1;
        *(int *)(oldName - 4) = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
        }
    }
    self->_fileName = (int)name;
    file = (igFileView *)self->_file;
    if (file != 0) {
        --file->_refCount;
        if (((unsigned long long)(long long)(int)file->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(file);
        }
    }
    self->_file = 0;
}

igResult igProgramFile_Open(igProgramFile *self, const char *path) {
    ProgramFileView *file = (ProgramFileView *)self;
    int pool;
    int allocator;
    int *old;
    int *header;
    int name;
    igFileView *stream;
    int refs;
    file->Reset();
    if (g_stringPool == 0) {
        pool = (int)StringPool_Allocate(0x10);
        if (pool != 0) {
            pool = (int)StringPool_Construct((StringPool *)pool);
        }
        g_stringPool = (StringPool *)pool;
    }
    name = (int)StringPool_Intern((StringPool *)g_stringPool, path);
    old = (int *)file->path;
    if (old != 0) {
        header = old - 2;
        refs = old[-1] - 1;
        old[-1] = refs;
        if (refs == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
        }
    }
    file->path = (const char *)name;
    allocator = (int)igObject_GetAllocator((igObject *)self);
    stream = file->stream;
    if (stream != 0) {
        stream->_refCount = stream->_refCount - 1;
        if (((unsigned long long)(long long)(int)stream->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(stream);
        }
    }
    file->stream = (igFileView *)igFile_Create(allocator);
    igFile_SetFileName((igFile *)file->stream, file->path);
    if (file->stream->OpenWithMode(4) == g_resultFailure) {
        igReport_Printf((const char *)"Unable to open: %s\n", (int)file->path);
        igReport_Flush();
        return g_resultFailure;
    }
    return g_resultSuccess;
}

void igProgramFile_Close(int *result, ProgramFileView *self) {
    self->stream->CloseHandle();
    self->Reset();
    *result = g_resultSuccess.v;
}

void igProgramFile_Load(int *result, ProgramFileView *self, int offset, int size, void **dest) {
    igFileView *stream;
    stream = self->stream;
    if (stream->Seek(offset, 0) == -1) {
        igReport_Printf("Error seeking to offset 0x%x in: %s\n", offset, self->path);
        igReport_Flush();
        self->Close();
        *result = g_resultFailure.v;
        return;
    }
    if (*dest == 0) {
        *dest = (void *)((Gap::Core::igObject *)self)->malloc(size);
        if (*dest == 0) {
            igReport_Printf("Error allocating buffer size 0x%x in: %s\n", size, self->path);
            igReport_Flush();
            self->Close();
            *result = g_resultFailure.v;
            return;
        }
    }
    memset(*dest, 0, size);
    stream = self->stream;
    if (stream->Read(*dest, size, 1) != 1) {
        igReport_Printf("Error reading: %s\n", self->path);
        igReport_Flush();
        self->Close();
        *result = g_resultFailure.v;
        return;
    }
    *result = g_resultSuccess.v;
}

/* igProgramFile vtable slot 27: status leaf. Ignores the object and writes the engine's current
 * failure-status word (the one an allocation failure publishes) through the output-first argument;
 * the same leaf as igPsx2Window slot 40. */
void igProgramFile_LoadSymbols(int *status_out) {
    *status_out = g_resultFailure.v;
}

/* igProgramFile vtable slot 28: status leaf, the same body as slot 27. */
void igProgramFile_LoadSymbolTable(int *status_out) {
    *status_out = g_resultFailure.v;
}

/* igProgramFile vtable slot 29: status leaf, the same body as slot 27. */
void igProgramFile_Demangle(int *status_out) {
    *status_out = g_resultFailure.v;
}

void igProgramFile_PrintHeader(igProgramFile *self) {
}

void igProgramFile_PrintSectionHeaders(igProgramFile *self) {
}

void igProgramFile_PrintSymbols(igProgramFile *self) {
}

