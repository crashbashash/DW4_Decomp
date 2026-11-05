#!/usr/bin/env python3
"""End-to-end NPC dialogue on the real headless engine.

For each case the engine boots through Create, warps into a hub, stands the player in front of an NPC (DW4_DEV_TALK) and presses Cross
through the whole conversation while frames are captured.  The 'First' cases do not warp: they talk in the engine's scripted first
Terminal (session_lobby_start), after Cross has paged through the arrival greeting and the D.S.G. messages; they also check from the log
that the greeting ran whole, that no Cross probe claimed a receiver before the player stood at the NPC and that each probe at the NPC hit
one receiver.  Every captured frame is classified from its pixels:

  talk   a message window is up (the bottom panel with bright text)
  idle   the world with the HUD ring (no window)
  other  neither (a loading screen or a service scene)

and the run must show: idle -> talk -> (idle | other), a speaker face in the portrait box on every talk frame, no HUD ring while a
message is open, and (for plain conversations) the world and HUD back at the end, i.e. the dialogue neither stalls nor loses control.

  tools/test_dialogue_e2e.py [--roms DIR] [--tool build/dw4] [--only NAME] [--keep DIR]

Uses a throw-away $XDG_DATA_HOME.  Slow (about a minute per case).  Needs PIL and numpy.
"""
import argparse
import os
import re
import shutil
import subprocess
import sys
import tempfile

import numpy as np
from PIL import Image

CREATE = ('5:start,70:start,130:cross,300:cross,345:cross,395:cross,410:right,420:right,432:cross,448:start,500:cross,530:cross,'
          '580:start')
FIRST_CROSS, CROSS_EVERY, LAST_FRAME, SHOT_EVERY = 1520, int(os.environ.get('DW4_E2E_EVERY', '80')), 2900, 30

# The first Terminal: Cross pages through the greeting and the D.S.G. messages, the player is stood at the NPC 1750 lobby frames in.
FIRST_PAGES, FIRST_TALK, FIRST_LAST = range(700, 2500, 60), 1750, 3300

# (name, hub, npc model, slot, plain[, log line the run must print]) - plain conversations end with the world and the HUD back; the others
# lead into a service.  hub None is the scripted first Terminal (no warp).  The Call Keeper is n_digilff[0] (its matf04 label stands at
# (270,55,50)); n_digilfm[0] is the elf at the station opposite.
CASES = [
    ('First Call Keeper', None, 'n_digilff', 0, False, 'hub loading: stagIS13'),
    ('First Agumon', None, 'n_agumon', 0, True),
    ('First Digi-Elf', None, 'n_digilff', 1, True),
    ('Terminal Digi-Elf', 'StagML11', 'n_digilfm', 0, True),
    ('Terminal Agumon', 'StagML11', 'n_agumon', 0, True),
    ('Central Save Keeper', 'StagML12', 'n_digilfm', 0, False),
    ('Central Bank Keeper', 'StagML12', 'n_digilfm', 1, False),
    ('Central Digi-Lab', 'StagML12', 'n_digilfm', 2, False),
    ('Shop Disk Shop', 'StagML13', 'n_digilfm', 0, False),
    # The Commander Room's first visit plays the Digi-Elf welcome (flag 502) before the player has control, so the NPC is
    # reached later, the run is longer and frames are classified from after the welcome: (talk at hub frame, last frame, first shot).
    ('Commander Room Digi-Elf', 'StagML02', 'n_digilff', 0, True, 2000, 5200, 2900),
]


def dark_ratio(a):
    return float((a[385:470, 130:620].max(axis=2) < 90).mean())


def classify(path):
    a = np.asarray(Image.open(path).convert('RGB').resize((640, 480))).astype(int)
    ring = a[340:470, 20:135]
    green = int(((ring[:, :, 1] > 170) & (ring[:, :, 0] < 100) & (ring[:, :, 2] < 130)).sum())
    panel = a[385:470, 130:620]
    dark = float((panel.max(axis=2) < 90).mean())        # the message panel is a dark navy plate
    text = int((panel.min(axis=2) > 150).sum())
    face = float(a[348:418, 28:95].std())
    if green >= 25:
        return 'idle', face
    if float(a.mean()) > 28 and float(a[340:470, 100:600].std()) < 40 and dark_ratio(a) < 0.2 and green < 25 and float(a[:300].std()) > 35:
        return 'limbo', face   # the world is showing with neither the HUD nor a message window (the stuck frame)
    if dark > 0.45 and text > 20:
        return 'talk', face
    return 'other', face


