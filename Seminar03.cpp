#include<iostream>
#include<string>

using namespace std;

enum Zona { CENTRALA = 1, PERIFERICA = 2 };

class Cofetarie {
private:
	const int id;
	Zona zona;
	string denumire;
	float vanzariTotale;
	int nrProduse;
	float* preturi;
public:
	static int nrCofetarii;
	Cofetarie() :id(++nrCofetarii) {
		//this->id = 0;
		this->denumire = "Cofetarie generala";
		this->vanzariTotale = 0;
		this->zona = PERIFERICA;
		this->nrProduse = 0;
		this->preturi = nullptr;
	}

	Cofetarie(int id, string denumire, float vanzariTotale, int nrProduse, float* preturi, Zona zona) :id(id) {
		//this->id = 0;
		nrCofetarii++;
		this->denumire = denumire;
		this->vanzariTotale = vanzariTotale;
		this->zona = zona;
		this->nrProduse = nrProduse;
		this->preturi = new float[nrProduse];
		for (int i = 0; i < this->nrProduse; i++)
		{
			this->preturi[i] = preturi[i];
		}
		delete[] preturi;
	}

	Cofetarie(const Cofetarie& copie) :id(++nrCofetarii) {
		this->denumire = copie.denumire;
		this->nrProduse = copie.nrProduse;
		this->vanzariTotale = copie.vanzariTotale;
		this->zona = copie.zona;

		if (copie.preturi != nullptr) {
			this->preturi = new float[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->preturi[i] = copie.preturi[i];
			}
		}
		else {
			this->preturi = nullptr;
		}

	}

	void operator=(const Cofetarie& copie) {
		this->denumire = copie.denumire;
		this->nrProduse = copie.nrProduse;
		this->vanzariTotale = copie.vanzariTotale;
		this->zona = copie.zona;

		if (this->preturi != nullptr) {
			delete[] this->preturi;
			this->preturi = nullptr;
		}

		if (copie.preturi != nullptr) {
			this->preturi = new float[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->preturi[i] = copie.preturi[i];
			}
		}
		else {
			this->preturi = nullptr;
		}

	}

	//get si set pentru nrProduse
	int getNrProduse() {
		return this->nrProduse;
	}

	void setNrProduse(int valoareNoua) {
		if (valoareNoua >= 0) {
			this->nrProduse = valoareNoua;
		}
		else {
			throw exception();
			//throw 404;
			//throw "Valoare negativa!";
		}
	}

	//get si set pentru preturi
	float* getPreturi() {
		//return this->preturi;
		float* vPreturi = new float[this->nrProduse];
		for (int i = 0; i < this->nrProduse; i++)
		{
			vPreturi[i] = this->preturi[i];
		}
		return vPreturi;
	}

	void setPreturi(float* vPreturi, int dim) {
		setNrProduse(dim);

		if (this->preturi != nullptr) {
			delete[] this->preturi;
			this->preturi = nullptr;
		}

		if (vPreturi != nullptr) {
			this->preturi = new float[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->preturi[i] = vPreturi[i];
			}

			delete[] vPreturi;
		}
		else {
			this->preturi = nullptr;
		}
	}

