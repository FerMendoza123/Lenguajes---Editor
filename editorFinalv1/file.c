/*
    Definicion de funciones relacionadas con archivos
*/

//Bibliotecas
#include <stdio.h>
#include<stdlib.h>
#include "file.h"
#include <string.h>


/*
    name es para el nombre del archivo a leer
    Save mode es para saber si el archivo tiene nombre
*/
void guardaArchivo(GRID gr,char name[],int sM)
{
    int i,j;
    FILE *archGrid;

    if(sM)//El save mode 1 es si no tiene nombre
    {
        strcpy(gr.name,name);
    }
    archGrid=fopen(gr.name,"wb");
    /*
        Tendremos que guardar uno a uno los datos porque los previos
        a los apuntadores contienen la informacion de necesaria
        para la reconstruccion de la matriz
    */
    fwrite(&gr.cellsize,sizeof(gr.cellsize),1,archGrid);
    fwrite(&gr.col,sizeof(gr.col),1,archGrid);
    fwrite(gr.name,sizeof(gr.name),1,archGrid);
    fwrite(&gr.pixSize,sizeof(gr.pixSize),1,archGrid);
    fwrite(&gr.row,sizeof(gr.row),1,archGrid);
    //se guardan uno a uno los datos de la matriz
    for(i=0;i<gr.row;i++)
        for(j=0;j<gr.col;j++)
            fwrite((*(gr.grid+i)+j),sizeof(int),1,archGrid);

    fclose(archGrid);
}

/*
    -tiene que leer en la misma maya, por eso es un apuntador
    -name para el nombre
    -oA (open After), si se crea uno nuevo los apuntadores estaran sin asignar
     pero si se abre un proyecto después espacio estará asignado, necesitamos
     reasignar el espacio para adecuarlo a la maya leida
*/
int leeArchivo(GRID*gr,char name[],int oA)
{
    int i,j,read=1;
    FILE *archGrid;
    archGrid=fopen(name,"rb");
    if (archGrid==NULL)
    {
        read=0;
    }
    if(read)
    {
        if(oA)
            freeGrid(gr);

        //Lee uno por uno los datos del dibujo
        fread(&gr->cellsize,sizeof(gr->cellsize),1,archGrid);
        fread(&gr->col,sizeof(gr->col),1,archGrid);
        fread(gr->name,sizeof(gr->name),1,archGrid);
        fread(&gr->pixSize,sizeof(gr->pixSize),1,archGrid);
        fread(&gr->row,sizeof(gr->row),1,archGrid);
        gr->grid=(int**)malloc(sizeof(int*)*gr->row);
        for(i=0;i<gr->row;i++)
        {
            *(gr->grid+i)=(int*)malloc(sizeof(int)*gr->col);
            for(j=0;j<gr->col;j++)
                fread((*(gr->grid+i)+j),sizeof(int),1,archGrid);
        }
    }
    fclose(archGrid);
    return read;
}
