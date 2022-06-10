/********************

    Definicion de funciones relacionadas con los colores

*********************/

//Bibliotecas
#include"colors.h"
#include"graphics.h"


//Recibe el tamaño de las celdas de colores
void drawColors(int c_Size)
{
    int i;
    //se dibujan arriba del borde inferior
    int yi=getmaxy()-c_Size;
    //A partir de la mitad de la pantalla
    int xi=(getmaxx()/2)-(16*c_Size/2);
    setcolor(WHITE);
    for(i=0;i<16;i++)
    {
        //el color de los bordes de la malla no se pinta porque despues no se podría quitar
        if(i!=DARKGRAY)
        {
            setfillstyle(SOLID_FILL,i);
            rectangle(xi,yi,xi+c_Size,yi+c_Size);
            floodfill(xi+1,yi+1,WHITE);
            xi+=c_Size;
        }
    }
}
