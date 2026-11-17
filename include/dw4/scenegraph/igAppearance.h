#ifndef DW4_IGAPPEARANCE_H
#define DW4_IGAPPEARANCE_H

struct igAppearance;
struct igNode;

#ifdef __cplusplus
extern "C" {
#endif

int igAppearance_AttachGraph(struct igAppearance *appearance, struct igNode *graph);
int igAppearance_DetachGraph(struct igAppearance *appearance, struct igNode *graph);

#ifdef __cplusplus
}
#endif

#endif
