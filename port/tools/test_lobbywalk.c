#include "dw4/lobby.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
static float distance(const float a[3],const float b[3])
{return hypotf(a[0]-b[0],a[2]-b[2]);}
static int same(const dw4_lobby_walk_state *a,const dw4_lobby_walk_state *b)
{return !memcmp(a->position,b->position,sizeof a->position) && a->yaw==b->yaw && a->speed==b->speed &&
    a->motion==b->motion && a->motion_ns==b->motion_ns && a->contacts==b->contacts;}
int main(int argc,char **argv)
{
    dw4_mount mount;assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../../local/extracted"));
    dw4_fb fb;assert(!dw4_fb_init(&fb,320,224));
    for(int species=0;species<4;species++) {
        dw4_lobby *l=dw4_lobby_open(&mount,species,"WALK");assert(l);
        dw4_lobby_walk_state spawn,now,held;assert(!dw4_lobby_walk(l,&spawn));
        dw4_lobby_input(l,1,0);
        for(unsigned i=0;!dw4_lobby_intro_done(l) && i<2500;i++)dw4_lobby_tick(l,1);
        assert(dw4_lobby_intro_done(l) && !dw4_lobby_script_error(l)[0]);
        /* Neutral input freezes demand, while the original Stop channel brakes. */
        dw4_lobby_input(l,0,0);for(unsigned i=0;i<30;i++)dw4_lobby_tick(l,0);
        assert(!dw4_lobby_walk(l,&spawn) && spawn.speed==0 && !strcmp(spawn.motion,"waitS"));
        dw4_lobby_jump(l,1);dw4_lobby_tick(l,0);
        assert(!dw4_lobby_walk(l,&now) && now.position[1]>spawn.position[1] && !strcmp(now.motion,"jumpS01"));
        float peak=now.position[1];unsigned falling=0,landing=0;
        for(unsigned i=0;i<120;i++) {
            dw4_lobby_tick(l,0);assert(!dw4_lobby_walk(l,&now));
            if(now.position[1]>peak)peak=now.position[1];
            falling|=!strcmp(now.motion,"jumpS02");landing|=!strcmp(now.motion,"jumpS03");
        }
        assert(peak>spawn.position[1]+5 && falling && landing && now.position[1]==spawn.position[1]);
        assert(!strcmp(now.motion,"waitS") && !dw4_lobby_script_error(l)[0]);
        assert(dw4_lobby_draw(l,&fb,0,NULL)>=0);
        dw4_lobby_input(l,1,0);dw4_lobby_jump(l,1);
        for(unsigned i=0;i<8;i++)dw4_lobby_tick(l,0);
        assert(!dw4_lobby_walk(l,&now) && now.position[1]>spawn.position[1] && distance(spawn.position,now.position)>0);
        dw4_lobby_status(l,1);for(unsigned i=0;i<30;i++)dw4_lobby_tick(l,0);
        assert(!dw4_lobby_walk(l,&held) && same(&now,&held));
        assert(dw4_lobby_draw(l,&fb,0,NULL)>=0 && !dw4_lobby_walk(l,&held) && same(&now,&held));
        dw4_lobby_status(l,0);dw4_lobby_input(l,0,0);
        for(unsigned i=0;i<120;i++)dw4_lobby_tick(l,0);
        assert(!dw4_lobby_walk(l,&spawn) && spawn.speed==0 && !strcmp(spawn.motion,"waitS"));
        dw4_lobby_input(l,.1f,.1f);for(unsigned i=0;i<30;i++)dw4_lobby_tick(l,0);
        assert(!dw4_lobby_walk(l,&now) && !distance(spawn.position,now.position));
        dw4_lobby_input(l,1,0);
        for(unsigned i=0;i<40;i++)dw4_lobby_tick(l,0);
        assert(!dw4_lobby_walk(l,&now) && now.speed>0 && !strcmp(now.motion,"runS"));
        assert(distance(spawn.position,now.position)>4 && distance(spawn.position,now.position)<30);
        dw4_lobby_control_state control;assert(!dw4_lobby_control(l,&control) && control.material_ticks>0);
        float camera[16];memcpy(camera,control.camera_world,sizeof camera);
        assert(dw4_lobby_draw(l,&fb,0,NULL)>=0);unsigned count;const dw4_layer_draw *draw=dw4_lobby_last_draws(l,&count);
        assert(draw && count);
        uint8_t pixels[320*224*4];memcpy(pixels,fb.rgba,sizeof pixels);
        for(unsigned i=0;i<3;i++)assert(dw4_lobby_draw(l,&fb,0,NULL)>=0);
        assert(!memcmp(pixels,fb.rgba,sizeof pixels));
        assert(!dw4_lobby_walk(l,&held) && same(&now,&held));
        dw4_lobby_control_state before_hold;assert(!dw4_lobby_control(l,&before_hold));
        assert(!memcmp(camera,before_hold.camera_world,sizeof camera));
        dw4_lobby_status(l,1);for(unsigned i=0;i<180;i++)dw4_lobby_tick(l,0);
        assert(!dw4_lobby_walk(l,&held) && same(&now,&held));
        assert(!dw4_lobby_control(l,&control) && !memcmp(&before_hold,&control,sizeof control));
        dw4_lobby_status(l,0);dw4_lobby_input(l,0,0);
        for(unsigned i=0;i<40;i++)dw4_lobby_tick(l,0);
        assert(!dw4_lobby_walk(l,&held) && held.speed==0 && !strcmp(held.motion,"waitS"));
        assert(distance(now.position,held.position)>0 && distance(now.position,held.position)<8);
        dw4_lobby_input(l,1,0);
        unsigned regions=0,blends=0;
        for(unsigned i=0;i<1400;i++) {
            dw4_lobby_control_state previous;assert(!dw4_lobby_control(l,&previous));
            dw4_lobby_tick(l,0);assert(!dw4_lobby_control(l,&control));
            float rotation=0;
            for(unsigned k=0;k<12;k++) {
                float d=previous.camera_world[k]-control.camera_world[k];rotation+=d*d;
            }
            if(previous.camera_region!=control.camera_region)regions++;
            if(rotation>1e-9f)blends++;
            assert(rotation<.04f); /* Authored region change cannot snap the rig. */
        }
        assert(regions && blends>20);
        assert(!dw4_lobby_walk(l,&now) && now.contacts && isfinite(now.position[0]) && isfinite(now.position[1]));
        assert(!dw4_lobby_script_error(l)[0]);
        assert(!dw4_lobby_control(l,&control) && memcmp(camera,control.camera_world,sizeof camera));
        printf("lobby walk species %d: position %.6f %.6f %.6f, contacts %u\n",species,now.position[0],now.position[1],now.position[2],now.contacts);
        dw4_lobby_close(l);
    }
    dw4_fb_free(&fb);dw4_mount_close(&mount);
    puts("lobby walk: four starters, authored acceleration/braking/run poses, collision, camera/material updates, draw/STATUS clock holds pass");
}
