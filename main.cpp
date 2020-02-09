#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Adresat {
    int id=0;
    string imie;
    string nazwisko;
    string adres;
    string adresEmail;
    string numerTelefonu;
};

int DodanieOsobyDoKsiazkiAdresowej(std:: vector <Adresat> &adresaci,int iloscPrzyjaciol) {
    int id;
    string imie;
    string nazwisko;
    string adres;
    string adresEmail;
    string numerTelefonu;
    int rozmiar=adresaci.size();
    if(adresaci.size()==0) {
        id=iloscPrzyjaciol+1;
    } else
        id=adresaci[rozmiar-1].id+1;
    cout<< "Podaj Imie: ";
    cin>>imie;
    cout<< "Podaj nazwisko: ";
    cin>>nazwisko;
    cout<< "Podaj adres: ";
    cin.sync();
    getline(cin, adres);
    cout<< "Podaj adres email: ";
    cin>>adresEmail;
    cout<< "Podaj numer telefonu: ";
    cin.sync();
    getline(cin,numerTelefonu);

    adresaci.push_back(Adresat());
    adresaci[iloscPrzyjaciol].id=id;
    adresaci[iloscPrzyjaciol].imie=imie;
    adresaci[iloscPrzyjaciol].nazwisko=nazwisko;
    adresaci[iloscPrzyjaciol].adres=adres;
    adresaci[iloscPrzyjaciol].adresEmail=adresEmail;
    adresaci[iloscPrzyjaciol].numerTelefonu=numerTelefonu;

    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("Ksiazka_Adresowa.txt",ios::out | ios::app);
    if(ksiazkaAdresowa.good()) {
        ksiazkaAdresowa<<adresaci[iloscPrzyjaciol].id<<"|";
        ksiazkaAdresowa<<adresaci[iloscPrzyjaciol].imie<<"|";
        ksiazkaAdresowa<<adresaci[iloscPrzyjaciol].nazwisko<<"|";
        ksiazkaAdresowa<<adresaci[iloscPrzyjaciol].adres<<"|";
        ksiazkaAdresowa<<adresaci[iloscPrzyjaciol].adresEmail<<"|";
        ksiazkaAdresowa<<adresaci[iloscPrzyjaciol].numerTelefonu<<"|"<<endl;
        cout<<endl;

        ksiazkaAdresowa.close();
        cout<<"Przyjaciel dodany!"<<endl;
        Sleep(1000);
    } else {
        cout<<"Nie ma pliku: Ksiazka_Adresowa.txt"<<endl;
    }
    iloscPrzyjaciol++;
    Sleep(1000);
    return iloscPrzyjaciol;
}

