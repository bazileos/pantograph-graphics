# Haptikus pantográf grafikus megjelenítő alkalmazása
Készítette Riskutia Balázs, a "Pantográf alapú kinesztetikus haptikus eszköz tervezése" című szakdolgozatának keretein belül, a BME MOGI Tanszéken.

## Bevezetés

Ezen program célja a haptikus pantográf end-effectorjának és az ezt körülvevő virtuális tér vizuális nyomonkövetésének megvalósítása. A program C++ nyelven lett megírva, a Magnum Engine és a Boost Asio könyvtárak felhasználásával. 

## Build

A program által használt library-ket Visual Studio-ba legegyszerűbb módon a Vcpkg package manager segítségével lehet behúzni, ennek telepítéséhez is a Visual Studioba való integrálásához lásd: [Install Vcpkg on Windows](https://docs.microsoft.com/en-us/cpp/build/install-vcpkg?view=msvc-160&tabs=windows). Ahhoz, hogy a vcpkg parancs mindenhol elérhető legyen, ne felejtsük annak könyvtárát betölteni a Path környezeti változóba. Ezt követően az alábbi library-k telepítendők:

```
vcpkg install magnum[*] --triplet x64-windows
vcpkg install magnum-plugins[*] --triplet x64-windows
vcpkg install boost-asio --triplet x64-windows
```

Innentől a Magnum és Boost Asio automatikusan elérhető a Visual Studioból, a program akadálymentesen buildelhető.

## Futtatás

Futtatáshoz parancssori argumentumként meg kell adni a programnak, hogy melyik soros porton figyelje a mikrovezérlőt. Ha Visual Studio-ban történik a futtatás, akkor ezt a Project Properties ablak Debugging füle alatti Command Arguments mezőben tudjuk megadni (írjuk be pl. egyszerűen, hogy COM3).

## Felépítés

### `ThesisGraphics.hpp` és `main.cpp`

A grafikus megjelenítésért és a felhasználói események figyeléséért a ThesisGraphics osztály felelős, alapvető felépítésének magyarázata megtalálható a [Magnum Engine dokumentációjában](https://doc.magnum.graphics/magnum/getting-started.html). A program logikailag az alábbi fő egységekre bontható:

- A 3D-s tér betölése, renderelése előre elkészített .glb kiterjesztésű fájlból. (Ez a modell tartamlazza a fallal körülhatárolt munkateret, valamint az end-effector és a golyó modelljét.)
- A felhasználó interakciók alapján a 3D-s tér újrarenderelése: kameramozgatás egérrel
- Minden időlépésben (az egyes renderelések között) a soros port lekérdezése a Serial osztályon keresztül, ezek után a mozgó objektumok pozícióinak frissítése.

Az utóbbi két logikai egység eseménykezelő függvényekkel van megvalósítva.


### Soros kommunikáció

A program folyamatosan gyűjti a mikrovezérlőtől érkező pozícióadatokat (az end-effector és a virtuális golyó pozícióit). A kommunikációt, és a beérkező (pontosvesszővel elválasztott) karakterláncok feldolgozását az ebben a projektben megvalósított Serial osztály végzi, a Boost Asio könyvtár használatával (`Serial.hpp` és `Serial.cpp`).