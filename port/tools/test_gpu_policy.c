#include "dw4/gpupolicy.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
int main(void)
{
    assert(!dw4_gpu_policy_required());
    assert(dw4_gpu_policy_accept("llvmpipe")); /* Explicit reference mode. */
    assert(!dw4_gpu_policy_begin(1));
    assert(dw4_gpu_policy_accept("AMD Radeon Graphics"));
    assert(dw4_gpu_policy_accept("AMD Custom GPU 0405 (radeonsi, van_gogh)"));
    assert(dw4_gpu_policy_accept("NV124"));
    assert(dw4_gpu_policy_accept("Mesa Intel(R) UHD Graphics"));
    assert(dw4_gpu_policy_accept("NVIDIA GeForce RTX"));
    assert(!dw4_gpu_policy_hardware("ANGLE (Radeon, SwiftShader software renderer)"));
    assert(!dw4_gpu_policy_hardware("LLVMPIPE (LLVM, 256 bits)"));
    assert(!dw4_gpu_policy_hardware("Intel OpenSWR"));
    assert(!dw4_gpu_policy_hardware("unknown renderer"));
    assert(!dw4_gpu_policy_accept("llvmpipe"));
    assert(strstr(dw4_gpu_policy_error(),"llvmpipe"));
    char original[384];snprintf(original,sizeof original,"%s",dw4_gpu_policy_error());
    dw4_gpu_policy_fail("later error");assert(!strcmp(original,dw4_gpu_policy_error()));
    dw4_gpu_policy_cpu(DW4_CPU_UI);dw4_gpu_policy_cpu(DW4_CPU_UI);
    assert(dw4_gpu_policy_cpu_count(DW4_CPU_UI)==2);
    assert(dw4_gpu_policy_begin(0));
    assert(!dw4_gpu_policy_error()[0] && !dw4_gpu_policy_cpu_count(DW4_CPU_UI));
    dw4_gpu_policy_fail("diagnostic fallback");assert(!dw4_gpu_policy_error()[0]);
    assert(dw4_gpu_policy_accept("softpipe"));
    puts("GPU policy: hardware families, software/unknown rejection, first error and reference isolation pass");
}
