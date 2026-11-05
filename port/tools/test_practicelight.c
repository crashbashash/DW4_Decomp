/* The practice stage's additive floor-grid overlays are dim in retail.  Retail's VU1 program CALC_INFINITE_4 rotates the packed light
 * block in place on every draw that follows a hardware matrix upload (a texture-matrix transform, leaving a texture-matrix scope), and
 * the EE re-sends the eye-space block only after a model-view upload, so the k-th draw after a fresh block is lit with the light turned
 * k further times.  stag0001's BG02 floor: ground00 and the draws up to node 2180 are k = 0 (127, saturated), node 2184 k = 1, node 2186
 * k = 2, nodes 2189 and 2191 k = 3.  The retail GS dump has the overlays at (96,87,109), (37,30,50) and (40,33,53) (alpha 128); the
 * port drew all of them (127,127,127,128), 2.5-5x too bright.  The per-channel tolerance is 1: the port's floor quantiser gives
 * (95,86,108) and (40,33,52) for two of them and is deliberately not tuned. */
#include "hubtest.h"
#include "dw4/lobby.h"
#include "dw4/igfile.h"
#include "dw4/scene.h"

static int close_to(const uint8_t *got, int r, int g, int b)
{return abs(got[0]-r)<=1 && abs(got[1]-g)<=1 && abs(got[2]-b)<=1 && got[3]==128;}
static int flat(const uint8_t rgba[3][4])
{return !memcmp(rgba[0],rgba[1],4) && !memcmp(rgba[0],rgba[2],4);}

