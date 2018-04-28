Ramki komunikacyjne
===================

UART
----

Komunikacja UART wykorzystywana jest do przesyłania danych pomiędzy
sterownikiem głównym (Nucleo F446) a urządzeniami odpowiedzialnymi za
łączność bezprzewodową (Router) oraz do połączenia między sterownikiem
głównym a komputerem pokładowym (Jetson).

W celu zapewnienia płynnej i niezawodnej komunikacji między operatorem a
łazikiem dane są przesyłane w postaci ramek o zdefiniowanym formacie:

-   znak ASCII ’\#’ - znak początku transmisji,

-   identyfikator ramki - liczba (w zakresie 0-255) określająca typ
    ramki, czyli jej długość i typ przesyłanych danych,

-   bity danych - dane w różnej postaci zależnie od typu ramki.

Powyższa konstrukcja podyktowana jest koniecznością przesyłania w obu
kierunkach różnorodnych danych i parametrów, dlatego ramka musi mieć
możliwość przyjmowania różnej długości. Ze względu na możliwość
przyjmowania przez przesyłane dane dowolnej wartości (0-255) niemożliwe
jest wykorzystanie znaku końca transmisji, gdyż istnieje ryzyko
wystąpienia takiego znaku wśród przesyłanych danych.

CAN
---

CAN jest szeregową magistralą komunikacyjną powszechnie wykorzystywaną w
przemyśle i motoryzacji. Charakteryzuje się dużą odpornością na
zakłócenia i łatwością obsługi. W łaziku została wykorzystana do
komunikacji pomiędzy wszystkimi modułami znajdującymi się na pokładzie
łazika. Transmisja może odbywać się z prędkością do 1Mb/s. Medium
pośredniczącym w transmisji jest skrętka dwu-przewodowa, w której
przesyłany jest napięciowy sygnał różnicowy.

Mikrokontrolery STM32 wykorzystywane na łaziku wspierają protokół CAN w
wersji 2.0A oraz 2.0B. Na potrzeby projektu zastosowano wersję 2.0A,
gdyż przestrzeń adresowa dostarczana przez tę wersję jest zdecydowanie
wystarczająca. Magistrala działa w konfiguracji multi-master. W praktyce
oznacza to, że każda z płytek nadaje informację na magistralę
niezależnie, ze stałym interwałem czasowym. W większości przypadków dane
przesyłane za pośrednictwem magistrali nie są danymi kluczowymi dla
działania innych podsystemów, a mają jedynie formę informacyjną dla
operatora. Dodatkowo częstotliwość nadawania ramek na magistralę nie
przekracza 50Hz, co przy szybkości transmisji rzędu 0.5Mb/s nie
wprowadza ryzyka zablokowania magistrali i utraty części danych.

Ramki identyfikowane są na podstawie adresu ramki (StdID).\
**Adres StdID jest równoznaczny z identyfikatorem ramki w komunikacji
UART.** Przyjmują one takie same wartości i odpowiadają tym samym
długościom ramek.

Zakresy adresów są przydzielane do konkretnych podsystemów:

-   100-159 platforma jezdna

-   160-199 manipulator

-   200-239 laboratorium

Zdefiniowane ramki
------------------

### 100-159 platforma jezdna {#platforma-jezdna .unnumbered}

100. Ramka do sterownika, określa prędkość i kierunek ruchu łazika,
    odpowiada odczytom ze standardowego joysticka. Długość ramki: 2
    znaki.

    -   wskazanieY wychylenie drążka w kierunku Y (prawo lewo)

    -   wskazanieX wychylenie drążka w kierunku X (przód tył)

    Uwagi: Wskazania joysticku są odwrócone względem intuicyjnego
    postrzegania (maksymalne wychylenie do przodu odpowiada wartości
    -100), wartość 0,0 oznacza położenie centralne, a tym samym łazik
    pozostaje bez ruchu.

101. Ramka do sterownika, zezwolenie na uruchomienie silników. Bez
    wysłania tej ramki silniki nie reagują na polecenie 100 (nastawy
    prędkości). Długość ramki: 1 znak.

    -   ’1’ wartość char (0x31) oznacza zezwolenie na ruch każda
        inna wartość oznacza brak zezwolenia i powoduje zatrzymanie
        napędów.

102. Ramka zawiera nastawy prędkości silników po prawej stronie

    -   Data[0] = prędkość silnika pierwszego

    -   Data[1] = prędkość silnika drugiego

    -   Data[2] = prędkość silnika trzeciego

    Uwagi: Wartości prędkości to int8 w zakresie od -100 do 100 gdzie 0
    oznacza zatrzymanie, 100 maksymalną prędkość obrotów do przodu, a
    -100 maksymalną prędkość obrotów do tyłu.

