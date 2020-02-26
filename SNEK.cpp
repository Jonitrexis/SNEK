#include <bits/stdc++.h>
#include <conio.h>
int losowanko(int n){
    return rand()%n;
}
struct Apple{
    int apple_x;
    int apple_y;
};
void drukuj(int n, char **tab){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            std::cout<<tab[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}
int main(){
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
    for(int i=0;i<s;i++){
        mapka[0][i]=35;// hasz
        mapka[i][0]=35;
        mapka[s-1][i]=35;
        mapka[i][s-1]=35;
    }
    snek.push_front(std::make_pair((s-1)/2,(s-1)/2));
    mapka[(s-1)/2][(s-1)/2]='O';
    bool przegrana=0;
    bool zjedzone=1;
    drukuj(s,mapka);
    while(przegrana==0){
        bool znal=0;
        char kierunek=0;
        kierunek=_getch();
        if(kierunek==72){   //UP
            std::pair<int,int> coordinates_front=snek.front();
            std::pair<int,int> coordinates_back=snek.back();
            mapka[snek[0].first][snek[0].second]='o';   //ustawienie obecnej glowy na cialo
            coordinates_front.first=(coordinates_front.first-1)%(s-2);  //wskazanie przyszlej pozycji glowy
            if(mapka[coordinates_front.first][coordinates_front.second]==35){   //jesli wychodzimy poza plansze
                coordinates_front.first=s-2;
            }
            snek.push_front(coordinates_front);
            mapka[snek[0].first][snek[0].second]='O';   //ustawienie glowy na nowej pozycji
            if(coordinates_front.first==jabuszko.apple_x && coordinates_front.second==jabuszko.apple_y){
                zjedzone=1;     //ustawienie jabuszka na zjedzone, nie trzeba wymazywac ogona
            }
            else{
                mapka[coordinates_back.first][coordinates_back.second]=32;  //wymazywanie ogona, gdy nie jemy jabuszka
                snek.pop_back();
            }
        }
        if(kierunek==80){   //DOWN
            std::pair<int,int> coordinates_front=snek.front();
            std::pair<int,int> coordinates_back=snek.back();
            mapka[snek[0].first][snek[0].second]='o';   //ustawienie obecnej glowy na cialo
            coordinates_front.first=(coordinates_front.first+1)%(s-1);  //wskazanie przyszlej pozycji glowy
            if(mapka[coordinates_front.first][coordinates_front.second]==35){   //jesli wychodzimy poza plansze
                coordinates_front.first=1;
            }
            snek.push_front(coordinates_front);
            mapka[snek[0].first][snek[0].second]='O';   //ustawienie glowy na nowej pozycji
            if(coordinates_front.first==jabuszko.apple_x && coordinates_front.second==jabuszko.apple_y){
                zjedzone=1;     //ustawienie jabuszka na zjedzone, nie trzeba wymazywac ogona
            }
            else{
                mapka[coordinates_back.first][coordinates_back.second]=32;  //wymazywanie ogona, gdy nie jemy jabuszka
                snek.pop_back();
            }
        }
        if(kierunek==75){   //LEFT
            std::pair<int,int> coordinates_front=snek.front();
            std::pair<int,int> coordinates_back=snek.back();
            mapka[snek[0].first][snek[0].second]='o';   //ustawienie obecnej glowy na cialo
            coordinates_front.second=(coordinates_front.second-1)%(s-2);  //wskazanie przyszlej pozycji glowy
            if(mapka[coordinates_front.first][coordinates_front.second]==35){   //jesli wychodzimy poza plansze
                coordinates_front.second=s-2;
            }
            snek.push_front(coordinates_front);
            mapka[snek[0].first][snek[0].second]='O';   //ustawienie glowy na nowej pozycji
            if(coordinates_front.first==jabuszko.apple_x && coordinates_front.second==jabuszko.apple_y){
                zjedzone=1;     //ustawienie jabuszka na zjedzone, nie trzeba wymazywac ogona
            }
            else{
                mapka[coordinates_back.first][coordinates_back.second]=32;   //wymazywanie ogona, gdy nie jemy jabuszka
                snek.pop_back();
            }
        }
        if(kierunek==77){   //RIGHT
            std::pair<int,int> coordinates_front=snek.front();
            std::pair<int,int> coordinates_back=snek.back();
            mapka[snek[0].first][snek[0].second]='o';   //ustawienie obecnej glowy na cialo
            coordinates_front.second=(coordinates_front.second+1)%(s-1);  //wskazanie przyszlej pozycji glowy
            if(mapka[coordinates_front.first][coordinates_front.second]==35){   //jesli wychodzimy poza plansze
                coordinates_front.second=1;
            }
            snek.push_front(coordinates_front);
            mapka[snek[0].first][snek[0].second]='O';   //ustawienie glowy na nowej pozycji
            if(coordinates_front.first==jabuszko.apple_x && coordinates_front.second==jabuszko.apple_y){
                zjedzone=1;     //ustawienie jabuszka na zjedzone, nie trzeba wymazywac ogona
            }
            else{
                mapka[coordinates_back.first][coordinates_back.second]=32;   //wymazywanie ogona, gdy nie jemy jabuszka
                snek.pop_back();
            }
        }
        if(zjedzone==1){
            while(znal==0){
                jabuszko.apple_x=losowanko(s);
                jabuszko.apple_y=losowanko(s);
                if(mapka[jabuszko.apple_x][jabuszko.apple_y]==32){
                    mapka[jabuszko.apple_x][jabuszko.apple_y]=42;
                    znal=1;
                    zjedzone=0;
                }
            }
        }
        system("cls");
        drukuj(s,mapka);
    }
}