void WczytajKsiazkeAdresowa(std:: vector <Adresat> &adresaci) {
    int idWprowadzanegoPrzyjaciela=0;
    string identyfikator;
    int id;
    string imie;
    string nazwisko;
    string adres;
    string adresEmail;
    string numerTelefonu;
    int dlugoscLinii=0;
    int iloscZnakow=0;
    int p=0;
    int k=0;
    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("Ksiazka_Adresowa.txt",ios::in);
    string linia;
    int nr_linii=1;
    while(getline(ksiazkaAdresowa,linia)) {
        dlugoscLinii=linia.length();

        switch(nr_linii) {
        case 1: {
            for(int i=0; i<dlugoscLinii; i++) {
                if(linia[i]=='|') {
                    if(iloscZnakow==0) {
                        identyfikator=linia.substr(0,i);
                        id = atoi(identyfikator.c_str());
                        p=i+1;
                    } else if(iloscZnakow==1) {
                        imie=linia.substr(p,i-p);
                        p=i;
                    } else if(iloscZnakow==2) {
                        nazwisko=linia.substr(p+1,i-p-1);
                        p=i;
                    } else if(iloscZnakow==3) {
                        adres=linia.substr(p+1,i-p-1);
                        p=i;
                    } else if(iloscZnakow==4) {
                        adresEmail=linia.substr(p+1,i-p-1);
                        p=i;
                    } else if(iloscZnakow==5) {
                        numerTelefonu=linia.substr(p+1,i-p-1);
                    }
                    iloscZnakow=iloscZnakow+1;
                }
            }
            adresaci.push_back(Adresat());
            adresaci[idWprowadzanegoPrzyjaciela].id=id;
            adresaci[idWprowadzanegoPrzyjaciela].imie=imie;
            adresaci[idWprowadzanegoPrzyjaciela].nazwisko=nazwisko;
            adresaci[idWprowadzanegoPrzyjaciela].adres=adres;
            adresaci[idWprowadzanegoPrzyjaciela].adresEmail=adresEmail;
            adresaci[idWprowadzanegoPrzyjaciela].numerTelefonu=numerTelefonu;
            Sleep(1000);
            break;
        }
        }
        if(nr_linii==1) {
            nr_linii=0;
            iloscZnakow=0;
            idWprowadzanegoPrzyjaciela=idWprowadzanegoPrzyjaciela+1;
        }
        nr_linii++;
    }
    ksiazkaAdresowa.close();
}
void WyswietlanieOsobZKsiazkiAdresowej(std:: vector <Adresat> &adresaci, int iloscPrzyjaciol) {
    for(int i=0; i<iloscPrzyjaciol; i++) {
        cout<<endl;
        cout<< "Nr. " <<adresaci[i].id<<endl;
        cout<< "Imie: " <<adresaci[i].imie<<endl;
        cout<< "Nazwisko: " <<adresaci[i].nazwisko<<endl;
        cout<< "Adres: " << adresaci[i].adres<<endl;
        cout<< "Email: " << adresaci[i].adresEmail<<endl;
        cout<< "Numer telefonu: " << adresaci[i].numerTelefonu<<endl;
    }

    system("pause");
}
void WyszukanieOsobyPoImieniu(std::vector <Adresat> &adresaci,string imie,int iloscPrzyjaciol) {
    int k=0;
    for(int i=0; i<iloscPrzyjaciol; i++) {
        if(adresaci[i].imie ==imie) {
            cout<<endl;
            cout<< "Nr. " <<adresaci[i].id<<endl;
            cout<< "Imie: " <<adresaci[i].imie<<endl;
            cout<< "Nazwisko: " <<adresaci[i].nazwisko<<endl;
            cout<< "Adres: " << adresaci[i].adres<<endl;
            cout<< "Email: " << adresaci[i].adresEmail<<endl;
            cout<< "Numer telefonu: " << adresaci[i].numerTelefonu<<endl;
            k++;
        }
    }
    if(k==0) {
        cout<<"Nie ma przyjaciela o danym imieniu!"<<endl;
    }
    system("pause");
}
void WyszukanieOsobyPoNazwisku(std::vector <Adresat> &adresaci,string nazwisko,int iloscPrzyjaciol) {
    int k=0;
    for(int i=0; i<iloscPrzyjaciol; i++) {
        if(adresaci[i].nazwisko ==nazwisko) {
            cout<<endl;
            cout<< "Nr. " <<adresaci[i].id<<endl;
            cout<< "Imie: " <<adresaci[i].imie<<endl;
            cout<< "Nazwisko: " <<adresaci[i].nazwisko<<endl;
            cout<< "Adres: " << adresaci[i].adres<<endl;
            cout<< "Email: " << adresaci[i].adresEmail<<endl;
            cout<< "Numer telefonu: " << adresaci[i].numerTelefonu<<endl;
            k++;
        }
    }
    if(k==0) {
        cout<<"Nie ma przyjaciela o danym nazwisku!"<<endl;
    }
    system("pause");
}

