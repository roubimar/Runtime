# Runtime

Autor: Marek Roubicek, Daniel Pina

Zadání: VM pro Java bytecode

Jazyk: C++

Struktura archivu

root
| jvms8.pdf - Java Virtual Machine Specification
| README.txt
|
├─── Runtime - slozka s kodem
	|
	├─── bin - spustitelny soubory pro testy 
	|
	├─── java - pomocne classy
	|
	├─── operands - jednotlive typy objekty ukladane na heapu
	|
	└─── test - testovací Javovské soubory a jejich .class soubory

Spusteni: pomoci Makefile prikazem make ve slozce Runtime a nasledne spustit prikazem "./bin/jvm.exe 'nazev spoustene classy"

Napr. "./bin/jvm.exe test/Main" nebo "./bin/jvm.exe text/CompareNumbers"

Trida Main vypocitava fibonacciho cislo pro zadane cislo ze vstupu.

 








