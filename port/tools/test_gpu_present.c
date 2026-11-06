#define _POSIX_C_SOURCE 200809L
#include "dw4/window.h"
#include "dw4/vk_present.h"
#include "dw4/gpupolicy.h"
#include <assert.h>
#include <signal.h>
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
#define HOLD_W 256
#define HOLD_H 224
static volatile sig_atomic_t hold_stop;
static void hold_signal(int sig){(void)sig;hold_stop=1;}
/* Each channel differs and sweeps the mid-tones, so a swapped channel order or a gamma shift changes the picture. */
static void hold_frame(dw4_fb *fb)
{
    for(int y=0;y<HOLD_H;y++)for(int x=0;x<HOLD_W;x++){
        unsigned char *p=fb->rgba+4*(y*HOLD_W+x);
        p[0]=x*7+y;p[1]=x+y*5;p[2]=x*3+y*11;p[3]=255;
    }
}
/* Shows the frame until SIGTERM. The GPU policy stays off so a software renderer can present. Exit 2: backend unavailable. */
static int hold(const char *backend)
{
    int vulkan=!strcmp(backend,"vk");dw4_window *w=NULL;dw4_vk *v=NULL;dw4_fb fb={0};
    if(vulkan?!(v=dw4_vk_open(HOLD_W,HOLD_H,"dw4",0)):!(w=dw4_window_open(HOLD_W,HOLD_H,"dw4",0)))return 2;
    assert(!dw4_fb_init(&fb,HOLD_W,HOLD_H));hold_frame(&fb);
    signal(SIGTERM,hold_signal);
    for(int shown=0;!hold_stop;){
        if(vulkan?dw4_vk_present(v,&fb)<=0:dw4_window_present(w,&fb)!=0)return 1;
        if(vulkan)dw4_vk_pump(v);else dw4_window_pump(w,NULL);
        if(!shown++){puts("presenting");fflush(stdout);}
        nanosleep(&(struct timespec){.tv_nsec=16000000},NULL);
    }
    if(vulkan)dw4_vk_close(v);else dw4_window_close(w);
    dw4_fb_free(&fb);return 0;
}
int main(int argc,char **argv)
{
    assert(argc==2);
    if(!strncmp(argv[1],"hold-",5))return hold(argv[1]+5);
    dw4_gpu_policy_begin(1);
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
