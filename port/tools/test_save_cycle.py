#!/usr/bin/env python3
"""End-to-end save cycle on the headless engine: create a character, save it at the Save Keeper, quit, relaunch and
call it back from the title's Call Digimon chooser into the Terminal.

  tools/test_save_cycle.py [--roms DIR] [--tool build/dw4]

Uses a throw-away $XDG_DATA_HOME so the real save library is never touched.  Exit status 1 on any failed expectation.
"""
import argparse
import os
import subprocess
import sys
import tempfile

# Create (LoadIntf2 states 4, 5 and GAMESTART in the slot scene): Dorumon, name "ac", Yes, START at the log-in prompt.
ROUTE = ('5:start,70:start,130:cross,300:cross,345:cross,395:cross,410:right,420:right,432:cross,448:start,500:cross,'
         '530:cross,580:start')
SAVE_CROSSES = ''.join(',%d:cross' % f for f in range(1700, 3500, 120))
CALL_ROUTE = '5:cross,200:start,260:cross,400:down,440:cross,600:cross,760:cross,900:start'

p = argparse.ArgumentParser()
p.add_argument('--roms', default='../../local/extracted')
p.add_argument('--tool', default='build/dw4')
a = p.parse_args()


def run(env_extra, script, frames, out):
    env = dict(os.environ, **env_extra)
    cmd = [a.tool, '--roms', a.roms, '--boot', '--window', '--headless', '--w', '640', '--h', '480', '--frames', str(frames),
           '--loading-min-seconds', '0', '--mute', '--input-script', script, '--out-dir', out]
    r = subprocess.run(cmd, env=env, capture_output=True, text=True, timeout=600)
    return r.stdout + r.stderr


def slots(path):
    with open(path, 'rb') as f:
        d = f.read()
    return [d[8 + s * 0x2000] for s in range(4)]


bad = []
with tempfile.TemporaryDirectory() as tmp:
    out = os.path.join(tmp, 'out')
    os.makedirs(out)
    env = {'XDG_DATA_HOME': tmp, 'DW4_SHOT_FRAMES': '0'}
    file = os.path.join(tmp, 'dw4', 'saves', 'BASLUS-20836savedata')
    text = run(dict(env, DW4_DEV_WARP='StagML12:0,stagIS12:0', DW4_DEV_WARP_FRAMES='300'), ROUTE + SAVE_CROSSES, 3500, out)
    if 'stagIS12 point 0' not in text:
        bad.append('the Save Keeper scene was not reached')
    if not os.path.exists(file):
        bad.append('no save file was written')
    elif slots(file)[0] != 1:
        bad.append('slot 1 of the save file is empty after the save')
    text = run(env, CALL_ROUTE, 1700, out)
    for need in ('Call Digimon -> memory card chooser', 'called ', 'loading: called ', 'entering the first playable stage'):
        if need not in text:
            bad.append('relaunch did not report: ' + need)
if bad:
    sys.exit('save cycle FAILED:\n  ' + '\n  '.join(bad))
print('save cycle: saved at the Save Keeper, relaunched, called from the chooser into the Terminal')
