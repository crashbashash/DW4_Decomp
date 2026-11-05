#include "dw4/lobby.h"
#include "dw4/png.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static dw4_script_value text(const char *s){return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
static void place(dw4_lobby *l,const char *v){dw4_script_value a[]={text("PLAYER"),{0},{DW4_SCRIPT_NUMBER,0,NULL,0},text("MOVETRANS"),text(v)},r;char e[256];assert(!dw4_lobby_player_service(l,"sd",a,5,&r,e,sizeof e));dw4_lobby_tick(l,0);}
static void direction(dw4_lobby *l,float dx,float dz){dw4_lobby_control_state c;assert(!dw4_lobby_control(l,&c));float yaw=atan2f(dx,dz)-atan2f(c.camera_world[8],c.camera_world[10]);dw4_lobby_input(l,sinf(yaw),-cosf(yaw));}
static uint32_t rgb_hash(const dw4_tex *t){uint32_t h=2166136261u;if(!t || !t->rgba)return 0;for(int i=0;i<t->w*t->h;i++)for(int c=0;c<3;c++)h=(h^t->rgba[4*i+c])*16777619u;return h;}
int main(int argc,char **argv){
 dw4_mount m;dw4_fb fb;assert(argc==2 && !dw4_mount_open(&m,argv[1]));assert(!dw4_fb_init(&fb,320,224));
 for(int species=0;species<4;species++){
  dw4_lobby *l=dw4_lobby_open(&m,species,"EDGE");assert(l);
  for(unsigned i=0;!dw4_lobby_intro_done(l) && i<2500;i++)dw4_lobby_tick(l,1);
  assert(dw4_lobby_intro_done(l));
  place(l,"V<18,20,-95>/V<0,0,0>"); /* view the blue stage-travel portal */
  for(unsigned i=0;i<180;i++)dw4_lobby_tick(l,0); /* settle the authored box-camera handoff */
  for(unsigned k=0;k<4;k++){dw4_lobby_portal_instances p;assert(!dw4_lobby_portal_slots(l,k,&p));assert(p.slots==(k==3?3:1) && p.visible_slots==1);
   if(k==3)assert(p.position[0]==5 && p.position[1]==27 && p.position[2]==15);
  }
  assert(dw4_lobby_draw(l,&fb,0,NULL)>=0);unsigned n,after;
  const dw4_layer_draw *draw=dw4_lobby_last_draws(l,&n);dw4_layer_draw *old=malloc(n*sizeof *old);assert(old);memcpy(old,draw,n*sizeof *old);
  for(unsigned i=0;i<60;i++)dw4_lobby_tick(l,0);
  assert(dw4_lobby_draw(l,&fb,0,NULL)>=0);draw=dw4_lobby_last_draws(l,&after);
  unsigned blue_before=0,blue_after=0,blue_moving=0;
  unsigned char *blue=malloc(after);assert(blue);
  for(unsigned i=0;i<after;i++){blue[i]=rgb_hash(draw[i].tex)==0xbcde2b3fu;blue_after+=blue[i];}
  for(unsigned i=0;i<n;i++)if(rgb_hash(old[i].tex)==0xbcde2b3fu){
   blue_before++;unsigned j=0,which=0;while(j<after){if(blue[j]){if(which==blue_before-1)break;which++;}j++;}
   if(j<after)for(unsigned v=0;v<3;v++)if(fabsf(old[i].v[v][0]-draw[j].v[v][0])>.1f || fabsf(old[i].v[v][1]-draw[j].v[v][1])>.1f){blue_moving++;break;}
  }
  fprintf(stderr,"blue portal texture: %u -> %u triangles, %u changing geometry\n",blue_before,blue_after,blue_moving);
  assert(blue_before && blue_after && blue_moving);free(blue);free(old);
  place(l,"V<175,30,-40>/V<0,0,0>");
  int first_fall=0,first_land=0,second_fall=0,second_land=0,held=0;float start_x=0;
  for(unsigned i=0;i<160;i++){
   direction(l,-1,0);dw4_lobby_tick(l,0);dw4_lobby_walk_state a;assert(!dw4_lobby_walk(l,&a));
   if(a.position[1]<30 && a.position[1]>20){assert(!strcmp(a.motion,"jumpS02"));if(!first_fall)start_x=a.position[0];first_fall=1;}
   if(first_fall && a.position[1]==20)first_land=1;
   if(first_land && a.position[1]<20 && a.position[1]>10)second_fall=1;
   if(second_fall && a.position[1]==10)second_land=1;
   if(first_fall && !held && a.position[1]>20){
    dw4_lobby_status(l,1);for(unsigned j=0;j<20;j++)dw4_lobby_tick(l,0);
    dw4_lobby_walk_state b;assert(!dw4_lobby_walk(l,&b));assert(!memcmp(a.position,b.position,sizeof a.position) && a.motion_ns==b.motion_ns);
    dw4_lobby_status(l,0);held=1;
   }
  }
  assert(first_fall && first_land && second_fall && second_land && held && start_x<167 && start_x>165);
  dw4_lobby_input(l,0,0);for(unsigned i=0;i<40;i++)dw4_lobby_tick(l,0);
  dw4_lobby_walk_state a;assert(!dw4_lobby_walk(l,&a));fprintf(stderr,"edge finish %.9g %.9g %.9g speed %.9g motion %s\n",a.position[0],a.position[1],a.position[2],a.speed,a.motion);
  assert(fabsf(a.position[1]-10)<1e-5f && !a.speed && !strcmp(a.motion,"waitS"));
  assert(!dw4_lobby_script_error(l)[0]);printf("portal/edge species %d: one centered commander instance, %u animated blue-portal triangles, fall at X %.6f, 30 -> 20 -> 10 and held fall pass\n",species,blue_moving,start_x);
  dw4_lobby_close(l);
 }
 dw4_fb_free(&fb);dw4_mount_close(&m);
}
