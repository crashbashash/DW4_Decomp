#include "dw4/lobbyui.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

struct events {unsigned count;char model[64],action[64];};
static void action_event(void *user,const char *model,const char *action)
{struct events *e=user;e->count++;snprintf(e->model,sizeof e->model,"%s",model);snprintf(e->action,sizeof e->action,"%s",action);}
static unsigned count_texture(dw4_lobbyui *ui, int w, int h)
{
    unsigned n, count = 0;
    const dw4_ui_draw *d = dw4_lobbyui_draws(ui, &n);
    for (unsigned i = 0; i < n; i++)
        count += d[i].tex && d[i].tex->w == w && d[i].tex->h == h;
    return count;
}
/* Lit MP dots on the left of the HUD ring: the mpparts texel (156,24,231). */
static unsigned mp_lit(const dw4_fb *fb)
{
    unsigned count = 0;
    for (unsigned y = 360; y < 416; y++) for (unsigned x = 15; x < 40; x++) {
        const uint8_t *p = fb->rgba + 4 * (y * fb->w + x);
        count += p[0] >= 120 && p[1] < 80 && p[2] >= 200;
    }
    return count;
}
/* Number quads on the 256x16 digit atlases: blank places project to UV 0, and
 * the distinct right-edge U values count the distinct digits shown. */
