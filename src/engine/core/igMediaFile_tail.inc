/* Opens the file in `mode` (0-3 text, 4-7 binary: read, write, append, read-write; 8 read). A relative
 * name is tried under each entry of the search path list until a device opens it. A text file is read
 * whole into the buffer. */
void igMediaFile_OpenWithMode(int *result, igMediaFileView *file, unsigned int mode) {
    char *searchPaths;
    char path[512];
    bool absolute;
    igMediaView *media;
    igMediaView *previous;
    int status;
    char *p;
    unsigned int n;

    if (file->_isOpen == 1) {
        *result = g_resultFailure.v;
        return;
    }
    file->_openMode = mode;
    switch (file->_openMode) {
    case 0: case 1: case 2: case 3: case 8:
        file->_isBinary = 0;
        break;
    case 4: case 5: case 6: case 7:
        file->_isBinary = 1;
        break;
    }
    switch (file->_openMode) {
    case 1: case 5: file->_write = 1; file->_read = 0; break;
    case 2: case 6: file->_write = 1; file->_read = 0; break;
    case 3: case 7: file->_write = 1; file->_read = 1; break;
    case 0: case 4: case 8: file->_write = 0; file->_read = 1; break;
    }
    file->_bufSize = 0;
    p = path;
    file->_bufPos = 0;
    n = sizeof(path);
    if (p != 0) {
        do {
            *p = 0;
            n -= 1;
            p += 1;
        } while (n != 0);
    }
    absolute = FilePath_IsAbsolute(file->_fileName);
    searchPaths = (char *)igAdxFile_GetSearchPaths();
    status = g_resultFailure.v;
    while (searchPaths != 0) {
        if (absolute) {
            path[0] = 0;
            searchPaths = 0;
        } else if (!igAdxFile_GetNextSearchPath(&searchPaths, path, sizeof(path))) {
            continue;
        }
        strcat(path, file->_fileName);
        previous = file->_media;
        media = igMediaFile_FindDeviceForPath(path);
        if (media != 0) {
            media->_refCount = media->_refCount + 1;
        }
        RELEASE_REF(file->_media);
        file->_media = media;
        if (file->_media == 0) break;
        if (file->_media != previous) {
            if (previous != 0) {
                previous->freeHandle(file->_fileHandle);
            }
            file->_fileHandle = file->_media->vfunc_23();
        }
        status = file->_media->vfunc_25(file->_fileHandle, path, file->_openMode).v;
        if (status == g_resultSuccess.v) break;
    }
    if (status == g_resultFailure.v) {
        if (GPR_00554c10 == 0) {
            int rc = igReport_Detail(DAT_004f9bd0, file->_fileName);
            if (rc != 1 && rc == 2) {
                GPR_00554c10 = 1;
            }
        }
        if (file->_media != 0) {
            file->_media->freeHandle(file->_fileHandle);
            RELEASE_REF(file->_media);
            file->_media = 0;
        }
        *result = g_resultFailure.v;
    } else {
        file->_media->seek(file->_fileHandle, 0, 2);
        file->_fileSize = file->_media->tell(file->_fileHandle);
        file->_media->seek(file->_fileHandle, 0, 0);
        if (file->_isBinary == 0) {
            igMediaFile_SetFileSize(file, file->_fileSize);
            if (file->_fileSize > 0) {
                int count = file->_media->read(file->_fileHandle, file->_fBuf, file->_fileSize);
                if (count != file->_fileSize) {
                    file->_fileSize = count;
                    igMediaFile_SetFileSize(file, count);
                }
            }
        }
        if (file->_openMode == 2) {
            file->_bufPos = file->_fileSize;
        } else {
            file->_bufPos = 0;
        }
        file->_isOpen = 1;
        *result = g_resultSuccess.v;
    }
}

void igMediaFile_Close(igMediaFileView *self) {
    igMediaView *media;

    if (self->_isOpen != 0) {
        self->flush();
        self->_media->close(self->_fileHandle);
        self->_media->freeHandle(self->_fileHandle);
        media = self->_media;
        REL(media)
        self->_media = 0;
        self->_fileHandle = -1;
        igObject_FreeMemory((int)self, (int)self->_fBuf);
        self->_fBuf = 0;
        self->_bufSize = 0;
        self->_bufPos = 0;
        self->_isOpen = 0;
    }
}

