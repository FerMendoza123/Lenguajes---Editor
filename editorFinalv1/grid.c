/*****************

    Definicion de funciones relacionadas con la malla

******************/

//Bibliotecas
#include "graphics.h"
#include "text.h"
#include "preview.h"
#include "file.h"
#include "screen.h"

void getSettings(GRID*gr,TButton iS)
{
    //se capturará el numero de renglones y columnas
    char rows[4],cols[4];
    //dubujado de texto en blanco
    setcolor(WHITE);
    //estilo de texto, orientacion y tamaño
    settextstyle(2,HORIZ_DIR,5);
    //Por defeto el nombre está en blanco
    gr->name[0]='\0';
    do
    {
        /*
            dibuja la pantalla de mensajes
            se usa bar porque con flood fill no borra las letras del
            que tambien son blancas (como el marco)
        */
        setfillstyle(SOLID_FILL,BLACK);
        bar(iS.x_ini,iS.y_ini,iS.x_ini+iS.width,iS.y_ini+iS.height);
        drawButton(iS);
    //Impresion de instrucciones sobre el boton
        outtextxy(iS.x_ini+15,iS.y_ini+15,"Dame el numero de renglones ");
        outtextxy(iS.x_ini+15,iS.y_ini+45,"(Se permiten un maximo de 26)");
        //captura de texto text.h
        intextxy(iS.x_ini+15,iS.y_ini+75,rows);
        //Borrado de contenido dentro de iS para el siguiente mensaje
        bar(iS.x_ini,iS.y_ini,iS.x_ini+iS.width,iS.y_ini+iS.height);
        drawButton(iS);

        outtextxy(iS.x_ini+15,iS.y_ini+15,"Dame el numero de columnas ");
        outtextxy(iS.x_ini+15,iS.y_ini+45,"(Se permiten un maximo de 24)");
        intextxy(iS.x_ini+15,iS.y_ini+75,cols);


    //Copiado de especificaciones
        gr->row=atoi(rows);
        gr->col=atoi(cols);
        if(gr->row>26||gr->col>24||gr->col==0||gr->row==0)
        {
            setfillstyle(SOLID_FILL,BLACK);
            bar(iS.x_ini,iS.y_ini,iS.x_ini+iS.width,iS.y_ini+iS.height);
            drawButton(iS);
            outtextxy(iS.x_ini+15,iS.y_ini+15,"Las especificaciones no concuerdan con las permitidas");
            outtextxy(iS.x_ini+15,iS.y_ini+45,"Introducelas de nuevo ");
            getch();
        }
    }while(gr->row>26||gr->col>24||gr->col==0||gr->row==0);
}


void initGrid(GRID*gr, int size,int pSize)
{
    int r, c,i;
    //asigna la memoria
    gr->grid=(int**)malloc(sizeof(int*)*gr->row);
    for(i=0;i<gr->row;i++)
    {
        *(gr->grid+i)=(int*)malloc(sizeof(int)*gr->col);
    }
    //Asigna los parametros de tamaño de pixel en preview y el temaño de celda
    gr->cellsize=size;
    gr->pixSize=pSize;

    for(r=0;r<gr->row;r++)
        for(c=0;c<gr->col;c++)
            *(*(gr->grid+r)+c)=WHITE;
}

void drawGrid(GRID gr)
{
    int i,j,xr,yi;
    //cordenada inicial de la malla en y
    yi=(getmaxy()/2)-(gr.cellsize*gr.row/2);
    //color de dibujado de celdas
    setcolor(DARKGRAY);
    for(i=0;i<gr.row;i++)
    {
        //cordenada inicial de la malla en x
        xr=(getmaxx()/2)- (gr.cellsize*gr.col/2);
        //se dibujaran uno por uno los cuadros de la malla
        for(j=0;j<gr.col;j++)
        {
            //se dibuja el siguiente rectangulo
            rectangle(xr,yi,xr+gr.cellsize,yi+gr.cellsize);
            //dibuja con los colores asignados de relleno
            setfillstyle(SOLID_FILL,*(*(gr.grid+i)+j));
            floodfill(xr+1,yi+1,DARKGRAY);
            //se modifica la cordenada para el siguiente cuadro
            xr+=gr.cellsize;
        }
        //se modifica la cordenada para el siguiente renglon de cuadros
        yi+=gr.cellsize;
    }

}

void freeGrid(GRID*gr)
{
    int i;
    //Libera la memoria
    for(i=0;i<gr->col;i++)
        free(*(gr->grid+i));
    free(gr->grid);
}

//oA es para saber si ya hay un archivo abierto, se usa en leeArchivo
int openGrid(TButton iS,GRID*gr,int oA)
{
    char name[30],flag=1;
    bar(iS.x_ini,iS.y_ini,iS.x_ini+iS.width,iS.y_ini+iS.height);
    drawButton(iS);
    outtextxy(iS.x_ini+15,iS.y_ini+15,"Dame el nombre del archivo");
    intextxy(iS.x_ini+15,iS.y_ini+45,name);
    //Si se abrio el archivo no regresa 1 y no entra al if
    if(!leeArchivo(gr,name,oA))
    {
        bar(iS.x_ini,iS.y_ini,iS.x_ini+iS.width,iS.y_ini+iS.height);
        drawButton(iS);
        outtextxy(iS.x_ini+15,iS.y_ini+15,"Error, no se encontro el archivo");
        getch();
        flag=0;
    }
    //flag indica si se pudo abrir
    return flag;
}

void verifyGrid(GRID*gr,int color)
{
    int i,j;
    int yi=(getmaxy()/2)-(gr->cellsize*gr->row/2);
    int xi=(getmaxx()/2)- (gr->cellsize*gr->col/2);
    //si se hace click dentro de la malla
    if(verifyCordinates(xi,yi,gr->cellsize*gr->col,gr->cellsize*gr->row))
    {
        //verifica una por una las celdas
        for(i=0;i<gr->row;i++)
        {
            xi=(getmaxx()/2)- (gr->cellsize*gr->col/2);
            for(j=0;j<gr->col;j++)
            {
                if(verifyCordinates(xi,yi,gr->cellsize,gr->cellsize))
                {
                    //Asigna el color en la matriz y rellena en la malla
                    *(*(gr->grid+i)+j)=color;
                    floodfill(mousex(),mousey(),DARKGRAY);
                    updatePreview(*gr,i,j,color);
                    //Se sale una vez que encontro el color (para hacerlo mas rapido)
                    i=gr->row;
                    j=gr->col;
                }
                xi+=gr->cellsize;
            }
            yi+=gr->cellsize;
        }
    }
}
