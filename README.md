# Port of Zelda Time to Triumph for PS Vita (French Version)

## Why this fork ?
The main goal was to have a french version of this game because i'm french :)
The second one was to correct some missing references on compilation files.
Thanks to usineur for his work and help.

## VPK
Latest version is available [here](https://github.com/NicolasR/Zelda3T-French/releases).

Note: saves can be found in `ux0:data/z3t/save` directory.

## Controls:

**On game selection screen / Inside inventory**

| Keys | &#x202F; |
| --- | --- |
| D-Pad | Navigate |
| Cross | Select game / Close inventory |

**In-game**

| Keys | &#x202F; |
| --- | --- |
| Left stick | Move Link |
| Right stick | Look around |
| Cross | Carry without gloves / Confirm / Pass text |
| Circle | Read / Open / Speak |
| Square | Use weapon |
| Triangle | Use selected object |
| L | See the map |
| R | Run |
| Right D-Pad | Item selection |
| Up D-Pad | See defeated monsters |
| Left D-Pad | See barter items |
| Down D-Pad | See fishes |
| L + R | Oni Link transformation |
| Select | Display help |
| Start | Save quit |


## Credits:

- Vincent Jouillat, for [Original game](http://www.zeldaroth.fr/us/z3t.php)
- [Nop90](https://www.github.com/nop90/Zelda3T), for:
  - his 3DS port that contains several memory leaks fixes I included in this port.
  - the "Impulse tracker" musics provided in his fork
- littlebalup, for key mapping inspiration

## Changelog:

1.2.2:
- Added multilingual support with autodetection
- Added English translation

1.2.1:
- Add "Fullscreen" option
- Add "Auto-hide menu bar" option
- Imgui settings can now be saved and reloaded.

1.2:
- SDL 1.2 (vitaGL) + imgui support (thx to @Rinnegatamante)

1.1b:
- Added missing translation

1.1:
- Fix more memory leaks
- External datas are not required anymore (about 195 Mb space gained)

1.0:
- First public release
