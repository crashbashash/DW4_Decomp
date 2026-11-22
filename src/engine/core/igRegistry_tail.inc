static inline char *registryText(igStringObj *s) { char *t = (char *)s->_buffer; if (t == 0) { return g_stringObjEmptyText; } return t; }

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

static inline char *listValueText(igStringObj *s) { char *t = (char *)s->_buffer; if (t == 0) { return g_stringObjEmptyText; } return t; }

static inline int *intern(char *s) {
    if (s == 0) {
        return 0;
    }
    return (int *)StringPool_Intern(InternedStrings::get(), (const char *)s);
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

static inline int enumValueText(void *o) { int a = *(int *)((char *)(*(int *)((char *)(o) + 12)) + 8); if (a == 0) { return (*(int *)&g_stringObjEmptyText); } return a; }
static inline int flagsValueText(void *o) { int a = *(int *)((char *)(*(int *)((char *)(o) + 12)) + 8); if (a == 0) { return (*(int *)&g_stringObjEmptyText); } return a; }

int g_registryIncludeDepth;

namespace Gap {
namespace Core {

static inline int openPath(igRegistry *self, const igStringObjRef &path) {
    igFile *file = self->_registryFile.p;
    return (int)file->fopen(registryText(path.p), "r");
}

void igRegistry::initDefaults() {
    igObject::initDefaults();
    _valueTable->setCount(0x100);
}

bool igRegistry::load(const char *registryFile, const char *path) {
    int found;
    igStringRef fileName(registryFile);
    if (fileName.p == 0 || strlen(fileName.p) == 0) {
        fileName = "alchemy.ini";
    }
    found = (int)_registryFile.p->fopen(fileName.p, "r");
    if (found == 0) {
        if (path == 0 || strlen(path) == 0) {
            path = ((char *)igObjectSystem_GetRootPath((int *)(((*(void * *)&g_objectSystem)))));
        }
        if (path != 0 && strlen(path) != 0) {
            igSmartPointer<igFolder> folder(igFolder::_instantiateFromPool((igMemoryPoolView *)getMemoryPool()));
            folder.p->setFolderName(path);
            found = openPath(this, folder.p->getPathToFile(fileName.p));
        }
    }
    if (found == 0) {
        igSmartPointer<igFolder> folder(igFolder::_instantiateFromPool((igMemoryPoolView *)getMemoryPool()));
        folder.p->setFolderName((char *)igObjectSystem_GetBasePath((int *)(((*(void * *)&g_objectSystem)))));
        found = openPath(this, folder.p->getPathToFile(fileName.p));
    }
    if (found == 0) {
        return false;
    }
    reset();
    parseRegistry(_registryFile, true);
    _registryFile.p->fclose();
    return true;
}

bool igRegistry::merge(igRegistry *sourceRegistry, unsigned char replaceDuplicates) {
    int i = 0;
    igSmartPointer<igRegistryValue> value;
    for (; i < sourceRegistry->_valueTable->getCount(); i++) {
        value = sourceRegistry->_valueTable->get(i);
        if (value != 0) {
            int section = findSection(sourceRegistry->getSectionName(value->_section), true);
            if (!replaceDuplicates && findValue(section, registryText(value->_valueName), false) != 0) {
                continue;
            }
            igStringObj *valueText = value->_value;
            igStringObj *valueName = value->_valueName;
            setValue(section, registryText(valueName), (const char *)registryText(valueText));
        }
    }
    return true;
}

/* The index of section `name`: the standard sections first, then the registry's own, added at the
 * end when `create` is set; -1 when it is missing. */
int igRegistry::findSection(const char *sectionName, unsigned char create) {
    int n;
    int i;
    for (i = 0; i < 11; i++) {
        if (igStrcasecmp(sectionName, g_registrySectionNames[i]) == 0) {
            return i;
        }
    }
    n = _additionalSectionNames->_count;
    for (i = 0; i < n; i++) {
        if (igStrcasecmp(sectionName, igStringObj_Text(((igStringObj **)_additionalSectionNames->_data)[i])) == 0) {
            return i + 11;
        }
    }
    if (create) {
        igStringObjRef section((igStringObj *)igStringObj_Create((int)getMemoryPool()));
        igStringObj_Set(section.get(), sectionName);
        ((igObjectList *)_additionalSectionNames.p)->append((igObject *)section.get());
        return n + 11;
    }
    return -1;
}

/* The number of keys a section holds. */
unsigned int igRegistry::getKeyCount(int sectionHandle) {
    int keys = 0;
    for (int i = 0; i < _valueTable->getCount(); i++) {
        igRegistryValue *value = _valueTable->get(i);
        if (value != 0 && value->_section == sectionHandle) {
            keys++;
        }
    }
    return keys;
}

/* Copies the index-th key of a section to strVal, retained; false when the section has fewer keys. */
bool igRegistry::getKeyName(int sectionHandle, const unsigned int index, igStringObjRef &strVal) {
    int i;
    int seen = 0;
    bool found = false;
    for (i = 0; i < _valueTable->getCount(); i++) {
        igRegistryValue *value = _valueTable->get(i);
        if (value != 0 && value->_section == sectionHandle) {
            if (seen == index) {
                strVal = value->_valueName;
                found = true;
                break;
            }
            seen++;
        }
    }
    return found;
}

bool igRegistry::getValue(int sectionHandle, const char *valueName, int &intVal, int defaultVal, unsigned char createValue) {
    bool found = false;
    igRegistryValue *value = findValue(sectionHandle, valueName, false);
    if (value != 0 && igStringObj_ToInt(value->_value, &intVal) != 0) {
        found = true;
    }
    if (!found) {
        intVal = defaultVal;
        if (createValue) {
            setValue(sectionHandle, valueName, defaultVal);
        }
    }
    return found;
}

bool igRegistry::getValue(int sectionHandle, const char *valueName, float &floatVal, float defaultVal, unsigned char createValue) {
    bool found = false;
    igRegistryValue *value = findValue(sectionHandle, valueName, false);
    if (value != 0 && igStringObj_ToFloat(value->_value, &floatVal) != 0) {
        found = true;
    }
    if (!found) {
        floatVal = defaultVal;
        if (createValue) {
            setValue(sectionHandle, valueName, defaultVal);
        }
    }
    return found;
}

bool igRegistry::getValue(int sectionHandle, const char *valueName, igStringObjRef &strVal, const char *defaultVal,
                          unsigned char createValue) {
    igRegistryValue *value = findValue(sectionHandle, valueName, false);
    if (value != 0) {
        strVal = value->_value;
    } else {
        igStringObjRef created((igStringObj *)igStringObj_Create((int)getMemoryPool()));
        igStringObj_Set(created.p, defaultVal);
        strVal = created;
        if (createValue) {
            setValue(sectionHandle, valueName, defaultVal);
        }
    }
    return value != 0;
}

bool igRegistry::getValue(int sectionHandle, const char *valueName, igStringRef &strVal, const char *defaultVal,
                          unsigned char createValue) {
    igRegistryValue *value = findValue(sectionHandle, valueName, false);
    if (value != 0) {
        strVal = registryText(value->_value);
    } else {
        strVal = defaultVal;
        if (createValue) {
            setValue(sectionHandle, valueName, defaultVal);
        }
    }
    return value != 0;
}

bool igRegistry::getValue(int sectionHandle, const char *valueName, igStringRefList *strListVal, unsigned char createValue) {
    igStringObj *a;
    igStringObj *b;
    const char *saved;
    int i; igRegistryValue *p; int n; int j; igStringObj *c; char *s2; igStringObj *held; igStringObj *c2; int at; int at2;

    saved = valueName;
    p = findValue(sectionHandle, valueName, false);
    if (p != 0) {
        igStringObj_Split(p->_value, 0x2C, (::igTDataList<char *> *)strListVal);
        *(igStringObj **)&a = (igStringObj *)igStringObj_Create((int)getMemoryPool());
        for (i = 0; i < strListVal->_count; i++) {
            {
                igStringRef r1 = StringList_CopyRetained(strListVal, i);
                igStringObj_Set(a, r1.p);
            }
            igStringObj_Trim(a);
            int *tmp;
            *(int **)&tmp = intern(listValueText(a));
            setStringAt(strListVal, i, &tmp);
            releaseRef(tmp);
        }
        held = a;
        ::igObject::release(held);
    } else if (createValue) {
        *(igStringObj **)&b = (igStringObj *)igStringObj_Create((int)getMemoryPool());
        n = strListVal->_count;
        if (n != 0) {
            igStringRef r2 = StringList_CopyRetained(strListVal, 0);
            igStringObj_Set(b, r2.p);
        }
        for (j = 1; j < n; j++) {
            c = b; at = c->_length;
            igStringObj_Insert(c, (char *)",", at, strlen(","));
            igStringRef r3 = StringList_CopyRetained(strListVal, j);
            /* matching construct: the word is read through the holder's address; r3.p swaps s0 and s6 */
            c2 = b; s2 = *(char **)&r3; at2 = c2->_length; igStringObj_Insert(c2, s2, at2, strlen(s2));
        }
        setValue(sectionHandle, saved, (const char *)listValueText(b));
        held = b;
        ::igObject::release(held);
    }
    return p != 0;
}

/* Read a boolean value; when it is missing or unreadable, `defaultVal` is returned through `boolVal`
 * and, with `createValue`, written into the registry. */
bool igRegistry::getValue(int sectionHandle, const char *valueName, unsigned char &boolVal, unsigned char defaultVal,
                          unsigned char createValue) {
    bool found = false;
    igRegistryValue *value = findValue(sectionHandle, valueName, false);
    if (value != 0 && igStringObj_ParseBool(value->_value, (char *)&boolVal)) {
        found = true;
    }
    if (!found) {
        boolVal = defaultVal;
        if (createValue) {
            setValue(sectionHandle, valueName, defaultVal);
        }
    }
    return found;
}
}
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
                if (((Gap::Core::igMetaEnum *)metaEnum)->getEnumValue(name, flag) == g_resultSuccess) {
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
            if (((Gap::Core::igMetaEnum *)metaEnum)->getEnumValue(name, *value) == g_resultSuccess) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

namespace Gap {
namespace Core {

bool igRegistry::getEnumValue(int sectionHandle, const char *valueName, igMetaEnum *metaEnum, int &enumVal,
                              int defaultVal, unsigned char createValue) {
    void *value = findValue(sectionHandle, valueName, false);
    if (value != 0) {
        igRegistry_ParseEnumValue((char *)enumValueText(value), &enumVal, (::igMetaEnum *)metaEnum, (char *)&percent_s[0]);
    } else {
        enumVal = defaultVal;
        if (createValue) {
            setValue(sectionHandle, valueName, defaultVal);
        }
    }
    return value != 0;
}

bool igRegistry::getFlagsValue(int sectionHandle, const char *valueName, igMetaEnum *metaEnum, unsigned int &flagsVal,
                               unsigned int defaultVal, unsigned char createValue) {
    void *value = findValue(sectionHandle, valueName, false);
    if (value != 0) {
        igRegistry_ParseEnumFlags((char *)flagsValueText(value), (int *)&flagsVal, (int)metaEnum, (char *)&percent_s[0]);
    } else {
        flagsVal = defaultVal;
        if (createValue) {
            setValue(sectionHandle, valueName, (int)defaultVal);
        }
    }
    return value != 0;
}

igRegistryValue *igRegistry::getRawValue(int index) {
    return _valueTable->get(index);
}

int igRegistry::getRawValueCount() const {
    return _valueTable->getCount();
}

bool igRegistry::setValue(int sectionHandle, const char *valueName, int intVal) {
    igRegistryValue *value = findValue(sectionHandle, valueName, true);
    if (value == 0) return false;
    igStringObj_SetInt((int)value->_value.p, intVal, (const char *)percent_d_7);
    return true;
}

bool igRegistry::setValue(int sectionHandle, const char *valueName, float floatVal) {
    igRegistryValue *value = findValue(sectionHandle, valueName, true);
    if (value == 0) {
        return false;
    }
    igStringObj_SetFloat((int)value->_value.p, "%f", floatVal);
    return true;
}

bool igRegistry::setValue(int sectionHandle, const char *valueName, const char *strVal) {
    igRegistryValue *value = findValue(sectionHandle, valueName, true);
    if (value == 0) return false;
    igStringObj_Set(value->_value, strVal);
    return true;
}

bool igRegistry::setValue(int sectionHandle, const char *valueName, unsigned char boolVal) {
    igRegistryValue *value = findValue(sectionHandle, valueName, true);
    if (value == 0) {
        return false;
    }
    igStringObj_SetBool((int)value->_value.p, boolVal, 0);
    return true;
}

void igRegistry::reset() {
    int n2;
    int j;
    ::igTDataList< ::igObject *> *l;
    int n1;
    int i;
    ::igObject *p;

    l = (::igTDataList< ::igObject *> *)_additionalSectionNames.p;
    n1 = l->_count;
    for (i = 0; i < n1; i++) {
        p = l->_data[i];
        ::igObject::release(p);
    }
    n2 = l->_count;
    for (j = 0; j < n2; j++) {
        l->_data[j] = 0;
    }
    l->_count = 0;
    _valueTable->clearAll();
}

/* Read registry text: `[section]` lines open a section, `key = value` lines set values (only new ones
 * unless `replaceDuplicates`), and `#` lines are directives. */
void igRegistry::parseRegistry(igFile *file, unsigned char replaceDuplicates) {
    char equals;
    unsigned char showQueries;
    int lineNum;
    char line[4096];
    char key[4096];
    char value[4096];
    int fields;
    int section;
    igRegistry *config;

    lineNum = 0;
    section = -1;
    while (readLine(file, line, &lineNum)) {
        if (sscanf(line," %c ", value) <= 0) {
            continue;
        }
        if (value[0] == '#') {
            preProcessLine(file, line, lineNum, replaceDuplicates);
            continue;
        }
        if (sscanf(line," [ %[_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./\\-] ]", value) == 1) {
            section = findSection(value, true);
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
        if (!replaceDuplicates && findValue(section, key, false) != 0) {
            continue;
        }
        setValue(section, key, (const char *)value);
    }
    config = (igRegistry *)g_objectSystem->configRegistry;
    showQueries = _showQueries;
    config->getValue(2, "showRegistryQueries", showQueries, showQueries, false);
    _showQueries = showQueries;
    if (_showQueries != 0 && config == this) {
        config->getValue(2, "showRegistryQueries", showQueries, showQueries, false);
    }
}

bool igRegistry::readLine(igFile *file, char *buffer, int *lineNum) {
    int c = file->fgetc();
    int prev = 0;
    bool comment = false;
    int n = 0;
    bool ret = false;
    bool lead = true;
    while (c != -1 && c != 0) {
        while (lead) {
            if (c == 0x20 || c == 9) { prev = c; c = file->fgetc(); }
            else lead = false;
        }
        if (c == 13) { c = file->fgetc(); continue; }
        if (c != 10) {
            if (!comment) {
                if (c == 0x3B) comment = true;
                else if (c == 0x2F && prev == 0x2F) { n -= 1; comment = true; }
                else {
                    if (n < 0xFFF) buffer[n] = c;
                    n += 1;
                }
            }
            goto next;
        }
        if (prev != 0x5C) break;
        lead = true;
        *lineNum += 1;
        if (!comment) n -= 1;
    next:
        prev = c;
        c = file->fgetc();
    }
    if (n > 0 || c != -1) {
        ret = true;
        *lineNum += 1;
    }
    if (n >= 0x1000) n = 0xFFF;
    buffer[n] = 0;
    return ret;
}

igRegistryValue *igRegistry::findValue(int sectionHandle, const char *valueName, unsigned char create) {
    int i = 0;
    int freeSlot = -1;
    igSmartPointer<igRegistryValue> value;
    for (; i < _valueTable->getCount(); i++) {
        value = _valueTable->get(i);
        if (value != 0 && sectionHandle == value->_section) {
            if (_valueNameCaseSensitive != 0) {
                if (strcmp(registryText(value->_valueName), valueName) == 0) {
                    return value;
                }
            } else {
                if (igStrcasecmp(registryText(value->_valueName), valueName) == 0) {
                    return value;
                }
            }
        } else if (value == 0 && freeSlot < 0) {
            freeSlot = i;
        }
    }
    if (create) {
        igRegistryValueList *values;
        if (freeSlot < 0) {
            freeSlot = _valueTable->getCount();
            _valueTable->setCount(freeSlot * 2);
        }
        igMemoryPoolView *pool = (igMemoryPoolView *)getMemoryPool();
        value.release();
        value.p = igRegistryValue::_instantiateFromPool(pool);
        values = _valueTable;
        values->set(freeSlot, value);
        value->_section = sectionHandle;
        igStringObj_Set(value->_valueName, valueName);
        return value;
    }
    return 0;
}

const char *igRegistry::getSectionName(int sectionHandle) {
    if (sectionHandle < 11) {
        return g_registrySectionNames[sectionHandle];
    }
    return registryText(((igStringObj **)_additionalSectionNames->_data)[sectionHandle - 11]);
}

/* An `#include "file"` or `#include <file>` directive: read the named file, relative to this file's
 * directory first, into the registry. Includes nest at most 12 deep. */
void igRegistry::preProcessLine(igFile *file, char *lineBuffer, int lineNum, unsigned char replaceDuplicates) {
    char open;
    char close;
    char path[4096];
    int found;

    if (sscanf(lineBuffer," # include %c %[^<>\"\n\r] %c", &open, path, &close) != 3) {
        return;
    }
    if (open != '"' && open != '<') return;
    if ((open == '"' && close != '"') || (open == '<' && close != '>')) return;
    if (g_registryIncludeDepth < 12) {
        g_registryIncludeDepth += 1;
        igSmartPointer<igRegistry> include(_instantiateFromPool(getMemoryPool()));
        found = 0;
        igStringObjRef directory((igStringObj *)igStringObj_Create((int)getMemoryPool()));
        igStringObj_Set(directory.get(), file->_fileName.p);
        igStringObj_RemovePathFilename(directory.get());
        if (directory.get()->_length != 0) {
            igRegistry *target = include.get();
            found = target->load(path, igStringObj_Text(directory.get())) & 0xFF;
        }
        if (found != 0 || include.get()->load(path, "")) {
            merge(include.get(), replaceDuplicates);
        }
        g_registryIncludeDepth -= 1;
    }
}
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
        ((Gap::Core::igRegistry *)config)->getValue(2,"assertOnErrors", g_reportAssertOnErrors, 1, 0);
        igStringObj *name = (igStringObj *)igStringObj_Create(allocator());
        if (((Gap::Core::igRegistry *)config)->getValue(2,"defaultReportLevel", *(igStringObjRef *)&name, (char *)"", 0)) {
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
        igObject::release(name);
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
    return igSmartPointer<igObject>((igObject *)((Gap::Core::igObjectList *)(((igResource *)directory)->_directoryList))->search((Gap::Core::igStringMetaField *)Gap::Core::igDirectory::k_name, name), kRetainReference);
}

void igResource_AddDirectory(int *p, int directory)
{
    ((Gap::Core::igObjectList *)(((igResource *)p)->_directoryList))->append((Gap::Core::igObject *)directory);
}

static inline void setNames(igResource *self, const igSmartPointer<igObject> &value) {
    igObject *held = value.p;
    igObject *old;
    if (held) held->_refCount = held->_refCount + 1;
    old = (igObject *)self->_alignmentStrings;
    igObject::release(old);
    self->_alignmentStrings = (int)held;
}

static inline void setValues(igResource *self, const igSmartPointer<igObject> &value) {
    igObject *held = value.p;
    igObject *old;
    if (held) held->_refCount = held->_refCount + 1;
    old = (igObject *)self->_alignmentValues;
    igObject::release(old);
    self->_alignmentValues = (int)held;
}

void igResource_AddAlignment(igResource *self, const char *name, int value) {
    if (self->_alignmentStrings == 0) {
        setNames(self, igSmartPointer<igObject>((igObject *)igStringObjList_Create((int)(((void *)((Gap::Core::igObject *)self)->getMemoryPool())))));
        setValues(self, igSmartPointer<igObject>((igObject *)igIntList_Create((int)(((void *)((Gap::Core::igObject *)self)->getMemoryPool())))));
    }
    igSmartPointer<igStringObj> entry((igStringObj *)igStringObj_Create((int)(((void *)((Gap::Core::igObject *)self)->getMemoryPool()))));
    igStringObj_Set(entry.p, name);
    ((Gap::Core::igObjectList *)self->_alignmentStrings)->append((Gap::Core::igObject *)entry.p);
    igTDataList<int> *values = (igTDataList<int> *)self->_alignmentValues;
    int top = values->count();
    if (top < values->_capacity) {
        values->_count = values->_count + 1;
    } else {
        ((Gap::Core::igDataList *)values)->resizeAndSetCount(top + 1, 4);
    }
    values->_data[top] = value;
}

static inline void setImageDirectory(igResource *owner, const igSmartPointer<igDirectory> &value) {
    igDirectory *held = value.p;
    igDirectory *old;
    if (held != 0) held->_refCount = held->_refCount + 1;
    old = (igDirectory *)owner->_imageDirectory;
    igObject::release(old);
    owner->_imageDirectory = (int)held;
}

igDirectory *igResource_GetImageDirectory(igResource *self) {
    if (self->_imageDirectory == 0) {
        int *hd;
        int v;
        int s2;
        igDirectory *s0;
        int old;
        setImageDirectory(self, igSmartPointer<igDirectory>(((igDirectory *)Gap::Core::igDirectory::_instantiateFromPool(((Gap::Core::igObject *)self)->getMemoryPool()))));
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

