/****************************

    Definicion de funciones relacionadas con botones

***************************/

//Bibliotecas
#include"graphics.h"
#include"boton.h"


//Funciones
void drawButton(TButton bt)
{

    setcolor(WHITE); //Pone el color de dibujo en blanco
    setfillstyle(SOLID_FILL,BLACK);  //color negro y tipo de llenado solido
    rectangle(bt.x_ini,bt.y_ini,bt.x_ini+bt.width,bt.y_ini+bt.height);   //Dibuja rectangulo
    floodfill(bt.x_ini+1,bt.y_ini+1,WHITE);  //Rellena tomando como referencia un punto dentro del rectangulo
    //Dibuja la etiqueta
    settextstyle(3,HORIZ_DIR,1);
    outtextxy(bt.x_ini+15,bt.y_ini+15,bt.label);
}

//Recibe el boton, el punto de inicio (x,y), ancho (w) alto (h) y el texto
void createButton(TButton *bt,int x, int y,int w,int h,char label[20])
{
    //Asigna las caracteriscticas recibidas en los parametros
    bt->x_ini=x;
    bt->y_ini=y;
    bt->width=w;
    bt->height=h;
    strcpy(bt->label,label);
}


/*
Esta funcion verifica las cordenadas del puntero para un rectangulo
La uso para saber si está sobre un boton
solo se le pasa el punto inicial (xi,yi) y las dimensiones
no el punto final
*/
int verifyCordinates (int xi,int yi,int w,int h)
{

    if( (mousex()>xi) && (mousex() < xi+w)
       && (mousey()>yi) && (mousey() < yi+h) )
    {
        return 1;
    }
    return 0;
}

void createButtons(TButton*bN,TButton*bO,TButton*bC,TButton*bS,TButton*bN2,TButton*bC2,TButton*bSA,TButton*bO2,TButton*iS)
{
    /*
    x es el tamaño que quiero de separacion entre los botones
    tres espacios para los botones y 4 para los espacios
    Entre ellos y el borde en la pantalla

    x2 será para el comienzo de dibujado de un boton
    se aumenta el tamaño del boton (w) mas el espacio
    entre ese y el siguiente (x)

    */
    int x=getmaxx()/7,x2=0,y=getmaxy()/2,w=getmaxx()/7;
    int hbd=getmaxy()/12;//Height button draw es la altura para los botones de la pantalla de dibujo
    int wbd=getmaxx()/6;//Width button draw, ancho para los botones de la pantalla de dibujo
    x2+=x;//espacion enctre el borde y el primer boton
    createButton(bN,x2,y,w,getmaxy()/6,"Nuevo");
    x2+=x+w;
    createButton(bO,x2,y,w,getmaxy()/6,"Abrir");
    x2+=x+w;
    createButton(bC,x2,y,w,getmaxy()/6,"Salir");

    //Botones segunda pantalla
    //hbd solo se multiplica porque los botones no estan separados, estan uno debajo del otro
    createButton(bN2,0,0,wbd,hbd,"Nuevo");
    createButton(bO2,0,hbd,wbd,hbd,"Abrir");
    createButton(bS,0,hbd*2,wbd,hbd,"Guardar");
    createButton(bSA,0,hbd*3,wbd,hbd,"Guardar como");
    createButton(bC2,0,hbd*4,wbd,hbd,"Salir");
    //Esta es la pantalla de mensajes, tiene las mismas caracteristicas de un boton salvo que no tiene texto
    createButton(iS,(getmaxx()/2)-(getmaxx()/4),(getmaxy()/2)-(getmaxy()/4),getmaxx()/2,getmaxy()/2,"");
}