void **igMediaFile_OpenFile(void **self, const char *fileName, int mode) {
    igResult readResult;
    igResult readBinaryResult;
    igResult writeResult;
    igResult writeBinaryResult;
    igResult updateResult;
    igResult updateBinaryResult;
    igResult appendResult;
    igResult appendBinaryResult;
    int status;

    igFile_SetFileName((int *)self, fileName);
    if (strcmp(mode, &text_r[0]) == 0) {
        readResult = ((igFileView *)(self))->openWithMode((int)(0));
        status = readResult.v;
        goto opened;
    }
    if (strcmp(mode, (int *)text_rb) == 0) {
        readBinaryResult = ((igFileView *)(self))->openWithMode((int)(4));
        status = readBinaryResult.v;
        goto opened;
    }
    if (strcmp(mode, (int *)((char *)text_w)) == 0) {
        writeResult = ((igFileView *)(self))->openWithMode((int)(1));
        status = writeResult.v;
        goto opened;
    }
    if (strcmp(mode, (int *)((char *)text_wb)) == 0) {
        writeBinaryResult = ((igFileView *)(self))->openWithMode((int)(5));
        status = writeBinaryResult.v;
        goto opened;
    }
    if ((strcmp(mode, (int *)text_r_plus) == 0) || (strcmp(mode, &text_w_plus[0]) == 0)) {
        updateResult = ((igFileView *)(self))->openWithMode((int)(3));
        status = updateResult.v;
        goto opened;
    }
    if ((strcmp(mode, (int *)text_r_plus_b) == 0) || (strcmp(mode, &text_w_plus_b[0]) == 0)) {
        updateBinaryResult = ((igFileView *)(self))->openWithMode((int)(7));
        status = updateBinaryResult.v;
        goto opened;
    }
    if ((strcmp(mode, (int *)text_a) == 0) || (strcmp(mode, &text_a_plus[0]) == 0)) {
        appendResult = ((igFileView *)(self))->openWithMode((int)(2));
        status = appendResult.v;
        goto opened;
    }
    if ((strcmp(mode, (int *)text_ab) == 0) || (strcmp(mode, &text_a_plus_b[0]) == 0)) {
        appendBinaryResult = ((igFileView *)(self))->openWithMode((int)(6));
        status = appendBinaryResult.v;
        goto opened;
    }
    return 0;
opened:
    return status == g_resultFailure.v ? 0 : self;
}

void igMediaFile_CloseFile(igMediaFileView *self)
{
    self->closeHandle();
}

void igMediaFile_SetFileSize(igMediaFileView *self, int size) {
    int buffer;
    int capacity;
    int storage;
    if (self->_bufSize < size) {
        capacity = size * 2;
        if (size > 0x100000) {
            capacity = size + 0x100000;
        }
        buffer = (int)self->_fBuf;
        if (buffer != 0) {
            storage = igObject_Reallocate((int)self, buffer, capacity);
        } else {
            storage = igObject_AllocateStorage((int)self, capacity);
        }
        self->_fBuf = (unsigned char *)storage;
        self->_bufSize = capacity;
    }
    self->_fileSize = size;
}

int igMediaFile_Read(igMediaFileView *self, int buffer, int size, int count) {
    int bytes;
    int got;
    int n;
    int cnt;
    int back;
    if (self->_isOpen == 0) {
        return -1;
    }
    bytes = size * count;
    if (self->_isBinary == 1) {
        got = self->_media->read(self->_fileHandle, (void *)buffer, (unsigned)count * size);
        n = got / size;
        back = n * size;
        if (got != back) {
            self->_media->seek(self->_fileHandle, back - got, 1);
        }
        return n;
    }
    cnt = count;
    if (self->_fileSize < self->_bufPos + bytes) {
        cnt = (self->_fileSize - self->_bufPos) / size;
        bytes = cnt * size;
    }
    memcpy(buffer, self->_fBuf + self->_bufPos, bytes, self->_bufPos);
    self->_bufPos = self->_bufPos + bytes;
    return cnt;
}

