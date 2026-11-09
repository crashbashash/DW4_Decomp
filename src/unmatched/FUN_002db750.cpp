struct ConfigToken { int vt; unsigned int _refCount; char *text; int kind; };
struct ConfigRecordList { int vt; int rc; int count; int capacity; int *data; int getCount() const { return count; } };
struct ConfigTextParser { char pad[52]; char *cursor; };
struct ConfigSettingEntry { int key; int value; int extra; };
struct ConfigSettingsRecord { int vt; int rc; ConfigRecordList *entries; int table; };
extern "C" {
void FUN_002db480(ConfigTextParser *);
int FUN_002dbc10(ConfigTextParser *, ConfigToken **);
int FUN_002db540(ConfigTextParser *, ConfigToken **);
int FUN_002db5e0(ConfigTextParser *, ConfigToken **);
int FUN_002db690(ConfigTextParser *, int *);
ConfigSettingEntry *FUN_002dc180(ConfigSettingEntry *);
void FUN_0030b320(int, char *, int);
void List_Resize(ConfigRecordList *, int, int);
ConfigSettingEntry *Memory_AllocateBufferDirect(int, void *);
void igObject_Destroy(ConfigToken *);
void *igObject_GetAllocator(void *);
extern char *DAT_004c22f0[4];
int FUN_002db750(ConfigTextParser *self, ConfigSettingsRecord *out);
}
static inline void storeToken(int table, ConfigToken *n) {
    char *text = n->text;
    int kind = n->kind;
    int t = table;
    text = (text == 0) ? DAT_004c22f0[0] : text;
    FUN_0030b320(t, text, kind);
}
static inline void releaseToken(ConfigToken *n) {
    n->_refCount = (int)n->_refCount - 1;
    if (((unsigned long long)((long long)(int)n->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(n);
    }
}
int FUN_002db750(ConfigTextParser *self, ConfigSettingsRecord *out) {
    ConfigRecordList *list;
    int index;
    ConfigSettingEntry *mem;
    ConfigSettingEntry *entry;
    ConfigToken *key = 0;
    ConfigToken *value = 0;
    ConfigToken *title = 0;
    int extra = 0;
    FUN_002db480(self);
    if (FUN_002dbc10(self, &title) != 0) {
        storeToken(out->table, title);
        releaseToken(title);
        title = 0;
    }
    FUN_002db480(self);
    if (*self->cursor != '{') {
        return 0;
    }
    self->cursor++;
    FUN_002db480(self);
    while (*self->cursor != '}' && *self->cursor != 0) {
        if (FUN_002db540(self, &key) == 0) {
            return 0;
        }
        if (FUN_002db690(self, &extra) == 0) {
            releaseToken(key);
            key = 0;
            return 0;
        }
        if (FUN_002db5e0(self, &value) == 0) {
            releaseToken(key);
            key = 0;
            return 0;
        }
        FUN_002db480(self);
        mem = Memory_AllocateBufferDirect(12, igObject_GetAllocator(self));
        entry = mem;
        if (mem != 0) {
            entry = FUN_002dc180(mem);
        }
        storeToken(entry->key, key);
        storeToken(entry->value, value);
        list = out->entries;
        index = list->count;
        if (index < list->capacity) {
            list->count = list->getCount() + 1;
        } else {
            List_Resize(list, index + 1, 4);
        }
        list->data[index] = (int)entry;
        releaseToken(key);
        key = 0;
        releaseToken(value);
        value = 0;
    }
    if (*self->cursor != '}') {
        return 0;
    }
    self->cursor++;
    return 1;
}
