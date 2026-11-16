#ifndef DW4_IGONOFFCOLORCHANGER_H
#define DW4_IGONOFFCOLORCHANGER_H

struct igBasicColorChanger;
struct igVec4f;

#ifdef __cplusplus
extern "C" {
#endif

void igOnOffColorChanger_RunStaticInit(void);
void igOnOffColorChanger_SetColor(struct igBasicColorChanger *changer, int highlighted, int on, int disabled, const struct igVec4f *color);

#ifdef __cplusplus
}
#endif

#endif
