#include "dw4/support/reflected.h"

#include "dw4/insight/igInsightCore.h"
#include "dw4/movie/igMovieManager.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igObject.h"
extern "C" void igMoviePlugin_Attach(igMoviePlugin *self, igInsightCore *insight);
extern "C" void igMoviePlugin_Detach(igMoviePlugin *self, igInsightCore *insight);
#include "dw4/movie/igMoviePlugin.h"
extern "C" igMetaObject *igMoviePlugin_GetMeta(void);

void igMoviePlugin_Attach(igMoviePlugin *self, igInsightCore *insight) {
    int allocator;
    igMovieManager *old;
    allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
    allocator = g_useOwnerAllocator != 0 ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
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

void igMoviePlugin_Detach(igMoviePlugin *self, igInsightCore *insight) {
    igInsightCore_RemoveManager(insight, (igObject *)self->_movieManager);
}

igMetaObject *igMoviePlugin_GetMeta(void)
{
    return g_igMoviePlugin_metaObject;
}

