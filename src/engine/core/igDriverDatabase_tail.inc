/* Read the verbose flag from the configuration registry and give each of the 13 properties an
 * empty value string. */
void igDriverDatabase_InitDefaults(igDriverDatabase *database) {
    unsigned char verbose;
    int i;
    igObject_InitDefaults((int)database);
    igRegistry_GetValueBool((int)((ObjectSystemView *)g_objectSystem[0])->configRegistry, 2, text_driverDatabaseVerbose, (char *)&verbose, database->_verbose, 1);
    database->_verbose = verbose;
    ObjectList_ResizeRetained((igTDataList<igObject *> *)database->_currentProperties, 13);
    ObjectList_ResizeRetained((igTDataList<igObject *> *)database->_subPropertyNames, 13);
    ObjectList_ResizeRetained((igTDataList<igObject *> *)database->_subPropertyValues, 13);
    i = 0;
    do {
        {
            igSmartPointer<igStringObj> value((igStringObj *)igStringObj_Create((int)igObject_GetAllocator((int)database)));
            objectListSetRetained(i, value.get(), (igObjectList *)database->_currentProperties);
        }
        i++;
    } while (i < 13);
}

void igDriverDatabase_ReleaseDefaults(int self) {
    igDriverDatabase_ClearRawDatabase((int *)self);
    igObject_ReleaseDefaults(self);
}

void igDriverDatabase_SetCurrentProperty(void *arg0, int arg1, int arg2) {
    igStringObj_Set(*(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 16) + (arg1 * 4)), arg2);
}

int igDriverDatabase_GetCurrentProperty(void *arg0, int arg1) {
    int var_v0;

    var_v0 = *(int *)((char *)((*(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 16) + (arg1 * 4)))) + 8);
    if (var_v0 == 0) {
        var_v0 = ((int *)g_stringObjEmptyText)[0];
    }
    return var_v0;
}

int igDriverDatabase_GetSubPropertyValue(igDriverDatabase *arg0, int arg1, int arg2) {
    igSmartPointer<igObject> sp5C;
    igSmartPointer<igObject> sp58;
    int sp54, sp50;
    igObject *x;
    int idx;
    int v;
    int r;
    sp5C.p = 0;
    sp58.p = 0;
    x = ((igObject **)((igObjectList *)arg0->_subPropertyNames)->_data)[arg1];
    if (x == 0) return 0;
    sp5C = x;
    sp58 = ((igObject **)((igObjectList *)arg0->_subPropertyValues)->_data)[arg1];
    if (arg2 == 0) {
        v = 0;
    } else {
        if (g_stringPool[0] == 0) {
            int al = ((int)StringPool_Allocate(16));
            if (al != 0) al = ((int)StringPool_Construct((StringPool *)al));
            g_stringPool[0] = al;
        }
        v = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)arg2);
    }
    sp54 = v;
    idx = FUN_001cafc0(sp5C.p, &sp54, 0);
    releaseString((const char *)sp54);
    if (idx >= 0) {
        StringList_CopyRetained(&sp50, sp58.p, idx);
        r = sp50;
        releaseString((const char *)r);
        return r;
    }
    return 0;
}

static inline char *textOf(const igSmartPointer<igStringObj> &ref) {
    char *s = (char *)ref.get()->_buffer;
    s = (s == 0) ? g_stringObjEmptyText[0] : s;
    return s;
}

void igDriverDatabase_GatherProperties(void *self, igTDataList<igVisualContextView *> *list) {
    int i;
    igSmartPointer<igStringObj> text(((igStringObj *)igStringObj_Create((int)(((void *)igObject_GetAllocator((int)self))))));
    if (igDriverDatabase_GetOSName((void *)(text.get())) != 0) {
        igDriverDatabase_SetCurrentProperty(self, 0, (int)(textOf(text)));
    }
    if (igDriverDatabase_GetCpuVendor((void *)(text.get())) != 0) {
        igDriverDatabase_SetCurrentProperty(self, 6, (int)(textOf(text)));
    }
    if (igDriverDatabase_GetCpuType((void *)(text.get())) != 0) {
        igDriverDatabase_SetCurrentProperty(self, 7, (int)(textOf(text)));
    }
    if (list == 0 || list->_count == 0) {
        return;
    }
    for (i = 0; i < list->_count; i++) {
        list->_data[i]->Describe(self);
    }
}

static inline int openPath(igDriverDatabase *database, const igSmartPointer<igStringObj> &path) {
    igFileView *file = (igFileView *)database->_databaseFile;
    int text = path.p->_buffer;
    if (text == 0) text = ((int *)g_stringObjEmptyText)[0];
    return file->Open((const char *)text, (const char *)&DAT_004f96a8[0]);
}

