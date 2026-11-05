#define _POSIX_C_SOURCE 200809L
#include "dw4/window.h"
#include "dw4/vk_present.h"
#include "dw4/gpupolicy.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef DW4_ENABLE_VULKAN
#include <vulkan/vulkan.h>
static int force_cpu;static unsigned devices;
void __real_vkGetPhysicalDeviceProperties(VkPhysicalDevice,VkPhysicalDeviceProperties *);
void __wrap_vkGetPhysicalDeviceProperties(VkPhysicalDevice gpu,VkPhysicalDeviceProperties *p)
{__real_vkGetPhysicalDeviceProperties(gpu,p);if(force_cpu)p->deviceType=VK_PHYSICAL_DEVICE_TYPE_CPU;}
VkResult __real_vkCreateDevice(VkPhysicalDevice,const VkDeviceCreateInfo *,const VkAllocationCallbacks *,VkDevice *);
VkResult __wrap_vkCreateDevice(VkPhysicalDevice gpu,const VkDeviceCreateInfo *c,const VkAllocationCallbacks *a,VkDevice *d)
{devices++;return __real_vkCreateDevice(gpu,c,a,d);}
#endif
int main(int argc,char **argv)
{
    assert(argc==2);dw4_gpu_policy_begin(1);
    if(!strcmp(argv[1],"sdl-reject")){
        dw4_window *w=dw4_window_open(96,64,"GPU SDL rejection",0);
        assert(!w && dw4_gpu_policy_error()[0]);puts("GPU SDL: forced software renderer rejected");
    }else if(!strcmp(argv[1],"sdl")){
        dw4_window *w=dw4_window_open(96,64,"GPU SDL probe",0);assert(w);
        dw4_fb fb={0};assert(!dw4_fb_init(&fb,23,17));
        for(unsigned p=0;p<23*17;p++){fb.rgba[4*p]=p;fb.rgba[4*p+1]=p*13;fb.rgba[4*p+2]=p*31;fb.rgba[4*p+3]=255;}
        assert(!dw4_window_present(w,&fb));dw4_window_close(w);dw4_fb_free(&fb);
        assert(!dw4_gpu_policy_error()[0]);puts("GPU SDL: hardware window presents a differently sized frame");
    }else{
#ifdef DW4_ENABLE_VULKAN
        force_cpu=!strcmp(argv[1],"vk-reject");
        dw4_vk *v=dw4_vk_open(96,64,"GPU Vulkan probe",force_cpu);
        if(force_cpu){assert(!v && !devices && dw4_gpu_policy_error()[0]);puts("GPU Vulkan: CPU-only candidates rejected before device creation");}
        else{
            assert(v && devices);dw4_fb fb={0};assert(!dw4_fb_init(&fb,23,17));
            for(unsigned p=0;p<23*17;p++){fb.rgba[4*p]=p;fb.rgba[4*p+1]=p*13;fb.rgba[4*p+2]=p*31;fb.rgba[4*p+3]=255;}
            for(unsigned i=0;i<4;i++)assert(dw4_vk_present(v,&fb)>0);
            assert(!dw4_gpu_policy_error()[0]);dw4_vk_close(v);dw4_fb_free(&fb);
            puts("GPU Vulkan: hardware swapchain and GPU frame resizing pass");
        }
#else
        puts("GPU Vulkan: backend not compiled, skipped");
#endif
    }
    for(unsigned kind=0;kind<DW4_CPU_KIND_COUNT;kind++)assert(!dw4_gpu_policy_cpu_count(kind));
    dw4_gpu_policy_begin(0);
}
