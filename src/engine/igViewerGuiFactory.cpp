/* igViewerGuiFactory: builds the viewer's menu actions and gives its colour changers their default colours. */
#include "dw4/igSmartPointer.h"

class igViewerSceneInfoManager;
typedef void (igViewerSceneInfoManager::*ViewerActionFunction)();

/* The igViewerAction instance (reflected as igViewerAction in dw4/reflected.h, which types _function as a word): the object the action calls and the member function it calls on it. */
struct ViewerAction : public igObject {
    igObject *_ref;
    ViewerActionFunction _function;
};

/* igViewerGuiFactory with its object references typed (dw4/reflected.h types them as words). */
struct GuiFactory : public igObject {
    igBasicColorChanger *_menuBackColor;
    igBasicColorChanger *_menuItemForeColor;
    igBasicColorChanger *_menuMarkColor;
    igBasicColorChanger *_iconBackColor;
    igBasicColorChanger *_bigIconColor;
    igBasicColorChanger *_bigIconHighlightColor;
    igBasicColorChanger *_smallIconOnOffColor;
    igObject *_font;
};

extern "C" {
ViewerAction *igViewerAction_Create(void *pool);
void igBasicColorChanger_SetColor(igBasicColorChanger *changer, int highlighted, int on, int disabled, const float *color);
void igOnOffColorChanger_SetColor(igBasicColorChanger *changer, int highlighted, int on, int disabled, const float *color);
extern int g_igViewerGuiFactory_metaObject[4];
extern float g_viewerClearColor[4];
extern float g_viewerTextColor[4];
extern float g_viewerDisabledTextColor[4];
extern float g_viewerHighlightTextColor[4];
extern float g_viewerSelectedColor[4];
extern float g_viewerBackColor[4];
extern float g_viewerHighlightBackColor[4];
}

static inline void createAction(igSmartPointer<ViewerAction> &holder, AdoptReference) {
    igRelease(holder.p);
    holder.p = igViewerAction_Create(0);
}

/* A new action bound to `ref` and `function`. */
extern "C" igSmartPointer<ViewerAction> igViewerGuiFactory_CreateAction(void *factory, igObject *ref, ViewerActionFunction function) {
    igSmartPointer<ViewerAction> action;
    createAction(action, AdoptReference());
    action->_ref = ref;
    action->_function = function;
    return action;
}

/* The factory has no widget of this kind: an empty reference. */
extern "C" igSmartPointer<igObject> igViewerGuiFactory_CreateEmpty(void *factory, int kind) {
    return igSmartPointer<igObject>(0, kRetainReference);
}

/* The default colour of each state (highlighted, on, disabled) of every colour changer the factory hands out. */
extern "C" void Gap__Viewer__igViewerGuiFactory__resetFields(GuiFactory *self) {
    igBasicColorChanger_SetColor(self->_menuBackColor, 0, 0, 0, g_viewerBackColor);
    igBasicColorChanger_SetColor(self->_menuBackColor, 0, 1, 0, g_viewerBackColor);
    igBasicColorChanger_SetColor(self->_menuBackColor, 1, 0, 0, g_viewerHighlightBackColor);
    igBasicColorChanger_SetColor(self->_menuBackColor, 1, 1, 0, g_viewerHighlightBackColor);
    igBasicColorChanger_SetColor(self->_menuBackColor, 0, 0, 1, g_viewerBackColor);
    igBasicColorChanger_SetColor(self->_menuItemForeColor, 0, 0, 0, g_viewerTextColor);
    igBasicColorChanger_SetColor(self->_menuItemForeColor, 0, 1, 0, g_viewerTextColor);
    igBasicColorChanger_SetColor(self->_menuItemForeColor, 1, 0, 0, g_viewerHighlightTextColor);
    igBasicColorChanger_SetColor(self->_menuItemForeColor, 1, 1, 0, g_viewerSelectedColor);
    igBasicColorChanger_SetColor(self->_menuItemForeColor, 0, 0, 1, g_viewerDisabledTextColor);
    igOnOffColorChanger_SetColor(self->_menuMarkColor, 0, 0, 0, g_viewerClearColor);
    igOnOffColorChanger_SetColor(self->_menuMarkColor, 1, 0, 0, g_viewerClearColor);
    igOnOffColorChanger_SetColor(self->_menuMarkColor, 0, 1, 0, g_viewerSelectedColor);
    igOnOffColorChanger_SetColor(self->_menuMarkColor, 1, 1, 0, g_viewerSelectedColor);
    igOnOffColorChanger_SetColor(self->_menuMarkColor, 0, 0, 1, g_viewerClearColor);
    igBasicColorChanger_SetColor(self->_iconBackColor, 0, 0, 0, g_viewerBackColor);
    igBasicColorChanger_SetColor(self->_iconBackColor, 1, 0, 0, g_viewerBackColor);
    igBasicColorChanger_SetColor(self->_iconBackColor, 0, 1, 0, g_viewerBackColor);
    igBasicColorChanger_SetColor(self->_iconBackColor, 1, 1, 0, g_viewerBackColor);
    igBasicColorChanger_SetColor(self->_iconBackColor, 0, 0, 1, g_viewerBackColor);
    igOnOffColorChanger_SetColor(self->_bigIconColor, 0, 0, 0, g_viewerTextColor);
    igOnOffColorChanger_SetColor(self->_bigIconColor, 1, 0, 0, g_viewerTextColor);
    igOnOffColorChanger_SetColor(self->_bigIconColor, 0, 1, 0, g_viewerTextColor);
    igOnOffColorChanger_SetColor(self->_bigIconColor, 1, 1, 0, g_viewerTextColor);
    igOnOffColorChanger_SetColor(self->_bigIconColor, 0, 0, 1, g_viewerTextColor);
    igOnOffColorChanger_SetColor(self->_bigIconHighlightColor, 0, 0, 0, g_viewerClearColor);
    igOnOffColorChanger_SetColor(self->_bigIconHighlightColor, 1, 0, 0, g_viewerHighlightTextColor);
    igOnOffColorChanger_SetColor(self->_bigIconHighlightColor, 0, 1, 0, g_viewerSelectedColor);
    igOnOffColorChanger_SetColor(self->_bigIconHighlightColor, 1, 1, 0, g_viewerSelectedColor);
    igOnOffColorChanger_SetColor(self->_bigIconHighlightColor, 0, 0, 1, g_viewerClearColor);
    igOnOffColorChanger_SetColor(self->_smallIconOnOffColor, 0, 0, 0, g_viewerTextColor);
    igOnOffColorChanger_SetColor(self->_smallIconOnOffColor, 0, 1, 0, g_viewerSelectedColor);
    igOnOffColorChanger_SetColor(self->_smallIconOnOffColor, 1, 0, 0, g_viewerHighlightTextColor);
    igOnOffColorChanger_SetColor(self->_smallIconOnOffColor, 1, 1, 0, g_viewerSelectedColor);
    igOnOffColorChanger_SetColor(self->_smallIconOnOffColor, 0, 0, 1, g_viewerDisabledTextColor);
}

extern "C" int Gap__Viewer__igViewerGuiFactory__vfunc_22(void) {
    return g_igViewerGuiFactory_metaObject[0];
}

extern "C" void igVec2f_Set(float *v, float x, float y) {
    v[0] = x;
    v[1] = y;
}

extern "C" void *igVec2f_Construct(void *v) {
    return v;
}
