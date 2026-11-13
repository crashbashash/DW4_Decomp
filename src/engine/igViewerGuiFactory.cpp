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

#include "dw4/igVec3f.h"
#include "dw4/igMath.h"

/* A cell of the viewer's 128x128 icon sheet by the values the initialiser gives it: a corner and the
 * extent from it, which together never pass 128. */
struct ViewerRect {
    igVec2f corner;
    igVec2f extent;
    ViewerRect() {}
};

/* The layout and the colours the viewer's menus are drawn with. The unit builds bottom-up (-inline bottomup):
 * the constructor with its 110 member constructors and setters expanded is over inline_max_size, so it goes
 * into the static initialiser with every one of them left as a call. */
struct ViewerGuiStyle {
    ViewerRect f0;
    ViewerRect f16;
    ViewerRect f32;
    ViewerRect f48;
    ViewerRect f64;
    ViewerRect f80;
    ViewerRect f96;
    ViewerRect f112;
    ViewerRect f128;
    ViewerRect f144;
    ViewerRect f160;
    ViewerRect f176;
    ViewerRect f192;
    ViewerRect f208;
    ViewerRect f224;
    ViewerRect f240;
    ViewerRect f256;
    igVec3f f272;
    ViewerRect f284;
    igVec3f f300;
    ViewerRect f312;
    ViewerRect f328;
    ViewerRect f344;
    ViewerRect f360;
    ViewerRect f376;
    ViewerRect f392;
    ViewerRect f408;
    ViewerRect f424;
    ViewerRect f440;
    ViewerRect f456;
    float f472;
    float f476;
    float f480;
    float f484;
    float f488;
    float f492;
    float f496;
    float f500;
    float f504;
    float f508;
    float f512;
    float f516;
    igVec3f f520;
    igVec4f clearColor;
    igVec4f textColor;
    igVec4f disabledTextColor;
    igVec4f highlightTextColor;
    igVec4f selectedColor;
    igVec4f f612;
    igVec4f f628;
    igVec4f backColor;
    igVec4f highlightBackColor;
    igVec4f f676;

