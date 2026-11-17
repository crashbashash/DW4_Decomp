#ifndef DW4_IGBASICCOLORCHANGER_H
#define DW4_IGBASICCOLORCHANGER_H

struct igBasicColorChanger;
struct igVec4f;

#ifdef __cplusplus
extern "C" {
#endif

void igBasicColorChanger_RunStaticInit(void);
void igBasicColorChanger_SetColor(struct igBasicColorChanger *changer, int highlighted, int on, int disabled, const struct igVec4f *color);

#ifdef __cplusplus
}
#endif

#endif
