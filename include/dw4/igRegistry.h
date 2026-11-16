#ifndef DW4_IGREGISTRY_H
#define DW4_IGREGISTRY_H

/* The configuration registry: sections of named values read with a default, optionally created when missing. `registry` is the igRegistry the object system holds. */
struct igRegistry;
struct igStringObj;

extern "C" {
int igRegistry_GetSectionIndex(struct igRegistry *self, char *name, int create);
unsigned char igRegistry_GetValueBool(int registry, int section, const char *name, char *value, int defaultValue, int create);
bool igRegistry_GetValueInt(int registry, int section, const char *key, int *out, int defaultValue, int create);
int igRegistry_GetValueString(int registry, int section, const char *key, int **out, char *def, int create);
int igRegistry_GetValueStringObj(int registry, int section, const char *key, struct igStringObj **out, const char *defaultValue, int create);
}

#endif
