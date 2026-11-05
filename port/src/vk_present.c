/* dw4/vk_present.c — the Vulkan present path; see include/dw4/vk_present.h for what it is and is not.
 *
 * GPU or explicit reference frames are transported through a staging buffer.
 * Normal frame resizing uses a GPU pixel pass; channel packing is a byte transfer.
 * Swapchain copies/transitions preserve format and presentation ordering.
 */
#define _GNU_SOURCE
#include "dw4/vk_present.h"
#include "dw4/gpupolicy.h"
#include "dw4/gl_layer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DW4_ENABLE_VULKAN

#include <SDL.h>
#include <vulkan/vulkan.h>   /* SDL_vulkan.h expects the Vulkan headers to come first */
#include <SDL_vulkan.h>

#include "dw4/pads.h"
#include "dw4/window.h"      /* dw4_window_key_button: the shared host key -> pad mapping */

#define VKOK(x, what)                                                              \
    do {                                                                           \
        VkResult r_ = (x);                                                         \
        if (r_ != VK_SUCCESS) {                                                    \
            fprintf(stderr, "vulkan: %s failed (%d)\n", what, (int)r_);            \
            return -1;                                                             \
        }                                                                          \
    } while (0)

/* the same, for the function that returns a pointer rather than a status */
#define VKP(x, what)                                                               \
    do {                                                                           \
        VkResult r_ = (x);                                                         \
        if (r_ != VK_SUCCESS) {                                                    \
            fprintf(stderr, "vulkan: %s failed (%d)\n", what, (int)r_);            \
            goto fail;                                                             \
        }                                                                          \
    } while (0)

struct dw4_vk {
    SDL_Window *win;
    int w, h, headless;
    dw4_gl_layer *scale_gpu;
    dw4_fb scaled;
    int focus_lost;
    SDL_GameController *pad;   /* the first gamepad SDL sees, if any */
    dw4_matepads *mates;       /* the next three: the co-op players 2-4 (dw4/pads.h) */
    int disconnected;
    VkInstance inst;
    VkSurfaceKHR surf;
    VkPhysicalDevice gpu;
    VkPhysicalDeviceProperties props;
    VkDevice dev;
    VkQueue queue;
    uint32_t qfam;
    VkSwapchainKHR sc;
    VkFormat fmt;
    VkColorSpaceKHR cspace;
    uint32_t nimg, cur_img;
    VkImage img[8];
    VkImageLayout lay[8];
    VkBuffer stage[8];
    VkDeviceMemory smem[8];
    uint8_t *map[8];
    size_t ssize;
    VkSemaphore sem_ok[8], sem_draw[8];
    VkFence fence;
    VkCommandPool cpool;
    VkCommandBuffer cmd;
    int have_swap;
    int swizzle;                 /* the swapchain is B,G,R,A while dw4_fb holds R,G,B,A bytes */
    int ever_opened;
};

int dw4_vk_built(void) { return 1; }

static int vk_pick_gpu(dw4_vk *v, const char *want_ext)
{
    VkPhysicalDevice gpus[8];
    uint32_t n = 0, i;
    (void)want_ext;
    if (vkEnumeratePhysicalDevices(v->inst, &n, NULL) != VK_SUCCESS || n == 0)
        return -1;
    if (n > 8)
        n = 8;
    if (vkEnumeratePhysicalDevices(v->inst, &n, gpus) != VK_SUCCESS)
        return -1;
    for (i = 0; i < n; i++) {
        uint32_t nq = 0, k;
        VkPhysicalDeviceProperties p;
        vkGetPhysicalDeviceProperties(gpus[i], &p);
        if(dw4_gpu_policy_required() && p.deviceType!=VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
           p.deviceType!=VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)continue;
        vkGetPhysicalDeviceQueueFamilyProperties(gpus[i], &nq, NULL);
        {
            VkQueueFamilyProperties qp[16];
            if (nq > 16)
                nq = 16;
            vkGetPhysicalDeviceQueueFamilyProperties(gpus[i], &nq, qp);
            for (k = 0; k < nq; k++) {
                VkBool32 present = VK_FALSE;
                if (!(qp[k].queueFlags & VK_QUEUE_GRAPHICS_BIT))
                    continue;
                if (v->surf) {
                    if (vkGetPhysicalDeviceSurfaceSupportKHR(gpus[i], k, v->surf, &present) !=
                        VK_SUCCESS || !present)
                        continue;
                }
                /* a discrete GPU is where a real driver lives; prefer it over llvmpipe */
                if (!v->gpu || p.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
                    v->gpu = gpus[i];
                    v->props = p;
                    v->qfam = k;
                }
            }
        }
    }
    if (!v->gpu){dw4_gpu_policy_fail("hardware Vulkan presentation device unavailable");
        return -1;
    }
    printf("vulkan: device \"%s\" (queue family %u%s)\n", v->props.deviceName, v->qfam,
           v->props.deviceType == VK_PHYSICAL_DEVICE_TYPE_CPU ? ", CPU" : "");
    return 0;
}

