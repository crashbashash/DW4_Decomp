#include "dw4/lobbycollision.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Randomised proof that the bounds prefilters never change a result: the same queries with and without the index must agree bit for bit. */
static unsigned rng_state=12345;
static float rnd(float lo,float hi){rng_state=rng_state*1664525u+1013904223u;return lo+(hi-lo)*((rng_state>>8)&0xffff)/65535.0f;}
static void differential(void)
{
    enum{TRIS=400,VERTS=TRIS*3};
    float wallv[VERTS*3],floorv[VERTS*3];uint32_t widx[VERTS],fidx[VERTS];
    for(unsigned t=0;t<TRIS;t++) {
        float scale=t%7==0?0.02f:t%11==0?300.0f:t%5==0?3.0f:40.0f;      /* tiny, huge and ordinary triangles */
        float cx=rnd(-200,200),cz=rnd(-200,200),cy=rnd(-20,60);
        for(unsigned k=0;k<3;k++) {
            wallv[9*t+3*k]=cx+rnd(-scale,scale);wallv[9*t+3*k+1]=cy+rnd(-scale,scale);wallv[9*t+3*k+2]=cz+rnd(-scale,scale);
            floorv[9*t+3*k]=cx+rnd(-scale,scale);floorv[9*t+3*k+1]=cy+rnd(-scale*.2f,scale*.2f);floorv[9*t+3*k+2]=cz+rnd(-scale,scale);
            widx[3*t+k]=fidx[3*t+k]=3*t+k;
        }
        if(t%9==0){for(unsigned k=0;k<3;k++){floorv[9*t+3*k+2]=floorv[9*t+2]+k*1e-4f;wallv[9*t+3*k]=wallv[9*t]+k*1e-4f;}} /* slivers */
    }
    dw4_lobby_collision plain={{wallv,widx,TRIS},{floorv,fidx,TRIS}},indexed=plain;
    assert(!dw4_lobby_collision_index(&indexed));
    for(unsigned n=0;n<20000;n++) {
        float old[3]={rnd(-200,200),rnd(-10,60),rnd(-200,200)};
        float pos_a[3]={old[0]+rnd(-6,6),old[1]+rnd(-3,3),old[2]+rnd(-6,6)},pos_b[3];memcpy(pos_b,pos_a,sizeof pos_b);
        float half=rnd(.5f,4);int wall=n&1,floor=(n>>1)&1;unsigned ra,rb;
        switch(n%3) {
        case 0: ra=dw4_lobby_collision_check(&plain,old,pos_a,half,4,4,wall,floor);rb=dw4_lobby_collision_check(&indexed,old,pos_b,half,4,4,wall,floor);break;
        case 1: ra=dw4_lobby_collision_air(&plain,old,pos_a,half,wall,floor);rb=dw4_lobby_collision_air(&indexed,old,pos_b,half,wall,floor);break;
        default: ra=dw4_lobby_collision_walk(&plain,old,pos_a,half,4,4,wall,floor);rb=dw4_lobby_collision_walk(&indexed,old,pos_b,half,4,4,wall,floor);
        }
        assert(ra==rb && !memcmp(pos_a,pos_b,sizeof pos_a));
    }
    free(indexed.wall.bounds);free(indexed.floor.bounds);
    puts("lobby collision: bounds prefilter equals the full scan on 20000 random queries (tiny, huge and sliver triangles)");
}
/* Dynamic prop walls (beHitLandModelInfo kind 0x402): a box proxy of a model instance, moved by the matrix the instance has now. */
static float dyn_matrix[16];static int dyn_active;static unsigned dyn_asked;
static int dyn_pose(void *user,unsigned index,float world[16])
{
    (void)user;dyn_asked++;
    if(!dyn_active || index!=0)return 0;
    memcpy(world,dyn_matrix,sizeof dyn_matrix);return 1;
}
static int dyn_last_only(void *user,unsigned index,float world[16])
{
    if(index!=*(unsigned *)user)return 0;
    memset(world,0,64);world[0]=world[5]=world[10]=world[15]=1;world[12]=50;return 1;
}
static void matrix_set(float m[16],float tx,float ty,float tz,int quarter_turn)
{
    memset(m,0,16*sizeof *m);m[5]=m[15]=1;
    if(quarter_turn){m[2]=-1;m[8]=1;}else m[0]=m[10]=1;   /* row-vector convention: local (x,y,z) -> (z,y,-x) */
    m[12]=tx;m[13]=ty;m[14]=tz;
}
/* A box x,z in [x0,x1] x [-5,5], y 0..50, four outward-facing sides of two triangles (the pack's proxies). */
static void box_build(float v[8*3],uint32_t idx[8*3],float x0,float x1)
{
    const float c[8][3]={{x0,0,-5},{x0,50,-5},{x1,50,-5},{x1,0,-5},{x0,0,5},{x0,50,5},{x1,50,5},{x1,0,5}};   /* 0..3 on z=-5, 4..7 on z=5 */
    /* the z=-5, x0, z=5 and x1 faces, each two triangles */
    static const unsigned tri[4][6]={{0,1,2,2,3,0},{4,5,1,1,0,4},{7,6,5,5,4,7},{3,2,6,6,7,3}};
    for(unsigned i=0;i<8;i++)memcpy(v+3*i,c[i],sizeof c[i]);
    for(unsigned f=0;f<4;f++)for(unsigned k=0;k<6;k++)idx[6*f+k]=tri[f][k];
}
static void dynamic_walls(void)
{
    float v[8*3];uint32_t idx[8*3];
    box_build(v,idx,-5,5);
    dw4_dynamic_wall node={{v,idx,8},{-7.07f,0,-7.07f,7.07f,50,7.07f},"g_test",0};
    dw4_lobby_collision c={{0}};
    c.dynamic=&node;c.ndynamic=1;c.pose=dyn_pose;
    matrix_set(dyn_matrix,50,0,0,0);dyn_active=1;
    float old[3]={30,0,0},pos[3]={44,0,0};
    /* the player (flag 7), an enemy-style flag (11), an NPC (3) and a bullet (2051) take the prop; the short form (no flag) and flag 1 do not */
    static const unsigned solid[]={7,11,3,2051};
    for(unsigned k=0;k<sizeof solid/sizeof *solid;k++) {
        memcpy(pos,(float[]){44,0,0},sizeof pos);
        assert(dw4_lobby_collision_check_for(&c,solid[k],old,pos,3,4,4,1,0)&1);
        assert(fabsf(pos[0]-(50-5-3*1.42f))<.05f && pos[1]==0 && pos[2]==0);   /* stopped at the face, one body radius away */
    }
    memcpy(pos,(float[]){44,0,0},sizeof pos);assert(!dw4_lobby_collision_check(&c,old,pos,3,4,4,1,0) && pos[0]==44);
    memcpy(pos,(float[]){44,0,0},sizeof pos);assert(!dw4_lobby_collision_check_for(&c,0,old,pos,3,4,4,1,0) && pos[0]==44);
    memcpy(pos,(float[]){44,0,0},sizeof pos);assert(!dw4_lobby_collision_check_for(&c,1,old,pos,3,4,4,1,0) && pos[0]==44);
    memcpy(pos,(float[]){44,0,0},sizeof pos);assert(!dw4_lobby_collision_check_for(&c,7,old,pos,3,4,4,0,0) && pos[0]==44);   /* no wall query */
    /* one-sided: from inside the box outward the face does not stop the ray */
    {float in[3]={50,0,0},out[3]={58,0,0};assert(!dw4_lobby_collision_check_for(&c,7,in,out,3,4,4,1,0) && out[0]==58);}
    /* a moved prop: the box stands where the matrix puts it now */
    matrix_set(dyn_matrix,90,0,0,0);
    memcpy(pos,(float[]){44,0,0},sizeof pos);assert(!dw4_lobby_collision_check_for(&c,7,old,pos,3,4,4,1,0) && pos[0]==44);
    old[0]=70;pos[0]=84;assert(dw4_lobby_collision_check_for(&c,7,old,pos,3,4,4,1,0)&1 && fabsf(pos[0]-(90-5-3*1.42f))<.05f);
    /* above the prop (the ray height is the position plus the down range) the box is gone */
    {float hi_old[3]={70,60,0},hi_pos[3]={84,60,0};assert(!dw4_lobby_collision_check_for(&c,7,hi_old,hi_pos,3,4,4,1,0) && hi_pos[0]==84);}
    /* an inactive instance (never generated, erased or broken) is no wall, wherever its matrix says it is */
    dyn_active=0;old[0]=70;pos[0]=84;assert(!dw4_lobby_collision_check_for(&c,7,old,pos,3,4,4,1,0) && pos[0]==84);
    dyn_active=1;
    /* retail's prefilter (FUN_00388640) is the proxy's local bound plus the matrix translation only, never rotated: a 100 unit wall (x -5..95) turned a
     * quarter turn runs along -z, but only the strip of its unrotated box (|z| <= 7.07 around the translation) is ever tested, so the walker in that strip is stopped and
     * the one beside the turned wall passes through it. */
    float lv[8*3];uint32_t li[8*3];
    box_build(lv,li,-5,95);
    dw4_dynamic_wall wall={{lv,li,8},{-7.07f,0,-7.07f,97.07f,50,7.07f},"g_wall",0};
    c.dynamic=&wall;matrix_set(dyn_matrix,0,0,0,1);
    {float o[3]={-30,0,-1},p[3]={-3,0,-1};   /* the world box is x -5..5, z -95..5: z=-1 is inside the strip */
     assert(dw4_lobby_collision_check_for(&c,7,o,p,3,4,4,1,0)&1 && p[0]<-5-3*1.42f+.05f);}
    {float o[3]={-30,0,-50},p[3]={-3,0,-50};   /* the turned wall is really here, but the unrotated prefilter box is not: retail walks through */
     assert(!dw4_lobby_collision_check_for(&c,7,o,p,3,4,4,1,0) && p[0]==-3);}
    /* more nodes than the query's stack holds: only the last one is live */
    enum{MANY=300};static dw4_dynamic_wall many[MANY];
    for(unsigned i=0;i<MANY;i++)many[i]=node;
    unsigned live=MANY-1;
    c.dynamic=many;c.ndynamic=MANY;c.pose=dyn_last_only;c.pose_user=&live;
    {float o[3]={30,0,0},p[3]={44,0,0};assert(dw4_lobby_collision_check_for(&c,7,o,p,3,4,4,1,0)&1 && fabsf(p[0]-(50-5-3*1.42f))<.05f);}
    live=MANY;{float o[3]={30,0,0},p[3]={44,0,0};assert(!dw4_lobby_collision_check_for(&c,7,o,p,3,4,4,1,0) && p[0]==44);}
    /* no pose reader: nothing is solid */
    c.pose=NULL;{float o[3]={30,0,0},p[3]={44,0,0};assert(!dw4_lobby_collision_check_for(&c,7,o,p,3,4,4,1,0) && p[0]==44);}
    puts("lobby collision: dynamic prop walls block by check flag while their instance is live, follow the matrix, keep retail's translation-only prefilter");
}
#define Y(v) ((v)+20.f)   /* the fixture floor sits above y 1: the retail reply treats a floor below height 1 as no floor at all */
int main(void)
{
    differential();
    dynamic_walls();
    /* A sloping floor bounded by x=0..20, with a wall at x=10. */
    const float floor[]={0,20,0, 20,22,0, 20,22,20, 0,20,0, 20,22,20, 0,20,20};
    const float wall[]={10,20,0,10,40,20,10,40,0,10,20,0,10,20,20,10,40,20};   /* faces -x: retail walls block only motion against their face normal */
    uint32_t indices[]={0,1,2,3,4,5};
    dw4_lobby_collision c={{wall,indices,2},{floor,indices,2}};
    float old[]={8,Y(.8f),5},pos[]={9,Y(.8f),6};
    assert(dw4_lobby_collision_move(&c,old,pos,1,4,4)&1);
    assert(pos[0]<8.59f && pos[2]<6); /* held back from the wall; the motion along the heading is cancelled (no slide) */
    assert(pos[1]>Y(.8f) && pos[1]<Y(1)); /* four-corner floor height */
    {float target[]={9,Y(.8f),6};
        assert(!dw4_lobby_collision_check(&c,old,target,1,4,4,0,1));
        assert(target[0]==9 && target[1]>Y(.8f));
        target[0]=30;target[1]=Y(20);
        assert(!dw4_lobby_collision_check(&c,old,target,1,4,4,0,0) && target[0]==30 && target[1]==Y(20));
        target[0]=9;target[1]=Y(.8f);
        assert(dw4_lobby_collision_check(&c,old,target,1,4,4,1,0)==1);
        assert(target[0]<8.59f && target[1]==Y(.8f));
    }
    c.wall.count=0;
    memcpy(old,pos,sizeof old);pos[0]=30;
    /* No floor below at all (x 30 is past the floor): retail reports the model supported and not landed (the solver's y -1 sentinel), so it keeps its
     * height and walks on in the air; nothing holds it at the edge and nothing starts SQ_FALL. */
    assert(!dw4_lobby_collision_move(&c,old,pos,1,4,4) && pos[0]==30 && pos[1]==old[1]);
    pos[0]=30;
    assert(!dw4_lobby_collision_walk(&c,old,pos,1,4,4,0,1) && pos[0]==30 && pos[1]==old[1]);
    pos[0]=15;pos[1]=old[1];pos[2]=10;
    assert(!dw4_lobby_collision_move(&c,old,pos,1,4,4));
    assert(fabsf(pos[1]-Y(1.6f))<0.001f); /* highest supported corner */
    pos[0]=15;old[1]=Y(20);
    assert(dw4_lobby_collision_move(&c,old,pos,1,4,4)&2); /* a floor exists below but outside the window: unsupported (SQ_FALL) */
    old[0]=pos[0]=15;old[2]=pos[2]=10;old[1]=Y(5);pos[1]=Y(6);
    assert(!dw4_lobby_collision_air(&c,old,pos,1,0,1) && pos[1]==Y(6)); /* ascent never snaps */
    pos[1]=Y(4);assert(!dw4_lobby_collision_air(&c,old,pos,1,0,1) && pos[1]==Y(4)); /* still airborne */
    old[1]=Y(2);pos[1]=Y(1);
    assert(dw4_lobby_collision_air(&c,old,pos,1,0,1)==4 && fabsf(pos[1]-Y(1.6f))<.001f);
    old[1]=Y(2);pos[1]=Y(1);assert(!dw4_lobby_collision_air(&c,old,pos,1,0,0) && pos[1]==Y(1));
    pos[0]=30;pos[1]=Y(1);assert(!dw4_lobby_collision_air(&c,old,pos,1,0,1) && pos[0]==30 && pos[1]==Y(1));
    /* the void below: a falling model with nothing to land on keeps falling to y 0, where the delivery layer lands it on the y 0 plane; there it is
     * supported again and keeps walking (the jump or charge attack after an air walk drops to the bottom of the map) */
    old[0]=pos[0]=30;old[1]=2;pos[1]=-1;assert(dw4_lobby_collision_air(&c,old,pos,1,0,1)==4 && pos[1]==0);
    old[1]=pos[1]=0;pos[0]=35;assert(!dw4_lobby_collision_walk(&c,old,pos,1,4,4,0,1) && pos[1]==0 && pos[0]==35);
    old[1]=pos[1]=-3;pos[0]=35;assert(dw4_lobby_collision_walk(&c,old,pos,1,4,4,0,1)==4 && pos[1]==0);   /* below y 0 it snaps to the plane and lands */
    /* a floor below height 1 is no floor to the reply either */
    {const float low[]={0,.5f,0, 20,.5f,0, 20,.5f,20, 0,.5f,0, 20,.5f,20, 0,.5f,20};
     dw4_lobby_collision d={{wall,indices,0},{low,indices,2}};float o[]={8,.5f,5},q[]={9,.5f,6};
     assert(!dw4_lobby_collision_walk(&d,o,q,1,4,4,0,1) && q[1]==.5f);}   /* supported at its own height, not snapped onto the .5 floor */
    puts("lobby collision: wall sliding, slopes, unsupported edges, the void air walk and vertical walking limits OK");
    return 0;
}
