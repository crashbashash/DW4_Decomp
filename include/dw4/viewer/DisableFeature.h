#ifndef DW4_DISABLEFEATURE_H
#define DW4_DISABLEFEATURE_H

/* One entry of the viewer's disable features: whether the feature may be switched off, its
 * igDisableExt feature id and its name ("texture", "lighting", "blending", ...). */
struct DisableFeature {
    bool supported;
    int feature;
    const char *name;

    DisableFeature(bool supported_, int feature_, const char *name_) {
        supported = supported_;
        feature = feature_;
        name = name_;
    }
};

/* Defined by igViewerSceneInfoManager.cpp; the renderer switches the features off and on. */
extern DisableFeature g_viewerDisableFeatures[12];

#endif