int igDriverDatabase_Load(igDriverDatabase *arg0, const char *arg1, const char *arg2) {
    int s0;
    igStringRef name((char *)arg1);
    const char *p5 = name.p;
    if (p5 == 0 || strlen(p5) == 0) {
        name = (char *)&text_drivers_ini[0];
    }
    {
        int al = ((int)igObject_GetAllocator((int)arg0));
        igRelease((igObject *)arg0->_databaseFile);
        arg0->_databaseFile = (int)((igObject *)igFile_Create(al));
    }
    s0 = ((igFileView *)arg0->_databaseFile)->Open(name.p, (const char *)&DAT_004f96a8[0]);
    if (s0 == 0) {
        if (arg2 == 0 || strlen(arg2) == 0) {
            arg2 = ((const char *)igObjectSystem_GetRootPath((int *)(((int *)g_objectSystem)[0])));
        }
        if (arg2 != 0 && strlen(arg2) != 0) {
            igSmartPointer<igFolderView> folder((igFolderView *)igFolder_Create(((int)igObject_GetAllocator((int)arg0))));
            folder.p->setFolderName((char *)arg2);
            s0 = openPath(arg0, folder.p->vfunc_23(name.p));
        }
    }
    if (s0 == 0) {
        igSmartPointer<igFolderView> folder((igFolderView *)igFolder_Create(((int)igObject_GetAllocator((int)arg0))));
        folder.p->setFolderName((char *)igObjectSystem_GetBasePath((int *)(((int *)g_objectSystem)[0])));
        s0 = openPath(arg0, folder.p->vfunc_23(name.p));
    }
    if (s0 == 0) {
        igRelease((igObject *)arg0->_databaseFile);
        arg0->_databaseFile = 0;
        return 0;
    }
    igStringObj_Set(arg0->_databaseFileName, *(int *)((char *)s0 + 12));
    igDriverDatabase_LoadDatabaseFile(arg0, (igFileView *)arg0->_databaseFile);
    ((igFileView *)arg0->_databaseFile)->Close();
    igRelease((igObject *)arg0->_databaseFile);
    arg0->_databaseFile = 0;
    return 1;
}

int igDriverDatabase_LoadFromFile(void *arg0, int arg1, int arg2) {
    if (arg1 == 0) {
        return 0;
    }
    igStringObj_Set(*(int *)((char *)arg0 + 36), arg2);
    igDriverDatabase_LoadFromString(arg0, arg1);
    return 1;
}

int igDriverDatabase_ClearRawDatabase(int *p)
{
    return igStringObj_Clear((igStringObj *)(*(int *)((char *)p + 40)));
}

static inline int n_of(const igTDataList<ConfigNode *> *list) { return list->_count; }

igTDataList<ConfigNode *> *igDriverDatabase_ParseDatabase(igDriverDatabase *s) {
    int cnt;
    ConfigNode *r;
    igTDataList<ConfigNode *> *l;
    int v;

    l = ((igTDataList<ConfigNode *> *)igDataList_Create(((int)igObject_GetAllocator((int)s))));
    s->_currentLine = 1;
    v = ((igStringObj *)s->_rawDatabase)->_buffer;
    if (v == 0) {
        v = ((int *)g_stringObjEmptyText)[0];
    }
    s->_dbIndex = v;
    do {
        r = FUN_002dae40(s);
        if (r != 0) {
            cnt = l->_count;
            if (cnt < l->_capacity) {
                l->_count = n_of(l) + 1;
            } else {
                List_Resize(l, cnt + 1, 4);
            }
            l->_data[cnt] = r;
        }
    } while (r != 0);
    return l;
}

static inline void clearSlot(igTDataList<ConfigNode *> *l, int i) {
    if (l->_count != 0 && i >= 0 && i < l->_count) {
        l->_data[i] = 0;
    }
}

