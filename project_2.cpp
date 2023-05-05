#include <bits/stdc++.h>
#include <ostream>

using namespace std;

class Abonament{
protected:
    string nume_abonament;
    float pret;
    int perioada;
public:
    // Constructor neparametrizat

    Abonament(){
        this -> nume_abonament = "";
        this -> pret = 0;
        this -> perioada = 0;
    }
    // Constructor parametrizat
    Abonament(string nume_abonament, float pret, int perioada){
        this -> nume_abonament = nume_abonament;
        this -> pret = pret;
        this -> perioada = perioada;
    }
    // Copy constructor
    Abonament(const Abonament &abonament){
        nume_abonament = abonament.nume_abonament;
        pret = abonament.pret;
        perioada = abonament.perioada;
    }
    virtual Abonament* nou() {
        return new Abonament(*this);
    };
    // Destructor
    ~Abonament() {}
    // Getteri
    string GetNume(){
        return nume_abonament;
    }
    virtual float GetPret(){
        return pret * perioada;
    }
    int GetPerioada(){
        return perioada;
    }
    //Setteri
    void SetNume(string nume_abonament){
        this -> nume_abonament = nume_abonament;
    }
    void SetPret(float pret){
        this -> pret = pret;
    }
    void SetPerioada(int perioada) {
        this->perioada = perioada;
    }
    // Supraincarcare '='
    Abonament& operator=(const Abonament &abonament){
        if(this == &abonament)
            return *this;
        nume_abonament = abonament.nume_abonament;
        pret = abonament.pret;
        perioada = abonament.perioada;
        return *this;
    }
    // Suparincarcare '>>'
    friend std:: istream& operator>>(std::istream &in, Abonament &abonament){
        in >> abonament.nume_abonament >> abonament.pret >> abonament.perioada;
        return in;
    }

    virtual void display(){
        cout << "Nume: " << nume_abonament << '\n';
        cout << "Pret: " << GetPret() <<'\n';
        cout << "Perioada: " << perioada << '\n';
    }

};

class Abonament_Premium : public Abonament{
    int reducere;
public:
    // Constructor neparametrizat
    Abonament_Premium(){
        reducere = 0;
    }
    virtual Abonament_Premium* nou() {
        return new Abonament_Premium(*this);
    }
    // Constructor parametrizat
    Abonament_Premium(int reducere){ this -> reducere = reducere;}
    // Evidentierea transmiterii parametrilor catre constructorul de baza
    Abonament_Premium(string nume_abonament, float pret, int perioada, int reducere): Abonament(nume_abonament, pret, perioada), reducere(reducere){}
    // Copy constructor
    Abonament_Premium(const Abonament_Premium &abonament_premium){
        reducere = abonament_premium.reducere;
    }
    // Destructor
    ~Abonament_Premium(){}
    // Getteri
    int GetReducere(){
        return reducere;
    }
    // Setteri
    void SetReducere(int reducere){
        this -> reducere = reducere;
    }
    // Supraincarcare '='
    Abonament_Premium& operator=(const Abonament_Premium &abonament_premium){
        if(this == &abonament_premium)
            return *this;
        reducere = abonament_premium.reducere;
        return *this;
    }
    // Supraincarcare '>>'
    friend std::istream& operator>>(std::istream &in, Abonament_Premium &abonament_premium){
        in >> abonament_premium.nume_abonament >> abonament_premium.pret >> abonament_premium.perioada>> abonament_premium.reducere;
        return in;
    }
    float GetPret() override {
        return (Abonament::pret - (reducere / 100.0) * Abonament::pret) * perioada;
    }

    void display() override{
        cout << "Nume: " << GetNume() << '\n';
        cout << "Pret: " << GetPret() << '\n';
        cout << "Perioada " << GetPerioada() << '\n';
        cout << "Reducere: " << GetReducere() << '\n';

    }

};