103. Ramka zawiera nastawy prędkości silników po lewej stronie

    -   Data[0] = prędkość silnika pierwszego

    -   Data[1] = prędkość silnika drugiego

    -   Data[2] = prędkość silnika trzeciego

    Uwagi: Wartości prędkości to int8 w zakresie od -100 do 100 gdzie 0
    oznacza zatrzymanie, 100 maksymalną prędkość obrotów do przodu, a
    -100 maksymalną prędkość obrotów do tyłu

104. Ramka do operatora, zawiera dane o prądzie pobieranym przez silniki
    po prawej stronie. Długość ramki: 6 znaków.

    -   currentValue1 & 0xFF;

    -   (currentValue1 & 0xFF00)\>\>8 ;

    -   currentValue2 & 0xFF;

    -   (currentValue2 & 0xFF00)\>\>8 ;

    -   currentValue3 & 0xFF;

    -   (currentValue3 & 0xFF00)\>\>8 ;

    Uwagi: currentValue to int16 zawierający prąd pobierany przez
    kolejne silniki, wartość currentValue odpowiada odczytom z
    przetwornika ADC i należy ją przeliczyć na wartość pobieranego
    prądu.

105. Ramka do operatora, zawiera dane o prądzie pobieranym przez silniki
    po lewej stronie. Długość ramki: 6 znaków.

    -   currentValue1 & 0xFF;

    -   (currentValue1 & 0xFF00)\>\>8 ;

    -   currentValue2 & 0xFF;

    -   (currentValue2 & 0xFF00)\>\>8 ;

    -   currentValue3 & 0xFF;

    -   (currentValue3 & 0xFF00)\>\>8 ;

    Uwagi: currentValue to int16 zawierający prąd pobierany przez
    kolejne silniki, wartość currentValue odpowiada odczytom z
    przetwornika ADC i należy ją przeliczyć na wartość pobieranego
    prądu.

106. Ramka do operatora, zawiera odczyty prędkości kół z enkoderów dla
    napędów z prawej strony. Długość ramki: 6 znaków.

    -   enkPrędkość1 & 0xFF;

    -   (enkPrędkość1 & 0xFF00)\>\>8 ;

    -   enkPrędkość2 & 0xFF;

    -   (enkPrędkość2 & 0xFF00)\>\>8 ;

    -   enkPrędkość3 & 0xFF;

    -   (enkPrędkość3 & 0xFF00)\>\>8 ;

    Uwagi: enkPrędkość to int16 zawierający prędkości obrotowe kolejnych
    kół.

107. Ramka do operatora, zawiera odczyty prędkości kół z enkoderów dla
    napędów z lewej strony. Długość ramki: 6 znaków.

    -   enkPrędkość1 & 0xFF;

    -   (enkPrędkość1 & 0xFF00)\>\>8 ;

    -   enkPrędkość2 & 0xFF;

    -   (enkPrędkość2 & 0xFF00)\>\>8 ;

    -   enkPrędkość3 & 0xFF;

    -   (enkPrędkość3 & 0xFF00)\>\>8 ;

    Uwagi: enkPrędkość to int16 zawierający prędkości obrotowe kolejnych
    kół.

108. Ramka do operatora, zawiera pomiary napięcia na kolejnych celach
    baterii. Długość ramki: 8 znaków.

    -   Vbat1 & 0xFF;

    -   (Vbat1 & 0xFF00)\>\>8 ;

    -   Vbat2 & 0xFF;

    -   (Vbat2 & 0xFF00)\>\>8 ;

    -   Vbat3 & 0xFF;

    -   (Vbat3 & 0xFF00)\>\>8 ;

    -   Vbat4 & 0xFF;

    -   (Vbat4 & 0xFF00)\>\>8 ;

    Uwagi: Vbat to napięcia zmierzone na kolejnych celach baterii. Są to
    wartości 12 bitowe, wymagają przeliczenia na wartości napięcia z
    uwzględnieniem dzielników napięcia zastosowanych na każdym z wejść
    analogowych (inne dla każdej z cel)

109. Ramka zawiera odczyty temperatur baterii zmierzone przez BMS.
    Długość ramki: 6 znaków

    -   batTemp1

    -   batTemp2

    -   batTemp3

    -   batTemp4

    -   batTemp5

    -   batTemp6

    Uwagi: batTemp to temperatura zmierzone na kolejnych bateriach. Są
    to wartości 8 bitowe (uint8), pomiar w zakresie 0-127 stopni z
    krokiem co 0.5 stopnia.