    ViewerGuiStyle() {
        f0.corner.set(0.0f, 0.0f);
        f0.extent.set(128.0f, 128.0f);
        f16.corner.set(35.0f, 103.0f);
        f16.extent.set(1.0f, 1.0f);
        f32.corner.set(0.0f, 73.0f);
        f32.extent.set(10.0f, 25.0f);
        f48.corner.set(11.0f, 73.0f);
        f48.extent.set(10.0f, 25.0f);
        f96.corner.set(123.0f, 93.0f);
        f96.extent.set(2.0f, 21.0f);
        f112.corner.set(126.0f, 93.0f);
        f112.extent.set(2.0f, 10.0f);
        f128.corner.set(0.0f, 110.0f);
        f128.extent.set(100.0f, 2.0f);
        f176.corner.set(24.0f, 73.0f);
        f176.extent.set(20.0f, 21.0f);
        f144.corner.set(35.0f, 103.0f);
        f144.extent.set(1.0f, 1.0f);
        f160.corner.set(73.0f, 99.0f);
        f160.extent.set(3.0f, 7.0f);
        f192.corner.set(65.0f, 74.0f);
        f192.extent.set(13.0f, 15.0f);
        f208.corner.set(14.0f, 113.0f);
        f208.extent.set(17.0f, 15.0f);
        f224.corner.set(87.0f, 76.0f);
        f224.extent.set(15.0f, 15.0f);
        f240.corner.set(109.0f, 75.0f);
        f240.extent.set(17.0f, 17.0f);
        f256.corner.set(65.0f, 75.0f);
        f256.extent.set(13.0f, 15.0f);
        f272.set(6.0f, 6.0f, 0.0f);
        f284.corner.set(2.0f, 113.0f);
        f284.extent.set(8.0f, 14.0f);
        f300.set(0.0f, 0.0f, 0.0f);
        f80.corner.set(106.0f, 96.0f);
        f80.extent.set(5.0f, 10.0f);
        f64.corner.set(81.0f, 97.0f);
        f64.extent.set(11.0f, 8.0f);
        f312.corner.set(3.0f, 100.0f);
        f312.extent.set(10.0f, 7.0f);
        f328.corner.set(16.0f, 100.0f);
        f328.extent.set(7.0f, 7.0f);
        f344.corner.set(26.0f, 100.0f);
        f344.extent.set(6.0f, 7.0f);
        f360.corner.set(34.0f, 100.0f);
        f360.extent.set(6.0f, 7.0f);
        f376.corner.set(42.0f, 100.0f);
        f376.extent.set(6.0f, 7.0f);
        f392.corner.set(50.0f, 100.0f);
        f392.extent.set(7.0f, 7.0f);
        f408.corner.set(59.0f, 100.0f);
        f408.extent.set(10.0f, 7.0f);
        f424.corner.set(46.0f, 74.0f);
        f424.extent.set(17.0f, 19.0f);
        f440.corner.set(114.0f, 98.0f);
        f440.extent.set(7.0f, 4.0f);
        f456.corner.set(114.0f, 106.0f);
        f456.extent.set(7.0f, 4.0f);
        f472 = 23.0f;
        f476 = 15.0f;
        f480 = 2.0f;
        f484 = 1.0f;
        f488 = 1.0f;
        f492 = 100.0f;
        f496 = 16.0f;
        f500 = 50.0f;
        f504 = 50.0f;
        f508 = -50.0f;
        f512 = -f504;
        f516 = f508;
        f520.set(1.5f, 1.5f, 1.0f);
        clearColor.set(0.0f, 0.0f, 0.0f, 0.0f);
        textColor.set(1.0f, 1.0f, 1.0f, 1.0f);
        disabledTextColor.set(0.5f, 0.5f, 0.5f, 1.0f);
        highlightTextColor.set(1.0f, 0.85f, 0.1f, 1.0f);
        selectedColor.set(0.85f, 0.24f, 0.19f, 1.0f);
        highlightBackColor.set(0.26f, 0.2f, 0.15f, 1.0f);
        f612.set(0.02f, 0.88f, 1.0f, 1.0f);
        f628.set(0.16f, 0.44f, 0.53f, 1.0f);
        backColor.set(0.0f, 0.23f, 0.41f, 0.7f);
        f676.set(0.39f, 0.42f, 0.24f, 1.0f);
    }
};

ViewerGuiStyle g_viewerGuiStyle;

