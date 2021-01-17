#include<vector>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define V 6
//Mos Craciun va putea extrage din fisierul dorinte scrisorile si datele despre copii
class Mos_Craciun
{
private:
	vector<vector<string>> Lista_Dorinte;
	vector<string> v;
	int lines = 0;
public:
	Mos_Craciun();
	~Mos_Craciun();
	void citire_csv(string);
	vector<string> LISTA_ORASE;
	vector<vector<string>> get_Lista_Dorinte();
	vector<string> get_v();
	int get_lines();
	int minKey(int key[], bool mstSet[]);
	void printMST(int parent[], int graph[V][V]);
	void primMST(int graph[V][V]);
	void calculareDrum();
	virtual void afisare_dorinte();

};
Mos_Craciun::Mos_Craciun()
{

}
Mos_Craciun::~Mos_Craciun()
{
	cout << "Obiectul a fost distrus" << endl;
}
vector<vector<string>> Mos_Craciun::get_Lista_Dorinte()
{
	return this->Lista_Dorinte;
}
vector<string> Mos_Craciun::get_v()
{
	return this->v;
}
int Mos_Craciun::get_lines()
{
	return this->lines;
}
//vom folosi un fisier csv , dorinte.txt, unde vom avea datele din scrisoare
//respectiv nume, prenume, varsta, oras,lista de dorinte, id copil(cuminte/rau),culoare plic
void Mos_Craciun::citire_csv(string file)
{
	ifstream in(file);
	string line, field;
	this->lines = 0;

	while (getline(in, line))
	{
		this->v.clear();
		stringstream ss(line);
		++this->lines;

		while (getline(ss, field, ','))
		{
			this->v.push_back(field);
		}
		this->Lista_Dorinte.push_back(this->v);
	}
Exceptie:
	try
	{
		if (lines == 0)

			throw lines;
	}
	catch (int lines)
	{
		cout << "Fisierul e gol" << endl;
		goto Exceptie;
	}

	in.close();
}
//afisarea cadourilor de copii
void Mos_Craciun::afisare_dorinte()
{

	for (int i = 0;i < this->lines;i++)
		cout << Lista_Dorinte[i][4] << endl;

}

//In continuarea vom calcula traseul primit de Mos Craciun
int Mos_Craciun::minKey(int key[], bool mstSet[])
{
	// Initialize min value  
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}
// O func?ie utilitarã pentru a imprima fi?ierul construit stocat în pãrinte []
void Mos_Craciun::printMST(int parent[], int graph[V][V])
{
	int suma = 0;
	cout << endl;
	cout << "Margine \t Greutate\n" << endl;

	for (int i = 1; i < this->LISTA_ORASE.size(); i++)
	{
		cout << this->LISTA_ORASE.at(parent[i])
			<< " - " << this->LISTA_ORASE.at(i)
			<< " \t" << graph[i][parent[i]] << " \n";

		suma = suma + graph[i][parent[i]];

		cout << "Costul minim= " << suma << endl;
	}
	//cout << "Costul minim= " << suma << endl;

}


// Func?ie pentru construirea si tipãrirea arborelui minim de acoperire pentru
// un grafic reprezentat folosind adiacenta
// reprezentare matricialã
void Mos_Craciun::primMST(int graph[V][V])
{
	int parent[V];// Matrice pentru a stoca arborele minim construit
	int key[V];// Valori cheie utilizate pentru a alege marginea greutãtii minime în tãieturã
	bool mstSet[V];//Pentru a reprezenta un set de vârfuri incluse în MST

	for (int i = 0; i < V; i++)
		key[i] = INT_MAX, mstSet[i] = false;//initializare chei ca infinit

	key[0] = 0;//facem tasta 0 astfel încât acest vârf sã fie ales ca primul vârf.
	parent[0] = -1;

	for (int count = 0; count < V - 1; count++)
	{
		// Alegem vârful cheii minime din
		// set de vârfuri care nu sunt încã incluse în arborele minim
		int u = minKey(key, mstSet);
		// Adãugam vârful ales în setul arborele minim
		mstSet[u] = true;

		for (int v = 0; v < V; v++)

			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
		// graficul [u] [v] este diferit de zero numai pentru vârfurile adiacente ale m
	   // mstSet [v] este fals pentru vârfurile care nu sunt încã incluse în MST
	  // Actualiza?i cheia numai dacã graficul [u] [v] este mai mic decât cheia [v]
	}
	printMST(parent, graph);
}


void Mos_Craciun::calculareDrum()
{
	//matricea de adiacenta a grafului de orase 
	int graph[V][V] = {
					 { 0, 3852, 3772, 0, 0, 0 },
					{ 3852, 0, 172, 0, 276, 185 },
					{ 3772, 172, 0, 290, 278, 0 },
					{ 0, 0, 290, 0, 38 , 471 },
					{ 0, 276, 278, 38, 0,446 },
					{ 0, 185, 0 ,471, 446, 0 }
	};
	primMST(graph);
}