void igDriverDatabase_DeleteConfigNodeList(void *self, igTDataList<ConfigNode *> *list) {
    int i = 0;
    goto first;
next:
    if (list->_data[i] != 0) {
        list->_data[i]->Delete(1);
    }
    clearSlot(list, i);
    i++;
test:
    if (i < list->_count) {
        goto next;
    }
done:
    list->_refCount = (int)list->_refCount - 1;
    if (((unsigned long long)((long long)(int)list->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(list);
    }
    return;
first:
    if (0 < list->_count) {
        goto test;
    }
    goto done;
}

void *igDriverDatabase_ConfigNode_Destruct(void *arg0, long long arg1) {
    if (arg0 != 0) {
        *(int *)((char *)(arg0) + 4) = (int)(&DAT_00530618[0]);
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            Memory_FreeBufferAliasB((void *)arg0);
        }
    }
    return arg0;
}

int igDriverDatabase_ApplyToRegistry(igDriverDatabase *arg0, int arg1, int arg2, int arg3) {
    int r;
    igTDataList<ConfigNode *> *a;
    int i;
    igSmartPointer<igRegistry> sp7C(((igRegistry *)igRegistry_Create(((int)igObject_GetAllocator((int)arg0)))));
    a = igDriverDatabase_ParseDatabase(arg0);
    for (i = 0; i < a->_count; i++) {
        igDriverDatabase_ProcessConfigNode(arg0, a->_data[i], sp7C.p, arg2);
    }
    igRegistry_Merge((void *)arg1, sp7C.p, arg3);
    r = *(char *)arg0->_dbIndex == 0;
    igDriverDatabase_DeleteConfigNodeList((void *)arg0, a);
    igDriverDatabase_ClearRawDatabase((int *)arg0);
    return r;
}

int FUN_002daab0(void)
{
    return 1;
}

/* Read the database file into the raw text, a line at a time; a ';' ends the line. */
void igDriverDatabase_LoadDatabaseFile(igDriverDatabase *self, igFileView *file) {
    char line[4096];
    char *p;
    int c;
    igStringObj *raw;
    unsigned int at;
    igDriverDatabase_ClearRawDatabase((int *)self);
    while (igDriverDatabase_ReadLineFromFile(self, file, line, 4096)) {
        p = line;
        while ((c = *p) != 0) {
            if (c == ';') {
                *p = '\n';
                p[1] = 0;
                break;
            }
            p++;
        }
        raw = (igStringObj *)self->_rawDatabase;
        at = raw->_length;
        igStringObj_Insert(raw, line, at, strlen(line));
    }
}

void igDriverDatabase_LoadFromString(void *arg0, int arg1) {
    char buf[4096];
    char *s2;
    int s1;
    char *p;
    int c;
    igDriverDatabase_ClearRawDatabase((int *)arg0);
    while (igDriverDatabase_ReadLineFromString((igDriverDatabase *)arg0, (char **)&arg1, (char *)buf, 0x1000)) {
        p = buf;
        while ((c = *p) != 0) {
            if (c == 0x3B) {
                *p = 0xA;
                p[1] = 0;
                break;
            }
            p++;
        }
        s2 = (char *)(*(int *)((char *)(arg0) + 40));
        s1 = *(int *)(s2 + 12);
        igStringObj_Insert((igStringObj *)s2, (char *)buf, s1, strlen(buf));
    }
}

int igDriverDatabase_GetOSName(void *arg0) {
    igStringObj_Set((int)arg0, (int)&text_psx2_2[0]);
    return 1;
}

int igDriverDatabase_GetCpuVendor(void *arg0) {
    igStringObj_Set((int)arg0, (int)&text_mips[0]);
    return 1;
}

int igDriverDatabase_GetCpuType(void *arg0) {
    igStringObj_Set((int)arg0, (int)&text_psx2_2[0]);
    return 1;
}

bool igDriverDatabase_ReadLineFromFile(void *a0, igFileView *s, char *buf, int n) {
    int c = s->vfunc_33();
    int i = 0;
    while (c != -1 && c != 10 && c != 13 && c != 0) {
        if (i < n - 2) buf[i] = c;
        c = s->vfunc_33();
        i++;
    }
    if (n - 2 < i) i = n - 2;
    buf[i] = 10;
    buf[i+1] = 0;
    return i > 0 || ~c != 0;
}

/* igDriverDatabase_ReadLineFromFile over text in memory: copy one line from `*cursor`, advancing it. */
bool igDriverDatabase_ReadLineFromString(igDriverDatabase *self, char **cursor, char *out, int size) {
    int i = 0;
    int limit;
    int c = *(*cursor)++;
    while (c != '\n' && c != '\r' && c != 0) {
        if (i < size - 2) {
            out[i] = c;
        }
        i++;
        c = *(*cursor)++;
    }
    limit = size - 2;
    if (i > limit) {
        i = limit;
    }
    out[i] = '\n';
    out[i + 1] = 0;
    return i > 0 || c != 0;
}

/* Parses the next node of the database text: a SETTINGS block or a section headed by one of the
 * keywords. Returns 0 at the end of the text or on a parse error. */
ConfigNode *FUN_002dae40(igDriverDatabase *self) {
    igStringObj *word = 0;
    ConfigNode *result = 0;
    int i;
    int keyword;
    bool found;
    igDriverDatabase_SkipWhitespace((int *)self);
    if (*(char *)self->_dbIndex == 0) {
        return 0;
    }
    if (igDriverDatabase_ParseIdentifier(self, (int *)&word)) {
        if (strcmp(igStringObj_Text(word), text_SETTINGS) == 0) {
            void *memory = Memory_AllocateBufferDirect(16, (igMemoryPoolView *)igObject_GetAllocator((int)self));
            ConfigSettingsNode *settings = (ConfigSettingsNode *)memory;
            if (memory != 0) {
                settings = (ConfigSettingsNode *)igDriverDatabase_SettingsNode_Construct(memory);
            }
            if (igDriverDatabase_ParseSettingsBlock(self, settings)) {
                result = (ConfigNode *)settings;
            } else if (settings != 0) {
                ((ConfigNode *)settings)->Delete(1);
            }
        } else {
            keyword = -1;
            found = false;
            for (i = 0; i < 13; i++) {
                const char *name = g_driverDatabaseKeywords[i];
                if (strcmp(igStringObj_Text(word), name) == 0) {
                    keyword = i;
                    found = true;
                    break;
                }
            }
            if (found) {
                void *memory = Memory_AllocateBufferDirect(28, (igMemoryPoolView *)igObject_GetAllocator((int)self));
                ConfigSectionNode *section = (ConfigSectionNode *)memory;
                if (memory != 0) {
                    section = (ConfigSectionNode *)igDriverDatabase_PropertyNode_Construct(memory, keyword);
                }
                if (igDriverDatabase_ParsePropertyBlock(self, section)) {
                    result = (ConfigNode *)section;
                } else if (section != 0) {
                    ((ConfigNode *)section)->Delete(1);
                }
            }
        }
        {
            igStringObj *held = word;
            held->_refCount = held->_refCount - 1;
            if ((held->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)held);
            }
        }
    }
    return result;
}