void igMediaFile_ReadAsync(igMediaFileView *self, int buffer, int size, int (*done)(int, int), int context) {
    if (self->_isOpen == 0) {
        done(context, -1);
    }
    if (self->_isBinary == 1) {
        self->_media->readAsync(self->_fileHandle, (void *)buffer, size, done, context);
    }
    done(context, self->Read((void *)buffer, 1, size));
}

int igMediaFile_Write(igMediaFileView *self, int buffer, int size, int count) {
    int bytes;
    if (self->_isOpen == 0) {
        return -1;
    }
    if (size == 0) {
        return 0;
    }
    if (self->_isBinary == 1) {
        if (self->_openMode == 6) {
            self->_media->seek(self->_fileHandle, 0, 2);
        }
        return self->_media->write(self->_fileHandle, (const void *)buffer, count * size) / size;
    }
    bytes = size * count;
    if (self->_openMode == 2) {
        self->_bufPos = self->_fileSize;
    }
    igMediaFile_SetFileSize(self, self->_bufPos + bytes);
    memcpy(self->_fBuf + self->_bufPos, buffer, bytes);
    self->_bufPos = self->_bufPos + bytes;
    return bytes / size;
}

int igMediaFile_Flush(igMediaFileView *self) {
    if (self->_isBinary != 0) {
        return 0;
    }
    if (self->_write != 0) {
        self->_media->seek(self->_fileHandle, 0, 0);
        self->_media->write(self->_fileHandle, self->_fBuf, self->_fileSize);
    }
    return 0;
}

static inline int isSpace(int c) { return _ctype_[c + 1] & 8; }

int igMediaFile_Scanf(igMediaFileView *self, const char *format, ...) {
    char *args;
    int n;
    int off;
    int length;
    int i;
    int count;
    if (self->_isBinary != 0) {
        return -1;
    }
    n = __builtin_args_info(2);
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    args = (char *)__builtin_next_arg(format) - off;
    if (format == 0) {
        return 0;
    }
    length = strlen(format);
    i = 0;
    count = 0;
    while (i < length) {
        char piece[512];
        int state = 0;
        int used = 0;
        while (!state) {
            if (i == length) {
                state = 1;
                continue;
            }
            if (format[i] != '%') {
                piece[used++] = format[i];
                i++;
            } else if (format[i] == '%' && format[i + 1] == '%') {
                piece[used] = format[i];
                piece[used + 1] = format[i + 1];
                i += 2;
                used += 2;
            } else if (format[i] == '%') {
                int space;
                int c;
                piece[used++] = format[i];
                i++;
                /* matching construct: variant test — the c-g and n-p ranges as unsigned differences */
                while (!(space = isSpace(c = format[i])) && c != 'u' && c != 'x' && c != 'i' && c != 's' &&
                       c != 'S' && (unsigned)(c - 'c') > 4 && c != 'C' && c != ']' && (unsigned)(c - 'n') > 2 &&
                       i != length) {
                    piece[used++] = c;
                    i++;
                }
                if (!space) {
                    piece[used++] = c;
                    i++;
                }
                state = 2;
            }
        }
        piece[used] = 0;
        strcat(piece, "%n");
        if (state == 1) {
            int consumed = 0;
            sscanf(self->_fBuf + self->_bufPos, piece, &consumed);
            self->_bufPos += consumed;
        } else {
            void *target;
            args += 8;
            target = *(void **)(args - 8);
            int consumed = 0;
            int matched = sscanf(self->_fBuf + self->_bufPos, piece, target, &consumed);
            if (matched == -1) {
                break;
            }
            count += matched;
            self->_bufPos += consumed;
        }
    }
    return count;
}

