void igRegistry_InitDefaults(void *self) {
    igObject_InitDefaults((igObject *)self);
    ObjectList_ResizeRetained((igTDataList<igObject *> *)((igRegistry *)self)->_valueTable, 0x100);
}

static inline char *pathText(igStringObj *s) { char *t = (char *)s->_buffer; if (t == 0) { return (g_stringObjEmptyText); } return t; }

static inline int openPath(igRegistry *self, const igSmartPointer<igStringObj> &path) {
    igFileView *file = (igFileView *)self->_registryFile;
    return file->Open(pathText(path.p), ((char *)"r"));
}

bool igRegistry_Load(igRegistry *self, char *name, char *dir) {
    int found;
    igStringRef held(name);
    if (held.p == 0 || strlen(held.p) == 0) {
        held ="alchemy.ini";
    }
    found = ((igFileView *)self->_registryFile)->Open(held.p, ((char *)"r"));
    if (found == 0) {
        if (dir == 0 || strlen(dir) == 0) {
            dir = ((char *)igObjectSystem_GetRootPath((int *)(((*(void * *)&g_objectSystem)))));
        }
        if (dir != 0 && strlen(dir) != 0) {
            igSmartPointer<igFolderView> folder((igFolderView *)igFolder_Create(((int)igObject_GetAllocator((igObject *)self))));
            folder.p->setFolderName(dir);
            found = openPath(self, folder.p->GetFullPath(held.p));
        }
    }
    if (found == 0) {
        igSmartPointer<igFolderView> folder((igFolderView *)igFolder_Create(((int)igObject_GetAllocator((igObject *)self))));
        folder.p->setFolderName(((char *)igObjectSystem_GetBasePath((int *)(((*(void * *)&g_objectSystem))))));
        found = openPath(self, folder.p->GetFullPath(held.p));
    }
    if (found == 0) {
        return false;
    }
    igRegistry_Clear(self);
    igRegistry_ParseFile(self, (igFileView *)self->_registryFile, 1);
    ((igFileView *)self->_registryFile)->Close();
    return true;
}

static inline char *registryText(igStringObj *s) { char *t = (char *)s->_buffer; if (t == 0) { return g_stringObjEmptyText; } return t; }

int igRegistry_Merge(void *self, igRegistry *inc, int overwrite) {
    int i = 0;
    igSmartPointer<igRegistryValue> cur;
    for (; i < ((igTDataList<igRegistryValue *> *)inc->_valueTable)->_count; i++) {
        cur = ((igTDataList<igRegistryValue *> *)inc->_valueTable)->_data[i];
        if (cur.p != 0) {
            int section = igRegistry_GetSectionIndex((igRegistry *)self, (char *)(igRegistry_GetSectionName(inc, cur.p->_section)), 1);
            if (overwrite == 0 && ((int)igRegistry_FindValue((igRegistry *)self, section, registryText((igStringObj *)cur.p->_valueName), 0)) != 0) {
                continue;
            }
            igStringObj *value = (igStringObj *)cur.p->_value;
            igStringObj *key = (igStringObj *)cur.p->_valueName;
            igRegistry_SetValueString(self, section, registryText(key), (const char *)(registryText(value)));
        }
    }
    return 1;
}

const char *const g_registrySectionNames[11] = {
    "APPS",
    "AUDIO",
    "CORE",
    "DISPLAY",
    "GFX",
    "MATH",
    "MODULES",
    "SG",
    "TESTS",
    "UTILS",
    "OPT"
};

/* The index of section `name`: the standard sections first, then the registry's own, added at the
 * end when `create` is set; -1 when it is missing. */
int igRegistry_GetSectionIndex(igRegistry *self, char *name, int create) {
    int n;
    int i;
    int result;
    igStringObj *created;
    igObjectList *sections;
    for (i = 0; i < 11; i++) {
        if (igStrcasecmp(name, g_registrySectionNames[i]) == 0) {
            return i;
        }
    }
    n = ((igObjectList *)self->_additionalSectionNames)->_count;
    for (i = 0; i < n; i++) {
        if (igStrcasecmp(name, igStringObj_Text(((igStringObj **)((igObjectList *)self->_additionalSectionNames)->_data)[i])) == 0) {
            return i + 11;
        }
    }
    if (create != 0) {
        igSmartPointer<igStringObj> section((igStringObj *)igStringObj_Create((int)igObject_GetAllocator((igObject *)self)));
        igStringObj_Set(section.get(), name);
        ObjectList_AppendRetained((igObjectList *)self->_additionalSectionNames, section.get());
        return n + 11;
    }
    return -1;
}

typedef igSmartPointer<igTDataList<igRegistryValue *> > IniPairListRef;

