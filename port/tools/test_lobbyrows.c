/* All sixteen player models stand in the Terminal: each shinka row opens, finishes its arrival, walks and draws (the starters, then the
 * twelve evolved forms with an equipped weapon asset). */
#include "dw4/lobby.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dw4/png.h"
int main(int argc,char **argv)
{
    dw4_mount mount;assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../../local/extracted"));
    dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));
    char weapon[32]={0};
    {   /* dorumon's created-card weapon is the equipped weapon every other form is given */
        dw4_lobby *l=dw4_lobby_open_row_stage(&mount,3,"ROW","stagML11",0,NULL);assert(l);
        dw4_lobby_player_state st;assert(!dw4_lobby_player(l,&st));snprintf(weapon,sizeof weapon,"%s",st.weapon_asset);dw4_lobby_close(l);
    }
    for(int row=0;row<16;row++){
        dw4_lobby *l=getenv("DW4_LOBBYROWS_UNARMED") && row>=4 ? dw4_lobby_open_row_stage_unarmed(&mount,row,"ROW","stagML11",0)
            : dw4_lobby_open_row_stage(&mount,row,"ROW","stagML11",0,row<4?NULL:weapon);
        if(!l){fprintf(stderr,"row %d (%s) did not open\n",row,dw4_lobby_model_name(row));assert(0);}
        dw4_lobby_input(l,1,0);
        for(unsigned i=0;!dw4_lobby_intro_done(l) && i<2500;i++)dw4_lobby_tick(l,1);
        if(!dw4_lobby_intro_done(l)||dw4_lobby_script_error(l)[0]){fprintf(stderr,"row %d (%s): %s\n",row,dw4_lobby_model_name(row),dw4_lobby_script_error(l));assert(0);}
        if(getenv("DW4_LOBBYROWS_IDLE"))dw4_lobby_input(l,0,0);
        for(unsigned i=0;i<(getenv("DW4_LOBBYROWS_IDLE")?240u:60u);i++)dw4_lobby_tick(l,0);
        dw4_lobby_walk_state w;assert(!dw4_lobby_walk(l,&w));
        assert(dw4_lobby_draw(l,&fb,0,NULL)>=0);
        if(getenv("DW4_LOBBYROWS_FRAMES")){char path[512];snprintf(path,sizeof path,"%s/row%02d.png",getenv("DW4_LOBBYROWS_FRAMES"),row);assert(!dw4_png_write(path,fb.rgba,fb.w,fb.h));}
        printf("lobby row %2d %-11s ok (motion %s)\n",row,dw4_lobby_model_name(row),w.motion);
        dw4_lobby_close(l);
    }
    return 0;
}