/* Apply one parsed node to the registry: a settings node writes its pairs into the section it names;
 * a section node applies its children when the property it tests holds. */
void igDriverDatabase_ProcessConfigNode(igDriverDatabase *self, ConfigNode *node, igRegistry *registry, int section) {
    int i;
    ConfigSectionNode *test;
    igStringObj *selector;
    unsigned char matches;
    char *actual;
    if (node->kind == 1) {
        int target;
        ConfigSettingsNode *settings = (ConfigSettingsNode *)node;
        target = igDriverDatabase_ResolveSettingsSection(self, ((ConfigSettingsNode *)node)->name, registry, section);
        if (target != -1) {
            igDriverDatabase_ApplySettings(self, settings->entries, registry, target);
        }
    } else {
        selector = ((ConfigSectionNode *)node)->selector;
        test = (ConfigSectionNode *)node;
        if (selector != 0 && selector->_length != 0) {
            actual = (char *)igDriverDatabase_GetSubPropertyValue(self, test->id, (int)igStringObj_Text(selector));
        } else {
            actual = (char *)igDriverDatabase_GetCurrentProperty(self, test->id);
        }
        if (actual == 0 || FUN_0012a78c(actual) == 0) {
            matches = 0;
        } else {
            matches = igDriverDatabase_CompareTyped(self, igDriverDatabase_GetPropertyValueType((int)self, test->id), actual, test->compareMode, igStringObj_Text(test->name));
        }
        if (matches) {
            for (i = 0; i < test->children->_count; i++) {
                igDriverDatabase_ProcessConfigNode(self, test->children->_data[i], registry, section);
            }
        }
    }
}

/* Write each key/value pair into the registry section, creating the key first. */
void igDriverDatabase_ApplySettings(igDriverDatabase *self, igTDataList<ConfigPair *> *entries, igRegistry *registry, int section) {
    char *key;
    int i;
    ConfigPair *pair;
    char *value;
    igStringObj *scratch = (igStringObj *)igStringObj_Create((int)igObject_GetAllocator((int)self));
    for (i = 0; i < entries->_count; i++) {
        pair = entries->_data[i];
        key = igStringObj_Text(pair->key);
        igRegistry_GetValueStringObj((int)registry, section, key, &scratch, (const char *)DAT_004f7910, 0);
        key = igStringObj_Text(pair->key);
        value = igStringObj_Text(pair->value);
        igRegistry_SetValueString(registry, section, key, value);
    }
    igRelease(scratch);
}

