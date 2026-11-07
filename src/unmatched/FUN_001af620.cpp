#include "dw4/reflected.h"
extern int DAT_004c22f0;
struct AppearanceNameEntry { char pad[8]; int _string; };
struct AppearanceNameList { char pad[8]; int _count; int _capacity; AppearanceNameEntry **_data; };
struct AppearanceWordList { char pad[8]; int _count; int _capacity; int *_data; };
struct igAppearanceView {
    char pad[12];
    int _skin;
    AppearanceWordList *_attachedSkins;
    AppearanceWordList *_attachedGraphs;
    AppearanceNameList *_segmentOverrideNameList;
    AppearanceWordList *_segmentOverrideGraphList;
};
extern "C" {
void FUN_001b7770(void *, int, int);
void FUN_001b7920(void *, int);
int FUN_001d9740(int, void *);
int FUN_001e04c0(void *, int);
int FUN_001af620(igAppearanceView *a, void *t);
}
static inline int overrideName(igAppearanceView *a, int i) {
    int s = a->_segmentOverrideNameList->_data[i]->_string;
    s = s == 0 ? DAT_004c22f0 : s;
    return s;
}
int FUN_001af620(igAppearanceView *a, void *t) {
    int i;
    int result;
    int n;
    result = 0;
    n = a->_segmentOverrideNameList->_count;
    for (i = 0; i < n; i++) {
        int graph = a->_segmentOverrideGraphList->_data[i];
        FUN_001b7770(t, overrideName(a, i), graph);
    }
    if (a->_skin != 0) {
        result = FUN_001d9740(a->_skin, t);
    }
    for (i = 0; i < a->_attachedSkins->_count; i++) {
        FUN_001d9740(a->_attachedSkins->_data[i], t);
    }
    for (i = 0; i < a->_attachedGraphs->_count; i++) {
        FUN_001e04c0(t, a->_attachedGraphs->_data[i]);
    }
    for (i = 0; i < n; i++) {
        FUN_001b7920(t, overrideName(a, i));
    }
    return result;
}
