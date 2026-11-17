/* Read the verbose flag from the configuration registry and give each of the 13 properties an
 * empty value string. */
void igDriverDatabase_InitDefaults(igDriverDatabase *database) {
    unsigned char verbose;
    int i;
    igObject_InitDefaults((igObject *)database);
    igRegistry_GetValueBool(g_objectSystem->configRegistry, 2,"driverDatabaseVerbose", &verbose, database->_verbose, 1);
    database->_verbose = verbose;
    ObjectList_ResizeRetained((igTDataList<igObject *> *)database->_currentProperties, 13);
    ObjectList_ResizeRetained((igTDataList<igObject *> *)database->_subPropertyNames, 13);
    ObjectList_ResizeRetained((igTDataList<igObject *> *)database->_subPropertyValues, 13);
    i = 0;
    do {
        {
            igSmartPointer<igStringObj> value((igStringObj *)igStringObj_Create((int)igObject_GetAllocator((igObject *)database)));
            objectListSetRetained(i, value.get(), (igObjectList *)database->_currentProperties);
        }
        i++;
    } while (i < 13);
}

void igDriverDatabase_ReleaseDefaults(int self) {
    igDriverDatabase_ClearRawDatabase((int *)self);
    igObject_ReleaseDefaults((igObject *)self);
}

void igDriverDatabase_SetCurrentProperty(void *self, int property, const char *value) {
    igStringObj_Set((igStringObj *)(((int *)((igObjectList *)((igDriverDatabase *)self)->_currentProperties)->_data)[property]), value);
}

char *g_stringObjEmptyText = "";

int igDriverDatabase_GetCurrentProperty(void *self, int property) {
    int text;

    text = ((igStringObj *)((int *)((igObjectList *)((igDriverDatabase *)self)->_currentProperties)->_data)[property])->_buffer;
    if (text == 0) {
        text = (*(int *)&g_stringObjEmptyText);
    }
    return text;
}

int igDriverDatabase_GetSubPropertyValue(igDriverDatabase *self, int property, int name) {
    igSmartPointer<igObject> names;
    igSmartPointer<igObject> values;
    int key, value;
    igObject *x;
    int idx;
    int interned;
    int r;
    names.p = 0;
    values.p = 0;
    x = ((igObject **)((igObjectList *)self->_subPropertyNames)->_data)[property];
    if (x == 0) return 0;
    names = x;
    values = ((igObject **)((igObjectList *)self->_subPropertyValues)->_data)[property];
    if (name == 0) {
        interned = 0;
    } else {
        if (g_stringPool == 0) {
            int al = ((int)StringPool_Allocate(16));
            if (al != 0) al = ((int)StringPool_Construct((StringPool *)al));
            g_stringPool = (StringPool *)al;
        }
        interned = (int)StringPool_Intern((StringPool *)g_stringPool, (const char *)name);
    }
    key = interned;
    idx = igStringRefList_IndexOf((igStringRefList *)names.p, (char *const *)&key, 0);
    releaseString((const char *)key);
    if (idx >= 0) {
        r = (int)StringList_CopyRetained((igStringRefList *)values.p, idx).p;
        return r;
    }
    return 0;
}

static inline char *textOf(const igSmartPointer<igStringObj> &ref) {
    char *s = (char *)ref.get()->_buffer;
    s = (s == 0) ? g_stringObjEmptyText : s;
    return s;
}