/* The registry section a settings node names, resolved through the override source when there is
 * one; -1 when it cannot be resolved under the override mode, else `fallback` for an unnamed node. */
int igDriverDatabase_ResolveSettingsSection(igDriverDatabase *self, igStringObj *sectionName, igRegistry *registry, int fallback) {
    igStringObj *name;
    int result;
    if (sectionName->_length == 0) {
        if (self->_overrideMode == 1) {
            return -1;
        }
        return fallback;
    }
    name = (igStringObj *)igStringObj_Create((int)igObject_GetAllocator((int)self));
    if (self->_overrideSource == 0) {
        igStringObj *held = name;
        char *s = (char *)sectionName->_buffer;
        int length = sectionName->_length;
        s = (s == 0) ? g_stringObjEmptyText[0] : s;
        igStringObj_SetN(held, (int)s, length);
    } else {
        char *s = (char *)sectionName->_buffer;
        char *key = (s == 0) ? g_stringObjEmptyText[0] : s;
        s = (s == 0) ? g_stringObjEmptyText[0] : s;
        if ((igRegistry_GetValueStringObj(self->_overrideSource, self->_overrideSourceSection, key, &name, s, 0) & 0xff) == 0 && self->_overrideMode == 1) {
            igRelease(name);
            return -1;
        }
    }
    result = igRegistry_GetSectionIndex(registry, igStringObj_Text(name), 1);
    igRelease(name);
    return result;
}

void igDriverDatabase_SkipWhitespace(int *arg0) {
    char c;
    while (_ctype_[(c = *(char *)arg0[13]) + 1] & 8) {
        if (c == 10) {
            arg0[11] = arg0[11] + 1;
        }
        arg0[13] = arg0[13] + 1;
    }
}

void igDriverDatabase_TrimTrailingWhitespace(int arg0, char *arg1) {
    int i;

    i = strlen(arg1) - 1;
    while (i >= 0 && (_ctype_[arg1[i] + 1] & 8)) {
        arg1[i] = 0;
        i--;
    }
}

bool igDriverDatabase_ParseIdentifier(igDriverDatabase *arg0, int *arg1) {
    char sp40[4096];
    bool var_s0;

    var_s0 = 0;
    igDriverDatabase_SkipWhitespace((int *)arg0);
    if (sscanf(arg0->_dbIndex, &text_abcdefghijklmnopqrstuvwxyzABCDEF[0], sp40) == 1) {
        arg0->_dbIndex = arg0->_dbIndex + strlen(sp40);
        *arg1 = ((int)igStringObj_Create(((int)igObject_GetAllocator((int)arg0))));
        igStringObj_Set(*arg1, (int)sp40);
        var_s0 = 1;
    }
    return var_s0;
}

bool igDriverDatabase_ReadToken(char *arg0, int *arg1) {
    char buf[4096];
    bool var_s0;

    var_s0 = false;
    igDriverDatabase_SkipWhitespace((int *)arg0);
    if (sscanf(*(int *)(arg0 + 52), &DAT_004f9718[0], buf) == 1) {
        *(int *)(arg0 + 52) = *(int *)(arg0 + 52) + strlen(buf);
        igDriverDatabase_TrimTrailingWhitespace((int)arg0, (char *)buf);
        *arg1 = ((int)igStringObj_Create(((int)igObject_GetAllocator((int)arg0))));
        igStringObj_Set(*arg1, (int)buf);
        var_s0 = true;
    }
    return var_s0;
}

bool igDriverDatabase_ParseOperator(char *arg0, int *arg1) {
    char buf[4096];
    bool var_s1;
    int var_s0;

    var_s1 = false;
    igDriverDatabase_SkipWhitespace((int *)arg0);
    if (sscanf(*(int *)(arg0 + 52), &DAT_004f9728[0], buf) == 1) {
        *(int *)(arg0 + 52) = *(int *)(arg0 + 52) + strlen(buf);
        for (var_s0 = 0; var_s0 < 3; var_s0++) {
            if (strcmp(buf, DAT_004f9670[var_s0]) == 0) {
                *arg1 = var_s0;
                var_s1 = true;
                break;
            }
        }
    }
    return var_s1;
}

static inline void append(igTDataList<int> *l, int v) {
    int i = l->_count;
    if (i < l->_capacity) {
        l->_count = l->count() + 1;
    } else {
        List_Resize((void *)l, i + 1, 4);
    }
    l->_data[i] = v;
}

