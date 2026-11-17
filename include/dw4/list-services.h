#ifndef DW4_LIST_SERVICES_H
#define DW4_LIST_SERVICES_H

/* Pool-string services the scene graph library defines. A pool string's characters follow a
 * reference-count word (text[-1]); each call takes a reference on the string it stores. Strings
 * are passed by pointer to the holder's word, the way a holder class passed by reference or by
 * value reaches the callee. */
#include "dw4/igTDataList.h"
struct igDataList;
struct igObject;
struct igStringRefList;
struct igStringMetaField;

#ifdef __cplusplus
extern "C" {
#endif

/* Appends *value to the list. */
void StringList_AppendRetained(struct igStringRefList *list, char *const *value);
/* The index of *key in the list, searching from `start`, or -1. */
int igStringRefList_IndexOf(struct igStringRefList *list, char *const *key, int start);
/* Stores *token in the field's slot of `object`, releasing the string it held. */
void igStringMetaField_AssignRetainedToken(struct igStringMetaField *field, void *object, char **token);
int ObjectList_RemoveAllRetained(igTDataList<struct igObject *> *list, struct igObject *object, int start);
void ObjectList_ResizeRetained(igTDataList<struct igObject *> *self, int count);
void List_AppendWords(struct igDataList *list, int count, const int *words);
void ObjectList_AppendRetainedList(igTDataList<struct igObject *> *self, igTDataList<struct igObject *> *source);

#ifdef __cplusplus
}
#endif

#endif
