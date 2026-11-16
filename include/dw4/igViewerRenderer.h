#ifndef DW4_IGVIEWERRENDERER_H
#define DW4_IGVIEWERRENDERER_H

struct igMetaObject;
struct igViewerRenderer;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igViewerRenderer_metaObject;
void igViewerRenderer_UpdateProjection(struct igViewerRenderer *renderer);
void igViewerRenderer_UpdateViewMatrix(struct igViewerRenderer *renderer);
void igViewerRenderer_UpdateSorting(struct igViewerRenderer *renderer);
void igViewerRenderer_UpdateScene(struct igViewerRenderer *renderer);
void igViewerRenderer_UpdateLighting(struct igViewerRenderer *renderer);
void igViewerRenderer_UpdateRenderStates(struct igViewerRenderer *renderer);
/* Takes the clear colour, the head light and the render states from the shared viewer options. */
void igViewerRenderer_ApplyOptions(struct igViewerRenderer *renderer);

#ifdef __cplusplus
}
#endif

#endif
