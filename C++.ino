/*
 * Nimetus: Isekeriv kaablirull
 * Kirjeldus: Kaabli pikkuse mõõtmine kooderi abil ja kuvamine LCD ekraanil
 * Autor: Mart-Hendrik Meikup (Rühm E)
 * Kuupäev: 24.11.2026
 * Versioon: v1.0
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Defineerime sisendid ja väljundid
#define KOODER_A 2   // Kooderi kanal A
#define KOODER_B 3   // Kooderi kanal B
#define S_VALJA 4    // Väljalülitamise lüliti

// Defineerime konstandid
#define S_CM 0.5     // Kaabli pikkus ühe impulsi kohta (cm)
#define L_MAX 200.0  // Kaabli maksimaalne pikkus (cm)

// Defineerime globaalsed muutujad
long N = 0;          // Impulsiloendur
byte A_eelmine = 0;  // Kanali A eelmine olek
float L = 0;         // Kaabli pikkus (cm)

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD ekraan I2C aadressiga 0x27

void setup()
{
  // Andmeside jadaliidese käivitamine
  Serial.begin(9600);
  // Algseadistus
  pinMode(KOODER_A, INPUT_PULLUP);
  pinMode(KOODER_B, INPUT_PULLUP);
  pinMode(S_VALJA, INPUT_PULLUP);
  // Ekraani käivitamine
  lcd.init();
  lcd.backlight();
  lcd.print("Kaablirull");
  // Impulsiloenduri nullimine
  N = 0;
  A_eelmine = digitalRead(KOODER_A);
}

bool kooder()
{
  // Loeme kooderi signaali
  byte A = digitalRead(KOODER_A);
  byte B = digitalRead(KOODER_B);
  if (A && !A_eelmine)
  {                  // Tuli uus impulss
    if (!B)
    {                // Kaablit tõmmatakse välja
      N = N + 1;     // Suurendame loendurit
    }
    else
    {                // Kaablit keritakse sisse
      N = N - 1;     // Vähendame loendurit
      if (N < 0)
      {
        N = 0;       // Kaabel on täielikult sisse keritud
      }
    }
    L = N * S_CM;    // Arvutame kaabli pikkuse

    // Programmi kontrollimine Serial Monitoriga
    Serial.print("Kaabli pikkus (cm): ");
    Serial.println(L);
    A_eelmine = A;   // Salvestame kanali A oleku
    return true;     // Uus impulss töödeldud
  }
  A_eelmine = A;     // Salvestame kanali A oleku
  return false;      // Uut impulssi ei tulnud
}

void ekraan()
{
  // Kuvame kaabli pikkuse ekraanil
  lcd.setCursor(0, 0);
  lcd.print("L = ");
  lcd.print(L / 100.0, 2);
  lcd.print(" m      ");
  lcd.setCursor(0, 1);
  if (L >= L_MAX)
  {                  // Kaabel on lõpus
    lcd.print("Kaabel lopus!   ");
  }
  else
  {
    lcd.print("                ");
  }
}

void valjalylitus()
{
  // Kontrollime, kas seade lülitati välja
  if (!digitalRead(S_VALJA))
  {
    lcd.clear();
    lcd.print("Seade valjas");
    Serial.println("Seade lylitati valja");
    while (1) {}     // Programm lõpetab töö
  }
}

void loop()
{
  if (kooder())     // Kooderi lugemise ja pikkuse arvutamise funktsioon
  {                 // Tuli uus impulss
    ekraan();       // Ekraanil kuvamise funktsioon
    delay(50);      // Viivitus 50 ms
    valjalylitus(); // Väljalülitamise kontrollfunktsioon
  }
}
