# Svetelny_senzor
Program pre Arduino

## Vlastnosti
- Ovladanie motora pomocou DRV8824
- Snimanie lasera dvoma snimacmi TSL1402R
- Signalizacia upozorneni na dvojfarebnej led
- Automatizovane zarovnanie pri detekovani lasera
- Detekcia silneho ambientneho svetla : cervena led
- Detekcia lasera na snimacoch : zlta led
- Nastaveny motor na 1/32 microstepping
- Vyvod uhla po Arduino Rx, Tx
- Vypisovanie krokov motora, aktualu poziciu lasera a errory po Arduino Rx, Tx
- Nastavovanie hodnot Laser a Ambient cez Rx, Tx
- Ovládanie motora cez Rx, Tx

## Prikazy
- Nastavenie citlivosti na ambientne svetlo
  - `<AMB> xxxx` kde hodnota je medzi 1-250
  - cim mensie cislo, tym vacsia citlivost
- Nastavenie citlivosti detekcie lasera
  - `<LASER> xxxx` kde hodnota je medzi 200-1000
  - cim vacsie cislo, tym vacsia citlivost
- Pohnutie motora
  - `<MOTOR> xxxx`
