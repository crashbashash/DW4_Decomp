#include "dw4/core/igSmartPointer.h"
#include "dw4/support/reflected.h"
#include "dw4/viewer/DisableFeature.h"
#include "dw4/gfx/igVisualContextDispatchView.h"
#include "dw4/viewer/igViewerRenderer.h"

#include "dw4/core/igObject.h"
#include "dw4/scenegraph/igTransform.h"
#include "dw4/scenegraph/igLightSet.h"
#include "dw4/scenegraph/igGroup.h"
#include "dw4/scenegraph/igAttrStackManager.h"
#include "dw4/scenegraph/igFrustCullTraversal.h"
#include "dw4/scenegraph/igCommonTraversal.h"
#include "dw4/viewer/ViewerOptions.h"
#include "dw4/gui/igModel.h"
#include "dw4/core/StringPool.h"
#include "dw4/core/igStringRef.h"
#include "dw4/attrs/igColorAttr.h"
#include "dw4/attrs/igAlphaFunctionAttr.h"
#include "dw4/attrs/igLightStateAttr.h"
#include "dw4/core/igDataLists.h"
#include "dw4/core/igObjectRefMetaField.h"
#include "dw4/viewer/igViewerParameters.h"
#include "dw4/scenegraph/igCommonTraversalDispatchView.h"
#include "dw4/scenegraph/igTransformDispatchView.h"
#include "dw4/attrs/igColorAttrDispatchView.h"
#include "dw4/attrs/igAlphaFunctionAttrDispatchView.h"
#include "dw4/attrs/igLightAttrDispatchView.h"
#include "dw4/attrs/igLightStateAttrDispatchView.h"
#include "dw4/attrs/igLightingStateAttrDispatchView.h"
#include "dw4/attrs/igAlphaStateAttrDispatchView.h"
#include "dw4/attrs/igCullFaceAttrDispatchView.h"
#include "dw4/attrs/igShadeModelAttrDispatchView.h"
#include "dw4/attrs/igPolygonModeAttrDispatchView.h"
#include "dw4/gfx/GfxMetaEnums.h"
#include "dw4/maths/igMathConstants.h"
extern "C" {

extern int text_igDisableExt[4];

/* The matrix setter of the visual context; IG_GFX_MATRIX_PROJECTION is the type the projection
 * matrix attribute passes. */
enum { IG_GFX_MATRIX_PROJECTION = 0 };

void igViewerRenderer_UpdateAttr(igViewerRenderer *self, igObject *attr);
void igViewerRenderer_SetOverride(igViewerRenderer *self, igObject *attr, int override);
void igViewerRenderer_FindLights(igViewerRenderer *self, igGroup *node);

struct Tag { };
static inline igObject *createColorAttr() {
    Tag tag = Tag();
    return (igObject *)igColorAttr_CreateInstance(0);
}
static inline igObject *createAlphaFunctionAttr() {
    Tag tag = Tag();
    return (igObject *)igAlphaFunctionAttr_Create(0);
}
static inline igObject *createFrustCullTraversal() {
    Tag tag = Tag();
    return (igObject *)igFrustCullTraversal_Create(0);
}

#include "dw4/attrs/igViewportAttr.h"
#include "dw4/support/list-services.h"
#include "dw4/maths/igMatrix44f.h"

/* Drops every reference `list` holds and empties it. */
#define CLEAR(source) { \
    igObjectList *l = (source); \
    int n = l->_count; \
    int i; \
    int m; \
    int j; \
    igObject *o; \
    for (i = 0; i < n; i++) { \
        o = ((igObject **)l->_data)[i]; \
        if (o != 0) { \
            o->_refCount = o->_refCount - 1; \
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o); \
        } \
    } \
    m = l->_count; \
    for (j = 0; j < m; j++) { \
        ((igObject **)l->_data)[j] = 0; \
    } \
    l->_count = 0; }
static inline void release(igObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}
struct ItemType {};
static inline igObject *createLightState(ItemType) { return (igObject *)igLightStateAttr_Create(0); }

#include "dw4/core/igMetaObject.h"
extern int text_meta[4];
#include "dw4/attrs/igAttr.h"
#include "dw4/attrs/igAttrPool.h"
static inline int asObjectRefField(int field) {
    if (field != 0 && igObject_IsKindOf((igObject *)field, g_igObjectRefMetaField_metaObject) != 0) {
        return field;
    }
    return 0;
}

static inline void removeFromList(int list, int object) {
    ObjectList_RemoveFirstRetained((igTDataList<igObject *> *)list, (igObject *)object, 0);
}