template<typename X>
X exMax(X x, X y)
{
	return (x > y) ? x : y;
}
//Clasa Elfi se ocupa de administrarea bugetului pentru fiecare copil
//astfel incat sa se incadreze in suma de 100$(bun), respectiv 10$(rau)
class Elfi : public Mos_Craciun
{
	int total = 0;
	int suma = 0;
	int numar_acadele = 0;
	int numarCarbuni = 0;
	int contor = 0;
	int contor2 = 0;
	const char delim = '*';
	string acadele;
	vector<string> id_copil = { "bun","bun","rau","bun","bun" };
public:
	friend class Doamna_Craciun;
	Elfi();
	~Elfi();
	int lines_Inventar = 0;
	void atribuire();
	vector<vector<string>> LISTA_DORINTE;
	vector<string> ve;
	int LINES;
	vector<vector<string>> Inventar;
	vector<string> vec;
	vector<string> lista_Orase;
	vector<string> Lista_Orase();
	vector<vector<string>> COPIE;
	vector<vector<string>> get_Copie();
	int get_Acadele();
	int get_Carbuni();
	string Lista_Jucarii;
	vector<string> liste_finale_cadouri;
	void afisare_jucarii();
	void citire_inventar(string);
	void afisare_inventar();
	vector<string> copie;
	void tokenize(std::string const &str, const char delim, std::vector<std::string> &out);
	vector<int> pozitii;
	vector<string> final;
	string cadouri = "";
	void afisare_dorinte()
	{
		for (int i = 0;i < this->lines_Inventar;i++)
		{
			cout << Inventar[i][0] << "," << Inventar[i][1] << endl;
		}
	}
};
Elfi::Elfi()
{

}
Elfi::~Elfi()
{
	cout << "Obiectul este distrus" << endl;
}

void Elfi::atribuire()
{
	this->LISTA_DORINTE = get_Lista_Dorinte();
	this->ve = get_v();
	this->LINES = get_lines();


}
//functie ajutatoare pentru a separa cadourile din lista de simbolul *
void Elfi::tokenize(string const &str, const char delim, vector<string> &out)
{
	stringstream ss(str);
	string s;
	while (std::getline(ss, s, delim)) {
		out.push_back(s);
	}
}

//vom adauga inca un fisier csv "inventar.txt" care va reprezenta ce se afla pe stoc si ce nu
void Elfi::citire_inventar(string file)
{
	ifstream in(file);
	string line, field;
	this->lines_Inventar = 0;

	while (getline(in, line))
	{
		this->vec.clear();
		stringstream ss(line);
		++this->lines_Inventar;

		while (getline(ss, field, ','))
		{
			this->vec.push_back(field);
		}
		this->Inventar.push_back(this->vec);
	}
Exceptie2:
	try
	{
		if (lines_Inventar == 0)

			throw lines_Inventar;
	}
	catch (int lines_Inventar)
	{
		cout << "Fisierul e gol" << endl;
		goto Exceptie2;
	}

	in.close();
	in.close();
}