static int vk_make_instance(dw4_vk *v)
{
    VkApplicationInfo app;
    VkInstanceCreateInfo ci;
    const char *ext[8];
    uint32_t next = 0, i;
    memset(&app, 0, sizeof(app));
    app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app.pApplicationName = "dw4";
    app.apiVersion = VK_API_VERSION_1_0;
    memset(&ci, 0, sizeof(ci));
    ci.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    ci.pApplicationInfo = &app;

    if (v->win) {
        if (!SDL_Vulkan_GetInstanceExtensions(v->win, &next, NULL))
            return -1;
        if (next > 8)
            return -1;
        if (!SDL_Vulkan_GetInstanceExtensions(v->win, &next, ext))
            return -1;
        for (i = 0; i < next; i++)
            printf("vulkan: instance extension %s\n", ext[i]);
        ci.enabledExtensionCount = next;
        ci.ppEnabledExtensionNames = ext;
    }
    VKOK(vkCreateInstance(&ci, NULL, &v->inst), "vkCreateInstance");
    return 0;
}

static int vk_make_device(dw4_vk *v)
{
    float prio = 1.0f;
    VkDeviceQueueCreateInfo qi;
    VkDeviceCreateInfo di;
    const char *dext[1];
    uint32_t nd = 0;
    memset(&qi, 0, sizeof(qi));
    qi.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    qi.queueFamilyIndex = v->qfam;
    qi.queueCount = 1;
    qi.pQueuePriorities = &prio;
    memset(&di, 0, sizeof(di));
    di.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    di.queueCreateInfoCount = 1;
    di.pQueueCreateInfos = &qi;
    if (v->surf) {
        dext[nd++] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
        di.enabledExtensionCount = nd;
        di.ppEnabledExtensionNames = dext;
    }
    VKOK(vkCreateDevice(v->gpu, &di, NULL, &v->dev), "vkCreateDevice");
    vkGetDeviceQueue(v->dev, v->qfam, 0, &v->queue);
    return 0;
}

static VkFormat vk_pick_format(dw4_vk *v, int *swizzle)
{
    VkSurfaceFormatKHR f[32];
    uint32_t n = 0, i;
    /* Preference order matters twice over.  (1) vkCmdCopyBufferToImage does no conversion, so a
     * format whose bytes already read R,G,B,A beats any other property -- the same trap that had the
     * SDL path present the red logo blue.  (2) *Not* sRGB: dw4_fb holds display-encoded bytes (what
     * the SDL path puts on screen verbatim), and an sRGB swapchain tells the display pipeline those
     * bytes are linear, so it would apply a gamma curve and wash the frame out.  UNORM is the
     * pass-through. */
    static const VkFormat pref[] = {
        VK_FORMAT_R8G8B8A8_UNORM, VK_FORMAT_B8G8R8A8_UNORM,
        VK_FORMAT_R8G8B8A8_SRGB,  VK_FORMAT_B8G8R8A8_SRGB,
    };
    VkFormat have[4] = {VK_FORMAT_UNDEFINED, VK_FORMAT_UNDEFINED, VK_FORMAT_UNDEFINED,
                        VK_FORMAT_UNDEFINED};
    size_t p;
    *swizzle = 0;
    {
        VkResult fr = vkGetPhysicalDeviceSurfaceFormatsKHR(v->gpu, v->surf, &n, NULL);
        if (fr != VK_SUCCESS || n == 0) {
            fprintf(stderr, "vulkan: surface format query returned %d with %u format(s)\n", (int)fr, (unsigned)n);
            return VK_FORMAT_UNDEFINED;
        }
    }
    if (n > 32)
        n = 32;
    {
        /* A surface may offer more formats than the 32 slots here (Mesa on Wayland does); the driver then
         * answers VK_INCOMPLETE with the first n filled in, which is exactly what is wanted. */
        VkResult fr = vkGetPhysicalDeviceSurfaceFormatsKHR(v->gpu, v->surf, &n, f);
        if (fr != VK_SUCCESS && fr != VK_INCOMPLETE) {
            fprintf(stderr, "vulkan: surface format list failed (%d)\n", (int)fr);
            return VK_FORMAT_UNDEFINED;
        }
    }
    for (i = 0; i < n; i++)
        for (p = 0; p < sizeof(pref) / sizeof(pref[0]); p++)
            if (f[i].format == pref[p] && have[p] == VK_FORMAT_UNDEFINED) {
                have[p] = f[i].format;
                v->cspace = f[i].colorSpace;
            }
    for (p = 0; p < sizeof(pref) / sizeof(pref[0]); p++)
        if (have[p] != VK_FORMAT_UNDEFINED) {
            *swizzle = (have[p] == VK_FORMAT_B8G8R8A8_UNORM || have[p] == VK_FORMAT_B8G8R8A8_SRGB);
            return have[p];
        }
    /* nothing familiar: take the surface's own first format, and judge by what it is */
    v->cspace = f[0].colorSpace;
    *swizzle = (f[0].format == VK_FORMAT_B8G8R8A8_UNORM || f[0].format == VK_FORMAT_B8G8R8A8_SRGB);
    return f[0].format;
}

