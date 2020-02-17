#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Adresat {
    int id=0;
    int idUzytkownika=0;
    string imie;
    string nazwisko;
    string adres;
    string adresEmail;
    string numerTelefonu;
};

struct Uzytkownik {
    int idUzytkownika;
    string login;
    string haslo;
};

int DodanieOsobyDoKsiazkiAdresowej(vector <Adresat> &adresaci,int iloscPrzyjaciol,int idUzytkownika,int NajwiekszeID) {
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
        id=NajwiekszeID+1;
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
    adresaci[iloscPrzyjaciol].id=NajwiekszeID;
    adresaci[iloscPrzyjaciol].idUzytkownika=idUzytkownika;
    adresaci[iloscPrzyjaciol].imie=imie;
    adresaci[iloscPrzyjaciol].nazwisko=nazwisko;
    adresaci[iloscPrzyjaciol].adres=adres;
    adresaci[iloscPrzyjaciol].adresEmail=adresEmail;
    adresaci[iloscPrzyjaciol].numerTelefonu=numerTelefonu;

    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("Ksiazka_Adresowa.txt",ios::out | ios::app);
    if(ksiazkaAdresowa.good()) {
        ksiazkaAdresowa<<adresaci[iloscPrzyjaciol].id<<"|";
        ksiazkaAdresowa<<adresaci[iloscPrzyjaciol].idUzytkownika<<"|";
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

void WczytajKsiazkeAdresowa(vector <Adresat> &adresaci,int idUzytkownika) {
    int idWprowadzanegoPrzyjaciela=0;
    string identyfikator,identyfikatorUzytkownika;
    int id,ident;
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
                        identyfikatorUzytkownika=linia.substr(p,p-i);
                        ident = atoi(identyfikatorUzytkownika.c_str());
                        p=i;
                    } else if(iloscZnakow==2) {
                        imie=linia.substr(p+1,i-p-1);
                        p=i;
                    } else if(iloscZnakow==3) {
                        nazwisko=linia.substr(p+1,i-p-1);
                        p=i;
                    } else if(iloscZnakow==4) {
                        adres=linia.substr(p+1,i-p-1);
                        p=i;
                    } else if(iloscZnakow==5) {
                        adresEmail=linia.substr(p+1,i-p-1);
                        p=i;
                    } else if(iloscZnakow==6) {
                        numerTelefonu=linia.substr(p+1,i-p-1);
                    }
                    iloscZnakow=iloscZnakow+1;
                }
            }
            if(ident==idUzytkownika) {
                adresaci.push_back(Adresat());
                adresaci[idWprowadzanegoPrzyjaciela].id=id;
                adresaci[idWprowadzanegoPrzyjaciela].idUzytkownika=ident;
                adresaci[idWprowadzanegoPrzyjaciela].imie=imie;
                adresaci[idWprowadzanegoPrzyjaciela].nazwisko=nazwisko;
                adresaci[idWprowadzanegoPrzyjaciela].adres=adres;
                adresaci[idWprowadzanegoPrzyjaciela].adresEmail=adresEmail;
                adresaci[idWprowadzanegoPrzyjaciela].numerTelefonu=numerTelefonu;
                Sleep(1000);
                break;
            }
        }
        }
        if(nr_linii==1) {
            if(ident==idUzytkownika) {
                nr_linii=0;
                iloscZnakow=0;
                idWprowadzanegoPrzyjaciela=idWprowadzanegoPrzyjaciela+1;
            } else {
                nr_linii=0;
                iloscZnakow=0;
            }
        }
        nr_linii++;
    }
    ksiazkaAdresowa.close();
}
void WyswietlanieOsobZKsiazkiAdresowej(vector <Adresat> &adresaci, int iloscPrzyjaciol, int idUzytkownika) {
    for(int i=0; i<iloscPrzyjaciol; i++) {
        if(adresaci[i].idUzytkownika==idUzytkownika) {
            cout<<endl;
            cout<< "Nr. " <<adresaci[i].id<<endl;
            cout<< "Imie: " <<adresaci[i].imie<<endl;
            cout<< "Nazwisko: " <<adresaci[i].nazwisko<<endl;
            cout<< "Adres: " << adresaci[i].adres<<endl;
            cout<< "Email: " << adresaci[i].adresEmail<<endl;
            cout<< "Numer telefonu: " << adresaci[i].numerTelefonu<<endl;
        }
    }
    system("pause");
}
void WyszukanieOsobyPoImieniu(vector <Adresat> &adresaci,string imie,int iloscPrzyjaciol,int idUzytkownika) {
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
void WyszukanieOsobyPoNazwisku(vector <Adresat> &adresaci,string nazwisko,int iloscPrzyjaciol,int idUzytkownika) {
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

int WyszukanieOstatniegoID(vector<Adresat> &adresaci) {
    int identyfikator;
    int rozmiar=adresaci.size();
    identyfikator=adresaci[rozmiar-1].id;
    return identyfikator;
}

bool czyIstniejeTakieID(vector <Adresat> &adresaci,int id) {
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

int NajwiekszeIDAdresata() {
    string identyfikator;
    int id,id1=0;
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
            for(int i =0; i<dlugoscLinii; i++) {
                if(linia[i]=='|') {
                    if(iloscZnakow==0) {
                        identyfikator=linia.substr(0,i);
                        id = atoi(identyfikator.c_str());
                    }
                }
            }
        }
        if(id>=id1) {
            id1=id;
        }
        Sleep(1000);
        break;
        }

        if(nr_linii==1) {
            nr_linii=0;
            iloscZnakow=0;
        }
        nr_linii++;
    }
    ksiazkaAdresowa.close();
    return id1+1;
}

