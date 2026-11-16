/* Opens the file in `mode` (0-3 text, 4-7 binary: read, write, append, read-write; 8 the mode it
 * was last opened in). A relative name is tried under each entry of the search path list in turn.
 * A text file is read whole into the buffer. */
void igPsx2File_OpenWithMode(int *result, igPsx2FileView *file, unsigned int mode) {
    char *searchPaths;
    char path[512];
    bool absolute;
    int flags;
    unsigned char more;
    int attempt;
    int retries;
    char *devicePath;
    int hasDirectory;
    int fd;
    char *p;
    unsigned int n;
    int size;
    flags = 0;
    if (mode == 8) mode = file->_openMode;
    if (file->_isOpen == 1 && file->_openMode == mode) {
        *result = g_resultSuccess.v;
    } else {
        switch (mode) {
        case 0: case 1: case 2: case 3: case 8:
            file->_isBinary = 0;
            break;
        case 4: case 5: case 6: case 7:
            file->_isBinary = 1;
            break;
        }
        switch (mode) {
        case 1: case 5: flags = SCE_TRUNC | SCE_CREAT | SCE_WRONLY; break;
        case 2: case 6: flags = SCE_CREAT | SCE_APPEND; break;
        case 3: case 7: flags = SCE_CREAT | SCE_RDWR; break;
        case 0: case 4: case 8: flags = SCE_RDONLY; break;
        }
        file->_bufSize = 0;
        p = path;
        file->_bufPos = 0;
        n = sizeof(path);
        file->_isOpen = 0;
        if (p != 0) {
            do {
                *p = 0;
                n -= 1;
                p += 1;
            } while (n != 0);
        }
        more = 1;
        absolute = FilePath_IsAbsolute(file->_fileName);
        hasDirectory = FilePath_HasDirectory(file->_fileName);
        searchPaths = (char *)igAdxFile_GetSearchPaths();
        attempt = 0;
        while (more && attempt < 0x100) {
            if (absolute) {
                path[0] = 0;
                more = 0;
                goto open;
            }
            if (hasDirectory != 0) {
                path[0] = 0;
                hasDirectory = 0;
                goto open;
            }
            more = igAdxFile_GetNextSearchPath(&searchPaths, path, sizeof(path));
            if (more) {
open:
                strcat(path, file->_fileName);
                devicePath = file->MakeCompleteFilename(path);
                if (*devicePath == 'c') {
                    retries = 10;
                    while ((fd = sceOpen(devicePath, flags)) < 0 && retries != 0) {
                        retries -= 1;
                    }
                } else {
                    fd = sceOpen(devicePath, flags, 0666);
                }
                file->_fileHandle = fd;
                if (!(0 > fd)) break;
            }
            attempt += 1;
        }
        if (file->_fileHandle < 0) {
            *result = g_resultFailure.v;
        } else {
            if (mode == 6) sceLseek(file->_fileHandle, 0, SCE_SEEK_END);
            if (file->_isBinary == 0) {
                size = sceLseek(file->_fileHandle, 0, SCE_SEEK_END);
                igPsx2File_GrowBuffer(file, size);
                sceLseek(file->_fileHandle, 0, SCE_SEEK_SET);
                if (size > 0) {
                    fd = sceRead(file->_fileHandle, file->_fBuf, size);
                    if (fd != size) igPsx2File_GrowBuffer(file, fd);
                }
                if (mode == 2) file->_bufPos = size;
                else file->_bufPos = 0;
            }
            file->_openMode = mode;
            file->_isOpen = 1;
            *result = g_resultSuccess.v;
        }
    }
}

void igPsx2File_Close(igPsx2FileView *self) {
    if (self->_fileHandle >= 0) {
        self->Flush();
        sceClose(self->_fileHandle);
        self->_fileHandle = -1;
        if (self->_fBuf != 0) {
            igObject_FreeMemory((igObject *)self, (void *)self->_fBuf);
        }
        self->_fBuf = 0;
        self->_bufSize = 0;
        self->_bufPos = 0;
        self->_isOpen = 0;
    }
}

void **igPsx2File_OpenFile(void **self, const char *fileName, int modeText) {
    igResult appendBinaryResult;
    igResult appendResult;
    igResult readWriteBinaryResult;
    igResult readWriteResult;
    igResult writeBinaryResult;
    igResult writeResult;
    igResult readBinaryResult;
    igResult readResult;
    int opened;

    igFile_SetFileName((int *)self, fileName);
    if (strcmp((const char *)modeText, "r") == 0) {
        readResult = ((igFileView *)(self))->OpenWithMode((int)(0));
        opened = readResult.v;
        goto block_21;
    }
    if (strcmp((const char *)modeText, "rb") == 0) {
        readBinaryResult = ((igFileView *)(self))->OpenWithMode((int)(4));
        opened = readBinaryResult.v;
        goto block_21;
    }
    if (strcmp((const char *)modeText, (const char *)(int *)((char *)"w")) == 0) {
        writeResult = ((igFileView *)(self))->OpenWithMode((int)(1));
        opened = writeResult.v;
        goto block_21;
    }
    if (strcmp((const char *)modeText, (const char *)(int *)((char *)"wb")) == 0) {
        writeBinaryResult = ((igFileView *)(self))->OpenWithMode((int)(5));
        opened = writeBinaryResult.v;
        goto block_21;
    }
    if ((strcmp((const char *)modeText, "r+") == 0) || (strcmp((const char *)modeText, "w+") == 0)) {
        readWriteResult = ((igFileView *)(self))->OpenWithMode((int)(3));
        opened = readWriteResult.v;
        goto block_21;
    }
    if ((strcmp((const char *)modeText, "r+b") == 0) || (strcmp((const char *)modeText, "w+b") == 0)) {
        readWriteBinaryResult = ((igFileView *)(self))->OpenWithMode((int)(7));
        opened = readWriteBinaryResult.v;
        goto block_21;
    }
    if ((strcmp((const char *)modeText, "a") == 0) || (strcmp((const char *)modeText, "a+") == 0)) {
        appendResult = ((igFileView *)(self))->OpenWithMode((int)(2));
        opened = appendResult.v;
        goto block_21;
    }
    if ((strcmp((const char *)modeText, "ab") == 0) || (strcmp((const char *)modeText, "a+b") == 0)) {
        appendBinaryResult = ((igFileView *)(self))->OpenWithMode((int)(6));
        opened = appendBinaryResult.v;
        goto block_21;
    }
    return 0;
block_21:
    return (opened == g_resultFailure.v) ? (void **)0 : self;
}

void igPsx2File_CloseFile(igPsx2FileView *self)
{
    self->CloseHandle();
}

void igPsx2File_GrowBuffer(igPsx2FileView *self, int size) {
    int n;
    if (self->_bufSize < size) {
        if (size > 0x100000) {
            n = size + 0x100000;
        } else {
            n = size * 2;
        }
        if (self->_fBuf != 0) {
            self->_fBuf = (unsigned char *)igObject_Reallocate((igObject *)self, (void *)self->_fBuf, n);
        } else {
            self->_fBuf = (unsigned char *)igObject_AllocateStorage((igObject *)self, n);
        }
        self->_bufSize = n;
    }
    self->_fileSize = size;
}

int igPsx2File_Read(igPsx2FileView *self, int buffer, int size, int count) {
    int base;
    int r;
    int q;
    int bytes;
    int a1;
    int lim;
    if (self->_fileHandle < 0) {
        return -1;
    }
    base = self->Tell();
    if (self->_isBinary == 1) {
        r = sceRead(self->_fileHandle, (void *)buffer, count * size);
        count = r / size;
        q = count * size;
        if (r != q) {
            sceLseek(self->_fileHandle, base + q, 0);
        }
        return count;
    }
    a1 = self->_bufPos;
    bytes = size * count;
    lim = self->_fileSize;
    if (lim < a1 + bytes) {
        count = (lim - a1) / size;
        bytes = count * size;
    }
    memcpy((void *)buffer, self->_fBuf + a1, bytes);
    self->_bufPos = self->_bufPos + bytes;
    return count;
}

int igPsx2File_Write(igPsx2FileView *self, int buffer, int size, int count) {
    int bytes;
    if (self->_fileHandle < 0) return -1;
    if (size == 0) return 0;
    if (self->_isBinary == 1) {
        if (self->_openMode == 6) {
            sceLseek(self->_fileHandle, 0, 2);
        }
        return sceWrite(self->_fileHandle, (const void *)buffer, count * size) / size;
    }
    bytes = size * count;
    if (self->_openMode == 2) {
        self->_bufPos = self->_fileSize;
    }
    igPsx2File_GrowBuffer(self, self->_bufPos + bytes);
    memcpy(self->_fBuf + self->_bufPos, (void *)buffer, bytes);
    self->_bufPos = self->_bufPos + bytes;
    return bytes / size;
}

int igPsx2File_Flush(igPsx2FileView *self) {
    if (self->_isBinary != 0) return 0; sceLseek(self->_fileHandle, 0, 0); sceWrite(self->_fileHandle, self->_fBuf, self->_fileSize); return 0;
}

int igPsx2File_Scanf(igPsx2FileView *self, const char *format, ...) {
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
            sscanf((const char *)(self->_fBuf + self->_bufPos), piece, &consumed);
            self->_bufPos += consumed;
        } else {
            void *target;
            args += 8;
            target = *(void **)(args - 8);
            int consumed = 0;
            int matched = sscanf((const char *)(self->_fBuf + self->_bufPos), piece, target, &consumed);
            if (matched == -1) {
                break;
            }
            count += matched;
            self->_bufPos += consumed;
        }
    }
    return count;
}

