#include "dw4/loadjob.h"
#include "dw4/frontui.h"
#include "dw4/lobby.h"
#include "dw4/png.h"
#include "dw4/scene.h"
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct gate {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int entered, release, fail;
    dw4_mount *mount;
};

static void *prepare(void *arg)
{
    struct gate *g = arg;
    pthread_mutex_lock(&g->mutex);
    g->entered = 1;
    pthread_cond_broadcast(&g->cond);
    while (!g->release) pthread_cond_wait(&g->cond, &g->mutex);
    pthread_mutex_unlock(&g->mutex);
    return g->fail ? NULL : dw4_lobby_open(g->mount, 0, "Loader");
}

int main(int argc, char **argv)
{
    dw4_mount m;
    dw4_fb fb;
    struct gate g = { .mutex = PTHREAD_MUTEX_INITIALIZER, .cond = PTHREAD_COND_INITIALIZER };
    assert(!dw4_mount_open(&m, argc > 1 ? argv[1] : "../local/extracted"));
    g.mount = &m;
    /* Original QS time getter 0x001bf790 uses sign-magnitude ticks of 2^23 ns.
     * Duration/65535 incorrectly ends this trace in 42 ms instead of 4.83 s. */
    uint32_t card_size;
    dw4_scene card;
    const uint8_t *card_blob = dw4_mount_entry(&m, 1, 1321, &card_size, NULL);
    assert(card_blob && !dw4_scene_load(&card, card_blob, card_size));
    const dw4_scene_seq *trace = &card.node[18].seq;
    assert(trace->ntimes == 12);
    assert(((const int64_t *)trace->times)[1] == 1660944384LL);
    assert(((const int64_t *)trace->times)[11] == 4831838208LL);
    uint32_t bs, bd;
    assert(dw4_scene_node_blend(&card, 19, &bs, &bd) && bs == 4 && bd == 1);
    float u0, v0, u1, v1;
    dw4_scene_set_time(&card, 130.0*1000000000/60);
    assert(dw4_scene_node_uv_offset(&card, 19, &u0, &v0));
    dw4_scene_set_time(&card, 150.0*1000000000/60);
    assert(dw4_scene_node_uv_offset(&card, 19, &u1, &v1));
    assert(u0 != u1);
    dw4_scene_close(&card);
    const dw4_manifest_file *asset = dw4_manifest_find(&m.man, "loadingUSA/ldagml11.igb");
    assert(asset && asset->pt == 1 && asset->entry == 1321);
    dw4_frontui *art = dw4_frontui_open_loading(&m, "stagML11");
    assert(art && dw4_frontui_items(art) == 17 && dw4_frontui_textures(art) == 1);
    assert(!dw4_fb_init(&fb, 640, 448));
    uint8_t *previous = malloc(640*448*4);
    assert(previous);
    /* Directory-qualified lookup must choose the stage and localization, despite
     * identical basenames elsewhere in the manifest. */
    const dw4_manifest_file *other = dw4_manifest_find(&m.man, "loadingUSA/ldagml02.igb");
    assert(other && other->entry == 1320);
    assert(dw4_manifest_find(&m.man, "loadingeng/ldagml11.igb")->entry == 831);
    assert(!dw4_frontui_open_loading(&m, "stagDoesNotExist"));
    /* Deliberately hold preparation. Rendering and polling must continue without
     * waiting, then the real CPU lobby loader runs while resident art is sampled. */
    dw4_loadjob *job = dw4_loadjob_start(prepare, &g, 1);
    assert(job);
    pthread_mutex_lock(&g.mutex);
    while (!g.entered) pthread_cond_wait(&g.cond, &g.mutex);
    pthread_mutex_unlock(&g.mutex);
    void *result = (void *)art;
    for (int frame = 0; frame < 150; ++frame) {
        assert(!dw4_loadjob_poll(job, &result) && result == art);
        dw4_fb_clear(&fb, 0, 0, 0);
        dw4_frontui_loading_sample(art, (uint64_t)frame*1000000000/60);
        assert(dw4_frontui_loading_ready(art) == (frame > 100));
        assert(dw4_frontui_draw(art, &fb, -1) > 0);
        if (!frame || frame == 130) memcpy(previous, fb.rgba, 640*448*4);
    }
    assert(memcmp(previous, fb.rgba, 640*448*4));
    /* The hexagon trace brightens the top-left outlines during the sweep;
     * this region excludes both scrolling text bands and the stage preview. */
    unsigned trace_before = 0, trace_after = 0;
    for (int y=0; y<100; ++y) for (int x=0; x<170; ++x) {
        const uint8_t *a = previous + (y*640+x)*4;
        const uint8_t *b = fb.rgba + (y*640+x)*4;
        trace_before += a[0]>75 && a[1]>100 && a[2]>100;
        trace_after += b[0]>75 && b[1]>100 && b[2]>100;
    }
    assert(trace_after > trace_before + 100);
    unsigned preview = 0, title = 0;
    for (int y=174; y<278; ++y) for (int x=251; x<390; ++x) {
        const uint8_t *p = fb.rgba + (y*640+x)*4;
        if ((int)p[2]-(int)p[0]>30 || (int)p[1]-(int)p[0]>30) ++preview;
    }
    for (int y=107; y<131; ++y) for (int x=40; x<260; ++x) {
        const uint8_t *p = fb.rgba + (y*640+x)*4;
        if (p[0]>100 && p[1]>100 && p[2]>100) ++title;
    }
    assert(preview>4000 && title>100); /* preview and stage-name lettering */
    if (argc > 2) assert(!dw4_png_write(argv[2], fb.rgba,640,448));
    /* Compare another destination at the same visible phase. Stage-specific
     * preview/name artwork must change, rather than reusing the lobby card. */
    memcpy(previous, fb.rgba, 640*448*4);
    dw4_frontui *different = dw4_frontui_open_loading(&m, "stagML02");
    assert(different);
    for (int frame=0; frame<150; ++frame)
        dw4_frontui_loading_sample(different, (uint64_t)frame*1000000000/60);
    dw4_fb_clear(&fb,0,0,0); dw4_frontui_draw(different,&fb,-1);
    assert(memcmp(previous,fb.rgba,640*448*4));
    dw4_frontui_close(different);
    /* Original completion locks the card, so later samples stay identical. */
    dw4_frontui_loading_lock(art);
    dw4_frontui_loading_sample(art,150ULL*1000000000/60);
    dw4_fb_clear(&fb,0,0,0); dw4_frontui_draw(art,&fb,-1);
    memcpy(previous,fb.rgba,640*448*4);
    dw4_frontui_loading_sample(art,151ULL*1000000000/60);
    dw4_fb_clear(&fb,0,0,0); dw4_frontui_draw(art,&fb,-1);
    assert(!memcmp(previous,fb.rgba,640*448*4));
    pthread_mutex_lock(&g.mutex);
    g.release = 1; pthread_cond_broadcast(&g.cond);
    pthread_mutex_unlock(&g.mutex);
    for (int frame = 0; !dw4_loadjob_poll(job, &result); ++frame) {
        dw4_fb_clear(&fb,0,0,0);
        dw4_frontui_loading_sample(art,(uint64_t)(frame+150)*1000000000/60);
        dw4_frontui_draw(art,&fb,-1);
    }
    assert(result);
    assert(dw4_loadjob_close(job) == result);
    dw4_lobby_close(result);
    /* NULL is a completed failure, not an eternally pending load. */
    g.fail = 1;
    job = dw4_loadjob_start(prepare, &g, 0);
    assert(job && dw4_loadjob_poll(job, &result) && !result);
    assert(!dw4_loadjob_close(job));
    /* Closing an unpolled worker joins it and returns its unpublished world. */
    g.fail = 0;
    job = dw4_loadjob_start(prepare, &g, 1);
    assert(job);
    result = dw4_loadjob_close(job);
    assert(result);
    dw4_lobby_close(result);
    free(previous);
    dw4_fb_free(&fb); dw4_frontui_close(art); dw4_mount_close(&m);
    pthread_cond_destroy(&g.cond); pthread_mutex_destroy(&g.mutex);
    puts("loading: stalled worker stays drawable, original stage card animates, atomic result/failure and shutdown OK");
}