/* The ids are held in a pointer-typed local so the compare puts the call result first (beq v0,s0). */
int igViewerRenderer_ObjectsTraverseNodeSelect(igTraversal *traversal, igNode *node) {
    int *kind;
    if (node->_flags & 1) {
        kind = (int *)g_igTransform_metaObject;
        if ((int *)((igObjectDispatchView *)node)->GetMeta() == kind
            || (kind = (int *)g_igLightSet_metaObject, (int *)((igObjectDispatchView *)node)->GetMeta() == kind)) return 0;
        if (igObject_IsKindOf((igObject *)node, g_igGroup_metaObject) != 0) return 2;
    }
    return 1;
}

void igViewerRenderer_PushLightStates(igViewerRenderer *self) {
    igAttrStackManager *attrStack;
    int count;
    int i;

    attrStack = (igAttrStackManager *)((igFrustCullTraversal *)self->_sceneTraversal)->_attrStack;
    igAttrStackManager_PushLightStateAttr(attrStack, (igLightStateAttr *)self->_headlightStateAttr, 0);
    if (attrStack->_simpleLightMgr == 0 && ((igViewerParameters *)self->_parameters)->_useSceneLights == 0) {
        count = ((igObjectList *)self->_lightStateList)->_count;
        for (i = 0; i < count; i++) {
            igAttrStackManager_PushLightStateAttr(attrStack, ((igLightStateAttr **)((igObjectList *)self->_lightStateList)->_data)[i], 1);
        }
    }
}

void igViewerRenderer_PopLightStates(igViewerRenderer *self) {
    igAttrStackManager *attrStack;
    int count;
    int i;

    attrStack = (igAttrStackManager *)((igFrustCullTraversal *)self->_sceneTraversal)->_attrStack;
    igAttrStackManager_PopLightStateAttr(attrStack, (igLightStateAttr *)self->_headlightStateAttr, 0);
    if ((attrStack->_simpleLightMgr == 0) && (((igViewerParameters *)self->_parameters)->_useSceneLights == 0)) {
        count = ((igObjectList *)self->_lightStateList)->_count;
        for (i = 0; i < count; i++) {
            igAttrStackManager_PopLightStateAttr(attrStack, ((igLightStateAttr **)((igObjectList *)self->_lightStateList)->_data)[i], 1);
        }
    }
}