/* Copy a parsed token's text into a node's string. */
static inline void storeText(igStringObj *target, igStringObj *token) {
    char *text = (char *)token->_buffer;
    int length = token->_length;
    igStringObj *t = target;
    text = (text == 0) ? g_stringObjEmptyText[0] : text;
    igStringObj_SetN(t, (int)text, length);
}

/* Drop the parser's reference to a token it has used. */
static inline void dropText(igStringObj *token) {
    token->_refCount = token->_refCount - 1;
    if ((token->_refCount & 0x7FFFFF) == 0) {
        igObject_Destroy(token);
    }
}

/* Parse a settings block: an optional parenthesised section name, then `{ key mode value ... }`. */
int igDriverDatabase_ParseSettingsBlock(igDriverDatabase *self, ConfigSettingsNode *out) {
    igTDataList<ConfigPair *> *list;
    int index;
    ConfigPair *created;
    ConfigPair *pair;
    igStringObj *key = 0;
    igStringObj *value = 0;
    igStringObj *section = 0;
    int mode = 0;
    igDriverDatabase_SkipWhitespace((int *)self);
    if (igDriverDatabase_ParseParenthesizedIdentifier(self, (int *)&section) != 0) {
        storeText(out->name, section);
        dropText(section);
        section = 0;
    }
    igDriverDatabase_SkipWhitespace((int *)self);
    if (*(char *)self->_dbIndex != '{') {
        return 0;
    }
    self->_dbIndex++;
    igDriverDatabase_SkipWhitespace((int *)self);
    while (*(char *)self->_dbIndex != '}' && *(char *)self->_dbIndex != 0) {
        if (!igDriverDatabase_ParseIdentifier(self, (int *)&key)) {
            return 0;
        }
        if (!igDriverDatabase_ParseOperator((char *)self, &mode)) {
            dropText(key);
            key = 0;
            return 0;
        }
        if (!igDriverDatabase_ReadToken((char *)self, (int *)&value)) {
            dropText(key);
            key = 0;
            return 0;
        }
        igDriverDatabase_SkipWhitespace((int *)self);
        created = (ConfigPair *)Memory_AllocateBufferDirect(sizeof(ConfigPair), igObject_GetAllocator((int)self));
        pair = created;
        if (created != 0) {
            pair = (ConfigPair *)igDriverDatabase_Setting_Construct(created);
        }
        storeText(pair->key, key);
        storeText(pair->value, value);
        list = out->entries;
        index = list->_count;
        if (index < list->_capacity) {
            list->_count = list->count() + 1;
        } else {
            List_Resize(list, index + 1, 4);
        }
        list->_data[index] = pair;
        dropText(key);
        key = 0;
        dropText(value);
        value = 0;
    }
    if (*(char *)self->_dbIndex != '}') {
        return 0;
    }
    self->_dbIndex++;
    return 1;
}

/* Parse a section block: an optional parenthesised selector, the compare mode and the expected value,
 * then `{ child ... }`. */
int igDriverDatabase_ParsePropertyBlock(igDriverDatabase *self, ConfigSectionNode *out) {
    int mode = 0;
    igStringObj *expected = 0;
    ConfigNode *child;
    igDriverDatabase_ParseParenthesizedIdentifier(self, (int *)&out->selector);
    if (!igDriverDatabase_ParseOperator((char *)self, &mode)) {
        return 0;
    }
    out->compareMode = mode;
    if (!igDriverDatabase_ReadToken((char *)self, (int *)&expected)) {
        return 0;
    }
    storeText(out->name, expected);
    dropText(expected);
    expected = 0;
    igDriverDatabase_SkipWhitespace((int *)self);
    if (*(char *)self->_dbIndex != '{') {
        return 0;
    }
    self->_dbIndex++;
    igDriverDatabase_SkipWhitespace((int *)self);
    while (*(char *)self->_dbIndex != '}' && *(char *)self->_dbIndex != 0) {
        child = (ConfigNode *)FUN_002dae40(self);
        if (child == 0) {
            break;
        }
        append((igTDataList<int> *)out->children, (int)child);
        igDriverDatabase_SkipWhitespace((int *)self);
    }
    if (*(char *)self->_dbIndex != '}') {
        return 0;
    }
    self->_dbIndex++;
    return 1;
}

/* Parse a parenthesised word: `(` then the word, skipping the closing character. */
int igDriverDatabase_ParseParenthesizedIdentifier(igDriverDatabase *parser, int *out) {
    char *cursor;
    igDriverDatabase_SkipWhitespace((int *)parser);
    cursor = (char *)parser->_dbIndex;
    if (*cursor != '(') {
        return 0;
    }
    parser->_dbIndex = (int)(cursor + 1);
    if (!igDriverDatabase_ParseIdentifier(parser, out)) {
        return 0;
    }
    igDriverDatabase_SkipWhitespace((int *)parser);
    parser->_dbIndex = parser->_dbIndex + 1;
    return 1;
}