static void vk_free_swap(dw4_vk *v)
{
    uint32_t i;
    if (!v->dev)
        return;
    if (v->have_swap) {
        vkDeviceWaitIdle(v->dev);
        for (i = 0; i < v->nimg; i++) {
            if (v->stage[i])
                vkDestroyBuffer(v->dev, v->stage[i], NULL);
            if (v->smem[i])
                vkFreeMemory(v->dev, v->smem[i], NULL);
            if (v->sem_ok[i])
                vkDestroySemaphore(v->dev, v->sem_ok[i], NULL);
            if (v->sem_draw[i])
                vkDestroySemaphore(v->dev, v->sem_draw[i], NULL);
            v->stage[i] = VK_NULL_HANDLE;
            v->smem[i] = VK_NULL_HANDLE;
            v->map[i] = NULL;
            v->sem_ok[i] = v->sem_draw[i] = VK_NULL_HANDLE;
        }
        vkDestroySwapchainKHR(v->dev, v->sc, NULL);
        v->sc = VK_NULL_HANDLE;
    }
    v->nimg = 0;
    v->have_swap = 0;
}

static int vk_make_swap(dw4_vk *v)
{
    VkSurfaceCapabilitiesKHR cap;
    VkSwapchainCreateInfoKHR ci;
    uint32_t i, want;
    int swz = 0;
    VkImageUsageFlags usage;

    if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(v->gpu, v->surf, &cap) != VK_SUCCESS) {
        fprintf(stderr, "vulkan: surface capabilities query failed\n");
        return -1;
    }
    v->fmt = vk_pick_format(v, &swz);
    if (v->fmt == VK_FORMAT_UNDEFINED) {
        fprintf(stderr, "vulkan: the surface offers none of the supported formats (R8G8B8A8/B8G8R8A8, UNORM/sRGB)\n");
        return -1;
    }
    v->swizzle = swz;
    if (cap.currentExtent.width != 0xffffffffu) {
        v->w = (int)cap.currentExtent.width;
        v->h = (int)cap.currentExtent.height;
    } else {
        if (v->w < (int)cap.minImageExtent.width)
            v->w = (int)cap.minImageExtent.width;
        if (v->h < (int)cap.minImageExtent.height)
            v->h = (int)cap.minImageExtent.height;
    }
    want = cap.minImageCount + 1;
    if (cap.maxImageCount && want > cap.maxImageCount)
        want = cap.maxImageCount;
    if (want > 8)
        want = 8;
    usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    if (!(cap.supportedUsageFlags & usage)) {
        fprintf(stderr, "vulkan: swapchain cannot be a transfer destination\n");
        return -1;
    }
    memset(&ci, 0, sizeof(ci));
    ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    ci.surface = v->surf;
    ci.minImageCount = want;
    ci.imageFormat = v->fmt;
    ci.imageColorSpace = v->cspace;
    ci.imageExtent.width = (uint32_t)v->w;
    ci.imageExtent.height = (uint32_t)v->h;
    ci.imageArrayLayers = 1;
    ci.imageUsage = usage;
    ci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ci.preTransform = cap.currentTransform;
    ci.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    /* The loop paces itself to the game's 60 Hz (engine.c frame_pace_sched).  FIFO blocks each present on the
     * next vblank, which on a 144 Hz display makes a 16.7 ms frame alternate between two and three vblanks and
     * feeds that jitter back into the schedule; MAILBOX never blocks and shows the newest frame at each vblank.
     * FIFO is the always-available fallback (and DW4_PRESENT=fifo forces it). */
    ci.presentMode = VK_PRESENT_MODE_FIFO_KHR;
    {
        const char *force = getenv("DW4_PRESENT");
        uint32_t np = 0, k;
        VkPresentModeKHR modes[16];
        if (!(force && !strcmp(force, "fifo")) &&
            vkGetPhysicalDeviceSurfacePresentModesKHR(v->gpu, v->surf, &np, NULL) == VK_SUCCESS && np) {
            if (np > 16) np = 16;
            if (vkGetPhysicalDeviceSurfacePresentModesKHR(v->gpu, v->surf, &np, modes) != VK_SUCCESS && np == 0)
                np = 0;
            for (k = 0; k < np; k++)
                if (modes[k] == VK_PRESENT_MODE_MAILBOX_KHR)
                    ci.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
        }
        fprintf(stderr, "vulkan: present mode %s\n", ci.presentMode == VK_PRESENT_MODE_MAILBOX_KHR ? "MAILBOX" : "FIFO");
    }
    ci.clipped = VK_TRUE;
    VKOK(vkCreateSwapchainKHR(v->dev, &ci, NULL, &v->sc), "vkCreateSwapchainKHR");
    if (vkGetSwapchainImagesKHR(v->dev, v->sc, &v->nimg, NULL) != VK_SUCCESS) {
        fprintf(stderr, "vulkan: swapchain image count query failed\n");
        return -1;
    }
    if (v->nimg > 8)
        v->nimg = 8;
    if (vkGetSwapchainImagesKHR(v->dev, v->sc, &v->nimg, v->img) != VK_SUCCESS) {
        fprintf(stderr, "vulkan: swapchain image query failed\n");
        return -1;
    }
    v->ssize = (size_t)v->w * v->h * 4;
    for (i = 0; i < v->nimg; i++) {
        VkBufferCreateInfo bi;
        VkMemoryRequirements mr;
        VkMemoryAllocateInfo ai;
        VkSemaphoreCreateInfo si;
        void *m;
        v->lay[i] = VK_IMAGE_LAYOUT_UNDEFINED;
        memset(&bi, 0, sizeof(bi));
        bi.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bi.size = v->ssize;
        bi.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        bi.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        VKOK(vkCreateBuffer(v->dev, &bi, NULL, &v->stage[i]), "vkCreateBuffer(staging)");
        vkGetBufferMemoryRequirements(v->dev, v->stage[i], &mr);
        memset(&ai, 0, sizeof(ai));
        ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        ai.allocationSize = mr.size;
        ai.memoryTypeIndex = ~0u;
        {
            VkPhysicalDeviceMemoryProperties mp;
            uint32_t k;
            vkGetPhysicalDeviceMemoryProperties(v->gpu, &mp);
            for (k = 0; k < mp.memoryTypeCount; k++)
                if ((mr.memoryTypeBits & (1u << k)) &&
                    (mp.memoryTypes[k].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) &&
                    (mp.memoryTypes[k].propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)) {
                    ai.memoryTypeIndex = k;
                    break;
                }
        }
        if (ai.memoryTypeIndex == ~0u)
            return -1;
        VKOK(vkAllocateMemory(v->dev, &ai, NULL, &v->smem[i]), "vkAllocateMemory(staging)");
        VKOK(vkBindBufferMemory(v->dev, v->stage[i], v->smem[i], 0), "vkBindBufferMemory");
        if (vkMapMemory(v->dev, v->smem[i], 0, v->ssize, 0, &m) != VK_SUCCESS)
            return -1;
        v->map[i] = (uint8_t *)m;
        memset(&si, 0, sizeof(si));
        si.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        VKOK(vkCreateSemaphore(v->dev, &si, NULL, &v->sem_ok[i]), "vkCreateSemaphore");
        VKOK(vkCreateSemaphore(v->dev, &si, NULL, &v->sem_draw[i]), "vkCreateSemaphore");
    }
    v->have_swap = 1;
    printf("vulkan: swapchain %dx%d, %u images, format %d%s\n", v->w, v->h, v->nimg, (int)v->fmt,
           v->swizzle ? " (B,G,R,A -- the frame is swizzled on upload)" : "");
    return 0;
}

