#include <iostream>
#include <ctime>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;

int numer=1;
int war=0;
class Character
{
protected:
    string name;
    int strength;
    int speed;
    int agility;

    public:

    virtual void wyswietl_postac()
    {
        cout<<"Nazwa postaci: "<<name<<endl;
        cout<<"Sila postaci: "<<strength<<endl;
        cout<<"Szybkosc postaci: "<<speed<<endl;
        cout<<"Zwinnosc postaci: "<<agility<<endl;
    }
    string get_name()
    {
        return name;
    }
};
class Enemy;
class Hero: public Character
{
    int experience=0;
    int level=1;
    int wins=0;
    int loses=0;
    public:

        void wyswietl_postac()
        {
            cout<<"Nazwa postaci: "<<name<<endl;
        cout<<"Sila postaci: "<<strength<<endl;
        cout<<"Szybkosc postaci: "<<speed<<endl;
        cout<<"Zwinnosc postaci: "<<agility<<endl;
        cout<<"Doswiadczenie postaci: "<<experience<<endl;
        cout<<"Level postaci: "<<level<<endl<<endl;
        }
   friend void createCharacter(Hero &c,int punkty);
   friend void fight(Hero &c,Enemy &e);
   friend void promotion(Hero &c);
   friend void load_from_file();
   friend void stats();
   friend void history();
};
vector <Hero> heroes;
vector <Hero> heroes_file;
vector <Enemy> enemies;


class Enemy: public Character
{
    int numer_wroga;
    int level;
    public:
    friend void generateEnemy(Enemy &c,int punkty);
    friend void fight(Hero &c,Enemy &e);
    friend void history();


            void wyswietl_postac()
        {
            cout<<"Nazwa postaci: "<<name<<numer_wroga<<endl;
        cout<<"Sila postaci: "<<strength<<endl;
        cout<<"Szybkosc postaci: "<<speed<<endl;
        cout<<"Zwinnosc postaci: "<<agility<<endl;
        cout<<"Level postaci: "<<level<<endl<<endl;
        }
    int get_number()
    {
        return numer_wroga;
    }
};

struct historia
{
    Hero bohater;
    Enemy przeciwnik;
    string status;
};

