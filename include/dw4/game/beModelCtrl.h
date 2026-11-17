#ifndef DW4_BEMODELCTRL_H
#define DW4_BEMODELCTRL_H

struct beBaseInfoRam;
struct igAABox;
struct beModelCtrl;
struct beModelCtrlInfo;
struct beModelCtrlInfoWork;
struct igMetaEnum;
struct CallbackArray;
struct igMetaObject;
struct igNode;

#ifdef __cplusplus
extern "C" {
#endif

void beModelCtrl_CallLua(struct beModelCtrl *self, struct beBaseInfoRam *ram, const char *function, const char *callName, const char *infoName, int bulletKind, int bulletBoxNo, const char *hitterName, int hitterRamNo, int hitterRecNo);
void beModelCtrl_DrawDebugHitBox(struct beModelCtrl *self, struct igNode *node, struct igAABox *box, float *color);
struct igMetaEnum *beModelCtrl_GetMessageEnum(void);
struct CallbackArray *beModelCtrl_Register(void);
void beModelCtrl_RunCommands(struct beModelCtrl *self, struct beModelCtrlInfo *info, struct beBaseInfoRam *ram, struct beModelCtrlInfoWork *work);
void beModelCtrl__OnGenerate(struct beModelCtrl *self, struct beBaseInfoRam *ram);
void beModelCtrl__OnGenerateFromParent(struct beModelCtrl *self, struct beBaseInfoRam *ram);

extern struct igMetaObject *g_beModelCtrl_metaObject;

#ifdef __cplusplus
}
#endif

#endif