void WczytajUzytkownikow(vector <Uzytkownik> &uzytkownicy) {
    int idWprowadzanegoUzytkownika=0;
    string identyfikator;
    int id;
    string login;
    string haslo;
    int dlugoscLinii=0;
    int iloscZnakow=0;
    int p=0;
    int k=0;
    fstream KsiazkaUzytkownikow;
    KsiazkaUzytkownikow.open("Uzytkownicy.txt",ios::in);
    string linia;
    int nr_linii=1;
    while(getline(KsiazkaUzytkownikow,linia)) {
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
                        login=linia.substr(p,i-p);
                        p=i;
                    } else if(iloscZnakow==2) {
                        haslo=linia.substr(p+1,i-p-1);
                        p=i;
                    }
                    iloscZnakow=iloscZnakow+1;
                }
            }
            uzytkownicy.push_back(Uzytkownik());
            uzytkownicy[idWprowadzanegoUzytkownika].idUzytkownika=id;
            uzytkownicy[idWprowadzanegoUzytkownika].login=login;
            uzytkownicy[idWprowadzanegoUzytkownika].haslo=haslo;
            Sleep(1000);
            break;
        }
        }
        if(nr_linii==1) {
            nr_linii=0;
            iloscZnakow=0;
            idWprowadzanegoUzytkownika=idWprowadzanegoUzytkownika+1;
        }
        nr_linii++;
    }
    KsiazkaUzytkownikow.close();
}

int DodanieUzytkownika( vector <Uzytkownik> &uzytkownicy,int iloscUzytkownikow) {
    int idUzytkownika;
    string login;
    string haslo;
    int rozmiar=uzytkownicy.size();
    if(uzytkownicy.size()==0) {
        idUzytkownika=iloscUzytkownikow+1;
    } else
        idUzytkownika=uzytkownicy[rozmiar-1].idUzytkownika+1;

    cout<< "Podaj login: ";
    cin.sync();
    getline(cin, login);
    cout<< "Podaj haslo: ";
    cin.sync();
    getline(cin,haslo);

    uzytkownicy.push_back(Uzytkownik());
    uzytkownicy[iloscUzytkownikow].idUzytkownika=idUzytkownika;
    uzytkownicy[iloscUzytkownikow].login=login;
    uzytkownicy[iloscUzytkownikow].haslo=haslo;

    fstream KsiazkaUzytkownikow;
    KsiazkaUzytkownikow.open("Uzytkownicy.txt",ios::out | ios::app);
    if(KsiazkaUzytkownikow.good()) {
        KsiazkaUzytkownikow<<uzytkownicy[iloscUzytkownikow].idUzytkownika<<"|";
        KsiazkaUzytkownikow<<uzytkownicy[iloscUzytkownikow].login<<"|";
        KsiazkaUzytkownikow<<uzytkownicy[iloscUzytkownikow].haslo<<"|"<<endl;
        cout<<endl;
        KsiazkaUzytkownikow.close();
        cout<<"Uzytkownik dodany!"<<endl;
        Sleep(1000);
    } else {
        cout<<"Nie ma pliku: Ksiazka_Adresowa.txt"<<endl;
    }
    iloscUzytkownikow++;
    Sleep(1000);
    return iloscUzytkownikow;
}

