#ifndef DW4_IGREGISTRY_H
#define DW4_IGREGISTRY_H

/* The configuration registry: sections of named values read with a default, optionally created when
 * missing. `registry` is the igRegistry the object system holds (g_objectSystem->configRegistry).
 * Each reader returns whether the value was found; when it was not, `defaultValue` is stored through
 * the out pointer and, with `create`, written into the registry. */
struct igStringRefList;
struct igMetaObject;
struct igRegistry;
struct igStringObj;

extern "C" {
int igRegistry_GetSectionIndex(struct igRegistry *self, char *name, int create);
unsigned char igRegistry_GetValueBool(struct igRegistry *registry, int section, const char *name, unsigned char *value, int defaultValue, int create);
bool igRegistry_GetValueInt(struct igRegistry *registry, int section, const char *key, int *out, int defaultValue, int create);
bool igRegistry_GetValueFloat(struct igRegistry *registry, int section, const char *key, float *out, int create, float defaultValue);
/* `out` holds an interned string: the old one is released, the new one retained */
int igRegistry_GetValueString(struct igRegistry *registry, int section, const char *key, char **out, char *def, int create);
int igRegistry_GetValueStringObj(struct igRegistry *registry, int section, const char *key, struct igStringObj **out, const char *defaultValue, int create);
/* Tail-jump copies of the readers in the data-pump library, with the readers' own signatures. */
bool igGetRegistryValue_Int(struct igRegistry *registry, int section, const char *key, int *out, int defaultValue, int create);
bool igGetRegistryValue_Float(struct igRegistry *registry, int section, const char *key, float *out, int create, float defaultValue);
int igGetRegistryValue_StringObj(struct igRegistry *registry, int section, const char *key, struct igStringObj **out, const char *defaultValue, int create);
int igGetRegistryValue_String(struct igRegistry *registry, int section, const char *key, char **out, char *def, int create);
unsigned char igGetRegistryValue_Bool(struct igRegistry *registry, int section, const char *name, unsigned char *value, int defaultValue, int create);
struct igMetaObject *igRegistry_GetOrCreateMetaObject(void);
void igRegistry_EnsureRegistered(void);
int igRegistry_GetNumValuesInSection(int registry, int section);
bool igRegistry_GetKeyName(int registry, int section, int index, struct igStringObj **key);
bool igRegistry_GetValueStringList(void *self, int section, const char *key, struct igStringRefList *list, int create);
void *igRegistry_Create(int pool);
bool igRegistry_Load(struct igRegistry *self, char *name, char *dir);
int igRegistry_Merge(void *self, struct igRegistry *inc, int overwrite);
extern struct igMetaObject *g_igRegistry_metaObject;
int igRegistry_GetValueEntry(void *self, int index);
int igRegistry_GetValueCount(void *self);
int igRegistry_IsLoadingEnabled(void);
}

#endif