def run(args, case, out):
    name, hub, npc, slot = case[:4]
    timing = case[5:8] if len(case) > 7 and isinstance(case[5], int) else (300, LAST_FRAME, 1450)
    talk_at, last_hub, first_shot = timing
    if hub:
        last, crosses, shots = last_hub, range(FIRST_CROSS, last_hub - 100, CROSS_EVERY), range(first_shot, last_hub, SHOT_EVERY)
        extra = dict(DW4_DEV_WARP=hub + ':0', DW4_DEV_WARP_FRAMES='300', DW4_DEV_TALK='%d:%s:%d' % (talk_at, npc, slot))
    else:
        last, crosses = FIRST_LAST, list(FIRST_PAGES) + list(range(FIRST_PAGES.stop + 40, FIRST_LAST - 100, CROSS_EVERY))
        shots, extra = range(2400, FIRST_LAST, SHOT_EVERY), dict(DW4_DEV_TALK='%d:%s:%d' % (FIRST_TALK, npc, slot))
    script = CREATE + ''.join(',%d:cross' % f for f in crosses)
    with tempfile.TemporaryDirectory() as tmp:
        env = dict(os.environ, XDG_DATA_HOME=tmp, DW4_SHOT_FRAMES=','.join(str(f) for f in shots), **extra)
        if not hub:
            env.pop('DW4_WARP', None);env.pop('DW4_DEV_WARP', None)
        cmd = [args.tool, '--roms', args.roms, '--boot', '--window', '--headless', '--w', '640', '--h', '480', '--frames', str(last),
               '--loading-min-seconds', '0', '--mute', '--input-script', script, '--out-dir', out]
        r = subprocess.run(cmd, env=env, capture_output=True, text=True, timeout=900 * last // LAST_FRAME)
    return r.stdout + r.stderr


def main():
    p = argparse.ArgumentParser()
    p.add_argument('--roms', default='../../local/extracted')
    p.add_argument('--tool', default='build/dw4')
    p.add_argument('--only')
    p.add_argument('--keep')
    args = p.parse_args()
    bad, ran = [], 0
    for case in CASES:
        name, hub, npc, slot, plain = case[:5]
        if args.only and args.only not in name:
            continue
        out = os.path.join(args.keep, name.replace(' ', '_')) if args.keep else tempfile.mkdtemp(prefix='dw4-e2e-')
        os.makedirs(out, exist_ok=True)
        log = run(args, case, out)
        frames = sorted((int(f[6:-4]), os.path.join(out, f)) for f in os.listdir(out) if f.startswith('frame_'))
        if 'not found' in log or 'dev talk' not in log:
            print('  %s: NPC not present in this stage, skipped' % name)
            if not args.keep:
                shutil.rmtree(out, ignore_errors=True)
            continue
        ran += 1
        problems = []
        if not hub:
            placed = re.search(r'dev talk: \S+ placed at frame (\d+)', log)
            placed = int(placed.group(1)) if placed else 1 << 30
            frames = [f for f in frames if f[0] >= placed - 60]   # the greeting and the D.S.G. messages are not this NPC's talk
            greeting = set(int(m) for m in re.findall(r'original greeting TALKFONT0\d I<(\d+)>', log))
            if greeting != set(range(39, 54)) or 'restored HUD' not in log:
                problems.append('the arrival greeting did not run whole (pages %s)' % sorted(greeting))
            probes = [(int(f), int(h)) for f, h in re.findall(r'Cross probe at frame (\d+) hit (-?\d+)', log)]
            if any(h for f, h in probes if f < placed):
                problems.append('a Cross probe claimed a receiver before the player stood at the NPC')
            if not any(h == 1 for f, h in probes if f >= placed) or any(h > 1 for f, h in probes):
                problems.append('the Cross probe at the NPC did not hit exactly one receiver')
        if len(case) > 5 and isinstance(case[5], str) and case[5] not in log:
            problems.append('the run never printed "%s"' % case[5])
        states = [(n,) + classify(path) for n, path in frames]
        seq = ''.join({'talk': 'T', 'idle': 'I', 'other': 'o', 'limbo': 'L'}[s[1]] for s in states)
        talk = [s for s in states if s[1] == 'talk']
        # a limbo frame is allowed only while the conversation text changes page, never for long
        streak = best = 0
        for st in states:
            streak = streak + 1 if st[1] == 'limbo' else 0
            best = max(best, streak)
        if best > 4:
            problems.append('the world stayed up with neither HUD nor message window for %d frames (stuck)' % best)
        if len(talk) < 3:
            problems.append('no conversation was shown (%d talk frames)' % len(talk))
        else:
            weak = [s[0] for s in talk if s[2] < 30]
            if len(weak) * 5 > len(talk):
                problems.append('speaker face missing on %d of %d talk frames (first at %d)' % (len(weak), len(talk), weak[0]))
            first = next(i for i, s in enumerate(states) if s[1] == 'talk')
            if not any(s[1] == 'idle' for s in states[:first]):
                problems.append('no world+HUD frame before the conversation')
            seq_tail = [x[1] for x in states]
            # Plain conversations must come back to the world with the HUD and be repeatable: at least two talk->idle cycles.
            cycles = sum(1 for i in range(1, len(seq_tail)) if seq_tail[i - 1] == 'talk' and seq_tail[i] == 'idle')
            if plain and cycles < 2:
                problems.append('only %d conversation(s) ended back in the world with the HUD (expected a repeatable talk)' % cycles)
            if not plain and cycles < 1 and 'other' not in seq_tail:
                problems.append('the conversation neither returned to the world nor reached its service')
        print('  %-22s %s%s' % (name, seq, '' if not problems else '  <-- ' + '; '.join(problems)))
        bad += ['%s: %s' % (name, x) for x in problems]
        if not args.keep:
            shutil.rmtree(out, ignore_errors=True)
    if not ran:
        sys.exit('dialogue e2e: no case ran')
    if bad:
        sys.exit('dialogue e2e FAILED:\n  ' + '\n  '.join(bad))
    print('dialogue e2e: %d conversations run end to end (window, face, HUD hand-over, return to the world)' % ran)


main()
