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
int p2SendRenderState(int mask);
void p2PrepareRenderState(int mask);
int p2BuildFunctionTables(void);
void p2SetupProgramVariants(void);
void p2FreeVariantTables(void);

#ifdef __cplusplus
}
#endif

#endif
