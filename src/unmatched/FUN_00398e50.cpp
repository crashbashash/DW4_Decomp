#include "dw4/reflected.h"

extern "C" {
int FUN_00398ef0(beModelCtrlNode2 *node, igCommonTraversal *traversal);
int FUN_00398e50(igCommonTraversal *traversal, beModelCtrlNode2 *node);
}

int FUN_00398e50(igCommonTraversal *traversal, beModelCtrlNode2 *node)
{
    return FUN_00398ef0(node, traversal);
}