int igMediaFile_Printf(igMediaFileView *self, int fmt, ...) {
    char buf[16384];
    int n;
    int off;
    int len;
    int pos;
    if (self->_isBinary != 0) {
        return -1;
    }
    n = __builtin_args_info(2);
    if (n >= 8) {
        off = 0;
    } else {
        off = (8 - n) * 8;
    }
    len = vsprintf(buf, fmt, (char *)__builtin_next_arg(fmt) - off);
    pos = self->_bufPos + len;
    if (pos >= self->_fileSize) {
        igMediaFile_SetFileSize(self, pos);
    }
    memcpy(self->_fBuf + self->_bufPos, buf, len);
    self->_bufPos = self->_bufPos + len;
    return len;
}

int igMediaFile_GetChar(igMediaFileView *self) {
    int c;
    int position;
    if (self->_isBinary != 0) {
        unsigned int handle = self->_fileHandle;
        igMediaView *media = self->_media;
        if (media->read(handle, &c, 1) != 0) {
            return c;
        }
        return -1;
    }
    position = self->_bufPos;
    if (position >= self->_fileSize) {
        return -1;
    }
    self->_bufPos = position + 1;
    return self->_fBuf[self->_bufPos - 1];
}

int igMediaFile_UngetChar(igMediaFileView *a, int c) {
    int n;
    if (a->_isBinary != 0) return -1;
    n = a->_bufPos;
    if (n == 0) return -1;
    a->_bufPos = n - 1;
    if ((c & 0xff) != a->_fBuf[a->_bufPos]) c = -1;
    return c;
}

int igMediaFile_PutChar(igMediaFileView *self, unsigned char c) {
    int end;

    if (self->_isBinary != 0) {
        return -1;
    }
    end = self->_bufPos + 1;
    if (end >= self->_fileSize) {
        igMediaFile_SetFileSize(self, end);
    }
    self->_fBuf[self->_bufPos] = c;
    self->_bufPos = self->_bufPos + 1;
    return c;
}

char *igMediaFile_GetString(igMediaFileView *self, char *buffer, int size) {
    if (buffer == 0) return 0;
    if (self->_isBinary != 0) return 0;
    if (self->_bufPos >= self->_fileSize) return 0;
    int i = 0;
    size = size - 1;
    if (size + self->_bufPos >= self->_fileSize) size = self->_fileSize - self->_bufPos;
    while (i < size) {
        unsigned char c = self->_fBuf[self->_bufPos];
        buffer[i] = c;
        i++;
        self->_bufPos = self->_bufPos + 1;
        if (c == 10) break;
    }
    buffer[i] = 0;
    return buffer;
}

int igMediaFile_PutString(igMediaFileView *self, int string) {
    int end;
    int length;

    if (string == 0) {
        return -1;
    }
    if (self->_isBinary != 0) {
        return -1;
    }
    length = strlen(string);
    end = self->_bufPos + length;
    if (end >= self->_fileSize) {
        igMediaFile_SetFileSize(self, end);
    }
    memcpy(self->_fBuf + self->_bufPos, string, length);
    self->_bufPos = self->_bufPos + length;
    return length;
}

int igMediaFile_Seek(igMediaFileView *self, int offset, int whence) {
    int base;
    int cur;
    if (self->_isBinary != 0) {
        base = self->tell();
        if (self->_media->seek(self->_fileHandle, offset, whence) != 0) {
            return 0;
        }
        cur = self->tell();
        switch (whence) {
        case 0:
            return -(cur != offset);
        case 1:
            return -(offset != cur - base);
        case 2:
            return 0;
        default:
            return -1;
        }
    } else {
        switch (whence) {
        case 0:
            self->_bufPos = offset;
            break;
        case 1:
            self->_bufPos = self->_bufPos + offset;
            break;
        case 2:
            self->_bufPos = self->_fileSize + offset;
            break;
        default:
            return -1;
        }
        if (self->_bufPos > self->_fileSize) {
            self->_bufPos = self->_fileSize;
        } else if (self->_bufPos < 0) {
            self->_bufPos = 0;
        }
        return 0;
    }
}

int igMediaFile_Tell(igMediaFileView *p) { if (p->_isBinary) { unsigned int a = p->_fileHandle; igMediaView *o = p->_media; return o->tell(a); } return p->_bufPos; }
