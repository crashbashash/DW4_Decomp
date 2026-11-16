/* libgraph.h - Sony libgraph: the GS reset and the vblank-synchronised field query (Sony libgraph.h). */
#ifndef DW4_SONY_LIBGRAPH_H
#define DW4_SONY_LIBGRAPH_H

/* the display mode sceGsResetGraph set, and whether a vblank callback is installed */
typedef struct {
    short inter;
    short omode;
    short ffmode;
    unsigned short version;
    int vsync_set;
    int vsync_id;
} GsGParam;

void sceGsResetGraph(short mode, short inter, short omode, short ffmode);
GsGParam *sceGsGetGParam(void);
void sceGsResetPath(void);
int sceGsSyncV(void);

#endif