/* The number of keys a section holds. */
int igRegistry_GetNumValuesInSection(int registry, int section) {
    int keys = 0;
    for (int i = 0; i < ((IniPairListRef &)((igRegistry *)registry)->_valueTable)->count(); i++) {
        igRegistryValue *entry = ((IniPairListRef &)((igRegistry *)registry)->_valueTable)->get(i);
        if (entry != 0 && entry->_section == section) {
            keys++;
        }
    }
    return keys;
}

/* Copies the index-th key of a section to *key, retained; false when the section has fewer keys. */
bool igRegistry_GetKeyName(int registry, int section, int index, igStringObj **key) {
    int i;
    int seen = 0;
    bool found = false;
    for (i = 0; i < ((IniPairListRef &)((igRegistry *)registry)->_valueTable)->count(); i++) {
        igRegistryValue *entry = ((IniPairListRef &)((igRegistry *)registry)->_valueTable)->get(i);
        if (entry != 0 && entry->_section == section) {
            if (seen == index) {
                *(igSmartPointer<igStringObj> *)key = (igStringObj *)entry->_valueName;
                found = true;
                break;
            }
            seen++;
        }
    }
    return found;
}

bool igRegistry_GetValueInt(igRegistry *registry, int section, const char *key, int *out, int defaultValue, int create) {
    bool found;
    void *value;

    found = false;
    value = ((void *)igRegistry_FindValue(registry, section, key, 0));
    if ((value != 0) && (igStringObj_ToInt((igStringObj *)((void *)((igRegistryValue *)value)->_value), (int *)out) != 0)) {
        found = true;
    }
    if (!found) {
        *out = defaultValue;
        if (create != 0) {
            igRegistry_SetValueInt((void *)registry, section, key, defaultValue);
        }
    }
    return found;
}

bool igRegistry_GetValueFloat(igRegistry *registry, int section, const char *key, float *out, int create, float defaultValue) {
    bool found;
    void *value;

    found = false;
    value = (void *)(((void *)igRegistry_FindValue(registry, section, key, 0)));
    if ((value != 0) && (igStringObj_ToFloat((igStringObj *)((void *)((igRegistryValue *)value)->_value), (float *)out) != 0)) {
        found = true;
    }
    if (!found) {
        *out = defaultValue;
        if (create != 0) {
            igRegistry_SetValueFloat((int)registry, section, key, defaultValue);
        }
    }
    return found;
}

int igRegistry_GetValueStringObj(igRegistry *registry, int section, const char *key, igStringObj **out, const char *defaultValue, int create) {
    igRegistryValue *node;
    igStringObj *string;
    igStringObj *old;
    node = igRegistry_FindValue((igRegistry *)registry, section, key, 0);
    if (node != 0) {
        string = (igStringObj *)node->_value;
        if (string) {
            ++string->_refCount;
        }
        old = *out;
        if (old) {
            --old->_refCount;
            if (((unsigned long long)(long long)(int)old->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)old);
        }
        *out = string;
    } else {
        igSmartPointer<igStringObj> created((igStringObj *)igStringObj_Create(((int)igObject_GetAllocator((igObject *)registry))));
        igStringObj_Set(created.p, defaultValue);
        string = created.p;
        if (string) {
            ++string->_refCount;
        }
        old = *out;
        if (old) {
            --old->_refCount;
            if (((unsigned long long)(long long)(int)old->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)old);
        }
        *out = string;
        if (create != 0) {
            igRegistry_SetValueString((void *)registry, section, key, (const char *)defaultValue);
        }
    }
    return node != 0;
}

static inline int valueStringPool(void) {
    int p;
    if (g_stringPool == 0) {
        p = ((int)StringPool_Allocate(0x10));
        if (p != 0) {
            p = ((int)StringPool_Construct((StringPool *)p));
        }
        g_stringPool = (StringPool *)p;
    }
    return (int)g_stringPool;
}

static inline char *valueText(igStringObj *s) { char *t = (char *)s->_buffer; if (t == 0) { return g_stringObjEmptyText; } return t; }

static inline void assignInterned(int **slot, char *s) {
    int *v = ((int *)StringPool_Intern((StringPool *)(valueStringPool()), (const char *)s));
    int *old = *slot;
    int *hd;
    int rc;
    if (old != 0) {
        hd = old - 2;
        rc = old[-1] - 1;
        old[-1] = rc;
        if (rc == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*hd), (StringTokenHeader *)hd);
        }
    }
    *slot = v;
}

int igRegistry_GetValueString(igRegistry *registry, int section, const char *key, char **out, char *def, int create) {
    igRegistryValue *value;

    value = igRegistry_FindValue(registry, section, key, 0);
    if (value != 0) {
        assignInterned((int **)out, valueText((igStringObj *)value->_value));
    } else {
        assignInterned((int **)out, def);
        if (create != 0) {
            igRegistry_SetValueString((void *)registry, section, key, (const char *)def);
        }
    }
    return value != 0;
}

