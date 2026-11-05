#include "dw4/gpupolicy.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
static int required;
static char error[384];
static uint64_t cpu[DW4_CPU_KIND_COUNT];
static int contains(const char *s,const char *word)
{
    if(!s)return 0;
    for(;*s;s++){
        size_t i=0;while(word[i] && s[i] && tolower((unsigned char)s[i])==tolower((unsigned char)word[i]))i++;
        if(!word[i])return 1;
    }return 0;
}
int dw4_gpu_policy_begin(int hardware_required)
{int previous=required;required=!!hardware_required;error[0]=0;memset(cpu,0,sizeof cpu);return previous;}
int dw4_gpu_policy_required(void){return required;}
int dw4_gpu_policy_hardware(const char *renderer)
{
    static const char *software[]={"llvmpipe","softpipe","swrast","swiftshader","lavapipe",
        "openswr","software rasterizer","software renderer","gdi generic","basic render driver"};
    for(unsigned i=0;i<sizeof software/sizeof *software;i++)if(contains(renderer,software[i]))return 0;
    /* Supported desktop families. Unknown/virtual renderers need an explicit
     * backend validation rather than being assumed to be hardware. */
    if(renderer && strlen(renderer)>=3 && toupper((unsigned char)renderer[0])=='N' &&
       toupper((unsigned char)renderer[1])=='V' && isxdigit((unsigned char)renderer[2]))return 1;
    return contains(renderer,"amd") || contains(renderer,"radeon") || contains(renderer,"nvidia") || contains(renderer,"intel");
}
int dw4_gpu_policy_accept(const char *renderer)
{
    if(!required || dw4_gpu_policy_hardware(renderer))return 1;
    if(!error[0])snprintf(error,sizeof error,"hardware GPU required; unsupported or software renderer: %s",renderer?renderer:"unavailable");
    return 0;
}
void dw4_gpu_policy_fail(const char *operation)
{if(required && !error[0])snprintf(error,sizeof error,"GPU operation failed: %s",operation?operation:"unknown");}
const char *dw4_gpu_policy_error(void){return error;}
int dw4_gpu_policy_cpu(unsigned kind)
{
    if(!required)return 0;
    if(kind<DW4_CPU_KIND_COUNT)__sync_fetch_and_add(cpu+kind,1);
    static const char *name[]={"UI","layer","mesh","fill","composite"};
    if(!error[0])snprintf(error,sizeof error,"CPU %s rendering forbidden in normal hardware mode",
        kind<DW4_CPU_KIND_COUNT?name[kind]:"unknown");
    return -1;
}
uint64_t dw4_gpu_policy_cpu_count(unsigned kind)
{return kind<DW4_CPU_KIND_COUNT?cpu[kind]:0;}
