/* Independent CPU/GPU material contract: modulation, alpha/depth, STQ, wrap and fog. */
#include "dw4/gl_layer.h"
#include "dw4/gl_render.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static dw4_layer_draw triangle(const dw4_tex *tex, float z)
{
    dw4_layer_draw d = {0};
    const float v[3][5] = {{-1, -1, -1, -1, 1}, {33, -1, 2, -1, 0.5f}, {-1, 33, -1, 2, 2}};
    memcpy(d.v, v, sizeof v);
    memset(d.rgba, 128, sizeof d.rgba);
    d.tex = tex;
    d.aref = -1;
    d.straight_rgb = 1;
    d.z[0] = d.z[1] = d.z[2] = z;
    return d;
}
static int compare(dw4_gl_layer *g, dw4_fb *cpu, dw4_fb *gpu, dw4_layer_draw *draws, int n,
                   int wrap, int linear, const char *name)
{
    int x, y, c, bad = 0, max = 0;
    dw4_fb_clear(cpu, 20, 30, 40);
    /* Nonuniform underlay detects upside-down uploads/readbacks. */
    for (y = 0; y < cpu->h; y++)
        for (x = 0; x < cpu->w; x++) {
            cpu->rgba[4 * (y * cpu->w + x) + 1] = y * 8;
            if(draws[0].color_mask&8)cpu->rgba[4*(y*cpu->w+x)+3]=37+y;
        }
    memcpy(gpu->rgba, cpu->rgba, (size_t)cpu->w * cpu->h * 4);
    dw4_render_zbuf_clear(cpu);
    dw4_render_tex_wrap = wrap;
    dw4_render_tex_linear = linear;
    dw4_render_layer_draws(cpu, draws, n, 1);
    if (dw4_gl_layer_draw(g, gpu, draws, n, wrap, linear, -1))
        return 1;
    /* Interior pixels avoid implementation-dependent triangle edge coverage. */
    for (y = 1; y < 14; y++)
        for (x = 1; x < 14; x++)
            for (c = 0; c < 4; c++) {
                int i = 4 * (y * cpu->w + x) + c;
                int delta = abs(cpu->rgba[i] - gpu->rgba[i]);
                if (delta > max)
                    max = delta;
                if (delta > 2)
                    bad++;
            }
    printf("GPU layer %-24s max delta %d %s\n", name, max, bad ? "FAILED" : "ok");
    return bad != 0;
}
int main(void)
{
    dw4_gl_layer *g;
    dw4_gl *peer;
    dw4_fb cpu = {0}, gpu = {0};
    uint8_t half[] = {200, 100, 40, 64}, red[] = {240, 0, 0, 128},blue[]={0,0,180,128};
    uint8_t grid[] = {255, 0, 0, 128, 0, 200, 0, 128, 0, 0, 180, 128, 64, 64, 64, 128};
    dw4_tex a = {half, 1, 1}, b = {red, 1, 1}, t = {grid, 2, 2},c={blue,1,1};
    dw4_layer_draw d[3];
    int bad = 0;
    if (!dw4_gl_built()) {
        puts("GPU layer: GLES unavailable, skipped");
        return 0;
    }
    /* Layer passes must restore the caller's EGL context and must not terminate
     * a display shared with the existing mesh renderer. */
    peer = dw4_gl_open(16, 16);
    if (!peer) {
        puts("GPU layer: EGL unavailable, skipped");
        return 0;
    }
    g = dw4_gl_layer_open(16, 16);
    if (!g) {
        puts("GPU layer: EGL unavailable, skipped");
        dw4_gl_close(peer);
        return 0;
    }
    if (dw4_fb_init(&cpu, 16, 16) || dw4_fb_init(&gpu, 16, 16))
        return 1;
    printf("GPU layer renderer: %s\n", dw4_gl_layer_info(g));
    /* Every RGB byte must survive normalized RGBA8 fetch before GS truncation.
     * This includes values whose float conversion lies just below the integer. */
    {
        uint8_t pixels[16*16*4];
        for(unsigned p=0;p<256;p++){
            pixels[4*p]=(uint8_t)p;pixels[4*p+1]=(uint8_t)(255-p);
            pixels[4*p+2]=(uint8_t)(p^85);pixels[4*p+3]=128;
        }
        dw4_tex bytes={pixels,16,16};dw4_layer_draw quad[2];
        /* Sample texel centers so this byte census does not test UV boundaries. */
        const float xyuv[4][5]={{-1,-1,-.03125f,-.03125f,1},{17,-1,1.09375f,-.03125f,1},
                               {-1,17,-.03125f,1.09375f,1},{17,17,1.09375f,1.09375f,1}};
        const unsigned index[2][3]={{0,1,2},{2,1,3}};
        for(unsigned t=0;t<2;t++){
            quad[t]=triangle(&bytes,100);quad[t].gs_raster=1;quad[t].filter=1;
            for(unsigned v=0;v<3;v++)memcpy(quad[t].v[v],xyuv[index[t][v]],sizeof xyuv[0]);
        }
        bad+=compare(g,&cpu,&gpu,quad,2,0,0,"all RGBA8 RGB bytes GS");
        for(unsigned p=0;p<256;p++)for(unsigned c=0;c<3;c++)
            assert(cpu.rgba[4*p+c]==pixels[4*p+c] && gpu.rgba[4*p+c]==pixels[4*p+c]);
    }
    /* Clears must reset masks left by depth-only passes and preserve exact
     * RGBA8 values, including a transparent offscreen portrait target. */
    assert(!dw4_gl_layer_clear(g,&gpu,17,53,191,0));
    for(int p=0;p<16*16;p++)assert(gpu.rgba[4*p]==17 && gpu.rgba[4*p+1]==53 && gpu.rgba[4*p+2]==191 && gpu.rgba[4*p+3]==0);
    d[0] = triangle(&a, 100);
    d[0].blend = 1;
    bad += compare(g, &cpu, &gpu, d, 1, 1, 0, "alpha once");
    d[0].blend = 0;
    bad += compare(g, &cpu, &gpu, d, 1, 1, 0, "opaque ignores alpha");
    d[0].straight_rgb = 0;
    bad += compare(g, &cpu, &gpu, d, 1, 1, 0, "legacy premult opaque");
    d[0].blend = 2;
    d[0].no_depth_write = 1;
    d[1] = triangle(&b, 50);
    bad += compare(g, &cpu, &gpu, d, 2, 1, 0, "additive depth mask");
    d[0].no_depth_write = 0;
    bad += compare(g, &cpu, &gpu, d, 2, 1, 0, "near depth occludes");
    d[1].z[0] = d[1].z[1] = d[1].z[2] = 100;
    bad += compare(g, &cpu, &gpu, d, 2, 1, 0, "equal depth passes");
    d[1].z[0]=d[1].z[1]=d[1].z[2]=50;d[1].depth_always=1;
    bad += compare(g,&cpu,&gpu,d,2,1,0,"ALWAYS overrides near");
    d[1].no_depth_write=1;
    d[2]=triangle(&c,75);
    bad += compare(g,&cpu,&gpu,d,3,1,0,"ALWAYS preserves depth");
    assert(cpu.rgba[4*(2*cpu.w+2)]==240 && cpu.rgba[4*(2*cpu.w+2)+2]==0);
    d[1].no_depth_write=0;
    bad += compare(g,&cpu,&gpu,d,3,1,0,"ALWAYS writes depth");
    assert(cpu.rgba[4*(2*cpu.w+2)]==0 && cpu.rgba[4*(2*cpu.w+2)+2]==180);
    d[1].depth_always=d[1].no_depth_write=0;
    d[0]=triangle(&b,100);d[0].color_mask=15;d[1]=triangle(&c,50);
    bad+=compare(g,&cpu,&gpu,d,2,1,0,"depth-only preserves color");
    assert(cpu.rgba[4*(2*cpu.w+2)]==20 && cpu.rgba[4*(2*cpu.w+2)+1]==16 && cpu.rgba[4*(2*cpu.w+2)+2]==40);
    assert(cpu.rgba[4*(2*cpu.w+2)+3]==39);
    d[0].no_depth_write=1;
    bad+=compare(g,&cpu,&gpu,d,2,1,0,"masked no-write admits far");
    assert(cpu.rgba[4*(2*cpu.w+2)+2]==180);
    d[0].no_depth_write=0;d[0].aref=128;
    bad+=compare(g,&cpu,&gpu,d,2,1,0,"masked alpha fail keeps Z");
    assert(cpu.rgba[4*(2*cpu.w+2)+2]==180);
    d[0].aref=-1;
    assert(!dw4_gl_layer_clear(g,&gpu,11,29,101,128));
    for(int p=0;p<16*16;p++)assert(gpu.rgba[4*p]==11 && gpu.rgba[4*p+1]==29 && gpu.rgba[4*p+2]==101 && gpu.rgba[4*p+3]==128);
    d[0].no_depth_write=0;d[1]=triangle(&b,100);
    bad+=compare(g,&cpu,&gpu,d,2,1,0,"color mask batch boundary");
    assert(cpu.rgba[4*(2*cpu.w+2)]==240);
    d[0].color_mask=5;
    bad+=compare(g,&cpu,&gpu,d,1,1,0,"partial RGBA write mask");
    assert(cpu.rgba[4*(2*cpu.w+2)]==20 && cpu.rgba[4*(2*cpu.w+2)+1]==0 && cpu.rgba[4*(2*cpu.w+2)+2]==40);
    d[0]=triangle(&a,100);d[0].color_mask=8;
    bad+=compare(g,&cpu,&gpu,d,1,1,0,"alpha channel preserved");
    assert(cpu.rgba[4*(2*cpu.w+2)+3]==39);
    d[0]=triangle(&a,100);d[0].blend=2;
    d[0].aref = 64;
    d[1].z[0] = d[1].z[1] = d[1].z[2] = 50;
    bad += compare(g, &cpu, &gpu, d, 2, 1, 0, "alpha fail keeps depth");
    d[0] = triangle(&b, 100);
    d[0].fog = 2;
    d[0].fog_color[0] = 0;
    d[0].fog_color[1] = 25;
    d[0].fog_color[2] = 63;
    bad += compare(g, &cpu, &gpu, d, 1, 1, 0, "coloured fog");
    d[0] = triangle(&t, 100);
    d[0].blend = 1;
    bad += compare(g, &cpu, &gpu, d, 1, 1, 1, "STQ repeat bilinear");
    bad += compare(g, &cpu, &gpu, d, 1, 0, 1, "STQ clamp bilinear");
    d[0].filter=1;
    bad += compare(g,&cpu,&gpu,d,1,1,1,"per-draw nearest");
    d[0].filter=2;
    bad += compare(g,&cpu,&gpu,d,1,1,0,"per-draw linear");
    d[0] = triangle(NULL, 100);
    d[0].blend = 2;
    bad += compare(g, &cpu, &gpu, d, 1, 1, 0, "untextured additive");
    d[0] = triangle(&b, 100);
    d[1] = triangle(NULL, 50);
    bad += compare(g, &cpu, &gpu, d, 2, 1, 0, "legacy untextured depth");
    {
        dw4_ui_draw ui[2]={{0}};
        for(unsigned i=0;i<2;i++){
            dw4_layer_draw source=triangle(i?&c:&b,i?50:100);
            ui[i].tex=source.tex;ui[i].stq=ui[i].gs_raster=ui[i].depth_mode=ui[i].depth_write=1;
            ui[i].filter=1;memcpy(ui[i].v,source.v,sizeof ui[i].v);memcpy(ui[i].z,source.z,sizeof ui[i].z);memcpy(ui[i].rgba,source.rgba,sizeof ui[i].rgba);
        }
        dw4_fb_clear(&cpu,0,0,0);dw4_fb_clear(&gpu,0,0,0);dw4_render_zbuf_clear(&cpu);
        dw4_render_ui_draws(&cpu,ui,2,1);assert(!dw4_gl_layer_ui(g,&gpu,ui,2));
        for(unsigned k=0;k<3;k++)assert(cpu.rgba[4*(2*cpu.w+2)+k]==gpu.rgba[4*(2*gpu.w+2)+k]);
        assert(cpu.rgba[4*(2*cpu.w+2)]==240);
        ui[1].depth_mode=2;ui[1].depth_write=0;
        dw4_fb_clear(&cpu,0,0,0);dw4_fb_clear(&gpu,0,0,0);dw4_render_zbuf_clear(&cpu);
        dw4_render_ui_draws(&cpu,ui,2,1);assert(!dw4_gl_layer_ui(g,&gpu,ui,2));
        assert(cpu.rgba[4*(2*cpu.w+2)+2]==180 && gpu.rgba[4*(2*gpu.w+2)+2]==180);
        ui[0].color_mask=15;ui[1].depth_mode=1;ui[1].depth_write=1;
        dw4_fb_clear(&cpu,20,30,40);dw4_fb_clear(&gpu,20,30,40);dw4_render_zbuf_clear(&cpu);
        dw4_render_ui_draws(&cpu,ui,2,1);assert(!dw4_gl_layer_ui(g,&gpu,ui,2));
        for(unsigned k=0;k<4;k++)assert(cpu.rgba[4*(2*cpu.w+2)+k]==gpu.rgba[4*(2*gpu.w+2)+k]);
        assert(cpu.rgba[4*(2*cpu.w+2)]==20 && cpu.rgba[4*(2*cpu.w+2)+2]==40);
        puts("GPU UI bridge: authored depth, filtering and depth-only color masks agree");
    }
    dw4_gl_layer_close(g);
    {
        const float view[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
        const float ambient[3] = {1, 1, 1};
        if (dw4_gl_frame_begin(peer, view, 0.7f, 1, ambient, NULL, 0) ||
            dw4_gl_frame_end(peer, &gpu)) {
            puts("GPU layer: peer EGL context did not survive");
            bad++;
        }
    }
    dw4_gl_close(peer);
    dw4_fb_free(&cpu);
    dw4_fb_free(&gpu);
    return bad ? 1 : 0;
}