dw4_vk *dw4_vk_open(int w, int h, const char *title, int headless)
{
    dw4_vk *v;
    VkFenceCreateInfo fi;
    VkCommandPoolCreateInfo pi;
    VkCommandBufferAllocateInfo ai;

    if (w <= 0 || h <= 0)
        return NULL;
    v = (dw4_vk *)calloc(1, sizeof(*v));
    if (!v)
        return NULL;
    v->w = w;
    v->h = h;
    v->headless = headless;
    /* headless is a device-only path on purpose: there is no surface to present to, but the loader
     * and a real driver are still exercised, which is what a check can assert without a display */
    if (!headless) {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
            fprintf(stderr, "vulkan: SDL_Init failed (%s)\n", SDL_GetError());
            free(v);
            return NULL;
        }
        v->win = SDL_CreateWindow(title ? title : "dw4", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN);
        if (!v->win) {
            fprintf(stderr, "vulkan: no SDL window (%s)\n", SDL_GetError());
            dw4_vk_close(v);
            return NULL;
        }
    }
    if (vk_make_instance(v) != 0 || vk_pick_gpu(v, NULL) != 0) {
        dw4_vk_close(v);
        return NULL;
    }
    if (!headless) {
        if (!SDL_Vulkan_CreateSurface(v->win, v->inst, &v->surf)) {
            fprintf(stderr, "vulkan: no VkSurfaceKHR (%s)\n", SDL_GetError());
            dw4_vk_close(v);
            return NULL;
        }
        /* the surface exists now, so the GPU choice must actually support presenting to it */
        v->gpu = NULL;
        if (vk_pick_gpu(v, NULL) != 0) {
            dw4_vk_close(v);
            return NULL;
        }
    }
    if (vk_make_device(v) != 0) {
        dw4_vk_close(v);
        return NULL;
    }
    memset(&fi, 0, sizeof(fi));
    fi.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fi.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    VKP(vkCreateFence(v->dev, &fi, NULL, &v->fence), "vkCreateFence");
    memset(&pi, 0, sizeof(pi));
    pi.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    pi.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    pi.queueFamilyIndex = v->qfam;
    VKP(vkCreateCommandPool(v->dev, &pi, NULL, &v->cpool), "vkCreateCommandPool");
    memset(&ai, 0, sizeof(ai));
    ai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    ai.commandPool = v->cpool;
    ai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    ai.commandBufferCount = 1;
    VKP(vkAllocateCommandBuffers(v->dev, &ai, &v->cmd), "vkAllocateCommandBuffers");
    if (!headless && vk_make_swap(v) != 0)
        goto fail;
    v->ever_opened = 1;
    /* Same pad policy as the SDL window: open the first gamepad, keep receiving events while unfocused. */
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    if (!headless) {
        int n = SDL_NumJoysticks(), i;
        for (i = 0; i < n; i++)
            if (SDL_IsGameController(i)) { v->pad = SDL_GameControllerOpen(i); break; }
        fprintf(stderr, "  vulkan pad: %d joystick(s), %s\n", n, v->pad ? SDL_GameControllerName(v->pad) : "none opened");
        v->mates = dw4_matepads_open(v->pad);
    }
    return v;

