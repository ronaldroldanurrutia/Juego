#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<list>





#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
using namespace std;

void gotoxy(int x,int y){
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwpos;
    dwpos.X=x;
    dwpos.Y=y;
    SetConsoleCursorPosition(hcon,dwpos);

}

class BALA{
    private:
            int x;
            int y;
    public:
        BALA(int _x,int _y){
            this->x=_x;
            this->y=_y;
        }
        int getx(){
            return x;
        }
        int gety(){
            return y;
        }
        void X(int _x){
            this->x=_x;
        }
        void Y(int _y){
            this->y = _y;
        }
        void mover();
        bool fuera();

};

void BALA::mover(){
    gotoxy(x,y);
    printf(" ");
    if(y>4){


    this->y--;
    gotoxy(x,y);
    printf("*");

    }
}

bool BALA::fuera(){
    if(y==4){
        gotoxy(x,y);
        printf(" ");
        return true;
    }
    return false;

}

class NAVE{
    private:
        int x;
        int y;
        int corazones;
        int vidas;
        int puntuacion;

    public:
        NAVE(int _x=10,int _y=10){
            this->x=_x;
            this->y=_y;
            this->corazones=3;
            this->vidas=2;
            this->puntuacion=0;
        }
        void crear();
        void mover();
        void limpiar();
        void pintar();
        void PintarCorazones();
        void resetear();
        void imprimirpuntuacion();
        int getx(){
            return this->x;
        }
        int gety(){
            return this->y;
        }
        void alterar(){
            this->corazones--;
        }
        int getvidas(){
            return this->vidas;
        }
        void alterarvidas(int n){
            this->vidas=n;
        }
        void alterarcorazones(int n){
            this->corazones=n;
        }
        void insertpuntuacion(int a){
            this->puntuacion+=(30*a);
        }
        void mostrarvidas();
};

void NAVE::crear(){
    gotoxy(x,y);printf("  %c",30);
    gotoxy(x,y+1);printf(" %c%c%c",40,207,41);
    gotoxy(x,y+2);printf("%c%c %c%c",30,190,190,30);

}

void NAVE::imprimirpuntuacion(){
    gotoxy(1,2);
    printf("PUNTUACION %d",this->puntuacion);

}

void NAVE::PintarCorazones(){
    gotoxy(64,2);printf("SALUD");
    gotoxy(70,2);printf("   ");
    for(int i=0;i<corazones;i++){
        gotoxy(70+i,2);printf("%c",3);
    }

}

void NAVE::mostrarvidas(){
    gotoxy(20,2);printf("VIDAS %d",this->vidas);

}

void NAVE::pintar(){
    for(int i=2;i<78;i++){
        gotoxy(i,3);printf("%c",205);
        gotoxy(i,33);printf("%c",205);

    }
    for(int i=4;i<33;i++){
        gotoxy(2,i);printf("%c",186);
        gotoxy(77,i);printf("%c",186);

    }
    gotoxy(2,3);printf("%c",201);
    gotoxy(2,33);printf("%c",200);
    gotoxy(77,3);printf("%c",187);
    gotoxy(77,33);printf("%c",188);


}

void NAVE::limpiar(){
    gotoxy(x,y);printf("     ");
    gotoxy(x,y+1);printf("     ");
    gotoxy(x,y+2);printf("     ");

}

void NAVE::resetear(){
    if(this->corazones==0){
        limpiar();
        gotoxy(x,y);printf("  *   ");
        gotoxy(x,y+1);printf(" ***  ");
        gotoxy(x,y+2);printf("  ***");
        Sleep(200);
        limpiar();
        this->corazones=3;
        this->vidas--;
        PintarCorazones();
        crear();

    }

}

void NAVE::mover(){
    imprimirpuntuacion();
    mostrarvidas();
    PintarCorazones();
    if(kbhit()){
            char tecla = getch();
            gotoxy(x,y);
            limpiar();
            if(tecla==IZQUIERDA && x>3)x--;
            if(tecla==ARRIBA && y>4)y--;
            if(tecla==DERECHA && x+6<77)x++;
            if(tecla==ABAJO && y+3<33)y++;
            crear();
            PintarCorazones();

    }


}



class AST{
    private:
        int x;
        int y;
    public:
        AST(int _x=10,int _y=4){
            this->x=_x;
            this->y=_y;
        }
        int getx(){
            return x;
        }
        int gety(){
            return y;
        }
        void X(int _x){
            this->x=_x;
        }
        void Y(int _y){
            this->y = _y;
        }
        void pintar();
        void mover();
        void choque(class NAVE &elemento);

};

void AST::pintar(){
    gotoxy(x,y);printf("%c",205);


}

void AST::mover(){
    gotoxy(x,y);printf(" ");
    y++;
    if(y>32){
        x = rand()%71+4;
        y = 4;

    }
    pintar();

}

void AST::choque(class NAVE &elemento){
        if(x>=elemento.getx() && x<(elemento.getx()+5) && y>=elemento.gety() && y<=(elemento.gety()+2)){
            elemento.alterar();
            elemento.limpiar();
            elemento.crear();
            elemento.PintarCorazones();
            x = rand()%71+4;
            y = 4;
        }

}

void presionar(){
    bool game_over=false;

    AST asteroide(10,4),asteroide1(16,15),asteroide2(20,20);
    NAVE elemento(30,30);
    BALA bala(elemento.getx()+2,elemento.gety()-1);
    elemento.crear();
    elemento.pintar();
    int a=1;
    list<BALA*>B;
    list<BALA*>::iterator it;
    list<AST*>ast;
    list<AST*>::iterator AIT;
    for(int i=0;i<5;i++){
        ast.push_back(new AST(rand()%71+4,rand()%5 + 5));

    }
    while(!game_over){
        if(kbhit()){
            char a = getch();
            if(a=='v'){
                B.push_back(new BALA(elemento.getx()+2,elemento.gety()-1));
            }
        }
        for(it=B.begin();it!=B.end();it++){
            (*it)->mover();
            if((*it)->fuera()){
                delete (*it);
                it = B.erase(it);
            }
        }
        if(elemento.getvidas()==0){
            gotoxy(30,30);
            printf("GAME OVER!");
            if(kbhit()){
                char c = getch();
                if(c == 'r'){
                    elemento.alterarvidas(3);
                    elemento.alterarcorazones(3);
                    gotoxy(30,30);
                    printf("           ");
                }
                else{
                    game_over = true;
                }
            }
        }
        elemento.mover();
        elemento.resetear();
        for(AIT = ast.begin();AIT!=ast.end();AIT++){
            (*AIT)->mover();
            (*AIT)->choque(elemento);
        }
        for(AIT = ast.begin();AIT!=ast.end();AIT++){
            for(it = B.begin(); it != B.end(); it++){
                if((*AIT)->getx()==(*it)->getx() && ((*AIT)->gety()==(*it)->gety() || (*it)->gety()-1 == (*AIT)->gety())){
                    gotoxy((*AIT)->getx(),(*AIT)->gety());
                    printf(" ");
                    gotoxy((*it)->getx(),(*it)->gety());
                    printf(" ");
                    delete(*it);
                    it = B.erase(it);
                    (*AIT)->X(rand()% 71 +4) ;
                    (*AIT)->Y(4);
                    elemento.insertpuntuacion(a);
                    a*=2;
                }
            }

        }
        Sleep(30);
    }
}
void OcultarCursor(){
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize= 1;
    cci.bVisible = TRUE;
    SetConsoleCursorInfo(hcon,&cci);


}


int main(){
    OcultarCursor();
    presionar();
    return 0;
}
