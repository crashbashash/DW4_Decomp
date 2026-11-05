#!/usr/bin/env python3
"""Opt-in hardware/display acceptance for normal rendering entry points."""
import argparse
import os
from pathlib import Path
import re
import subprocess
import tempfile

p=argparse.ArgumentParser()
p.add_argument('--roms',default='../../local/extracted')
p.add_argument('--tool',default='build/dw4')
p.add_argument('--present-tool',default='build/test_gpu_present')
a=p.parse_args()
env=dict(os.environ,SDL_VIDEODRIVER='x11',SDL_AUDIODRIVER='dummy',DW4_GPU_POLICY_TRACE='1')
env.pop('SDL_RENDER_DRIVER',None)
zero=r'GPU policy CPU audit: UI 0 layer 0 mesh 0 fill 0 composite 0'
def run(label,args,extra=None,trace=True,success=True):
    result=subprocess.run(args,env=dict(env,**(extra or {})),capture_output=True,text=True)
    output=result.stdout+result.stderr
    assert (result.returncode==0)==success,(label,result.returncode,output[-6000:])
    if trace:assert re.search(zero,output),(label,output[-6000:])
    print(f'GPU entry {label}: pass')
    return output
with tempfile.TemporaryDirectory(prefix='dw4-gpu-entries-') as tmp:
    for mode in ('sdl','vk','vk-reject'):
        run(mode,[a.present_tool,mode],trace=False)
    run('SDL software rejection',[a.present_tool,'sdl-reject'],{'SDL_RENDER_DRIVER':'software'},trace=False)
    base=[a.tool,'--roms',a.roms,'--w','320','--h','224','--fps','--frames','4']
    for presenter in ('--window','--vulkan'):
        run('stage '+presenter,base+['--stage','stag0102.igb',presenter])
        output=run('startup/movie '+presenter,base+['--boot',presenter,'--input-script','6:cross'])
        assert 'boot cards: Bandai' in output and 'played 6 movie frame(s)' in output
    run('standalone movie',[a.tool,'--roms',a.roms,'--movie','aus_opening.sfd','--window','--fps','--input-script','6:cross'])
    run('software GLES rejection',base+['--boot','--gl','--headless','--skip-logos','--out-dir',tmp],
        {'LIBGL_ALWAYS_SOFTWARE':'1'},success=False)
print('GPU entries: normal stage, startup/cards/movie, standalone movie, hardware presentation and rejected software backends pass')
