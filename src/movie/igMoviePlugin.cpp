#include "dw4/reflected.h"

extern "C" int igInsightCore_AddManager(int insight, igMovieManager *manager);
extern "C" igMovieManager *igMovieManager_CreateInstance(int allocator);
extern "C" int Memory_GetAllocatorBySelector(int selector);
extern "C" int igObject_Destroy(igObject *object);
extern "C" int igObject_GetAllocator(igMoviePlugin *object);
extern "C" int kIGMemoryPoolHandleUser0[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" void igMoviePlugin_Attach(igMoviePlugin *self, int insight);
extern "C" int igInsightCore_RemoveManager(int insight, int manager);
extern "C" void igMoviePlugin_Detach(igMoviePlugin *self, int insight);
extern "C" int g_igMoviePlugin_metaObject[4];
extern "C" int igMoviePlugin_GetMeta(void);

void igMoviePlugin_Attach(igMoviePlugin *self, int insight) {
    int allocator;
    igMovieManager *old;
    allocator = igObject_GetAllocator(self);
    allocator = g_useOwnerAllocator != 0 ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
    old = (igMovieManager *)self->_movieManager;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    self->_movieManager = (int)igMovieManager_CreateInstance(allocator);
    ((igMovieManager *)self->_movieManager)->_audioDisabled = 1;
    igInsightCore_AddManager(insight, (igMovieManager *)self->_movieManager);
}

void igMoviePlugin_Detach(igMoviePlugin *self, int insight) {
    igInsightCore_RemoveManager(insight, self->_movieManager);
}

int igMoviePlugin_GetMeta(void)
{
    return g_igMoviePlugin_metaObject[0];
}