static inline int listStringPool(void) {
    int p;
    if (g_stringPool == 0) {
        p = ((int)StringPool_Allocate(0x10));
        if (p != 0) {
            p = ((int)StringPool_Construct((StringPool *)p));
        }
        g_stringPool = (StringPool *)p;
    }
    return (int)g_stringPool;
}

static inline char *listValueText(igStringObj *s) { char *t = (char *)s->_buffer; if (t == 0) { return g_stringObjEmptyText; } return t; }

static inline int *intern(char *s) {
    if (s == 0) {
        return 0;
    }
    return ((int *)StringPool_Intern((StringPool *)(listStringPool()), (const char *)s));
}

static inline void releaseRef(int *old) {
    int *hd;
    int rc;
    if (old != 0) {
        hd = old - 2;
        rc = old[-1] - 1;
        old[-1] = rc;
        if (rc == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*hd), (StringTokenHeader *)hd);
        }
    }
}

static inline void setStringAt(igStringRefList *l, int i, int **v) {
    int n = l->_count;
    if (n != 0 && i >= 0 && i < n) {
        int **slot = &((int **)l->_data)[i];
        int *w = *v;
        if (w != 0) {
            w[-1] = w[-1] + 1;
        }
        releaseRef(*slot);
        *slot = *v;
    }
}

bool igRegistry_GetValueStringList(void *self, int section, const char *key, igStringRefList *list, int create) {
    igStringObj *a;
    igStringObj *b;
    const char *saved;
    int i; igRegistryValue *p; int n; int j; igStringObj *c; char *s2; igStringObj *held; igStringObj *c2; int at; int at2;

    saved = key;
    p = igRegistry_FindValue((igRegistry *)self, section, key, 0);
    if (p != 0) {
        igStringObj_Split((igStringObj *)p->_value, 0x2C, (igTDataList<char *> *)list);
        *(igStringObj **)&a = (igStringObj *)(igStringObj_Create(((int)igObject_GetAllocator((igObject *)self))));
        for (i = 0; i < list->_count; i++) {
            {
                igStringRef r1 = StringList_CopyRetained(list, i);
                igStringObj_Set(a, r1.p);
            }
            igStringObj_Trim(a);
            int *tmp;
            *(int **)&tmp = intern(listValueText(a));
            setStringAt(list, i, &tmp);
            releaseRef(tmp);
        }
        held = a;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long)((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
        }
    } else if (create != 0) {
        *(igStringObj **)&b = (igStringObj *)(igStringObj_Create(((int)igObject_GetAllocator((igObject *)self))));
        n = list->_count;
        if (n != 0) {
            igStringRef r2 = StringList_CopyRetained(list, 0);
            igStringObj_Set(b, r2.p);
        }
        for (j = 1; j < n; j++) {
            c = b; at = c->_length;
            igStringObj_Insert(c, (char *)",", at, strlen(","));
            igStringRef r3 = StringList_CopyRetained(list, j);
            /* matching construct: the word is read through the holder's address; r3.p swaps s0 and s6 */
            c2 = b; s2 = *(char **)&r3; at2 = c2->_length; igStringObj_Insert(c2, s2, at2, strlen(s2));
        }
        igRegistry_SetValueString(self, section, saved, (const char *)(listValueText(b)));
        held = b;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long)((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
        }
    }
    return p != 0;
}

/* Read a boolean value; when it is missing or unreadable, `defaultValue` is returned through `value`
 * and, with `create`, written into the registry. */
unsigned char igRegistry_GetValueBool(igRegistry *registry, int section, const char *name, unsigned char *value, int defaultValue, int create) {
    unsigned char found = 0;
    igRegistryValue *entry = igRegistry_FindValue(registry, section, name, 0);
    if (entry != 0 && igStringObj_ParseBool((igStringObj *)entry->_value, (char *)value)) {
        found = 1;
    }
    if (!found) {
        *value = defaultValue;
        if (create != 0) {
            igRegistry_SetValueBool((int)registry, section, name, defaultValue);
        }
    }
    return found;
}

/* Parse a flags value: a number (decimal or 0x hex), or names of the enum's values separated by spaces
 * and or-ed together. Leading text that matches `format` up to its `%s` is skipped, and the rest of
 * `format` ends the value. False when part of it is not understood. */
