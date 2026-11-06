/* host.c -- the host backend of the platform seam (porting P2.1).
 *
 * P2.1's deliverable is the *layer*, not the implementations: the seam is inventoried
 * (`include/dw4/platform.h`, from the recovered `igPsx2*` -> generic-interface mapping) and the
 * interfaces live here, one layer under the engine.  The worked example is already real:
 * `src/igfile.c` **is** the host `igFile` (P2.3's first increment -- a plain file, an AFS entry, a
 * manifest name or a stage reference, all mapped), which is why the table marks `igPsx2File` as
 * `DW4_IF_HOST`.  Every other interface is a stub that says so, so the engine's calls fail loudly
 * instead of silently reading nothing.
 */
#include <stdio.h>
#include <string.h>
#include "dw4/platform.h"

/* One row per igPsx2 class that sits under a generic interface. The field count is the generic
 * interface's serialised field count; it is what a host implementation has to fill in. */
const dw4_iface dw4_ifaces[] = {
    { "igPsx2AudioContext", "igAudioContext", 1, DW4_IF_STUB },
    { "igPsx2AudioSourceList", "igDataList", 3, DW4_IF_STUB },
    { "igPsx2BlendEquationExt", "igBlendEquationExt", 1, DW4_IF_STUB },
    { "igPsx2CallStackTracer", "igCallStackTracer", 0, DW4_IF_STUB },
    { "igPsx2Clut", "igClut", 7, DW4_IF_STUB },
    { "igPsx2Controller", "igController", 2, DW4_IF_INPUT },
    { "igPsx2ControllerManager", "igControllerManager", 1, DW4_IF_INPUT },
    { "igPsx2DecalExt", "igDecalExt", 1, DW4_IF_STUB },
    { "igPsx2DisableExt", "igDisableExt", 0, DW4_IF_STUB },
    { "igPsx2EnvironmentMapShader", "igEnvironmentMapShader2", 21, DW4_IF_STUB },
    { "igPsx2File", "igFile", 8, DW4_IF_HOST },
    { "igPsx2Folder", "igFolder", 1, DW4_IF_STUB },
    { "igPsx2Image", "igMemoryImage", 0, DW4_IF_STUB },
    { "igPsx2ImageConvert", "igImageConvert", 0, DW4_IF_STUB },
    { "igPsx2IndexArray", "igIndexArray", 5, DW4_IF_STUB },
    { "igPsx2LongList", "igDataList", 3, DW4_IF_STUB },
    { "igPsx2LongTimer", "igLongTimer", 4, DW4_IF_STUB },
    { "igPsx2Media", "igMedia", 0, DW4_IF_STUB },
    { "igPsx2MultiTextureExt", "igMultiTextureExt", 0, DW4_IF_STUB },
    { "igPsx2ParticleArray", "igParticleArray", 22, DW4_IF_STUB },
    { "igPsx2PointSpriteExt", "igPointSpriteExt", 18, DW4_IF_STUB },
    { "igPsx2ScissorExt", "igScissorExt", 0, DW4_IF_STUB },
    { "igPsx2Semaphore", "igSemaphore", 0, DW4_IF_STUB },
    { "igPsx2Thread", "igThread", 10, DW4_IF_STUB },
    { "igPsx2ThreadManager", "igThreadManager", 2, DW4_IF_STUB },
    { "igPsx2UserUCodeExt", "igUserUCodeExt", 0, DW4_IF_STUB },
    { "igPsx2VertexArray1_1", "igVertexArray1_1", 6, DW4_IF_STUB },
    { "igPsx2VertexArray2", "igVertexArray2", 3, DW4_IF_STUB },
    { "igPsx2VertexStream", "igVertexStream", 6, DW4_IF_STUB },
    { "igPsx2VisualContext", "igVisualContext", 28, DW4_IF_STUB },
    { "igPsx2Window", "igWindow", 0, DW4_IF_STUB },
};

const unsigned dw4_nifaces = sizeof(dw4_ifaces) / sizeof(dw4_ifaces[0]);

/* The distinct generic interfaces in the table (igDataList carries two igPsx2* classes, so the count
 * of interfaces is smaller than the count of classes). */
unsigned dw4_platform_ifaces(void)
{
    unsigned i, j, n = 0;

    for (i = 0; i < dw4_nifaces; i++) {
        for (j = 0; j < i; j++)
            if (strcmp(dw4_ifaces[j].iface, dw4_ifaces[i].iface) == 0)
                break;
        if (j == i)
            n++;
    }
    return n;
}

unsigned dw4_platform_status(int verbose)
{
    unsigned i, stubs = 0;

    for (i = 0; i < dw4_nifaces; i++) {
        if (dw4_ifaces[i].status == DW4_IF_STUB) {
            stubs++;
            if (verbose)
                printf("  stub  %-32s (%s, %u field(s))\n", dw4_ifaces[i].iface,
                       dw4_ifaces[i].igpsx2, dw4_ifaces[i].fields);
        } else if (verbose) {
            printf("  host  %-32s (%s, %u field(s))\n", dw4_ifaces[i].iface,
                   dw4_ifaces[i].igpsx2, dw4_ifaces[i].fields);
        }
    }
    return stubs;
}