extern "C" {
ViewerAction *igViewerAction_Create(void *pool);
void igBasicColorChanger_SetColor(igBasicColorChanger *changer, int highlighted, int on, int disabled, const igVec4f *color);
void igOnOffColorChanger_SetColor(igBasicColorChanger *changer, int highlighted, int on, int disabled, const igVec4f *color);
extern int g_igViewerGuiFactory_metaObject[4];
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
    igBasicColorChanger_SetColor(self->_menuBackColor, 0, 0, 0, &g_viewerGuiStyle.backColor);
    igBasicColorChanger_SetColor(self->_menuBackColor, 0, 1, 0, &g_viewerGuiStyle.backColor);
    igBasicColorChanger_SetColor(self->_menuBackColor, 1, 0, 0, &g_viewerGuiStyle.highlightBackColor);
    igBasicColorChanger_SetColor(self->_menuBackColor, 1, 1, 0, &g_viewerGuiStyle.highlightBackColor);
    igBasicColorChanger_SetColor(self->_menuBackColor, 0, 0, 1, &g_viewerGuiStyle.backColor);
    igBasicColorChanger_SetColor(self->_menuItemForeColor, 0, 0, 0, &g_viewerGuiStyle.textColor);
    igBasicColorChanger_SetColor(self->_menuItemForeColor, 0, 1, 0, &g_viewerGuiStyle.textColor);
    igBasicColorChanger_SetColor(self->_menuItemForeColor, 1, 0, 0, &g_viewerGuiStyle.highlightTextColor);
    igBasicColorChanger_SetColor(self->_menuItemForeColor, 1, 1, 0, &g_viewerGuiStyle.selectedColor);
    igBasicColorChanger_SetColor(self->_menuItemForeColor, 0, 0, 1, &g_viewerGuiStyle.disabledTextColor);
    igOnOffColorChanger_SetColor(self->_menuMarkColor, 0, 0, 0, &g_viewerGuiStyle.clearColor);
    igOnOffColorChanger_SetColor(self->_menuMarkColor, 1, 0, 0, &g_viewerGuiStyle.clearColor);
    igOnOffColorChanger_SetColor(self->_menuMarkColor, 0, 1, 0, &g_viewerGuiStyle.selectedColor);
    igOnOffColorChanger_SetColor(self->_menuMarkColor, 1, 1, 0, &g_viewerGuiStyle.selectedColor);
    igOnOffColorChanger_SetColor(self->_menuMarkColor, 0, 0, 1, &g_viewerGuiStyle.clearColor);
    igBasicColorChanger_SetColor(self->_iconBackColor, 0, 0, 0, &g_viewerGuiStyle.backColor);
    igBasicColorChanger_SetColor(self->_iconBackColor, 1, 0, 0, &g_viewerGuiStyle.backColor);
    igBasicColorChanger_SetColor(self->_iconBackColor, 0, 1, 0, &g_viewerGuiStyle.backColor);
    igBasicColorChanger_SetColor(self->_iconBackColor, 1, 1, 0, &g_viewerGuiStyle.backColor);
    igBasicColorChanger_SetColor(self->_iconBackColor, 0, 0, 1, &g_viewerGuiStyle.backColor);
    igOnOffColorChanger_SetColor(self->_bigIconColor, 0, 0, 0, &g_viewerGuiStyle.textColor);
    igOnOffColorChanger_SetColor(self->_bigIconColor, 1, 0, 0, &g_viewerGuiStyle.textColor);
    igOnOffColorChanger_SetColor(self->_bigIconColor, 0, 1, 0, &g_viewerGuiStyle.textColor);
    igOnOffColorChanger_SetColor(self->_bigIconColor, 1, 1, 0, &g_viewerGuiStyle.textColor);
    igOnOffColorChanger_SetColor(self->_bigIconColor, 0, 0, 1, &g_viewerGuiStyle.textColor);
    igOnOffColorChanger_SetColor(self->_bigIconHighlightColor, 0, 0, 0, &g_viewerGuiStyle.clearColor);
    igOnOffColorChanger_SetColor(self->_bigIconHighlightColor, 1, 0, 0, &g_viewerGuiStyle.highlightTextColor);
    igOnOffColorChanger_SetColor(self->_bigIconHighlightColor, 0, 1, 0, &g_viewerGuiStyle.selectedColor);
    igOnOffColorChanger_SetColor(self->_bigIconHighlightColor, 1, 1, 0, &g_viewerGuiStyle.selectedColor);
    igOnOffColorChanger_SetColor(self->_bigIconHighlightColor, 0, 0, 1, &g_viewerGuiStyle.clearColor);
    igOnOffColorChanger_SetColor(self->_smallIconOnOffColor, 0, 0, 0, &g_viewerGuiStyle.textColor);
    igOnOffColorChanger_SetColor(self->_smallIconOnOffColor, 0, 1, 0, &g_viewerGuiStyle.selectedColor);
    igOnOffColorChanger_SetColor(self->_smallIconOnOffColor, 1, 0, 0, &g_viewerGuiStyle.highlightTextColor);
    igOnOffColorChanger_SetColor(self->_smallIconOnOffColor, 1, 1, 0, &g_viewerGuiStyle.selectedColor);
    igOnOffColorChanger_SetColor(self->_smallIconOnOffColor, 0, 0, 1, &g_viewerGuiStyle.disabledTextColor);
}

extern "C" int igViewerGuiFactory_GetMeta(void) {
    return g_igViewerGuiFactory_metaObject[0];
}