void igViewerRenderer_Traverse(igViewerRenderer *self) {
    igObject *previous;
    igObject *output;
    ((igVisualContextDispatchView *)self->_visualContext)->setMatrix(IG_GFX_MATRIX_PROJECTION, (int)((igViewerParameters *)self->_parameters)->_projectionMatrix);
    ((igVisualContextDispatchView *)self->_visualContext)->SetViewMatrixHint(((igViewerParameters *)self->_parameters)->_viewMatrix);
    previous = (igObject *)self->_lightOutput;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if (((unsigned long long)((long long)(int)previous->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->_lightOutput = 0;
    previous = (igObject *)self->_sceneOutput;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if (((unsigned long long)((long long)(int)previous->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->_sceneOutput = 0;
    if (((igViewerParameters *)self->_parameters)->_scene != 0) {
        if (self->_lightingState != 0) {
            ((igCommonTraversalDispatchView *)self->_lightTraversal)->reset();
            ((igCommonTraversalDispatchView *)self->_lightTraversal)->setTime(((igViewerParameters *)self->_parameters)->_drawTime);
            ((igCommonTraversalDispatchView *)self->_lightTraversal)->apply((igObject *)self->_attrSet);
            output = ((igCommonTraversalDispatchView *)self->_lightTraversal)->getOutput();
            if (output != 0) {
                output->_refCount = output->_refCount + 1;
            }
            previous = (igObject *)self->_lightOutput;
            if (previous != 0) {
                previous->_refCount = previous->_refCount - 1;
                if (((unsigned long long)((long long)(int)previous->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(previous);
                }
            }
            self->_lightOutput = (int)output;
        }
        ((igCommonTraversalDispatchView *)self->_sceneTraversal)->reset();
        ((igCommonTraversalDispatchView *)self->_sceneTraversal)->setTime(((igViewerParameters *)self->_parameters)->_drawTime);
        igViewerRenderer_PushLightStates(self);
        ((igCommonTraversalDispatchView *)self->_sceneTraversal)->apply((igObject *)self->_attrSet);
        igViewerRenderer_PopLightStates(self);
        output = ((igCommonTraversalDispatchView *)self->_sceneTraversal)->getOutput();
        if (output != 0) {
            output->_refCount = output->_refCount + 1;
        }
        previous = (igObject *)self->_sceneOutput;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if (((unsigned long long)((long long)(int)previous->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(previous);
            }
        }
        self->_sceneOutput = (int)output;
    }
}

void igViewerRenderer_InitializeDrawing(igViewerRenderer *self) {
    igObject *extension = ((igVisualContextDispatchView *)self->_visualContext)->GetExtension((const char *)text_igDisableExt);
    if (extension != 0) {
        extension->_refCount = extension->_refCount + 1;
    }
    igObject *previous = (igObject *)self->_disableExtension;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if (((unsigned long long)((long long)(int)previous->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->_disableExtension = (int)extension;
    ((igCommonTraversalDispatchView *)self->_lightTraversal)->setVisualContext((igObject *)self->_visualContext);
    ((igCommonTraversalDispatchView *)self->_sceneTraversal)->setVisualContext((igObject *)self->_visualContext);
    igViewerRenderer_UpdateProjection(self);
    igViewerRenderer_UpdateViewMatrix(self);
    igViewerRenderer_UpdateSorting(self);
    igViewerRenderer_UpdateLighting(self);
    igViewerRenderer_UpdateRenderStates(self);
    igViewerRenderer_UpdateScene(self);
}

/* The disable-feature extension's slot 29 switches a render feature on or off.
 * ABI view only: never instantiated. */
class igDisableExtensionDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void setDisabled(int feature, bool disabled);
};
/* A render output's slot 22 renders it into a visual context.
 * ABI view only: never instantiated. */
class igRenderOutputDispatchView : public igObjectDispatchView {
public:
    virtual void d21();
    virtual void render(int visualContext);
};

static inline bool BitMask_IsSet(igBitMask *mask, unsigned int bit) {
    return (((unsigned int *)mask->_data)[bit >> 5] & (1 << (bit & 0x1F))) != 0;
}

/* Draws the light and scene outputs with the projection matrix of the parameters, switching off
 * for the duration of the draw the features the parameters' disable mask selects. */
void Gap__Viewer__igViewerRenderer__Render(igViewerRenderer *self) {
    igViewerParameters *params = (igViewerParameters *)self->_parameters;
    int count = ((igBitMask *)params->_disables)->_bitCount;
    int i;
    int j;
    ((igVisualContextDispatchView *)self->_visualContext)->setMatrix(IG_GFX_MATRIX_PROJECTION, (int)&params->_projectionMatrix[0]);
    if (self->_disableExtension != 0) {
        for (i = 0; i < count; i++) {
            if (g_viewerDisableFeatures[i].supported
                && BitMask_IsSet((igBitMask *)((igViewerParameters *)self->_parameters)->_disables, i)) {
                ((igDisableExtensionDispatchView *)self->_disableExtension)->setDisabled(g_viewerDisableFeatures[i].feature, true);
            }
        }
    }
    if (self->_lightOutput != 0) {
        ((igRenderOutputDispatchView *)self->_lightOutput)->render(self->_visualContext);
    }
    if (self->_sceneOutput != 0) {
        ((igRenderOutputDispatchView *)self->_sceneOutput)->render(self->_visualContext);
    }
    if (self->_disableExtension != 0) {
        for (j = 0; j < count; j++) {
            if (g_viewerDisableFeatures[j].supported
                && BitMask_IsSet((igBitMask *)((igViewerParameters *)self->_parameters)->_disables, j)) {
                ((igDisableExtensionDispatchView *)self->_disableExtension)->setDisabled(g_viewerDisableFeatures[j].feature, false);
            }
        }
    }
}

void igViewerRenderer_ApplyOptions(igViewerRenderer *renderer) {
    ModelChange useSceneLightsChanged;
    ModelChange useHeadLightChanged;
    ModelChange useHeadLightSpecularChanged;
    ModelChange alphaTestChanged;
    ModelChange alphaTestForceChanged;
    ModelChange backFaceCullingChanged;
    ModelChange backFaceCullingForceChanged;
    ModelChange wireframeChanged;
    ModelChange wireframeForceChanged;
    ModelChange flatShadingChanged;
    ModelChange flatShadingForceChanged;
    ModelChange sortTextureChanged;
    ModelChange sortTransparentChanged;
    ModelChange sortTransparentDistanceChanged;
    ModelChange transparencyModeChanged;
    SharedViewerOptions *f;
    SharedViewerOptions *options;
    SharedViewerOptions *g;
    unsigned char hasSceneLights;
    int useHeadLight;
    int headLight;
    if (g_sharedViewerOptions == 0) {
        f = (SharedViewerOptions *)operator new(sizeof(SharedViewerOptions));
        if (f != 0) f = igViewerDefaults_Construct(f);
        g_sharedViewerOptions = f;
    }
    g_sharedViewerOptions->useCount = g_sharedViewerOptions->useCount + 1;
    options = g_sharedViewerOptions;
    hasSceneLights = ((igObjectList *)renderer->_lightList)->_count > 0;
    if (options->autoSceneLights != 0) {
        ((igViewerParameters *)renderer->_parameters)->_useSceneLights = hasSceneLights;
    } else {
        ((igViewerParameters *)renderer->_parameters)->_useSceneLights = options->useSceneLights;
    }
    useSceneLightsChanged.source = 0;
    useSceneLightsChanged.type = 2;
    useSceneLightsChanged.field = g_igViewerParameters_useSceneLightsMetaField;
    igModel_NotifyViews((igModel *)renderer->_parameters, &useSceneLightsChanged);
    if (options->autoHeadLight != 0) {
        /* matching construct: respell sweep under C++ — the C int-valued !s1 */
        useHeadLight = (bool)hasSceneLights ^ 1;
    } else {
        useHeadLight = options->useHeadLight;
    }
    headLight = useHeadLight & 0xFF;
    ((igViewerParameters *)renderer->_parameters)->_useHeadLight = (headLight & ((!options->useHeadLightSpecular) & 0xFF)) != 0;
    useHeadLightChanged.source = 0;
    useHeadLightChanged.type = 2;
    useHeadLightChanged.field = g_igViewerParameters_useHeadLightMetaField;
    igModel_NotifyViews((igModel *)renderer->_parameters, &useHeadLightChanged);
    ((igViewerParameters *)renderer->_parameters)->_useHeadLightSpecular = (headLight & options->useHeadLightSpecular) != 0;
    useHeadLightSpecularChanged.source = 0;
    useHeadLightSpecularChanged.type = 2;
    useHeadLightSpecularChanged.field = g_igViewerParameters_useHeadLightSpecularMetaField;
    igModel_NotifyViews((igModel *)renderer->_parameters, &useHeadLightSpecularChanged);
    ((igViewerParameters *)renderer->_parameters)->_alphaTest = options->alphaTest;
    alphaTestChanged.source = 0;
    alphaTestChanged.type = 2;
    alphaTestChanged.field = g_igViewerParameters_alphaTestMetaField;
    igModel_NotifyViews((igModel *)renderer->_parameters, &alphaTestChanged);
    ((igViewerParameters *)renderer->_parameters)->_alphaTestForce = options->forceAlphaTest;
    alphaTestForceChanged.source = 0;
    alphaTestForceChanged.type = 2;
    alphaTestForceChanged.field = g_igViewerParameters_alphaTestForceMetaField;
    igModel_NotifyViews((igModel *)renderer->_parameters, &alphaTestForceChanged);
    ((igViewerParameters *)renderer->_parameters)->_backFaceCulling = options->backFaceCullingMode;
    backFaceCullingChanged.source = 0;
    backFaceCullingChanged.type = 2;
    backFaceCullingChanged.field = g_igViewerParameters_backFaceCullingMetaField;
    igModel_NotifyViews((igModel *)renderer->_parameters, &backFaceCullingChanged);
    ((igViewerParameters *)renderer->_parameters)->_backFaceCullingForce = options->forceBackFaceCulling;
    backFaceCullingForceChanged.source = 0;
    backFaceCullingForceChanged.type = 2;
    backFaceCullingForceChanged.field = g_igViewerParameters_backFaceCullingForceMetaField;
    igModel_NotifyViews((igModel *)renderer->_parameters, &backFaceCullingForceChanged);
    ((igViewerParameters *)renderer->_parameters)->_wireframe = options->wireframeMode;
    wireframeChanged.source = 0;
    wireframeChanged.type = 2;
    wireframeChanged.field = g_igViewerParameters_wireframeMetaField;
    igModel_NotifyViews((igModel *)renderer->_parameters, &wireframeChanged);
    ((igViewerParameters *)renderer->_parameters)->_wireframeForce = options->forceWireframe;
    wireframeForceChanged.source = 0;
    wireframeForceChanged.type = 2;
    wireframeForceChanged.field = g_igViewerParameters_wireframeForceMetaField;
    igModel_NotifyViews((igModel *)renderer->_parameters, &wireframeForceChanged);
    ((igViewerParameters *)renderer->_parameters)->_flatShading = 0;
    flatShadingChanged.source = 0;
    flatShadingChanged.type = 2;
    flatShadingChanged.field = g_igViewerParameters_flatShadingMetaField;
    igModel_NotifyViews((igModel *)renderer->_parameters, &flatShadingChanged);
    ((igViewerParameters *)renderer->_parameters)->_flatShadingForce = 0;
    flatShadingForceChanged.source = 0;
    flatShadingForceChanged.type = 2;
    flatShadingForceChanged.field = g_igViewerParameters_flatShadingForceMetaField;
    igModel_NotifyViews((igModel *)renderer->_parameters, &flatShadingForceChanged);
    ((igViewerParameters *)renderer->_parameters)->_sortTexture = 0;
    sortTextureChanged.source = 0;
    sortTextureChanged.type = 2;
    sortTextureChanged.field = g_igViewerParameters_sortTextureMetaField;
    igModel_NotifyViews((igModel *)renderer->_parameters, &sortTextureChanged);
    ((igViewerParameters *)renderer->_parameters)->_sortTransparent = 1;
    sortTransparentChanged.source = 0;
    sortTransparentChanged.type = 2;
    sortTransparentChanged.field = g_igViewerParameters_sortTransparentMetaField;
    igModel_NotifyViews((igModel *)renderer->_parameters, &sortTransparentChanged);
    ((igViewerParameters *)renderer->_parameters)->_sortTransparentDistance = 0;
    sortTransparentDistanceChanged.source = 0;
    sortTransparentDistanceChanged.type = 2;
    sortTransparentDistanceChanged.field = g_igViewerParameters_sortTransparentDistanceMetaField;
    igModel_NotifyViews((igModel *)renderer->_parameters, &sortTransparentDistanceChanged);
    ((igViewerParameters *)renderer->_parameters)->_transparencyMode = 0;
    transparencyModeChanged.source = 0;
    transparencyModeChanged.type = 2;
    transparencyModeChanged.field = g_igViewerParameters_transparencyModeMetaField;
    igModel_NotifyViews((igModel *)renderer->_parameters, &transparencyModeChanged);
    if (g_sharedViewerOptions != 0) {
        if (--g_sharedViewerOptions->useCount <= 0) {
            f = g_sharedViewerOptions;
            if (f != 0) {
                if (&f->internedString) releaseString((const char *)f->internedString);
                if (f != 0) releaseString(f->extraCommandLine);
                operator delete(f);
            }
            g_sharedViewerOptions = 0;
        }
    }
}

void igViewerRenderer_resetFields(igViewerRenderer *self) {
    float white[4];
    float direction[3];
    SharedViewerOptions *options;
    igObject *previous;
    igSmartPointer<igObject> color(createColorAttr());
    white[0] = 1.0f; white[1] = 1.0f; white[2] = 1.0f; white[3] = 1.0f;
    ((igColorAttrDispatchView *)color.p)->SetColor(white);
    if (g_sharedViewerOptions == 0) {
        SharedViewerOptions *f = (SharedViewerOptions *)operator new(sizeof(SharedViewerOptions));
        if (f != 0) f = igViewerDefaults_Construct(f);
        g_sharedViewerOptions = f;
    }
    g_sharedViewerOptions->useCount = g_sharedViewerOptions->useCount + 1;
    options = g_sharedViewerOptions;
    igSmartPointer<igObject> alphaFunction(createAlphaFunctionAttr());
    ((igAlphaFunctionAttrDispatchView *)alphaFunction.p)->SetAlphaFunc(IG_GFX_ALPHA_FUNCTION_GREATER);
    ((igAlphaFunctionAttrDispatchView *)alphaFunction.p)->SetRefValue(options->alphaTestReference);
    ((igLightAttrDispatchView *)self->_headlightAttr)->setDiffuse(options->headLightDiffuse);
    ((igLightAttrDispatchView *)self->_headlightAttr)->setSpecular((const float *)&g_vec4Zero);
    ((igLightAttrDispatchView *)self->_headlightAttr)->setAmbient(options->headLightAmbient);
    direction[0] = -g_vec3ZAxis.x;
    direction[1] = -g_vec3ZAxis.y;
    direction[2] = -g_vec3ZAxis.z;
    ((igLightAttrDispatchView *)self->_headlightAttr)->setDirection(direction);
    {
        igLightAttr *headlight = (igLightAttr *)self->_headlightAttr;
        headlight->_lightType = 0;
        headlight->_changed = 1;
    }
    {
        igObject *headlight = (igObject *)self->_headlightAttr;
        igLightStateAttr *headlightState = (igLightStateAttr *)self->_headlightStateAttr;
        if (headlight != 0) {
            headlight->_refCount = headlight->_refCount + 1;
        }
        previous = (igObject *)headlightState->_light;
        if (previous) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7FFFFF) == 0) igObject_Destroy(previous);
        }
        headlightState->_light = (int)headlight;
    }
    if (g_sharedViewerOptions != 0) {
        if (--g_sharedViewerOptions->useCount <= 0) {
            SharedViewerOptions *released = g_sharedViewerOptions;
            if (released != 0) {
                if (&released->internedString) releaseString((const char *)released->internedString);
                if (released != 0) releaseString(released->extraCommandLine);
                operator delete(released);
            }
            g_sharedViewerOptions = 0;
        }
    }
    igViewerRenderer_UpdateAttr(self, color.p);
    igViewerRenderer_UpdateAttr(self, alphaFunction.p);
    igViewerRenderer_UpdateAttr(self, (igObject *)self->_backFaceCullingAttr);
    igViewerRenderer_UpdateAttr(self, (igObject *)self->_alphaTestAttr);
    igViewerRenderer_UpdateAttr(self, (igObject *)self->_shadeModelAttr);
    igViewerRenderer_UpdateAttr(self, (igObject *)self->_polygonModeAttr);
    igViewerRenderer_UpdateAttr(self, (igObject *)self->_lightingAttr);
    igGroup_AppendChild((igGroup *)self->_attrSet, (igNode *)self->_headlightTransform);
    igGroup_AppendChild((igGroup *)self->_headlightTransform, (igNode *)self->_headlightSet);
    ObjectList_AppendRetained((igObjectList *)((igLightSet *)self->_headlightSet)->_lights, (igObject *)self->_headlightAttr);
    igGroup_AppendChild((igGroup *)self->_attrSet, (igNode *)self->_attrSetOverride);
    ((igTraversal *)self->_lightTraversal)->_nodeSelectProcEnabled = 1;
    ((igTraversal *)self->_lightTraversal)->_nodeSelectProc = (int)&igViewerRenderer_ObjectsTraverseNodeSelect;
    ((igTraversal *)self->_lightTraversal)->_userTimeState = 1;
    igSmartPointer<igObject> sceneTraversal(createFrustCullTraversal());
    ((igTraversal *)sceneTraversal.p)->_userTimeState = 1;
    igFrustCullTraversal_SetOuterFrustCullScale((igFrustCullTraversal *)sceneTraversal.p, 1.1f);
    previous = sceneTraversal.p;
    if (previous) previous->_refCount = previous->_refCount + 1;
    {
        igObject *old = (igObject *)self->_sceneTraversal;
        if (old) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
    }
    self->_sceneTraversal = (int)previous;
}

void igViewerRenderer_ViewportResized(igViewerRenderer *self) {
    igFrustCullTraversal *traversal;

    traversal = (igFrustCullTraversal *)self->_sceneTraversal;
    FUN_001b0000((igAttrStackManager *)traversal->_attrStack, g_igViewportAttr_metaObject,
                 (igAttrDefaultManager *)traversal->_defaultManager, (igVisualContextCapabilityManager *)traversal->_capabilityManager);
}

void igViewerRenderer_UpdateProjection(igViewerRenderer *self) {
    ModelChange projectionChanged;
    igViewerParameters *params;
    params = (igViewerParameters *)self->_parameters;
    igCommonTraversal_SetPerspective((void *)self->_sceneTraversal, params->_hfov, -1.0f, params->_ratio, params->_nearPlane, params->_farPlane);
    igMatrix44f_Copy(((igViewerParameters *)self->_parameters)->_projectionMatrix, ((igFrustCullTraversal *)self->_sceneTraversal)->_projMat);
    projectionChanged.type = 2;
    projectionChanged.source = 0;
    projectionChanged.field = g_igViewerParameters_projectionMatrixMetaField;
    igModel_NotifyViews((igModel *)self->_parameters, &projectionChanged);
}

void igViewerRenderer_UpdateViewMatrix(igViewerRenderer *self) {
    float viewMatrix[16];

    igMatrix44f_Copy(viewMatrix, ((igViewerParameters *)self->_parameters)->_viewMatrix);
    igCommonTraversal_SetViewMatrix(self->_sceneTraversal, (int *)viewMatrix);
    igCommonTraversal_SetViewMatrix(self->_lightTraversal, (int *)viewMatrix);
    ((igTransformDispatchView *)self->_headlightTransform)->SetMatrix(((igFrustCullTraversal *)self->_sceneTraversal)->_viewMatInv);
}

void igViewerRenderer_UpdateSorting(igViewerRenderer *self) {
    int mode;
    igSorter *sorter;
    igViewerParameters *params;

    sorter = (igSorter *)((igFrustCullTraversal *)self->_sceneTraversal)->_sorter;
    params = (igViewerParameters *)self->_parameters;
    mode = 0;
    if (params->_sortTexture != 0) {
        mode |= 0x20;
    }
    if (params->_sortTransparent != 0) {
        mode |= 1;
    }
    if (params->_sortTransparentDistance != 0) {
        mode |= 4;
    }
    sorter->_mode = sorter->_mode & mode;
    sorter->_mode = sorter->_mode | mode;
    sorter->_transparencyDrawMode = ((igViewerParameters *)self->_parameters)->_transparencyMode;
}

void igViewerRenderer_UpdateScene(igViewerRenderer *self) {
    int i;
    int count;
    igObject *light;
    igLightStateAttr *state;
    int offset;
    igGroup *sceneRoot = (igGroup *)self->_attrSetOverride;
    igObjectList *children = (igObjectList *)sceneRoot->_childList;
    int childCount;
    if (children != 0) {
        childCount = children->_count;
    } else {
        childCount = 0;
    }
    if (childCount > 0) {
        igGroup_RemoveChildAt(sceneRoot, 0);
    }
    CLEAR((igObjectList *)self->_lightStateList)
    CLEAR((igObjectList *)self->_lightList)
    if (((igViewerParameters *)self->_parameters)->_scene != 0) {
        igGroup_AppendChild((igGroup *)self->_attrSetOverride, (igNode *)((igViewerParameters *)self->_parameters)->_scene);
        igViewerRenderer_FindLights(self, (igGroup *)((igViewerParameters *)self->_parameters)->_scene);
    }
    count = ((igObjectList *)self->_lightList)->_count;
    for (i = 0; i < count; i++) {
            {
            igSmartPointer<igObject> item(createLightState(ItemType()));
            light = ((igObject **)((igObjectList *)self->_lightList)->_data)[i];
            state = (igLightStateAttr *)item.p;
            if (light != 0) light->_refCount = light->_refCount + 1;
            release((igObject *)state->_light);
            state->_light = (int)light;
            ((igLightStateAttrDispatchView *)item.p)->SetState(0);
            ObjectList_AppendRetained((igObjectList *)self->_lightStateList, item.p);
            }
    }
    release((igObject *)self->_sceneOutput);
    self->_sceneOutput = 0;
}

void igViewerRenderer_FindLights(igViewerRenderer *self, igGroup *node) {
    int count; int i; int offset;
    if (node->_flags & 1) {
        if (igObject_IsKindOf(node, g_igGroup_metaObject) != 0) {
            count = 0;
            if (node->_childList != 0) count = ((igNodeList *)node->_childList)->_count;
            i = 0;
            if (0 < count) {
                offset = 0;
                do {
                    igViewerRenderer_FindLights(self, *(igGroup **)((char *)((igNodeList *)node->_childList)->_data + offset));
                    i += 1;
                    offset += 4;
                } while (i < count);
            }
        } else if (igObject_IsKindOf(node, g_igLightSet_metaObject) != 0) {
            count = ((igObjectList *)node->_childList)->_count;
            i = 0;
            if (0 < count) {
                offset = 0;
                do {
                    ObjectList_AppendUniqueRetained((igTDataList<igObject *> *)self->_lightList, *(igObject **)((char *)((igObjectList *)node->_childList)->_data + offset));
                    i += 1;
                    offset += 4;
                } while (i < count);
            }
        }
    }
}

void igViewerRenderer_UpdateLighting(igViewerRenderer *self) {
    bool lighting = true;
    bool lit = true;
    igViewerParameters *params = (igViewerParameters *)self->_parameters;
    if (params->_useSceneLights == 0 && params->_useHeadLight == 0) lit = false;
    if (!lit && params->_useHeadLightSpecular == 0) lighting = false;
    self->_lightingState = lighting;
    params = (igViewerParameters *)self->_parameters;
    if (params->_useHeadLight != 0 || params->_useHeadLightSpecular != 0) {
        ((igLightStateAttrDispatchView *)self->_headlightStateAttr)->SetState(1);
        if (((igViewerParameters *)self->_parameters)->_useHeadLightSpecular != 0) {
            if (g_sharedViewerOptions == 0) {
                SharedViewerOptions *f = (SharedViewerOptions *)operator new(sizeof(SharedViewerOptions));
                if (f != 0) f = igViewerDefaults_Construct(f);
                g_sharedViewerOptions = f;
            }
            g_sharedViewerOptions->useCount = g_sharedViewerOptions->useCount + 1;
            ((igLightAttrDispatchView *)self->_headlightAttr)->setSpecular(g_sharedViewerOptions->headLightSpecular);
            if (g_sharedViewerOptions != 0) {
                if (--g_sharedViewerOptions->useCount <= 0) {
                    SharedViewerOptions *released = g_sharedViewerOptions;
                    if (released != 0) {
                        if (&released->internedString) releaseString((const char *)released->internedString);
                        if (released != 0) releaseString(released->extraCommandLine);
                        operator delete(released);
                    }
                    g_sharedViewerOptions = 0;
                }
            }
        } else {
            ((igLightAttrDispatchView *)self->_headlightAttr)->setSpecular((const float *)&g_vec4Zero);
        }
    } else {
        ((igLightStateAttrDispatchView *)self->_headlightStateAttr)->SetState(0);
    }
    ((igLightingStateAttrDispatchView *)self->_lightingAttr)->SetState(self->_lightingState);
    igViewerRenderer_UpdateAttr(self, (igObject *)self->_lightingAttr);
    igViewerRenderer_SetOverride(self, (igObject *)self->_lightingAttr, ((bool)self->_lightingState) ^ 1);
}

void igViewerRenderer_UpdateRenderStates(igViewerRenderer *self) {
    ((igAlphaStateAttrDispatchView *)self->_alphaTestAttr)->SetState(((igViewerParameters *)self->_parameters)->_alphaTest);
    igViewerRenderer_UpdateAttr(self, (igObject *)self->_alphaTestAttr);
    igViewerRenderer_SetOverride(self, (igObject *)self->_alphaTestAttr, ((igViewerParameters *)self->_parameters)->_alphaTestForce);
    ((igCullFaceAttrDispatchView *)self->_backFaceCullingAttr)->SetState(((igViewerParameters *)self->_parameters)->_backFaceCulling);
    igViewerRenderer_UpdateAttr(self, (igObject *)self->_backFaceCullingAttr);
    igViewerRenderer_SetOverride(self, (igObject *)self->_backFaceCullingAttr, ((igViewerParameters *)self->_parameters)->_backFaceCullingForce);
    ((igShadeModelAttrDispatchView *)self->_shadeModelAttr)->SetMode(((igViewerParameters *)self->_parameters)->_flatShading ? IG_GFX_SHADING_MODE_FACET : IG_GFX_SHADING_MODE_SMOOTH);
    igViewerRenderer_UpdateAttr(self, (igObject *)self->_shadeModelAttr);
    igViewerRenderer_SetOverride(self, (igObject *)self->_shadeModelAttr, ((igViewerParameters *)self->_parameters)->_flatShadingForce);
    ((igPolygonModeAttrDispatchView *)self->_polygonModeAttr)->SetMode(((igViewerParameters *)self->_parameters)->_wireframe ? IG_GFX_RENDER_MODE_LINES : IG_GFX_RENDER_MODE_FILL);
    igViewerRenderer_UpdateAttr(self, (igObject *)self->_polygonModeAttr);
    igViewerRenderer_SetOverride(self, (igObject *)self->_polygonModeAttr, ((igViewerParameters *)self->_parameters)->_wireframeForce);
}

/* The attribute in `attrSet` of the same class as `attr`. */
int igViewerRenderer_FindAttrFromType(igObjectDispatchView *attr, igAttrSet *attrSet) {
    int field = asObjectRefField((int)igMetaObject_FindFieldByName(g_igAttr_metaObject, (const char *)text_meta));
    return igProperty_FindByPointer((void *)attrSet->_attributes, (void *)field, (int)attr->GetMeta());
}

/* Replaces the attribute of `attr`'s class in `attrSet` by the shared pool's copy of `attr`. */
extern "C" int igViewerRenderer_UpdateSharedAttr(igObject *attr, igAttrSet *attrSet) {
    int found = igViewerRenderer_FindAttrFromType((igObjectDispatchView *)attr, attrSet);
    if (found != 0) {
        removeFromList(attrSet->_attributes, found);
        igSmartPointer<igObject> shared = igAttrPool_GetSharedAttr(igAttrPool_GetStaticAttrPool(), igSmartPointer<igObject>(attr, kRetainReference));
        ObjectList_AppendRetained((igObjectList *)attrSet->_attributes, shared.get());
        return 1;
    }
    return 0;
}

/* Moves the attribute of `attr`'s class from `from` to `to`. */
void igViewerRenderer_TransferAttrFromType(igAttrSet *from, igAttrSet *to, igObject *attr) {
    int found;

    found = igViewerRenderer_FindAttrFromType((igObjectDispatchView *)attr, from);
    if (found != 0) {
        ObjectList_RemoveFirstRetained((igTDataList<igObject *> *)from->_attributes, (igObject *)found, 0);
        ObjectList_AppendRetained((igObjectList *)to->_attributes, (igObject *)found);
    }
}

void igViewerRenderer_UpdateAttr(igViewerRenderer *self, igObject *attr) {
    if ((attr != 0) && !(igViewerRenderer_UpdateSharedAttr(attr, (igAttrSet *)self->_attrSetOverride) & 0xFF) && !(igViewerRenderer_UpdateSharedAttr(attr, (igAttrSet *)self->_attrSet) & 0xFF)) {
        igSmartPointer<igObject> shared = igAttrPool_GetSharedAttr(igAttrPool_GetStaticAttrPool(), igSmartPointer<igObject>(attr, kRetainReference));
        ObjectList_AppendRetained((igObjectList *)((igAttrSet *)self->_attrSet)->_attributes, shared.get());
    }
}

/* Moves `attr`'s class of attribute into the override set when `override` is set, back otherwise. */
void igViewerRenderer_SetOverride(igViewerRenderer *self, igObject *attr, int override) {
    if (override != 0) {
        igViewerRenderer_TransferAttrFromType((igAttrSet *)self->_attrSet, (igAttrSet *)self->_attrSetOverride, attr);
        return;
    }
    igViewerRenderer_TransferAttrFromType((igAttrSet *)self->_attrSetOverride, (igAttrSet *)self->_attrSet, attr);
}

int igViewerRenderer_GetMeta(void) {
    return (int)g_igViewerRenderer_metaObject;
}

void igViewerRenderer_ReleaseDrawing(void) {

}

}
