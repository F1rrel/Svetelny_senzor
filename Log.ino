//Filip Štec
//8.4.2016
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
// o Pridana kontrola stepov motora, ak by bola hodnota moc velka, tak sa program zacykli a blika 
//   cervena ledka
// o Pridane citanie hodnot errorAmbient a errorLaser z EEPROM na adresach 0 a 1 pomocou EEPROM.get
// o Opravene drobne chyby

