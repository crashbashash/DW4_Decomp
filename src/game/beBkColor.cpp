#include "dw4/reflected.h"
#include "dw4/igObjectVirtuals.h"

extern "C" int beBkColor_GetInfoMeta(void);
extern "C" int beBkColor_GetMeta(void);
extern "C" void beBkColor_Prepare(beBkColor *self);
extern "C" int g_beBkColorInfo_metaObject[4];
extern "C" int g_beBkColor_metaObject[4];

/* The visual context: slot 175 sets the colour the frame is cleared to. */
class igVisualContextVirtuals : public igObjectVirtuals {
public:
    DW4_SLOTS_100(s)
    DW4_SLOTS_20(t) DW4_SLOTS_20(u) DW4_SLOTS_5(v) DW4_SLOTS_5(w) DW4_SLOTS_1(x) DW4_SLOTS_1(y) DW4_SLOTS_1(z) DW4_SLOTS_1(zz)
    virtual void setClearColor(float *rgba);
};

/* The window: slot 36 returns the visual context it draws into. */
class igWindowVirtuals : public igObjectVirtuals {
public:
    DW4_SLOTS_5(s) DW4_SLOTS_5(t) DW4_SLOTS_5(u)
    virtual igVisualContextVirtuals *getVisualContext();
};
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
        igWindowVirtuals *window = (igWindowVirtuals *)((igInsightCore *)self->_insight)->_window;
        beBkColorInfo *info = ((beBkColorInfo **)((beBaseInfoList *)self->_infoList)->_data)[0];
        igVisualContextVirtuals *context = window->getVisualContext();
        context->setClearColor(info->_rgba);
        self->_isClear = 1;
    }
}

int beBkColor_GetMeta(void)
{
    return g_beBkColor_metaObject[0];
}

