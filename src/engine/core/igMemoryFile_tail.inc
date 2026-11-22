namespace Gap {
namespace Core {

void igMemoryFile::setMemoryFile(const char *filename, const void *pFileBuffer, int iBufferSize)
{
    arkRegister();
    if (pFileBuffer != 0) {
        igSmartPointer<igMemoryFileEntry> entry(igMemoryFileEntry::_instantiateFromPool(_entryList->getMemoryPool()));
        entry->setName(filename);
        entry->setSize(iBufferSize);
        entry->setBuffer((void *)pFileBuffer);
        _entryList->append(entry.p);
    }
}

void igMemoryFile::getMemoryFile(const char *filename, const void *&pOutBuffer, int &iBufferSize)
{
    igMemoryFileEntry *entry;

    pOutBuffer = 0;
    iBufferSize = 0;
    if (_entryList != 0) {
        entry = _entryList->search((igStringMetaField *)igNamedObject::k_name, filename);
        if (entry != 0) {
            pOutBuffer = entry->getBuffer();
            iBufferSize = entry->getSize();
        }
    }
}

igResult igMemoryFile::open(OpenMode mode)
{
    const void *buffer;
    int size;

    if (_bIsOpen != 0) {
        return g_resultSuccess;
    }
    if (mode == kDefaultOpenMode) {
        mode = _openMode;
    }
    switch (mode) {
    case kWrite:
    case kAppend:
    case kReadWrite:
    case kWriteBinary:
    case kAppendBinary:
        return g_resultFailure;
    default:
        return g_resultFailure;
    case kRead:
    case kReadBinary:
        getMemoryFile(_fileName.p, buffer, size);
        if (buffer == 0) {
            return g_resultFailure;
        }
        _iSeekPosition = 0;
        _buffer = (char *)buffer;
        _iBufferSize = size;
        _bIsOpen = 1;
        _fileHandle = (int)buffer;
        return g_resultSuccess;
    }
}

void igMemoryFile::close()
{
    _bIsOpen = 0;
}

igFile *igMemoryFile::fopen(const char *path, const char *mode)
{
    int ok;
    setFileName(path);
    if (strcmp(mode, "r") == 0) {
        ok = open(kRead) == g_resultSuccess;
    } else if (strcmp(mode, "rb") == 0) {
        ok = open(kReadBinary) == g_resultSuccess;
    } else {
        return 0;
    }
    return ok ? this : 0;
}

void igMemoryFile::fclose()
{
    close();
}

int igMemoryFile::fread(void *ptr, int size, int nElts)
{
    int n;
    int pos;
    int left;

    if (_bIsOpen == 0) {
        return -1;
    }
    pos = _iSeekPosition;
    n = size * nElts;
    left = _iBufferSize - pos;
    if (left < n) {
        n = left;
    }
    if (n <= 0) {
        return 0;
    }
    memcpy(ptr, _buffer + pos, n);
    _iSeekPosition += n;
    return n / size;
}

/* Vtable slot 29 of igMemoryFile: an unsupported-operation stub returning -1, the error value
 * vfunc_33 (read one byte) returns at end of buffer. The receiver is not touched, hence no
 * parameters. */
int igMemoryFile::fwrite(const void *ptr, int size, int nElts)
{
    return -1;
}

int igMemoryFile::fscanf(const char *format, ...)
{
    return -1;
}

int igMemoryFile::fprintf(const char *format, ...)
{
    return -1;
}

/* Vtable slot 32 of igMemoryFile: a stub returning 0 (success, nothing to do) for an operation a
 * buffer-backed file does not need. The receiver is not touched, hence no parameters. */
int igMemoryFile::fflush()
{
    return 0;
}

int igMemoryFile::fgetc()
{
    int position;
    char r;

    if (_bIsOpen == 0) {
        return -1;
    }
    position = _iSeekPosition;
    if ((_iBufferSize - position) <= 0) {
        return -1;
    }
    r = *(char *)(position + (int)_buffer);
    _iSeekPosition = position + 1;
    return r;
}

/* Vtable slot 35 of igMemoryFile: an unsupported-operation stub returning -1, the error value
 * vfunc_33 (read one byte) returns at end of buffer. The receiver is not touched, hence no
 * parameters. */
int igMemoryFile::fputc(int c)
{
    return -1;
}

/* Vtable slot 36 of igMemoryFile: a stub returning 0 (success, nothing to do) for an operation a
 * buffer-backed file does not need. The receiver is not touched, hence no parameters. */
char *igMemoryFile::fgets(char *s, int n)
{
    return 0;
}

/* Vtable slot 37 of igMemoryFile: an unsupported-operation stub returning -1, the error value
 * vfunc_33 (read one byte) returns at end of buffer. The receiver is not touched, hence no
 * parameters. */
int igMemoryFile::fputs(const char *s)
{
    return -1;
}

int igMemoryFile::fseek(int offset, int whence)
{
    int t;
    switch (whence) {
    case 0:
        _iSeekPosition = offset;
        break;
    case 1:
        _iSeekPosition = _iSeekPosition + offset;
        break;
    case 2:
        _iSeekPosition = _iBufferSize + offset;
        break;
    }
    t = _iSeekPosition;
    if (t < 0) return -1;
    return -(_iBufferSize < t);
}

/* Accessor: the current read/seek offset into the file's memory buffer (`_iSeekPosition`, +56). */

int igMemoryFile::ftell()
{
    return _iSeekPosition;
}

/* Vtable slot 34 of igMemoryFile: an unsupported-operation stub returning -1, the error value
 * vfunc_33 (read one byte) returns at end of buffer. The receiver is not touched, hence no
 * parameters. */
int igMemoryFile::ungetc(int character)
{
    return -1;
}
}
}

