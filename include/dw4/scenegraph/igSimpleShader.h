#ifndef DW4_IGSIMPLESHADER_H
#define DW4_IGSIMPLESHADER_H
#include "dw4/core/igObjectDispatchView.h"

/* The kit's igSimpleShader (alchemy-kit_202309 igSg/igSimpleShader.h, an igShader2 and so an igGroup) has no
 * registered class in DW4's image, yet the shader factories and processors configure and run their target shaders
 * through it: it is seen as a dispatch view with its fields (_shaderData, _processor, _passMask,
 * _dataPumpManager, after igGroup's) and the virtual slot the factories call, 29, which empties the shader's
 * children. A struct, as reflected.h forward-declares it.
 * ABI view only: never instantiated. */
struct igSimpleShaderDispatchView : public igObjectDispatchView {
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void reset();                                                   /* slot 29 */
    char _pad8[28];
    Gap::Sg::igShaderData *_shaderData;                                     /* +36 */
    int _processor;                                                         /* +40 */
    int _passMask;                                                          /* +44 */
    int _dataPumpManager;                                                   /* +48 */
};

#endif
