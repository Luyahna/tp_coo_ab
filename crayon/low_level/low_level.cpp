
#include <cpr/cpr.h>

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

using namespace std;

class Ville {
 private:
  string nom_ville;
  int code_postal;
  float prix_m2;

 public:
  Ville(string nom_ville, int code_postal, float prix_m2)
      : nom_ville(nom_ville), code_postal(code_postal), prix_m2(prix_m2) {}

  Ville(const json& data)
      : nom_ville(data["nom_ville"].get<string>()),
        code_postal(data["code_postal"].get<int>()),
        prix_m2(data["prix_m2"].get<float>()) {}

  Ville(int id) {
    cpr::Response r = cpr::Get(
        cpr::Url{"http://127.0.0.1:8000/villes/" + to_string(id) + "/"});

    json j = json::parse(r.text);
    nom_ville = j["nom_ville"].get<string>();
    code_postal = j["code_postal"].get<int>();
    prix_m2 = j["prix_m2"].get<float>();
  }

  void afficher() const {
    cout << "Nom de la ville: " << nom_ville << endl;
    cout << "Code postal: " << code_postal << endl;
    cout << "Prix au m2: " << prix_m2 << " EUR" << endl;
  }
};

class Local {
 private:
  string nom_local;
  unique_ptr<Ville> p_ville;
  int surface_local;
  int ville;

 public:
  Local(string nom_local_, int surface_local_, int ville_)
      : nom_local(nom_local_), ville(ville_), surface_local(surface_local_) {
    p_ville = make_unique<Ville>(ville);
  }

  Local(const json& data)
      : nom_local(data["nom_local"]),
        surface_local(data["surface_local"]),
        ville(data["ville"]) {
    p_ville = make_unique<Ville>(ville);
  }

  Local(int id) {
    cpr::Response r = cpr::Get(
        cpr::Url{"http://127.0.0.1:8000/local/" + to_string(id) + "/"});

    json j = json::parse(r.text);
    nom_local = j["nom_local"];
    surface_local = j["surface_local"];
    ville = j["ville"];
    p_ville = make_unique<Ville>(ville);
  }

  void afficher1() const {
    cout << "Nom du local: " << nom_local << endl;
    cout << "Surface du local: " << surface_local << " m2" << endl;
    cout << "ID de la ville: " << ville << endl;

    // p_ville->afficher(); // Affiche les informations de la ville
  }
};

class Machine {
 private:
  string nom_machine;
  int prix_machine;
  int n_serie_machine;

 public:
  Machine(string nom_machine_, int prix_machine_, int n_serie_machine_)
      : nom_machine(nom_machine_),
        prix_machine(prix_machine_),
        n_serie_machine(n_serie_machine_) {}

  Machine(const json& data)
      : nom_machine(data["nom_machine"].get<string>()),
        prix_machine(data["prix_machine"].get<int>()),
        n_serie_machine(data["n_serie_machine"].get<int>()) {}

  Machine(int id) {
    cpr::Response r = cpr::Get(
        cpr::Url{"http://127.0.0.1:8000/machine/" + to_string(id) + "/"});

    json j = json::parse(r.text);
    nom_machine = j["nom_machine"];
    prix_machine = j["prix_machine"];
    n_serie_machine = j["n_serie_machine"];
  }

  void afficherM() const {
    cout << "Nom machine: " << nom_machine << endl;
    cout << "Prix machine: " << prix_machine << "euros" << endl;
    cout << "Numero de serie: " << n_serie_machine << endl;

    // p_ville->afficher(); // Affiche les informations de la ville
  }
};

class Objet {
 private:
  string nom_objet;
  int prix_objet;

 public:
  Objet(string nom_objet_, int prix_objet_)
      : nom_objet(nom_objet_), prix_objet(prix_objet_) {}

  Objet(const json& data)
      : nom_objet(data["nom_objet"].get<string>()),
        prix_objet(data["prix_objet"].get<int>()) {}

  Objet(int id) {
    cpr::Response r = cpr::Get(
        cpr::Url{"http://127.0.0.1:8000/objet/" + to_string(id) + "/"});

    json j = json::parse(r.text);
    nom_objet = j["nom_objet"];
    prix_objet = j["prix_objet"];
  }

  void afficherO() const {
    cout << "Nom objet: " << nom_objet << endl;
    cout << "Prix objet: " << prix_objet << "euros" << endl;

    // p_ville->afficher(); // Affiche les informations de la ville
  }
};

class Usine {
 private:
  vector < unique_ptr<Machine> p_machine;
  int machine;

 public:
  Usine(int machine_) : machine(machine_) {
    p_machine = make_unique<Machine>(machine);
  }

  Usine(const json& data) : machine(data["machine"]) {
    p_machine = make_unique<Machine>(machine);
  }

  Usine(int id) {
    cpr::Response r = cpr::Get(
        cpr::Url{"http://127.0.0.1:8000/usine/" + to_string(id) + "/"});

    json j = json::parse(r.text);
    machine = j["machine"];
    p_machine = make_unique<Machine>(machine);
  }