fail:
    dw4_vk_close(v);
    return NULL;
}

static void vk_image_barrier(VkCommandBuffer cb, VkImage im, VkImageLayout from, VkImageLayout to,
                             VkAccessFlags src, VkAccessFlags dst)
{
    VkImageMemoryBarrier b;
    memset(&b, 0, sizeof(b));
    b.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    b.oldLayout = from;
    b.newLayout = to;
    b.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    b.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    b.image = im;
    b.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    b.subresourceRange.levelCount = 1;
    b.subresourceRange.layerCount = 1;
    b.srcAccessMask = src;
    b.dstAccessMask = dst;
    vkCmdPipelineBarrier(cb, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
                         0, 0, NULL, 0, NULL, 1, &b);
}

int dw4_vk_present(dw4_vk *v, const dw4_fb *fb)
{
    VkResult r;
    uint32_t idx = 0;
    VkCommandBufferBeginInfo bi;
    VkBufferImageCopy cp;
    VkSubmitInfo si;
    VkPresentInfoKHR pi;
    VkPipelineStageFlags wait = VK_PIPELINE_STAGE_TRANSFER_BIT;
    size_t i, n;

    if (!v || !v->have_swap)
        return 0;                       /* headless: nothing to present to */
    if (!fb || !fb->rgba || fb->w <= 0 || fb->h <= 0)
        return -1;

    VKOK(vkWaitForFences(v->dev, 1, &v->fence, VK_TRUE, (uint64_t)-1), "vkWaitForFences");
    r = vkAcquireNextImageKHR(v->dev, v->sc, (uint64_t)-1, v->sem_ok[0], VK_NULL_HANDLE, &idx);
    if (r == VK_ERROR_OUT_OF_DATE_KHR || r == VK_SUBOPTIMAL_KHR) {
        vk_free_swap(v);
        return vk_make_swap(v) == 0 ? 1 : -1;
    }
    if (r != VK_SUCCESS && r != VK_SUBOPTIMAL_KHR)
        return -1;
    if (idx >= v->nimg)
        return -1;
    v->cur_img = idx;

    n = (size_t)v->w * (size_t)v->h;
    if(dw4_gpu_policy_required() && (fb->w!=v->w || fb->h!=v->h)){
        if(!v->scale_gpu || v->scaled.w!=v->w || v->scaled.h!=v->h){
            dw4_gl_layer_close(v->scale_gpu);v->scale_gpu=NULL;dw4_fb_free(&v->scaled);
            if(dw4_fb_init(&v->scaled,v->w,v->h)){dw4_gpu_policy_fail("Vulkan scale target allocation");return -1;}
            v->scale_gpu=dw4_gl_layer_open(v->w,v->h);
        }
        if(!v->scale_gpu || dw4_gl_layer_scale(v->scale_gpu,&v->scaled,fb)){
            dw4_gpu_policy_fail("Vulkan GPU frame resize");return -1;
        }
        fb=&v->scaled;
    }
    if ((int)fb->w != v->w || (int)fb->h != v->h) {
        /* The opening movie is 640x480 regardless of the requested window.
         * Scale into the swapchain-sized staging buffer, preserving byte order. */
        int x, y;
        for (y = 0; y < v->h; y++) {
            size_t sy = (size_t)y * fb->h / v->h;
            for (x = 0; x < v->w; x++) {
                size_t sx = (size_t)x * fb->w / v->w;
                const uint8_t *src = fb->rgba + (sy * fb->w + sx) * 4;
                uint8_t *dst = v->map[idx] + ((size_t)y * v->w + x) * 4;
                dst[0] = src[v->swizzle ? 2 : 0];
                dst[1] = src[1];
                dst[2] = src[v->swizzle ? 0 : 2];
                dst[3] = src[3];
            }
        }
    } else if (v->swizzle)
        for (i = 0; i < n; i++) {
            v->map[idx][i * 4 + 0] = fb->rgba[i * 4 + 2];
            v->map[idx][i * 4 + 1] = fb->rgba[i * 4 + 1];
            v->map[idx][i * 4 + 2] = fb->rgba[i * 4 + 0];
            v->map[idx][i * 4 + 3] = fb->rgba[i * 4 + 3];
        }
    else
        memcpy(v->map[idx], fb->rgba, n * 4);

    VKOK(vkResetCommandBuffer(v->cmd, 0), "vkResetCommandBuffer");
    memset(&bi, 0, sizeof(bi));
    bi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    bi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    VKOK(vkBeginCommandBuffer(v->cmd, &bi), "vkBeginCommandBuffer");
    vk_image_barrier(v->cmd, v->img[idx], v->lay[idx], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                     v->lay[idx] == VK_IMAGE_LAYOUT_UNDEFINED ? 0 : VK_ACCESS_MEMORY_READ_BIT,
                     VK_ACCESS_TRANSFER_WRITE_BIT);
    memset(&cp, 0, sizeof(cp));
    cp.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    cp.imageSubresource.layerCount = 1;
    cp.imageExtent.width = (uint32_t)v->w;
    cp.imageExtent.height = (uint32_t)v->h;
    cp.imageExtent.depth = 1;
    vkCmdCopyBufferToImage(v->cmd, v->stage[idx], v->img[idx], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                           1, &cp);
    vk_image_barrier(v->cmd, v->img[idx], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                     VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_ACCESS_TRANSFER_WRITE_BIT,
                     VK_ACCESS_MEMORY_READ_BIT);
    v->lay[idx] = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    VKOK(vkEndCommandBuffer(v->cmd), "vkEndCommandBuffer");

    VKOK(vkResetFences(v->dev, 1, &v->fence), "vkResetFences");
    memset(&si, 0, sizeof(si));
    si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    si.waitSemaphoreCount = 1;
    /* the acquire semaphore is index 0's: the fence above serialises frames, so only one acquire is
     * ever outstanding (signalling a per-image semaphore and waiting on a different one hangs) */
    si.pWaitSemaphores = &v->sem_ok[0];
    si.pWaitDstStageMask = &wait;
    si.commandBufferCount = 1;
    si.pCommandBuffers = &v->cmd;
    si.signalSemaphoreCount = 1;
    si.pSignalSemaphores = &v->sem_draw[idx];
    VKOK(vkQueueSubmit(v->queue, 1, &si, v->fence), "vkQueueSubmit");
    memset(&pi, 0, sizeof(pi));
    pi.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    pi.waitSemaphoreCount = 1;
    pi.pWaitSemaphores = &v->sem_draw[idx];
    pi.swapchainCount = 1;
    pi.pSwapchains = &v->sc;
    pi.pImageIndices = &idx;
    r = vkQueuePresentKHR(v->queue, &pi);
    if (r == VK_ERROR_OUT_OF_DATE_KHR || r == VK_SUBOPTIMAL_KHR) {
        vk_free_swap(v);
        return vk_make_swap(v) == 0 ? 1 : -1;
    }
    return r == VK_SUCCESS ? 1 : -1;
}

