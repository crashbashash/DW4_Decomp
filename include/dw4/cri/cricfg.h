/* CRI CFG: a small table of named integer settings the other CRI libraries read at start-up;
 * src/cri/cricfg.c. */
#ifndef DW4_CRI_CRICFG_H
#define DW4_CRI_CRICFG_H

#ifdef __cplusplus
extern "C" {
#endif

void CRICFG_Init(void);
void CRICFG_Finish(void);
int CRICFG_Write(const char *name, int value);
int CRICFG_Read(const char *name, int *value);

#ifdef __cplusplus
}
#endif

#endif
