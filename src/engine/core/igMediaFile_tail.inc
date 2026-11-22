unsigned char g_igMediaFile_openNoticeIgnored;

namespace Gap {
namespace Core {

/* Opens the file in `mode` (0-3 text, 4-7 binary: read, write, append, read-write; 8 read). A relative
 * name is tried under each entry of the search path list until a device opens it. A text file is read
 * whole into the buffer. */
igResult igMediaFile::open(OpenMode mode)
{
    const char *searchPaths;
    char path[512];
    bool absolute;
    igMedia *media;
    igMedia *previous;
    igResult status;
    char *p;
    unsigned int n;

    if (_isOpen == 1) {
        return g_resultFailure;
    }
    _openMode = mode;
    switch (_openMode) {
    case kRead: case kWrite: case kAppend: case kReadWrite: case kDefaultOpenMode:
        _isBinary = 0;
        break;
    case kReadBinary: case kWriteBinary: case kAppendBinary: case kReadWriteBinary:
        _isBinary = 1;
        break;
    }
    switch (_openMode) {
    case kWrite: case kWriteBinary: _write = 1; _read = 0; break;
    case kAppend: case kAppendBinary: _write = 1; _read = 0; break;
    case kReadWrite: case kReadWriteBinary: _write = 1; _read = 1; break;
    case kRead: case kReadBinary: case kDefaultOpenMode: _write = 0; _read = 1; break;
    }
    _bufSize = 0;
    p = path;
    _bufPos = 0;
    n = sizeof(path);
    if (p != 0) {
        do {
            *p = 0;
            n -= 1;
            p += 1;
        } while (n != 0);
    }
    absolute = Gap::Core::igFile::isAbsolutePath(_fileName.p);
    searchPaths = Gap::Core::igFile::getSearchPath();
    status = g_resultFailure;
    while (searchPaths != 0) {
        if (absolute) {
            path[0] = 0;
            searchPaths = 0;
        } else if (!Gap::Core::igFile::getNextPath(&searchPaths, path, sizeof(path))) {
            continue;
        }
        strcat(path, _fileName.p);
        previous = _media;
        media = igMedia::findMedia(path);
        _media = media;
        if (_media == 0) break;
        if (_media != previous) {
            if (previous != 0) {
                previous->deleteFile(_fileHandle);
            }
            _fileHandle = _media->createFile();
        }
        status = _media->open(_fileHandle, path, _openMode);
        if (status == g_resultSuccess) break;
    }
    if (status == g_resultFailure) {
        if (g_igMediaFile_openNoticeIgnored == 0) {
            int rc = igReport_Detail("Could not open file \"%s\".", _fileName.p);
            if (rc != 1 && rc == 2) {
                g_igMediaFile_openNoticeIgnored = 1;
            }
        }
        if (_media != 0) {
            _media->deleteFile(_fileHandle);
            _media = 0;
        }
        return g_resultFailure;
    }
    _media->seek(_fileHandle, 0, 2);
    _fileSize = _media->tell(_fileHandle);
    _media->seek(_fileHandle, 0, 0);
    if (_isBinary == 0) {
        fit(_fileSize);
        if (_fileSize > 0) {
            int count = _media->read(_fileHandle, _fBuf, _fileSize);
            if (count != _fileSize) {
                _fileSize = count;
                fit(count);
            }
        }
    }
    if (_openMode == kAppend) {
        _bufPos = _fileSize;
    } else {
        _bufPos = 0;
    }
    _isOpen = 1;
    return g_resultSuccess;
}

void igMediaFile::close()
{
    if (_isOpen != 0) {
        fflush();
        _media->close(_fileHandle);
        _media->deleteFile(_fileHandle);
        _media = 0;
        _fileHandle = -1;
        free(_fBuf);
        _fBuf = 0;
        _bufSize = 0;
        _bufPos = 0;
        _isOpen = 0;
    }
}

igFile *igMediaFile::fopen(const char *path, const char *mode)
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

void igMediaFile::fclose()
{
    close();
}

void igMediaFile::fit(int newSize)
{
    int buffer;
    int capacity;
    int storage;
    if (_bufSize < newSize) {
        capacity = newSize * 2;
        if (newSize > 0x100000) {
            capacity = newSize + 0x100000;
        }
        buffer = (int)_fBuf;
        if (buffer != 0) {
            storage = (int)realloc((void *)buffer, capacity);
        } else {
            storage = (int)malloc(capacity);
        }
        _fBuf = (unsigned char *)storage;
        _bufSize = capacity;
    }
    _fileSize = newSize;
}

int igMediaFile::fread(void *ptr, int size, int nElts)
{
    int bytes;
    int got;
    int n;
    int cnt;
    int back;
    if (_isOpen == 0) {
        return -1;
    }
    bytes = size * nElts;
    if (_isBinary == 1) {
        got = _media->read(_fileHandle, ptr, (unsigned)nElts * size);
        n = got / size;
        back = n * size;
        if (got != back) {
            _media->seek(_fileHandle, back - got, 1);
        }
        return n;
    }
    cnt = nElts;
    if (_fileSize < _bufPos + bytes) {
        cnt = (_fileSize - _bufPos) / size;
        bytes = cnt * size;
    }
    memcpy(ptr, _fBuf + _bufPos, bytes);
    _bufPos = _bufPos + bytes;
    return cnt;
}

void igMediaFile::freadAsynchronous(void *ptr, int sizeInBytes, igIOCallbackFunction *callback, int token)
{
    if (_isOpen == 0) {
        callback(token, -1);
    }
    if (_isBinary == 1) {
        _media->readAsynchronous(_fileHandle, ptr, sizeInBytes, callback, token);
    }
    callback(token, fread(ptr, 1, sizeInBytes));
}

int igMediaFile::fwrite(const void *ptr, int size, int nElts)
{
    int bytes;
    if (_isOpen == 0) {
        return -1;
    }
    if (size == 0) {
        return 0;
    }
    if (_isBinary == 1) {
        if (_openMode == kAppendBinary) {
            _media->seek(_fileHandle, 0, 2);
        }
        return _media->write(_fileHandle, ptr, nElts * size) / size;
    }
    bytes = size * nElts;
    if (_openMode == kAppend) {
        _bufPos = _fileSize;
    }
    fit(_bufPos + bytes);
    memcpy(_fBuf + _bufPos, ptr, bytes);
    _bufPos = _bufPos + bytes;
    return bytes / size;
}

int igMediaFile::fflush()
{
    if (_isBinary != 0) {
        return 0;
    }
    if (_write != 0) {
        _media->seek(_fileHandle, 0, 0);
        _media->write(_fileHandle, _fBuf, _fileSize);
    }
    return 0;
}
}
}

