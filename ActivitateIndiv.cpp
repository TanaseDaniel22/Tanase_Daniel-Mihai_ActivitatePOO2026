#include <iostream>
#include <string>

using namespace std;

enum TipCafenea { TO_GO = 1, BISTRO  2, LOUNGE = 3 };

//Structura clasei si Atributele acesteia
class Cafenea{};
private: // protejeaza datele de modificari neautorizate din exterior (principiul encapsularii)
	const int id; // variabilele "const" trebuie initializate obligatoriu in lista de initializare a constructorului, nu in corpul acestuia
	static int nrCafenele; // (variabila de clasa) retine numarul de obiecte create din aceasta clasa
	string denumire; 
	TipCafenea tip; // retine una dintre valorile definite ( TO_GO, BISTRO, LOUNGE )
	float incasariZilnice; 
	int nrBauturi;
	float* preturiBauturi; // pointer catre un alocament dinaimc pe Heap. Nu contine tabloul propriu-zis, ci doar adresa de inceput a acestuia. Tabloul este alocat in constructor si eliberat in destructor.

	// Constructori