int SprawdzLogowanie( vector <Uzytkownik> &uzytkownicy, string login, string haslo) {
    int dlugosc=uzytkownicy.size();
    int p=0,k=1;
    for(int i=0; i<dlugosc; i++) {
        if(uzytkownicy[i].login==login) {
            p=i;
            break;
        }
    }
    for(int i=0; i<dlugosc; i++) {
        if(uzytkownicy[i].haslo==haslo) {
            k=i;
            break;
        }
    }
    if(p==k) {
        cout<<"Logowanie udane!"<<endl;
            Sleep(1000);
        return uzytkownicy[p].idUzytkownika;
    } else {
        cout<<"Logowanie nie udane!"<<endl;
            Sleep(1000);
        return 0;
    }

}

void zapis(vector<Adresat> &adresaci, int idAdresata,int idUzytkownika) {

    int idWprowadzanegoPrzyjaciela=0;
    string identyfikator,identyfikatorUzytkownika;
    int id,ident;
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
                        identyfikatorUzytkownika=linia.substr(p,p-i);
                        ident = atoi(identyfikatorUzytkownika.c_str());
                        p=i;
                    } else if(iloscZnakow==2) {
                        imie=linia.substr(p+1,i-p-1);
                        p=i;
                    } else if(iloscZnakow==3) {
                        nazwisko=linia.substr(p+1,i-p-1);
                        p=i;
                    } else if(iloscZnakow==4) {
                        adres=linia.substr(p+1,i-p-1);
                        p=i;
                    } else if(iloscZnakow==5) {
                        adresEmail=linia.substr(p+1,i-p-1);
                        p=i;
                    } else if(iloscZnakow==6) {
                        numerTelefonu=linia.substr(p+1,i-p-1);
                    }
                    iloscZnakow=iloscZnakow+1;
                }
            }
            fstream ksiazka;
            ksiazka.open("Adresaci.txt",ios::out | ios::app);
            if(ksiazka.good()) {
                if(id!=idAdresata) {
                    ksiazka<<id<<"|";
                    ksiazka<<ident<<"|";
                    ksiazka<<imie<<"|";
                    ksiazka<<nazwisko<<"|";
                    ksiazka<<adres<<"|";
                    ksiazka<<adresEmail<<"|";
                    ksiazka<<numerTelefonu<<"|"<<endl;
                    ksiazka.close();
                }
                break;
            } else
                break;
        }
        }
        if(nr_linii==1) {
            if(ident==idUzytkownika) {
                nr_linii=0;
                iloscZnakow=0;
                idWprowadzanegoPrzyjaciela=idWprowadzanegoPrzyjaciela+1;
            } else {
                nr_linii=0;
                iloscZnakow=0;
            }
        }
        nr_linii++;
    }
    ksiazkaAdresowa.close();
}

void ZamianaPlikow() {
    ofstream ksiazkaAdresowa("Ksiazka_Adresowa.txt",ios::out|ios::trunc);
    {
        fstream ksiazka;
        ksiazka.open("Adresaci.txt",ios::in);
        {
            string linia;
            int nr_linii=1;
            while(getline(ksiazka,linia)) {
                int dlugoscLinii=linia.length();
                switch(nr_linii) {
                case 1: {
                    if(ksiazkaAdresowa.good()) {
                        ksiazkaAdresowa<<linia<<endl;
                    }
                    break;
                }
                }
                if(nr_linii==1) {
                    nr_linii=0;
                }
                nr_linii++;
            }
        }
        ksiazka.close();
    }
}

void usuwanieOsobyZeStruktury(vector<Adresat> &adresaci, int id) {
    int pozycja=0;
    for(int i=0; i<adresaci.size(); i++) {
        if(adresaci[i].id==id) {
            pozycja=i;
            break;
        }
    }
    adresaci.erase(adresaci.begin()+pozycja);
}

