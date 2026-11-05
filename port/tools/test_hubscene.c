#include "dw4/lobby.h"
#include "dw4/png.h"
#include "dw4/igfile.h"
#include "dw4/playerpoint.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char **argv)
{
    dw4_mount m;assert(!dw4_mount_open(&m,argc>1?argv[1]:"../local/extracted"));
    const char *stages[]={"stagML11","stagML12","stagML13"};
    dw4_fb fb;assert(!dw4_fb_init(&fb,320,224));
    static const unsigned regions[]={17,37,24},entries[]={820,824,828};
    uint64_t hashes[3]={0};
    for(unsigned i=0;i<3;i++) {
        dw4_igfile model={0},sound={0};
        assert(!dw4_igfile_open_stage_pack(&model,&m,stages[i],0,0));
        assert(!dw4_igfile_open_stage_pack(&sound,&m,stages[i],1,0));
        uint32_t bytes;assert(model.data==dw4_mount_entry(&m,0,entries[i],&bytes,NULL) && model.len==bytes);
        assert(sound.data==dw4_mount_entry(&m,0,entries[i]-1,&bytes,NULL) && sound.len==bytes);
        dw4_igfile_close(&sound);
        dw4_lobby *l=dw4_lobby_open_stage(&m,0,"HubTest",stages[i],0);
        if(!l){fprintf(stderr,"hub scene failed: %s\n",stages[i]);return 1;}
        dw4_lobby_world_state info;assert(!dw4_lobby_world_info(l,&info));
        assert(!strcmp(info.stage,stages[i]) && info.arrival_point==0 && info.materials && info.floor_triangles && info.wall_triangles);
        assert(info.camera_regions==regions[i]);
        if(i==0)assert(info.floor_triangles==226 && info.wall_triangles==286);
        assert(dw4_lobby_draw(l,&fb,0,NULL)>0);
        /* Unpublished worlds retain the real black startup fade. Only the
         * explicit asset diagnostic omits that fade; this is not gameplay. */
        for(unsigned p=0;p<320*224;p++)assert(!fb.rgba[4*p] && !fb.rgba[4*p+1] && !fb.rgba[4*p+2]);
        int triangles=dw4_lobby_draw_environment(l,&fb);assert(triangles>0);
        printf("hub scene %s: %d submitted triangles; %u camera regions; floor %u/wall %u triangles\n",stages[i],triangles,info.camera_regions,info.floor_triangles,info.wall_triangles);
        uint64_t hash=1469598103934665603ULL;
        for(unsigned p=0;p<320*224*4;p++)hash=(hash^fb.rgba[p])*1099511628211ULL;
        hashes[i]=hash;
        assert(dw4_lobby_draw_environment(l,&fb)==triangles);
        uint64_t repeated=1469598103934665603ULL;
        for(unsigned p=0;p<320*224*4;p++)repeated=(repeated^fb.rgba[p])*1099511628211ULL;
        assert(repeated==hash);
        if(argc>2){char path[512];snprintf(path,sizeof path,"%s/%s.png",argv[2],stages[i]);assert(!dw4_png_write(path,fb.rgba,fb.w,fb.h));}
        dw4_lobby_close(l);
        for(int point=1;point<=2;point++) {
            l=dw4_lobby_open_stage(&m,0,"HubTest",stages[i],point);assert(l);
            float matrix[16];assert(!dw4_playerpoint_matrix(model.data,model.len,point,0,matrix));
            dw4_lobby_walk_state player;assert(!dw4_lobby_walk(l,&player));
            assert(!memcmp(player.position,matrix+12,sizeof player.position));
            assert(!dw4_lobby_world_info(l,&info) && info.arrival_point==point);
            dw4_lobby_close(l);
        }
        dw4_igfile_close(&model);
    }
    assert(hashes[0]!=hashes[1] && hashes[1]!=hashes[2] && hashes[0]!=hashes[2]);
    puts("hub preparation: three distinct authored environments, real model/support ownership, dynamic camera bounds, collision graphs, return points and read-only diagnostic rendering pass; gameplay publication remains separate");
    dw4_fb_free(&fb);dw4_mount_close(&m);return 0;
}
