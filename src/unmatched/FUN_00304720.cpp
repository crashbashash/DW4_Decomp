#include "dw4/reflected.h"
extern "C" {
igPluginRepository *FUN_002bc930(...);
int FUN_002eb010(...);
int ObjectList_AppendRetained(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
char *StringPool_Intern(...);
int igNamedObject_SetName(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_00586f20[4];
}
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) {}
    ~igSmartPointer() {
        T *object = p;
        if (object != 0) {
            object->_refCount = object->_refCount - 1;
            if ((object->_refCount & 0x7FFFFF) == 0) igObject_Destroy(object);
        }
    }
};
extern "C" void FUN_00304720(igPluginHelper *helper, int name, int location, int locationType) {
    int pool;
    char *text;
    igPluginRepository *target;
    char *old;
    igSmartPointer<igPluginRepository> repository(FUN_002bc930(igObject_GetAllocator(helper)));
    igNamedObject_SetName(repository.p, name);
    target = repository.p;
    if (DAT_00586f20[0] == 0) {
        pool = FUN_002eb010(0x10);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        DAT_00586f20[0] = pool;
    }
    text = StringPool_Intern(DAT_00586f20[0], location);
    old = (char *)target->_location;
    if (old != 0) {
        int *header = (int *)(old - 8);
        int count = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = count;
        if (count == 0) {
            StringChunk_ReleaseHeader(*header, header);
        }
    }
    target->_location = (int)text;
    repository.p->_locationType = locationType;
    ObjectList_AppendRetained(helper->_repositoryList, repository.p);
}
