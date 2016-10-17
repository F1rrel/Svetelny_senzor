//Filip Štec
//17.10.2016
//
//Program arduino pre svetelny stabilizator
//
//Ovladanie motora pomocou DRV8824
//Snimanie lasera dvoma snimacmi TSL1402R
//Signalizacia upozorneni na dvojfarebnej led
//Automatizovane zarovnanie pri detekovani lasera
//Detekcia silneho ambientneho svetla : cervena led
//Detekcia detekovania lasera na snimacoch : zlta led
//Nastaveny motor na 1/32 microstepping
//Vyvod uhla po seriovej linke RS232

//Change log ku Program3.1
// o Pridane vypisovanie errorov, peak a stepov pre lepsi debug
// o Pridana moznost zapisat hodnoty do AMB a LASER formou:
//    <LASER> xxxx pricom hodnota moze byt <200,1000>
//    <AMB> xxxx pricom hodnota moze byt <1,250>
// o Pridana moznost pohnut motorom <MOTOR> xxxx pricom zapisujeme steps
//    650 ~= 1mm

