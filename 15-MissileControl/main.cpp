#include <iostream>
#include<string>
#include<cstdio>
#include<windows.h>
#include<conio.h>
#include<cstdio>
#include<ctime>
#include<random>
using namespace std;

default_random_engine RandomGenerator(time(0));
uniform_int_distribution<int> randX(7, 35);
uniform_int_distribution<int> randY(1, 2);
uniform_int_distribution<int> speed(0, 10);
bool play = true;
const int height = 20;
const int width = 40;
bool  shooter= false;
enum Colors { blue=1, green, cyan, red, purple, yellow, grey, dgrey, hblue, hgreen, hred, hpurple, hyellow, hwhite };
char ColorChar(char ch, int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    cout << ch;
}
struct positions{
    int x;
    int y;
    int color;

};

positions shot;
positions player;
positions enemy;

int points = 0;
int miss = 0;

void Draw(){
    system("cls");
    srand(time(0));
    Colors color = Colors(rand()%10);
    for(int i =0; i < width + 1; i++)
        ColorChar('-', red);
    cout << endl;
    for(int i =0; i < height; i++){
        ColorChar('|', red);
        for(int j =0; j<width; j++){
            bool flag = true;
            if(j == enemy.x && i == enemy.y){
                ColorChar('W', enemy.color);
                flag = false;
            }
            if(j == player.x && i == player.y){
                ColorChar('X', player.color);
                flag = false;

            }
            if(shot.x == j && shot.y == i){
                ColorChar('*', shot.color);
                flag = false;
            }
            if(flag)
                cout << " ";
        }
        ColorChar('|', red);
        cout << endl;
    }
    for(int i =0; i < width + 1; i++)
        ColorChar('-', red);
    cout << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cyan);
    cout << "Points : " << points << " Miss : " << miss << endl;
}
void Input(){
    if(_kbhit()){
        switch(_getch()){
        case 27:
            play = false;
            break;
        case 75:
            player.x--;
            break;
        case 77:
            player.x++;
            break;
        case 80:
            player.y++;
            break;
        case 72:
            player.y--;
            break;

        case 't':
            shooter = true;
            break;
        case 'p':
            system("cls");
            cout << "\n\n\t\tPAUSE\n\n";
            cout << "\n\tEnter any key to continue\n";
            _getch();
            break;
        }
    }
}
void randEnemy(){
     enemy.x = randX(RandomGenerator);
     enemy.y = randY(RandomGenerator);
}
void Logic(){

        if(shooter){

            if(shot.y > player.y - 10){
                shot.y--;
                if(shot.x < player.x)
                    shot.x++;
                if(shot.x > player.x )
                    shot.x--;
            }


        }
        if(shot.y < player.y - 10){
            shot.x = width / 2;
            shot.y = height - 2;
            shooter = false;
        }
        if(shot.y == enemy.y && shot.x == enemy.x)
        {
            points ++;
            randEnemy();
            cout << "\a";
        }
        if(enemy.y > height -5){
            randEnemy();
            miss++;
        }
        if(enemy.y <height){
            if(speed(RandomGenerator) == 5)
                enemy.y+= 1;
        }
        //player logic
        if(player.x < 1)
            player.x = 0;
        if(player.x > width - 1)
            player.x = width-1;
        if(player.y < 1)
            player.y = 0;
        if(player.y > height -1)
            player.y = height - 1;
        if(miss == 10)
            play == false;
        if(points == 10)
            play = false;
}

void Begin(){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cyan);
        cout << "\n\n\t\tWelcome to Missile control\n\n";
        cout << "\n\tUse The arrows to control the cross\n";
        cout << "\n\t[t]Shot [arrow down] Reload the missile\n";
        cout << "\n\t[ESC]Exit [p]Pause\n\t";
        cout << "\n10 points to win the Game Good Luck Enter any key to start\n";
        cout << "\n\n\n\tTip: after shot the missile use up arrow to move the missile to up\n\n";
        _getch();
        srand(time(nullptr));
        player.color = blue;
        player.x = 5;
        player.y = 5;
        shot.color = yellow;
        shot.x = width / 2;
        shot.y = height - 2;
        enemy.x = randX(RandomGenerator);
        enemy.y = randY(RandomGenerator);
        enemy.color = green;

}
void WhoWin(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), blue);
    system("cls");
    if(points == 10 || points > miss){
        cout << "\n\n\t\tYou win\n\n\t\t";
    }
    else if(points < miss || miss == 10){
        cout << "\n\n\t\tYou loose the Game\t\t";
    }
    cout << "Thanks to play\n" << endl;
}
int main(){

        Begin();
        while(play){
        Logic();
        Input();
        Draw();
        }
    WhoWin();
    return 0;
}
