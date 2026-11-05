#!/usr/bin/env python3
"""Check title pacing after slow audio preroll with silent SDL dummy devices."""
import argparse
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import time


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--roms', default='../../local/extracted')
    parser.add_argument('--tool', type=Path, help='host executable (default: port/build/dw4)')
    args = parser.parse_args()
    port = Path(__file__).resolve().parents[1]
    ffmpeg = shutil.which('ffmpeg')
    assert ffmpeg, 'ffmpeg is required'
    with tempfile.TemporaryDirectory(prefix='dw4-title-pacing-') as temp:
        # Delay each of the three ADX decodes enough to expose a pacing origin
        # incorrectly taken before preroll. No audio reaches speakers.
        wrapper = Path(temp) / 'ffmpeg'
        wrapper.write_text('#!/usr/bin/env python3\nimport os, time\ntime.sleep(2)\n'
                           'os.execv(' + repr(ffmpeg) + ', [' + repr(ffmpeg) + '] + __import__("sys").argv[1:])\n')
        wrapper.chmod(0o755)
        # Remove presentation's own vsync wait so it cannot mask a pacing bug.
        present = Path(temp) / 'present.c'
        present.write_text('void SDL_RenderPresent(void *renderer) { (void)renderer; }\n')
        shim = Path(temp) / 'present.so'
        subprocess.run(['cc', '-shared', '-fPIC', str(present), '-o', str(shim)], check=True)
        preload = str(shim) + (' ' + os.environ['LD_PRELOAD'] if os.environ.get('LD_PRELOAD') else '')
        env = dict(os.environ, SDL_VIDEODRIVER='dummy', SDL_AUDIODRIVER='dummy',
                   LD_PRELOAD=preload, SDL_RENDER_VSYNC='0', DW4_SKIP_MOVIE='1', PATH=temp + os.pathsep + os.environ['PATH'])
        for name in ('DW4_FL_T', 'DW4_FL_DEBUG', 'DW4_FL_SEQ'):
            env.pop(name, None)
        cmd = ['stdbuf', '-oL', str((args.tool or port / 'build/dw4').resolve()), '--roms', str(Path(args.roms).resolve()),
               '--boot', '--window', '--gl', '--frames', '60', '--w', '320', '--h', '240',
               '--input-script', '999:cross']
        loaded = finished = None
        lines = []
        with subprocess.Popen(cmd, env=env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                              text=True) as process:
            for line in process.stdout:
                lines.append(line)
                if 'menu audio:' in line:
                    loaded = time.monotonic()
                if 'title: presented 60 frame(s)' in line:
                    finished = time.monotonic()
            assert process.wait() == 0, ''.join(lines)
        assert loaded is not None and finished is not None, ''.join(lines)
        elapsed = finished - loaded
        assert elapsed >= 0.98, f'title opening raced after audio preroll: {elapsed:.3f}s'
        print(f'title pacing: first 60 frames took {elapsed:.3f}s after audio preroll; opening cadence preserved')


if __name__ == '__main__':
    main()