int dw4_vk_pump_in(dw4_vk *v, dw4_input_state *in) { return dw4_vk_pump_mates(v, in, NULL); }

int dw4_vk_pump_mates(dw4_vk *v, dw4_input_state *in, dw4_input_state mates[3])
{
    SDL_Event e;
    if (!v || !v->win)
        return 1;              /* no window (device-only path): nothing to pump, never "closed" */
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            if (in)
                dw4_input_button(in, DW4_BTN_QUIT, 1);
            return 0;
        }
        if (e.type==SDL_WINDOWEVENT) {
            if (e.window.event==SDL_WINDOWEVENT_FOCUS_LOST || e.window.event==SDL_WINDOWEVENT_MINIMIZED) {
                v->focus_lost=1;
                if (in) { dw4_input_init(in);in->focus_pause=1; }
            }
            if (e.window.event==SDL_WINDOWEVENT_FOCUS_GAINED) v->focus_lost=0;
        }
        if (in && v->mates && dw4_matepads_event(v->mates, v->pad, &e, mates)) continue;   /* a co-op mate's pad */
        if (e.type == SDL_KEYDOWN) {
            if (in && !e.key.repeat && e.key.keysym.scancode==SDL_SCANCODE_P) { in->pause=1;continue; }
            if (in && !e.key.repeat && e.key.keysym.scancode==SDL_SCANCODE_R) { in->resume=1;continue; }
            if (e.key.keysym.sym == SDLK_ESCAPE)
                return 0;
            if (in && !e.key.repeat) {
                int b = dw4_window_key_button(e.key.keysym.scancode);
                if (b)
                    dw4_input_button(in, b, 1);
            }
        }
        if (in && (e.type == SDL_CONTROLLERBUTTONDOWN || e.type == SDL_CONTROLLERBUTTONUP)) {
            int b = dw4_window_pad_button(e.cbutton.button);
            if (b)
                dw4_input_button(in, b, e.type == SDL_CONTROLLERBUTTONDOWN);
        }
        if (in && e.type == SDL_CONTROLLERAXISMOTION) {
            if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
                dw4_input_axis(in, DW4_AXIS_LX, e.caxis.value / 32767.0f);
            else if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY)
                dw4_input_axis(in, DW4_AXIS_LY, -(e.caxis.value / 32767.0f));   /* +y is up */
            else if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT)
                dw4_input_button(in, DW4_BTN_L2, e.caxis.value > 16384);
            else if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
                dw4_input_button(in, DW4_BTN_R2, e.caxis.value > 16384);
        }
        if (e.type == SDL_CONTROLLERDEVICEADDED && !v->pad && SDL_IsGameController(e.cdevice.which)) {
            v->pad = SDL_GameControllerOpen(e.cdevice.which);
            if (v->pad) v->disconnected = 0;
        }
        if (e.type == SDL_CONTROLLERDEVICEREMOVED && v->pad &&
            e.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(v->pad))) {
            SDL_GameControllerClose(v->pad);
            v->pad = NULL;
            v->disconnected = 1;
            if (in) { int fp = in->focus_pause; dw4_input_init(in); in->focus_pause = fp; }
        }
        if (e.type == SDL_KEYUP && in) {
            int b = dw4_window_key_button(e.key.keysym.scancode);
            if (b)
                dw4_input_button(in, b, 0);
        }
        if (e.type == SDL_WINDOWEVENT &&
            (e.window.event == SDL_WINDOWEVENT_RESIZED ||
             e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED))
            continue;
    }
    if (in) { in->focus_lost=v->focus_lost; in->disconnected=v->disconnected; }
    return 1;
}