int main(int argc,char **argv)
{
    const char *root=argc>1?argv[1]:"../../local/extracted";
    dw4_mount mount;assert(!dw4_mount_open(&mount,root));
    /* The scene walk: the per-mesh rotation count k, read straight off the loaded stage graph. */
    {
        dw4_igfile gf={0};static dw4_scene s;
        assert(!dw4_igfile_open_stage_pack(&gf,&mount,"stag0001",0,0));assert(!dw4_scene_load_world(&s,gf.data,gf.len));
        static const struct {uint32_t node,k;} want[]={{2174,0},{2176,0},{2179,0},{2180,0},{2184,1},{2186,2},{2189,3},{2191,3},{2195,0},{2197,0},{2199,0}};
        for(unsigned i=0;i<sizeof want/sizeof *want;i++) {
            fprintf(stderr,"practice light: node %u k=%u (want %u)\n",want[i].node,dw4_scene_node_light_rot(&s,want[i].node),want[i].k);
            assert(dw4_scene_node_light_rot(&s,want[i].node)==want[i].k);
        }
        dw4_scene_close(&s);
    }
    dw4_playerrecords *players=dw4_playerrecords_open();dw4_be_state state;dw4_be_init(&state);
    struct boot host={players,dw4_scriptservices_open()};assert(players && host.sd);
    assert(dw4_scriptservices_register(host.sd,0,"GAMERAM",NULL,-1,1,dw4_playerrecords_service,players));
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&host);dw4_filelist *f=dw4_filelist_open(&mount);assert(e && f);
    dw4_scriptengine_filelist(e,f);
    assert(!dw4_filelist_begin(f,e,"stagIS10",1));assert(!dw4_filelist_shared(f));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(f,dw4_stageobjects_route,objects));assert(!dw4_filelist_bind_layers(f,dw4_stageobjects_bind_layers,objects));
    char error[512];dw4_databases *db=dw4_databases_open(objects,error,sizeof error);assert(db);
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","Prac",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};
    dw4_hubruntime *h=dw4_hubruntime_prepare(&mount,&initial,"stag0001",0,1,error,sizeof error);assert(h);
    unsigned t=0;for(;t<3000 && !has_text(h,"TALKFONT05","font00");t++)step(h,0,t%60==59?0x4000:0);
    assert(t<3000);idle(h,60);
    dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));assert(dw4_hubruntime_draw(h,&fb,NULL)>0);
    unsigned n=0;const dw4_layer_draw *d=dw4_lobby_last_draws(dw4_hubruntime_world(h),&n);assert(d && n>0);

    /* The additive draws with one dim constant colour, in draw order (the UI's additive draws are 127 or per-vertex): the four overlay
     * meshes, one run of equal colour and texture each.  Nodes 2184 and 2186 share a 64x32 texture and differ in colour. */
    struct {int w,h;uint8_t rgba[4];unsigned draws;} run[8];unsigned nrun=0;
    unsigned flat127=0,ambient=0,other_add=0;
    for(unsigned i=0;i<n;i++) {
        const dw4_layer_draw *x=&d[i];
        if(x->blend!=2) {
            if(flat(x->rgba) && x->rgba[0][0]==127 && x->rgba[0][1]==127 && x->rgba[0][2]==127 && x->rgba[0][3]==128)flat127++;
            if(flat(x->rgba) && x->rgba[0][0]==31 && x->rgba[0][1]==25 && x->rgba[0][2]==44 && x->rgba[0][3]==128)ambient++;
            continue;
        }
        if(!flat(x->rgba) || (x->rgba[0][0]==127 && x->rgba[0][1]==127 && x->rgba[0][2]==127)) {other_add++;continue;}
        if(nrun && run[nrun-1].w==x->tex->w && run[nrun-1].h==x->tex->h && !memcmp(run[nrun-1].rgba,x->rgba[0],4)){run[nrun-1].draws++;continue;}
        assert(nrun<8);
        run[nrun].w=x->tex->w;run[nrun].h=x->tex->h;memcpy(run[nrun].rgba,x->rgba[0],4);run[nrun].draws=1;nrun++;
    }
    for(unsigned i=0;i<nrun;i++)fprintf(stderr,"practice light: dim additive run %u: %dx%d (%u,%u,%u,%u) x%u draws\n",i,run[i].w,run[i].h,run[i].rgba[0],run[i].rgba[1],run[i].rgba[2],run[i].rgba[3],run[i].draws);
    assert(nrun==4);
    assert(run[0].w==64 && run[0].h==32 && close_to(run[0].rgba,96,87,109));   /* node 2184, k = 1 */
    assert(run[1].w==64 && run[1].h==32 && close_to(run[1].rgba,37,30,50));    /* node 2186, k = 2 */
    assert(close_to(run[2].rgba,40,33,53));                                    /* node 2189, k = 3 */
    assert(close_to(run[3].rgba,40,33,53));                                    /* node 2191, k = 3 */
    assert(run[2].w*run[2].h!=run[3].w*run[3].h);

    /* k = 0 is untouched: the ordinary floor (ground00, saturated 127), the ambient-only walls and every other draw keep their colour.
     * These counts were taken from the port before the rotation existed, when ground00 matched the retail dump vertex for vertex. */
    fprintf(stderr,"practice light: non-additive flat 127 draws %u, ambient-only (31,25,44) draws %u, other additive %u\n",flat127,ambient,other_add);
    assert(flat127==643 && ambient==799);

    /* The picture: the green the grid used to add over the floor at x 380..500, y 120..200 (green minus the larger of red and blue;
     * retail max 36, mean 4.0; before the rotation max 178, mean 10.4). */
    {
        unsigned peak=0;double sum=0;unsigned cnt=0;
        for(int y=120;y<=200;y++)for(int x=380;x<=500;x++) {
            const uint8_t *p=fb.rgba+4*((size_t)y*640+x);int m=p[0]>p[2]?p[0]:p[2];int g=p[1]-m;if(g<0)g=0;
            if((unsigned)g>peak)peak=(unsigned)g;sum+=g;cnt++;
        }
        fprintf(stderr,"practice light: green excess x380..500 y120..200: max %u, mean %.2f (retail max 36, mean 4.0; before max 178, mean 10.4)\n",peak,sum/cnt);
        assert(peak<=60 && sum/cnt<=5.5);
    }
    dw4_fb_free(&fb);dw4_hubruntime_close(h);
    puts("practice light: the floor-grid overlays are lit with the VU1's rotated light");
    return 0;
}