bool igRegistry_ParseEnumFlags(char *text, int *value, int metaEnum, char *format) {
    char *s;
    char *end;
    bool ok;
    char *found;
    char *token;
    int length;
    char name[256];
    int flag;
    s = text;
    end = text + strlen(text);
    *value = 0;
    ok = true;
    while (*s && (_ctype_[*s + 1] & 8)) s++;
    while (*s && *format && *s == *format) {
        s++;
        format++;
    }
    if (*format == '%') {
        format++;
        if (*format == 's') format++;
    }
    if (*format != 0) {
        found = strstr(s, format);
        if (found != 0) end = found;
        else ok = false;
    }
    if ((_ctype_ + 1)[*s] & 4) {
        if (strncmp(text,"0x", 2) == 0) {
            if (sscanf(text,"0x%x", value) == 1) return 1;
        } else {
            if (sscanf(text, (const char *)percent_d_7, value) == 1) return 1;
        }
    } else {
        while (*s && s < end) {
            while (*s && (_ctype_[*s + 1] & 8)) s++;
            token = s;
            while (*s && !(_ctype_[*s + 1] & 8) && s < end) s++;
            length = s - token;
            if (*token != 0) {
                if (length > 255) length = 255;
                strncpy(name, token, length);
                name[length] = 0;
                flag = 0;
                if (igMetaEnum_GetValueByName((igMetaEnum *)metaEnum, name, &flag) == g_resultSuccess) {
                    *value |= (unsigned int)flag;
                } else {
                    ok = false;
                }
            }
        }
    }
    return ok;
}

static inline bool sameChar(int a, int b) { return (char)a == (char)b; }
static inline int isSpaceChar(char c) { return _ctype_[c + 1] & 8; }