void zapis(std::vector<Adresat>adresaci, int id) {
    ofstream ksiazkaAdresowa("Ksiazka_Adresowa.txt",ios::out|ios::trunc);
    for (short j = 0; j < adresaci.size(); j++) {
        ksiazkaAdresowa<<adresaci[j].id<<"|";
        ksiazkaAdresowa<<adresaci[j].imie<<"|";
        ksiazkaAdresowa<<adresaci[j].nazwisko<<"|";
        ksiazkaAdresowa<<adresaci[j].adres<<"|";
        ksiazkaAdresowa<<adresaci[j].adresEmail<<"|";
        ksiazkaAdresowa<<adresaci[j].numerTelefonu<<"|"<<endl;
    }
    getchar();
}
void usuwanieOsoby(std::vector<Adresat> &adresaci, int id) {
    int pozycja=0;
    for(int i=0; i<adresaci.size(); i++) {
        if(adresaci[i].id==id) {
            pozycja=i;
            break;
        }
    }
    adresaci.erase(adresaci.begin()+pozycja);
    zapis(adresaci,id);
}
int WyszukanieOstatniegoID(std::vector<Adresat> &adresaci) {
    int identyfikator;
    int rozmiar=adresaci.size();
    identyfikator=adresaci[rozmiar-1].id;
    return identyfikator;
}
void edycjaImienia(std::vector <Adresat> &adresaci,int id, string noweImie) {
    for(int i=0; i<adresaci.size(); i++) {
        if(adresaci[i].id==id) {
            adresaci[i].imie=noweImie;
        }
    }
    Sleep(1000);
    zapis(adresaci,id);
}
void edycjaNazwiska(std::vector <Adresat> &adresaci,int id, string noweNazwisko) {
    for(int i=0; i<adresaci.size(); i++) {
        if(adresaci[i].id==id) {
            adresaci[i].nazwisko=noweNazwisko;
        }
    }
    Sleep(1000);
    zapis(adresaci,id);
}
void edycjaNumeruTelefonu(std::vector <Adresat> &adresaci,int id, string nowyTelefon) {
    for(int i=0; i<adresaci.size(); i++) {
        if(adresaci[i].id==id) {
            adresaci[i].numerTelefonu=nowyTelefon;
        }
    }
    Sleep(1000);
    zapis(adresaci,id);
}
void edycjaEmail(std::vector <Adresat> &adresaci,int id, string nowyEmail) {
    for(int i=0; i<adresaci.size(); i++) {
        if(adresaci[i].id==id) {
            adresaci[i].adresEmail=nowyEmail;
        }
    }
    Sleep(1000);
    zapis(adresaci,id);
}
void edycjaAdresu(std::vector <Adresat> &adresaci,int id, string nowyAdres) {
    for(int i=0; i<adresaci.size(); i++) {
        if(adresaci[i].id==id) {
            adresaci[i].adres=nowyAdres;
        }
    }
    Sleep(1000);
    zapis(adresaci,id);
}
bool czyIstniejeTakieID(std::vector<Adresat> &adresaci,int id) {
    int pozycja=0;
    for(int i=0; i<adresaci.size(); i++) {
        if(adresaci[i].id==id) {
            pozycja=1;
            break;
        }
    }
    if(pozycja==1)
        return 1;
    else
        return 0;
}

