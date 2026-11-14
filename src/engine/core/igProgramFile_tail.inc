void Gap__Core__igProgramFile__vfunc_23(igProgramFile *arg0) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    char *temp_a0;
    igFileView *temp_a0_2;
    char *temp_s1;

    if (g_stringPool[0] == 0) {
        var_v0 = ((int)StringPool_Allocate(0x10));
        if (var_v0 != 0) {
            var_v0 = ((int)StringPool_Construct((StringPool *)var_v0));
        }
        g_stringPool[0] = var_v0;
    }
    temp_s1 = (char *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)0);
    temp_a0 = (char *)arg0->_fileName;
    if (temp_a0 != 0) {
        temp_a1 = (int *)(temp_a0 - 8);
        temp_v1 = *(int *)(temp_a0 - 4) - 1;
        *(int *)(temp_a0 - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
        }
    }
    arg0->_fileName = (int)temp_s1;
    temp_a0_2 = (igFileView *)arg0->_file;
    if (temp_a0_2 != 0) {
        --temp_a0_2->_refCount;
        if (((unsigned long long)(long long)(int)temp_a0_2->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(temp_a0_2);
        }
    }
    arg0->_file = 0;
}

igResult Gap__Core__igProgramFile__vfunc_24(igProgramFile *self, const char *path) {
    ProgramFileView *file = (ProgramFileView *)self;
    int pool;
    int allocator;
    int *old;
    int *header;
    int name;
    igFileView *stream;
    int refs;
    file->Reset();
    if (g_stringPool[0] == 0) {
        pool = (int)StringPool_Allocate(0x10);
        if (pool != 0) {
            pool = (int)StringPool_Construct((StringPool *)pool);
        }
        g_stringPool[0] = pool;
    }
    name = StringPool_Intern((StringPool *)g_stringPool[0], path);
    old = (int *)file->path;
    if (old != 0) {
        header = old - 2;
        refs = old[-1] - 1;
        old[-1] = refs;
        if (refs == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*header, (int)header);
        }
    }
    file->path = (const char *)name;
    allocator = (int)igObject_GetAllocator((int)self);
    stream = file->stream;
    if (stream != 0) {
        stream->_refCount = stream->_refCount - 1;
        if (((unsigned long long)(long long)(int)stream->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(stream);
        }
    }
    file->stream = (igFileView *)igFile_Create(allocator);
    FUN_002e30b0((int *)file->stream, file->path);
    if (file->stream->vfunc_23(4) == g_resultFailure) {
        FUN_00304430((const char *)&DAT_004ff4f0[0], (int)file->path);
        FUN_00304680();
        return g_resultFailure;
    }
    return g_resultSuccess;
}

void Gap__Core__igProgramFile__vfunc_25(int *result, ProgramFileView *self) {
    self->stream->vfunc_24();
    self->Reset();
    *result = g_resultSuccess.v;
}

void Gap__Core__igProgramFile__vfunc_26(int *result, ProgramFileView *self, int offset, int size, void **dest) {
    igFileView *stream;
    stream = self->stream;
    if (stream->Seek(offset, 0) == -1) {
        FUN_00304430(DAT_004ff510, offset, self->path);
        FUN_00304680();
        self->Close();
        *result = g_resultFailure.v;
        return;
    }
    if (*dest == 0) {
        *dest = (void *)igObject_AllocateStorage((int)self, size);
        if (*dest == 0) {
            FUN_00304430(DAT_004ff540, size, self->path);
            FUN_00304680();
            self->Close();
            *result = g_resultFailure.v;
            return;
        }
    }
    memset(*dest, 0, size);
    stream = self->stream;
    if (stream->Read(*dest, size, 1) != 1) {
        FUN_00304430(DAT_004fdda0, self->path);
        FUN_00304680();
        self->Close();
        *result = g_resultFailure.v;
        return;
    }
    *result = g_resultSuccess.v;
}

/* igProgramFile vtable slot 27: status leaf. Ignores the object and writes the engine's current
 * failure-status word (the one an allocation failure publishes) through the output-first argument;
 * the same leaf as igPsx2Window slot 40. */
void Gap__Core__igProgramFile__vfunc_27(int *status_out) {
    *status_out = g_resultFailure.v;
}

/* igProgramFile vtable slot 28: status leaf, the same body as slot 27. */
void Gap__Core__igProgramFile__vfunc_28(int *status_out) {
    *status_out = g_resultFailure.v;
}

/* igProgramFile vtable slot 29: status leaf, the same body as slot 27. */
void Gap__Core__igProgramFile__vfunc_29(int *status_out) {
    *status_out = g_resultFailure.v;
}

void Gap__Core__igProgramFile__vfunc_30(igProgramFile *self) {
}

void Gap__Core__igProgramFile__vfunc_31(igProgramFile *self) {
}

void Gap__Core__igProgramFile__vfunc_32(igProgramFile *self) {
}

