/****************

    Definicion de funciones relacionadas con la previsualizacion

*****************/

#include "graphics.h"
#include "preview.h"

void drawSprite(GRID gr)
{
    int r,c;
    int xi,yi;

    xi=(getmaxx()/2)+(gr.cellsize*gr.col/2);
    xi+=40;//Esquina sup izquierda de la ventana de preview a partir de la malla

    yi=(getmaxy()/2)-(gr.cellsize*gr.row/2);
    for(r=0;r<gr.row;r++)
        for(c=0;c<gr.col;c++)
        {
            //dibuja los cuadros de preview con el color asignado
            setfillstyle(SOLID_FILL,(*(*(gr.grid+r)+c)));
            bar(xi+c*gr.pixSize,yi+r*gr.pixSize,xi+(c+1)*gr.pixSize,yi+(r+1)*gr.pixSize);
        }

}


void updatePreview(GRID gr,int r, int c,int color)
{
    int xi,yi;

    xi=(getmaxx()/2)+(gr.cellsize*gr.col/2);
    xi+=40; //Esquina sup izquierda de la ventana de preview

    yi=(getmaxy()/2)-(gr.cellsize*gr.row/2);

    setcolor(color);
    setfillstyle(SOLID_FILL,*(*(gr.grid+r)+c));
    bar(xi+c*gr.pixSize,yi+r*gr.pixSize,xi+(c+1)*gr.pixSize,yi+(r+1)*gr.pixSize);
}

void drawPreviewContour(GRID gr)
{
    int xi,yi;

    xi=(getmaxx()/2)+(gr.cellsize*gr.col/2);
    xi+=35;  //Esquina superior del contorno de preview (separado 5 pixeles del sprite)
    yi=(getmaxy()/2)-(gr.cellsize*gr.row/2)-5;
    //Rectangulo con bordes separados 5 pixeles de la representacion del sprite
    setcolor(WHITE);
    rectangle(xi,yi,xi+(gr.col*gr.pixSize)+10,yi+(gr.row*gr.pixSize)+10);
}