class Persoana{
protected:
    int id;
    string nume;
    string cnp;
    static int UrmId;
public:
    // Constructor neparametrizat
    Persoana(){
        id = 0;
        nume = "";
        cnp = "";
    }
    // Constructor parametrizat
    Persoana(string nume, string cnp): id(GetUrmId()), nume(nume), cnp(cnp) {};
    // Copy constructor
    Persoana(const Persoana &persoana){
        id = persoana.id;
        nume = persoana.nume;
        cnp = persoana.cnp;
    }
    // Destructor
    virtual ~Persoana() {}
    // Getteri
    int GetId(){
        return id;
    }
    static int GetUrmId(){
        return UrmId++;
    }
    // Supraincarcare '='
    Persoana& operator=(const Persoana &persoana){
        if(this == &persoana)
            return *this;
        id = persoana.id;
        nume = persoana.nume;
        cnp = persoana.cnp;
    }
    // Supraincarcare '>>'
    friend std::istream& operator>>(std::istream &in, Persoana &persoana){
        in >> persoana.id >> persoana.nume >> persoana.cnp;
    }
    // Supraincarcare '<<'
    friend ostream& operator<<(ostream &out, Persoana &persoana){
        out << "Id: " << persoana.id << '\n';
        out << "Nume: " << persoana.nume << '\n';
        out << "Cnp: " << persoana.cnp;
        return out;
    }
};
int Persoana::UrmId = 1;
class Abonat : public Persoana{
    string nr_telefon;
    Abonament* x;
public:
    // Constructor neparametrizat
    Abonat(){
        nr_telefon = "-";
        x = nullptr;
    }
    // Constructor parametrizat
    Abonat(string nume, string cnp, string nr_telefon, Abonament* x) : Persoana(nume, cnp), nr_telefon(nr_telefon), x(x) {};
    // Copy constructor
    Abonat(const Abonat &abonat) : Persoana(abonat){
        nr_telefon = abonat.nr_telefon;
        x = abonat.x -> nou();
    }
    // Destructor
    ~Abonat(){ delete this -> x; }
    // Getteri
    string GetNumar(){
        return nr_telefon;
    }
    Abonament* GetAbonament(){
        return this -> x;
    }
    // Supraincarcare '='
    Abonat& operator=(const Abonat &abonat){
        if(this == &abonat)
            return *this;
        Persoana::operator=(abonat);
        nr_telefon = abonat.nr_telefon;
        this -> x = abonat.x -> nou();
        //x = abonat.x;
    }
    // Supraincarcare '>>'
    friend std::istream& operator>>(std::istream &in, Abonat &abonat){
        cout << "Introduceti numar telefon: ";
        in >> abonat.nr_telefon;
        abonat.id = abonat.GetUrmId();
        cout << "Introduceti nume persoana: ";
        in >> abonat.nume;
        cout << "Introduceti CNP: ";
        in >> abonat.cnp;
        cout << "Doriti sa achizitionati abonament premium? -> ";
        if(abonat.x) delete abonat.x;
        string raspuns;
        in >> raspuns;
        if(raspuns == "nu"){
            abonat.x = new Abonament();
            cout << "Introduceti numele, pretul si perioada abonamentului simplu: ";
            in >> *(abonat.x);
        }
        else{
            abonat.x = new Abonament_Premium();
            cout << "Introduceti numele, pretul, perioada si reducerea abonamentului premium: ";
            in >> *dynamic_cast<Abonament_Premium *>(abonat.x);
        }
        return in;
    }
    // Supraincarcare '<<'
    friend ostream& operator<<(ostream &out, Abonat &abonat){
        out << "Numar telefon: " << abonat.nr_telefon << '\n';
        out << "Date abonament: ";
        abonat.x->display();
        out << "Id: " << abonat.id << '\n';
        out << "Nume: " << abonat.nume << '\n';
        out << "Cnp: " << abonat.cnp << '\n';
        return out;
    }
};
class Clienti{
    vector<Abonat> abonati;
public:
    // Constructor neparametrizat
    Clienti() : abonati() {};
    // Constructor parametrizat
    Clienti(Abonat abonat){
        abonati.push_back(abonat);
    }
    // Copy constructor
    Clienti(const Clienti &client){
        abonati = client.abonati;
    }
    // Destructor
    ~Clienti() {};
    void adauga(Abonat abonat){
        abonati.push_back(abonat);
    }
    void sterge(){
        if(abonati.size())
            abonati.pop_back();
        else{
            cout << "Lista este deja goala" << '\n';
        }
    }
    float SumaTotala(){
        float res = 0;
        for(int i = 0; i < abonati.size(); ++i)
            res += abonati[i].GetAbonament()->GetPret();
        return res;
    }
    int NrAbonatiPremium(){
        int res = 0;
        for(int i = 0; i < abonati.size(); ++i)
            if(dynamic_cast<Abonament_Premium*>(abonati[i].GetAbonament()) != nullptr)
                res ++;
        return res;
    }
    friend ostream &operator<<(ostream &out, const Clienti &clienti) {
        // cout << clienti.abonati.size();
        for(auto x : clienti.abonati){
            out << x << '\n';
        }
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Clienti& clienti) {
        int n;
        cout << "Introduceti numarul de abonati: ";
        in >> n; // Citim numarul de abonati
        clienti.abonati.resize(n); // Redimensionam vectorul de abonati
        for(int i = 0; i < n; i++) {
            // Citim datele pentru fiecare abonat
            cout << "Introduceti datele clientului " << i + 1 << " : ";
            in >> clienti.abonati[i];
        }
        return in;
    }
    Clienti& operator=(const Clienti& other) {
        if (this == &other) {
            return *this;
        }
        // copierea vectorului de abonati
        abonati.clear();
        for (const auto& abonat : other.abonati) {
            abonati.push_back(abonat);
        }
        return *this;
    }

};
class Menu{
    const string citire_clienti = "Citire-clienti";
    const string adauga_client = "Adauga-client";
    const string afisare_clienti = "Afisare-clienti";
    const string suma_totala = "Suma-totala";
    const string numar_premium = "Numar-premium";
    const string sterge_client = "Sterge-client";
    const string final = "Final";

