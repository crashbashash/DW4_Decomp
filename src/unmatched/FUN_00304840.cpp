#include "dw4/igSmartPointer.h"
extern "C" {
int strlen(int);
int strncmp(int, int, unsigned);
igPluginRepository *FUN_002bc930(int);
int StringPool_Allocate(int);
int ObjectList_AppendRetained(int, igPluginRepository *);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, char *);
int igNamedObject_SetName(igPluginRepository *, int);
int igObject_GetAllocator(igPluginHelper *);
extern int DAT_004c22c8[4];
extern int DAT_004c22d0[4];
extern int DAT_004fafb8[4];
extern int DAT_004fafc0[4];
extern int DAT_00586f20[4];
extern char GPR_00554c18;
extern char GPR_00554c1c;
}

static inline void setLocation(const igSmartPointer<igPluginRepository> &ref, int path, const int &skip) {
    igPluginRepository *repository = ref.p;
    int interned, left;
    int old;
    int *header;
    if (DAT_00586f20[0] == 0) {
        int pool = StringPool_Allocate(16);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        DAT_00586f20[0] = pool;
    }
    interned = StringPool_Intern(DAT_00586f20[0], (char *)(path + skip));
    old = repository->_location;
    if (old != 0) {
        header = (int *)(old - 8);
        left = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = left;
        if (left == 0) {
            StringChunk_ReleaseHeader(*header, header);
        }
    }
    repository->_location = interned;
}
static inline void setLocation(const igSmartPointer<igPluginRepository> &ref, char *location) {
    igPluginRepository *repository = ref.p;
    int interned, left;
    int old;
    int *header;
    if (DAT_00586f20[0] == 0) {
        int pool = StringPool_Allocate(16);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        DAT_00586f20[0] = pool;
    }
    interned = StringPool_Intern(DAT_00586f20[0], location);
    old = repository->_location;
    if (old != 0) {
        header = (int *)(old - 8);
        left = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = left;
        if (left == 0) {
            StringChunk_ReleaseHeader(*header, header);
        }
    }
    repository->_location = interned;
}
extern "C" void FUN_00304840(igPluginHelper *self, int name, int path) {
    if (GPR_00554c18 == 0) {
        DAT_004fafb8[0] = strlen(DAT_004c22c8[0]);
        GPR_00554c18 = 1;
    }
    if (GPR_00554c1c == 0) {
        DAT_004fafc0[0] = strlen(DAT_004c22d0[0]);
        GPR_00554c1c = 1;
    }
    igSmartPointer<igPluginRepository> repository(FUN_002bc930(igObject_GetAllocator(self)));
    igNamedObject_SetName(repository.get(), name);
    if (strncmp(path, DAT_004c22c8[0], DAT_004fafb8[0]) == 0) {
        setLocation(repository, path, DAT_004fafb8[0]);
        repository.get()->_locationType = 1;
    } else if (strncmp(path, DAT_004c22d0[0], DAT_004fafc0[0]) == 0) {
        setLocation(repository, path, DAT_004fafc0[0]);
        repository.get()->_locationType = 2;
    } else {
        setLocation(repository, (char *)path);
        repository.get()->_locationType = 0;
    }
    ObjectList_AppendRetained(self->_repositoryList, repository.get());
}
