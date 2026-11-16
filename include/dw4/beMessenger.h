#ifndef DW4_BEMESSENGER_H
#define DW4_BEMESSENGER_H

struct beBaseInfoRam;
struct beMessenger;
struct igMetaEnum;
struct igMetaObject;
struct igObject;

#ifdef __cplusplus
extern "C" {
#endif

void beMessenger_AppendBool(struct beMessenger *self, unsigned char value);
void beMessenger_AppendFloat(struct beMessenger *self, float value);
void beMessenger_AppendInt(struct beMessenger *self, int value);
void beMessenger_AppendLong(struct beMessenger *self, long long value);
void beMessenger_AppendMatrix(struct beMessenger *self, void *value);
void beMessenger_AppendObject(struct beMessenger *self, struct igObject *object);
void beMessenger_AppendString(struct beMessenger *self, const char *text);
void beMessenger_AppendVec3(struct beMessenger *self, float *value);
void beMessenger_ClearBool(struct beMessenger *self);
void beMessenger_ClearInt(struct beMessenger *self);
void beMessenger_ClearObjects(struct beMessenger *self);
void beMessenger_ClearVec3(struct beMessenger *self);
struct beMessenger *beMessenger_CreateInstance(int allocator);
void beMessenger_DispatchSelected(struct beMessenger *self, const char *message);
void beMessenger_EnqueueSelected(struct beMessenger *self, const char *text, long long delay);
void beMessenger_EnsureRegistered(void);
unsigned char beMessenger_GetBool(struct beMessenger *self, int index);
int beMessenger_GetBoolCount(struct beMessenger *self);
float beMessenger_GetFloat(struct beMessenger *self, int index);
int beMessenger_GetFloatCount(struct beMessenger *self);
int beMessenger_GetInt(struct beMessenger *self, int index);
int beMessenger_GetIntCount(struct beMessenger *self);
long long beMessenger_GetLong(struct beMessenger *self, int index);
int beMessenger_GetLongCount(struct beMessenger *self);
void beMessenger_GetMatrix(void *out, struct beMessenger *self, int index);
int beMessenger_GetMatrixCount(struct beMessenger *self);
struct igObject *beMessenger_GetObject(struct beMessenger *self, int index);
int beMessenger_GetObjectCount(struct beMessenger *self);
struct igMetaObject *beMessenger_GetOrCreateMetaObject(void);
const char *beMessenger_GetString(struct beMessenger *self, int index);
int beMessenger_GetStringCount(struct beMessenger *self);
void beMessenger_GetVec3(float *out, struct beMessenger *self, int index);
int beMessenger_GetVec3Count(struct beMessenger *self);
void beMessenger_PopArgContext(struct beMessenger *self);
void beMessenger_PrepareDelayedGroup(struct beMessenger *self, const char *group);
void beMessenger_PrepareDelayedSelection(struct beMessenger *self, const char *group, const char *name, int number);
void beMessenger_PushArgContext(struct beMessenger *self);
void beMessenger_RegisterReceiver(struct beMessenger *self, struct beBaseInfoRam *ram, const char *group, const char *name, int id);
void beMessenger_RegisterReceiverFromInfo(struct beMessenger *self, struct beBaseInfoRam *ram, const char *group);
void beMessenger_ResizeBool(struct beMessenger *self, int count);
int beMessenger_ResolveEnumValue(struct beMessenger *self, struct igMetaEnum *metaEnum, const char *name);
void beMessenger_SelectGroup(struct beMessenger *self, const char *group);
void beMessenger_SelectReceivers(struct beMessenger *self, const char *group, const char *name, int id);
void beMessenger_SendDelayedGroup(struct beMessenger *self, const char *group, const char *message, long long delay);
void beMessenger_SendDelayedNamed(struct beMessenger *self, const char *group, const char *name, int id, const char *message, long long delay);
void beMessenger_SendGroup(struct beMessenger *self, const char *group, const char *message);
void beMessenger_SendNamed(struct beMessenger *self, const char *group, const char *name, int id, const char *message);
void beMessenger_SendRam(struct beMessenger *self, const char *group, int id, const char *message);
void beMessenger_SetBool(struct beMessenger *self, int index, unsigned char value);
void beMessenger_SetFreezeTime(struct beMessenger *self, int frozen);
void beMessenger_SetInt(struct beMessenger *self, int index, int value);
void beMessenger_SetRunCheck(struct beMessenger *self, unsigned char enabled);

extern struct igMetaObject *g_beMessenger_metaObject;

#ifdef __cplusplus
}
#endif

#endif
