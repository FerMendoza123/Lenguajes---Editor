/*************
    Este es un intento de version final para el editor de sprites
    Aquí se implementan las librerias .h para las mayas botones y demas necesario
*************/



/*Bibliotecas
    Las otras se comunican por medio de screen.h*/
#include "graphics.h"
#include "screen.h"


//Funcion principal
int main()
{
    int dFlag;//Bandera para la desicion
    //Creamos los botones (estructura en boton.h) para la pantalla principal y de dibujo (screen.h)
    TButton bNew,bOpen,bClose;
    //infoScreen no es un boton pero tiene casi las mismas caracteristicas
    TButton bSave,bNew2,bClose2,bOpen2,bSaveAs,infoScreen;
    //Creamos la maya (estructura en grid.h)
    GRID gr;

    //iniciamos la ventana (graphics.h)
    initwindow(1000,700);

    //Funcion para asignar las caracteristicas (boton.h)
    createButtons(&bNew,&bOpen,&bClose,&bSave,&bNew2,&bClose2,&bSaveAs,&bOpen2,&infoScreen);

    //Dibujamos la pantalla de inicio (screen.h)
    drawMainScreen(bNew,bOpen,bClose);
    //Funcion para utilizar la pantalla de inicio (screen.h), regresa 1 si se va a utilizar y 0 si no
    dFlag=useMainScreen(bNew,bOpen,bClose,infoScreen,&gr);

    //Despues limpiamos la pantalla
    cleardevice();

    if(dFlag)
    {
        //Dibujamos la pantalla de dibujo (screen.h)
        drawDrawScreen(bSave,bNew2,bClose2,bSaveAs,bOpen2,gr);
        //Funcionpara utilizar la pantalla de dibujo
        useDrawScreen(&gr,bSave,bNew2,bClose2,bSaveAs,bOpen2,getmaxy()/16,infoScreen);
    }
    //Fin del programa
    closegraph();
    return 0;
}
