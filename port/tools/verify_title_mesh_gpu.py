#!/usr/bin/env python3
"""Complete title opening/flash/UI composition on hardware vs CPU reference."""
import argparse
import os
from pathlib import Path
import re
import subprocess
import tempfile
import numpy as np
from PIL import Image

p=argparse.ArgumentParser()
p.add_argument('--roms',default='../../local/extracted')
p.add_argument('--tool',default='build/dw4')
a=p.parse_args()
with tempfile.TemporaryDirectory(prefix='dw4-title-mesh-') as tmp:
    outputs=[]
    for mode in ('--software','--gl'):
        out=Path(tmp)/mode[2:];out.mkdir();outputs.append(out)
        r=subprocess.run([a.tool,'--roms',a.roms,'--boot','--headless',mode,'--skip-logos',
            '--frames','300','--fps-lock','0','--no-fps','--w','320','--h','224','--out-dir',str(out)],
            env=dict(os.environ,DW4_GPU_POLICY_TRACE='1'),capture_output=True,text=True)
        assert r.returncode==0,(r.stdout+r.stderr)[-8000:]
        if mode=='--gl':
            assert 'hardware GPU required' in r.stdout
            assert re.search(r'GPU policy CPU audit: UI 0 layer 0 mesh 0 fill 0 composite 0',r.stderr),r.stderr[-4000:]
    worst_mean=worst_far=0
    for frame in range(300):
        cpu=np.array(Image.open(outputs[0]/f'frame_{frame:04d}.png'))[:,:,:3].astype(int)
        gpu=np.array(Image.open(outputs[1]/f'frame_{frame:04d}.png'))[:,:,:3].astype(int)
        delta=abs(cpu-gpu);mean=float(delta.mean());far=float((delta.max(2)>4).mean()*100)
        assert mean<=1 and far<=1,(frame,mean,far)
        worst_mean=max(worst_mean,mean);worst_far=max(worst_far,far)
    print(f'Title GPU: 300 composed frames, zero CPU calls; max RGB mean {worst_mean:.4f}, >4/channel {worst_far:.3f}% (CPU reference, not retail pixel parity)')
