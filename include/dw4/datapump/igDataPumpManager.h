#ifndef DW4_IGDATAPUMPMANAGER_H
#define DW4_IGDATAPUMPMANAGER_H

/* igDataPumpManager drives the data pumps of its _dataPumpList: appending a pump list or the list of
 * an igDataPumpInfo, and updating every pump with the time. */
struct igDataPumpManager;
struct igDataPumpList;
struct igDataPumpInfo;
struct igObject;

#ifdef __cplusplus
extern "C" {
#endif
struct igDataPumpList *igDataPumpInfo_GetList(struct igDataPumpInfo *self);
int igDataPumpInfo_Append(struct igDataPumpInfo *self, struct igObject *pump);
int igDataPumpManager_Update(struct igDataPumpManager *self, long long time);
int igDataPumpManager_AppendList(struct igDataPumpManager *self, struct igDataPumpList *list);
int igDataPumpManager_AppendInfo(struct igDataPumpManager *self, struct igDataPumpInfo *info);
void igDataPumpManager_EnsureRegistered(void);
struct igMetaObject *igDataPumpManager_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
