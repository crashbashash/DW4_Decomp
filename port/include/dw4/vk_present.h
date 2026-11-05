/* dw4/vk_present.h — presenting the frame through a Vulkan swapchain.
 *
 * This is the output path for GPU or explicitly selected reference frames, replacing SDL2's
 * renderer (src/window.c) with a Vulkan swapchain.  SDL2 still creates the window and the
 * VkSurfaceKHR (SDL_Vulkan_CreateSurface is the supported way in, and it keeps a Wayland
 * session and input working), but nothing of the frame goes through SDL's renderer any more.
 *
 * No shaders and no graphics pipeline are needed for the final copy: the frame is uploaded to a staging
 * buffer and copied into the acquired swapchain image, so the whole path is
 * `vkCmdCopyBufferToImage` plus two layout transitions.  That also means the *format* matters:
 * vkCmdCopyBufferToImage does no conversion, so a B8G8R8A8 swapchain with an R,G,B,A framebuffer
 * would present the red logo blue -- the same trap that caught the SDL path (window.c), handled here
 * by choosing an R8G8B8A8 format when the surface offers one and swizzling R/B when it does not.
 * A differently sized normal frame is resized on GPU before the staging copy.
 *
 * Everything here is optional and detected via pkg-config (`DW4_ENABLE_VULKAN`); without it the
 * module compiles to no-ops and the caller keeps using the SDL path.
 */
#ifndef DW4_VK_PRESENT_H
#define DW4_VK_PRESENT_H

#include "dw4/render.h"
#include "dw4/input.h"

typedef struct dw4_vk dw4_vk;

/* 1 when this build has a Vulkan backend at all. */
int dw4_vk_built(void);

/* Open a window that presents through Vulkan.  `headless` still initialises the loader and a device
 * (so the path is exercised where there is no display) but creates no surface or swapchain.  Returns
 * NULL on any failure, having printed why. */
dw4_vk *dw4_vk_open(int w, int h, const char *title, int headless);

/* Upload `fb` and present it.  Returns 1 when it was presented, 0 when there was nothing to present
 * to (headless) and -1 on a Vulkan failure the caller should treat as fatal for this window. */
int dw4_vk_present(dw4_vk *v, const dw4_fb *fb);

/* Pump window events; 0 when the user closed the window. */
int dw4_vk_pump(dw4_vk *v);

/* As `dw4_vk_pump`, but also decodes keyboard events into `in` (Space/Enter -> Cross, Esc -> quit),
 * so a caller that owns the loop (the movie player) can honour a skip key. */
int dw4_vk_pump_in(dw4_vk *v, dw4_input_state *in);
/* As `dw4_vk_pump_in`; the controllers after the first one feed `mates[0..2]` (co-op players 2-4, dw4/pads.h). NULL: they stay player 1's. */
int dw4_vk_pump_mates(dw4_vk *v, dw4_input_state *in, dw4_input_state mates[3]);

/* What the backend reports about itself (for a check): the GPU name, the swapchain format and
 * whether the frame had to be swizzled.  Any pointer may be NULL. */
void dw4_vk_report(dw4_vk *v, char *gpu, size_t gpu_len, char *fmt, size_t fmt_len, int *swizzle);

void dw4_vk_close(dw4_vk *v);

#endif /* DW4_VK_PRESENT_H */