/* Parse a single enum value the same way: a number, or one value name. */
int igRegistry_ParseEnumValue(char *text, int *value, igMetaEnum *metaEnum, char *format) {
    char name[260];
    char *end;
    int length;
    char *token;
    char *f;
    char *s;
    f = format;
    s = text;
    end = text + strlen(text);
    while (!(!*s) && isSpaceChar(*s)) {
        s++;
    }
    while (!(!*s) && *f != 0 && sameChar(*s, *f)) {
        s++;
        f++;
    }
    if (*f == '%') {
        f++;
        if (*f == 's') {
            f++;
        }
    }
    if (*f != 0) {
        char *found = strstr(s, f);
        if (found != 0) {
            end = found;
        } else {
            return 0;
        }
    }
    if ((_ctype_ + 1)[*s] & 4) {
        if (strncmp(text,"0x", 2) == 0) {
            if (sscanf(text,"0x%x", value) == 1) {
                return 1;
            }
        } else if (sscanf(text, (const char *)percent_d_7, value) == 1) {
            return 1;
        }
    } else {
        token = s;
        while (!(!*s) && !isSpaceChar(*s) && s < end) {
            s++;
        }
        if (*token != 0) {
            length = s - token;
            if (length > 255) {
                length = 255;
            }
            strncpy(name, token, length);
            name[length] = 0;
            if (igMetaEnum_GetValueByName(metaEnum, name, value) == g_resultSuccess) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}



static inline int enumValueText(void *o) { int a = *(int *)((char *)(*(int *)((char *)(o) + 12)) + 8); if (a == 0) { return (*(int *)&g_stringObjEmptyText); } return a; }

int igRegistry_GetValueEnum(int registry, int section, const char *key, int metaEnum, int *out, int defaultValue, int create) {
    void *value;
    value = (void *)(((void *)igRegistry_FindValue((igRegistry *)registry, section, key, 0)));
    if (value != 0) {
        igRegistry_ParseEnumValue((char *)(enumValueText(value)), out, (igMetaEnum *)metaEnum, (char *)&percent_s[0]);
    } else {
        *out = defaultValue;
        if (create != 0) {
            igRegistry_SetValueInt((void *)registry, section, key, defaultValue);
        }
    }
    return value != 0;
}

static inline int flagsValueText(void *o) { int a = *(int *)((char *)(*(int *)((char *)(o) + 12)) + 8); if (a == 0) { return (*(int *)&g_stringObjEmptyText); } return a; }

int igRegistry_GetValueFlags(int registry, int section, const char *key, int metaEnum, int *out, int defaultValue, int create) {
    void *value;
    value = (void *)(((void *)igRegistry_FindValue((igRegistry *)registry, section, key, 0)));
    if (value != 0) {
        igRegistry_ParseEnumFlags((char *)(flagsValueText(value)), out, metaEnum, (char *)&percent_s[0]);
    } else {
        *out = defaultValue;
        if (create != 0) {
            igRegistry_SetValueInt((void *)registry, section, key, defaultValue);
        }
    }
    return value != 0;
}

int igRegistry_GetValueEntry(void *self, int index) {
    return ((int *)((igRegistryValueList *)((igRegistry *)self)->_valueTable)->_data)[index];
}

int igRegistry_GetValueCount(void *self) {
    return ((igRegistryValueList *)((igRegistry *)self)->_valueTable)->_count;
}

int igRegistry_SetValueInt(void *registry, int section, const char *key, int number) {
    void *value;
    value = (void *)((void *)igRegistry_FindValue((igRegistry *)registry, section, key, 1));
    if (value == 0) return 0;
    igStringObj_SetInt(((igRegistryValue *)value)->_value, number, (const char *)percent_d_7);
    return 1;
}

int igRegistry_SetValueFloat(int a0, int a1, const char *a2, float x) {
    igRegistryValue *o = igRegistry_FindValue((igRegistry *)a0, a1, a2, 1);
    if (o == 0) {
        return 0;
    }
    igStringObj_SetFloat(o->_value, "%f", x);
    return 1;
}

int igRegistry_SetValueString(void *registry, int section, const char *key, const char *value) {
    igRegistryValue *entry = igRegistry_FindValue((igRegistry *)registry, section, key, 1);
    if (entry == 0) return 0;
    igStringObj_Set((igStringObj *)entry->_value, value);
    return 1;
}

int igRegistry_SetValueBool(int registry, int section, const char *key, int flag) {
    void *value;

    value = (void *)(((void *)igRegistry_FindValue((igRegistry *)registry, section, key, 1)));
    if (value == 0) {
        return 0;
    }
    igStringObj_SetBool(((igRegistryValue *)value)->_value, flag, 0);
    return 1;
}

void igRegistry_Clear(igRegistry *self) {
    int n2;
    int j;
    igTDataList<igObject *> *l;
    int n1;
    int i;
    igObject *p;

    l = (igTDataList<igObject *> *)self->_additionalSectionNames;
    n1 = l->_count;
    for (i = 0; i < n1; i++) {
        p = l->_data[i];
        if (p != 0) {
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long)((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    n2 = l->_count;
    for (j = 0; j < n2; j++) {
        l->_data[j] = 0;
    }
    l->_count = 0;
    ObjectList_ClearRetainedPreserveCount((igTDataList<igObject *> *)self->_valueTable);
}

/* Read registry text: `[section]` lines open a section, `key = value` lines set values (only new ones
 * unless `overwrite`), and `#` lines are directives. */
void igRegistry_ParseFile(igRegistry *self, igFileView *file, int overwrite) {
    char equals;
    unsigned char showQueries;
    int lineNumber;
    char line[4096];
    char key[4096];
    char value[4096];
    int fields;
    int section;
    igRegistry *config;

    lineNumber = 0;
    section = -1;
    while (igRegistry_ReadLine(self, file, line, &lineNumber)) {
        if (sscanf(line," %c ", value) <= 0) {
            continue;
        }
        if (value[0] == '#') {
            igRegistry_ProcessInclude(self, file, line, lineNumber, overwrite);
            continue;
        }
        if (sscanf(line," [ %[_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./\\-] ]", value) == 1) {
            section = igRegistry_GetSectionIndex(self, value, 1);
            continue;
        }
        fields = sscanf(line," %[_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./\\-] %c %[^\r\n]", key, &equals, value);
        if (fields <= 0 || fields == 1) {
            continue;
        }
        if (fields > 1 && equals != '=') {
            continue;
        }
        if (fields == 2) {
            value[0] = 0;
        }
        if (overwrite == 0 && igRegistry_FindValue(self, section, key, 0) != 0) {
            continue;
        }
        igRegistry_SetValueString(self, section, key, value);
    }
    config = g_objectSystem->configRegistry;
    showQueries = self->_showQueries;
    igRegistry_GetValueBool(config, 2,"showRegistryQueries", &showQueries, showQueries, 0);
    self->_showQueries = showQueries;
    if (self->_showQueries != 0 && config == self) {
        igRegistry_GetValueBool(config, 2,"showRegistryQueries", &showQueries, showQueries, 0);
    }
}

bool igRegistry_ReadLine(void *unused, igFileView *s, char *buf, int *lines) {
    int c = s->GetChar();
    int prev = 0;
    bool comment = false;
    int n = 0;
    bool ret = false;
    bool lead = true;
    while (c != -1 && c != 0) {
        while (lead) {
            if (c == 0x20 || c == 9) { prev = c; c = s->GetChar(); }
            else lead = false;
        }
        if (c == 13) { c = s->GetChar(); continue; }
        if (c != 10) {
            if (!comment) {
                if (c == 0x3B) comment = true;
                else if (c == 0x2F && prev == 0x2F) { n -= 1; comment = true; }
                else {
                    if (n < 0xFFF) buf[n] = c;
                    n += 1;
                }
            }
            goto next;
        }
        if (prev != 0x5C) break;
        lead = true;
        *lines += 1;
        if (!comment) n -= 1;
    next:
        prev = c;
        c = s->GetChar();
    }
    if (n > 0 || c != -1) {
        ret = true;
        *lines += 1;
    }
    if (n >= 0x1000) n = 0xFFF;
    buf[n] = 0;
    return ret;
}

igRegistryValue *igRegistry_FindValue(igRegistry *self, int section, const char *key, int create) {
    int i = 0;
    int freeSlot = -1;
    igSmartPointer<igRegistryValue> r;
    for (; i < ((igRegistryValueList *)self->_valueTable)->_count; i++) {
        igRegistryValue *entry = ((igRegistryValue **)((igRegistryValueList *)self->_valueTable)->_data)[i];
        igRegistryValue *old;
        if (entry != 0) entry->_refCount = entry->_refCount + 1;
        old = r.p;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
        }
        r.p = entry;
        if (r.p != 0 && section == r.p->_section) {
            int name;
            if (self->_valueNameCaseSensitive != 0) {
                name = (((igStringObj *)r.p->_valueName)->_buffer == 0) ? (*(int *)&g_stringObjEmptyText) : ((igStringObj *)r.p->_valueName)->_buffer;
                if (strcmp((const char *)name, key) == 0) {
                    return r;
                }
            } else {
                name = (((igStringObj *)r.p->_valueName)->_buffer == 0) ? (*(int *)&g_stringObjEmptyText) : ((igStringObj *)r.p->_valueName)->_buffer;
                if (igStrcasecmp((const char *)name, key) == 0) {
                    return r;
                }
            }
        } else if (r.p == 0 && freeSlot < 0) {
            freeSlot = i;
        }
    }
    if (create != 0) {
        int entry;
        igRegistryValueList *values;
        igRegistryValue *old;
        igRegistryValue *t;
        if (freeSlot < 0) {
            freeSlot = ((igRegistryValueList *)self->_valueTable)->_count;
            ObjectList_ResizeRetained((igTDataList<igObject *> *)(((igRegistryValueList *)self->_valueTable)), freeSlot * 2);
        }
        entry = ((int)igObject_GetAllocator((igObject *)self));
        old = r.p;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
        }
        r.p = (igRegistryValue *)igRegistryValue_Create(entry);
        values = (igRegistryValueList *)self->_valueTable;
        self = (igRegistry *)r.p;
        if (self != 0) ((igRegistryValue *)self)->_refCount = ((igRegistryValue *)self)->_refCount + 1;
        old = ((igRegistryValue **)values->_data)[freeSlot];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
        }
        if (values->_count != 0 && freeSlot >= 0 && freeSlot < values->_count) ((igRegistryValue **)values->_data)[freeSlot] = (igRegistryValue *)self;
        r.p->_section = section;
        igStringObj_Set((igStringObj *)r.p->_valueName, key);
        return r;
    }
    return 0;
}

int igRegistry_GetSectionName(void *self, int section) {
    int name;

    if (section < 0xB) {
        return ((int *)g_registrySectionNames)[section];
    }
    name = ((igStringObj **)((igTDataList<int> *)((igRegistry *)self)->_additionalSectionNames)->_data)[section - 11]->_buffer;
    if (name == 0) return (*(int *)&g_stringObjEmptyText); return name;
}

int g_registryIncludeDepth;

/* An `#include "file"` or `#include <file>` directive: read the named file, relative to this file's
 * directory first, into the registry. Includes nest at most 12 deep. */
void igRegistry_ProcessInclude(igRegistry *self, igFileView *file, char *line, int lineNumber, int overwrite) {
    char open;
    char close;
    char path[4096];
    int found;

    if (sscanf(line," # include %c %[^<>\"\n\r] %c", &open, path, &close) != 3) {
        return;
    }
    if (open != '"' && open != '<') return;
    if ((open == '"' && close != '"') || (open == '<' && close != '>')) return;
    if (g_registryIncludeDepth < 12) {
        g_registryIncludeDepth += 1;
        igSmartPointer<igRegistry> include((igRegistry *)igRegistry_Create((int)igObject_GetAllocator((igObject *)self)));
        found = 0;
        igSmartPointer<igStringObj> directory((igStringObj *)igStringObj_Create((int)igObject_GetAllocator((igObject *)self)));
        igStringObj_Set(directory.get(), file->_fileName);
        igStringObj_RemovePathFilename(directory.get());
        if (directory.get()->_length != 0) {
            igRegistry *target = include.get();
            found = igRegistry_Load(target, path, igStringObj_Text(directory.get())) & 0xFF;
        }
        if (found != 0 || igRegistry_Load(include.get(), path, (char *)"")) {
            igRegistry_Merge(self, include.get(), overwrite);
        }
        g_registryIncludeDepth -= 1;
    }
}

int igReportNotice(const char *format, ...) {
    int named = __builtin_args_info(2);
    int offset;
    if (named >= 8) offset = 0; else offset = (8 - named) * 8;
    return igReport_VReport(4, format, (int)((char*)__builtin_next_arg(format) - offset));
}

int igReport_Detail(const char *format, ...) {
    int named = __builtin_args_info(2);
    int offset;
    if (named >= 8) offset = 0; else offset = (8 - named) * 8;
    return igReport_VReport(6, format, (int)((char*)__builtin_next_arg(format) - offset));
}

int igReport_Info(const char *format, ...) {
    int named = __builtin_args_info(2);
    int offset;
    if (named >= 8) offset = 0; else offset = (8 - named) * 8;
    return igReport_VReport(5, format, (int)((char *)__builtin_next_arg(format) - offset));
}

int igReportError(const char *format, ...) {
    int named = __builtin_args_info(2);
    int offset;
    if (named >= 8) offset = 0; else offset = (8 - named) * 8;
    return igReport_VReport(1, format, (int)((char*)__builtin_next_arg(format) - offset));
}

int igReport_Warning(const char *format, ...) {
    int named = __builtin_args_info(2);
    int offset;
    if (named >= 8) offset = 0; else offset = (8 - named) * 8;
    return igReport_VReport(2, format, (int)((char*)__builtin_next_arg(format) - offset));
}

int g_reportLevel = 5;
unsigned char g_reportAssertOnErrors = 1;

int igReport_DefaultHandler(int level, int message) {
    const char *levelName;
    if (((int *)&g_reportLevel)[0] < level) {
        return 0;
    }
    levelName = "UNKNOWN";
    switch (level) {
    case 0: levelName = "INTERNAL ERROR"; break;
    case 1: levelName = "ERROR"; break;
    case 2: levelName = "WARNING"; break;
    case 3: levelName = "DEPRECATION"; break;
    case 4: levelName = "NOTICE"; break;
    case 5: levelName = "INFO"; break;
    case 6: levelName = "DETAIL"; break;
    }
    if (level < 4) {
        igReport_ErrorPrintf((int)"%s: %s\n", levelName, message);
        igReport_FlushError();
    } else {
        igReport_Printf("%s: %s\n", levelName, message);
        igReport_Flush();
        return 0;
    }
    igReport_ErrorPrintf((int)"No stack trace available in this build.\n");
    igReport_FlushError();
    if (g_reportAssertOnErrors != 0) {
        if (level == 0 || level == 1) return 1;
    }
    return 0;
}

int (*g_reportHandler)(int, char *) = (int (*)(int, char *))igReport_DefaultHandler;

int igReport_VReport(int level, const char *format, int args) {
    char buf[0x1000];
    int length;

    if (g_reportHandler == 0) {
        return 0;
    }
    length = vsnprintf(buf, 0x1000, format, (char *)args);
    if ((length < 0) || (length >= 0x1000)) {
        buf[0xFFF] = 0;
    }
    return g_reportHandler(level, buf);
}

static inline int allocator(void) {
    int a = ((int)Memory_GetCurrentAllocator());
    if (g_useOwnerAllocator != 0) {
        return a;
    }
    return ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString));
}

