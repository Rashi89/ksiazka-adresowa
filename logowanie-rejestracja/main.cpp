#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Uzytkownik {
    int id=0;
    string login;
    string haslo;
};

int SprawdzanieLogowania(std::vector <Uzytkownik> &uzytkownicy,string login, string haslo)
{
    int k=0;
    int l=0;
    for(int i=0;i<uzytkownicy.size();i++)
    {
        if(uzytkownicy[i].login==login)
        {
            k=i;
        }
        if(uzytkownicy[i].haslo==haslo)
        {
            l=i;
        }
    }
    if(k==l)
    {
        cout<<"Logowanie udane!"<<endl;
        return uzytkownicy[k].id;
    }
    else if(k!=l)
    {
        cout<<"Nieudane logowanie!"<<endl;
        return 1;
    }
}

int DodanieUzytkownika(std:: vector <Uzytkownik> &uzytkownicy,int idUzytkownika ) {
    int id=idUzytkownika;
    int iloscPrzyjaciol=idUzytkownika;
    int rozmiar=uzytkownicy.size();
    if(uzytkownicy.size()==0) {
        id=iloscPrzyjaciol+1;
    } else
        id=uzytkownicy[rozmiar-1].id+1;
    string login,haslo;
    cout<< "Login: ";
    cin>>login;
    cout<< "Haslo: ";
    cin>>haslo;
    uzytkownicy.push_back(Uzytkownik());
    uzytkownicy[iloscPrzyjaciol].id=id;
    uzytkownicy[iloscPrzyjaciol].login=login;
    uzytkownicy[iloscPrzyjaciol].haslo=haslo;

    fstream ksiazkaUzytkownikow;
    ksiazkaUzytkownikow.open("KsiazkaUzytkownikow.txt",ios::out | ios::app);
    if(ksiazkaUzytkownikow.good()) {
        ksiazkaUzytkownikow<<uzytkownicy[iloscPrzyjaciol].id<<"|";
        ksiazkaUzytkownikow<<uzytkownicy[iloscPrzyjaciol].login<<"|";
        ksiazkaUzytkownikow<<uzytkownicy[iloscPrzyjaciol].haslo<<"|"<<endl;
        cout<<endl;

        ksiazkaUzytkownikow.close();
        cout<<"Przyjaciel dodany!"<<endl;
        Sleep(1000);
    } else {
        cout<<"Nie ma pliku: KsiazkaUzytkownikow.txt"<<endl;
    }
    iloscPrzyjaciol++;
    Sleep(1000);
    return iloscPrzyjaciol;
}

void WczytajUzytkownikow(std:: vector <Uzytkownik> &uzytkownicy) {
    int idUzytkownika=0;
    string identyfikator;
    int id;
    string login;
    string haslo;
    int dlugoscLinii=0;
    int iloscZnakow=0;
    int p=0;
    int k=0;
    fstream ksiazkaUzytkownikow;
    ksiazkaUzytkownikow.open("KsiazkaUzytkownikow.txt",ios::in);
    string linia;
    int nr_linii=1;
    while(getline(ksiazkaUzytkownikow,linia)) {
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
            uzytkownicy[idUzytkownika].id=id;
            uzytkownicy[idUzytkownika].login=login;
            uzytkownicy[idUzytkownika].haslo=haslo;

            Sleep(1000);
            break;
        }
        }
        if(nr_linii==1) {
            nr_linii=0;
            iloscZnakow=0;
            idUzytkownika=idUzytkownika+1;
        }
        nr_linii++;
    }
    ksiazkaUzytkownikow.close();
}

int WyszukanieOstatniegoID(std::vector<Uzytkownik> &uzytkownicy) {
    int identyfikator;
    int rozmiar=uzytkownicy.size();
    identyfikator=uzytkownicy[rozmiar-1].id;
    return identyfikator;
}

int main()
{
    std::vector <Uzytkownik> uzytkownicy;
    char wybor;
    string login,haslo;
    int idUzytkownika=1;
    WczytajUzytkownikow(uzytkownicy);
    int idWprowadzanegoUzytkownika;
    int ID;
    if(uzytkownicy.size()==0) {
        idWprowadzanegoUzytkownika=uzytkownicy.size();
    } else {
        ID=WyszukanieOstatniegoID(uzytkownicy);
        idWprowadzanegoUzytkownika=ID;
    }
    while(1)
    {
        system("cls");
        cout<< "-------------->MENU<--------------"<<endl;
        cout<< "1. Logowanie. "<<endl;
        cout<< "2. Rejestracja. "<<endl;
        cout<< "3. Zamknij program. "<<endl;
        cin>>wybor;
        if(wybor=='2')
        {
            idWprowadzanegoUzytkownika=DodanieUzytkownika(uzytkownicy,idWprowadzanegoUzytkownika);
            //cout<<idWprowadzanegoUzytkownika<<endl;
            Sleep(1000);
        }
        else if(wybor=='1')
        {
            cout <<"Podaj login: ";
            cin>>login;
            cout<<"Podaj haslo: ";
            cin >>haslo;
            idUzytkownika=SprawdzanieLogowania(uzytkownicy,login, haslo);
            //cout<<idUzytkownika<<endl;
            Sleep(1000);
        }

    }
    return 0;
}
