#ifndef DW4_IGBOUNDINGBOXESMAKER_H
#define DW4_IGBOUNDINGBOXESMAKER_H

struct igAABox;
struct igBoundingBoxesMaker;
struct igMemoryPoolView;
struct igNode;

#ifdef __cplusplus
extern "C" {
#endif

struct igBoundingBoxesMaker *FUN_001a4830(struct igMemoryPoolView *pool);
/* The bounding box of `node`, in a new box that already holds one reference. */
struct igAABox *FUN_001b2ed0(struct igBoundingBoxesMaker *maker, struct igNode *node);

#ifdef __cplusplus
}
#endif

#endif
