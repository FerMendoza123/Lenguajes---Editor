/**********************

    Declaracion de funciones relacionadas con la malla

************************/

//Bibliotecas
#include "boton.h"

//if necesario para evitar la redeclaracion
#ifndef _GRID
#define _GRID 5
//Estructura
typedef struct
{
    char name[25];
    int row,col;
    int cellsize;
    int pixSize;
    int**grid;
}GRID;
#endif

//Funciones
void getSettings(GRID*gr,TButton iS);
void initGrid(GRID*gr, int size,int pSize);
void freeGrid(GRID*gr);
void drawGrid(GRID gr);
int openGrid(TButton iS,GRID*gr,int oA);
void verifyGrid(GRID*gr,int color);

