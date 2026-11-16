#ifndef DW4_BEBASEINFORAMTIMER_H
#define DW4_BEBASEINFORAMTIMER_H

struct beBaseInfoRamTimer;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beBaseInfoRamTimer *beBaseInfoRamTimer_Create(int allocator);

extern struct igMetaObject *g_beBaseInfoRamTimer_metaObject;

#ifdef __cplusplus
}
#endif

#endif