historia hist[128];
int iterator_hist=0;
void createCharacter(Hero &c,int punkty)
{
    int sila;
    int szybkosc;
    string nazwa;
    cout<<"Podaj nazwe postaci: "<<endl;
    cin>>nazwa;
    c.name=nazwa;
    int warunek=0;
    if(heroes.size()>0)
    {
       while(warunek==0)
    {
           for(auto n:heroes)
    {
        if(n.get_name()==nazwa)
        {
            cout<<"Istnieje bohater o podanej nazwie!"<<endl;
            cout<<"Podaj inna nazwe: "<<endl;
            cin>>nazwa;
            c.name=nazwa;
            break;
        }
        else
        {
            warunek=1;
        }
    }
    }
    }


    cout<<"Twoja postac nazywa sie: "<<c.name<<endl<<endl;
    cout<<"Punkty do rodzielenia: "<<punkty<<endl<<endl;
    do
    {
        cout<<"Podaj ilosc punktow sily:"<<endl<<endl;
       cin>>sila;
       if(sila>punkty)
       {
           cout<<"Nie wystarczajaca liczba punktow do rozdysponowania!"<<endl<<endl;
       }
       else
       {
           c.strength=sila;
       }
    }while(sila>punkty);

    cout<<endl<<"Ilosc punktow sily: "<<c.strength<<endl<<endl;
    cout<<"Ilosc pozostalych punktow: "<<punkty-c.strength<<endl<<endl;
        do
    {
    cout<<"Podaj ilosc punktow szybkosci:"<<endl<<endl;
    cin>>szybkosc;
       if(szybkosc>punkty-c.strength)
       {
           cout<<"Nie wystarczajaca liczba punktow do rozdysponowania!"<<endl<<endl;
       }
       else
       {
           c.speed=szybkosc;
       }
    }while(szybkosc>punkty-c.strength);
    cout<<endl<<"Ilosc punktow szybkosci: "<<c.speed<<endl<<endl;
    cout<<"Ilosc pozostalych punktow: "<<punkty-c.strength-c.speed<<endl<<endl;
    c.agility=punkty-c.strength-c.speed;
    cout<<"Ilosc punktow zwinnosci: "<<c.agility<<endl<<endl;
    c.experience=0;
    c.level=1;
    cout<<"Level postaci: "<<c.level<<endl<<endl;
    cout<<"Doswiadczenie postaci: "<<c.experience<<endl<<endl;

}
void generateEnemy(Enemy &c,int punkty)
{
    c.numer_wroga=numer;
    string nazwa="Wrog";
    c.name=nazwa;
    c.strength=rand()%101;
    int reszta=punkty-c.strength;
    c.speed=rand()%reszta;
    reszta-=c.speed;
    c.agility=reszta;
    c.level=rand()%3+1;
    cout<<"Nazwa postaci: "<<c.name<<c.numer_wroga<<endl<<endl;
    cout<<"Sila postaci: "<<c.strength<<endl<<endl;
    cout<<"Szybkosc postaci: "<<c.speed<<endl<<endl;
    cout<<"Zwinnosc postaci: "<<c.agility<<endl<<endl;
    cout<<"Level postaci: "<<c.level<<endl<<endl;
    numer++;
}
void menu();
void load_from_file()
{
    fstream bohaterowie;
    string nazwa;
    string name;
    Hero c;
    int strength,speed,agility;

    if(war==0)
    {
       bohaterowie.open("bohaterowie.txt",fstream::in);
		do
	{
	    bohaterowie>>c.name>>c.strength>>c.speed>>c.agility;
	    c.level=1;
        c.experience=0;
        heroes_file.push_back(c);
	}while(!bohaterowie.eof());
    bohaterowie.close();
    war++;
    }

    for(auto n:heroes_file)
    {
        n.wyswietl_postac();
    }
    cout<<"Wybierz postac do wczytania!"<<endl<<endl;
    cin>>nazwa;

    if(heroes.size()>0)
    {
        for(auto n:heroes)
        {
            if(n.get_name()==nazwa)
            {
                cout<<"Istnieje bohater o podanej nazwie!"<<endl<<endl;
                cout<<"Nie mozna zaladowac postaci!"<<endl<<endl;
                break;
                menu();

            }
            else
            {
                for(auto m:heroes_file)
                    {
                        if(m.get_name()==nazwa)
                            {
                            heroes.push_back(m);
                            break;
                            }

                    }
            }
        }
    }
    else if(heroes.size()==0)
    {
      for(auto m:heroes_file)
                    {
                        if(m.get_name()==nazwa)
                            {
                            heroes.push_back(m);
                            break;
                            }
                    }
    }

        menu();
}

void promotion(Hero &c)
{
    cout<<"Udalo ci sie awansowac. Twoj level to: "<<c.level<<endl;
    cout<<"Masz do rozdysponowania 10 punktow!"<<endl;
    int sila;
    int szybkosc;
    do
    {
        cout<<"Podaj ilosc punktow sily:"<<endl<<endl;

       cin>>sila;
       if(sila>10)
       {
           cout<<"Nie wystarczajaca liczba punktow do rozdysponowania!"<<endl<<endl;
       }
       else{
        c.strength+=sila;
       }


    }while(sila>10);

    cout<<endl<<"Ilosc punktow sily: "<<c.strength<<endl<<endl;
    cout<<"Ilosc pozostalych punktow: "<<10-sila<<endl<<endl;
        do
    {
    cout<<"Podaj ilosc punktow szybkosci:"<<endl<<endl;

    cin>>szybkosc;
    if(szybkosc>10-sila)
       {
           cout<<"Nie wystarczajaca liczba punktow do rozdysponowania!"<<endl<<endl;
       }
       else{
        c.speed+=szybkosc;
       }


    }while(szybkosc>10-sila);
    cout<<endl<<"Ilosc punktow szybkosci: "<<c.speed<<endl<<endl;
    cout<<"Ilosc pozostalych punktow: "<<10-sila-szybkosc<<endl<<endl;
    c.agility+=10-sila-szybkosc;
    cout<<"Ilosc punktow zwinnosci: "<<c.agility<<endl<<endl;
}

