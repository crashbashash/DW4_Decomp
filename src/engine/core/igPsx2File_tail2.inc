namespace Gap {
namespace Core {

/* Opens the file in `mode` (0-3 text, 4-7 binary: read, write, append, read-write; 8 the mode it
 * was last opened in). A relative name is tried under each entry of the search path list in turn.
 * A text file is read whole into the buffer. */
igResult igPsx2File::open(OpenMode mode)
{
    const char *searchPaths;
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
    if (mode == kDefaultOpenMode) {
        mode = _openMode;
    }
    if (_isOpen == 1 && _openMode == mode) {
        return g_resultSuccess;
    }
    switch (mode) {
    case kRead: case kWrite: case kAppend: case kReadWrite: case kDefaultOpenMode:
        _isBinary = 0;
        break;
    case kReadBinary: case kWriteBinary: case kAppendBinary: case kReadWriteBinary:
        _isBinary = 1;
        break;
    }
    switch (mode) {
    case kWrite: case kWriteBinary: flags = SCE_TRUNC | SCE_CREAT | SCE_WRONLY; break;
    case kAppend: case kAppendBinary: flags = SCE_CREAT | SCE_APPEND; break;
    case kReadWrite: case kReadWriteBinary: flags = SCE_CREAT | SCE_RDWR; break;
    case kRead: case kReadBinary: case kDefaultOpenMode: flags = SCE_RDONLY; break;
    }
    _bufSize = 0;
    p = path;
    _bufPos = 0;
    n = sizeof(path);
    _isOpen = 0;
    if (p != 0) {
        do {
            *p = 0;
            n -= 1;
            p += 1;
        } while (n != 0);
    }
    more = 1;
    absolute = isAbsolutePath(_fileName.p);
    hasDirectory = containsRelativePath(_fileName.p);
    searchPaths = getSearchPath();
    attempt = 0;
    while (more && attempt < 0x100) {
        if (absolute) {
            path[0] = 0;
            more = 0;
            goto tryPath;
        }
        if (hasDirectory != 0) {
            path[0] = 0;
            hasDirectory = 0;
            goto tryPath;
        }
        more = getNextPath(&searchPaths, path, sizeof(path));
        if (more) {
tryPath:
            strcat(path, _fileName.p);
            devicePath = (char *)generateFilename(path);
            if (*devicePath == 'c') {
                retries = 10;
                while ((fd = sceOpen(devicePath, flags)) < 0 && retries != 0) {
                    retries -= 1;
                }
            } else {
                fd = sceOpen(devicePath, flags, 0666);
            }
            _fileHandle = fd;
            if (!(0 > fd)) break;
        }
        attempt += 1;
    }
    if (_fileHandle < 0) {
        return g_resultFailure;
    }
    if (mode == kAppendBinary) {
        sceLseek(_fileHandle, 0, SCE_SEEK_END);
    }
    if (_isBinary == 0) {
        size = sceLseek(_fileHandle, 0, SCE_SEEK_END);
        growBuffer(size);
        sceLseek(_fileHandle, 0, SCE_SEEK_SET);
        if (size > 0) {
            fd = sceRead(_fileHandle, _fBuf, size);
            if (fd != size) growBuffer(fd);
        }
        if (mode == kAppend) _bufPos = size;
        else _bufPos = 0;
    }
    _openMode = mode;
    _isOpen = 1;
    return g_resultSuccess;
}

void igPsx2File::close()
{
    if (_fileHandle >= 0) {
        fflush();
        sceClose(_fileHandle);
        _fileHandle = -1;
        if (_fBuf != 0) {
            free(_fBuf);
        }
        _fBuf = 0;
        _bufSize = 0;
        _bufPos = 0;
        _isOpen = 0;
    }
}

igFile *igPsx2File::fopen(const char *path, const char *mode)
{
    igResult readResult;
    igResult readBinaryResult;
    igResult writeResult;
    igResult writeBinaryResult;
    igResult updateResult;
    igResult updateBinaryResult;
    igResult appendResult;
    igResult appendBinaryResult;
    int status;

    setFileName(path);
    if (strcmp(mode, "r") == 0) {
        readResult = open(kRead);
        status = readResult.v;
        goto opened;
    }
    if (strcmp(mode, "rb") == 0) {
        readBinaryResult = open(kReadBinary);
        status = readBinaryResult.v;
        goto opened;
    }
    if (strcmp(mode, "w") == 0) {
        writeResult = open(kWrite);
        status = writeResult.v;
        goto opened;
    }
    if (strcmp(mode, "wb") == 0) {
        writeBinaryResult = open(kWriteBinary);
        status = writeBinaryResult.v;
        goto opened;
    }
    if ((strcmp(mode, "r+") == 0) || (strcmp(mode, "w+") == 0)) {
        updateResult = open(kReadWrite);
        status = updateResult.v;
        goto opened;
    }
    if ((strcmp(mode, "r+b") == 0) || (strcmp(mode, "w+b") == 0)) {
        updateBinaryResult = open(kReadWriteBinary);
        status = updateBinaryResult.v;
        goto opened;
    }
    if ((strcmp(mode, "a") == 0) || (strcmp(mode, "a+") == 0)) {
        appendResult = open(kAppend);
        status = appendResult.v;
        goto opened;
    }
    if ((strcmp(mode, "ab") == 0) || (strcmp(mode, "a+b") == 0)) {
        appendBinaryResult = open(kAppendBinary);
        status = appendBinaryResult.v;
        goto opened;
    }
    return 0;
opened:
    return status == g_resultFailure.v ? 0 : this;
}

void igPsx2File::fclose()
{
    close();
}

void igPsx2File::growBuffer(int size)
{
    int n;

    if (_bufSize < size) {
        if (size > 0x100000) {
            n = size + 0x100000;
        } else {
            n = size * 2;
        }
        if (_fBuf != 0) {
            _fBuf = (unsigned char *)realloc(_fBuf, n);
        } else {
            _fBuf = (unsigned char *)malloc(n);
        }
        _bufSize = n;
    }
    _fileSize = size;
}

int igPsx2File::fread(void *ptr, int size, int nElts)
{
    int base;
    int r;
    int q;
    int bytes;
    int a1;
    int lim;

    if (_fileHandle < 0) {
        return -1;
    }
    base = ftell();
    if (_isBinary == 1) {
        r = sceRead(_fileHandle, ptr, nElts * size);
        nElts = r / size;
        q = nElts * size;
        if (r != q) {
            sceLseek(_fileHandle, base + q, 0);
        }
        return nElts;
    }
    a1 = _bufPos;
    bytes = size * nElts;
    lim = _fileSize;
    if (lim < a1 + bytes) {
        nElts = (lim - a1) / size;
        bytes = nElts * size;
    }
    memcpy(ptr, _fBuf + a1, bytes);
    _bufPos = _bufPos + bytes;
    return nElts;
}

int igPsx2File::fwrite(const void *ptr, int size, int nElts)
{
    int bytes;

    if (_fileHandle < 0) {
        return -1;
    }
    if (size == 0) {
        return 0;
    }
    if (_isBinary == 1) {
        if (_openMode == kAppendBinary) {
            sceLseek(_fileHandle, 0, 2);
        }
        return sceWrite(_fileHandle, ptr, nElts * size) / size;
    }
    bytes = size * nElts;
    if (_openMode == kAppend) {
        _bufPos = _fileSize;
    }
    growBuffer(_bufPos + bytes);
    memcpy(_fBuf + _bufPos, ptr, bytes);
    _bufPos = _bufPos + bytes;
    return bytes / size;
}

int igPsx2File::fflush()
{
    if (_isBinary != 0) {
        return 0;
    }
    sceLseek(_fileHandle, 0, 0);
    sceWrite(_fileHandle, _fBuf, _fileSize);
    return 0;
}

int igPsx2File::fscanf(const char *format, ...)
{
    char *args;
    int n;
    int off;
    int length;
    int i;
    int count;

    if (_isBinary != 0) {
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
            sscanf((const char *)(_fBuf + _bufPos), piece, &consumed);
            _bufPos += consumed;
        } else {
            void *target;
            args += 8;
            target = *(void **)(args - 8);
            int consumed = 0;
            int matched = sscanf((const char *)(_fBuf + _bufPos), piece, target, &consumed);
            if (matched == -1) {
                break;
            }
            count += matched;
            _bufPos += consumed;
        }
    }
    return count;
}

int igPsx2File::fprintf(const char *format, ...)
{
    char buf[16384];
    int n;
    int off;
    int len;
    int cur;

    if (_isBinary != 0) {
        return -1;
    }
    n = __builtin_args_info(2);
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    len = vsprintf(buf, format, (char *)__builtin_next_arg(format) - off);
    cur = _bufPos + len;
    if (cur >= _fileSize) {
        growBuffer(cur);
    }
    memcpy(_fBuf + _bufPos, buf, len);
    _bufPos = _bufPos + len;
    return len;
}

int igPsx2File::fgetc()
{
    int c;
    int i;

    if (_isBinary != 0) {
        sceRead(_fileHandle, &c, 1);
        return c;
    }
    i = _bufPos;
    if (i >= _fileSize) {
        return -1;
    }
    _bufPos = i + 1;
    return _fBuf[_bufPos - 1];
}

int igPsx2File::ungetc(int c)
{
    int pos;
    int result;

    result = c;
    if (_isBinary != 0) {
        return -1;
    }
    pos = _bufPos;
    if (pos == 0) {
        return -1;
    }
    _bufPos = pos - 1;
    if ((result & 0xFF) != _fBuf[_bufPos]) {
        result = -1;
    }
    return result;
}

int igPsx2File::fputc(int c)
{
    int end;

    if (_isBinary != 0) {
        return -1;
    }
    end = _bufPos + 1;
    if (end >= _fileSize) {
        growBuffer(end);
    }
    _fBuf[_bufPos] = c;
    _bufPos = _bufPos + 1;
    return (unsigned char)c;
}

char *igPsx2File::fgets(char *s, int n)
{
    int i;
    unsigned char c;

    if (s == 0) {
        return 0;
    }
    if (_isBinary != 0) {
        return 0;
    }
    if (_bufPos >= _fileSize) {
        return 0;
    }
    i = 0;
    n = n - 1;
    if (n + _bufPos >= _fileSize) {
        n = _fileSize - _bufPos;
    }
    while (i < n) {
        c = _fBuf[_bufPos];
        s[i] = c;
        i++;
        _bufPos = _bufPos + 1;
        if (c == 10) {
            break;
        }
    }
    s[i] = 0;
    return s;
}

int igPsx2File::fputs(const char *s)
{
    int end;
    int length;

    if (s == 0) {
        return -1;
    }
    if (_isBinary != 0) {
        return -1;
    }
    length = strlen(s);
    end = _bufPos + length;
    if (end >= _fileSize) {
        growBuffer(end);
    }
    memcpy(_fBuf + _bufPos, s, length);
    _bufPos = _bufPos + length;
    return length;
}

int igPsx2File::fseek(int offset, int whence)
{
    int s;
    int v1;
    int v0;

    if (_isBinary != 0) {
        switch (whence) {
        case 0:
            s = sceLseek(_fileHandle, offset, 0);
            return -(s != offset);
        case 1:
            s = ftell();
            return -(offset != sceLseek(_fileHandle, offset, 1) - s);
        case 2:
            sceLseek(_fileHandle, offset, 2);
            return 0;
        default:
            return -1;
        }
    } else {
        switch (whence) {
        case 0:
            _bufPos = offset;
            break;
        case 1:
            _bufPos = _bufPos + offset;
            break;
        case 2:
            _bufPos = _fileSize + offset;
            break;
        default:
            return -1;
        }
        v1 = _fileSize;
        v0 = _bufPos;
        if (v1 < v0) _bufPos = v1;
        else if (v0 < 0) _bufPos = 0;
        return 0;
    }
}

int igPsx2File::ftell()
{
    if (_isBinary != 0) {
        return sceLseek(_fileHandle, 0, 1);
    }
    return _bufPos;
}

const char *igPsx2File::defaultPrefix;
}
}
int g_igPsx2_useCdrom;

namespace Gap {
namespace Core {

void igPsx2File::userRegister()
{
    if (g_igPsx2_useCdrom == 0) {
        if (defaultPrefix == 0) {
            defaultPrefix = "host0:";
        }
    } else {
        defaultPrefix = "cdrom0:";
    }
}

char *igPsx2File::makeCompletePath(char *path) {
    igStringRef text = joinPrefix((char *)defaultPrefix, path);
    return (char *)Memory_Reallocate(text.p, (igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString));
}

/* Joins the file's device prefix and `path`, keeps the result as _completeFilename and returns it. */
const char *igPsx2File::generateFilename(const char *name)
{
    igStringRef full = joinPrefix(_prefix.p, (char *)name);
    _completeFilename = full;
    return full.p;
}
}
}

static inline void appendText(const igSmartPointer<igStringObj> &ref, char *chars) {
    igStringObj *text = ref.p;
    int length = text->_length;
    igStringObj_Insert(text, chars, (unsigned int)length, (unsigned int)(strlen(chars)));
}

namespace Gap {
namespace Core {

igStringRef igPsx2File::joinPrefix(char *prefix, char *path) {
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
igSmartPointer<igStringRefList> igPsx2Folder::getFiles() const
{
    FolderEntry entry;
    FolderFileStat stat;
    int handle = sceDopen(_folderName.p);
    if (handle < 0) {
        return igSmartPointer<igStringRefList>((igStringRefList *)0, kRetainReference);
    }
    igSmartPointer<igStringRefList> list((igStringRefList *)igStringRefList_Create((int)getMemoryPool()));
    igStringObjRef path((igStringObj *)igStringObj_Create((int)getMemoryPool()));
    while (sceDread(handle, &entry) != 0) {
        /* matching construct: the name is addressed as the byte after the stat here and as entry.name below; one
         * spelling for both is common-subexpression-eliminated into a saved register retail does not use */
        igStringObj_Format(path.get(), "%s/%s", _folderName.p, (char *)(&entry.stat + 1));
        char *full = (char *)path.get()->_buffer;
        full = (full == 0) ? g_stringObjEmptyText : full;
        if (sceGetstat(full, &stat) != 0) {
            continue;
        }
        if ((stat.mode & SCE_STM_FMT) == SCE_STM_FDIR) {
            continue;
        }
        igStringRef name(entry.name);
        StringList_AppendRetained(list.p, (char *const *)&name);
    }
    sceDclose(handle);
    return list;
}

/* Lists the folder's subdirectories, the same walk keeping only S_IFDIR entries. */
igSmartPointer<igStringRefList> igPsx2Folder::getSubFolders() const
{
    FolderEntry entry;
    FolderFileStat stat;
    int handle = sceDopen(_folderName.p);
    if (handle < 0) {
        return igSmartPointer<igStringRefList>((igStringRefList *)0, kRetainReference);
    }
    igSmartPointer<igStringRefList> list((igStringRefList *)igStringRefList_Create((int)getMemoryPool()));
    igStringObjRef path((igStringObj *)igStringObj_Create((int)getMemoryPool()));
    while (sceDread(handle, &entry) != 0) {
        /* matching construct: the name is addressed as the byte after the stat here and as entry.name below; one
         * spelling for both is common-subexpression-eliminated into a saved register retail does not use */
        igStringObj_Format(path.get(), "%s/%s", _folderName.p, (char *)(&entry.stat + 1));
        char *full = (char *)path.get()->_buffer;
        full = (full == 0) ? g_stringObjEmptyText : full;
        if (sceGetstat(full, &stat) != 0) {
            continue;
        }
        if ((stat.mode & SCE_STM_FMT) != SCE_STM_FDIR) {
            continue;
        }
        igStringRef name(entry.name);
        StringList_AppendRetained(list.p, (char *const *)&name);
    }
    sceDclose(handle);
    return list;
}
}
}

