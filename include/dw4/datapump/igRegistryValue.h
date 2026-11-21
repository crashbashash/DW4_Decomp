#ifndef DW4_IGREGISTRYVALUE_H
#define DW4_IGREGISTRYVALUE_H

/* The vector conversions and registry reads of the Alchemy utilities: a vector parsed from text
 * (with a sscanf format, or the flexible array form when the format is null), a vector formatted
 * into an interned string, and a vector read from a registry key whose default is the formatted
 * default vector. */
struct igRegistry;

#ifdef __cplusplus
extern "C" {
#endif
int igConvertString_Vec4f(const char *text, float *vector, const char *format);
int igConvertToString_Vec3f(char **result, const float *vector, const char *format);
int igConvertToString_Vec4f(char **result, const float *vector, const char *format);
int igGetRegistryValue_Vec3f(struct igRegistry *registry, int section, const char *key, float *value, const float *defaultValue, unsigned char create);
int igGetRegistryValue_Vec4f(struct igRegistry *registry, int section, const char *key, float *value, const float *defaultValue, unsigned char create);
#ifdef __cplusplus
}
#endif

#endif