int dw4_vk_pump(dw4_vk *v) { return dw4_vk_pump_in(v, NULL); }

void dw4_vk_report(dw4_vk *v, char *gpu, size_t gpu_len, char *fmt, size_t fmt_len, int *swizzle)
{
    if (!v)
        return;
    if (gpu && gpu_len)
        snprintf(gpu, gpu_len, "%s", v->props.deviceName);
    if (fmt && fmt_len)
        snprintf(fmt, fmt_len, "%s", v->have_swap ? "swapchain" : "no swapchain (headless)");
    if (swizzle)
        *swizzle = v->swizzle;
}

void dw4_vk_close(dw4_vk *v)
{
    if (!v)
        return;
    dw4_gl_layer_close(v->scale_gpu);dw4_fb_free(&v->scaled);
    if (v->dev) {
        vkDeviceWaitIdle(v->dev);
        vk_free_swap(v);
        if (v->cmd)
            vkFreeCommandBuffers(v->dev, v->cpool, 1, &v->cmd);
        if (v->cpool)
            vkDestroyCommandPool(v->dev, v->cpool, NULL);
        if (v->fence)
            vkDestroyFence(v->dev, v->fence, NULL);
        vkDestroyDevice(v->dev, NULL);
    }
    if (v->surf)
        vkDestroySurfaceKHR(v->inst, v->surf, NULL);
    if (v->inst)
        vkDestroyInstance(v->inst, NULL);
    if (v->win)
        SDL_DestroyWindow(v->win);
    if (v->pad)
        SDL_GameControllerClose(v->pad);
    dw4_matepads_close(v->mates);
    if (v->ever_opened)
        SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
    free(v);
}

#else /* !DW4_ENABLE_VULKAN */

int dw4_vk_built(void) { return 0; }
dw4_vk *dw4_vk_open(int w, int h, const char *title, int headless)
{
    (void)w; (void)h; (void)title; (void)headless;
    return NULL;
}
int dw4_vk_present(dw4_vk *v, const dw4_fb *fb) { (void)v; (void)fb; return 0; }
int dw4_vk_pump(dw4_vk *v) { (void)v; return 0; }
int dw4_vk_pump_mates(dw4_vk *v, dw4_input_state *in, dw4_input_state mates[3]) { (void)v; (void)in; (void)mates; return 0; }
int dw4_vk_pump_in(dw4_vk *v, dw4_input_state *in) { (void)v; (void)in; return 0; }
void dw4_vk_report(dw4_vk *v, char *a, size_t b, char *c, size_t d, int *e)
{
    (void)v; (void)a; (void)b; (void)c; (void)d; (void)e;
}
void dw4_vk_close(dw4_vk *v) { (void)v; }

#endif /* DW4_ENABLE_VULKAN */
