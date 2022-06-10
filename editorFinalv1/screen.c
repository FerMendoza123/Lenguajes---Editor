/**************

    Definicion de funciones relacionadas con la pantalla

*************/

//Bibliotecas
#include "boton.h"
#include "preview.h"
#include "graphics.h"
#include "text.h"
#include "file.h"
#include "colors.h"

//Aqui dibujamos la pantalla con "nuevo" "abrir" y "salir"
//Para eso necesitamos la biblioteca para los botones
void drawMainScreen (TButton bN,TButton bO,TButton bC)

{
    //Dibuja todos los botones (boton.h)
    drawButton(bN);
    drawButton(bO);
    drawButton(bC);
    //Dinuja el nombre de editor
    settextstyle(3,HORIZ_DIR,4);
    outtextxy(getmaxx()/3,getmaxy()/4,"Editor.C");
}

void drawDrawScreen(TButton bS,TButton bN2,TButton bC2,TButton bSA,TButton bO2,GRID gr)
{
    //Dibuja la malla (grid.h)
    drawGrid(gr);
    //La previsualización (preview.h)
    drawSprite(gr);
    drawPreviewContour(gr);

    //Dibuja todos los botones
    drawButton(bS);
    drawButton(bN2);
    drawButton(bC2);
    drawButton(bSA);
    drawButton(bO2);

    //Dibuja la barra de colores
    drawColors(getmaxy()/16);
    //Titulo del dibujo
    outtextxy(getmaxx()/3,0,gr.name);
}


int useMainScreen(TButton bN,TButton bO,TButton bC,TButton iS,GRID*gr)
{
    /**********Solo se tomará una decision, se usa o no se usa la malla**********/
    /*
        flag determina que decisión se a tomado y dflag si se ha terminado
        con la toma de decision, se habrá terminado solo si se introducen
        correctamente los parametros o si se decide salir, aunque se pensó
        suponer que entrará

        edo es para saber si se necesita redibujar la pantalla, se usa en caso de no
        haber introducido de manera correcta los parametros
    */
    int edo=0,flag=1,dflag=1;
    while (dflag)
    {
        //Rebujado de pantalla si no se han introducido correctamente los parametros
        if(edo)
        {
            cleardevice();
            drawMainScreen(bN,bO,bC);
            edo=0;
        }

        //si se hace click sobre el boton nuevo, veifyCordinates verifica si el cursor está sobre un boton (boton.h)
        if(ismouseclick(WM_LBUTTONDOWN)&&
           verifyCordinates(bN.x_ini, bN.y_ini, bN.width, bN.height) )
        {
            //Se piden las caracteristicas de la malla (grid.h)
            getSettings(gr,iS);
            //Se inicializa la malla (grid.h)
            initGrid(gr,20,5);
            //se tomó correctamente la decisión (getSettings solo sale cuando se introdujeron los parametros adecuados)
            dflag=0;
        }

        if(ismouseclick(WM_LBUTTONDOWN)&&
           verifyCordinates(bO.x_ini, bO.y_ini, bO.width, bO.height) )
        {
            //Funcion para abrir la malla (grid.h)
            if(openGrid(iS,gr,0))
            {
                //si se pudo abrir se sale
                dflag=0;
            }
            clearmouseclick(WM_LBUTTONDOWN);
            edo=1;
        }

        if(ismouseclick(WM_LBUTTONDOWN)&&
           verifyCordinates(bC.x_ini, bC.y_ini, bC.width, bC.height) )
           {
                flag=0;
                dflag=0;
           }
    }
    clearmouseclick(WM_LBUTTONDOWN);
    return flag;//se regresa la decision tomada
}


//Recibe todos los botones que va a usar la malla, el tamaño de el boton color y la pantalla de informacion
void useDrawScreen(GRID *gr,TButton bS,TButton bN2,TButton bC2,TButton bSA,TButton bO2,int c_Size,TButton iS)
{
    /*
        se inicia con el color de fondo de la maya
        la pantalla no se necesita dibujar de nuevo (aun), el estado es 0
        flag = 1 para entrar al ciclo
    */
    int color=WHITE,edoScreen=0,flag=1;
    //Cordenadas de la barra de colores
    int yi2=getmaxy()-c_Size;
    int xi2=(getmaxx()/2)-(8*c_Size);
    char name[30];

    setfillstyle(SOLID_FILL,color);

    while(flag)
    {
        while(ismouseclick(WM_LBUTTONDOWN))
        {
            /**********verifyGrid********/
            //verifica si se dio click dentro de la malla (grid.h)
            verifyGrid(gr,color);
            //verifica si se clickeo dentro de la barra de colores
            if(verifyCordinates(xi2,yi2,(15*c_Size),c_Size))
            {
                //Recupera el color del cuado en el que está el cursor
                color=getpixel(mousex(),mousey());
                //Lo asigna al color actual
                setfillstyle(SOLID_FILL,color);
            }
            //Verifica si se clickeo dentro de el boton de guardar como
            if(verifyCordinates(bSA.x_ini,bSA.y_ini,bSA.width,bSA.height))
            {
                //Pregunta el nombre del archivo
                setfillstyle(SOLID_FILL,BLACK);
                bar(iS.x_ini,iS.y_ini,iS.x_ini+iS.width,iS.y_ini+iS.height);
                drawButton(iS);
                outtextxy(iS.x_ini+15,iS.y_ini+15,"Dame el nombre del archivo");
                intextxy(iS.x_ini+15, iS.y_ini+45,name);
                //guarda el archivo file.h
                guardaArchivo(*gr,name,1);
                edoScreen=1;
            }
            //Verifica en guardar
            if(verifyCordinates(bS.x_ini,bS.y_ini,bS.width,bS.height))
            {
                //Si es la primera vez no tendrá titulo
                if(gr->name[0]=='\0')
                {
                    setfillstyle(SOLID_FILL,BLACK);
                    bar(iS.x_ini,iS.y_ini,iS.x_ini+iS.width,iS.y_ini+iS.height);
                    drawButton(iS);
                    outtextxy(iS.x_ini+15,iS.y_ini+15,"Dame el nombre del archivo");
                    intextxy(iS.x_ini+15, iS.y_ini+45,gr->name);
                    guardaArchivo(*gr,gr->name,1);
                    edoScreen=1;
                }
                else
                {
                    guardaArchivo(*gr,"",0);
                }
            }
            //Verifica en nuevo
            if(verifyCordinates(bN2.x_ini,bN2.y_ini,bN2.width,bN2.height))
            {
                //Pregunta si se desea salir text.h
                if(verifyExit(iS,gr))
                {
                    getSettings(gr,iS);
                    initGrid(gr,20,5);
                }
                edoScreen=1;
            }
            //Verifica en abrir
            if(verifyCordinates(bO2.x_ini,bO2.y_ini,bO2.width,bO2.height))
            {
                //Pregunta si quiere salir
                if(verifyExit(iS,gr))
                {
                    //se manda a abrir
                    openGrid(iS,gr,1);
                }
                edoScreen=1;
            }
            if(verifyCordinates(bC2.x_ini,bC2.y_ini,bC2.width,bC2.height))
            {
                //Pregunta si se quiere salir
                if(verifyExit(iS,gr))
                    //Fin del ciclo
                    flag=0;
                else
                //si no se reimprime la pantalla
                    edoScreen=1;
            }
            if(edoScreen)
            {
                //Se borra todo y se reimprime
                cleardevice();
                drawDrawScreen(bS,bN2,bC2,bSA,bO2,*gr);
                edoScreen=0;
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}