static inline char *levelText(igStringObj *s) {
    char *t = (char *)s->_buffer;
    if (t == 0) {
        return (g_stringObjEmptyText);
    }
    return t;
}

char g_reportSettingsLoaded;

void igReport_ReadSettings(void) {
    g_reportSettingsLoaded = 1;
    igRegistry *config = g_objectSystem->configRegistry;
    if (config != 0) {
        igRegistry_GetValueBool(config, 2,"assertOnErrors", &g_reportAssertOnErrors, 1, 0);
        igStringObj *name = (igStringObj *)igStringObj_Create(allocator());
        if (igRegistry_GetValueStringObj(config, 2,"defaultReportLevel", &name, (char *)"", 0) != 0) {
            char *t = levelText(name);
            if (strcmp(t,"kDetail") == 0) {
                g_reportLevel = 6;
            } else if (strcmp(t,"kInfo") == 0) {
                g_reportLevel = 5;
            } else if (strcmp(t,"kNotice") == 0) {
                g_reportLevel = 4;
            } else if (strcmp(t,"kWarning") == 0) {
                g_reportLevel = 2;
            } else if (strcmp(t,"kError") == 0) {
                g_reportLevel = 1;
            }
        }
        igRelease(name);
    }
}

void igReport_RestoreDefaults(void) {
    g_reportHandler = (int (*)(int, char *))igReport_DefaultHandler;
    g_reportSettingsLoaded = 0;
    ((int *)&g_reportLevel)[0] = 5;
}

