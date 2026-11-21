#ifndef DW4_IGREGISTRY_H
#define DW4_IGREGISTRY_H

/* The configuration registry is Gap::Core::igRegistry (alchemy-kit_202309 igCore/igRegistry.h); the
 * object system holds one (g_objectSystem->configRegistry). */
struct igRegistry;
struct igStringObj;

extern "C" {
/* Tail-jump copies of the registry's readers in the data-pump library: each reader returns whether the
 * value was found; when it was not, `defaultValue` is stored through the out pointer and, with `create`,
 * written into the registry. */
bool igGetRegistryValue_Int(struct igRegistry *registry, int section, const char *key, int *out, int defaultValue, unsigned char create);
bool igGetRegistryValue_Float(struct igRegistry *registry, int section, const char *key, float *out, unsigned char create, float defaultValue);
bool igGetRegistryValue_StringObj(struct igRegistry *registry, int section, const char *key, struct igStringObj **out, const char *defaultValue, unsigned char create);
bool igGetRegistryValue_String(struct igRegistry *registry, int section, const char *key, char **out, char *def, unsigned char create);
bool igGetRegistryValue_Bool(struct igRegistry *registry, int section, const char *name, unsigned char *value, unsigned char defaultValue, unsigned char create);
int igRegistry_IsLoadingEnabled(void);
}

#endif
