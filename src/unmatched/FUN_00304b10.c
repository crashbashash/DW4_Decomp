typedef struct IniKeyText { char pad[4]; int _refCount; char *text; } IniKeyText;
typedef struct IniValueList { char pad[4]; int _refCount; int count; } IniValueList;
typedef struct IniSystemTables { char pad[56]; void *ini; } IniSystemTables;
extern IniSystemTables *DAT_00586dc8;
extern char *DAT_004c22f0;
extern char DAT_004fafc8[];
IniValueList *FUN_002b90e0(int);
void FUN_00304840(void *, char *, char *);
int FUN_00306360(void *, char *, int);
unsigned int FUN_003064b0(void *, int);
int FUN_00306510(void *, int, int, IniKeyText **);
int FUN_00306aa0(void *, int, char *, IniValueList *, int);
void StringChunk_ReleaseHeader(int, int *);
void StringList_CopyRetained(char **, IniValueList *, int);
void igObject_Destroy(void *);
int igObject_GetAllocator(void *);
static inline char *keyText(IniKeyText *s) { char *t = s->text; if (t == 0) { return DAT_004c22f0; } return t; }
static inline void dropKey(IniKeyText *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
    }
}
static inline void dropValues(IniValueList *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
    }
}
static inline void dropString(char *s) {
    if (s != 0) {
        int *hd = (int *)(s - 8);
        int rc = ((int *)s)[-1] - 1;
        ((int *)s)[-1] = rc;
        if (rc == 0) { StringChunk_ReleaseHeader(*hd, hd); }
    }
}
void FUN_00304b10(void *self) {
    void *ini;
    int section;
    unsigned int n;
    unsigned int i;
    int j;
    IniKeyText *key;
    IniValueList *values;
    char *string;
    char *text;
    IniValueList *held;
    ini = DAT_00586dc8->ini;
    section = FUN_00306360(ini, DAT_004fafc8, 1);
    if (section >= 0) {
        n = FUN_003064b0(ini, section);
        for (i = 0; i < n; i++) {
            key = 0;
            if (FUN_00306510(ini, section, i, &key) == 0) {
                dropKey(key);
            } else {
                *(IniValueList **)&values = FUN_002b90e0(igObject_GetAllocator(self));
                held = values;
                if (FUN_00306aa0(ini, section, keyText(key), held, 0) == 0) {
                    dropValues(values);
                    dropKey(key);
                } else {
                    for (j = 0; j < (held = values)->count; j++) {
                        StringList_CopyRetained(&string, values, j);
                        text = string;
                        FUN_00304840(self, keyText(key), text);
                        dropString(string);
                    }
                    dropValues(held);
                    dropKey(key);
                }
            }
        }
    }
}