void fight(Hero &c,Enemy &e)
{
    hist[iterator_hist].bohater=c;
    hist[iterator_hist].przeciwnik=e;
    int win=0;
    if(rand()%10>3)
    {
       win++;
    }

    if(c.level>=e.level)
    {
        win++;
    }

if(c.strength>e.strength)
    {
        win++;
    }
 if(c.speed>e.speed)
    {
        win++;
    }
if(c.agility>e.agility)
        {
            win++;
        }
            if(win>=3)
    {
        cout<<"Wygrales pojedynek!!!"<<endl;
     c.experience+=rand()%5+1;
            cout<<"Doswiadczenie postaci: "<<c.experience<<endl;
        cout<<"Level postaci: "<<c.level<<endl;
        c.wins++;
        hist[iterator_hist].status="Wygrana";
                if(c.experience>=10)
        {
            c.level++;
            c.experience=c.experience%10;
            promotion(c);
        }

    }
    else
    {
        cout<<"Przegrales pojedynek!!!"<<endl;
        cout<<"Straciles 1 punkt doswiadczenia!"<<endl;
        c.loses++;
        hist[iterator_hist].status="Przegrana";

        if(c.experience>0)
        {
            c.experience-=1;
        }

        cout<<"Doswiadczenie postaci: "<<c.experience<<endl;
    }

    iterator_hist++;
}

void stats()
{
    for(auto n:heroes)
    {
        cout<<"Bohater: "<<n.name<<endl;
        cout<<"Liczba wygranych pojedynkow: "<<n.wins<<endl;
        cout<<"Liczba przegranych pojedynkow: "<<n.loses<<endl;
    }
}
void history()
{
    for(int i=0;i<iterator_hist;i++)
    {
        hist[i].bohater.wyswietl_postac();
        cout<<endl;
        hist[i].przeciwnik.wyswietl_postac();
        cout<<"Status pojedynku: "<<hist[i].status<<endl;
    }
}

void menu()
{
    int numer;
    cout<<"MENU"<<endl<<endl;
    cout<<"1.Stworzenie postaci."<<endl;
    cout<<"2.Wczytanie istniejacej postaci"<<endl;
    cout<<"3.Stworzenie wroga"<<endl;
    cout<<"4.Wyswietl postacie"<<endl;
    cout<<"5.Walka"<<endl;
    cout<<"6.Wyswietl statystyki pojedynkow"<<endl;
    cout<<"7.Wyswietl historie walk"<<endl;
    cout<<"8.Wyjscie z gry"<<endl;
    cin>>numer;

    switch(numer)
    {
    case 1:
        {
            Hero c;
            system("CLS");
            createCharacter(c,100);
            heroes.push_back(c);
            menu();
            break;
        }
    case 2:
        {
            Hero c;
            system("CLS");
            load_from_file();
            break;
        }
    case 3:
        {
            system("CLS");
            Enemy e;
            generateEnemy(e,100);
            enemies.push_back(e);
            menu();
            break;
        }
    case 4:
        {
            system("CLS");
            for(auto n:heroes)
            {
                n.wyswietl_postac();
            }
            menu();
            break;
        }
    case 5:
        {
            system("CLS");
            string nazwa;

            cout<<"Wybierz postac: "<<endl;
            for(auto n:heroes)
            {
                n.wyswietl_postac();
            }

            cin>>nazwa;
             for(auto &n:heroes)
            {
                        if(n.get_name()==nazwa)
        {
            int nr=rand()%enemies.size()+1;
            for(auto m:enemies)
            {
                if(m.get_number()==nr)
                {
                    m.wyswietl_postac();

                    fight(n,m);
                }
            }
        }
            }
            menu();
        }
    case 6:
        {
            system("CLS");
            stats();
            menu();
            break;
        }
    case 7:
        {
            system("CLS");
            history();
            menu();
            break;
        }
    case 8:
        {
            exit(0);
        }
    }
}

int main()
{
    srand(time(NULL));
menu();
}

