#!/usr/bin/env python3
"""Confirm the actual recovered Options flow persists and reloads across processes."""
import argparse
import os
from pathlib import Path
import subprocess
import tempfile
from PIL import Image

port = Path(__file__).resolve().parent.parent
parser = argparse.ArgumentParser()
parser.add_argument('--roms', default=str(port.parent.parent / 'local/extracted'))
a = parser.parse_args()
script = '5:start,70:start,120:down,150:cross,310:right,340:down,365:right,400:down,425:cross'
with tempfile.TemporaryDirectory(prefix='dw4-options-menu-') as tmp:
    root = Path(tmp)
    env = dict(os.environ, XDG_CONFIG_HOME=str(root / 'config'), DW4_SKIP_MOVIE='1')
    config = root / 'config/dw4/config.ini'
    def run(frames):
        result = subprocess.run([str(port / 'build/dw4'), '--roms', a.roms, '--boot',
                                 '--headless', '--frames', str(frames), '--w', '160', '--h', '112',
                                 '--out-dir', str(root), '--input-script', script],
                                env=env, text=True, capture_output=True, check=True)
        assert 'title: option screen opened' in result.stdout, result.stdout
        if frames > 425:
            assert 'title: option screen closed -> main menu' in result.stdout, result.stdout
        return result.stdout
    # Display edits do not reach storage before the recovered close commits them.
    run(330)
    assert config.read_text() == '[options]\ncamera=near\nlight=hard\n'
    out = run(510)
    assert 'Dungeon camera = Far, Light = Soft' in out
    assert config.read_text() == '[options]\ncamera=far\nlight=soft\n'
    out = run(510)  # fresh host, toggles the loaded values back
    assert 'Dungeon camera = Near, Light = Hard' in out
    assert config.read_text() == '[options]\ncamera=near\nlight=hard\n'
    config.write_text('; edited outside the game\n[options]\ncamera=far\nlight=hard\n[future]\nfoo=keep\n')
    out = run(510)
    assert 'Dungeon camera = Near, Light = Soft' in out
    assert config.read_text() == '; edited outside the game\n[options]\ncamera=near\nlight=soft\n[future]\nfoo=keep\n'
    # Follow the real Game Start/name/login route in fresh processes. The held
    # camsp0101 floor patch has no actors, UI, portal animation or texture seams;
    # its mode colors are covered by the independent retail GS/image oracle.
    login = ('5:start,70:start,130:cross,300:cross,345:cross,395:cross,410:right,420:right,432:cross,448:start,500:cross,530:cross,580:start')
    for mode, rgb in (('hard', (22, 72, 228)), ('soft', (61, 88, 188))):
        saved = '[options]\ncamera=near\nlight=' + mode + '\n'
        config.write_text(saved)
        result = subprocess.run([str(port / 'build/dw4'), '--roms', a.roms, '--boot',
                                 '--headless', '--frames', '1080', '--w', '160', '--h', '112',
                                 '--out-dir', str(root), '--input-script', login],
                                env=env, text=True, capture_output=True, check=True)
        assert 'login: arrived;' in result.stdout, result.stdout
        assert config.read_text() == saved
        with Image.open(root / 'frame_1079.png') as frame:
            assert frame.convert('RGB').getpixel((120, 50)) == rgb, mode
print('Options menu: persistence, relaunch, external edits and saved Light -> lobby rendering ok')
