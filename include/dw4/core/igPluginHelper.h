#ifndef DW4_IGPLUGINHELPER_H
#define DW4_IGPLUGINHELPER_H

struct igPluginHelper;

#ifdef __cplusplus
extern "C" {
#endif
void igPluginHelper_AddRepository(struct igPluginHelper *helper, int name, int location, int locationType);

#ifdef __cplusplus
}
#endif

#endif