void igDriverDatabase_GatherProperties(void *self, igTDataList<igVisualContextView *> *list) {
    int i;
    igSmartPointer<igStringObj> text(((igStringObj *)igStringObj_Create((int)(((void *)igObject_GetAllocator((igObject *)self))))));
    if (igDriverDatabase_GetOSName((void *)(text.get())) != 0) {
        igDriverDatabase_SetCurrentProperty(self, 0, textOf(text));
    }
    if (igDriverDatabase_GetCpuVendor((void *)(text.get())) != 0) {
        igDriverDatabase_SetCurrentProperty(self, 6, textOf(text));
    }
    if (igDriverDatabase_GetCpuType((void *)(text.get())) != 0) {
        igDriverDatabase_SetCurrentProperty(self, 7, textOf(text));
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
    if (text == 0) text = (*(int *)&g_stringObjEmptyText);
    return file->Open((const char *)text, (const char *)"r");
}

int igDriverDatabase_Load(igDriverDatabase *self, const char *fileName, const char *rootPath) {
    int opened;
    igStringRef name((char *)fileName);
    const char *p5 = name.p;
    if (p5 == 0 || strlen(p5) == 0) {
        name = (char *)"drivers.ini";
    }
    {
        int al = ((int)igObject_GetAllocator((igObject *)self));
        igRelease((igObject *)self->_databaseFile);
        self->_databaseFile = (int)((igObject *)igFile_Create(al));
    }
    opened = ((igFileView *)self->_databaseFile)->Open(name.p, (const char *)"r");
    if (opened == 0) {
        if (rootPath == 0 || strlen(rootPath) == 0) {
            rootPath = ((const char *)igObjectSystem_GetRootPath((int *)((*(int *)&g_objectSystem))));
        }
        if (rootPath != 0 && strlen(rootPath) != 0) {
            igSmartPointer<igFolderView> folder((igFolderView *)igFolder_Create(((int)igObject_GetAllocator((igObject *)self))));
            folder.p->setFolderName((char *)rootPath);
            opened = openPath(self, folder.p->GetFullPath(name.p));
        }
    }
    if (opened == 0) {
        igSmartPointer<igFolderView> folder((igFolderView *)igFolder_Create(((int)igObject_GetAllocator((igObject *)self))));
        folder.p->setFolderName((char *)igObjectSystem_GetBasePath((int *)((*(int *)&g_objectSystem))));
        opened = openPath(self, folder.p->GetFullPath(name.p));
    }
    if (opened == 0) {
        igRelease((igObject *)self->_databaseFile);
        self->_databaseFile = 0;
        return 0;
    }
    igStringObj_Set((igStringObj *)self->_databaseFileName, (const char *)((igFile *)opened)->_fileName);
    igDriverDatabase_LoadDatabaseFile(self, (igFileView *)self->_databaseFile);
    ((igFileView *)self->_databaseFile)->Close();
    igRelease((igObject *)self->_databaseFile);
    self->_databaseFile = 0;
    return 1;
}

int igDriverDatabase_LoadFromFile(void *self, int text, int fileName) {
    if (text == 0) {
        return 0;
    }
    igStringObj_Set((igStringObj *)((igDriverDatabase *)self)->_databaseFileName, (const char *)fileName);
    igDriverDatabase_LoadFromString(self, text);
    return 1;
}

void igDriverDatabase_ClearRawDatabase(int *p)
{
    igStringObj_Clear((igStringObj *)((igDriverDatabase *)p)->_rawDatabase);
}

static inline int n_of(const igTDataList<ConfigNode *> *list) { return list->_count; }

igTDataList<ConfigNode *> *igDriverDatabase_ParseDatabase(igDriverDatabase *s) {
    int cnt;
    ConfigNode *r;
    igTDataList<ConfigNode *> *l;
    int v;

    l = ((igTDataList<ConfigNode *> *)igDataList_Create(((int)igObject_GetAllocator((igObject *)s))));
    s->_currentLine = 1;
    v = ((igStringObj *)s->_rawDatabase)->_buffer;
    if (v == 0) {
        v = (*(int *)&g_stringObjEmptyText);
    }
    s->_dbIndex = v;
    do {
        r = igDriverDatabase_ParseNode(s);
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

void *igDriverDatabase_ConfigNode_Destruct(void *node, long long deleteFlag) {
    if (node != 0) {
        ((ConfigNodeData *)node)->vtable = (int)(&g_ConfigNode_vtable[0]);
        if (((long long) (deleteFlag << 0x30) >> 0x30) > 0) {
            Memory_FreeBufferAliasB((void *)node);
        }
    }
    return node;
}

int igDriverDatabase_ApplyToRegistry(igDriverDatabase *self, int registry, int section, int mergeMode) {
    int r;
    igTDataList<ConfigNode *> *a;
    int i;
    igSmartPointer<igRegistry> parsed(((igRegistry *)igRegistry_Create(((int)igObject_GetAllocator((igObject *)self)))));
    a = igDriverDatabase_ParseDatabase(self);
    for (i = 0; i < a->_count; i++) {
        igDriverDatabase_ProcessConfigNode(self, a->_data[i], parsed.p, section);
    }
    igRegistry_Merge((void *)registry, parsed.p, mergeMode);
    r = *(char *)self->_dbIndex == 0;
    igDriverDatabase_DeleteConfigNodeList((void *)self, a);
    igDriverDatabase_ClearRawDatabase((int *)self);
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

void igDriverDatabase_LoadFromString(void *self, int text) {
    char buf[4096];
    char *raw;
    int length;
    char *p;
    int c;
    igDriverDatabase_ClearRawDatabase((int *)self);
    while (igDriverDatabase_ReadLineFromString((igDriverDatabase *)self, (char **)&text, (char *)buf, 0x1000)) {
        p = buf;
        while ((c = *p) != 0) {
            if (c == 0x3B) {
                *p = 0xA;
                p[1] = 0;
                break;
            }
            p++;
        }
        raw = (char *)((igDriverDatabase *)self)->_rawDatabase;
        length = ((igStringObj *)raw)->_length;
        igStringObj_Insert((igStringObj *)raw, (char *)buf, length, strlen(buf));
    }
}

int igDriverDatabase_GetOSName(void *text) {
    igStringObj_Set((igStringObj *)text, "psx2");
    return 1;
}

int igDriverDatabase_GetCpuVendor(void *text) {
    igStringObj_Set((igStringObj *)text, "mips");
    return 1;
}

int igDriverDatabase_GetCpuType(void *text) {
    igStringObj_Set((igStringObj *)text, "psx2");
    return 1;
}

bool igDriverDatabase_ReadLineFromFile(void *a0, igFileView *s, char *buf, int n) {
    int c = s->GetChar();
    int i = 0;
    while (c != -1 && c != 10 && c != 13 && c != 0) {
        if (i < n - 2) buf[i] = c;
        c = s->GetChar();
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

const char *const g_driverDatabaseKeywords[13] = {
    "OS",
    "PLATFORM",
    "PLATFORM_VERSION",
    "VENDOR",
    "CHIPSET",
    "DRIVER",
    "CPU_VENDOR",
    "CPU_TYPE",
    "GFX_CAPABILITY",
    "USER_STRING",
    "USER_INT",
    "USER_FLOAT",
    "USER_BOOL"
};

/* Parses the next node of the database text: a SETTINGS block or a section headed by one of the
 * keywords. Returns 0 at the end of the text or on a parse error. */
ConfigNode *igDriverDatabase_ParseNode(igDriverDatabase *self) {
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
        if (strcmp(igStringObj_Text(word),"SETTINGS") == 0) {
            void *memory = Memory_AllocateBufferDirect(16, (igMemoryPoolView *)igObject_GetAllocator((igObject *)self));
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
                void *memory = Memory_AllocateBufferDirect(28, (igMemoryPoolView *)igObject_GetAllocator((igObject *)self));
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
        if (actual == 0 || strlen(actual) == 0) {
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
    igStringObj *scratch = (igStringObj *)igStringObj_Create((int)igObject_GetAllocator((igObject *)self));
    for (i = 0; i < entries->_count; i++) {
        pair = entries->_data[i];
        key = igStringObj_Text(pair->key);
        igRegistry_GetValueStringObj(registry, section, key, &scratch, (const char *)"", 0);
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
    name = (igStringObj *)igStringObj_Create((int)igObject_GetAllocator((igObject *)self));
    if (self->_overrideSource == 0) {
        igStringObj *held = name;
        char *s = (char *)sectionName->_buffer;
        int length = sectionName->_length;
        s = (s == 0) ? g_stringObjEmptyText : s;
        igStringObj_SetN(held, (int)s, length);
    } else {
        char *s = (char *)sectionName->_buffer;
        char *key = (s == 0) ? g_stringObjEmptyText : s;
        s = (s == 0) ? g_stringObjEmptyText : s;
        if ((igRegistry_GetValueStringObj((igRegistry *)self->_overrideSource, self->_overrideSourceSection, key, &name, s, 0) & 0xff) == 0 && self->_overrideMode == 1) {
            igRelease(name);
            return -1;
        }
    }
    result = igRegistry_GetSectionIndex(registry, igStringObj_Text(name), 1);
    igRelease(name);
    return result;
}

void igDriverDatabase_SkipWhitespace(int *parser) {
    igDriverDatabase *database = (igDriverDatabase *)parser;
    char c;
    while (_ctype_[(c = *(char *)database->_dbIndex) + 1] & 8) {
        if (c == 10) {
            database->_currentLine = database->_currentLine + 1;
        }
        database->_dbIndex = database->_dbIndex + 1;
    }
}

void igDriverDatabase_TrimTrailingWhitespace(int parser, char *text) {
    int i;

    i = strlen(text) - 1;
    while (i >= 0 && (_ctype_[text[i] + 1] & 8)) {
        text[i] = 0;
        i--;
    }
}

bool igDriverDatabase_ParseIdentifier(igDriverDatabase *self, int *out) {
    char word[4096];
    bool found;

    found = 0;
    igDriverDatabase_SkipWhitespace((int *)self);
    if (sscanf((const char *)self->_dbIndex, "%[_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./\\-]", word) == 1) {
        self->_dbIndex = self->_dbIndex + strlen(word);
        *out = ((int)igStringObj_Create(((int)igObject_GetAllocator((igObject *)self))));
        igStringObj_Set((igStringObj *)*out, word);
        found = 1;
    }
    return found;
}

bool igDriverDatabase_ReadToken(char *parser, int *out) {
    igDriverDatabase *database = (igDriverDatabase *)parser;
    char buf[4096];
    bool found;

    found = false;
    igDriverDatabase_SkipWhitespace((int *)parser);
    if (sscanf((const char *)database->_dbIndex, "%[^\r\n{};]", buf) == 1) {
        database->_dbIndex = database->_dbIndex + strlen(buf);
        igDriverDatabase_TrimTrailingWhitespace((int)parser, (char *)buf);
        *out = ((int)igStringObj_Create(((int)igObject_GetAllocator((igObject *)parser))));
        igStringObj_Set((igStringObj *)*out, buf);
        found = true;
    }
    return found;
}

const char *const g_driverDatabaseOperators[3] = { "=", ">=", "!=" };

bool igDriverDatabase_ParseOperator(igDriverDatabase *self, int *out) {
    char buf[4096];
    bool found;
    int i;

    found = false;
    igDriverDatabase_SkipWhitespace((int *)self);
    if (sscanf((const char *)self->_dbIndex, "%[=<>!]", buf) == 1) {
        self->_dbIndex = self->_dbIndex + strlen(buf);
        for (i = 0; i < 3; i++) {
            if (strcmp(buf, g_driverDatabaseOperators[i]) == 0) {
                *out = i;
                found = true;
                break;
            }
        }
    }
    return found;
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
    text = (text == 0) ? g_stringObjEmptyText : text;
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
        if (!igDriverDatabase_ParseOperator(self, &mode)) {
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
        created = (ConfigPair *)Memory_AllocateBufferDirect(sizeof(ConfigPair), igObject_GetAllocator((igObject *)self));
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
    if (!igDriverDatabase_ParseOperator(self, &mode)) {
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
        child = (ConfigNode *)igDriverDatabase_ParseNode(self);
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

int igDriverDatabase_GetPropertyValueType(int self, int property) {
    switch (property) {
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
        if (sscanf(actual," %i ", &first) != 1) return 0;
        if (sscanf(expected," %i ", &second) != 1) return 0;
        result = igDriverDatabase_CompareValues((int)self, first, compareMode, second);
        break;
    }
    case 2: {
        float first = 0;
        float second = 0;
        if (sscanf(actual," %f ", &first) != 1) return 0;
        if (sscanf(expected," %f ", &second) != 1) return 0;
        result = igDriverDatabase_CompareFloat((int)self, compareMode, first, second);
        break;
    }
    case 3: {
        unsigned char first = 0;
        unsigned char second = 0;
        igSmartPointer<igStringObj> text((igStringObj *)igStringObj_Create((int)igObject_GetAllocator((igObject *)self)));
        igStringObj_Set(text.get(), actual);
        if (!igStringObj_ParseBool(text.get(), (char *)&first)) return 0;
        igStringObj_Set(text.get(), expected);
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

int igDriverDatabase_CompareString(int dummy0, int actual, int mode, int expected) {
    switch (mode) {
    case 0:
        return strcasecmp((const char *)actual, (const char *)expected) == 0;
    case 1:
        return strncasecmp((const char *)actual, (const char *)expected, strlen((const char *)expected)) == 0;
    case 2:
        return strcasecmp((const char *)actual, (const char *)expected) != 0;
    default:
        return 0;
    }
}

int igDriverDatabase_CompareValues(int dummy0, int actual, int mode, int expected) {
    switch (mode) {
    case 0:
        return actual == expected;
    case 1:
        return actual >= expected;
    case 2:
        return actual != expected;
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

void *igDriverDatabase_Setting_Construct(void *self) {
    ((ConfigPairData *)self)->vtable = (int)(&g_ConfigPair_vtable[0]);
    ((ConfigPair *)self)->key = (igStringObj *)igStringObj_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString)));
    ((ConfigPair *)self)->value = (igStringObj *)igStringObj_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString)));
    return self;
}

ConfigPair *igDriverDatabase_Setting_Destruct(ConfigPair *self, int delete_storage) {
    igStringObj *p;
    igStringObj *q;
    if (self) {
        ((ConfigPairData *)self)->vtable = (int)&g_ConfigPair_vtable[0];
        p = self->key;
        --p->_refCount;
        if (((unsigned long long)(long long)(int)p->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy((igObject *)p);
        self->key = 0;
        q = self->value;
        --q->_refCount;
        if (((unsigned long long)(long long)(int)q->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy((igObject *)q);
        self->value = 0;
        if ((short)delete_storage > 0) Memory_FreeBufferAliasB(self);
    }
    return self;
}

void *igDriverDatabase_SettingsNode_Construct(void *self) {
    int allocator;

    ((ConfigSettingsNode *)self)->vtable = (int)(&g_ConfigNode_vtable[0]);
    ((ConfigSettingsNode *)self)->kind = 1;
    ((ConfigSettingsNode *)self)->vtable = (int)(&g_ConfigSettingsNode_vtable[0]);
    if (g_useOwnerAllocator != 0) {
        allocator = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent));
    } else {
        allocator = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleList));
    }
    ((ConfigSettingsNode *)self)->entries = (igTDataList<ConfigPair *> *)igDataList_Create(allocator);
    ((ConfigSettingsNode *)self)->name = (igStringObj *)igStringObj_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString)));
    return self;
}

void *igDriverDatabase_SettingsNode_Destruct(ConfigSettingsNode *self, long long deleteFlag) {
    int i;
    int s3;
    igObject *a0;
    igTDataList<ConfigPair *> *v1;
    int v0;
    ConfigPair *e;
    if (self != 0) {
        self->vtable = (int)&g_ConfigSettingsNode_vtable[0];
        for (i = 0; i < self->entries->_count; i++) {
            s3 = i * 4;
            e = self->entries->_data[i];
            if (e != 0) {
                e->Delete(1);
            }
            v1 = self->entries;
            v0 = v1->_count;
            if (v0 != 0 && i >= 0 && i < v0) {
                *(int *)((char *)v1->_data + s3) = 0;
            }
        }
        a0 = (igObject *)self->entries;
        a0->_refCount = a0->_refCount - 1;
        if ((a0->_refCount & 0x7fffff) == 0) igObject_Destroy(a0);
        self->entries = 0;
        a0 = self->name;
        a0->_refCount = a0->_refCount - 1;
        if ((a0->_refCount & 0x7fffff) == 0) igObject_Destroy(a0);
        self->name = 0;
        if (self != 0) {
            self->vtable = (int)&g_ConfigNode_vtable[0];
        }
        if ((short)deleteFlag > 0) {
            Memory_FreeBufferAliasB(self);
        }
    }
    return self;
}

void *igDriverDatabase_PropertyNode_Construct(void *self, int property) {
    int allocator;

    ((ConfigSectionNode *)self)->vtable = (int)(&g_ConfigNode_vtable[0]);
    ((ConfigSectionNode *)self)->kind = 0;
    ((ConfigSectionNode *)self)->vtable = (int)(&g_ConfigSectionNode_vtable[0]);
    ((ConfigSectionNode *)self)->id = property;
    ((ConfigSectionNode *)self)->compareMode = 0;
    ((ConfigSectionNode *)self)->selector = 0;
    ((ConfigSectionNode *)self)->name = (igStringObj *)igStringObj_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString)));
    if (g_useOwnerAllocator != 0) {
        allocator = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent));
    } else {
        allocator = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleList));
    }
    ((ConfigSectionNode *)self)->children = (igTDataList<ConfigNode *> *)igDataList_Create(allocator);
    return self;
}

