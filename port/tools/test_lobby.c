#include "dw4/lobby.h"
#include "dw4/scene.h"
#include "dw4/igfile.h"
#include "dw4/frontend.h"
#include "dw4/png.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct layer_mask {int mode;unsigned background,players,npcs;};
static int layer_visible(void *user,const char *name)
{
    struct layer_mask *m=user;
    m->background+=!strcmp(name,"BG02");m->players+=!strcmp(name,"PC01");m->npcs+=!strcmp(name,"NP01");
    if(m->mode==2)return 0;
    return !m->mode || (strcmp(name,"BG01") && strcmp(name,"BG02") && strcmp(name,"BG03") && strcmp(name,"GM01") && strcmp(name,"GM03"));
}

int main(int argc, char **argv)
{
    dw4_mount mount;
    dw4_fb fb;
    unsigned tick, species;
    assert(argc == 2 && !dw4_mount_open(&mount, argv[1]));
    {
        dw4_igfile f = {0};
        dw4_scene scene;
        unsigned bound = 0, inherited = 0, different = 0;
        assert(!dw4_igfile_open_stage_ref(&f, &mount, dw4_frontend_first_stage(), 0));
        assert(!dw4_scene_load(&scene, f.data, f.len));
        for (unsigned i = 0; i < scene.nnode; i++) {
            const char *name = dw4_scene_node_texture_name(&scene, i);
            if (scene.node[i].id == 14185) {
                assert(name && !strcmp(name, "ML01GR00_n.png"));
                bound++;
            }
            if (dw4_scene_node_mesh(&scene, i) != UINT32_MAX && name) {
                if (!strcmp(name, "ML01GR00_n.png")) inherited++;
                else different++;
                assert(!dw4_scene_node_texture(&scene, i));
            }
        }
        assert(bound && inherited && different);
        dw4_scene_close(&scene);
        dw4_igfile_close(&f);
    }
    assert(!strcmp(dw4_frontend_first_stage(), "stagml11.igb"));
    {
        dw4_ref refs[2];
        assert(dw4_igfile_stage_refs(&mount, dw4_frontend_first_stage(), refs, 2) == 2);
        assert(refs[0].pt == 0 && refs[0].entry == 820);
        assert(refs[1].pt == 0 && refs[1].entry == 819);
    }
    assert(!dw4_fb_init(&fb, 320, 240));
    for (species = 0; species < 4; species++) {
        dw4_lobby *l = dw4_lobby_open(&mount, species, "azA");
        assert(l);
        for(unsigned k=0;k<4;k++) {
            dw4_lobby_portal_state portal;
            assert(!dw4_lobby_portal(l,k,&portal));
            assert(portal.powered==(k==3) && !portal.active && portal.visible);
        }
        dw4_lobby_control_state control;
        assert(!dw4_lobby_control(l, &control));
        assert(!control.hud && !control.box_camera && !control.player_control &&
               !control.model_control && !control.material_updates && !control.material_ticks);
        {
            static const char *weapon[] = {"w_common07.igb", "w_common05.igb",
                                           "w_common01.igb", "w_common06.igb"};
            dw4_lobby_player_state player;
            assert(!dw4_lobby_player(l, &player));
            assert(!strcmp(player.weapon_asset, weapon[species]));
            assert(!strcmp(player.label, "slash") && !strcmp(player.motion, "waitS"));
            assert(!strcmp(player.bone, "RArm04") && player.weapon_triangles > 10);
        }
        for (tick = 0; tick <= 323; tick++) {
            dw4_lobby_tick(l, 1); /* input during choreography cannot dismiss the first page */
            if(tick<=259) {
                int entry=(int)tick-180;
                dw4_lobby_presentation_state state;
                assert(!dw4_lobby_presentation(l,&state) && state.tick==tick);
                assert(fabsf(state.player_alpha-fminf(1,fmaxf(0,(entry+1)/50.0f)))<.0004f);
                assert(fabsf(state.screen_alpha-fminf(1,(tick>=5?tick-4:0)/60.0f))<.0004f);
                if(tick==0) assert(state.player_motion_ns==0 && !state.player_loop);
                if(entry==61) assert(!state.player_loop);
                if(entry==62) assert(state.player_loop && !state.player_motion_ns);
                if(entry<0) assert(!state.arrival_mask && !state.player_loop && !state.player_motion_ns);
                if(entry>=0 && entry<=5) assert(state.arrival_mask==1);
                if(entry>=6 && entry<=11) assert(state.arrival_mask==3);
                if(entry>=12 && entry<=36) assert(state.arrival_mask==7);
                if(entry>=56) assert(!state.arrival_mask);
                if(entry==0) assert(fabsf(state.arrival_alpha[0]-1.0f/6)<1e-6f);
                if(entry<7 || entry>=80) assert(!state.particle_mask);
                if(entry>=7 && entry<=12) assert(state.particle_mask==1);
                if(entry>=13 && entry<=18) assert(state.particle_mask==3);
                if(entry>=19 && entry<=66) assert(state.particle_mask==7);
                if(tick==5 || tick==6 || tick==65) {
                    assert(dw4_lobby_draw(l,&fb,999,NULL)>0);
                    unsigned nonblack=0;
                    for(unsigned p=0;p<320*240;p++) nonblack+=!!(fb.rgba[4*p]|fb.rgba[4*p+1]|fb.rgba[4*p+2]);
                    assert((nonblack>0)==(tick>=5));
                }
                if(tick==204) {
                    assert(dw4_lobby_draw(l,&fb,999,NULL)>0);
                    unsigned n,stars=0,hash=2166136261u;
                    const dw4_layer_draw *draw=dw4_lobby_last_draws(l,&n);
                    for(unsigned j=0;j<n;j++) if(draw[j].tex && draw[j].tex->w==32 &&
                        draw[j].rgba[0][0]>128 && !draw[j].fog && draw[j].no_depth_write) {
                        assert(draw[j].blend==2 && draw[j].aref==12);stars++;
                    }
                    assert(stars==48); /* eight sprites in each of three groups */
                    for(unsigned p=0;p<320*240*4;p++) hash=(hash^fb.rgba[p])*16777619u;
                    assert(dw4_lobby_draw(l,&fb,0,NULL)>0);
                    unsigned repeated=2166136261u;
                    for(unsigned p=0;p<320*240*4;p++) repeated=(repeated^fb.rgba[p])*16777619u;
                    assert(hash==repeated);
                    struct layer_mask hidden={.mode=2};
                    assert(!dw4_lobby_draw_layers(l,&fb,0,NULL,layer_visible,&hidden));
                }
            }
            if(tick==0 || tick==17 || tick==18) {
                dw4_lobby_npc_state moving;
                assert(!dw4_lobby_npc(l,2,&moving));
                if(tick==0) assert(moving.speed>0 && moving.speed<0.01f);
                else if(tick==17) assert(moving.speed>0.13f && moving.speed<=0.14f);
                else assert(moving.speed==0.14f);
            }
            if (tick < 323) assert(dw4_lobby_message(l) == -1);
        }
        assert(dw4_lobby_message(l) == -1);
        for (tick = 0; tick < 16; tick++) dw4_lobby_tick(l, 1);
        assert(dw4_lobby_message(l) == 39);
        dw4_lobby_npc_state guide,male,second,before;
        assert(!dw4_lobby_npc(l,0,&male) && male.speed>0.139f);
        assert(!dw4_lobby_npc(l,1,&guide) && guide.phase==3);
        assert(guide.yaw>177 && guide.yaw<179 && guide.speed==0);
        assert(!dw4_lobby_npc(l,2,&before));
        for(unsigned wait=0;wait<(species==0?2400u:0u);wait++) dw4_lobby_tick(l,0);
        assert(dw4_lobby_message(l)==39);
        assert(!dw4_lobby_npc(l,2,&second));
        printf("route male %.3f/%.3f/%.3f guide %.3f/%.3f/%.3f second %.3f/%.3f/%.3f contact %u\n",male.position[0],male.position[1],male.position[2],guide.position[0],guide.position[1],guide.position[2],second.position[0],second.position[1],second.position[2],second.contacts);
        if(species==0) {
            assert(second.position[0]>before.position[0]+20 && second.contacts);
            before=second;
            for(unsigned wait=0;wait<2400;wait++) dw4_lobby_tick(l,0);
            assert(!dw4_lobby_npc(l,2,&second));
            assert(fabsf(second.position[0]-before.position[0])<0.01f && fabsf(second.position[2]-before.position[2])<0.01f);
        }

        for (tick = 39; tick <= 53; tick++) {
            assert(dw4_lobby_message(l) == (int)tick);
            dw4_lobby_tick(l, 1);
            if (tick == 41 || tick == 46 || tick == 48 || tick == 50 || tick == 53) {
                /* Clear text immediately; let the old window close before opening
                 * the next group. Input throughout either animation is ignored. */
                assert(dw4_lobby_message(l) == -1);
                for (int wait = 0; wait < 16; wait++) dw4_lobby_tick(l, 1);
                if (tick == 53) break;
                if (tick == 48) {
                    for (int wait = 0; wait < 90; wait++) {
                        assert(dw4_lobby_message(l) == -1);
                        dw4_lobby_tick(l, 1);
                    }
                }
                for (int wait = 0; wait < 16; wait++) {
                    assert(dw4_lobby_message(l) == -1);
                    dw4_lobby_tick(l, 1);
                }
            }
        }
        assert(dw4_lobby_message(l) == -1 && !dw4_lobby_intro_done(l));
        dw4_lobby_npc_state departure=guide;
        assert(!dw4_lobby_npc(l,1,&guide));
        assert(guide.phase==5 && guide.motion==0 && guide.speed==0);
        assert(!memcmp(guide.position,departure.position,sizeof guide.position));
        for (tick = 0; tick < 119; tick++) {
            before=guide;
            dw4_lobby_tick(l, 1);
            assert(!dw4_lobby_npc(l,1,&guide));
            assert(guide.phase==5 && guide.motion==0);
            assert(fabsf(remainderf(guide.yaw-before.yaw,360))<10.001f);
            assert(hypotf(guide.position[0]-before.position[0],guide.position[2]-before.position[2])<0.141f);
            if(tick==0) assert(guide.speed>0 && guide.speed<0.01f);
            if(tick>=18) assert(guide.speed==0.14f);
            assert(!dw4_lobby_intro_done(l));
            assert(!dw4_lobby_control(l, &control));
            assert(!control.hud && !control.box_camera && !control.player_control &&
                   !control.model_control && !control.material_updates && !control.material_ticks);
            if(tick==8 || tick==9) {
                assert(!dw4_lobby_npc(l,2,&second));
                assert((second.position[0]==240)==(tick==9));
            }
        }
        dw4_lobby_tick(l, 0);
        assert(dw4_lobby_intro_done(l));
        assert(!dw4_lobby_control(l, &control));
        assert(control.hud && control.box_camera && control.player_control &&
               control.model_control && control.material_updates && control.material_ticks == 1);
        assert(control.camera_region < 17);
        assert(guide.position[0]<departure.position[0]-10 && guide.position[1]==10);
        for (unsigned i = 0; i < 16; i++) assert(isfinite(control.camera_world[i]));
        unsigned handoff_tick = control.handoff_tick;
        for (unsigned i = 0; i < 180; i++) dw4_lobby_tick(l, 1);
        assert(!dw4_lobby_control(l, &control));
        assert(control.handoff_tick == handoff_tick && control.material_ticks == 181);
        assert(dw4_lobby_message(l) == -1);
        assert(!dw4_lobby_npc(l,1,&guide) && guide.phase==6 && guide.motion==1 && guide.speed==0);
        assert(guide.position[0]<departure.position[0]-35);
        assert(hypotf(guide.position[0]-20,guide.position[2]+35)<5 && guide.position[1]==10);
        assert(!dw4_lobby_npc(l,0,&male) && !dw4_lobby_npc(l,2,&second));
        assert(male.position[0]==258.187f && male.position[1]==40 && male.position[2]==174 && male.yaw==180);
        assert(second.position[0]==240 && second.position[1]==40 && second.position[2]==-150 && second.yaw==0);
        assert(male.speed==0 && second.speed==0);

        assert(dw4_lobby_draw(l, &fb, 600, NULL) > 0);
        {
            unsigned n, lit = 0, glow = 0, masked = 0;
            const dw4_layer_draw *d = dw4_lobby_last_draws(l, &n);
            for (unsigned i = 0; i < n; i++) {
                lit += d[i].rgba[0][0] < 100;
                glow += d[i].blend == 2;
                masked += d[i].no_depth_write;
                assert(d[i].straight_rgb && d[i].gs_raster);
                assert(d[i].fog == 2 || (d[i].fog == 0 && d[i].blend == 1 && d[i].no_depth_write && d[i].aref == -1));
                for(unsigned e=0;e<3;e++) {
                    assert(d[i].v[e][0]>=0 && d[i].v[e][0]<=fb.w);
                    assert(d[i].v[e][1]>=0 && d[i].v[e][1]<=fb.h);
                    assert(isfinite(d[i].z[e]) && d[i].z[e]>0);
                }
                for (unsigned e = 0; e < 3; e++) assert(d[i].rgba[e][3] <= 128);
            }
            assert(lit && glow && masked);
        }
        {
            unsigned nonblack = 0, colored = 0;
            for (tick = 0; tick < 320*240; tick++) {
                const unsigned char *p = fb.rgba+4*tick;
                nonblack += !!(p[0]|p[1]|p[2]);
                colored += abs(p[0]-p[1]) > 20 || abs(p[1]-p[2]) > 20;
            }
            assert(nonblack > 20000 && colored > 10000);
        }
        unsigned world_hash = 2166136261u;
        for (unsigned p = 0; p < 320*240*4; p++) world_hash = (world_hash ^ fb.rgba[p])*16777619u;
        {
            dw4_lobby_presentation_state before,after;
            assert(!dw4_lobby_presentation(l,&before));
            struct layer_mask mask={0};
            int all=dw4_lobby_draw_layers(l,&fb,600,NULL,layer_visible,&mask);assert(all>0);
            unsigned hash=2166136261u;
            for(unsigned p=0;p<320*240*4;p++)hash=(hash^fb.rgba[p])*16777619u;
            assert(hash==world_hash && mask.background && mask.players && mask.npcs);
            mask=(struct layer_mask){.mode=1};
            int actors=dw4_lobby_draw_layers(l,&fb,600,NULL,layer_visible,&mask);
            assert(actors>0 && actors<all && mask.players && mask.npcs);
            dw4_lobby_player_state player;assert(!dw4_lobby_player(l,&player) && player.weapon_submitted_triangles);
            mask=(struct layer_mask){.mode=2};
            assert(!dw4_lobby_draw_layers(l,&fb,600,NULL,layer_visible,&mask));
            assert(!dw4_lobby_presentation(l,&after) && !memcmp(&before,&after,sizeof before));
        }
        assert(dw4_lobby_draw(l, &fb, 600, &(dw4_fefont){.have=1}) > 0);
        unsigned hud_hash = 2166136261u;
        for (unsigned p = 0; p < 320*240*4; p++) hud_hash = (hud_hash ^ fb.rgba[p])*16777619u;
        assert(hud_hash != world_hash);
        assert(!dw4_lobby_control(l,&control) && control.material_ticks == 181);
        assert(!dw4_lobby_npc(l,1,&before));
        assert(!memcmp(&guide,&before,sizeof guide)); /* draws cannot move the guide */
        if (getenv("DW4_LOBBY_TEST_FRAME")) {
            char path[1024];
            snprintf(path,sizeof path,"%s-%u.png",getenv("DW4_LOBBY_TEST_FRAME"),species);
            assert(!dw4_png_write(path,fb.rgba,320,240));
        }
        if (getenv("DW4_LOBBY_TEST_FRAME"))
            assert(!dw4_png_write(getenv("DW4_LOBBY_TEST_FRAME"), fb.rgba, 320, 240));
        /* Commands change presentation eligibility, without a teleport or a
         * render-driven clock. Power-on arms OFF; only SWON starts activation. */
        for(unsigned portal=0;portal<4;portal++) {
            dw4_lobby_portal_state state;
            assert(!dw4_lobby_portal_command(l,portal,"SQ_POWEROF"));
            assert(!dw4_lobby_portal_command(l,portal,"SQ_SWON"));
            assert(!dw4_lobby_portal(l,portal,&state) && !state.active);
            assert(!dw4_lobby_portal_command(l,portal,"SQ_POWERON"));
            assert(!dw4_lobby_portal(l,portal,&state) && state.powered && !state.active && state.action==1);
            assert(!dw4_lobby_portal_command(l,portal,"SQ_SWON"));
            assert(!dw4_lobby_portal(l,portal,&state) && state.active && state.action==3);
        }
        for(unsigned wait=0;wait<42;wait++) dw4_lobby_tick(l,0);
        unsigned removed_portal_triangles=0;
        for(unsigned portal=0;portal<4;portal++) {
            dw4_lobby_portal_state before,after;
            assert(!dw4_lobby_portal(l,portal,&before) && before.active && before.action==2);
            assert(dw4_lobby_draw(l,&fb,0,NULL)>0);
            unsigned n;const dw4_layer_draw *draw=dw4_lobby_last_draws(l,&n);
            uint32_t hash=2166136261u;
            for(unsigned p=0;p<320*240*4;p++) hash=(hash^fb.rgba[p])*16777619u;
            assert(dw4_lobby_draw(l,&fb,999999,NULL)>0);
            uint32_t repeat=2166136261u;
            for(unsigned p=0;p<320*240*4;p++) repeat=(repeat^fb.rgba[p])*16777619u;
            assert(hash==repeat && !dw4_lobby_portal(l,portal,&after));
            assert(after.animation_ns==before.animation_ns);
            assert(!dw4_lobby_portal_visible(l,portal,0));
            assert(dw4_lobby_draw(l,&fb,0,NULL)>0);
            unsigned hidden;draw=dw4_lobby_last_draws(l,&hidden);(void)draw;
            assert(hidden<=n);removed_portal_triangles+=n-hidden;
            assert(!dw4_lobby_portal_visible(l,portal,1));
            assert(!dw4_lobby_portal_command(l,portal,"SQ_SWOF"));
        }
        assert(removed_portal_triangles>0);
        for(unsigned wait=0;wait<32;wait++) dw4_lobby_tick(l,0);
        for(unsigned portal=0;portal<4;portal++) {
            dw4_lobby_portal_state state;
            assert(!dw4_lobby_portal(l,portal,&state) && !state.active && state.action==1);
        }
        assert(!dw4_lobby_actor_visible(l,1,0));
        assert(dw4_lobby_draw(l,&fb,0,NULL)>0);
        unsigned hidden;dw4_lobby_last_draws(l,&hidden);
        assert(!dw4_lobby_actor_visible(l,1,1));
        assert(dw4_lobby_draw(l,&fb,0,NULL)>0);
        unsigned visible;dw4_lobby_last_draws(l,&visible);assert(visible>hidden);
        assert(dw4_lobby_actor_visible(l,4,0)<0 && dw4_lobby_portal_visible(l,4,0)<0);
        assert(dw4_lobby_portal_command(l,0,"UNKNOWN")<0);
        const dw4_tex *shadow=dw4_lobby_shadow_map(l);
        assert(shadow && shadow->w==256 && shadow->h==256);
        unsigned shadow_pixels=0;
        for(unsigned p=0;p<256*256;p++) {
            assert(!shadow->rgba[4*p] && !shadow->rgba[4*p+1] && !shadow->rgba[4*p+2]);
            assert(shadow->rgba[4*p+3]<=77);shadow_pixels+=shadow->rgba[4*p+3]!=0;
        }
        assert(shadow_pixels);
        /* Changing Light affects shading/atlases without advancing the scene or
         * changing the projective caster map. Restoring Hard restores every byte. */
        size_t bytes=(size_t)fb.w*fb.h*4;
        uint8_t *hard=malloc(bytes), *map=malloc(256*256*4);
        assert(hard && map);
        memcpy(hard,fb.rgba,bytes);memcpy(map,shadow->rgba,256*256*4);
        dw4_lobby_set_light(l,0);
        assert(dw4_lobby_draw(l,&fb,0,NULL)>0);
        assert(memcmp(hard,fb.rgba,bytes));
        assert(!memcmp(map,shadow->rgba,256*256*4));
        dw4_lobby_set_light(l,1);
        assert(dw4_lobby_draw(l,&fb,0,NULL)>0);
        assert(!memcmp(hard,fb.rgba,bytes));
        free(hard);free(map);
        for(unsigned actor=0;actor<4;actor++) if(actor!=1)
            assert(!dw4_lobby_actor_visible(l,actor,0));
        assert(dw4_lobby_draw(l,&fb,0,NULL)>0);
        shadow_pixels=0;for(unsigned p=0;p<256*256;p++) shadow_pixels+=shadow->rgba[4*p+3]!=0;
        assert(shadow_pixels); /* low-detail player caster survives independently */
        for(unsigned actor=0;actor<4;actor++) assert(!dw4_lobby_actor_visible(l,actor,0));
        assert(dw4_lobby_draw(l,&fb,0,NULL)>0);
        for(unsigned p=0;p<256*256;p++) assert(!shadow->rgba[4*p+3]);
        /* Appearance publication preserves world state and failed preparation
         * leaves the last valid graph/pose renderable. Exercise repeated swaps. */
        for(unsigned actor=0;actor<4;actor++)assert(!dw4_lobby_actor_visible(l,actor,1));
        dw4_lobby_presentation_state held,after;
        assert(!dw4_lobby_presentation(l,&held));
        dw4_lobby_status(l,1);
        static const char *swaps[]={"w_common05","w_common01","w_common06","w_common02","w_common03","w_common04","w_common07"};
        char error[256];
        for(unsigned swap=0;swap<21;swap++){
            assert(!dw4_lobby_weapon(l,&mount,swaps[swap%7],error,sizeof error));
            dw4_lobby_player_state player;assert(!dw4_lobby_player(l,&player));
            assert(!strncmp(player.weapon_asset,swaps[swap%7],strlen(swaps[swap%7])));
            assert(player.weapon_triangles>10 && player.motion[0] && player.bone[0]);
            assert(dw4_lobby_draw(l,&fb,0,NULL)>0);
            assert(!dw4_lobby_player(l,&player) && player.weapon_submitted_triangles);
            unsigned parts=swap%7>=3 && swap%7<=5?2:1;assert(dw4_lobby_weapon_parts(l)==parts);
            unsigned submitted=0;
            for(unsigned part=0;part<parts;part++) {
                dw4_lobby_weapon_part_state attachment;assert(!dw4_lobby_weapon_part(l,part,&attachment));
                assert(!strcmp(attachment.bone,part?"LArm04":"RArm04"));
                assert(attachment.triangles>10 && attachment.submitted_triangles);
                submitted+=attachment.submitted_triangles;
            }
            assert(submitted==player.weapon_submitted_triangles);
            assert(!dw4_lobby_presentation(l,&after) && after.tick==held.tick);
            assert(!dw4_lobby_control(l,&control) && control.handoff_tick==handoff_tick);
        }
        assert(dw4_lobby_weapon(l,&mount,"missing_weapon",error,sizeof error)<0);
        dw4_lobby_player_state valid;assert(!dw4_lobby_player(l,&valid));
        assert(!strcmp(valid.weapon_asset,"w_common07.igb"));
        assert(dw4_lobby_draw(l,&fb,0,NULL)>0);
        dw4_lobby_close(l);
    }
    {
        dw4_be_state state;dw4_be_init(&state);
        dw4_scriptengine *scripts=dw4_scriptengine_open(&state,NULL,NULL);assert(scripts);
        dw4_lobby *l=dw4_lobby_open(&mount,0,"azA");assert(l);
        assert(!dw4_lobby_attach_scripts(l,&mount,scripts,&state,42));
        assert(dw4_lobby_attach_scripts(l,&mount,scripts,&state,42));
        for(unsigned t=0;t<10000;t++) {
            assert(!dw4_scriptengine_tick(scripts));dw4_lobby_tick(l,1);
            assert(!dw4_lobby_script_error(l)[0]);
        }
        dw4_lobby_ai_state ai;assert(!dw4_lobby_ai(l,&ai));
        assert(dw4_lobby_intro_done(l) && ai.events>2 && ai.choices>10 && ai.hp>=1 && ai.hp<=3);
        dw4_lobby_presentation_state held,held_after;assert(!dw4_lobby_presentation(l,&held));
        dw4_lobby_status(l,1);
        for(unsigned j=0;j<180;j++)dw4_lobby_tick(l,1);
        assert(!dw4_lobby_presentation(l,&held_after) && !memcmp(&held,&held_after,sizeof held));
        dw4_lobby_ai_state held_ai;assert(!dw4_lobby_ai(l,&held_ai) && !memcmp(&ai,&held_ai,sizeof ai));
        assert(!dw4_lobby_health(l,1,70,20,170,60));assert(dw4_lobby_health(l,1,171,20,170,60));
        dw4_lobby_status(l,0);dw4_lobby_tick(l,0);assert(!dw4_lobby_presentation(l,&held_after) && held_after.tick==held.tick+1);
        assert(!dw4_lobby_ai(l,&ai));
        dw4_random random=state.random;
        assert(dw4_lobby_draw(l,&fb,0,NULL)>0);
        assert(!memcmp(&random,&state.random,sizeof random));
        dw4_lobby_ai_state after;assert(!dw4_lobby_ai(l,&after));
        assert(!memcmp(&ai,&after,sizeof ai));
        dw4_lobby_detach_scripts(l);dw4_lobby_detach_scripts(l);
        assert(dw4_script_run(dw4_scriptengine_vm(scripts),"aim_n_digilff.lua"));
        assert(strstr(dw4_script_error(dw4_scriptengine_vm(scripts)),"not loaded"));
        dw4_scriptengine_close(scripts); /* detached owner can outlive the VM */
        dw4_lobby_close(l);
        puts("lobby scripts: original WPos, continued AI patrol, draw independence and detach-before-VM-close OK");
    }
    dw4_fb_free(&fb);
    dw4_mount_close(&mount);
    puts("lobby: four species, accelerated choreography, long-dialogue route/wall limit, greeting, guide departure, exact delayed relocations and control handoff OK");
    return 0;
}