int igDriverDatabase_GetPropertyValueType(int arg0, int arg1) {
    switch (arg1) {
    case 8:
    case 10:
        return 1;
    case 11:
        return 2;
    case 12:
        return 3;
    case 9:
    default:
        return 0;
    }
}

/* Compare a property's text with the expected text as its value type (string, int, float or bool). */
unsigned char igDriverDatabase_CompareTyped(igDriverDatabase *self, int valueType, char *actual, int compareMode, char *expected) {
    unsigned char result;
    switch (valueType) {
    case 1: {
        int first = 0;
        int second = 0;
        if (sscanf(actual, DAT_004f9730, &first) != 1) return 0;
        if (sscanf(expected, DAT_004f9730, &second) != 1) return 0;
        result = igDriverDatabase_CompareValues((int)self, first, compareMode, second);
        break;
    }
    case 2: {
        float first = 0;
        float second = 0;
        if (sscanf(actual, DAT_004f9738, &first) != 1) return 0;
        if (sscanf(expected, DAT_004f9738, &second) != 1) return 0;
        result = igDriverDatabase_CompareFloat((int)self, compareMode, first, second);
        break;
    }
    case 3: {
        unsigned char first = 0;
        unsigned char second = 0;
        igSmartPointer<igStringObj> text((igStringObj *)igStringObj_Create((int)igObject_GetAllocator((int)self)));
        igStringObj_Set((int)text.get(), (int)actual);
        if (!igStringObj_ParseBool(text.get(), (char *)&first)) return 0;
        igStringObj_Set((int)text.get(), (int)expected);
        if (!igStringObj_ParseBool(text.get(), (char *)&second)) return 0;
        result = igDriverDatabase_CompareBool((int)self, first, compareMode, second);
        break;
    }
    default:
    case 0:
        result = igDriverDatabase_CompareString((int)self, (int)actual, compareMode, (int)expected);
    }
    return result;
}

int igDriverDatabase_CompareString(int dummy0, int arg1, int arg2, int arg3) {
    switch (arg2) {
    case 0:
        return strcasecmp(arg1, arg3) == 0;
    case 1:
        return strncasecmp(arg1, arg3, strlen(arg3)) == 0;
    case 2:
        return strcasecmp(arg1, arg3) != 0;
    default:
        return 0;
    }
}

int igDriverDatabase_CompareValues(int dummy0, int arg1, int arg2, int arg3) {
    switch (arg2) {
    case 0:
        return arg1 == arg3;
    case 1:
        return arg1 >= arg3;
    case 2:
        return arg1 != arg3;
    default:
        return 0;
    }
}

bool igDriverDatabase_CompareFloat(int unused, int mode, float a, float b) {
    switch (mode) {
    case 0:
        return a == b;
    case 1:
        return a >= b;
    case 2:
        return a != b;
    }
    return false;
}

int igDriverDatabase_CompareBool(int p, unsigned char a, int m, unsigned char b) { switch (m) { case 0: return a == b; case 1: goto z; case 2: return a != b; } z: return 0; }

void *igDriverDatabase_Setting_Construct(void *arg0) {
    *(int *)((char *)(arg0) + 8) = (int)(&DAT_00530608[0]);
    *(int *)((char *)(arg0) + 0) = ((int)igStringObj_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString))));
    *(int *)((char *)(arg0) + 4) = ((int)igStringObj_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString))));
    return arg0;
}

ConfigPair *igDriverDatabase_Setting_Destruct(ConfigPair *self, int delete_storage) {
    igStringObj *p;
    igStringObj *q;
    if (self) {
        *(int **)((char *)self + 8) = &DAT_00530608[0];
        p = self->key;
        --p->_refCount;
        if (((unsigned long long)(long long)(int)p->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy((void *)p);
        self->key = 0;
        q = self->value;
        --q->_refCount;
        if (((unsigned long long)(long long)(int)q->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy((void *)q);
        self->value = 0;
        if ((short)delete_storage > 0) Memory_FreeBufferAliasB(self);
    }
    return self;
}

void *igDriverDatabase_SettingsNode_Construct(void *arg0) {
    int var_v0;

    *(int *)((char *)(arg0) + 4) = (int)(&DAT_00530618[0]);
    *(int *)((char *)(arg0) + 0) = 1;
    *(int *)((char *)(arg0) + 4) = (int)(&DAT_005305f8[0]);
    if (g_useOwnerAllocator != 0) {
        var_v0 = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent));
    } else {
        var_v0 = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleList));
    }
    *(int *)((char *)(arg0) + 8) = ((int)igDataList_Create(var_v0));
    *(int *)((char *)(arg0) + 12) = ((int)igStringObj_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString))));
    return arg0;
}