igSmartPointer<igObject> igResource_GetDirectory(void *directory, const char *name) {
    if (strcmp(name, "igImageDirectory") == 0) {
        return igSmartPointer<igObject>((igObject *)igResource_GetImageDirectory((igResource *)directory), kRetainReference);
    }
    return igSmartPointer<igObject>((igObject *)igProperty_FindByName((igObjectList *)((igResource *)directory)->_directoryList, (igMetaField *)g_igDirectory_nameField, name), kRetainReference);
}

int igResource_AddDirectory(int *p, int directory)
{
    return ObjectList_AppendRetained((igObjectList *)((igResource *)p)->_directoryList, (igObject *)directory);
}

static inline void setNames(igResource *self, const igSmartPointer<igObject> &value) {
    igObject *held = value.p;
    igObject *old;
    if (held) held->_refCount = held->_refCount + 1;
    old = (igObject *)self->_alignmentStrings;
    if (old) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    self->_alignmentStrings = (int)held;
}

static inline void setValues(igResource *self, const igSmartPointer<igObject> &value) {
    igObject *held = value.p;
    igObject *old;
    if (held) held->_refCount = held->_refCount + 1;
    old = (igObject *)self->_alignmentValues;
    if (old) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    self->_alignmentValues = (int)held;
}

void igResource_AddAlignment(igResource *self, const char *name, int value) {
    if (self->_alignmentStrings == 0) {
        setNames(self, igSmartPointer<igObject>((igObject *)igStringObjList_Create((int)(((void *)igObject_GetAllocator((igObject *)self))))));
        setValues(self, igSmartPointer<igObject>((igObject *)igIntList_Create((int)(((void *)igObject_GetAllocator((igObject *)self))))));
    }
    igSmartPointer<igStringObj> entry((igStringObj *)igStringObj_Create((int)(((void *)igObject_GetAllocator((igObject *)self)))));
    igStringObj_Set(entry.p, name);
    ObjectList_AppendRetained((igObjectList *)self->_alignmentStrings, (igObject *)entry.p);
    igTDataList<int> *values = (igTDataList<int> *)self->_alignmentValues;
    int top = values->count();
    if (top < values->_capacity) {
        values->_count = values->_count + 1;
    } else {
        List_Resize(values, top + 1, 4);
    }
    values->_data[top] = value;
}