int igPsx2File_Printf(igPsx2FileView *self, int format, ...) {
    char buf[16384];
    int n;
    int off;
    int len;
    int cur;
    if (self->_isBinary != 0) {
        return -1;
    }
    n = __builtin_args_info(2);
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    len = vsprintf(buf, (const char *)format, (char *)__builtin_next_arg(format) - off);
    cur = self->_bufPos + len;
    if (cur >= self->_fileSize) {
        igPsx2File_GrowBuffer(self, cur);
    }
    memcpy(self->_fBuf + self->_bufPos, buf, len);
    self->_bufPos = self->_bufPos + len;
    return len;
}

int igPsx2File_GetChar(igPsx2FileView *self) {
    int c;
    int i;

    if (self->_isBinary != 0) {
        sceRead(self->_fileHandle, &c, 1);
        return c;
    }
    i = self->_bufPos;
    if (i >= self->_fileSize) {
        return -1;
    }
    self->_bufPos = i + 1;
    return self->_fBuf[self->_bufPos - 1];
}

int igPsx2File_UngetChar(igPsx2FileView *self, int c) {
    int pos;
    int result;

    result = c;
    if (self->_isBinary != 0) {
        return -1;
    }
    pos = self->_bufPos;
    if (pos == 0) {
        return -1;
    }
    self->_bufPos = pos - 1;
    if ((result & 0xFF) != self->_fBuf[self->_bufPos]) {
        result = -1;
    }
    return result;
}

int igPsx2File_PutChar(igPsx2FileView *self, unsigned char c) {
    int end;

    if (self->_isBinary != 0) {
        return -1;
    }
    end = self->_bufPos + 1;
    if (end >= self->_fileSize) {
        igPsx2File_GrowBuffer(self, end);
    }
    self->_fBuf[self->_bufPos] = c;
    self->_bufPos = self->_bufPos + 1;
    return c;
}

char *igPsx2File_GetString(igPsx2FileView *self, char *buffer, int size) {
    if (buffer == 0) {
        return 0;
    }
    if (self->_isBinary != 0) {
        return 0;
    }
    if (self->_bufPos >= self->_fileSize) {
        return 0;
    }
    int i = 0;
    size = size - 1;
    if (size + self->_bufPos >= self->_fileSize) {
        size = self->_fileSize - self->_bufPos;
    }
    while (i < size) {
        unsigned char c = self->_fBuf[self->_bufPos];
        buffer[i] = c;
        i++;
        self->_bufPos = self->_bufPos + 1;
        if (c == 10) {
            break;
        }
    }
    buffer[i] = 0;
    return buffer;
}

int igPsx2File_PutString(igPsx2FileView *self, char *text) {
    int end;
    int length;

    if (text == 0) {
        return -1;
    }
    if (self->_isBinary != 0) {
        return -1;
    }
    length = strlen(text);
    end = self->_bufPos + length;
    if (end >= self->_fileSize) {
        igPsx2File_GrowBuffer(self, end);
    }
    memcpy(self->_fBuf + self->_bufPos, text, length);
    self->_bufPos = self->_bufPos + length;
    return length;
}

