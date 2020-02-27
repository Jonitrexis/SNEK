#include <bits/stdc++.h>
#include <conio.h>
#include <Windows.h>
//cokolwiek by sie zmienilo
int losowanko(int n){       //generowanie losowych liczb w zaleznosci od rozmiaru planszy
    return rand()%n;
}
struct Apple{       //tworzenie jabuszka
    int apple_x;
    int apple_y;
};
void hidecursor(){              //funkcja do ukrywania kursora
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
void cursor(int y, int x){      //funkcja do ustawiania pozycji kursora
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}
void console_colour(unsigned short colour){     //zabawa z kolorowaniem terminala
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    SetConsoleTextAttribute(hOut, colour);
}
void drukuj(int n, char **tab) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 || i == n - 1 || j == 0 || j == n - 1)   console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);        //kolorujemy ramki planszy
            std::cout << tab[i][j];
            console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);     // ustawiamy standardowe ustawienia kolorow tekstu i tla konsoli
            if ((i == 0 || i == n - 1 || j==0 || j==n-2)&&(j!=n-1)) console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);    //kolorujemy ramki planszy
                std::cout << " ";
                console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);     // ustawiamy standardowe ustawienia kolorow tekstu i tla konsoli
        }
        std::cout << std::endl;
    }
}
int main(){
    hidecursor();       //wywolanie funkcji ukrywajacej kursor
    int s;
    srand(time(NULL));
    Apple jabuszko;
    std::deque <std::pair<int,int> > snek;
    std::cout<<"Podaj rozmiar planszy:"<<std::endl;
    std::cin>>s;
    char **mapka;
    mapka=new char *[s];
    for(int i=0;i<s;i++)    mapka[i]=new char[s];
    for(int i=0;i<s;i++){
        for(int j=0;j<s;j++){
            mapka[i][j]=32; //spacja
        }
    }
    for(int i=0;i<s;i++){       //haszowanie ramek
        mapka[0][i]=35;// hasz
        mapka[i][0]=35;
        mapka[s-1][i]=35;
        mapka[i][s-1]=35;
    }
    snek.push_front(std::make_pair((s-1)/2,(s-1)/2));   //ustawienie glowy weza na srodku
    mapka[(s-1)/2][(s-1)/2]='O';
    bool przegrana=0;
    bool zjedzone=1;
    drukuj(s,mapka);
    while(przegrana==0){
        hidecursor();
        bool znal=0;
        char kierunek=0;
        kierunek=_getch();
        if(kierunek==72){   //UP
            std::pair<int,int> coordinates_front=snek.front();      //koordynaty glowy weza
            std::pair<int,int> coordinates_back=snek.back();        //koordynaty ogona weza
            mapka[snek[0].first][snek[0].second]='o';
            cursor(snek[0].first+2,2*snek[0].second);   //ustawienie obecnej glowy na cialo
            console_colour(FOREGROUND_GREEN| FOREGROUND_INTENSITY);       //kolorujemy weza na zielono
            std::cout<<"o";
            coordinates_front.first=(coordinates_front.first-1)%(s-2);  //wskazanie przyszlej pozycji glowy
            if(mapka[coordinates_front.first][coordinates_front.second]==35){   //jesli wychodzimy poza plansze
                coordinates_front.first=s-2;
            }
            snek.push_front(coordinates_front);
            mapka[snek[0].first][snek[0].second]='O';
            cursor(snek[0].first+2,2*snek[0].second);   //ustawienie glowy na nowej pozycji
            std::cout<<"O";
            console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);     // ustawiamy standardowe ustawienia kolorow tekstu i tla konsoli
            if(coordinates_front.first==jabuszko.apple_x && coordinates_front.second==jabuszko.apple_y){
                zjedzone=1;     //ustawienie jabuszka na zjedzone, nie trzeba wymazywac ogona
            }
            else{
                mapka[coordinates_back.first][coordinates_back.second]=32;
                cursor(coordinates_back.first+2,2*coordinates_back.second);     //wymazywanie ogona, gdy nie jemy jabuszka
                std::cout<<" ";
                snek.pop_back();
            }
        }
        if(kierunek==80){   //DOWN
            std::pair<int,int> coordinates_front=snek.front();      //koordynaty glowy weza
            std::pair<int,int> coordinates_back=snek.back();        //koordynaty ogona weza
            mapka[snek[0].first][snek[0].second]='o';
            cursor(snek[0].first+2,2*snek[0].second);   //ustawienie obecnej glowy na cialo
            console_colour(FOREGROUND_GREEN | FOREGROUND_INTENSITY);       //kolorujemy weza na zielono
            std::cout<<"o";
            coordinates_front.first=(coordinates_front.first+1)%(s-1);  //wskazanie przyszlej pozycji glowy
            if(mapka[coordinates_front.first][coordinates_front.second]==35){   //jesli wychodzimy poza plansze
                coordinates_front.first=1;
            }
            snek.push_front(coordinates_front);
            mapka[snek[0].first][snek[0].second]='O';
            cursor(snek[0].first+2,2*snek[0].second);   //ustawienie glowy na nowej pozycji
            std::cout<<"O";
            console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);     // ustawiamy standardowe ustawienia kolorow tekstu i tla konsoli
            if(coordinates_front.first==jabuszko.apple_x && coordinates_front.second==jabuszko.apple_y){
                zjedzone=1;     //ustawienie jabuszka na zjedzone, nie trzeba wymazywac ogona
            }
            else{
                mapka[coordinates_back.first][coordinates_back.second]=32;
                cursor(coordinates_back.first+2,2*coordinates_back.second);     //wymazywanie ogona, gdy nie jemy jabuszka
                std::cout<<" ";
                snek.pop_back();
            }
        }
        if(kierunek==75){   //LEFT
            std::pair<int,int> coordinates_front=snek.front();      //koordynaty glowy weza
            std::pair<int,int> coordinates_back=snek.back();        //koordynaty ogona weza
            mapka[snek[0].first][snek[0].second]='o';
            cursor(snek[0].first+2,2*snek[0].second);   //ustawienie obecnej glowy na cialo
            console_colour(FOREGROUND_GREEN| FOREGROUND_INTENSITY);       //kolorujemy weza na zielono
            std::cout<<"o";
            coordinates_front.second=(coordinates_front.second-1)%(s-2);  //wskazanie przyszlej pozycji glowy
            if(mapka[coordinates_front.first][coordinates_front.second]==35){   //jesli wychodzimy poza plansze
                coordinates_front.second=s-2;
            }
            snek.push_front(coordinates_front);
            mapka[snek[0].first][snek[0].second]='O';
            cursor(snek[0].first+2,2*snek[0].second);   //ustawienie glowy na nowej pozycji
            std::cout<<"O";
            console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);     // ustawiamy standardowe ustawienia kolorow tekstu i tla konsoli
            if(coordinates_front.first==jabuszko.apple_x && coordinates_front.second==jabuszko.apple_y){
                zjedzone=1;     //ustawienie jabuszka na zjedzone, nie trzeba wymazywac ogona
            }
            else{
                mapka[coordinates_back.first][coordinates_back.second]=32;
                cursor(coordinates_back.first+2,2*coordinates_back.second);     //wymazywanie ogona, gdy nie jemy jabuszka
                std::cout<<" ";
                snek.pop_back();
            }
        }
        if(kierunek==77){   //RIGHT
            std::pair<int,int> coordinates_front=snek.front();      //koordynaty glowy weza
            std::pair<int,int> coordinates_back=snek.back();        //koordynaty ogona weza
            mapka[snek[0].first][snek[0].second]='o';
            cursor(snek[0].first+2,2*snek[0].second);   //ustawienie obecnej glowy na cialo
            console_colour(FOREGROUND_GREEN| FOREGROUND_INTENSITY);       //kolorujemy weza na zielono
            std::cout<<"o";
            coordinates_front.second=(coordinates_front.second+1)%(s-1);  //wskazanie przyszlej pozycji glowy
            if(mapka[coordinates_front.first][coordinates_front.second]==35){   //jesli wychodzimy poza plansze
                coordinates_front.second=1;
            }
            snek.push_front(coordinates_front);
            mapka[snek[0].first][snek[0].second]='O';
            cursor(snek[0].first+2,2*snek[0].second);   //ustawienie glowy na nowej pozycji
            std::cout<<"O";
            console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);     // ustawiamy standardowe ustawienia kolorow tekstu i tla konsoli
            if(coordinates_front.first==jabuszko.apple_x && coordinates_front.second==jabuszko.apple_y){
                zjedzone=1;     //ustawienie jabuszka na zjedzone, nie trzeba wymazywac ogona
            }
            else{
                mapka[coordinates_back.first][coordinates_back.second]=32;
                cursor(coordinates_back.first+2,2*coordinates_back.second);     //wymazywanie ogona, gdy nie jemy jabuszka
                std::cout<<" ";
                snek.pop_back();
            }
        }
        if(zjedzone==1){
            while(znal==0){
                jabuszko.apple_x=losowanko(s);
                jabuszko.apple_y=losowanko(s);
                if(mapka[jabuszko.apple_x][jabuszko.apple_y]==32){
                    mapka[jabuszko.apple_x][jabuszko.apple_y]=42;
                    cursor(jabuszko.apple_x+2,2*jabuszko.apple_y);
                    console_colour(FOREGROUND_RED);     //kolorujemy jabuszko na czerwono
                    std::cout<<"*";
                    console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);     // ustawiamy standardowe ustawienia kolorow tekstu i tla konsoli
                    znal=1;
                    zjedzone=0;
                }
            }
        }
    }
}
