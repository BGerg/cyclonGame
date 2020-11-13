# Cyclon Arcade Game
Cyclon game on STM32F103 Nucleo-64 developer board with WS2812 led circle

### Basics idea

* handle two players
* Score feedback
* who accumulates ten points he/she is the winner

### Technical "steps" to implementing
what we need: players_color, player score

START
1. A gyűrű fele az egyik játékos a másik fele a másik járékos színével világít.
2. A kezdő játékos szinei párszor villognak
3. A gyűrű szinei lekapcsolnak
4. 12 és 8 óránál egy led zölden világít
5. Adott játékos színének megfelelő led "körbefut" addig amíg a gomb nincs megnyomva
6. Ellenőrzés, hogy a srága led és a "futó" led pozíciója a gombnyomás pillanatában egyezett-e
7. (ha igen 1 pontal növekednek az adott játékos pontjai)
8. 12 órai ledtől jobbra és balra a játékosok pontjaival egyenlő mennyiségű led világít pár másodpercig.
9. Aki vezet annak a a "pontjai" villognak párat
10. (ha döntetlen mindkettő pontjai villognak)
11. Ha valaki pontjai elérik a 8-at nyert és az egész gyűrű az ő színével villog párat
12. Ha még nincs nyertes játékosváltás újrakezdődik a 3. ponttól
