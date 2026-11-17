#ifndef DW4_IGVIEW_H
#define DW4_IGVIEW_H

struct igView;
struct igModel;
struct igMetaObject;
struct CallbackArray;

#ifdef __cplusplus
extern "C" {
#endif

struct CallbackArray *igView_Register(void);
void igView_SetModel(struct igView *view, struct igModel *model);
struct igMetaObject *igView_GetPublishedMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
