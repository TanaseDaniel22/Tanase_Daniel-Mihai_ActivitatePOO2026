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
	// Constructorii sunt metode speciale apelate automat la instantierea unui obiect. Nu au tip returnat (nici macar
	// si au acelasi nume cu clasa. Pot fi supraincarcati (overloaded) pentru a permite initializarea obiectelor in moduri diferite.

	//Constructorul fara parametri (Default constructor) 
	// este apelat atunci cand obiectul este creat fara a fi initializat cu valori specifice

	public:
		Cafenea() id(++nrCafenele) { // lista de initializare a constructorului, executata inainte de corpul acestuia. 
			this->denumire = "Cafenea necunoscuta"; // this-> pointer implicit catre obiectul curent care se construieste
			this->tip = TO_GO;                      // diferentiaza atributele clasei de parametri cu acelasi nume
			this->incasariZilnice = 0;
			this->nrBauturi = 0;
			this->preturiBauturi = nullptr; // fiind un obiect fara produse, pointerul este setat pe "nullptr" ptr a preveni referentierea
			// unor adrese de memorie aleatorii (garbage values) care ar putea duce la erori de rulare (runtime errors)
		}

		//Constructorul cu parametri
		Cafenea(string denumire, TipCafenea tip, float incasari, int nrBauturi, float* preturi)
			: id(++nrCafenele) {
			this->denumire = denumire;
			this->tip = tip;
			this->incasariZilnice = incasari;
			this->nrBauturi = nrBauturi;
			
			if (preturi != nullptr && nrBauturi > 0) {
				this->preturiBauturi = new float[nrBauturi]; // aloca dinamic pe Heap spatiu pentru un tablou de "nrBauturi elem de tip float. Operatorul "new" returneaza adresa primului element
				for (int i = 0; i < nrBauturi; i++) {      //Deep Copy : Bucla "for" copiaza fiecare valoare individual din tabloul "preturi" in tabloul zona proprie de memorie (this->preturiBauturi).
					this->preturiBauturi[i] = preturi[i]; // copierea valorilor din tabloul preturi in tabloul preturiBauturi al obiectului

					// Daca nu se face deep copy, atunci ambele obiecte (cel care apeleaza constructorul si cel care este creat) 
					// vor avea pointeri care indica catre acelasi tablou de preturi. cauzand prabusirea programului la dezalocare
				}
			}
			else {
				this->preturiBauturi = nullptr; // daca nu exista bauturi, pointerul este setat pe nullptr
				this->nrBauturi = 0; // si numarul de bauturi este setat la 0
			}
		}
