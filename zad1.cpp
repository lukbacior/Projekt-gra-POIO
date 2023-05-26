#include <iostream>
#include <ctime>
using namespace std;

class Character
{
private:
    string name;
    int strength;
    int speed;
    int agility;

    public:
    friend void createCharacter(Character &c,int punkty);
    friend void generateEnemy(Character &c,int punkty);
    friend void fight(Character &c,Character &e);

    void wyswietl_postac()
    {
        cout<<"Nazwa postaci: "<<name<<endl;
        cout<<"Sila postaci: "<<strength<<endl;
        cout<<"Szybkosc postaci: "<<speed<<endl;
        cout<<"Zwinnosc postaci: "<<agility<<endl;
    }
};

void createCharacter(Character &c,int punkty)
{
    cout<<"Podaj nazwe postaci: "<<endl;
    cin>>c.name;
    cout<<"Twoja postac nazywa sie: "<<c.name<<endl;
    cout<<"Punkty do rodzielenia: "<<punkty<<endl;
    cout<<"Podaj ilosc punktow sily:"<<endl;
    cin>>c.strength;
    cout<<"Ilosc punktow sily: "<<c.strength<<endl;
    cout<<"Ilosc pozostalych punktow: "<<punkty-c.strength<<endl;
    cout<<"Podaj ilosc punktow szybkosci:"<<endl;
    cin>>c.speed;
    cout<<"Ilosc punktow szybkosci: "<<c.speed<<endl;
    cout<<"Ilosc pozostalych punktow: "<<punkty-c.strength-c.speed<<endl;
    c.agility=punkty-c.strength-c.speed;
    cout<<"Ilosc punktow zwinnosci: "<<c.agility<<endl;


}
void generateEnemy(Character &c,int punkty)
{
    int numer=49;
    char nazwa[128]={'W','r','o','g'};
    nazwa[4]=(char)numer;
    c.name=nazwa;
    c.strength=rand()%101;
    int reszta=punkty-c.strength;
    c.speed=rand()%reszta;
    reszta-=c.speed;
    c.agility=reszta;
    cout<<"Nazwa postaci: "<<c.name<<endl;
    cout<<"Sila postaci: "<<c.strength<<endl;
    cout<<"Szybkosc postaci: "<<c.speed<<endl;
    cout<<"Zwinnosc postaci: "<<c.agility<<endl;
    numer++;
}

void fight(Character &c,Character &e)
{
    int win=0;
    if(c.strength>e.strength)
    {
        win++;
    }
    if(c.speed>e.speed)
    {
        win++;
    }
    if(win==2)
    {
        cout<<"Wygrales pojedynek!!!"<<endl;
    }
    else
    {
        if(c.agility>e.agility)
        {
            win++;
        }
            if(win==2)
    {
        cout<<"Wygrales pojedynek!!!"<<endl;
    }
    else
    {
        cout<<"Przegrales pojedynek!!!"<<endl;
    }
    }

}


int main()
{
    srand(time(NULL));
Character c1;
Character c2;
createCharacter(c1,100);
generateEnemy(c2,100);
fight(c1,c2);
}

