#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int wiersze = 23;
const int kolumny = 12;

int pole [wiersze] [kolumny] = { 0 };

struct Blok
{
    int x, y;
}; 

Blok a[4], b[4];

int figures[7][4] =
{
    1,3,5,7,
    2,4,5,7,
    3,5,4,6,
    3,5,4,7,
    2,3,5,7,
    3,5,7,6,
    2,3,4,5,
};

bool kolizja()
{
    for (int i = 0; i < 4; i++)
    {
        if (a[i].x < 0 || a[i].x >= kolumny || a[i].y >= wiersze)
        {
            return 0;
        }
        else if (pole[a[i].y][a[i].x])
        {
            return 0;
        }
    }
    return 1;
};
void rotacja(bool r)
{
    if (r)
    {
        Blok p = a[1];
        for (int i=0;i<4;i++)
        {
            int x = a[i].y-p.y;
            int y = a[i].x-p.x;
            a[i].x = p.x-x;
            a[i].y = p.y+y;
        }
        if (!kolizja())
        {
            for (int i=0;i<4;i++)
            {
                a[i]=b[i];
            }
        }
    }
}

void poruszanie(int dx)
{
    for (int i=0;i<4;i++) 
    { 
        b[i]=a[i];
        a[i].x+=dx; 
    }
    if (!kolizja())
    {
        for (int i=0;i<4; i++)
        {
            a[i]=b[i];
        }
    }
}
int wynik = 0;
int end = 0;

int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(336, 700), "Tetris Minecraft");
    
    Texture t1, t2, t3;
    t1.loadFromFile("images/bloki.jpg");
    t2.loadFromFile("images/tlo.png");
    t3.loadFromFile("images/frame.png");


    Sprite s(t1), background(t2), ramka(t3);

    int dx = 0; bool rotate = 0; int colorNum = 1;
    float timer = 0, delay = 0.3;



    sf::Text text;
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    sf::Font font;
    font.loadFromFile("arial.ttf");
    text.setFont(font);

    
    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                window.close();
            }
            if (e.type == Event::KeyPressed)
            {
                if (e.key.code == Keyboard::Up)
                {
                    rotate = 1;
                }
                else if (e.key.code == Keyboard::Left)
                {
                    dx = -1;
                }
                else if (e.key.code == Keyboard::Right)
                {
                    dx = 1;
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            delay = 0.05;
        }
        if (end != 1)
        {
            poruszanie(dx);
            rotacja(rotate);


            if (timer > delay)
            {
                for (int i = 0; i < kolumny; i++)
                {
                    if (pole[2][i] > 0)
                    {
                        text.setCharacterSize(50);
                        text.setString("You lost !!!");
                        text.setPosition(70, 330);
                        window.draw(text);
                        window.display();
                        end = 1;
                    }
                }
                for (int i = 0; i < 4; i++)
                {
                    b[i] = a[i];
                    a[i].y += 1;
                }

                if (!kolizja())
                {
                    for (int i = 0; i < 4; i++)
                    {
                        pole[b[i].y][b[i].x] = colorNum;
                    }
                    colorNum = 1 + rand() % 16;
                    int n = rand() % 7;
                    for (int i = 0; i < 4; i++)
                    {
                        a[i].x = figures[n][i] % 2;
                        a[i].y = figures[n][i] / 2;
                    }
                }

                timer = 0;
            }
        }
        if (end == 0)
        {
            int k = wiersze - 1;
            for (int i = wiersze - 1; i > 0; i--)
            {
                int count = 0;
                for (int j = 0; j < kolumny; j++)
                {
                    if (pole[i][j])
                    {
                        count++;
                    }
                    pole[k][j] = pole[i][j];
                }
                if (count < kolumny)
                {
                    k--;
                }
                else
                {
                    wynik++;
                }
            }

            dx = 0;
            rotate = 0;
            delay = 0.3;
            window.clear(Color::White);
            window.draw(background);
            window.draw(ramka);


            for (int i = 0; i < wiersze; i++)
                for (int j = 0; j < kolumny; j++)
                {
                    if (pole[i][j] == 0)
                    {
                        continue;
                    }
                    s.setTextureRect(IntRect(pole[i][j] * 28 - 28, 0, 28, 28));
                    s.setPosition(j * 28, i * 28);
                    window.draw(s);
                }

            for (int i = 0; i < 4; i++)
            {
                s.setTextureRect(IntRect(colorNum * 28 - 28, 0, 28, 28));
                s.setPosition(a[i].x * 28, a[i].y * 28);
                window.draw(s);
            }
            ramka.setPosition(-45, 644);
            char tekst[100];
            sprintf_s(tekst, "%d", wynik);
            std::string wyj = tekst;
            text.setPosition(175, 660);
            text.setString(wyj);

            window.draw(ramka);
            window.draw(text);
            window.display();
        }
        }

    return 0;
}
