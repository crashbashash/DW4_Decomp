#include "dw4/reflected.h"
#include "dw4/igObjectDispatchView.h"

extern "C" int Gap__Core__igObject__userConstruct(...);
extern "C" int igMetaObject_CountInstances(...);
extern "C" int igAdxAudio_GetMeta(void);
extern "C" void Gap__Core__igObject__userDestruct(void);
extern "C" void igAdxAudio_userDestruct(void);
extern "C" void igAdxAudio_userConstruct(igAdxAudio *self);
extern "C" int g_igAdxAudio_metaObject[4];

void igAdxAudio_userConstruct(igAdxAudio *self) {
    Gap__Core__igObject__userConstruct();
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    self->_bIsInitialized = 0;
    self->_adxt = 0;
}

int igAdxAudio_GetMeta(void)
{
    return g_igAdxAudio_metaObject[0];
}

void igAdxAudio_userDestruct(void)
{
    Gap__Core__igObject__userDestruct();
}