void *igDriverDatabase_PropertyNode_Destruct(ConfigSectionNode *self, long long deleteFlag) {
    int i;
    int s3;
    igObject *a0;
    igTDataList<ConfigNode *> *v1;
    int v0;
    ConfigNode *e;
    if (self != 0) {
        self->vtable = (int)&g_ConfigSectionNode_vtable[0];
        a0 = self->name;
        a0->_refCount = a0->_refCount - 1;
        if ((a0->_refCount & 0x7fffff) == 0) igObject_Destroy(a0);
        self->name = 0;
        a0 = self->selector;
        if (a0 != 0) {
            a0->_refCount = a0->_refCount - 1;
            if ((a0->_refCount & 0x7fffff) == 0) igObject_Destroy(a0);
            self->selector = 0;
        }
        for (i = 0; i < self->children->_count; i++) {
            s3 = i * 4;
            e = self->children->_data[i];
            if (e != 0) {
                e->Delete(1);
            }
            v1 = self->children;
            v0 = v1->_count;
            if (v0 != 0 && i >= 0 && i < v0) {
                *(int *)((char *)v1->_data + s3) = 0;
            }
        }
        a0 = (igObject *)self->children;
        a0->_refCount = a0->_refCount - 1;
        if ((a0->_refCount & 0x7fffff) == 0) igObject_Destroy(a0);
        self->children = 0;
        if (self != 0) {
            self->vtable = (int)&g_ConfigNode_vtable[0];
        }
        if ((short)deleteFlag > 0) {
            Memory_FreeBufferAliasB(self);
        }
    }
    return self;
}