static void number_quads(dw4_lobbyui *ui, unsigned *blank, unsigned *distinct)
{
    unsigned n;
    float seen[64];
    const dw4_ui_draw *d = dw4_lobbyui_draws(ui, &n);
    *blank = *distinct = 0;
    for (unsigned i = 0; i < n; i++) {
        if (!d[i].tex || d[i].tex->w != 256 || d[i].tex->h != 16) continue;
        float u = 0;
        for (unsigned e = 0; e < 3; e++) u = fmaxf(u, d[i].v[e][2]);
        if (u == 0 && d[i].v[0][3] == 0 && d[i].v[1][3] == 0 && d[i].v[2][3] == 0) { (*blank)++; continue; }
        unsigned k = 0;
        while (k < *distinct && seen[k] != u) k++;
        if (k == *distinct && *distinct < 64) seen[(*distinct)++] = u;
    }
}
int main(int argc, char **argv)
{
    dw4_mount mount;
    dw4_scene scene;
    dw4_fb fb;
    dw4_fefont normal, minimum;
    uint32_t size;
    assert(argc == 2 && !dw4_mount_open(&mount, argv[1]));
    assert(!dw4_fefont_load_face(&normal, &mount, "NORMAL"));
    assert(!dw4_fefont_load_face(&minimum, &mount, "MINIMUM"));
    assert(normal.nall == 484 && minimum.nall == 484);
    const dw4_glyph *a = dw4_fefont_glyph(&normal, 'D'), *b = dw4_fefont_glyph(&minimum, 'D');
    assert(a && b && a->h > b->h && a->u0 != b->u0);
    dw4_fefont_free(&normal);
    dw4_fefont_free(&minimum);
    const uint8_t *blob = dw4_mount_entry(&mount, 0, 820, &size, NULL);
    assert(blob && !dw4_scene_load(&scene, blob, size) && !dw4_fb_init(&fb, 640, 448));
    dw4_lobbyui *ui = dw4_lobbyui_open(&mount, &scene, blob, size);
    assert(ui);
    assert(dw4_lobbyui_message(ui) == -1 && dw4_lobbyui_draw(ui, &fb) == 0);
    dw4_lobbyui_start(ui);
    for (unsigned i = 0; i < 16; i++) {
        assert(dw4_lobbyui_message(ui) == -1);
        dw4_fb_clear(&fb, 32, 32, 32);
        assert(dw4_lobbyui_draw(ui, &fb) > 0);
        assert(!count_texture(ui, 512, 512)); /* text waits for window completion */
        dw4_lobbyui_tick(ui, 1);
    }
    for (int page = 39; page <= 53; page++) {
        assert(dw4_lobbyui_message(ui) == page);
        dw4_fb_clear(&fb, 32, 32, 32);
        assert(dw4_lobbyui_draw(ui, &fb) > 0);
        assert(count_texture(ui, 512, 512));
        int talk = page < 49 || page > 50;
        assert((count_texture(ui, 64, 64) > 0) == talk);
        unsigned n, body = 0, name = 0;
        const dw4_ui_draw *d = dw4_lobbyui_draws(ui, &n);
        for (unsigned i = 0; i < n; i++)
            if (d[i].tex->w == 512) {
                if (d[i].rgba[0][2] == 60)
                    name++;
                else {
                    body++;
                    for (unsigned e = 0; e < 3; e++) {
                        assert(d[i].v[e][0] >= (talk ? 107.9f : 23.9f) && d[i].v[e][0] < 620);
                        assert(d[i].v[e][1] >= 316.9f && d[i].v[e][1] < 429);
                    }
                }
            }
        assert(body && (name == 16) == talk);
        if (page == 39) {
            /* Disc layout's first H and speaker D, measured against retail GS. */
            int h = 0, sp = 0;
            for (unsigned i = 0; i < n; i++)
                if (d[i].tex->w == 512) {
                    h |= d[i].rgba[0][2] == 114 && fabsf(d[i].v[0][0] - 108) < 0.01f &&
                         d[i].v[0][1] > 316.9f && d[i].v[0][1] < 317.1f;
                    sp |= d[i].rgba[0][2] == 60 && fabsf(d[i].v[0][0] - 40) < 0.01f &&
                          d[i].v[0][1] > 287.9f && d[i].v[0][1] < 288.1f;
                }
            assert(h && sp);
        }
        dw4_lobbyui_tick(ui, 1);
        if (page == 41 || page == 46 || page == 48 || page == 50 || page == 53) {
            assert(dw4_lobbyui_message(ui) == -1);
            dw4_fb_clear(&fb, 32, 32, 32);
            dw4_lobbyui_draw(ui, &fb);
            assert(!count_texture(ui, 512, 512));
            for (unsigned i = 0; i < 16; i++)
                dw4_lobbyui_tick(ui, 1);
            if (page == 53)
                break;
            if (page == 48)
                for (unsigned i = 0; i < 90; i++) {
                    assert(dw4_lobbyui_delay(ui) && dw4_lobbyui_draw(ui, &fb) == 0);
                    dw4_lobbyui_tick(ui, 1);
                }
            for (unsigned i = 0; i < 16; i++) {
                assert(dw4_lobbyui_message(ui) == -1);
                dw4_lobbyui_tick(ui, 1);
            }
        }
    }
    assert(dw4_lobbyui_page(ui) == 15 && dw4_lobbyui_draw(ui, &fb) == 0);
    unsigned portraits[16];
    for (unsigned species = 0; species < 16; species++) { /* every player form has its own portrait tile */
        dw4_lobbyui *hud = dw4_lobbyui_open(&mount, &scene, blob, size);
        assert(hud);
        dw4_lobbyui_restore_hud(hud, species);
        for (unsigned i = 0; i < 180; i++) dw4_lobbyui_tick(hud, 0);
        dw4_fb_clear(&fb,32,32,32);
        assert(dw4_lobbyui_draw(hud,&fb)>0);
        /* A full gauge shows every dot at the texture's own brightness, not
         * under the dark socket ring drawn earlier in scene order. */
        assert(mp_lit(&fb) >= 100);
        /* Retail HUD uses authored panels/numbers; no extra glyph name row. */
        unsigned hud_count;const dw4_ui_draw *hud_draw=dw4_lobbyui_draws(hud,&hud_count);
        for(unsigned i=0;i<hud_count;i++)assert(!hud_draw[i].tex ||
            hud_draw[i].tex->w!=512 || hud_draw[i].tex->h!=512);
        portraits[species] = 2166136261u;
        for (unsigned y = 354; y < 394; y++) for (unsigned x = 42; x < 78; x++)
            for (unsigned c = 0; c < 3; c++) portraits[species] =
                (portraits[species] ^ fb.rgba[4*(y*640+x)+c])*16777619u;
        for (unsigned other = 0; other < species; other++) assert(portraits[species] != portraits[other]);
        unsigned nd;const dw4_ui_draw *before_number=dw4_lobbyui_draws(hud,&nd);
        float *before_uv=malloc(nd*6*sizeof *before_uv);assert(before_uv);
        for(unsigned i=0;i<nd;i++)for(unsigned e=0;e<3;e++){before_uv[6*i+2*e]=before_number[i].v[e][2];before_uv[6*i+2*e+1]=before_number[i].v[e][3];}
        assert(!dw4_lobbyui_health(hud,10,85,20,170,60));
        assert(dw4_lobbyui_draw(hud,&fb)>0);
        unsigned changed=0,after_count;const dw4_ui_draw *after_number=dw4_lobbyui_draws(hud,&after_count);assert(after_count==nd);
        for(unsigned i=0;i<nd;i++)for(unsigned e=0;e<3;e++)changed+=before_uv[6*i+2*e]!=after_number[i].v[e][2] || before_uv[6*i+2*e+1]!=after_number[i].v[e][3];
        assert(changed);free(before_uv);
        for(unsigned tick=0;tick<180;tick++)dw4_lobbyui_tick(hud,0);
        for(unsigned meter=0;meter<2;meter++){
            uint32_t node;dw4_hudmeter held=*dw4_lobbyui_meter(hud,meter,&node);
            assert(held.time>1000000000 && held.time<3000000000);
            for(unsigned repeat=0;repeat<2;repeat++){
                assert(dw4_lobbyui_draw(hud,&fb)>0);
                assert(!memcmp(&held,dw4_lobbyui_meter(hud,meter,NULL),sizeof held));
                unsigned sampled=0;
                for(unsigned j=0;j<scene.nnode;j++)if(scene.node[j].has_seq){
                    uint32_t ancestor=j;
                    while(ancestor<scene.nnode && scene.node[ancestor].id!=node)ancestor=scene.node[ancestor].parent;
                    if(ancestor<scene.nnode){assert(scene.node[j].time_bias==held.time);sampled++;}
                }
                assert(sampled);
            }
        }
        {
            /* Level 99 with 99999 HP/MP (retail max-stat captures): every HP/MP
             * place and both level places show a 9; only the third level
             * place is blank. Level 999 fills all three level places. */
            unsigned blank, distinct;
            assert(!dw4_lobbyui_health(hud,99,99999,99999,99999,99999));
            assert(dw4_lobbyui_draw(hud,&fb)>0);
            number_quads(hud,&blank,&distinct);
            assert(blank == 2 && distinct == 1);
            assert(!dw4_lobbyui_health(hud,999,99999,99999,99999,99999));
            assert(dw4_lobbyui_draw(hud,&fb)>0);
            number_quads(hud,&blank,&distinct);
            assert(blank == 0 && distinct == 1);
            assert(!dw4_lobbyui_health(hud,10,85,20,170,60));
        }
        dw4_hudmeter old_hp=*dw4_lobbyui_meter(hud,0,NULL);
        dw4_playerhealth dead={.level=10,.hp=0,.mp=30,.max_hp=170,.max_mp=60,.hp_publish=0};
        assert(!dw4_lobbyui_health_publish(hud,&dead));
        assert(!memcmp(&old_hp,dw4_lobbyui_meter(hud,0,NULL),sizeof old_hp));
        assert(dw4_lobbyui_meter(hud,1,NULL)->target!=0);
        assert(dw4_lobbyui_health(hud,10,0,0,0,0)<0);
        assert(!dw4_lobbyui_health(hud,10,0,0,170,60));
        for(unsigned tick=0;tick<180;tick++)dw4_lobbyui_tick(hud,0);
        assert(dw4_lobbyui_meter(hud,0,NULL)->time==1000000000);
        assert(dw4_lobbyui_meter(hud,1,NULL)->time==1000000000);
        dw4_fb_clear(&fb,32,32,32);
        assert(dw4_lobbyui_draw(hud,&fb)>0 && !mp_lit(&fb));
        dw4_lobbyui_close(hud);
    }
    struct events events={0};dw4_lobbyui_actions(ui,action_event,&events);
    dw4_script_value args[]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"i_messwn",8},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"GENERATE",8},{DW4_SCRIPT_STRING,0,"SQ_OPEN",7}},result={0};char error[128];
    assert(!dw4_lobbyui_script_service(ui,"sd",args,5,&result,error,sizeof error));
    assert(events.count==1 && !strcmp(events.model,"i_messwn") && !strcmp(events.action,"OPEN"));
    args[3]=(dw4_script_value){DW4_SCRIPT_STRING,0,"SQ_CLOSE",8};
    assert(!dw4_lobbyui_script_service(ui,"sd",args,4,&result,error,sizeof error));
    assert(events.count==2 && !strcmp(events.action,"CLOSE"));
    dw4_lobbyui_actions(ui,NULL,NULL);unsigned count=events.count;
    args[3]=(dw4_script_value){DW4_SCRIPT_STRING,0,"SQ_OPEN",7};
    assert(!dw4_lobbyui_script_service(ui,"sd",args,4,&result,error,sizeof error));assert(events.count==count);
    dw4_lobbyui_close(ui);
    dw4_fb_free(&fb);
    dw4_scene_close(&scene);
    dw4_mount_close(&mount);
    puts("lobby UI: all 15 pages, original portrait/windows, two faces, typography, transitions "
         "and beep wait OK");
    return 0;
}
