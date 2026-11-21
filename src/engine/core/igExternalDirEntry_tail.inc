unsigned char g_igExternalDirEntry_loadFailureWarned;

namespace Gap {
namespace Core {

void igExternalDirEntry::readSetup(igIGBFile *igb)
{
    int answer;
    _externalFilePath = (const char *)igb->_basePath;
    resolve((igResolveFunction *)igb->_userLoadFunction);
    if (_ref == 0 && g_igExternalDirEntry_loadFailureWarned == 0) {
        answer = igReport_Warning("igIGBFile::readFile() - External Entry \"%s\" failed to load with base path (\"%s\")\n", _entryName.p, _externalFilePath.p);
        if (answer != 1 && answer == 2) {
            g_igExternalDirEntry_loadFailureWarned = 1;
        }
    }
    ((igDirectory *)igb)->setRef(_index, (void *)_ref);
}

void igExternalDirEntry::setDirectoryName(const char *dirName)
{
    _directoryName = dirName;
}

void igExternalDirEntry::setRef(void *refParam)
{
    igObject *old;
    igObject::ref((igObject *)refParam);
    old = (igObject *)_ref;
    igObject::release(old);
    _ref = (int)refParam;
}

bool igExternalDirEntry::load(igResolveFunction *userFunction)
{
    igSmartPointer<igIGBFileView> stream(((igIGBFileView *)igIGBFile_Create((int)getMemoryPool())));
    char *s1;
    int len;
    int c;
    char *buf;
    stream.get()->_userLoadFunction = (int)userFunction;
    stream.get()->ReadFile(_directoryName.p);
    if (stream.get()->_count == 0) {
        s1 = _directoryName.p;
        len = strlen(_externalFilePath.p);
        len = len + strlen(s1);
        c = strlen("/");
        buf = (char *)malloc(c + len + 1);
        strcpy(buf, _externalFilePath.p);
        strcat(buf, "/");
        strcat(buf, _directoryName.p);
        stream.get()->ReadFile(buf);
        free((void *)buf);
    }
    setRef((void *)((igDirectory *)((int)(stream.get())))->findRefByEntryName((char const *)_entryName.p));
    if (_ref == 0) {
        setRef((void *)((igDirectory *)((int)(stream.get())))->findRefByEntryName((char const *)("root")));
    }
    return _ref != 0;
}
}
}

/* Drops the reference the clone was created with; the smart pointer holding it keeps its own. */
static inline void dropCreationReference(igVirtualObject *object) {
    object->_refCount = object->_refCount - 1;
    if ((object->_refCount & 0x7FFFFF) == 0) {
        igObject_Destroy(object);
    }
}

namespace Gap {
namespace Core {

/* Resolve the entry through the resource manager's directory of its name, creating and registering
 * that directory if it is missing. When the directory cannot resolve it, the entry loads its file and
 * then calls `loadFunction`; a resolved entry is cloned into the directory so later lookups find it. */
bool igExternalDirEntry::resolve(igResolveFunction *userFunction)
{
    igMemoryPoolView *pool;
    igResource *resource = g_objectSystem->resource;
    igSmartPointer< ::igObject> directory = igResource_GetDirectory(resource, _directoryName.p);
    if (directory.get() == 0) {
        pool = getMemoryPool();
        directory.release();
        directory.p = (::igObject *)Gap::Core::igDirectory::_instantiateFromPool(pool);
        ((igDirectory *)(directory.get()))->setDirectoryName(_directoryName.p);
        igResource_AddDirectory((int *)resource, (int)directory.get());
    }
    ((igDirectoryDispatchView *)directory.get())->ResolveExternalEntry((igExternalDirEntryView *)this);
    if (_ref == 0) load(userFunction);
    if (_ref == 0 && userFunction != 0) userFunction(this);
    if (_ref != 0) {
        igSmartPointer<igDirEntryView> entry((igDirEntryView *)cloneViaMetadata(1), kRetainReference);
        dropCreationReference(entry.get());
        ((igNamedObject *)entry.get())->setName(_entryName.p);
        entry->_refType = 0;
        entry->SetRef(_ref);
        entry->_index = ((igDirectoryView *)directory.get())->_count;
        ((igObjectList *)(directory.get()))->append((igObject *)entry.get());
        return 1;
    }
    return 0;
}

void igExternalDirEntry::initDefaults()
{
    igDirEntry::initDefaults();
    _resolveMethod = 2;
    _refType = 0;
}

void igExternalDirEntry::releaseDefaults()
{
    setRef(0);
    igObject_ReleaseDefaults((::igObject *)this);
}
}
}