static inline int isSpace(int c) { return _ctype_[c + 1] & 8; }

namespace Gap {
namespace Core {

int igMediaFile::fscanf(const char *format, ...) {
    char *args;
    int n;
    int off;
    int length;
    int i;
    int count;
    if (((igMediaFileView *)this)->_isBinary != 0) {
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
            sscanf((const char *)_fBuf + _bufPos, piece, &consumed);
            _bufPos += consumed;
        } else {
            void *target;
            args += 8;
            target = *(void **)(args - 8);
            int consumed = 0;
            int matched = sscanf((const char *)_fBuf + _bufPos, piece, target, &consumed);
            if (matched == -1) {
                break;
            }
            count += matched;
            _bufPos += consumed;
        }
    }
    return count;
}

int igMediaFile::fprintf(char const *fmt, ...) {
    char buf[16384];
    int n;
    int off;
    int len;
    int pos;
    if (((igMediaFileView *)this)->_isBinary != 0) {
        return -1;
    }
    n = __builtin_args_info(2);
    if (n >= 8) {
        off = 0;
    } else {
        off = (8 - n) * 8;
    }
    len = vsprintf(buf, (const char *)fmt, (char *)__builtin_next_arg(fmt) - off);
    pos = _bufPos + len;
    if (pos >= _fileSize) {
        fit(pos);
    }
    memcpy(_fBuf + _bufPos, buf, len);
    _bufPos = _bufPos + len;
    return len;
}

int igMediaFile::fgetc()
{
    int c;
    int position;
    if (_isBinary != 0) {
        unsigned int handle = _fileHandle;
        igMedia *media = _media;
        if (media->read(handle, &c, 1) != 0) {
            return c;
        }
        return -1;
    }
    position = _bufPos;
    if (position >= _fileSize) {
        return -1;
    }
    _bufPos = position + 1;
    return _fBuf[_bufPos - 1];
}

int igMediaFile::ungetc(int c)
{
    int n;
    if (_isBinary != 0) return -1;
    n = _bufPos;
    if (n == 0) return -1;
    _bufPos = n - 1;
    if ((c & 0xff) != _fBuf[_bufPos]) c = -1;
    return c;
}

int igMediaFile::fputc(int c)
{
    int end;

    if (_isBinary != 0) {
        return -1;
    }
    end = _bufPos + 1;
    if (end >= _fileSize) {
        fit(end);
    }
    _fBuf[_bufPos] = c;
    _bufPos = _bufPos + 1;
    return (unsigned char)c;
}

char *igMediaFile::fgets(char *s, int n)
{
    if (s == 0) return 0;
    if (_isBinary != 0) return 0;
    if (_bufPos >= _fileSize) return 0;
    int i = 0;
    n = n - 1;
    if (n + _bufPos >= _fileSize) n = _fileSize - _bufPos;
    while (i < n) {
        unsigned char c = _fBuf[_bufPos];
        s[i] = c;
        i++;
        _bufPos = _bufPos + 1;
        if (c == 10) break;
    }
    s[i] = 0;
    return s;
}

int igMediaFile::fputs(const char *s)
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
        fit(end);
    }
    memcpy(_fBuf + _bufPos, s, length);
    _bufPos = _bufPos + length;
    return length;
}

int igMediaFile::fseek(int offset, int whence)
{
    int base;
    int cur;
    if (_isBinary != 0) {
        base = ftell();
        if (_media->seek(_fileHandle, offset, whence) != 0) {
            return 0;
        }
        cur = ftell();
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
        if (_bufPos > _fileSize) {
            _bufPos = _fileSize;
        } else if (_bufPos < 0) {
            _bufPos = 0;
        }
        return 0;
    }
}

int igMediaFile::ftell()
{
    if (_isBinary) {
        unsigned int a = _fileHandle;
        igMedia *o = _media;
        return o->tell(a);
    }
    return _bufPos;
}
}
}
