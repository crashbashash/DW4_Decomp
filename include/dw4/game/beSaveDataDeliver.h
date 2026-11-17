#ifndef DW4_BESAVEDATADELIVER_H
#define DW4_BESAVEDATADELIVER_H

struct beSaveDataDeliver;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void beSaveDataDeliver_AllocateData(struct beSaveDataDeliver *deliver, int size);
void beSaveDataDeliver_EnsureRegistered(void);
void beSaveDataDeliver_FreeData(struct beSaveDataDeliver *deliver);
struct igMetaObject *beSaveDataDeliver_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
