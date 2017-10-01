#include <iostream>
#include <SDL/SDL.h>
#include <string>
using namespace std;
#include "GerenatePicture.h"

int main(int argc, char *argv[])
{
freopen("CON", "w", stdout);
freopen("CON", "r", stdin);
freopen("CON", "w", stderr);

    Window w(12*34,12*34);
    w.SetColor(255,255,255);
    Edit editeur;
    editeur.ReadFile();


  while( w.runningState()) //while the user don't close the window
   {

        w.FillRect();
        editeur.Input(w);
        editeur.BlitterEcran(w);
        w.Update();
   }

    //Clean up by the destructor

    return 0;

}
