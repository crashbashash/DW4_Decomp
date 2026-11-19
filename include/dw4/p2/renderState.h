#ifndef DW4_RENDERSTATE_H
#define DW4_RENDERSTATE_H

#ifdef __cplusplus
extern "C" {
#endif

extern int p2FunctionTableSizes[3];
extern int p2FunctionTables[72];
extern int p2LightCalcPending;
extern int p2LightingProgramBits;
extern long long p2VertexArrayMask;
/* The programs with feature bit 30: [0] runs the GS register uploads, [6] draws particles. */
extern int p2VariantsBit30[8];
/* Statistics: render state sends, and what each send uploaded. */
extern long long p2StatPassSetupsSent;
extern long long p2StatVuBufferLayoutsSent;
extern long long p2StatGsRegistersSent;
extern long long p2StatBlendMatricesSent;
extern long long p2StatVertexFormatsSent;
extern long long p2StatGifTagsSent;
extern long long p2StatLightsSent;
extern long long p2StatLightingFunctionsSent;
extern long long p2StatFunctionTablesSent;
extern long long p2StatStateSends;
int p2SendRenderState(int mask);
void p2PrepareRenderState(int mask);
/* Sets the vertex format bits and the program capability mask from the current program, the bound
 * arrays and the primitive. */
void p2BuildVertexFormat(void);
int p2BuildFunctionTables(void);
void p2SetupProgramVariants(void);
void p2FreeVariantTables(void);

#ifdef __cplusplus
}
#endif

#endif
