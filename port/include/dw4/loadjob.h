/* One CPU asset-preparation job. Work must not call window/GPU services.
 * Context stays caller-owned until close. Close joins unfinished work.
 * Poll returns 0 while pending and 1 once the result is safe to consume. */
#ifndef DW4_LOADJOB_H
#define DW4_LOADJOB_H
typedef struct dw4_loadjob dw4_loadjob;
typedef void *(*dw4_load_work)(void *context);
dw4_loadjob *dw4_loadjob_start(dw4_load_work work, void *context, int threaded);
/* Non-threaded jobs execute on first poll, for deterministic headless probes. */
int dw4_loadjob_poll(dw4_loadjob *, void **result);
/* Result remains caller-owned, including on early shutdown. */
void *dw4_loadjob_close(dw4_loadjob *);
#endif
