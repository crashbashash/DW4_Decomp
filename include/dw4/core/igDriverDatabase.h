#ifndef DW4_IGDRIVERDATABASE_H
#define DW4_IGDRIVERDATABASE_H

#include "dw4/core/igTDataList.h"
struct ConfigNode;
struct igDriverDatabase;
struct igVisualContextView;

extern "C" {
void igDriverDatabase_SetSubPropertyValue(struct igDriverDatabase *self, int section, const char *key, char *value);
void *igDriverDatabase_Create(int pool);
int igDriverDatabase_LoadFromFile(void *self, int text, int fileName);
int igDriverDatabase_ApplyToRegistry(struct igDriverDatabase *self, int registry, int section, int mergeMode);
igTDataList<struct ConfigNode *> *igDriverDatabase_ParseDatabase(struct igDriverDatabase *s);
void igDriverDatabase_DeleteConfigNodeList(void *self, igTDataList<struct ConfigNode *> *list);
int igDriverDatabase_Load(struct igDriverDatabase *self, const char *fileName, const char *rootPath);
void igDriverDatabase_SetCurrentProperty(void *self, int property, const char *value);
void igDriverDatabase_GatherProperties(void *self, igTDataList<struct igVisualContextView *> *list);
}

#endif
