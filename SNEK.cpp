#include <bits/stdc++.h>
#include <conio.h>
int losowanko(int n){
    return rand()%n;
}
struct Apple{
    int apple_x;
    int apple_y;
};
int main(){
    int s;
    srand(time(NULL));
    Apple jabuszko;
    std::deque <std::pair<int,int> > snek;
    std::cout<<"Podaj rozmiar planszy:"<<std::endl;
    std::cin>>s;
    char mapka[s][s];
    std::cout<<"git1";
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
    std::cout<<"git";
    char kierunek;
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
        kierunek=getch();
        std::cout<<kierunek;
    }
}