void edycjaImienia(vector <Adresat> &adresaci,int id, int idUzytkownika, string noweImie) {
    for(int i=0; i<adresaci.size(); i++) {
        if(adresaci[i].id==id&&adresaci[i].idUzytkownika==idUzytkownika) {
            adresaci[i].imie=noweImie;
        }
    }
}
void edycjaNazwiska(vector <Adresat> &adresaci,int id, int idUzytkownika, string noweNazwisko) {
    for(int i=0; i<adresaci.size(); i++) {
        if(adresaci[i].id==id&&adresaci[i].idUzytkownika==idUzytkownika) {
            adresaci[i].nazwisko=noweNazwisko;
        }
    }
}

void edycjaAdresu(vector <Adresat> &adresaci,int id, int idUzytkownika, string nowyAdres) {
    for(int i=0; i<adresaci.size(); i++) {
        if(adresaci[i].id==id&&adresaci[i].idUzytkownika==idUzytkownika) {
            adresaci[i].adres=nowyAdres;
        }
    }
}

void edycjaAdresuEmail(vector <Adresat> &adresaci,int id, int idUzytkownika, string nowyAdresEmail) {
    for(int i=0; i<adresaci.size(); i++) {
        if(adresaci[i].id==id&&adresaci[i].idUzytkownika==idUzytkownika) {
            adresaci[i].adresEmail=nowyAdresEmail;
        }
    }
}

void edycjaTelefonu(vector <Adresat> &adresaci,int id, int idUzytkownika, string nowyTelefon) {
    for(int i=0; i<adresaci.size(); i++) {
        if(adresaci[i].id==id&&adresaci[i].idUzytkownika==idUzytkownika) {
            adresaci[i].numerTelefonu=nowyTelefon;
        }
    }
}

int sprawdzPozycje(vector <Adresat> &adresaci, int idAdresata, int idUzytkownika) {
    int pozycja =0;
    for(int i=0; i<adresaci.size(); i++) {
        if(idAdresata!=adresaci[i].id) {
            pozycja=pozycja+1;
        }
        else break;
    }
    return pozycja;
}

void zapisEdycji(vector<Adresat> &adresaci, int idAdresata,int idUzytkownika) {

    int idWprowadzanegoPrzyjaciela=0;
    string identyfikator,identyfikatorUzytkownika;
    int id,ident;
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
                        identyfikatorUzytkownika=linia.substr(p,p-i);
                        ident = atoi(identyfikatorUzytkownika.c_str());
                        p=i;
                    } else if(iloscZnakow==2) {
                        imie=linia.substr(p+1,i-p-1);
                        p=i;
                    } else if(iloscZnakow==3) {
                        nazwisko=linia.substr(p+1,i-p-1);
                        p=i;
                    } else if(iloscZnakow==4) {
                        adres=linia.substr(p+1,i-p-1);
                        p=i;
                    } else if(iloscZnakow==5) {
                        adresEmail=linia.substr(p+1,i-p-1);
                        p=i;
                    } else if(iloscZnakow==6) {
                        numerTelefonu=linia.substr(p+1,i-p-1);
                    }
                    iloscZnakow=iloscZnakow+1;
                }
            }
            fstream ksiazka;
            ksiazka.open("Adresaci.txt",ios::out | ios::app);
            if(ksiazka.good()) {
                if(id!=idAdresata) {
                    ksiazka<<id<<"|";
                    ksiazka<<ident<<"|";
                    ksiazka<<imie<<"|";
                    ksiazka<<nazwisko<<"|";
                    ksiazka<<adres<<"|";
                    ksiazka<<adresEmail<<"|";
                    ksiazka<<numerTelefonu<<"|"<<endl;
                }
                if(id==idAdresata) {
                        int i=sprawdzPozycje(adresaci,idAdresata,idUzytkownika);
                        ksiazka<<adresaci[i].id<<"|";
                        ksiazka<<adresaci[i].idUzytkownika<<"|";
                        ksiazka<<adresaci[i].imie<<"|";
                        ksiazka<<adresaci[i].nazwisko<<"|";
                        ksiazka<<adresaci[i].adres<<"|";
                        ksiazka<<adresaci[i].adresEmail<<"|";
                        ksiazka<<adresaci[i].numerTelefonu<<"|"<<endl;
                }
                ksiazka.close();
                Sleep(1000);
                break;
            } else
                break;
        }
        }
        if(nr_linii==1) {
            if(ident==idUzytkownika) {
                nr_linii=0;
                iloscZnakow=0;
                idWprowadzanegoPrzyjaciela=idWprowadzanegoPrzyjaciela+1;
            } else {
                nr_linii=0;
                iloscZnakow=0;
            }
        }
        nr_linii++;
    }
    ksiazkaAdresowa.close();
}

