
#include<string>
#include<iostream>
#include<cpr/cpr.h>
#include<nlohmann/json.hpp>

using json = nlohmann::json;

using namespace std;

class Ville {
private :
	string nom_ville;
	int code_postal;
	float prix_m2;

public :
	Ville( string nom_ville , int code_postal ,float prix_m2): nom_ville(nom_ville), code_postal(code_postal), prix_m2(prix_m2) {}
	
        Ville(const json& data): nom_ville(data["nom_ville"].get<string>()),
        code_postal(data["code_postal"].get<int>()),
        prix_m2(data["prix_m2"].get<float>()) {}
        
	Ville(int id) 
	{
		cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/villes/" + to_string(id) + "/"});

		json j = json::parse(r.text);
		nom_ville = j["nom_ville"].get<string>();
		code_postal = j["code_postal"].get<int>();
		prix_m2 = j["prix_m2"].get<float>();
    	}
    	
	void afficher() const 
	{
		cout << "Nom de la ville: " << nom_ville << endl;
		cout << "Code postal: " << code_postal << endl;
		cout << "Prix au m2: " << prix_m2 << " EUR" << endl;
        }
        
};

class Local {
private :
	string nom_local;
	unique_ptr<Ville> p_ville;
	int surface_local;
	int ville; 
	

public :
	Local( string nom_local_, int surface_local_, int ville_ ) : nom_local(nom_local_), ville(ville_), surface_local(surface_local_) {
	    p_ville = make_unique<Ville>(ville);
	}
	
        Local(const json& data): nom_local(data["nom_local"]),
        surface_local(data["surface_local"]),
        ville(data["ville"]) {
        	p_ville = make_unique<Ville>(ville);
        }
        
	Local(int id) 
	{
		cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/local/" + to_string(id) + "/"});

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
		
		//p_ville->afficher(); // Affiche les informations de la ville
	
        }
};



int main()
{
	
	//r.status_code;                  // 200
	//r.header["content-type"];       // application/json; charset=utf-8
	//r.text;				// JSON text string

	const auto v = Ville{1};
	
	v.afficher();
	
	const auto l = Local{4};
	l.afficher1();
	
	//cout<<r.text<<endl<<r.status_code<<endl;
	
	return 0;
}