void Elfi::afisare_inventar()
{
	for (int i = 0;i < this->lines_Inventar;i++)
	{
		cout << Inventar[i][0] << "," << Inventar[i][1] << endl;
	}

}
//functia afiseaza listele finale de cadouri
void Elfi::afisare_jucarii()
{
	atribuire();
	for (int i = 0;i < this->LINES; i++)
	{
		suma = 0;

		if (this->id_copil.at(i) == "bun")
		{
			Lista_Jucarii.clear();
			Lista_Jucarii.append(this->LISTA_DORINTE[i][4]);
			tokenize(Lista_Jucarii, delim, final);
			for (size_t i = 0;i < final.size();i++)
			{
				cout << final.at(i) << " ";
				cout << endl;
			}

			for (size_t j = 0;j < final.size();j++)
			{
				for (size_t k = 0; k < this->lines_Inventar;k++)
				{
					if (final.at(j) == Inventar[k][0])
					{

						suma = suma + stoi(this->Inventar[k][1]);
						pozitii.push_back(k);
						//retine pozitiile ultimului element adaugat
						cout << suma << endl;
						if (suma <= 100)
						{
							contor++;
							//creste numarul de copii care au suma cadourilor < 100
							if (cadouri.size() == 0)
							{
								cadouri.append(this->Inventar[k][0]);
								//adaugam jucaria in cadou
								cout << "Craciun" << endl;
								cout << cadouri;
							}
							else
							{
								//apoi vom adauga separator
								cadouri.append("*");
								//din nou adaugam un nou cadou
								cadouri.append(this->Inventar[k][0]);
							}
						}
						else
						{
							//creste numarul copiilor care au suma mai mare decat 100
							contor2++;
						}

					}
				}

			}
			if (suma > 100)

				for (int x = contor; x < pozitii.size();x++)
				{
					suma = suma - stoi(this->Inventar[pozitii[x]][1]);
				}

			// cout << "Ceva";
		//	cout << contor << endl;
			//cout << contor2 << endl;
			if (contor2 != 0 && suma == 0)//daca suma este 0 va primi cadou default
			{
				cout << "Va primi un cadou default = 100$\n";
				cout << "Set_Bakugan";
				cout << endl;
				cadouri.append("Set_Bakugan");
				suma = 100;
			}

			if (contor == 0 && contor2 == 0 && suma == 0)
			{
				cout << "Produsele date nu se gasesc in lista" << endl;
				cadouri.append("Set Bakugan");
			}

			if (this->id_copil[i] == "bun" && suma != 0)
			{
				numar_acadele = 100 - suma;//indiferent daca sunt fix 100
				acadele = to_string(numar_acadele);
				total = total + numar_acadele;//aflam numarul total de acadele
			}

			cout << "\x1b[1;35m" << total << "\x1b[0m" << endl;

		}
		//cazul copilului rau
		else if (this->id_copil[i] == "rau")
		{
			cout << endl;
			cout << "Copii rai vor primi un cadou de 10$ (pistol):(( " << endl;
			cadouri.append("pistol");
			cout << "Copii rai vor primi si un carbune" << endl;
			cadouri.append("*");
			cadouri.append("carbune");
			suma = 10;
			this->numarCarbuni++;
			acadele = "";
		}
		//adaugam in lista finala de cadouri datele+cadoruile+acadelele
		liste_finale_cadouri.push_back(LISTA_DORINTE[i][0]);
		liste_finale_cadouri.push_back(LISTA_DORINTE[i][1]);
		liste_finale_cadouri.push_back(cadouri);
		liste_finale_cadouri.push_back(LISTA_DORINTE[i][3]);
		liste_finale_cadouri.push_back(LISTA_DORINTE[i][5]);
		liste_finale_cadouri.push_back(acadele);
		COPIE.push_back(liste_finale_cadouri);

		for (int i = 0;i < liste_finale_cadouri.size();i++)
		{
			cout << "\x1b[1;92m" << liste_finale_cadouri[i] << "\x1b[0m" << " ";
			cout << endl;
		}

		if (LISTA_DORINTE[i][5] == "albastru")
		{
			for (int i = 0;i < liste_finale_cadouri.size();i++)
			{
				cout << "\x1b[34m" << liste_finale_cadouri[i] << "\x1b[0m" << " ";

			}
		}

		else if (LISTA_DORINTE[i][5] == "roz")
		{
			for (int i = 0;i < liste_finale_cadouri.size();i++)
			{
				cout << "\x1b[31m" << liste_finale_cadouri[i] << "\x1b[0m" << " ";
			}
		}

		liste_finale_cadouri.clear();
		cadouri.clear();
		contor = 0;
		contor2 = 0;
		pozitii.clear();
		contor = 0;
		contor2 = 0;
		final.clear();

	}
}

vector<string> Elfi::Lista_Orase()
{
	this->lista_Orase.clear();

	this->lista_Orase.push_back("Laponia");
	for (int i = 0;i < this->COPIE.size(); i++)
	{
		this->lista_Orase.push_back(this->COPIE[i][3]);
	}
	return this->lista_Orase;
}


//numarul de acadele total
int Elfi::get_Acadele()
{
	return this->total;
}
//copie la lista de cadouri finale
vector<vector<string>> Elfi::get_Copie()
{
	return this->COPIE;
}
//numarul de carbuni
int Elfi::get_Carbuni()
{
	return this->numarCarbuni;
}


//Clasa Troli va determina numarul de ambalaje pentru baieti, respectiv fete
class Troli
{
	vector<vector<string>> lista_troli;
	int numarAmbalajeBaieti = 0;
	int numarAmbalajeFete = 0;
public:
	Troli();
	~Troli();
	//friend class Elfi;
	void set_Lista(Elfi object);
	void Ambalare();
	void afisare();
	void Ambalare(int nrBaieti, int nrFete)//polimorfism
	{//determinarea numarul de ambalaje folosite pentru fete si baieti

		cout << "Baietii-ambalaje albastre" << endl;
		cout << "Fete-ambalaje roz" << endl;
	}
};