110. Ramka zawiera współrzędne GPS. Długość ramki: 8 znaków

    -   długośćGeo & 0xFF;

    -   (długośćGeo & 0xFF00)\>\>8 ;

    -   (długośćGeo & 0xFF0000)\>\>16 ;

    -   (długośćGeo & 0xFF000000)\>\>24 ;

    -   szerokośćGeo & 0xFF;

    -   (szerokośćGeo & 0xFF00)\>\>8 ;

    -   (szerokośćGeo & 0xFF0000)\>\>16 ;

    -   (szerokośćGeo & 0xFF000000)\>\>24 ;

    Uwagi: długość i szerokość to zmienne typu float zawierające
    informacje o stopniach (bez podziału na stopnie i minuty). Szerokość
    geograficzna (N i S), długość geograficzna (E i W).

111. Dane z IMU. Długość ramki: 12 znaków

    -   przyspieszenieX & 0xFF;

    -   (przyspieszenieX & 0xFF00)\>\>8 ;

    -   przyspieszenieY & 0xFF;

    -   (przyspieszenieY & 0xFF00)\>\>8 ;

    -   przyspieszenieZ & 0xFF;

    -   (przyspieszenieZ & 0xFF00)\>\>8 ;

    -   żyroskopX & 0xFF;

    -   (żyroskopX & 0xFF00)\>\>8 ;

    -   żyroskopY & 0xFF;

    -   (żyroskopY & 0xFF00)\>\>8 ;

    -   żyroskopZ & 0xFF;

    -   (żyroskopZ & 0xFF00)\>\>8 ;

    Uwagi: przyspieszenie i żyroskop to int16 zawierające odczyty z IMU,
    wymagają przeliczenia na wskazania przyspieszenia i prędkości
    kątowej.

112. Dane z Magnetometru. Długość ramki: 6 znaków

    -   magnetometrX & 0xFF;

    -   (magnetometrX & 0xFF00)\>\>8 ;

    -   magnetometrY & 0xFF;

    -   (magnetometrY & 0xFF00)\>\>8 ;

    -   magnetometrZ & 0xFF;

    -   (magnetometrZ & 0xFF00)\>\>8 ;

    Uwagi: magnetoemtr to int16 zawierający odczyty z Magnetometru.

113. Temperatura silników po prawej stronie. Długość ramki: 3 znaki

    -   tempSilnik1

    -   tempSilnik2

    -   tempSilnik3

    Uwagi: tempSilnik to temperatura zmierzone na kolejnych silnikach.
    Są to wartości 8 bitowe (uint8), pomiar w zakresie 0-128 stopni z
    krokiem co 0.5 stopnia.

114. Temperatura silników po lewej stronie. Długość ramki: 3 znaki

    -   tempSilnik1

    -   tempSilnik2

    -   tempSilnik3

    Uwagi: tempSilnik to temperatura zmierzone na kolejnych silnikach.
    Są to wartości 8 bitowe (uint8), pomiar w zakresie 0-128 stopni z
    krokiem co 0.5 stopnia.

115. Ograniczenie mocy silników. Ramka przesyłana do łazika. Długość
    ramki: 1 znak

    -   Moc silnika

    Uwagi: Moc silnika przyjmuje wartość od 1 do 20, gdzie 1 moc
    minimalna 20 pełna moc.

116. Status sterownika silników po prawej stronie. Długość ramki: 1 znak

    -   Status sterownika silników prawy

    Uwagi: Status przyjmuje następujące wartości:

    -   1: Sterownik uruchomiony (start)

    -   2: Sterownik zatrzymany (stop)

    -   3: Brak zasilania silników

    -   4: Inny problem

117. Status sterownika silników po lewej stronie. Długość ramki: 1 znak

    -   Status sterownika silników lewy

    Uwagi: patrz 116

118. Status BMS’a

    -   118

    -   Status sterownika silników lewy

    Uwagi: Status przyjmuje następujące wartości:

    -   1: OK

    -   2: zbyt niskie napięcie

    -   3: zbyt wysoka temp

    -   4: zbyt wysoki prąd

119. Maksymalna prędkość

    -   119

    -   Współczynnik prędkości maksymalnej

    Uwagi: Współczynnik prędkości maksymalnej przyjmuje wartości od 1 do
    20, gdzie 1 bardzo wolno, 20 moc maksymalna.

120. Ograniczenie prądu

    -   120

    -   Współczynnik ograniczenia prądu

    Uwagi: Współczynnik ograniczenia prądu przyjmuje wartości od 1 do
    200.

