#!/usr/bin/env python3
"""Exercise a failed lobby load, Retry and Back using a private manifest copy."""
import argparse
import os
import tempfile
from verify_frontend import run, png_rows

p = argparse.ArgumentParser()
p.add_argument('--roms', default='../../local/extracted')
a = p.parse_args()
roms = os.path.abspath(a.roms)
script = ('5:start,70:start,130:cross,300:cross,345:cross,395:cross,410:right,420:right,432:cross,448:start,500:cross,530:cross,580:start,685:cross,695:circle,705:start')
with tempfile.TemporaryDirectory(prefix='dw4-loading-failure-') as tmp:
    assets = os.path.join(tmp, 'assets')
    frames = os.path.join(tmp, 'frames')
    os.mkdir(assets)
    os.mkdir(frames)
    for filename in os.listdir(roms):
        if filename.upper() == 'NDMW.IGB':
            blob = open(os.path.join(roms, filename), 'rb').read()
            # The selector's entry-based preview still works; the lobby's named
            # player lookup fails. Original archives remain untouched.
            assert b'm_dorumon.igb' in blob
            blob = blob.replace(b'm_dorumon.igb', b'm_dorumox.igb')
            with open(os.path.join(assets, filename), 'wb') as f:
                f.write(blob)
        elif filename.upper().endswith('.AFS'):
            os.symlink(os.path.join(roms, filename), os.path.join(assets, filename))
    rc, out, err = run('build/dw4', ['--roms', assets, '--boot', '--headless',
                     '--frames', '780', '--w', '320', '--h', '224',
                     '--input-script', script, '--out-dir', frames])
    assert rc == 0, err
    assert out.count('loading: retry Main Lobby') == 1, out
    assert 'loading: back to created card' in out, out
    assert out.count('title: logging in') == 2, out
    assert 'title: created Dorumon named ac' in out, out
    assert 'entering the first playable stage' not in out, out
    assert 'assets unavailable; Retry/Back' in err, err
    w, h, bpp, rows = png_rows(os.path.join(frames, 'frame_0700.png'))
    lit = sum(max(row[x:x+3]) > 30 for row in rows for x in range(0,w*bpp,bpp))
    assert lit > 1000, 'Back did not reopen the created card'
print('loading failure: Retry, Back, retained created character and no partial arrival OK')

# Hold a successfully prepared destination without publishing it or advancing
# arrival, then verify the real ten-second wall-clock minimum and eventual handoff.
import re
for value in ('-1', 'nan', 'inf', '10junk', '86401', ''):
    rc, out, err = run('build/dw4', ['--loading-min-seconds', value])
    assert rc == 2 and 'requires seconds between' in err, (value, rc, err)
with tempfile.TemporaryDirectory(prefix='dw4-loading-hold-') as frames:
    common = ['--roms', roms, '--boot', '--headless', '--w', '320', '--h', '224',
              '--input-script', script, '--out-dir', frames]
    rc, out, err = run('build/dw4', common + ['--frames', '780', '--loading-min-seconds', '86400'])
    assert rc == 0 and 'loading: Main Lobby;' in out, err
    assert 'entering the first playable stage' not in out, out
    assert '0 lobby frame(s)' in out, out
    rc, out, err = run('build/dw4', common + ['--frames', '1300', '--loading-min-seconds', '10'])
    assert rc == 0, err
    hold = re.search(r'loading: visible for ([0-9.]+) seconds \(minimum 10.000\)', out)
    assert hold and float(hold[1]) >= 10.0, out
    assert out.count('entering the first playable stage: stagml11.igb') == 1, out
    assert 'login: arrived;' in out, out
print('loading hold: ten-second wall-clock minimum, eventual arrival, early-exit cleanup and argument validation OK')