int main() {
    std::vector <Adresat> adresaci;
    WczytajKsiazkeAdresowa(adresaci);
    int idWprowadzanegoPrzyjaciela;
    int ID;
    if(adresaci.size()==0) {
        idWprowadzanegoPrzyjaciela=adresaci.size();
    } else {
        ID=WyszukanieOstatniegoID(adresaci);
        idWprowadzanegoPrzyjaciela=ID;
    }

    int iloscPrzyjaciol=0;
    int id;
    char wybor,wybor1;
    string imie,nazwisko,adres,numerTelefonu,email;
    while(1) {
        iloscPrzyjaciol=adresaci.size();
        system("cls");
        cout<< "-------------->MENU<--------------"<<endl;
        cout<< "1. Dodaj adresata."<<endl;
        cout<< "2. Wyszukiwanie po nazwisku."<<endl;
        cout<< "3. Wyszukiwanie po imieniu."<<endl;
        cout<< "4. Wyswietl wszystkich adresatow."<<endl;
        cout<< "5. Usun adresata."<<endl;
        cout<< "6. Edycja adresata."<<endl;
        cout<< "9. Zakoncz."<<endl;
        cout<<"Twoj wybor: ";
        cin>>wybor;

        if(wybor=='1') {
            iloscPrzyjaciol=DodanieOsobyDoKsiazkiAdresowej(adresaci,iloscPrzyjaciol);

        } else if(wybor=='2') {
            if(iloscPrzyjaciol==0) {
                cout<<"Brak przyjaciol do wyswietlenia!"<<endl;
                system("pause");
            } else {
                cout<<"Podaj nazwisko: "<<endl;
                cin>>nazwisko;
                WyszukanieOsobyPoNazwisku(adresaci,nazwisko,iloscPrzyjaciol);
            }
        } else if(wybor=='3') {
            if(iloscPrzyjaciol==0) {
                cout<<"Brak przyjaciol do wyswietlenia!"<<endl;
                system("pause");
            } else {
                cout<<"Podaj imie: "<<endl;
                cin>>imie;
                WyszukanieOsobyPoImieniu(adresaci,imie,iloscPrzyjaciol);
            }

        } else if(wybor=='4') {
            iloscPrzyjaciol=adresaci.size();
            WyswietlanieOsobZKsiazkiAdresowej(adresaci,iloscPrzyjaciol);
        } else if(wybor=='5') {
            cout<<"Podaj numer id osoby ktorej chcesz usunac ";
            cin>>id;

            if(czyIstniejeTakieID(adresaci,id)==false) {
                cout<<"Nie ma osoby o takim ID."<<endl;
                Sleep(2000);
            } else {
                cout<<"Jestes pewny <t/n>: ";
                cin>>wybor1;
                if(wybor1=='t') {
                    usuwanieOsoby(adresaci,id);
                    Sleep(1000);
                } else {
                    ;
                }
            }

        } else if(wybor=='6') {
            cout<<"Podaj numer id osoby do zmiany: ";
            cin>>id;
            czyIstniejeTakieID(adresaci,id);
            if(czyIstniejeTakieID(adresaci,id)==false) {
                cout<<"Nie ma osoby o takim ID."<<endl;
                Sleep(2000);
            } else {
                cout<<"1. Imie."<<endl;
                cout<<"2. Nazwisko."<<endl;
                cout<<"3. Numer telefonu."<<endl;
                cout<<"4. Email."<<endl;
                cout<<"5. Adres."<<endl;
                cout<<"6. Powrot do menu."<<endl;
                cin>>wybor1;
                if(wybor1=='1') {
                    cout<<"Podaj nowe imie: ";
                    cin>>imie;
                    edycjaImienia(adresaci,id,imie);
                } else if(wybor1=='2') {
                    cout<<"Podaj nowe nazwisko: ";
                    cin>>nazwisko;
                    edycjaNazwiska(adresaci,id,nazwisko);
                } else if(wybor1=='3') {
                    cout<<"Podaj nowy numer telefonu: "<<endl;
                    cin.sync();
                    getline(cin, numerTelefonu);
                    edycjaNumeruTelefonu(adresaci,id,numerTelefonu);
                } else if(wybor1=='4') {
                    cout<<"Podaj nowy adres email: "<<endl;
                    cin>>email;
                    edycjaEmail(adresaci,id,email);
                } else if(wybor1=='5') {
                    cout<<"Podaj nowy adres: "<<endl;
                    cin.sync();
                    getline(cin, adres);
                    edycjaAdresu(adresaci,id,adres);
                } else if(wybor1=='6') {
                    ;
                }

            }
        } else if(wybor=='9') {
            exit(0);
        }
    }
    return 0;
}