### 160-199 platforma jezdna {#platforma-jezdna-1 .unnumbered}

### 200-239 platforma jezdna {#platforma-jezdna-2 .unnumbered}

Konwersja danych
================

Wartości przesłane za pomocą protokołów komunikacyjnych opisanych w
poprzednim rozdziale wymagają konwersji, aby można było je wyświetlić i
analizować w jednostkach SI. Poniższy rozdział zawiera niezbędne do tego
wzory i przekształcenia.

currentValue
------------

W zależności od potrzeb w projekcie Strzyga zastosowano sterowniki
silników wyposażone w dwa różne czujniki poboru prądu ACS714 o zakresie
pomiaru 20A lub 50A. Charakteryzują się one różną czułością ($sens$).
Dla czujnika 20A $sens$ = 100mV/A, a dla czujnika 50A $sens$ = 40mV/A.
Czujniki 50A zastosowano w sterownikach silników napędowych, a 20A w
sterownikach silników manipulatora. Dodatkowo pomiędzy wyjściem czujnika
a wejściem mikrokontrolera zastosowano dzielnika napięcia z rezystorów
$R_1 = 1k$ i $R_2 = 1.5k$. Przetwornik ADC na mikrokontrolerze pracuje z
rozdzielczością 12 bitów i mierzy napięcie w zakresie od 0 do 3.3V.

Uwzględniając powyższe otrzymujemy zależność:

$$\textrm{pobierany prąd[A]}=\frac{3.3*currentValue*(R_1+R_2)}{2^{12}*R_2*sens}$$

enkPrędkość
-----------

Do pomiaru prędkości kół wykorzystywane są enkodery magnetyczne AMS
AS5040B o rozdzielczości 12 bit pracujące w trybie kwadraturowym. Pomiar
prędkości dokonywany jest poprzez pomiar czasu między wystąpieniem
kolejnych zboczy narastających na sygnale z kanału A. Kanał B
wykorzystywany jest do określenia kierunku obrotu. Enkoder umieszczony
jest bezpośrednio na wale stąd nie ma konieczności uwzględniania w
obliczeniach wpływu przekładni na prędkość. Wartość przesyłana jest
zależna od preskalera timera $prescaler=250$, prescalera wejściowego
$INprescaler=4$ oraz zegara taktującego timer $clock = 36MHz$. Jeżeli
enkPrędkość przyjmie wartość 0xFFFF oznacza to, że koło jest całkowicie
zatrzymane.

Uwzględniając powyższe otrzymujemy zależność:

$$\textrm{prędkość obrotowa [rpm]}=\frac{clock*INprescaler*60}{prescaler*enkPrędkość}$$

Vbat
----

Odczyt napięcia na kolejnych celach baterii jest stosunkowo prosty, gdyż
odczytujemy tutaj napięcie podzielone jedynie za pomocą rezystancyjnego
dzielnika napięcia. Dla każdej z cel wykorzystano inny dzielnik.
Dodatkowo należy pamiętać o sposobie przetwarzania napięcia opisanym w
podrozdziale enkPrędkość

Odczyt napięcia sprowadza się do wzoru:
$$\textrm{napięcie na baterii [V]}=\frac{3.3*Vbat*(R_1+R_2)}{2^{12}*R_1}$$
Poniższa tabela zawiera wartości rezystorów $R_1$ i $R_2$ dla
poszczególnych cel

           $R_1$   $R_2$
  ------- ------- -------
   Vbat1    22k    6.8k
   Vbat2   12.4k    22k
   Vbat3    10k     33k
   Vbat4    10k     47k

batTemp
-------

Pomiar temperatury poszczególnych modułów bateryjnych dokonywany za
pomocą termistorów NTC w układzie półmostkowym. Rezystor $R_1 = 10k$,
rezystancja nominalna termistora $R_0 = 22k$. Konwersję na poziomie
aplikacji opisuje wzór:
$$\textrm{temperatura baterii }[^{\circ}C] = \frac{batTemp}{2}$$
Jednakże konwersja wykonywana na poziomie mikrokontrolera jest dużo
bardziej złożona i opisana wzorem:
$$\textrm{temperatura baterii }[^{\circ}C] = \frac{1}{A_1+B_1*ln\frac{R_1}{(\frac{4096}{ADC}-1)*R_0}}-273.15$$
Gdzie $A_1$ oraz $B_1$ są parametrami zdefiniowanymi w dokumentacji
termistora, a ADC jest bezpośrednim wynikiem pomiaru z przetwornika
analogowo-cyfrowego.
