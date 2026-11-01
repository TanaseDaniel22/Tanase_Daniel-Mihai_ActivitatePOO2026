#include <iostream>
#include <string>

using namespace std;

enum TipCafenea { TO_GO = 1, BISTRO = 2, LOUNGE = 3 };


//Structura clasei si Atributele acesteia
class Cafenea {
	;
private: // protejeaza datele de modificari neautorizate din exterior (principiul encapsularii)
	const int id; // variabilele "const" trebuie initializate obligatoriu in lista de initializare a constructorului, nu in corpul acestuia
	static int nrCafenele; // (variabila de clasa) retine numarul de obiecte create din aceasta clasa
	string denumire;
	TipCafenea tip; // retine una dintre valorile definite ( TO_GO, BISTRO, LOUNGE )
	float incasariZilnice;
	int nrBauturi;
	float* preturiBauturi;
};// pointer catre un alocament dinaimc pe Heap. Nu contine tabloul propriu-zis, ci doar adresa de inceput a acestuia. Tabloul este alocat in constructor si eliberat in destructor.

	// Constructori
	// Constructorii sunt metode speciale apelate automat la instantierea unui obiect. Nu au tip returnat (nici macar
	// si au acelasi nume cu clasa. Pot fi supraincarcati (overloaded) pentru a permite initializarea obiectelor in moduri diferite.

	//Constructorul fara parametri (Default constructor) 
	// este apelat atunci cand obiectul este creat fara a fi initializat cu valori specifice;;

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

// !!! Regula celor 3 (Rule of Three) - daca o clasa are un constructor care aloca memorie dinamica, 
// trebuie sa aiba si un destructor si un copy constructor pentru a gestiona corect memoria.
// [clasa cu pointeri] --> necesita manual 1. Destructor, 2. Copy Constructor, 3. Operator =

// Destructorul este apelat automat la sfarsitul duratei de viata a obiectului (cand acesta iese din scope sau este sters).

~Cafenea() {
	if (this->preturiBauturi != nullptr) {
		delete[] this->preturiBauturi; // elibereaza memoria alocata dinamic pentru tabloul de preturi
		this->preturiBauturi = nullptr; // seteaza ptr pe nullptr pentru a evita suspendarea lor

	}
}

// Copy Constructor - este apelat atunci cand un obiect este creat ca o copie a altui obiect.
Cafenea(const Cafenea& copie) : id(++nrCafenele) {
	this->denumire = copie.denumire;
	this->tip = copie.tip;
	this->incasariZilnice = copie.incasariZilnice;
	this->nrBauturi = copie.nrBauturi;

	if (copie.preturiBauturi != nullptr && copie.nrBauturi > 0) {
		this->preturiBauturi = new float[copie.nrBauturi];
		for (int i = 0; i < copie.nrBauturi; i++) {
			this->preturiBauturi[i] = copie.preturiBauturi[i];
		}
	}
	else {
		this->preturiBauturi = nullptr;
	}
}

// Operatorul de atribuire (Assignment Operator) - este apelat atunci cand un obiect existent este atribuit altui obiect existent.

Cafenea& operator=(const Cafenea& copie) {
	if (this == &copie) {
		return *this;
	}

	if (this->preturiBauturi != nullptr) {
		delete[] this->preturiBauturi;
		this->preturiBauturi = nullptr;
	}

	this->denumire = copie.denumire;
	this->tip = copie.tip;
	this->incasariZilnice = copie.incasariZilnice;
	this->nrBauturi = copie.nrBauturi;

	if (copie.preturiBauturi != nullptr && copie.nrBauturi > 0) {
		this->preturiBauturi = new float[copie.nrBauturi];
		for (int i = 0; i < copie.nrBauturi; i++) {
			this->preturiBauturi[i] = copie.preturiBauturi[i];
		}
	}
	else {
		this->preturiBauturi = nullptr;
	}

	return *this;
}

// Encapsulare (Getteri si Setteri) - metode publice care permit accesul controlat la atributele private ale clasei.

