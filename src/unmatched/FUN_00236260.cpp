#include "dw4/igSmartPointer.h"

struct TextValue : public igObject { char *text; };
struct ShadowSettings { int enabled; int width; int height; int left; int top; int right; int bottom; float scale; };
struct ShadowConfig {
    char pad0[184];
    int width;
    int height;
    char pad192[4];
    int left;
    int top;
    int right;
    int bottom;
    unsigned char verbose;
};
extern "C" {
TextValue *FUN_002b9500(int allocator);
int Memory_GetAllocatorBySelector(int selector);
void FUN_0030b3c0(TextValue *value, const char *text);
void FUN_0030b720(TextValue *value, int number, const char *format);
int printf(const char *, ...);
extern int DAT_00587048[4];
extern char *DAT_004c22f0[4];
extern char DAT_004e9760[];
extern char DAT_004e9778[];
extern char DAT_004e9780[];
extern char DAT_004e9788[];
extern char DAT_004e9798[];
extern char DAT_004e97a8[];
extern char DAT_004e97b8[];
ShadowSettings FUN_00236260(ShadowConfig *config);
}
static inline void describe(const igSmartPointer<TextValue> &text, int value) {
    if (value < 0) {
        FUN_0030b3c0(text.p, DAT_004e9778);
    } else {
        FUN_0030b720(text.p, value, DAT_004e9780);
    }
}
static inline const char *textOf(const TextValue *value) {
    const char *s = value->text;
    s = (s == 0) ? DAT_004c22f0[0] : s;
    return s;
}
ShadowSettings FUN_00236260(ShadowConfig *config) {
    igSmartPointer<TextValue> text(FUN_002b9500(Memory_GetAllocatorBySelector(DAT_00587048[0])));
    ShadowSettings settings;
    settings.enabled = 1;
    settings.width = config->width;
    settings.height = config->height;
    if (config->verbose) {
        printf(DAT_004e9760);
    }
    describe(text, config->left);
    if (config->verbose) {
        printf(DAT_004e9788, textOf(text.p));
    }
    describe(text, config->top);
    if (config->verbose) {
        printf(DAT_004e9798, textOf(text.p));
    }
    describe(text, config->right);
    if (config->verbose) {
        printf(DAT_004e97a8, textOf(text.p));
    }
    describe(text, config->bottom);
    if (config->verbose) {
        printf(DAT_004e97b8, textOf(text.p));
    }
    settings.left = config->left;
    settings.top = config->top;
    settings.right = config->right;
    settings.bottom = config->bottom;
    settings.scale = 1.0f;
    return settings;
}
