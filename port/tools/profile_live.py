#!/usr/bin/env python3
"""Live-window frame-rate profile of the connected hub across presentation backends and resolutions.

Opens a real window per configuration, scripts the pad through the title into the Main Lobby, then uses DW4_DEV_WARP to
visit Central, Shop and the Terminal again, and summarises DW4_FRAME_TRACE per stage (loading seconds excluded).
It needs a display and a GPU; it is a measurement tool, not a pass/fail test, unless --min-fps is given.

  tools/profile_live.py [--roms DIR] [--configs vulkan:1280x960,sdl:2560x1440] [--dwell FRAMES] [--min-fps N]

A configuration is <backend>:<WxH> with backend `vulkan` (--vulkan swapchain) or `sdl` (SDL2 renderer).  Pass
SDL_GAMECONTROLLER_IGNORE_DEVICES in the environment when a physical pad is attached.
"""
import argparse
import os
import re
import subprocess
import sys

ROUTE = ('5:start,70:start,130:cross,300:cross,345:cross,395:cross,410:right,420:right,432:cross,448:start,500:cross,530:cross,580:start')
NAMES = {'title': 'Title/menu', 'chr': 'Char/Call', 'login': 'Login', 'options': 'Options', 'loading': 'Loading card',
         'StagML11': 'Terminal', 'StagML12': 'Central', 'StagML13': 'Shop', 'StagML02': 'Commander'}
OPTIONS_ROUTE = '5:cross,150:start,230:down,270:cross'   # title -> Start -> Option, then idle on the Option screen
MENU_ROUTE = '5:cross,200:start'   # skip the FMV, reach the title, press Start and idle on the main menu
CALL_ROUTE = '5:cross,200:start,260:cross,400:down,440:cross,600:cross'   # Game Start -> Call Digimon -> card chooser -> data grid, then idle


def slowed(route, start=300, factor=20):
    """Spread the character-creation presses (frames >= start) apart so each screen stays up for a few seconds."""
    out = []
    for item in route.split(','):
        f, rest = item.split(':', 1) if ':' in item else item.split('+', 1)
        sep = ':' if ':' in item else '+'
        f = int(f)
        out.append('%d%s%s' % (f if f < start else start + (f - start) * factor, sep, rest))
    return ','.join(out)

CREATE_ROUTE = slowed(ROUTE)

p = argparse.ArgumentParser()
p.add_argument('--roms', default='../../local/extracted')
p.add_argument('--tool', default='build/dw4')
p.add_argument('--configs', default='vulkan:2560x1440,sdl:2560x1440', help='the highest resolution is the one that matters')
p.add_argument('--dwell', type=int, default=700, help='frames to stay in each stage before the next warp')
p.add_argument('--warp', default='StagML12:0,StagML13:0,StagML11:1,StagML02:0')
p.add_argument('--menu', action='store_true', help='profile the title and main menu only (no hub warps)')
p.add_argument('--options', action='store_true', help='profile the Option screen only')
p.add_argument('--call', action='store_true', help='profile the Call Digimon screens (card chooser, data select) only; needs a saved character in the save library')
p.add_argument('--create', action='store_true', help='profile character creation, login and the loading card (slowed route, 8 s loading card, no hub warps)')
p.add_argument('--min-fps', type=float, default=0.0, help='fail when a stage averages below this')
a = p.parse_args()

script = CALL_ROUTE if a.call else OPTIONS_ROUTE if a.options else MENU_ROUTE if a.menu else (CREATE_ROUTE if a.create else ROUTE + ''.join(',%d:cross' % f for f in range(900, 1700, 60)))
stage_order = ('chr',) if a.call else ('options',) if a.options else ('title',) if a.menu else (('title', 'chr', 'login', 'loading', 'StagML11') if a.create else ('title', 'chr', 'login', 'loading', 'StagML11', 'StagML12', 'StagML13', 'StagML02'))
failed = False
print('%-18s %-9s %4s %6s %9s %8s %9s %s' % ('config', 'stage', 'sec', 'fps', 'work ms', 'max ms', 'over/s', 'min fps'))
for cfg in a.configs.split(','):
    backend, res = cfg.split(':')
    w, h = res.split('x')
    cmd = [a.tool, '--roms', a.roms, '--skip-logos', '--mute', '--loading-min-seconds', '8' if a.create else '0', '--w', w, '--h', h,
           '--input-script', script]
    if backend == 'vulkan':
        cmd.append('--vulkan')
    elif backend != 'sdl':
        sys.exit('unknown backend %r' % backend)
    env = dict(os.environ, DW4_FRAME_TRACE='1')
    if not a.menu and not a.create and not a.options and not a.call:
        env.update(DW4_DEV_WARP=a.warp, DW4_DEV_WARP_FRAMES=str(a.dwell))
    total = 40 if (a.menu or a.options or a.call) else (110 if a.create else 40 + len(a.warp.split(',')) * (a.dwell // 60 + 8) + 20)
    try:
        r = subprocess.run(cmd, env=env, capture_output=True, text=True, timeout=total)
        text = r.stdout + r.stderr
    except subprocess.TimeoutExpired as e:   # the run is open-ended; the timeout is the normal end
        text = (e.stdout or b'').decode(errors='replace') + (e.stderr or b'').decode(errors='replace')
    lines = text.splitlines()
    stages = {}
    for i, ln in enumerate(lines):
        m = re.search(r'frame-trace: (\d+) frames/s, work avg ([\d.]+) ms max ([\d.]+) ms, (\d+) over.*?(\[(?:partly )?loading\])?$', ln)
        if not m:
            continue
        sl = next((l for l in lines[i + 1:i + 4] if 'stage:' in l), None)
        if not sl:
            continue
        st = re.search(r'stage: (\w+)', sl)[1]
        sc = dict(zip(('title', 'chr', 'login', 'options', 'loading', 'world'), map(int, re.findall(r'(\d+)', sl.split('screens:')[1]))))
        tot = sum(sc.values()) or 1
        top = max(sc, key=sc.get)
        if sc[top] / tot < 0.7:
            continue                      # a second that straddles two screens
        key = st if top == 'world' else top
        if key in NAMES and float(m[2]) < 100 and int(m[1]) < 200:
            stages.setdefault(key, []).append((int(m[1]), float(m[2]), float(m[3]), int(m[4])))
    for st in stage_order:
        rows = stages.get(st, [])[1:] if st.startswith('Stag') else stages.get(st, [])
        if not rows:
            print('%-18s %-9s no samples' % (cfg, NAMES[st]))
            failed = failed or a.min_fps > 0
            continue
        n = len(rows)
        fps = sum(x[0] for x in rows) / n
        print('%-18s %-9s %4d %6.1f %9.2f %8.2f %9.1f %d' % (cfg, NAMES[st], n, fps, sum(x[1] for x in rows) / n,
              max(x[2] for x in rows), sum(x[3] for x in rows) / n, min(x[0] for x in rows)))
        if a.min_fps and fps < a.min_fps:
            failed = True
sys.exit(1 if failed else 0)
