#include "dw4/support/reflected.h"
#include "dw4/windowinput/igWindowDispatchView.h"
#include "dw4/game/beBkColor.h"
#include "dw4/game/beBkColorInfo.h"

extern "C" igMetaObject *beBkColor_GetInfoMeta(void);
extern "C" igMetaObject *beBkColor_GetMeta(void);
extern "C" void beBkColor_Prepare(beBkColor *self);

extern "C" void beBkColor_UpdateRam(beBkColor *self);

void beBkColor_Prepare(beBkColor *self) {
    self->_isClear = 0;
}

igMetaObject *beBkColor_GetInfoMeta(void)
{
    return g_beBkColorInfo_metaObject;
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

igMetaObject *beBkColor_GetMeta(void)
{
    return g_beBkColor_metaObject;
}

