Bibliotek zbudowana, za��czona w ca�o�ci

Aby uruchomi� nale�y najpierw zbudowa� bibliotek�. (wszystkie poni�sze czynno�ci zosta�y wykonane w Visual studio 2015, nie mam pewno�ci czy w innych te� zadzia�a - na pewno nie dzia�� w 2017)
W tym celu po pierwsze nale�y odpali� aplikacje urg_cpp.sln znajduj�c� si� w folderze: ...urg_library-1.2.2\vs2010\cpp
Otworzy sie 8 projekt�w w visualu, aby zbudowa� biblioteke uruchom je.
Po zbudowaniu biblioteki dalszym krokiem jest poszukiwanie plik�w .bat, i ich przekopiowanie do podanego folderu, wed�ug orginalnej instrukcji:

"1.Copy the batch file provided by Visual Studio to set the necessary environment variables for compiling. 
Copy Program Files\Microsoft Visual Studio *\Common7\Tools\vsvars32.bat to urg_library-*.*.*\windowsexe 
(Replace the asterisks '*' above with the version of the library and Visual Studio you use.) 

2.Execute the bat file to prepare environment for compilation. 
Run the urg_library-*.*.*\windowsexe\compile.bat file. (If the vsvars32.bat file is not present in the same folder, it will end with error.) 

For details, please check the compile.bat file."

Po uruchomieniu pliku compile.bat, jezeli wszytsko wczesnije zosta�o wykonane poprawnie i szcz�cie nam dopisuje biblioteka zosta�� zbudowana poprawnie.

Program do obs�ugi LIDARa znajduje sie w projekcie get_distance. 

Wrazie pyta� prosze o kontakt - dhoffmann44@gmail.com