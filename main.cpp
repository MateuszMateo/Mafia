#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <deque>
#include <functional>
#include <vector>
#include <map>
#include <set>

#define DEBUG(x) {cout << #x << " = " << x << endl;}
//#define DEBUG(x) ;

using namespace std;

const int MAX_N = 200;
const int MAX_M = 20000;

int wartosci_punktow[MAX_N+5];

vector<int> poloczenia[MAX_N+5];
vector<int> powiekszona_tablica_poloczen[MAX_N*2 + 3];
vector<int> tablica_krawedzi[MAX_M + MAX_N + 3];

int wartosci_krawedzi[MAX_M + MAX_N + 3];
int poczatki_krawedzi[MAX_M + MAX_N + 3];
int konce_krawedzi[MAX_M + MAX_N + 3];

bool czy_dodane[MAX_N*2]={0,};

deque<int> BFS(int poczatek, int koniec){
    for(int i=0;i<MAX_N+2;++i) {
        czy_dodane[i] = 0;
    }
    deque<int> kolejka;
    deque<int> wynik;
    int poprzednicy[MAX_N*2 +1];
    int poprzednie_krawedzie[MAX_M+MAX_N*2+3];
    kolejka.push_back(poczatek);
    while(kolejka.size()>0){
        int sprawdzane_miasto = kolejka.front();
        kolejka.pop_front();
        DEBUG(sprawdzane_miasto);
        if(sprawdzane_miasto==koniec){
            break;
        }else{
            DEBUG(powiekszona_tablica_poloczen[sprawdzane_miasto].size());
            for(int i = 0; i < powiekszona_tablica_poloczen[sprawdzane_miasto].size(); ++i){
                int sprawdzana_krawedz = powiekszona_tablica_poloczen[sprawdzane_miasto][i];
                int sprawdzany_sasiad = konce_krawedzi[sprawdzana_krawedz];
                DEBUG(sprawdzana_krawedz);
                DEBUG(sprawdzany_sasiad);

                if(czy_dodane[sprawdzany_sasiad]==false&&wartosci_krawedzi[sprawdzana_krawedz]>0){
                    cout<<"Dodaje punkt - "<< sprawdzany_sasiad << endl;
                    kolejka.push_back(sprawdzany_sasiad);
                    poprzednicy[sprawdzany_sasiad]=sprawdzane_miasto;
                    poprzednie_krawedzie[sprawdzany_sasiad]=sprawdzana_krawedz;
                    czy_dodane[sprawdzany_sasiad]=true;
                }
            }
        }
    }
    if(czy_dodane[koniec]==0){
        wynik.push_back(-3);
        return wynik;
    }else{
        int wytyczna = koniec;
        wynik.push_front(wytyczna);
        while(1){
            DEBUG(wytyczna);
            DEBUG(poprzednicy[wytyczna]);
            if(poprzednicy[wytyczna]==poczatek){
                break;
            }
            wytyczna=poprzednicy[wytyczna];
            wynik.push_front(wytyczna);
        }
        wynik.push_front(poczatek);
        return wynik;
    }
}

int main()
{
    int n; //ilość punktów
    int m; //ilość połączeń
    cin >> n;
    cin >> m;

    int poczatek, koniec;
    cin >> poczatek;
    cin >> koniec;

    for(int i = 0; i < n; ++i){
        int wartosc;
        cin >> wartosc;
        wartosci_punktow[i]=wartosc;
    }

    for(int i = 0; i < m; ++i){
        int x,y;
        cin >> x;
        cin >> y;
        poloczenia[x - 1].push_back(y - 1);
        poloczenia[y - 1].push_back(x - 1);
    }

    //    for(int i = 0; i < n; ++i){
    //        cout << endl;
    //        cout << "Punkt "<< i + 1<< " ma wartosc -> " << wartosci_punktow[i] << endl;
    //        cout << "laczy sie z: ";
    //        for(int j = 0; j < poloczenia[i].size(); ++j){
    //            cout<< poloczenia[i][j] + 1 <<", ";
    //        }
    //        cout<<endl;
    //    }

    int licz_kra = 0;

    for(int i = 0; i < n; ++i){
        int nowy_numer_wierzcholka = (i*2)+1;
        powiekszona_tablica_poloczen[nowy_numer_wierzcholka-1].push_back(nowy_numer_wierzcholka);
        tablica_krawedzi[nowy_numer_wierzcholka-1].push_back(licz_kra);
        wartosci_krawedzi[licz_kra]=wartosci_punktow[i];
        poczatki_krawedzi[licz_kra]=nowy_numer_wierzcholka-1;
        konce_krawedzi[licz_kra]=nowy_numer_wierzcholka;
        ++licz_kra;
    }

    for(int i = 0; i < n; ++i){
        int nowy_numer_wierzcholka = (i*2)+1;
        for(int j = 0; j < poloczenia[i].size(); ++j){
            powiekszona_tablica_poloczen[nowy_numer_wierzcholka].push_back(j*2);
            tablica_krawedzi[nowy_numer_wierzcholka].push_back(licz_kra);
            wartosci_krawedzi[licz_kra]=10000002;
            poczatki_krawedzi[licz_kra]=nowy_numer_wierzcholka;
            konce_krawedzi[licz_kra]=poloczenia[i][j]*2;
            ++licz_kra;
        }
    }


    for(int i = 0; i < n*2+1; ++i){
        cout<<"Punkt "<<i<<" posiada "<<tablica_krawedzi[i].size()<<" krawedzi: "<<endl;
        for(int j = 0; j< tablica_krawedzi[i].size();++j){
            cout<<" - "<<tablica_krawedzi[i][j]<<" do punktu: "<<konce_krawedzi[tablica_krawedzi[i][j]]<<" przepustowosc: ";
            if(wartosci_krawedzi[tablica_krawedzi[i][j]]==10000002){
                cout<<"nieskonczona ( "<<wartosci_krawedzi[tablica_krawedzi[i][j]]<<" )";
            }else{
                cout<<wartosci_krawedzi[tablica_krawedzi[i][j]];
            }
            cout<<endl;
        }
    }
    cout<<endl<<endl<<"||||||||||||||||||||||||| (^._.^) |||||||||||||||||||||||||"<<endl<<endl;

    deque<int>pierwsza_trasa = BFS((poczatek-1)*2,(koniec-1)*2 +1);

    for(int i = 0; i<pierwsza_trasa.size(); ++i){
        cout<< " - punkt "<<pierwsza_trasa[i]<<endl;
    }



    return 0;
}

