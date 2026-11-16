#ifndef DW4_BEMODELCTRLINFOWORK_H
#define DW4_BEMODELCTRLINFOWORK_H

struct beBaseInfoRam;
struct beModelCtrl;
struct beModelCtrlInfoWork;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beModelCtrlInfoWork *beModelCtrlInfoWork_Create(int allocator);
void *beModelCtrlInfoWork_Destroy(struct beModelCtrlInfoWork *self, long long delete_storage);
void *beModelCtrlInfoWork_Register(void);
void beModelCtrlInfoWork_SetSeqLabel(struct beModelCtrl *self, struct beBaseInfoRam *ram, struct beModelCtrlInfoWork *work, const char *seqName, const char *labelName);

extern struct igMetaObject *g_beModelCtrlInfoWork_metaObject;
extern int g_beModelCtrlInfoWork_vtable[4];

#ifdef __cplusplus
}
#endif

#endif