float* getPreturiBauturi() const { // const la finalul metodei garanteaza ca apelarea acestei metode nu va modifica starea / atributele obiectului
	if (this->preturiBauturi == nullptr || this->nrBauturi == 0) {
		return nullptr;
	}
	float* copie = new float[this->nrBauturi];
	for (int i = 0; i < this->nrBauturi; i++) { // permite copierea valorilor din tabloul preturiBauturi in tabloul copie pentru a preveni modificarea directa a acestuia din exteriorul clasei
		copie[i] = this->preturiBauturi[i]; // copierea valorilor din tabloul preturiBauturi in tabloul copie pentru a preveni modificarea directa a acestuia din exteriorul clasei
	}
	return copie;  // returneaza o copie a tabloului de preturi pentru a preveni modificarea directa a acestuia din exteriorul clasei

}
void setPreturiBauturi(const float* noiPreturi, int nouNrBauturi) { // permite setarea unui nou tablou de preturi pentru obiectul curent, inlocuind vechiul tablou daca exista
	if (noiPreturi != nullptr && nouNrBauturi > 0) { // verifica daca tabloul de preturi transmis ca parametru nu este nullptr si are un numar valid de elemente
		if (this->preturiBauturi != nullptr) { // daca tabloul de preturi existent nu este nullptr, elibereaza memoria alocata anterior pentru a preveni scurgerile de memorie
			delete[] this->preturiBauturi; // elibereaza memoria alocata anterior pentru a preveni scurgerile de memorie
		}
		this->nrBauturi = nouNrBauturi; // seteaza numarul de bauturi la noul numar transmis ca parametru
		this->preturiBauturi = new float[nouNrBauturi]; // aloca dinamic un nou tablou de preturi cu dimensiunea noului numar de bauturi
		for (int i = 0; i < nouNrBauturi; i++) { // copiaza valorile din tabloul de preturi transmis ca parametru in noul tablou al obiectului curent
			this->preturiBauturi[i] = noiPreturi[i]; // copierea valorilor din tabloul de preturi transmis ca parametru in noul tablou al obiectului curent
		}
	}
}

// Operatorul index []
// permite accesul la elementele tabloului de preturi prin intermediul unui index, similar cu un tablou normal

float& operator[](int index) {
	if (index >= 0 && index < this->nrBauturi && this->preturiBauturi != nullptr) { // verifica daca indexul este valid si daca tabloul de preturi nu este nullptr
		return this->preturiBauturi[index]; // returneaza referinta la elementul de la indexul specificat, permitand modificarea acestuia
	}
	throw out_of_range("Index invalid sau tabloul de preturi este null."); // arunca o exceptie daca indexul este invalid sau tabloul de preturi este nullptr
}

// Operatorul +=
// modifica obiectul curent adaugand suma la incasari si returneaza *this prin referinta ptr apeluri de tipul (c1 += suma += suma2) etc.

Cafenea& operator+=(float suma) {
	if (suma > 0) { // verifica daca suma de adaugat }
		this->incasariZilnice += suma; // adauga suma la incasarile zilnice ale cafenelei
	}
	return *this;
}

// Operatorul negatie !
// permite verificarea daca incasarile zilnice sunt pozitive sau nu, returnand true daca sunt pozitive si false altfel

bool operator!() const {
	return this->nrBauturi == 0 || this->preturiBauturi == nullptr; // returneaza true daca meniul este gol. Permite scrierea codului intuitiv : 
																	// if (!cafenea) { cout << "Meniul este gol!";
}

// Operatorii de incrementare (++) 
// permit incrementarea incasarilor zilnice ale cafenelei, fie prin preincrementare (++cafenea), fie prin postincrementare (cafenea++)

// 1. Pre-incrementare (++ob) - modifica obiectul curent si returneaza referinta la acesta
Cafenea& operator++() {
	this->incasariZilnice += 10.0f;
	return *this;
}

// 2. Post-incrementare (ob++) - modifica obiectul curent, dar returneaza o copie a starii anterioare a acestuia
Cafenea operator++(int) {
	Cafenea copie = *this; // creeaza o copie a obiectului curent
	this->incasariZilnice += 10.0f; // incrementeaza incasarile zilnice ale cafenelei
	return copie; // returneaza copia anterioara a obiectului
}

// Operatorul de comparare < si Cast Explicit
bool operator<(const Cafenea& c) const { // compara obiectul curent cu alt obiect de tip Cafenea, returnand true daca obiectul curent are mai putine bauturi decat cel comparat
	return this->nrBauturi < c.nrBauturi; // returneaza true daca obiectul curent are mai putine bauturi decat cel comparat, false altfel
}

explicit operator float() const { // returneaza suma incasarilor zilnice ale cafenelei, permitand conversia explicita a obiectului in float
	if (this->nrBauturi == 0 || this->preturiBauturi == nullptr) { // verifica daca tabloul de preturi este nullptr sau daca numarul de bauturi este 0, caz in care returneaza 0.0f
		return 0.0f; // returneaza 0.0f daca tabloul de preturi este nullptr sau daca numarul de bauturi este 0
	}
	float suma = 0; // calculeaza suma preturilor bauturilor pentru a returna media acestora
	for (int i = 0; i < this->nrBauturi; i++) { // bucla pentru a calcula suma preturilor bauturilor
		suma += this->preturiBauturi[i]; // adauga pretul fiecarei bauturi la suma totala
	}
	return suma / this->nrBauturi; // returneaza media preturilor bauturilor
}



