#ifndef DW4_BESAVEDATADELIVER_H
#define DW4_BESAVEDATADELIVER_H

struct beSaveDataDeliver;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void beSaveDataDeliver_AllocateData(struct beSaveDataDeliver *deliver, int size);
void beSaveDataDeliver_FreeData(struct beSaveDataDeliver *deliver);

#ifdef __cplusplus
}
#endif

#endif
