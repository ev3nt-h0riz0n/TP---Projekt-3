# TP---Projekt-3
## Projekt wykonany przez Doriana Neumann (198415) oraz Antoniego Sulkowskiego (197564)

By użyc biblioteki należy pobrać plik c++ oraz ewentualnie skonfigurować CMakeLists.txt, aby odpowiadała użytkownikowi (m.in. z wyszukiwaniem PATH'u). Ponadto obowiązkowe jest posiadanie bibliotek: matplotplusplus oraz libsndfile.
Linki do repozytorium z bibliotekami:
MATPLOTPLUSPLUS: https://github.com/alandefreitas/matplotplusplus
LIBSNDFILE: https://github.com/libsndfile/libsndfile

Po poprawnym skonfigurowaniu należy wpisać do Pythona:
	'import sygnaly'

## Generowanie sygnałów sinusoidalnych, cosinusoidalnych, piłokształtnych, prostokątnych

SINUSOIDALNA: 		
'sygnaly.sin(f)'
gdzie f - wybrana przez użytkownika częstotliwość w Hz. 

COSINUSOIDALNA: 	'sygnaly.sin(f)' 	- gdzie f - wybrana przez użytkownika częstotliwość w Hz. 
PROSTAKATNY: 		'sygnaly.prosto(f, w)' 	- gdzie f - częstotliwość, w - współczynnik wypełnienia
PROSTAKATNY: 		'sygnaly.pilo(f)'	- gdzie f - częstotliwość

Przykład: Wpisując do konsoli 'sygnaly.sin(5)' otrzymamy wykres funkcji cosinus o częstotliwości 5 Hz.

## Wizualizowanie sygnału dźwiękowego z rozszerzeniem .wav oraz wizualizacja jego autokorelacji
Aby zrealizować funkcję należy wpisać do Pythona:

	'sygnaly.wizualizacja(sciezka/do/pliku/audio.wav,n)'	
gdzie n to n-krotne pomniejszenia liczby próbek sygnału, w celu zmniejszenia obciążenia programu i ograniczenia potencjalnych zacięć. N powinno należeć do liczb naturalnych dodatnich.

Przykład: Wpisując do konsoli 'sygnaly.wizualizacja("C:\\Users\\Jarek\\ProgramIII\\audio.wav", 4) otrzymamy wykres wizualizujący dźwięk pliku znajdującego się na tej ścieżce o nazwie audio.wav z 4-krotnie mniejszą ilością próbek. Wpisując 1 liczba próbek pozostanie jednakowa jak w pliku. Jako drugi obraz wygeneruje się wizualizacja autokorelacji dźwięku z pliku.
__!!! UWAGA !!!: Obowiązkowe jest wpisywanie podwójnych ukośników (\\).__

W pliku CMakeLists.txt jest duzo dodanych ścieżek ze względu na to, że mój komputer nie wyszukiwał ich domyślnie. Proszę usunąć zbędne :)).