////////////////////////////////

// Prietenia in C++ (friend) si Operatori Stream (In/Out)
// deoarece operatorul << are in stanga sa un stream (std::cout), iar in dreapta obiectul "Cafenea", 
//acesta nu poate fi membru al clasei, deoarece primul parametru trebuie sa fie un obiect de tip stream.

friend ostream& operator<<(ostream& out, const Cafenea& c);
friend istream& operator>>(istream& in, Cafenea& c);
};

// friend : ofera acestei functii externe acces direct la membrii privati (private:) ai clasei, 
// permitand afisarea si citirea obiectelor Cafenea fara a expune atributele private in mod public.

ostream& operator<<(ostream& out, const Cafenea& c) { // supraincarca operatorul << pentru a permite afisarea obiectelor de tip Cafenea in mod intuitiv (cout << c1;)
	out << "\n[ID " << c.id << "] Cafeneaua '" << c.denumire << "'"; // afiseaza ID-ul si denumirea cafenelei
	out << " | Tip: " << (c.tip == TO_GO ? "To Go" : (c.tip == BISTRO ? "Bistro" : "Lounge"));		// afiseaza tipul cafenelei in functie de valoarea enum-ului TipCafenea
	out << " | Incasari: " << c.incasariZilnice << " lei"; // afiseaza incasarile zilnice ale cafenelei
	out << "\n  Meniu (" << c.nrBauturi << " bauturi): "; // afiseaza numarul de bauturi din meniu
	if (c.preturiBauturi != nullptr && c.nrBauturi > 0) { // afiseaza preturile bauturilor daca tabloul de preturi nu este nullptr si numarul de bauturi este mai mare ca 0
		for (int i = 0; i < c.nrBauturi; i++) { // bucla pentru a afisa preturile bauturilor
			out << c.preturiBauturi[i] << (i == c.nrBauturi - 1 ? " lei." : " lei, "); // afiseaza pretul fiecarei bauturi, adaugand un punct la finalul ultimului pret si o virgula intre celelalte
		}
	}
	else { // daca tabloul de preturi este nullptr sau numarul de bauturi este 0, afiseaza un mesaj corespunzator
		out << "Fara produse.";
	}
	out << endl;
	return out; // Returneaza stream-ul out pentru a permite operatia in lant (cout << c1 << c2;)
}

istream& operator>>(istream& in, Cafenea& c) { // permite citirea obiectelor de tip Cafenea in mod intuitiv (cin >> c1;)
	cout << "Denumire: "; // afiseaza mesajul pentru a cere denumirea cafenelei
	in >> c.denumire; // citeste denumirea cafenelei de la utilizator
	cout << "Tip (1-TO_GO, 2-BISTRO, 3-LOUNGE): "; // afiseaza mesajul pentru a cere tipul cafenelei
	int tempTip; // citeste tipul cafenelei ca intreg pentru a-l converti ulterior in TipCafenea
	in >> tempTip; // citeste tipul cafenelei de la utilizator 
	c.tip = static_cast<TipCafenea>(tempTip); // converteste intregul citit in TipCafenea folosind static_cast pentru a asigura tipul corect al enum-ului
	cout << "Incasari zilnice: "; // afiseaza mesajul pentru a cere incasarile zilnice ale cafenelei
	in >> c.incasariZilnice; // citeste incasarile zilnice ale cafenelei de la utilizator 

	cout << "Numar bauturi: "; // afiseaza mesajul pentru a cere numarul de bauturi din meniu
	in >> c.nrBauturi; // citeste numarul de bauturi din meniu de la utilizator 

	// Curatam memoria existenta inainte de citirea unui nou tablou
	if (c.preturiBauturi != nullptr) {
		delete[] c.preturiBauturi;
	}

	if (c.nrBauturi > 0) { // daca numarul de bauturi este mai mare ca 0, aloca un nou tablou pentru preturi si citeste valorile acestora de la utilizator
		c.preturiBauturi = new float[c.nrBauturi]; // aloca dinamic un tablou de preturi pentru bauturi
		for (int i = 0; i < c.nrBauturi; i++) { // bucla pentru a citi preturile bauturilor de la utilizator
			cout << "Pret bautura [" << i << "]: "; // afiseaza mesajul pentru a cere pretul fiecarei bauturi
			in >> c.preturiBauturi[i]; // citeste pretul fiecarei bauturi de la utilizator
		} 
	}
	else { // daca numarul de bauturi este 0 sau mai mic, seteaza pointerul preturiBauturi pe nullptr pentru a preveni referentierea unor adrese de memorie invalide
		c.preturiBauturi = nullptr;
	}

	return in; // Returneaza stream-ul in pentru a permite operatia in lant (cin >> c1 >> c2;)
}