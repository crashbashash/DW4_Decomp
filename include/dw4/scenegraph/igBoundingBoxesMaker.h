#ifndef DW4_IGBOUNDINGBOXESMAKER_H
#define DW4_IGBOUNDINGBOXESMAKER_H

struct igAABox;
struct igBoundingBoxesMaker;
struct igMemoryPoolView;
struct igNode;

#ifdef __cplusplus
extern "C" {
#endif

/* The bounding box of `node`, in a new box that already holds one reference. */
struct igAABox *igBoundingBoxesMaker_ComputeBox(struct igBoundingBoxesMaker *maker, struct igNode *node);

#ifdef __cplusplus
}
#endif

#endif