Troli::Troli()
{

}
Troli::~Troli()
{
	cout << "Obiectul a fost distrus" << endl;
}
void Troli::set_Lista(Elfi object)
{
	this->lista_troli = object.get_Copie();
}
void Troli::afisare()
{
	for (size_t i = 0;i < lista_troli.size();i++)
	{
		for (size_t j = 0;j < lista_troli[i].size();j++)

			cout << "Lista= " << lista_troli.at(i).at(j) << " ";
		cout << endl;
	}
}
void Troli::Ambalare()
{//determinarea numarul de ambalaje folosite pentru fete si baieti

	for (size_t i = 0;i < lista_troli.size();i++)
	{
		if (this->lista_troli[i][4] == "albastru")
		{
			this->numarAmbalajeBaieti++;
		}
		else if (this->lista_troli[i][4] == "roz")
		{
			this->numarAmbalajeFete++;
		}
	}

	cout << endl;
	cout << "Numarul de ambalaje pentru baieti este = " << this->numarAmbalajeBaieti << endl;
	cout << "Numarul de ambalaje pentru fete este =" << this->numarAmbalajeFete << endl;
}


//Doamna_Craciun va calcula bugetul extra pentru acadele+carbuni
//De asemenea ea va avea acces si la traseul lui Mos_Craciun
class Doamna_Craciun :public Elfi, public Troli
{
private:
	vector<vector<string>> Lista_Doamna_Craciun;
	int numarAcadele = 0;
	int numarCarbuni = 0;
public:
	friend class Elfi;
	Doamna_Craciun();
	~Doamna_Craciun();
	void set_Lista_Doamna_Craciun(Elfi object)
	{
		this->Lista_Doamna_Craciun = object.get_Copie();
	}
	void Afisare_Buget_Extra();
};
Doamna_Craciun::Doamna_Craciun()
{

}
Doamna_Craciun::~Doamna_Craciun()
{
	cout << "Obiectul a fost distrus" << endl;
}

void Doamna_Craciun::Afisare_Buget_Extra()
{
	double Buget = 0;
	Buget = this->get_Acadele() * 1 + this->get_Carbuni()*0.5;
	cout << endl;
	cout << "Bugetul extra este " << Buget << "$" << endl;
}
int main()
{
	Mos_Craciun mosul;
	Elfi elfi;
	Troli troli;
	Doamna_Craciun d;
	bool open = true;
	char choice;
	int nrFete = 0, nrBaieti = 0;
	//abstractizare
	elfi.citire_inventar("Inventar.txt");
	elfi.afisare_dorinte();
	Mos_Craciun *mos2 = &elfi;
	mos2->afisare_dorinte();

	troli.Ambalare(nrFete, nrBaieti);

	while (open)
	{
		cout << "***********************************************************************" << endl;
		cout << "\t Welcome To Santa's house \n" << endl;
		cout << "\t<><><><><><><><><><><><><><><><><><> \n";
		cout << "\t  Merry Christmas!:) " << endl;
		cout << "\t<><><><><><><><><><><><><><><><><><> \n" << endl;
		cout << "**********************************************************************" << endl;
		cout << "1- Afisarea Dorintelor " << endl;
		cout << "2- Afisarea Listelor de cadouri finale de la Elfi " << endl;
		cout << "3- Afisarea numarului de ambalaje roz/albastre de la Troli " << endl;
		cout << "4- Afisarea bugetului extra calculat de Doamna_Craciun" << endl;
		cout << "5- Afisarea lungimii drumului lui Mos_Craciun + orasele parcurse" << endl;
		cout << "6- Doamna Craciun vrea sa stie traseul lui Mos_Craciun " << endl;
		cout << "7- Exit " << endl;
		cout << "Please enter your choice= ";
		cin >> choice;
		switch (choice) {

		case '1':
			mosul.citire_csv("dorinte.txt");
			mosul.afisare_dorinte();
			break;
		case '2':
			elfi.citire_csv("dorinte.txt");
			elfi.citire_inventar("inventar.txt");
			elfi.afisare_jucarii();
			break;
		case '3':
			troli.set_Lista(elfi);
			troli.Ambalare();
			break;
		case '4':
			d.citire_csv("dorinte.txt");
			d.citire_inventar("inventar.txt");
			d.set_Lista_Doamna_Craciun(elfi);
			d.afisare_jucarii();
			d.Afisare_Buget_Extra();
			d.calculareDrum();
			break;
		case '5':
			elfi.citire_csv("dorinte.txt");
			mosul.citire_csv("dorinte.txt");
			elfi.citire_inventar("inventar.txt");
			elfi.afisare_jucarii();
			mosul.LISTA_ORASE = elfi.Lista_Orase();
			mosul.calculareDrum();
			break;
		case '6':
			elfi.citire_csv("dorinte.txt");
			mosul.citire_csv("dorinte.txt");
			elfi.citire_inventar("inventar.txt");
			elfi.afisare_jucarii();
			d.LISTA_ORASE = elfi.Lista_Orase();
			d.calculareDrum();
			break;
		case '7':
			open = false;
			break;
		default:
			break;
		}

	}
	return 0;
}