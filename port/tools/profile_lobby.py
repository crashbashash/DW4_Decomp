#!/usr/bin/env python3
"""Profile the lobby's per-frame CPU cost headlessly (no display, no GPU needed).

Boots through the title with a scripted pad into the Main Lobby, lets the first-arrival introduction and the
Digi-Elf greeting dialogue run, and reads the engine's DW4_FRAME_TRACE output.  The headless build draws the
world on the software path, so only the CPU-side figures are meaningful: scene-node driving, the mesh loop
(poses, instance sampling), and the lobby tick.  The GPU passes and the UI show up here as software cost and are
reported but not judged.

  tools/profile_lobby.py [--roms DIR] [--frames N] [--budget-ms X]

Exit status 1 when the CPU-side cost per frame (node-drive + mesh-loop + tick) exceeds --budget-ms.
"""
import argparse
import os
import re
import subprocess
import sys

ROUTE = ('5:start,70:start,130:cross,300:cross,345:cross,395:cross,410:right,420:right,432:cross,448:start,500:cross,530:cross,580:start')

p = argparse.ArgumentParser()
p.add_argument('--roms', default='../../local/extracted')
p.add_argument('--tool', default='build/dw4')
p.add_argument('--frames', type=int, default=1400)
p.add_argument('--budget-ms', type=float, default=0.0, help='fail when CPU-side ms/frame exceeds this (0 = report only)')
p.add_argument('--skip', type=int, default=1, help='lobby trace seconds to discard (the arrival spike)')
p.add_argument('--rows', action='store_true', help='print every sampled second (the arrival introduction is the first rows)')
a = p.parse_args()

script = ROUTE + ''.join(',%d:cross' % f for f in range(a.frames - 400, a.frames, 60))
env = dict(os.environ, DW4_FRAME_TRACE='1')
cmd = [a.tool, '--roms', a.roms, '--boot', '--window', '--headless', '--w', '1280', '--h', '960',
       '--frames', str(a.frames), '--loading-min-seconds', '0', '--input-script', script, '--out-dir', '/tmp/dw4-profile']
os.makedirs('/tmp/dw4-profile', exist_ok=True)
r = subprocess.run(cmd, env=env, capture_output=True, text=True)
if r.returncode != 0:
    sys.exit('run failed (%d):\n%s' % (r.returncode, r.stderr[-2000:]))
lines = (r.stdout + r.stderr).splitlines()
rows = []
for i, ln in enumerate(lines):
    m = re.search(r'lobby tick ([\d.]+) draw ([\d.]+)', ln)
    s = re.search(r'draw split: node-drive ([\d.]+) mesh-loop ([\d.]+) \(pose ([\d.]+) instances ([\d.]+)\) shadow ([\d.]+) '
                  r'world ([\d.]+) native-ui ([\d.]+) dialogue/ui ([\d.]+)', ' '.join(lines[i + 1:i + 4]))
    if m and s and float(m[2]) > 0:
        rows.append((float(m[1]),) + tuple(float(x) for x in s.groups()))
if a.rows:
    for k, r_ in enumerate(rows):
        print('s%02d tick %.2f drive %.2f mesh-loop %.2f pose %.2f' % (k, r_[0], r_[1], r_[2], r_[3]))
rows = rows[a.skip:]
if not rows:
    sys.exit('no lobby trace lines (route did not reach the lobby in %d frames)' % a.frames)
names = ['tick', 'node-drive', 'mesh-loop', 'pose', 'instances', 'shadow(sw)', 'world(sw)', 'native-ui(sw)', 'dialogue(sw)']
avg = [sum(r_[k] for r_ in rows) / len(rows) for k in range(len(names))]
for n, v in zip(names, avg):
    print('%-14s %7.2f ms' % (n, v))
cpu = avg[0] + avg[1] + avg[2]
print('CPU-side (tick + node-drive + mesh-loop): %.2f ms over %d sample second(s)' % (cpu, len(rows)))
if a.budget_ms and cpu > a.budget_ms:
    sys.exit('CPU-side %.2f ms exceeds the %.2f ms budget' % (cpu, a.budget_ms))
