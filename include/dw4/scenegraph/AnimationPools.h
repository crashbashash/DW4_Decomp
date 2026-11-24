#ifndef DW4_ANIMATIONPOOLS_H
#define DW4_ANIMATIONPOOLS_H
#include "dw4/core/igSmartPointer.h"

/* The scene graph's shared animation pools: the combiners' bone-info pool, the animation-state pool
 * and the Enbaya decompression-context pool. */
extern "C" {
}

extern igSmartPointer<igAnimationCombinerBoneInfoPool> g_igAnimationCombinerBoneInfoPool_instance;
extern igSmartPointer<igAnimationStatePool> g_igAnimationStatePool_instance;
extern igSmartPointer<igEnbayaContextPool> g_igEnbayaContextPool_instance;

#endif