int igPsx2File_Seek(igPsx2FileView *self, int offset, int whence) {
    int s;
    if (self->_isBinary != 0) {
        switch (whence) {
        case 0:
            s = sceLseek(self->_fileHandle, offset, 0);
            return -(s != offset);
        case 1:
            s = self->Tell();
            return -(offset != sceLseek(self->_fileHandle, offset, 1) - s);
        case 2:
            sceLseek(self->_fileHandle, offset, 2);
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
        {int v1 = self->_fileSize; int v0 = self->_bufPos;
        if (v1 < v0) self->_bufPos = v1;
        else if (v0 < 0) self->_bufPos = 0;}
        return 0;
    }
}

int igPsx2File_Tell(igPsx2File *self) {
    if (self->_isBinary != 0) {
        return sceLseek(self->_fileHandle, 0, 1);
    }
    return self->_bufPos;
}

int g_igPsx2File_defaultPrefix;
int g_igPsx2_useCdrom;

void igPsx2File_InitDefaultPrefix(void) {
    if (g_igPsx2_useCdrom == 0) {
        if ((*(int * *)&g_igPsx2File_defaultPrefix) == 0) {
            (*(int * *)&g_igPsx2File_defaultPrefix) = (int *)("host0:");
        }
    } else {
        (*(int * *)&g_igPsx2File_defaultPrefix) = (int *)"cdrom0:";
    }
}

char *igPsx2File_MakeCompletePath(char *path) {
    igStringRef text = igPsx2File_JoinPrefix((char *)g_igPsx2File_defaultPrefix, path);
    return (char *)Memory_Reallocate(text.p, (igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString));
}

/* Joins the file's device prefix and `path`, keeps the result as _completeFilename and returns it. */
char *igPsx2File_MakeCompleteFilename(igPsx2FileView *self, char *path) {
    igStringRef name = igPsx2File_JoinPrefix(self->_prefix, path);
    retainString(name.p);
    releaseString(self->_completeFilename);
    self->_completeFilename = name.p;
    return name.p;
}

static inline void appendText(const igSmartPointer<igStringObj> &ref, char *chars) {
    igStringObj *text = ref.p;
    int length = text->_length;
    igStringObj_Insert(text, chars, (unsigned int)length, (unsigned int)(strlen(chars)));
}

igStringRef igPsx2File_JoinPrefix(char *prefix, char *path) {
    char *chars;
    int limit, i;
    char c;
    igSmartPointer<igStringObj> text(((igStringObj *)igStringObj_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString)))));
    if (prefix == 0) {
        igStringObj_Set(text.get(), path);
    } else if (*prefix == 0x63) {
        igStringObj_Set(text.get(), prefix);
        c = *path;
        if (c != 0x5C && c != 0x2F) {
            appendText(text,"\\");
        }
        appendText(text, path);
        appendText(text,";1");
        limit = strlen(path) + 8;
        for (i = 7; i < limit; i++) {
            chars = (char *)text.get()->_buffer + i;
            if (*chars == 0x2F) {
                *chars = 0x5C;
            } else {
                *chars = _toupper(*chars);
            }
        }
    } else {
        igStringObj_Set(text.get(), prefix);
        appendText(text, path);
    }
    chars = (char *)text.get()->_buffer;
    if (chars == 0) {
        chars = g_stringObjEmptyText;
    }
    igStringRef result(chars);
    return result;
}

/* Lists the folder's files: each sceDread entry's full path is stat'ed and directories skipped. */
igSmartPointer<igObject> igPsx2Folder_ListFiles(igPsx2Folder *self) {
    FolderEntry entry;
    FolderFileStat stat;
    int handle = sceDopen((const char *)self->_folderName);
    if (handle < 0) {
        return igSmartPointer<igObject>(0, kRetainReference);
    }
    igSmartPointer<igObject> list((igObject *)igStringRefList_Create(((int)igObject_GetAllocator((igObject *)self))));
    igSmartPointer<igObject> path((igObject *)igStringObj_Create(((int)igObject_GetAllocator((igObject *)self))));
    while (sceDread(handle, &entry) != 0) {
        /* matching construct: the name is addressed as the byte after the stat here and as entry.name below; one
         * spelling for both is common-subexpression-eliminated into a saved register retail does not use */
        igStringObj_Format((igStringObj *)path.p,"%s/%s", self->_folderName, (char *)(&entry.stat + 1));
        char *full = (char *)((igStringObj *)path.p)->_buffer;
        full = (full == 0) ? g_stringObjEmptyText : full;
        if (sceGetstat(full, &stat) != 0) {
            continue;
        }
        if ((stat.mode & SCE_STM_FMT) == SCE_STM_FDIR) {
            continue;
        }
        igStringRef name(entry.name);
        StringList_AppendRetained(list.p, &name);
    }
    sceDclose(handle);
    return list;
}

/* Lists the folder's subdirectories, the same walk keeping only S_IFDIR entries. */
igSmartPointer<igObject> igPsx2Folder_ListDirectories(igPsx2Folder *self) {
    FolderEntry entry;
    FolderFileStat stat;
    int handle = sceDopen((const char *)self->_folderName);
    if (handle < 0) {
        return igSmartPointer<igObject>(0, kRetainReference);
    }
    igSmartPointer<igObject> list((igObject *)igStringRefList_Create(((int)igObject_GetAllocator((igObject *)self))));
    igSmartPointer<igObject> path((igObject *)igStringObj_Create(((int)igObject_GetAllocator((igObject *)self))));
    while (sceDread(handle, &entry) != 0) {
        /* matching construct: the name is addressed as the byte after the stat here and as entry.name below; one
         * spelling for both is common-subexpression-eliminated into a saved register retail does not use */
        igStringObj_Format((igStringObj *)path.p,"%s/%s", self->_folderName, (char *)(&entry.stat + 1));
        char *full = (char *)((igStringObj *)path.p)->_buffer;
        full = (full == 0) ? g_stringObjEmptyText : full;
        if (sceGetstat(full, &stat) != 0) {
            continue;
        }
        if ((stat.mode & SCE_STM_FMT) != SCE_STM_FDIR) {
            continue;
        }
        igStringRef name(entry.name);
        StringList_AppendRetained(list.p, &name);
    }
    sceDclose(handle);
    return list;
}

