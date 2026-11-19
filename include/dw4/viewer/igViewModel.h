#ifndef DW4_IGVIEWMODEL_H
#define DW4_IGVIEWMODEL_H

struct igMetaObject;
struct igMetaField;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igViewModel_metaObject;
extern struct igMetaField *g_igViewModel_viewMatrixMetaField;
extern struct igMetaField *g_igViewModel_hfovMetaField;
extern struct igMetaField *g_igViewModel_nearPlaneMetaField;
extern struct igMetaField *g_igViewModel_farPlaneMetaField;
extern struct igMetaField *g_igViewModel_positionMetaField;
extern struct igMetaField *g_igViewModel_directionMetaField;
extern struct igMetaField *g_igViewModel_viewUpVectorMetaField;
extern struct igMetaField *g_igViewModel_viewLeftVectorMetaField;
extern struct igMetaField *g_igViewModel_sceneUpVectorMetaField;
extern struct igMetaField *g_igViewModel_ratioMetaField;
extern struct igMetaField *g_igViewModel_drawTimeMetaField;

#ifdef __cplusplus
}
#endif

#endif