    Clienti clienti;
    void Instructiuni(){
        cout << "Instructiuni de utilizare: " << '\n';
        cout << citire_clienti << " -> Citeste lista de clienti" << '\n';
        cout << adauga_client << " -> Adauga un client la lista curent" << '\n';
        cout << afisare_clienti << " -> Afiseaza lista clientilor" << '\n';
        cout << suma_totala << " -> Afiseaza suma de bani de la toti abonatii" << '\n';
        cout << numar_premium << " -> Afiseaza numarul de abonamente premium" << '\n';
        cout << sterge_client << " -> Sterge ultimul client din lista" << '\n';
        cout << final << " -> Inchide rularea programului" << '\n';
    }
public:
    void RuleazaComenzi(){
        Instructiuni();
        string comanda;
        cin >> comanda;
        while(comanda != final){
            if(comanda == citire_clienti)
                cin >> this -> clienti;
            else if(comanda == adauga_client){
                Abonat abonat_nou;
                cin >> abonat_nou;
                this -> clienti.adauga(abonat_nou);
            }
            else if(comanda == afisare_clienti){
                cout << this -> clienti << '\n';
            }
            else if(comanda == suma_totala){
                cout << this -> clienti.SumaTotala() << '\n';
            }
            else if(comanda == numar_premium){
                cout << this -> clienti.NrAbonatiPremium() << '\n';
            }
            else if(comanda == sterge_client){
                this -> clienti.sterge();
            }
            else{
                cout << "Comanda nu este valida, introduceti comanda valida: " << '\n';
            }
            cout << "Introduceti o comanda noua: ";
            cin >> comanda;
        }
    }
};
void testDownCast(){
    Abonament* abonament = new Abonament_Premium("Abonament premium", 50, 12, 10);
    Abonament_Premium* abonament_premium = dynamic_cast<Abonament_Premium*>(abonament);
    if (abonament_premium != nullptr) {
        int reducere = abonament_premium->GetReducere();
        cout << "Reducerea pentru abonamentul premium este: " << reducere << "%" << endl;
    }
}
int main(){
    Menu ex;
    ex.RuleazaComenzi();
    //testDownCast();
    return 0;
}