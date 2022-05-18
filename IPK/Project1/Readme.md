# IPK - Počítačové komunikace a sítě - Projekt 1

* autor: Daniel Záležák
* login: xzalez01
* dátum: 11.3.2022

## Popis projektu

Projekt je implementovaný v jazyku C. Aplikácia vytvorí server, s ktorým následne klient komunikuje pomocou protokolu HTTP. Server odpovedá taktiež pomocou HTTP protokolu. Typ odpovede je text/plain. 


### Preklad a spustenie

Server sa prekladá pomocou príkazu make, ktorý vytvorí spustitelný subor hinfosvc. Server je spustitelný iba s argumentom označujúcim port na ktorom server bude počúvať.

```
$ make
$ ./hinfosvc %port%
```

## Použitie

Server dokáže spracovať nasledujúce 3 typy otázok:
1. Získanie doménového mena
Vráti sieťové meno počítača vrátane domény, napríklad:
GET http://servername:12345/hostname

merlin.fit.vutbr.cz
```
$curl http://localhost:12345/hostname
```
2. Získanie informacií o CPU 
Vráti informaciu o procesore, napríklad:
GET http://servername:12345/cpu-name

Intel(R) Xeon(R) CPU E5-2640 0 @ 2.50GHz
```
$curl http://localhost:12345/cpu-name
```
3. Aktuálna záťaž 
Vráti aktuálnu informaciu o zátaži.
GET http://servername:12345/load

65%
```
$curl http://localhost:12345/load
```
## Ukončenie servera
Server je možné ukončiť pomocou CTRL+C.

