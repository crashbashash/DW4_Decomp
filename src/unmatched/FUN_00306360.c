extern char *DAT_004fb160[];
void *FUN_002b9500();
int igStringObj_Set();
int ObjectList_AppendRetained();
int igObject_Destroy();
int igObject_GetAllocator();
int thunk_strcasecmp();
extern char *DAT_004c22f0[4];
typedef struct IniNameText { char pad[4]; int _refCount; char *text; } IniNameText;
typedef struct IniSectionList { char pad[8]; int count; int cap; IniNameText **data; } IniSectionList;
typedef struct IniSectionsView { char pad[16]; IniSectionList *sections; } IniSectionsView;
static inline char *text(IniNameText *s) { char *t = s->text; if (t == 0) { return DAT_004c22f0[0]; } return t; }
int FUN_00306360(IniSectionsView *self, char *name, int create) {
    int n;
    int i;
    int result;
    IniNameText *s;
    IniNameText *held;

    for (i = 0; i < 11; i++) {
        if (thunk_strcasecmp(name, DAT_004fb160[i]) == 0) {
            return i;
        }
    }
    n = self->sections->count;
    for (i = 0; i < n; i++) {
        if (thunk_strcasecmp(name, text(self->sections->data[i])) == 0) {
            return i + 11;
        }
    }
    if (create != 0) {
        *(IniNameText **)&s = FUN_002b9500(igObject_GetAllocator(self));
        igStringObj_Set(s, name);
        held = s;
        ObjectList_AppendRetained(self->sections, held);
        i = n + 11;
        held = s;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long)((long long)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
        }
 return i; }
    return -1;
}
