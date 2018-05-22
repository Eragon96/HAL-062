Bibliotek zbudowana, za³¹czona w ca³oœci

Aby uruchomiæ nale¿y najpierw zbudowaæ bibliotekê. (wszystkie poni¿sze czynnoœci zosta³y wykonane w Visual studio 2015, nie mam pewnoœci czy w innych te¿ zadzia³a - na pewno nie dzia³¹ w 2017)
W tym celu po pierwsze nale¿y odpaliæ aplikacje urg_cpp.sln znajduj¹c¹ siê w folderze: ...urg_library-1.2.2\vs2010\cpp
Otworzy sie 8 projektów w visualu, aby zbudowaæ biblioteke uruchom je.
Po zbudowaniu biblioteki dalszym krokiem jest poszukiwanie plików .bat, i ich przekopiowanie do podanego folderu, wed³ug orginalnej instrukcji:

"1.Copy the batch file provided by Visual Studio to set the necessary environment variables for compiling. 
Copy Program Files\Microsoft Visual Studio *\Common7\Tools\vsvars32.bat to urg_library-*.*.*\windowsexe 
(Replace the asterisks '*' above with the version of the library and Visual Studio you use.) 

2.Execute the bat file to prepare environment for compilation. 
Run the urg_library-*.*.*\windowsexe\compile.bat file. (If the vsvars32.bat file is not present in the same folder, it will end with error.) 

For details, please check the compile.bat file."

Po uruchomieniu pliku compile.bat, jezeli wszytsko wczesnije zosta³o wykonane poprawnie i szczêœcie nam dopisuje biblioteka zosta³¹ zbudowana poprawnie.

Program do obs³ugi LIDARa znajduje sie w projekcie get_distance. 

Wrazie pytañ prosze o kontakt - dhoffmann44@gmail.com