#ifndef DW4_P2VU0_H
#define DW4_P2VU0_H

struct p2Vu0Lock;

#ifdef __cplusplus
extern "C" {
#endif

extern struct p2Vu0Lock p2Vu0LockState;
void p2LockVu0(const char *owner);
void p2UnlockVu0(void);
int p2GetVu0Program(void);

#ifdef __cplusplus
}
#endif

#endif
