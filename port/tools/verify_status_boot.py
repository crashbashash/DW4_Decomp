#!/usr/bin/env python3
"""Normal title/create/lobby/STATUS route with real scene and authored UI owners."""
import argparse
import os
import subprocess
import tempfile
from pathlib import Path
from verify_frontend import png_rows
p=argparse.ArgumentParser();p.add_argument('--roms',default='../../local/extracted');p.add_argument('--tool',default='build/dw4');p.add_argument('--out-dir');p.add_argument('--dialogue-button',choices=('cross','circle'),default='cross');a=p.parse_args()
script=('5:start,70:start,130:cross,300:cross,345:cross,395:cross,410:right,420:right,432:cross,448:start,500:cross,530:cross,580:start,600:cross')
script+=','+','.join(f'{i}:{a.dialogue_button}' for i in range(1000,1900,10))
script+=(',1100:start,2400:start,2600:cross,2800:cross,3000:circle,3200:circle,'
         '3400:down,3500:cross,3700:cross,3900:circle,4100:circle,4300:down,'
         '4400:cross,4600:circle,4800:circle,5100:start,5400:circle')
with tempfile.TemporaryDirectory(prefix='dw4-status-boot-') as tmp:
    out=Path(a.out_dir or tmp);out.mkdir(parents=True,exist_ok=True)
    env=dict(os.environ,DW4_STATUS_TRACE='1')
    r=subprocess.run([a.tool,'--roms',a.roms,'--boot','--headless','--software','--frames','5700',
        '--w','320','--h','224','--input-script',script,'--out-dir',str(out)],env=env,capture_output=True,text=True)
    text=r.stdout+r.stderr
    if a.out_dir:(out/'trace.log').write_text(text)
    assert r.returncode==0,text[-8000:]
    assert text.count('session generator roster: 0 authored infos')==2,text[-8000:]
    assert text.count('STATUS: accepted Start for player 0')==2,text[-8000:]
    assert text.count('STATUS: root closed; world/NPC clocks preserved; health/HUD restored')==2,text[-8000:]
    assert 'world_visible 0' in text,text[-8000:]
    for model in ('i_stsoubi','i_stfolder','i_sttitle'):
        assert f'STATUS model {model} ' in text,model
    w,h,bpp,rows=png_rows(out/'frame_2550.png');assert (w,h)==(320,224)
    ink=sum(all(rows[y][bpp*x+c]>180 for c in range(3)) for y in range(10,39) for x in range(115,175))
    assert ink>90,('root labels absent',ink)
    print(f'normal STATUS boot ({a.dialogue_button} dialogue): post-intro admission, authored root text, equipment/DEVICE/skill views, two actual closes and world/NPC/health/HUD restoration pass')
