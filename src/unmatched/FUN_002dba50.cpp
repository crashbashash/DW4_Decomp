struct ConfigToken { int vt; unsigned int _refCount; char *text; int kind; };
struct ConfigChildList { int vt; int rc; int count; int capacity; int *data; int getCount() const { return count; } };
struct ConfigTextParser { char pad[52]; char *cursor; };
struct ConfigSectionRecord { char pad[12]; int table; ConfigChildList *children; int id; char f24[4]; };
extern "C" {
void FUN_002dbc10(ConfigTextParser *, char *);
int FUN_002db690(ConfigTextParser *, int *);
int FUN_002db5e0(ConfigTextParser *, ConfigToken **);
void FUN_0030b320(int, char *, int);
void FUN_002db480(ConfigTextParser *);
int FUN_002dae40(ConfigTextParser *);
void List_Resize(ConfigChildList *, int, int);
void igObject_Destroy(ConfigToken *);
extern char *DAT_004c22f0[4];
int FUN_002dba50(ConfigTextParser *self, ConfigSectionRecord *out);
}
static inline void append(ConfigChildList *l, int v) {
    int i = l->count;
    if (i < l->capacity) {
        l->count = l->getCount() + 1;
    } else {
        List_Resize(l, i + 1, 4);
    }
    l->data[i] = v;
}
static inline char *textOf(ConfigToken *n) { char *t = n->text; return (t == 0) ? DAT_004c22f0[0] : t; }
int FUN_002dba50(ConfigTextParser *self, ConfigSectionRecord *out) {
    int id = 0;
    ConfigToken *name = 0;
    int child;
    char *text;
    ConfigToken *n;
    int table;
    int kind;
    FUN_002dbc10(self, out->f24);
    if (FUN_002db690(self, &id) == 0) {
        return 0;
    }
    out->id = id;
    if (FUN_002db5e0(self, &name) == 0) {
        return 0;
    }
    n = name;
    text = n->text;
    kind = n->kind;
    table = out->table;
    text = (text == 0) ? DAT_004c22f0[0] : text;
    FUN_0030b320(table, text, kind);
    n = name;
    n->_refCount = (int)n->_refCount - 1;
    if (((unsigned long long)((long long)(int)n->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(n);
    }
    name = 0;
    FUN_002db480(self);
    if (*self->cursor != '{') {
        return 0;
    }
    self->cursor++;
    FUN_002db480(self);
    while (*self->cursor != '}' && *self->cursor != 0) {
        child = FUN_002dae40(self);
        if (child == 0) {
            break;
        }
        append(out->children, child);
        FUN_002db480(self);
    }
    if (*self->cursor != '}') {
        return 0;
    }
    self->cursor++;
    return 1;
}
