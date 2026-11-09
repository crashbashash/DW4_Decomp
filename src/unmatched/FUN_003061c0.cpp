#include "dw4/igSmartPointer.h"

extern "C" {
int FUN_00306360(void *, int, int);
int FUN_00307700(void *, int, char *, char *);
int FUN_00307c10(void *, int, char *, int);
int FUN_00307f80(void *, int);
extern char *DAT_004c22f0[4];
typedef struct IniPairText { char pad[8]; char *text; } IniPairText;
typedef struct IniPairEntry : public igObject { int section; IniPairText *value; IniPairText *key; } IniPairEntry;
typedef struct IniPairList { char pad[8]; int count; int cap; IniPairEntry **data; } IniPairList;
typedef struct IniIncludeView { char pad[8]; IniPairList *pairs; } IniIncludeView;
}
static inline char *textOf(IniPairText *s) { char *t = s->text; if (t == 0) { return DAT_004c22f0[0]; } return t; }

extern "C" int FUN_003061c0(void *self, IniIncludeView *inc, int overwrite) {
    int i = 0;
    igSmartPointer<IniPairEntry> cur;
    for (; i < inc->pairs->count; i++) {
        cur = inc->pairs->data[i];
        if (cur.p != 0) {
            int section = FUN_00306360(self, FUN_00307f80(inc, cur.p->section), 1);
            if (overwrite == 0 && FUN_00307c10(self, section, textOf(cur.p->key), 0) != 0) {
                continue;
            }
            IniPairText *value = cur.p->value;
            IniPairText *key = cur.p->key;
            FUN_00307700(self, section, textOf(key), textOf(value));
        }
    }
    return 1;
}
