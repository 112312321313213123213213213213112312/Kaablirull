# Isekeriv kaablirull – kaabli pikkuse mõõtmine

EEV5120 Mehhatroonikasüsteemid – projekt (2026 sügis), Rühm E.

Arduino programm, mis mõõdab isekeriva kaablirulli trumlile paigaldatud kooderi abil välja tõmmatud kaabli pikkust ja kuvab selle LCD ekraanil. Programm on koostatud algoritmi plokkskeemi järgi (`plokkskeem.png`).

## Tööpõhimõte

1. Seadistatakse sisendid ja väljundid, käivitatakse ekraan ja nullitakse impulsiloendur (N = 0).
2. Loetakse kooderi signaali. Iga uue impulsi korral:
   - kaabli väljatõmbamisel N = N + 1, tagasikerimisel N = N − 1;
   - arvutatakse pikkus L = N × s (s = kaabli pikkus ühe impulsi kohta);
   - kuvatakse pikkus ekraanil, kui L ≥ 2 m, kuvatakse hoiatus „Kaabel lõpus“;
   - oodatakse 50 ms;
   - kontrollitakse, kas seade lülitati välja. Kui jah, programm lõpetab töö.

## Programmi funktsioonid

| Funktsioon | Ülesanne |
|---|---|
| `setup()` | Algseadistus, ekraani käivitamine, loenduri nullimine |
| `kooder()` | Kooderi lugemine, loenduri muutmine ja pikkuse arvutamine |
| `ekraan()` | Pikkuse ja hoiatuse kuvamine LCD ekraanil |
| `valjalylitus()` | Väljalülitamise kontroll |
| `loop()` | Kutsub funktsioone välja |

Programmi tööd saab jälgida Serial Monitoriga (9600 baud).

## Riistvara

| Komponent | Ühendus |
|---|---|
| Arduino Uno | – |
| Inkrementaalkooder | A → D2, B → D3 |
| 16x2 LCD (I2C, 0x27) | SDA → A4, SCL → A5 |
| Väljalülitamise lüliti | D4 (LOW = välja) |

## Vajalik teek

- `LiquidCrystal_I2C` (Arduino IDE → Tools → Manage Libraries)

## Failid

- `kaablirull/kaablirull.ino` – programmi kood
- `plokkskeem.png` – algoritmi plokkskeem
