#!/usr/bin/env python3
"""Real-asset playback checks using SDL's dummy and PCM file output drivers.
No sound reaches speakers. Run from the port: tools/verify_audio.py --roms ../../local/extracted.
"""
import argparse
import os
from pathlib import Path
import subprocess
import tempfile

PORT = Path(__file__).resolve().parent.parent


def run(args, env, timeout=120):
    p = subprocess.run([str(x) for x in args], env=env, cwd=PORT,
                       capture_output=True, text=True, timeout=timeout)
    assert p.returncode == 0, p.stdout + p.stderr
    return p.stdout + p.stderr


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--roms', default='../../local/extracted')
    opts = parser.parse_args()
    roms = Path(opts.roms).resolve()
    env = dict(os.environ, SDL_AUDIODRIVER='dummy', SDL_VIDEODRIVER='dummy')
    # Menu/lobby preparation decodes several original streams and resident banks.
    # Allow CPU contention in parallel checks without changing playback timing.
    report = run([PORT / 'build/test_audio', roms], env, timeout=120)
    if 'SDL2 not built' in report:
        print('audio playback: SDL2 not built; skipped')
        return
    # Standalone/session and lobby menu preparation resolve the original clips.
    assert report.count('  menu audio:') >= 24, report
    for mapping in ('ST_CHARA -> [0.53]', 'AM_TITLE -> [0.19]', 'AM_START -> [0.18]',
                    'CURSOR_START -> STAGIS10.sfp sequence 1, waveform 2, 46312 frames',
                    'CURSOR_MOVE -> allse.sfp sequence 2, waveform 28, 4368 frames',
                    'CURSOR_DECIDE -> allse.sfp sequence 1, waveform 29, 12320 frames',
                    'CURSOR_CANCEL -> allse.sfp sequence 0, waveform 30, 2800 frames',
                    'WINDOW_OPEN -> allse.sfp sequence 6, waveform 24, 7672 frames',
                    'WINDOW_CLOSE -> allse.sfp sequence 5, waveform 25, 5432 frames',
                    'CURSOR_MOVE2 -> STAGIS10.sfp sequence 3, waveform 0, 4928 frames',
                    'WINDOW_CLOSE2 -> allse.sfp sequence 8, waveform 47, 12544 frames',
                    'CURSOR_NG -> allse.sfp sequence 3, waveform 27, 14840 frames'):
        assert mapping in report, report
    assert 'loop 658336..6582824' in report, report
    for level in ('ST_CHARA -> -40, gain 0.628906', 'AM_TITLE -> -30, gain 0.707031',
                  'AM_START -> -30, gain 0.707031', 'ST_LOBBY -> -50, gain 0.558594',
                  'AM_LOBBY -> -160, gain 0.156250'):
        assert level in report, report
    print('front-end levels: authored stream attenuation and simulation-clock SE repeat gate verified')
    assert report.count('  lobby audio:') >= 6, report
    for mapping in ('ST_LOBBY -> [0.58], 6673184 frames, loop 1620576..6661052',
                    'AM_LOBBY -> [0.13], 1912224 frames, loop 22976..1879961',
                    'mlBEEP01 -> STAGML01.sfp sequence 7, waveform 7, 96320 frames'):
        assert report.count(mapping) == 2, report
    assert report.count('lobby audio cue: mlBEEP01') == 1, report
    assert report.index('lobby audio cue: mlBEEP01') < report.index('lobby: terminal message'), report
    print('lobby audio: music/ambience loops and terminal bank entry verified; start/cancel cleanup ok')
    print('menu audio: all eleven retail clips resolve; authored music loop retained')
    with tempfile.TemporaryDirectory(prefix='dw4-audio-') as temp:
        temp = Path(temp)
        lobby_muted = temp / 'lobby-muted.pcm'
        muted_report = run([PORT / 'build/test_audio', roms, 'mute'],
                           dict(env, SDL_AUDIODRIVER='disk', SDL_DISKAUDIOFILE=str(lobby_muted)))
        assert muted_report.count('lobby audio cue: mlBEEP01') == 1, muted_report
        output = lobby_muted.read_bytes()
        assert len(output) >= 48000 * 4 // 20 and not any(output), 'muted lobby must output silence'
        print('lobby mute: silent device output throughout greeting and beep')
        for name in ('aus_opening.sfd' , 'ajp_opening.sfd', 'aeu_opening.sfd'):
            reference, capture = temp / 'reference.pcm', temp / 'capture.pcm'
            run([PORT / 'build/dw4asset', 'media', roms, 'convert', name, reference,
                 '-map', '0:a:0', '-ac', '2', '-ar', '48000', '-f', 's16le'], env)
            disk = dict(env, SDL_AUDIODRIVER='disk', SDL_DISKAUDIOFILE=str(capture))
            report = run([PORT / 'build/dw4', '--roms', roms, '--movie', name,
                          '--window', '--headless', '--input-script', '30:cross'], disk)
            assert '[skipped]' in report and 'movie audio clock:' in report, report
            source, output = reference.read_bytes(), capture.read_bytes()
            # SDL's disk driver writes silence while a device is paused during
            # preroll. Once started, the emitted PCM must be an exact prefix.
            off = output.find(source[:4096])
            assert off >= 0 and len(output) - off >= 48000 * 4 // 2, report
            assert output[off:] == source[:len(output) - off], name
            print(f'{name}: SDL output matches source PCM exactly; skip stops playback')
        muted = temp / 'muted.pcm'
        report = run([PORT / 'build/dw4', '--roms', roms, '--movie', 'aus_opening.sfd',
                      '--window', '--headless', '--mute', '--input-script', '30:cross'],
                     dict(env, SDL_AUDIODRIVER='disk', SDL_DISKAUDIOFILE=str(muted)))
        assert 'movie audio clock:' in report and '[skipped]' in report, report
        samples = muted.read_bytes()
        assert len(samples) >= 48000 * 4 // 2 and not any(samples), 'muted output must be silence'
        print('CLI mute: silent PCM output while the movie audio clock advances')
        report = run([PORT / 'build/dw4', '--roms', roms, '--movie', 'aus_opening.sfd',
                      '--window', '--headless', '--input-script', '3:cross'],
                     dict(env, SDL_AUDIODRIVER='dw4-invalid-driver'))
        assert 'audio: unavailable:' in report and '[skipped]' in report, report
        report = run([PORT / 'build/dw4', '--roms', roms, '--movie', 'aus_opening.sfd',
                      '--input-script', '3:cross'], env)
        assert 'movie audio:' not in report and '[skipped]' in report, report
    print('audio playback: missing-device fallback and silent decode-only path ok')


if __name__ == '__main__':
    main()
