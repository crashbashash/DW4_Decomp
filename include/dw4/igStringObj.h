#ifndef DW4_IGSTRINGOBJ_H
#define DW4_IGSTRINGOBJ_H

struct igStringObj;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

/* Nonzero when `text` ends in a dot and `extension`, compared without case; `extension` may include
 * the dot. */
int igStringObj_HasFileExtensionText(char *text, char *extension);
void *igStringObj_Create(int pool);
void igStringObj_EnsureRegistered(void);
/* The text an empty igStringObj reads as (its buffer is null). */
extern char *g_stringObjEmptyText;
void igStringObj_Set(struct igStringObj *self, const char *text);
void igStringObj_SetInt(int self, int value, const char *format);
void igStringObj_Insert(struct igStringObj *self, char *insert, unsigned int at, unsigned int n);
int igStringObj_Erase(struct igStringObj *self, unsigned int pos, unsigned int len);
void igStringObj_ToLower(struct igStringObj *self);
/* Keeps the text from its last dot on, or empties it when a directory separator comes first. */
void igStringObj_KeepExtension(struct igStringObj *self);
void igStringObj_StripDirectory(struct igStringObj *self);

#ifdef __cplusplus
}
#endif

#endif
