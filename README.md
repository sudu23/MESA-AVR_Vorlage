# MESA-AVR MPLAB X Projektvorlage

Dies ist die Projektvorlage, um mit dem MESA-AVR ein neues Projekt zu starten.

## Features
* Port-Pins sind der Funktion entsprechend konfiguriert (Inputs: Schalter, Taster / Outputs: LEDs) und weisen sinnvolle Namen (RBGLED_color, HBLED) auf
* CycleCync ist implementiert
* printf ist implementiert

## Hardware
* **MCU:** AVR128DB48
* **Taktfrequenz:** 4 MHz output (default)
* **Peripherie:** TCB3 als CycleCync-Quelle, USART2 für die printf-Umleitung (Debugging)

## Voraussetzungen (getestet)
* **IDE:** MPLAB X v6.25 oder neuer
* **Compiler:** XC8 v3.1 oder neuer
* **Programmer:** PICkit 4 / SNAP (UPDI)


## Installation
1. Repository klonen: `git clone https://github.com/DEIN_NAME/PROJEKT.git`
2. Projekt in MPLAB X öffnen.
3. Falls der Compiler-Pfad nicht stimmt: Rechtsklick auf Projekt -> Properties -> Conf -> Compiler auswählen.