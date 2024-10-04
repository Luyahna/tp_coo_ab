#include<string>
#include<iostream>
#include<cpr/cpr.h>
#include<nlohmann/json.hpp>

using namespace std;

class Ville {
private :
	string nom_ville;
	int code_postal;
	float prix_m2;

public :
	Ville( string nom_ville , int code_postal ,float prix_m2): nom_ville(nom_ville),           	  code_postal(code_postal), prix_m2(prix_m2) {}
	
	
	void afficher() const {
        cout << "Nom de la ville: " << nom_ville << endl;
        cout << "Code postal: " << code_postal << endl;
        cout << "Prix au m²: " << prix_m2 << " EUR" << endl;
        }
};



int main()
{
	Ville v("toulouse",31400,5000);
	//v.afficher();
	
	cpr::Response r = cpr::Get(cpr::Url{"https://api.github.com/repos/whoshuu/cpr/contributors"});
	r.status_code;                  // 200
	r.header["content-type"];       // application/json; charset=utf-8
	r.text;                         // JSON text string

	cout<<r.text<<endl<<r.status_code<<endl;
	return 0;
}




