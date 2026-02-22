# Trenutna Verzija - DAW Test Checklist i Ocekivanja

Datum: 2026-02-21  
Scope: trenutni build nakon P5 Round-3 (prije P6)

## 1. Sto je aktivno u ovoj verziji

Aktivni host/UI parametri (APVTS):
- `style.mode` (Tech / Neuro / Dark)
- `env.amp.att`
- `env.amp.rel`
- `macro.neuro_formant`
- `macro.fm_metal`
- `macro.roller_dynamics`
- `macro.liquid_depth`
- `macro.style_morph`

Frontend kontrole:
- Style selector: `Tech`, `Neuro`, `Dark`
- 4 macro rotary kontrole
- 1 style morph slider

## 2. Brzi Smoke Test (obavezno)

1. Plugin scan i load
- Koraci:
  - Rescan VST3 u DAW-u.
  - Ucitaj `DnB Bass Synth` na instrument track.
- Ocekivano:
  - Plugin se ucita bez crasha.
  - GUI se otvara (macro panel + style selector + style morph).

2. MIDI i audio izlaz
- Koraci:
  - Posalji MIDI note (npr. C1-C3), drzane i kratke note.
- Ocekivano:
  - Cuje se stabilan output.
  - Bez dropova/clickova u normalnom radu.

## 3. Kontrole koje moraju raditi

1. `style.mode`
- Test:
  - Prebacuj `Tech -> Neuro -> Dark` uz isti pattern.
- Ocekivano:
  - Cuje se razlika karaktera.
  - `Dark` je agresivniji; `Tech` pitomiji.

2. `macro.neuro_formant`
- Test:
  - Sweep 0 -> 1.
- Ocekivano:
  - Primjetna promjena tonalnog karaktera/boje.

3. `macro.fm_metal`
- Test:
  - Sweep 0 -> 1 u `Dark` stilu, pa isto u `Tech`.
- Ocekivano:
  - U `Dark` stilu jaci metal/FM efekt.
  - U `Tech` stilu efekt je ograniceniji (style constraint).

4. `macro.roller_dynamics`
- Test:
  - Sweep 0 -> 1 na istom note loopu.
- Ocekivano:
  - Cuje se promjena dinamike/movementa (nije no-op).

5. `macro.liquid_depth`
- Test:
  - Sweep 0 -> 1.
- Ocekivano:
  - Zvuk postaje “meksi/tamni” (manje agresivan high/dist karakter).

6. `macro.style_morph`
- Test:
  - Sweep 0 -> 1 i automacija lane.
- Ocekivano:
  - Cuje se kontinuirana promjena karakter path prisutnosti.

7. `env.amp.att` i `env.amp.rel`
- Test:
  - Automacija ili host kontrola min/max.
- Ocekivano:
  - Kraci attack = brzi onset.
  - Dugi release = duzi rep.

## 4. Host Automation Test

1. Napravi automation lane za sve aktivne parametre.
2. Playback 16-32 bar.

Ocekivano:
- Parametri odgovaraju na automation bez pucanja audio-a.
- Nema “mrtvih” aktivnih parametara iz sekcije 1.

## 5. Sto NE treba ocekivati u ovoj verziji

1. Parametri ispod nisu dio aktivnog host contracta:
- `sub.shape`
- `sub.phase`
- `sys.xover`
- `osc.fm.ratio`
- `fx.ott.mix`

2. Preset/state migracija nije P5 cilj:
- Moguce je da full recall/save behavior jos nije finalan (to je P6 scope).

3. Napredni vizualni feedback (analizatori) je jos ogranicen:
- Vizualni panel je primarno placeholder razine.

## 6. Fail kriteriji (odmah prijaviti)

- Plugin se ne ucitava ili rusi DAW.
- Nema audio izlaza na validan MIDI input.
- Bilo koja aktivna kontrola iz sekcije 1 je no-op.
- Automation uzrokuje hard artefakte, dropout ili freeze.
- Style naming ili macro set odstupa od:
  - Style: `Tech`, `Neuro`, `Dark`
  - Macro set: `neuro_formant`, `fm_metal`, `roller_dynamics`, `liquid_depth`

## 7. Preporuceni format biljeski za test

- DAW + verzija:
- OS:
- Buffer/SR:
- Test case:
- Rezultat (`PASS`/`FAIL`):
- Kratka napomena + eventualni screenshot/audio clip:
