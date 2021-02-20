# Projekt - Wavfiles
* nie działa łączenie dźwięków (fal?)
* Usunięte wczytywanie z pliku
## Jak działa?
```
gcc main.c functions.c wavefile.c -o test -lm
./test
```
## pliki:
```fst.wav``` - pierwszy .wav<br>
```snd.wav``` - drugi .wav<br>
```merged.wav``` - połączone dwie fale
```noise.wav``` - dodane szumy
```blur20.wav blur200.wav blur2000.wav``` - próby odszumiania (dziwny efekt)