void *igDriverDatabase_SettingsNode_Destruct(ConfigSettingsNode *arg0, long long arg1) {
    int var_s0;
    int s3;
    igObject *a0;
    igTDataList<ConfigPair *> *v1;
    int v0;
    ConfigPair *e;
    if (arg0 != 0) {
        arg0->vtable = (int)&DAT_005305f8[0];
        for (var_s0 = 0; var_s0 < arg0->entries->_count; var_s0++) {
            s3 = var_s0 * 4;
            e = arg0->entries->_data[var_s0];
            if (e != 0) {
                e->Delete(1);
            }
            v1 = arg0->entries;
            v0 = v1->_count;
            if (v0 != 0 && var_s0 >= 0 && var_s0 < v0) {
                *(int *)((char *)v1->_data + s3) = 0;
            }
        }
        a0 = (igObject *)arg0->entries;
        a0->_refCount = a0->_refCount - 1;
        if ((a0->_refCount & 0x7fffff) == 0) igObject_Destroy(a0);
        arg0->entries = 0;
        a0 = arg0->name;
        a0->_refCount = a0->_refCount - 1;
        if ((a0->_refCount & 0x7fffff) == 0) igObject_Destroy(a0);
        arg0->name = 0;
        if (arg0 != 0) {
            arg0->vtable = (int)&DAT_00530618[0];
        }
        if ((short)arg1 > 0) {
            Memory_FreeBufferAliasB(arg0);
        }
    }
    return arg0;
}

void *igDriverDatabase_PropertyNode_Construct(void *arg0, int arg1) {
    int var_v0;

    *(int *)((char *)(arg0) + 4) = (int)(&DAT_00530618[0]);
    *(int *)((char *)(arg0) + 0) = 0;
    *(int *)((char *)(arg0) + 4) = (int)(&DAT_005305e8[0]);
    *(int *)((char *)(arg0) + 8) = arg1;
    *(int *)((char *)(arg0) + 20) = 0;
    *(int *)((char *)(arg0) + 24) = 0;
    *(int *)((char *)(arg0) + 12) = ((int)igStringObj_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString))));
    if (g_useOwnerAllocator != 0) {
        var_v0 = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent));
    } else {
        var_v0 = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleList));
    }
    *(int *)((char *)(arg0) + 16) = ((int)igDataList_Create(var_v0));
    return arg0;
}

void *igDriverDatabase_PropertyNode_Destruct(ConfigSectionNode *arg0, long long arg1) {
    int var_s0;
    int s3;
    igObject *a0;
    igTDataList<ConfigNode *> *v1;
    int v0;
    ConfigNode *e;
    if (arg0 != 0) {
        arg0->vtable = (int)&DAT_005305e8[0];
        a0 = arg0->name;
        a0->_refCount = a0->_refCount - 1;
        if ((a0->_refCount & 0x7fffff) == 0) igObject_Destroy(a0);
        arg0->name = 0;
        a0 = arg0->selector;
        if (a0 != 0) {
            a0->_refCount = a0->_refCount - 1;
            if ((a0->_refCount & 0x7fffff) == 0) igObject_Destroy(a0);
            arg0->selector = 0;
        }
        for (var_s0 = 0; var_s0 < arg0->children->_count; var_s0++) {
            s3 = var_s0 * 4;
            e = arg0->children->_data[var_s0];
            if (e != 0) {
                e->Delete(1);
            }
            v1 = arg0->children;
            v0 = v1->_count;
            if (v0 != 0 && var_s0 >= 0 && var_s0 < v0) {
                *(int *)((char *)v1->_data + s3) = 0;
            }
        }
        a0 = (igObject *)arg0->children;
        a0->_refCount = a0->_refCount - 1;
        if ((a0->_refCount & 0x7fffff) == 0) igObject_Destroy(a0);
        arg0->children = 0;
        if (arg0 != 0) {
            arg0->vtable = (int)&DAT_00530618[0];
        }
        if ((short)arg1 > 0) {
            Memory_FreeBufferAliasB(arg0);
        }
    }
    return arg0;
}

