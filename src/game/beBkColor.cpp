#include "dw4/reflected.h"
#include "dw4/igWindowDispatchView.h"

extern "C" int beBkColor_GetInfoMeta(void);
extern "C" int beBkColor_GetMeta(void);
extern "C" void beBkColor_Prepare(beBkColor *self);
extern "C" int g_beBkColorInfo_metaObject[4];
extern "C" int g_beBkColor_metaObject[4];

extern "C" void beBkColor_UpdateRam(beBkColor *self);

void beBkColor_Prepare(beBkColor *self) {
    self->_isClear = 0;
}

int beBkColor_GetInfoMeta(void)
{
    return g_beBkColorInfo_metaObject[0];
}

void beBkColor_UpdateRam(beBkColor *self) {
    if (self->_isClear == 0) {
        igWindowDispatchView *window = (igWindowDispatchView *)((igInsightCore *)self->_insight)->_window;
        beBkColorInfo *info = ((beBkColorInfo **)((beBaseInfoList *)self->_infoList)->_data)[0];
        igVisualContextDispatchView *context = window->getVisualContext();
        context->setClearColor(info->_rgba);
        self->_isClear = 1;
    }
}

int beBkColor_GetMeta(void)
{
    return g_beBkColor_metaObject[0];
}

