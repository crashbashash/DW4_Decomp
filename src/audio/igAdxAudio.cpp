#include "dw4/reflected.h"
#include "dw4/igObjectDispatchView.h"

#include "dw4/igObject.h"
#include "dw4/igMetaObject.h"
extern "C" igMetaObject *igAdxAudio_GetMeta(void);
extern "C" void igAdxAudio_userDestruct(igAdxAudio *self);
extern "C" void igAdxAudio_userConstruct(igAdxAudio *self);
#include "dw4/igAdxAudio.h"

void igAdxAudio_userConstruct(igAdxAudio *self) {
    Gap__Core__igObject__userConstruct(self);
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    self->_bIsInitialized = 0;
    self->_adxt = 0;
}

igMetaObject *igAdxAudio_GetMeta(void)
{
    return g_igAdxAudio_metaObject;
}

void igAdxAudio_userDestruct(igAdxAudio *self)
{
    Gap__Core__igObject__userDestruct(self);
}
