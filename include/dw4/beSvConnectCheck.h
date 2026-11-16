#ifndef DW4_BESVCONNECTCHECK_H
#define DW4_BESVCONNECTCHECK_H

struct beSvConnectCheck;
struct beSvConnectCheckWork;
struct beSvDeliver;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beSvConnectCheck *beSvConnectCheck_Create(int allocator);
int beSvConnectCheck_FillDeliver(int *slotWords, struct beSvDeliver *deliver);
void beSvConnectCheck_Poll(struct beSvConnectCheckWork *check);
void beSvConnectCheck_PollMultitap(int check, struct beSvDeliver *deliver);

extern struct igMetaObject *g_beSvConnectCheck_metaObject;

#ifdef __cplusplus
}
#endif

#endif
