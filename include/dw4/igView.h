#ifndef DW4_IGVIEW_H
#define DW4_IGVIEW_H

struct igView;
struct igModel;

#ifdef __cplusplus
extern "C" {
#endif

struct CallbackArray *igView_Register(void);
void igView_SetModel(struct igView *view, struct igModel *model);

#ifdef __cplusplus
}
#endif

#endif
