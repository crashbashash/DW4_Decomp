int FUN_00306360();
int FUN_00307700();
int FUN_00307c10();
int FUN_00307f80();
int igObject_Destroy();
extern char *DAT_004c22f0[4];
typedef struct IniPairText { char pad[8]; char *text; } IniPairText;
typedef struct IniPairEntry { char pad[4]; int _refCount; int section; IniPairText *value; IniPairText *key; } IniPairEntry;
typedef struct IniPairList { char pad[8]; int count; int cap; IniPairEntry **data; } IniPairList;
typedef struct IniIncludeView { char pad[8]; IniPairList *pairs; } IniIncludeView;
static inline char *text(IniPairText *s) { char *t = s->text; if (t == 0) { return DAT_004c22f0[0]; } return t; }
int FUN_003061c0(void *self, IniIncludeView *inc, int overwrite) {
    IniPairEntry *p;
    int i;
    IniPairEntry *held;
    int section;
    IniPairEntry *volatile cur;

    i = 0;
    cur = 0;
    for (; i < inc->pairs->count; i++) {
        p = inc->pairs->data[i];
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
        held = cur;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long)((long long)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
        }
        cur = p;
        held = cur;
        if (held != 0) {
            section = FUN_00306360(self, FUN_00307f80(inc, held->section), 1);
            if (overwrite == 0 && FUN_00307c10(self, section, text(cur->key), 0) != 0) {
                continue;
            }
            held = cur;
            { IniPairText *v = held->value; IniPairText *k = held->key; FUN_00307700(self, section, text(k), text(v)); }
        }
    }
    held = cur;
    if (held != 0) {
        held->_refCount = held->_refCount - 1;
        if (((unsigned long long)((long long)held->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(held);
        }
    }
    return 1;
}
