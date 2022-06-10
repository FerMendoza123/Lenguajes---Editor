/****************************

    Declaracion de funciones relacionadas con botones

***************************/

//if necesario para evitar redefinicion
#ifndef _BUTTON
#define _BUTTON 1
//Estructura
typedef struct
{
    int x_ini,y_ini,height,width;
    char label[20];
}TButton;

#endif

//Funnciones
void createButton(TButton *bt,int x, int y,int w,int h,char label[20]);
void drawButton(TButton bt);
int verifyCordinates (int xi,int yi,int xf,int yf);
void createButtons(TButton*bN,TButton*bO,TButton*bC,TButton*bS,TButton*bN2,TButton*bC2,TButton*bSA,TButton*bO2,TButton*iS);





