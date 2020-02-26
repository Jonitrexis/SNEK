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
    bool przegrana=0;
    while(przegrana==0){
        bool znal=0;
        while(znal==0){
            jabuszko.apple_x=losowanko(s);
            jabuszko.apple_y=losowanko(s);
            if(mapka[jabuszko.apple_x][jabuszko.apple_y]==32){
                mapka[jabuszko.apple_x][jabuszko.apple_y]=42;
                znal=1;
            }
        }
        char kierunek=0;
        kierunek=_getch();
        std::cout<<kierunek;
        if(kierunek==72){   //UP
            std::cout<<"UP";
        }
        if(kierunek==80){   //DOWN
            std::cout<<"DOWN";
        }
        if(kierunek==75){   //LEFT

        }
        if(kierunek==77){   //RIGHT

        }
    }
}
