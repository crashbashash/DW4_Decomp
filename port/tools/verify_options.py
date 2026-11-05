#!/usr/bin/env python3
"""Asset-independent INI and host path checks, always in isolated user storage."""
import os
from pathlib import Path
import shutil
import subprocess
import tempfile

binary = Path('build/test_options').resolve()
subprocess.run([binary], check=True)
with tempfile.TemporaryDirectory(prefix='dw4-config-') as tmp:
    root = Path(tmp)
    home = root / 'home'
    home.mkdir()
    env = dict(os.environ, HOME=str(home), XDG_CONFIG_HOME='')
    def run(exe, mode, expected):
        result = subprocess.run([exe, mode], env=env, cwd=root, text=True, capture_output=True, check=True)
        assert Path(result.stdout.strip()) == expected, result.stdout
        assert expected.read_text() == '[options]\ncamera=near\nlight=hard\n'
    run(binary, 'normal', home / '.config/dw4/config.ini')
    env['XDG_CONFIG_HOME'] = 'relative/ignored'
    run(binary, 'normal', home / '.config/dw4/config.ini')
    env['XDG_CONFIG_HOME'] = str(root / '配置 settings')
    run(binary, 'normal', root / '配置 settings/dw4/config.ini')
    beside = root / 'portable 游戏'
    beside.mkdir()
    portable = beside / 'test_options'
    shutil.copy2(binary, portable)
    run(portable, 'portable', beside / 'userdata/config/config.ini')
    # A file in place of the chosen directory must fail, without falling back.
    blocked = root / 'blocked'
    blocked.write_text('keep me')
    env['XDG_CONFIG_HOME'] = str(blocked)
    result = subprocess.run([binary, 'normal'], env=env, cwd=root, capture_output=True)
    assert result.returncode != 0 and blocked.read_text() == 'keep me'
print('configuration paths: ok')