void EdycjaIZamianaPlikow(vector <Adresat> &adresaci,int id, int idUzytkownika) {
    zapisEdycji(adresaci,id,idUzytkownika);
    ZamianaPlikow();
    //fstream f_conf( "Adresaci.txt", ios::in ); //resetowanie pliku o danej nazwie
    //reset(f_conf);
    remove("Adresaci.txt");
    cout<<"Zmiany zapisane!"<<endl;
}

void zapisHasla(vector<Uzytkownik> &uzytkownicy) {
    ofstream KsiazkaUzytkownikow("Uzytkownicy.txt",ios::out|ios::trunc);
    for (short j = 0; j < uzytkownicy.size(); j++) {
        KsiazkaUzytkownikow<<uzytkownicy[j].idUzytkownika<<"|";
        KsiazkaUzytkownikow<<uzytkownicy[j].login<<"|";
        KsiazkaUzytkownikow<<uzytkownicy[j].haslo<<"|"<<endl;
    }
}

void edycjaHasla(vector <Uzytkownik> &uzytkownicy,int idUzytkownika,string noweHaslo) {
    for(int i=0; i<uzytkownicy.size(); i++) {
        if(uzytkownicy[i].idUzytkownika==idUzytkownika) {
            uzytkownicy[i].haslo=noweHaslo;
        }
    }
    zapisHasla(uzytkownicy);
}