	void afisare() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Vanzari totale: " << this->vanzariTotale;
		cout << endl << "Zona: ";
		if (this->zona == 1) {
			cout << "CENTRALA";
		}
		else {
			cout << "PERIFERICA";

		}
		cout << endl << "Nr. produse: " << this->nrProduse;
		if (this->nrProduse > 0) {
			cout << " cu urmatoarele preturi: ";
			for (int i = 0; i < this->nrProduse - 1; i++)
			{
				cout << this->preturi[i] << " lei, ";
			}
			cout << this->preturi[this->nrProduse - 1] << " lei.";
		}
	}

	bool operator<(const Cofetarie& c) {
		return this->nrProduse < c.nrProduse;
	}

	~Cofetarie() {
		cout << endl << "S-a apelat destructorul!";
		if (this->preturi != nullptr) {
			delete[] this->preturi;
		}
	}

	void operator+=(float vanzariTotaleDeAdunat) {
		this->vanzariTotale += vanzariTotaleDeAdunat;
	}

	//operatorul negatie
	bool operator!() {
		return this->vanzariTotale > 0;
	}

	//operatorul functie
	float operator()(float valoareDeAdaugat)
	{
		return this->vanzariTotale + valoareDeAdaugat;
	}

	//operatorul index
	float& operator[](int index) {
		if (index >= 0 && index < this->nrProduse) {
			return this->preturi[index];
		}
		else {
			throw exception();
		}
	}

	//operator << / operator de afisare
	friend void operator<<(ostream& out, Cofetarie c) {
		out << endl << "Operator de afisare: ";
		out << endl << "Id: " << c.id;
		out << endl << "Denumire: " << c.denumire;
		out << endl << "Vanzari totale: " << c.vanzariTotale;
		out << endl << "Zona: ";
		if (c.zona == CENTRALA) out << "CENTRALA";
		if (c.zona == PERIFERICA) out << "PERIFERICA";
		out << endl << "Nr produse: " << c.nrProduse;
		if (c.preturi != nullptr) {
			out << endl << "Preturi: ";
			for (int i = 0; i < c.nrProduse - 1; i++) {
				out << c.preturi[i] << " grame, ";
			}
			out << c.preturi[c.nrProduse - 1] << " grame.";
		}
	}

	friend void operator>>(istream& in, Cofetarie& c);

	//postincrementare ob++
	Cofetarie operator++(int) {
		Cofetarie copie = *this;
		this->vanzariTotale++;

		return copie;
	}

	//preincrementare ++ob
	Cofetarie operator++() {
		this->vanzariTotale++;
		return *this;
	}

	//cast explicit
	explicit operator int() {
		return this->nrProduse;
	}
};

void operator>>(istream& in, Cofetarie& c) {
	cout << endl << "Vanzari totale: ";
	in >> c.vanzariTotale;

	cout << endl << "Denumire: ";
	in >> c.denumire;

	cout << endl << "Zona: ";
	int zona;
	in >> zona;

	if (zona == 1) c.zona = CENTRALA;
	if (zona == 2) c.zona = PERIFERICA;

	cout << endl << "Nr produse: ";
	in >> c.nrProduse;

	cout << endl << "Preturi: ";

	if (c.preturi != nullptr) {
		delete[] c.preturi;
		c.preturi = nullptr;
	}

	c.preturi = new float[c.nrProduse];
	for (int i = 0; i < c.nrProduse; i++) {
		cout << endl << "preturi[" << i << "]: ";
		in >> c.preturi[i];
	}
}

int Cofetarie::nrCofetarii = 0;

void main() {
	Cofetarie cofetarieGenerala;

	if (!cofetarieGenerala) {
		cout << endl << "Vanzarile totale sunt pozitive!";
	}
	else {
		cout << endl << "Nu exista vanzari!";
	}

	cout << endl << cofetarieGenerala(100);

	cout << cofetarieGenerala;

	float* preturi = new float[3] {18.5, 24, 15.5};
	Cofetarie* cofetarieRomana = new Cofetarie(7, "CofetarieRomana", 97000, 3, preturi, CENTRALA);
	(*cofetarieRomana) += 100;

	if (cofetarieGenerala < *cofetarieRomana) {
		cout << endl << "Cofetaria Generala are mai putine produse decat cofetaria Romana!";
	}
	else {
		cout << endl << "Cofetaria Romana are mai putine produse decat cofetaria Generala!";
	}

	(*cofetarieRomana)[0] = 20;

	cout << endl << (*cofetarieRomana)[0];

	cout << *cofetarieRomana;

	//Cofetarie cofetarieUnirii;
	//cin >> cofetarieUnirii;
	//cout << cofetarieUnirii;

	Cofetarie cofetarie1 = cofetarieGenerala++;

	cout << cofetarie1;
	cout << cofetarieGenerala;

	Cofetarie cofetarie2 = ++cofetarieGenerala;

	cout << cofetarie2;
	cout << cofetarieGenerala;

	cout << endl << "Cast cofetarie -> int: " << int(*cofetarieRomana);

	delete cofetarieRomana;

	cout << endl << "Numar cofetarii: " << Cofetarie::nrCofetarii;
}