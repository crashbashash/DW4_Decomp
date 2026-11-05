/* The save scene host: stagIS12 prepares through the original pack/Lua, SaveCtrl and SaveIntf run on real MODELCTRL/
 * TEXTCTL services, and the scripted pad drives a character through the save to the card. Headless. */
#include "savetest.h"

int main(int argc,char **argv)
{
    capture_dir=argc>2?argv[2]:NULL;
    dw4_mount mount;assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../../local/extracted"));
    dw4_playerrecords *players=dw4_playerrecords_open();dw4_be_state state;dw4_be_init(&state);
    struct boot host={players,dw4_scriptservices_open()};assert(players && host.sd);
    assert(dw4_scriptservices_register(host.sd,0,"GAMERAM",NULL,-1,1,dw4_playerrecords_service,players));
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&host);dw4_filelist *f=dw4_filelist_open(&mount);assert(e && f);
    dw4_scriptengine_filelist(e,f);
    assert(!dw4_filelist_begin(f,e,"stagIS10",1));assert(!dw4_filelist_shared(f));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(f,dw4_stageobjects_route,objects));assert(!dw4_filelist_bind_layers(f,dw4_stageobjects_bind_layers,objects));
    char error[512];dw4_databases *db=dw4_databases_open(objects,error,sizeof error);assert(db);
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","SaveScn",error,sizeof error));
    char dir[]="/tmp/dw4-savescene-XXXXXX";assert(mkdtemp(dir));
    dw4_memcard *card=dw4_memcard_open(dir);assert(card && dw4_memcard_ready(card));
    dw4_savescene_source src={players,&state,0,card};
    dw4_savescene *s=dw4_savescene_open(&mount,&src,error,sizeof error);
    if(!s){fprintf(stderr,"open: %s\n",error);assert(0);}
    struct scene_run run;
    assert(!drive_scene(s,0,&run,1));
    assert(!strcmp(run.stage,"stagML12") && run.pos==2);   /* a saved player returns to Central at the Save Keeper's point */
    int32_t ninzu;assert(!dw4_property_number(dw4_playerrecords_get(dw4_savescene_records(s),"GETCOMMON",0),"NINZU",&ninzu) && ninzu==1);
    verify_card(card,dw4_savescene_records(s));
    char bak[600];snprintf(bak,sizeof bak,"%s/%s.bak",dir,DW4_MEMCARD_FILE);assert(!access(bak,R_OK));   /* the previous (empty) file was kept */
    printf("savescene: stagIS12 saved the character to slot 0 in %u ticks, returned stagML12 at point 2; %d frames drawn\n",run.ticks,run.frames);
    dw4_savescene_close(s);
    /* A scene drawn on a shared GPU layer takes its images and font atlases with it: the layer caches uploads by pixel pointer, so entries left
     * behind would draw a later scene's (or card's) texture at the same address with the old image, and the scene's reference must be released. */
    dw4_gl_layer *layer=dw4_gl_layer_open(640,448);
    if(layer) {
        dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));
        dw4_savescene *g=dw4_savescene_open(&mount,&src,error,sizeof error);assert(g && dw4_savescene_use_gpu(g,layer));
        assert(dw4_gl_layer_owners(layer)==2);uint64_t ns=0;
        for(int k=0;k<300;k++){dw4_savescene_input(g,0,0,k%20==0?0x4000:0);ns+=16666667ULL;if(dw4_savescene_tick(g,ns))break;
            if(k%30==29){dw4_gl_layer_clear(layer,&fb,0,0,0,255);assert(dw4_savescene_draw(g,&fb)>=0);}}
        int cached=dw4_gl_layer_cached_textures(layer);assert(cached>0);
        dw4_savescene_close(g);
        printf("savescene: shared GPU layer held %d textures and 2 owners while open, %d and %d after the close\n",cached,dw4_gl_layer_cached_textures(layer),dw4_gl_layer_owners(layer));
        assert(dw4_gl_layer_cached_textures(layer)==0 && dw4_gl_layer_owners(layer)==1);
        dw4_fb_free(&fb);dw4_gl_layer_close(layer);
    } else puts("savescene: no GPU layer here, the shared-layer cache check is skipped");
    dw4_memcard_close(card);remove_dir(dir);
    return 0;
}