  void afficherU() const {
    cout << "ID machine: " << machine << endl;

    // p_ville->afficher(); // Affiche les informations de la ville
  }
};

class QuantiteRessource {
 private:
  unique_ptr<Ressource> p_ressource;
  int quantite;
  int ressource;

 public:
  QuantiteRessource(int quantite_, int ressource_)
      : quantite(quantite_), ressource(ressource_) {
    p_ressource = make_unique<Ressource>(ressource);
  }

  QuantiteRessource(const json& data)
      : quantite(data["quantite"]), ressource(data["ressource"]) {
    p_ressource = make_unique<Ressource>(ressource);
  }

  QuantiteRessource(int id) {
    cpr::Response r = cpr::Get(cpr::Url{
        "http://127.0.0.1:8000/quantiteressource/" + to_string(id) + "/"});

    json j = json::parse(r.text);
    quantite = j["quantite"];
    ressource = j["ressource"];
    p_ressource = make_unique<Ressource>(ressource);
  }

  void afficherR() const {
    cout << "Quantite: " << quantite << endl;
    cout << "ID de la ressource: " << ressource << endl;

    // p_ville->afficher(); // Affiche les informations de la ville
  }
};

class Stock {
 private:
  unique_ptr<Usine> p_usine;
  int usine;
  unique_ptr<Objet> p_objet;
  int objet;
  int nombre;

 public:
  Stock(int usine_, int objet_, int nombre_)
      : usine(nom_local_), objet(ville_), nombre(surface_local_) {
    p_objet = make_unique<Objet>(objet);
    p_usine = make_unique<Usine>(usine);
  }

  Stock(const json& data)
      : usine(data["usine"]), objet(data["objet"]), nombre(data["nombre"]) {
    p_objet = make_unique<Objet>(objet);
    p_usine = make_unique<Usine>(usine);
  }

  Stock(int id) {
    cpr::Response r = cpr::Get(
        cpr::Url{"http://127.0.0.1:8000/stock/" + to_string(id) + "/"});

    json j = json::parse(r.text);
    objet = j["objet"];
    nombre = j["nombre"];
    usine = j["usine"];
    p_objet = make_unique<Objet>(objet);
    p_usine = make_unique<Usine>(usine);
  }

  void affichers() const {
    cout << "ID d'objet: " << objet << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "ID de la usine: " << usine << endl;

    // p_ville->afficher(); // Affiche les informations de la ville
  }
};

class Etape {
 private:
  string nom_etape;
  unique_ptr<QuantiteRessource> p_quantite_ressource;
  int quantite_ressource int duree;
  unique_ptr<Machine> p_machine;
  int machine;
  unique_ptr<Etape> p_etape_suivante;
 int etape_suivante

     public : Etape(string nom_etape_, int quantite_ressource_, int duree_,
                    int machine_, int etape_suivante_)
     : nom_etape(nom_etape_),
       quantite_ressource(quantite_ressource_),
       duree(duree_),
       machine(machine_),
       etape_suivante(etape_suivante_) {
    p_quantite_ressource = make_unique<QuantiteRessource>(quantite_ressource);
    p_machine = make_unique<Machine>(machine);
    p_etape_suivante = make_unique<Etape>(etape_suivante);
  }

  Etape(const json& data)
      : nom_etape(data["nom_etape"]),
        quantite_ressource(data["quantite_ressource"]),
        machine(data["machine"]),
        etape_suivante(data["etape_suivante"]),
        duree(data["duree"]) {
    p_quantite_ressource = make_unique<QuantiteRessource>(quantite_ressource);
    p_machine = make_unique<Machine>(machine);
    p_etape_suivante = make_unique<Etape>(etape_suivante);
  }

  Etape(int id) {
    cpr::Response r = cpr::Get(
        cpr::Url{"http://127.0.0.1:8000/local/" + to_string(id) + "/"});

    json j = json::parse(r.text);
    nom_etape = j["nom_etape"];
    quantite_ressource = j["quantite_ressource"];
    machine = j["machine"];
    etape_suivante = j["etape_suivante"];
    duree = j["duree"];
    p_quantite_ressource = make_unique<QuantiteRessource>(quantite_ressource);
    p_machine = make_unique<Machine>(machine);
    p_etape_suivante = make_unique<Etape>(etape_suivante);
  }

  void afficherE() const {
    cout << "Nom de l etape: " << nom_etape << endl;
    cout << "ID quantite ressource: " << quantite_ressource << endl;
    cout << "ID machine : " << machine << endl;
    cout << "Duree: " << duree << endl;
    cout << "ID etape suivante " << etape_suivante << endl;

    // p_ville->afficher(); // Affiche les informations de la ville
  }
};

int main() {
  // r.status_code;                  // 200
  // r.header["content-type"];       // application/json; charset=utf-8
  // r.text;				// JSON text string

  const auto v = Ville{1};

  v.afficher();

  const auto l = Local{4};
  l.afficher1();

  const auto m = Machine{1};
  m.afficherM();

  const auto o = Objet{1};
  m.afficherM();

  const auto etape1 = Etape{1};
  m.afficherE();

  // cout<<r.text<<endl<<r.status_code<<endl;

  return 0;
}