static inline void setImageDirectory(igResource *owner, const igSmartPointer<igDirectory> &value) {
    igDirectory *held = value.p;
    igDirectory *old;
    if (held != 0) held->_refCount = held->_refCount + 1;
    old = (igDirectory *)owner->_imageDirectory;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old);
    }
    owner->_imageDirectory = (int)held;
}

igDirectory *igResource_GetImageDirectory(igResource *self) {
    if (self->_imageDirectory == 0) {
        int *hd;
        int v;
        int s2;
        igDirectory *s0;
        int old;
        setImageDirectory(self, igSmartPointer<igDirectory>(((igDirectory *)igDirectory_Create((int)igObject_GetAllocator((igObject *)self)))));
        s0 = (igDirectory *)self->_imageDirectory;
        if (0 == g_stringPool) {
            v = ((int)StringPool_Allocate(16));
            if (v != 0) {
                v = ((int)StringPool_Construct((StringPool *)v));
            }
            g_stringPool = (StringPool *)v;
        }
        s2 = (int)StringPool_Intern((StringPool *)g_stringPool, (const char *)(((char *)"igImageDirectory")));
        old = s0->_name;
        if (old != 0) {
            hd = (int *)(old - 8);
            v = *(int *)(old - 4) - 1;
            *(int *)(old - 4) = v;
            if (v == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*hd), (StringTokenHeader *)hd);
            }
        }
        s0->_name = s2;
        ((igDirectory *)self->_imageDirectory)->_managingResource = (int)self;
        igResource_AddDirectory((int *)self, self->_imageDirectory);
    }
    fflush(_impure_ptr->_stdout);
    return (igDirectory *)self->_imageDirectory;
}

void igResource_AsyncLoadThreadProc(int *result, void *file) {
    int resource;

    if (file == 0) {
        *result = g_resultFailure.v;
    } else {
        resource = (int)((igDirectoryView *)file)->_managingResource;
        if (((igDirectoryView *)file)->_loadedRefCount > 1) {
            igResource_ReadFileWithSearchPaths((igResource *)resource, (igIGBFileView *)file);
            igResource_UnloadDirectory((igResource *)resource, (const char *)((igDirectoryView *)file)->_name);
        }
        *result = g_resultSuccess.v;
    }
}

