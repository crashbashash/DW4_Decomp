#include "dw4/igSmartPointer.h"

struct ConfigPlatformText : public igObject { char *text; };
class ConfigPlatformSource {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void Describe(void *target);
};
struct ConfigPlatformSourceList : public igObject { int count; int capacity; ConfigPlatformSource **data; };
extern "C" {
void *igObject_GetAllocator(void *);
ConfigPlatformText *FUN_002b9500(void *);
void FUN_002d96f0(void *, int, char *);
int FUN_002dac30(ConfigPlatformText *);
int FUN_002dac60(ConfigPlatformText *);
int FUN_002dac90(ConfigPlatformText *);
extern char *DAT_004c22f0[4];
void FUN_002da010(void *self, ConfigPlatformSourceList *list);
}

static inline char *textOf(const igSmartPointer<ConfigPlatformText> &ref) {
    char *s = ref.get()->text;
    s = (s == 0) ? DAT_004c22f0[0] : s;
    return s;
}
void FUN_002da010(void *self, ConfigPlatformSourceList *list) {
    int i;
    igSmartPointer<ConfigPlatformText> text(FUN_002b9500(igObject_GetAllocator(self)));
    if (FUN_002dac30(text.get()) != 0) {
        FUN_002d96f0(self, 0, textOf(text));
    }
    if (FUN_002dac60(text.get()) != 0) {
        FUN_002d96f0(self, 6, textOf(text));
    }
    if (FUN_002dac90(text.get()) != 0) {
        FUN_002d96f0(self, 7, textOf(text));
    }
    if (list == 0 || list->count == 0) {
        return;
    }
    for (i = 0; i < list->count; i++) {
        list->data[i]->Describe(self);
    }
}
