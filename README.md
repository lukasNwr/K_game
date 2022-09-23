Doc by `© Copyright 2010-2015 KPI FEI TUKE - Miroslav Biňas`  
[URL DOCS](http://it4kt.cnl.sk/c/pvjc/2015/problemset.04.k.html)  
Thanks!

***

# K

### Ciele
1. Naučiť sa pracovať s typom bool z knižnice stdbool.h.
2. Pracovať so štruktúrovanými typmi.
3. Pracovať s dvojrozmerným poľom.
4. Pracovať so vstupno-výstupnými parametrami funkcií.

### Hra K
Hra _K_ vychádza z hry 2048 a podobne, ako aj hra 2048 sa hrá na poli o rozmeroch 4x4. Jediným rozdielom medzi týmito hrami je skutočnosť, že v hre K budete miesto čísel na hracích kameňoch používať písmená. Hráč vie tieto kamene posúvať do štyroch strán (v pôvodnej hre pomocou kurzorových kláves, v našom prevedení pomocou načítavania znakov, resp. reťazcov zo štandardného vstupu).

Každý nový ťah hry sa začína vygenerovaním náhodnej dlaždice s písmenom `'A'` alebo `'B'`. Pri pohybe do strán sa dlaždice presunú tak ďaleko do danej strany, ako je to možné. Zastaviť ich môže buď iná dlaždica alebo okraj hracieho poľa. Ak sa pri presúvaní stretnú (dotknú) dve dlaždice s rovnakým písmenom, spoja sa do nasledujúceho písmena v poradí abecedy. Napr. ak sa pri presúvaní spoja dve písmená `'C'`, vznikne ich spojením jedno písmeno `'D'`. Výsledná dlaždica, ktorá vznikla spojením dvoch iných dlaždíc, už však nemôže byť v danom ťahu spojená so žiadnou inou dlaždicou s rovnakým písmenom.

Hráč dostáva za svoju hru body. Jeho skóre sa aktualizuje zakaždým, ak pri ťahu dôjde k spojeniu dvoch alebo viacerých dlaždíc. Spôsob výpočtu skóre je opísaný v samostatnej časti tohto textu.

Hra sa končí vtedy, keď sa na hracej ploche objaví dlaždica s písmenom `'K'` (odtiaľ pramení aj názov tejto hry).

Vašou úlohou bude naprogramovať hru K v jazyku C implementovaním týchto dvoch modulov:

1. Modul samotnej hry K.
2. Modul reprezentujúci Hall of Fame (sieň slávy najlepších hráčov).

Tieto moduly obsahujú všetky potrebné funkcie na implementáciu hry K. V rámci modulu si samozrejme môžete vytvoriť aj ďalšie pomocné funkcie. Nesmiete však nijako meniť a upravovať hlavičkové súbory oboch modulov!

#### Modul K
Tento modul predstavuje hlavný modul hry, v ktorom sa budú nachádzať všetky funkcie a údajové typy potrebné pre implementáciu samotnej hry K. Konkrétne bude obsahovať zadefinovaný štruktúrovaný údajový typ `GAME` a funkcie `update()`, `render()`, `is_move_possible()`, `is_game_won()` a preddefinovanú funkciu `add_random_tile()` na pridanie náhodnej dlaždice s písmenom `'A'` alebo `'B'` do hracieho poľa.

Funkcia render() slúži na vykreslenie hracieho poľa hráča. Podoba vykreslenia nie je definovaná a taktiež nebude hodnotená v testoch. S grafickou stránkou hry sa teda môžete pohrať sami.

#### Údajový typ GAME
Tento údajový typ reprezentuje samotnú hru. Význam jednotlivých položiek je nasledovný:

* **board** - dvojrozmerné pole reprezentujúce hraciu plochu a aktuálny stav hry, a
* **score** - aktuálny počet bodov (skóre), ktoré hráč nahral počas hry.

#### Úloha #1: Je hra vyhratá?
Ako bolo uvedené v pravidlách hry, hra je považovaná za vyhratú vtedy, keď sa na hracej ploche objaví písmeno `'K'`. Vašou úlohou je vytvoriť funkciu `bool is_game_won(const GAME game)`, ktorá tento stav overí.

Funkcia má tento parameter:

* **const GAME game** - štruktúrovaný typ reprezentujúci stav aktuálnej hry

Funkcia vráti hodnotu `true`, ak sa na hracej ploche už písmeno `'K'` nachádza. V opačnom prípade vráti funkcia hodnotu false.

#### Úloha #2: Je možné vykonať ďalší ťah?
Hra sa bude hrať dovtedy, pokiaľ bude možné vykonať ďalší ťah. To znamená, že sa na hracom poli bude nachádzať prázdne miesto alebo sa budú vedľa seba nachádzať dve dlaždice s rovnakým písmenom. Vašou úlohou je overiť, či je alebo nie je možné vykonať ďalší ťah. Preto vytvorte funkciu `bool is_move_possible(const GAME game)`, ktorá túto úlohu vyrieši.

Funkcia má tento parameter:

* **const GAME game** - štruktúrovaný typ reprezentujúci stav aktuálnej hry
Funkcia vráti hodnotu `true`, ak je možné v hre vykonať ďalší ťah. V opačnom prípade vráti funkcia hodnotu `false`.

Túto funkciu je možné použiť na overenie, či je možné vykonať v hre ďalší ťah. Ak ďalší ťah už vykonať nie je možné, hra sa pre hráča skončila.

#### Úloha #3: Zmena stavu hry
Stav hry sa zmení zakaždým, keď hráč vykoná pohyb do jednej zo štyroch strán - hore, dole, vľavo a vpravo. Ak je možné pohnúť sa, všetky dlaždice sa presunú v danom smere tak ďaleko, ako je to možné. Zastaviť ich môže buď iná dlaždica alebo okraj hracieho poľa. Ak sa pri presúvaní stretnú (dotknú) dve dlaždice s rovnakým písmenom, spoja sa do nasledujúceho písmena v poradí abecedy (Napr. zo spojenia dvoch písmen `'H'` vznikne jedno písmeno `'I'`).

Možnosti spojenia dvoch a viacerých dlaždíc v jednom riadku sú ilustrované na nasledujúcich príkladoch. Rovnaké správanie je však možné aplikovať pre všetky smery.

```
+---+---+---+---+                   +---+---+---+---+
| A |   | A |   |   (smer vpravo)   |   |   |   | B |
+---+---+---+---+                   +---+---+---+---+
```

```
+---+---+---+---+                   +---+---+---+---+
| A |   | A | A |   (smer vpravo)   |   |   | A | B |
+---+---+---+---+                   +---+---+---+---+
```

```
+---+---+---+---+                   +---+---+---+---+
| A | A | A | A |   (smer vpravo)   |   |   | B | B |
+---+---+---+---+                   +---+---+---+---+
```

```
+---+---+---+---+                   +---+---+---+---+
| B | A | A |   |   (smer vpravo)   |   |   | B | B |
+---+---+---+---+                   +---+---+---+---+
```

Vašou úlohou je vytvoriť funkciu `bool update(GAME *game, int dy, int dx)`, ktorá pohyb daným smerom zabezpečí.

Funkcia má tieto parametre:

* **GAME *game** - referencia na štruktúrovaný typ reprezentujúci stav aktuálnej hry
* **int dx** - smer v osi X, ktorý môže mať len jednu z troch hodnôt: -1, ak sa jedná o smer vľavo, 0, ak sa nejedná o zmenu smeru v x-ovej osi a 1, ak sa jedná o smer vpravo.
* **int dy** - smer v osi Y, ktorý môže mať len jednu z troch hodnôt: -1, ak sa jedná o smer hore, 0, ak sa nejedná o zmenu smeru v y-ovej osi a 1, ak sa jedná o smer dolu.

Funkcia vráti hodnotu `true`, ak sa stav hry zmenil. V opačnom prípade vráti funkcia hodnotu `false`.

Funkcia však vráti hodnotu `false` aj v prípade, ak bola funkcia nesprávne použitá. To je v prípade, ak je funkcia zavolaná spôsobom, kedy sa má vykonať pohyb do viac ako jednej strany súčasne alebo naopak do žiadnej strany.

Príklady použitia funkcie `update()` sú uvedené v nasledujúcich fragmentoch kódu.

### Modul hof
Súčasťou hry bude v tomto prípade aj tzv. sieň slávy (z angl. Hall of Fame, skrátene hof). Bude reprezentovaná zoznamom desiatich najlepších hráčov hry. Tento zoznam sa bude nachádzať v samostatnom súbore, ktorý v prípade potreby nahráte a po jeho aktualizácii ho zasa uložíte späť na disk. Tento zoznam bude usporiadaný v poradí od najlepšieho hráča po najhoršieho.

Tento modul bude obsahovať zadefinovaný štruktúrovaný údajový typ **PLAYER**, funkciu `add_player()` a preddefinované funkcie `save()` a `load()`.

Preddefinovaná funkcia `load()` zabezpečí nahratie zoznamu zo súboru a jeho uloženie do výstupného parametra funkcie **list**. Funkcia vráti počet načítaných položiek, pričom max. počet, ktorý zo súboru načíta, je práve 10. V prípade, že sa jej súbor nepodarí načítať, vráti hodnotu _-1_.

Sieň slávy je na disku reprezentovaná formou textového súboru, v ktorom každý riadok má nasledovnú štruktúru:
```
NAME SCORE
```
kde **NAME** reprezentuje meno hráča, ktoré pozostáva z postupnosti znakov bez znaku medzera; a **SCORE** je celé číslo reprezentujúce dosiahnuté skóre hráča. Táto dvojica je od seba oddelená znakom medzera.
Preddefinovaná funkcia `save()` zabezpečí uloženie zoznamu do súboru. O úspešnosti, resp. neúspešnosti tejto operácie funkcia informuje návratovou hodnotou typu `bool`.

#### Údajový typ PLAYER
Tento údajový typ reprezentuje záznam v tabuľke Hall of Fame. Význam jednotlivých položiek je nasledovný:

* **name** - meno hráča, a
* **score** - počet bodov (skóre), ktoré hráč dosiahol.

#### Úloha #4: Aktualizácia Hall of Fame
Po dohratí hry nasleduje kontrola toho, či dosiahnuté skóre umožní hráčovi zápis do siene slávy. Ak áno, jeho meno bude zaradené na správne miesto v desiatke najlepších hráčov v poradí od najlepšieho hráča (hráč, ktorý získal najviac bodov). Vašou úlohou je teda vytvoriť funkciu `bool add_player(PLAYER list[], int* size, const PLAYER player)`, ktorá v prípade, že hráč do siene slávy patrí, ho zaradí na správne miesto.

Funkcia má tieto parametre:

* **PLAYER list[]** - Referencia na aktuálny zoznam desiatky najlepších hráčov. Zoznam je reprezentovaný ako jednorozmerné pole, ktoré je dlhé práve 10 položiek typu **PLAYER**.
* **int* size** - Skutočná veľkosť zoznamu siene slávy, ktorý je dlhý max. 10 položiek. Zoznam môže byt kratší v prípade, ak vašu hru začínate s prázdnou sieňou slávy.
* **const PLAYER player** - Hráč, ktorý má byť vložený do siene slávy.

Funkcia vráti hodnotu `true` v prípade, že hráč sa do siene slávy dostal alebo hodnotu `false`, ak sa do nej nedostal. Okrem toho v prípade úspešného zápisu aktualizuje zoznam, na ktorý ukazuje parameter **list** a rovnako tak v prípade potreby aktualizuje aj celkovú veľkosť zoznamu, ktorá je uložená v parametri **size**.

V prípade, ak hráč dosiahol rovnaký počet bodov ako existujúci záznam v sieni slávy, tieto položky budú usporiadané vzostupne na základe mena hráčov.
***
### Structure
```
.
├── k
│   ├── k.c
│   ├── k.h
│   ├── hof.c
│   ├── hof.h
│   ├── main.c
│   └── Makefile
```
***

### Compile/Run App

**Compile:** `make all`  
 or  
 `gcc -std=c11 -Werror -Wall main.c k.c hof.c -lm -o k`

 **Run:**
  `./k`

**Remove:** `make clean`

***

* #BadCode #Amateur