int main() {

    vector <Uzytkownik> uzytkownicy;
    WczytajUzytkownikow(uzytkownicy);
    int iloscPrzyjaciol=0;
    int iloscUzytkownikow=0;
    int id;
    char wybor,wybor1;
    string imie,nazwisko,adres,numerTelefonu,email,login,haslo;
    while(1) {
        iloscUzytkownikow=uzytkownicy.size();
        system("cls");
        cout<< "1. Rejestracja "<<endl;
        cout<< "2. Logowanie "<<endl;
        cout<< "3. Zakoncz "<<endl;
        cin>>wybor;
        if(wybor=='1') {
            iloscUzytkownikow=DodanieUzytkownika(uzytkownicy,iloscUzytkownikow);
        } else if(wybor=='2') {
            cout<<"Podaj login: "<<endl;
            cin>>login;
            cout<<"Podaj haslo: "<<endl;
            cin>>haslo;
            int idUzytkownika=SprawdzLogowanie(uzytkownicy,login,haslo);
            if(idUzytkownika!=0) {
                vector <Adresat> adresaci;
                WczytajKsiazkeAdresowa(adresaci,idUzytkownika);
                int idWprowadzanegoPrzyjaciela=0;
                while(idUzytkownika!=0) {
                    system("cls");
                    cout<<"1. Dodaj adresata "<<endl;
                    cout<<"2. Wyszukaj po imieniu "<<endl;
                    cout<<"3. Wyszukaj po nazwisku "<<endl;
                    cout<<"4. Wyswietl wszystkich adresatow "<<endl;
                    cout<<"5. Usun adresata "<<endl;
                    cout<<"6. Edycja danych adresata "<<endl;
                    cout<<"7. Zmiana hasla "<<endl;
                    cout<<"9. Wyloguj sie "<<endl;
                    cin>>wybor;
                    if(wybor=='1') {
                        int naj=NajwiekszeIDAdresata();
                        iloscPrzyjaciol=adresaci.size();
                        iloscPrzyjaciol=DodanieOsobyDoKsiazkiAdresowej(adresaci,iloscPrzyjaciol,idUzytkownika, naj);
                    } else if(wybor=='2') {
                        iloscPrzyjaciol=adresaci.size();
                        cout<<"Podaj imie: "<<endl;
                        cin>>imie;
                        WyszukanieOsobyPoImieniu(adresaci,imie,iloscPrzyjaciol,idUzytkownika);
                    } else if(wybor=='3') {
                        iloscPrzyjaciol=adresaci.size();
                        cout<<"Podaj nazwisko: "<<endl;
                        cin>>nazwisko;
                        WyszukanieOsobyPoNazwisku(adresaci,nazwisko,iloscPrzyjaciol,idUzytkownika);
                    } else if (wybor=='4') {
                        iloscPrzyjaciol=adresaci.size();
                        WyswietlanieOsobZKsiazkiAdresowej(adresaci,iloscPrzyjaciol,idUzytkownika);
                    } else if (wybor=='5') {
                        iloscPrzyjaciol=adresaci.size();
                        cout<<"Podaj id osoby do usuniecia: "<<endl;
                        cin>>id;
                        cout<<"Czy jestes pewny? <t/n>"<<endl;
                        cin>>wybor;
                        if(wybor=='t'){
                            if(czyIstniejeTakieID(adresaci,id)==1) {
                            zapis(adresaci,id,idUzytkownika);
                            ZamianaPlikow();
                            remove("Adresaci.txt");
                            usuwanieOsobyZeStruktury(adresaci,id);
                            cout<<"Uzytkownik usuniety! "<<endl;
                            Sleep(1000);
                        } else
                            cout<<"nie ma takiego id!"<<endl;
                            Sleep(1000);
                        }
                        else if(wybor=='n')
                        {
                            ;
                        }
                    } else if (wybor=='6') {
                        cout<<"Podaj id adresata do zmiany"<<endl;
                        cin>>id;
                        if(czyIstniejeTakieID(adresaci,id)==1) {
                            cout<<"1. Imie "<<endl;
                            cout<<"2. Nazwisko "<<endl;
                            cout<<"3. Adres "<<endl;
                            cout<<"4. Adres email "<<endl;
                            cout<<"5. Numer telefonu "<<endl;
                            cin>> wybor;
                            if(wybor=='1') {
                                cout<<"Podaj nowe imie: "<<endl;
                                cin>>imie;
                                edycjaImienia(adresaci,id,idUzytkownika,imie);
                                EdycjaIZamianaPlikow(adresaci,id,idUzytkownika);
                            } else if(wybor=='2') {
                                cout<<"Podaj nowe nazwisko: "<<endl;
                                cin>>nazwisko;
                                edycjaNazwiska(adresaci,id,idUzytkownika,nazwisko);
                                EdycjaIZamianaPlikow(adresaci,id,idUzytkownika);
                            } else if(wybor=='3') {
                                cout<< "Podaj nowy adres: ";
                                cin.sync();
                                getline(cin, adres);
                                edycjaAdresu(adresaci,id,idUzytkownika,adres);
                                EdycjaIZamianaPlikow(adresaci,id,idUzytkownika);
                            } else if(wybor=='4') {
                                cout<<"Podaj nowy adres email: ";
                                cin>>email;
                                edycjaAdresuEmail(adresaci,id,idUzytkownika,email);
                                EdycjaIZamianaPlikow(adresaci,id,idUzytkownika);
                            } else if(wybor=='5') {
                                cout<< "Podaj nowy nr telefonu: ";
                                cin.sync();
                                getline(cin, numerTelefonu);
                                edycjaTelefonu(adresaci,id,idUzytkownika,numerTelefonu);
                                EdycjaIZamianaPlikow(adresaci,id,idUzytkownika);
                            }
                        } else
                            cout<<"nie ma takiego id!"<<endl;
                            Sleep(1000);
                    } else if(wybor=='7') {
                        cout<<"Podaj nowe haslo: "<<endl;
                        cin>>haslo;
                        edycjaHasla(uzytkownicy,idUzytkownika,haslo);
                        zapisHasla(uzytkownicy);
                    } else if(wybor=='9') {
                        idUzytkownika=0;
                    }
                }
            }
        } else if(wybor=='3') {
            exit(0);
        }
    }
    return 0;
}
