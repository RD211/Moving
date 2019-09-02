#include <iostream>
#include <string>
#define _WIN32_WINNT 0x0502
#include <windows.h>
#include <sstream>
#include <conio.h>
#include <process.h>
using namespace std;
int color=30,color2=30;
COORD Mouse,Begin,Info,Back;
bool value = false,rainbow=false,railgun=false;
namespace patch
{
template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}
}

void setColor(int Color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);

}
void setMouse(COORD Mouse)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Mouse);
}
void notrail(bool value,string caracter, COORD Mouse)
{
    if(value)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Mouse);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        for(int i =0; i<caracter.length(); i++)
        {
            cout<<" ";
        }
    }

}
void projectile(void* number)
{
    setColor(color);
    setMouse(Mouse);
    for(COORD i = Mouse; i.Y>=6; i.Y--)
    {
        if(rainbow)
        {
            setColor(rand()%9);
        }
        else
        {
            setColor(color);
        }
        setMouse(i);
        cout<<"|";
        i.Y+=1;
        setMouse(i);
        setColor(0);
        Sleep(50);
        cout<<" ";
        i.Y-=1;
    }
}
int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO current;
    SetConsoleTitle("Game -RD");
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    char input;

    string caracter="X";
    Back.X=0;
    Back.Y=6;
    Mouse.X=10;
    Mouse.Y=20;
    Begin.X=0;
    Begin.Y=0;
    Info.X=0;
    Info.Y=5;
    while(true)
    {
        GetConsoleScreenBufferInfo (hConsole, &current);
        setMouse(Info);
        setColor(30);
        cout<<"*Color: "<<color<<"  "<<"*Caracter: "<<caracter<<"  "<<"Coords Text: X: "<<Mouse.X<<" Y: "<<Mouse.Y;
        for(int i = 0; i<current.dwSize.X-43-patch::to_string(color).length()-caracter.length()- patch::to_string(Mouse.X).length()- patch::to_string(Mouse.Y).length(); i++)
        {
            cout<<" ";
        }

        setMouse(Begin);
        setColor(0);
        input = getch();
        switch(input)
        {
        case 'w':
            notrail(value,caracter,Mouse);
            Mouse.Y-=1;
            break;
        case 'a':
            notrail(value,caracter,Mouse);

            Mouse.X-= caracter.length();
            break;
        case 's':
            notrail(value,caracter,Mouse);

            Mouse.Y+=1;
            break;
        case 'd':
            notrail(value,caracter,Mouse);

            Mouse.X+= caracter.length();
            break;
        case 'q':
            notrail(value,caracter,Mouse);
            system("cls");
            break;
        case 'f':
            if(railgun)
            {
                _beginthread(projectile, 0, NULL);
            }
            else
            {
                setColor(color);
                setMouse(Mouse);
                for(COORD i = Mouse; i.Y>=6; i.Y--)
                {
                    if(rainbow)
                    {
                        setColor(rand()%9);
                    }
                    else
                    {
                        setColor(color);
                    }
                    setMouse(i);
                    cout<<"|";
                    i.Y+=1;
                    setMouse(i);
                    setColor(0);
                    Sleep(50);
                    cout<<" ";
                    i.Y-=1;
                }
            }

            break;
        case '1':
            cin>>color;
            break;
        case '2':
            getline(cin,caracter);
            break;
        case '3':
            if(value)
            {
                value= false;
            }
            else
            {
                value=true;
            }
            break;
        case '4':
            int a;
            cin>>a;
            setColor(color);
            setMouse(Mouse);
            for(COORD i = Mouse; i.Y>=Mouse.Y-a; i.Y--)
            {
                if(i.Y<=5||i.X<0||i.X>208-caracter.length()||i.Y>49)
                {
                    break;
                }
                if(rainbow)
                {
                    setColor(rand()%9);
                }
                else
                {
                    setColor(color);
                }
                setMouse(i);
                cout<<"|";
            }
            break;
        case '5':
            int b;
            cin>>b;
            setColor(color);
            setMouse(Mouse);
            for(COORD i = Mouse; i.X<=Mouse.X+b; i.X++)
            {
                if(i.Y<=5||i.X<0||i.X>208-caracter.length()||i.Y>49)
                {
                    break;
                }
                if(rainbow)
                {
                    setColor(rand()%9);
                }
                else
                {
                    setColor(color);
                }
                setMouse(i);
                cout<<"-";
            }
            break;
        case '6':
            if(rainbow)
            {
                rainbow=false;
            }
            else
            {
                rainbow=true;
            }

            break;
        case '7':
            if(!rainbow)
            {
                cin>>color2;
                setColor(color2);
            }
            setMouse(Back);
            for(int d= 6; d<50; d++)
            {


                for(int i =0; i<211; i++)
                {
                    if(rainbow)
                    {
                        setColor(rand()%100);
                    }
                    setMouse(Back);
                    cout<<" ";
                    Back.X+=1;
                }
                Back.X=0;
                Back.Y+=1;
            }
            Back.X=0;
            Back.Y=6;
            break;
        case 'H':
            MessageBox(
                NULL,
                (LPCSTR)"- w, a, s, d (to Move)\n- 1(change color *int)\n- 2(to change caracter)\n- 3(toggle trail)\n- 4(creates upward line)\n- 5(creates horizontal line)\n- 6(Toggles rainbow)\n- 7(change background)\n- q(clear)\n- f(fire)\n- 8 toggle railgun",
                (LPCSTR)"Commands",NULL);
            break;
        case'8':
                if(railgun)
                {
                    railgun=false;
                }
                else
                {
                    railgun=true;
                }
            break;

        }


        if(Mouse.Y<=5)
        {
            Mouse.Y=6;
        }
        if(Mouse.X<0)
        {
            Mouse.X=0;
        }
        if(Mouse.X>211-caracter.length())
        {
            Mouse.X=211-caracter.length();
        }
        if(Mouse.Y>49)
        {
            Mouse.Y=49;
        }
        if(rainbow)
        {
            setColor(rand()%1000+10);
        }
        else
        {
            setColor(color);
        }

        setMouse(Mouse);
        cout<<caracter;

    }
}

