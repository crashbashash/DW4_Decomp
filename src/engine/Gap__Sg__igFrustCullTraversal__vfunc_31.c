/* 0x001c4620 — igFrustCullTraversal slot 31: per-run reset.  Runs the shared
 * igCommonTraversal reset (src/unmatched/Gap__Sg__igCommonTraversal__vfunc_31.cpp,
 * which clears the traversal's flags and work lists), then drops the current
 * model-view and projection matrix references so the next run starts without
 * one. */
#include "dw4/reflected.h"
int Gap__Sg__igCommonTraversal__vfunc_31();

void Gap__Sg__igFrustCullTraversal__vfunc_31(igFrustCullTraversal *self) {
    Gap__Sg__igCommonTraversal__vfunc_31();
    self->_curMVMat = 0;
    self->_curProjectionMat = 0;
}
