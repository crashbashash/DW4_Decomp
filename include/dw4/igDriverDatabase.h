#ifndef DW4_IGDRIVERDATABASE_H
#define DW4_IGDRIVERDATABASE_H

#include "dw4/igTDataList.h"
struct ConfigNode;
struct igDriverDatabase;

extern "C" {
void igDriverDatabase_SetSubPropertyValue(struct igDriverDatabase *self, int section, const char *key, char *value);
void *igDriverDatabase_Create(int pool);
int igDriverDatabase_LoadFromFile(void *self, int text, int fileName);
int igDriverDatabase_ApplyToRegistry(struct igDriverDatabase *self, int registry, int section, int mergeMode);
igTDataList<struct ConfigNode *> *igDriverDatabase_ParseDatabase(struct igDriverDatabase *s);
void igDriverDatabase_DeleteConfigNodeList(void *self, igTDataList<struct ConfigNode *> *list);
}

#endif
