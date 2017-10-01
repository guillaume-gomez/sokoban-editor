#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include <iostream>
#include <fstream>

using namespace std;
#include "GerenatePicture.h"

Edit::Edit()
{
    Case=new Image [145];
    Case[144].changeFond("images/caisse.bmp");
}
Edit::~Edit()
{
    delete [] Case;

}
void Edit::BlitterEcran(const Window& screen)
{
    for(int i=0;i<145;i++)
        {
        Case[i].BlitSurfaces(  screen,Case[i]);
        }
}

void Edit::ReadFile()
{
    int x,y,i;
    char c;
    x=y=0;
    i=1;  // because 0 modulo 12 = 0

    ifile.open("gg.txt");
    if(ifile==NULL)
    {
        cerr << "Erreur de lecture du fichier,"<<endl;
        cerr << "Avez vous supprimer le fichier niveau.txt?"<<endl;
        cerr << "Ce programme devient infonctionnelle sans celui ci"<<endl;
        exit(1);
    }

if(ifile)
{

 while(ifile.get(c) && i<=144)
 {

        switch(c)   //  define the picture
        {          //NB it could be better if a charged only picture of each link of bmp.And after use a copy constructor
        case '0':
        Case[i-1].changeFond("white");  //c'est juste pour le voir sur la console ,il n'y a pas d'image pareil
        break;
        case '1':
        Case[i-1].changeFond("images/mur.bmp");
        break;
        case '2':
        Case[i-1].changeFond("images/caisse.bmp");
        break;
        case '3':
        Case[i-1].changeFond("images/objectif.bmp");
        break;
        case '4':
        Case[i-1].changeFond("images/mario_bas.bmp");
        break;
        case '5':
        Case[i-1].changeFond("images/caisse_ok.bmp"); //a vrai dire sur le fichier du site du zero il y a un 5 !?!
        break;
        }

            Case[i-1].SetX(x); // definie les coordonnés pour l'instance en cours de transformation
            Case[i-1].SetY(y);
  //label pour sauter les lignes plus haut quand la suface est vide
            if(i%12 == 0)// permet de mettre les bonnes coordonnés
            {
                y+=34;
                x=0;
            }
            else
            {
                x+=34;
            }
     i++;
    }
}
ifile.close();
}

void Edit::Input( Window& w)
{
    SDL_WaitEvent(&event);

    switch(event.type)
    {
        case  SDL_QUIT :
           w.Quit();
        break;

        case SDL_MOUSEMOTION:
                Case[144].SetX(event.button.x+10); /* On change les coordonnées du pointeur soit case 145 */
                Case[144].SetY(event.button.y+10) ;
            break;

        case SDL_MOUSEBUTTONDOWN:
                int indice;
            indice=FindCoord(event);
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    if(Case[144].GetName()!="images/mario_bas.bmp" || FindNbMArio()!=false )
                    {
                    Case[indice].changeFond(Case[144].GetName() );
                    }
                }
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {
                   Case[indice].changeFond("white");//bien entendu cette image n'existe pas
                }
            break;

        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {

                case SDLK_KP1:
                Case[144].changeFond("images/mur.bmp");
                break;
                case SDLK_KP2:
                Case[144].changeFond("images/caisse.bmp");
                break;
                case SDLK_KP3:
                Case[144].changeFond("images/caisse_ok.bmp");
                break;
                case SDLK_KP4:
                Case[144].changeFond("images/objectif.bmp");
                break;
                case SDLK_KP5:
                Case[144].changeFond("images/mario_bas.bmp");
                break;
                case SDLK_s:
                if(FindNbMArio()!=false || TestLevel()==false )
                {
                    printf("vous ne pouvez sauvegarder car il n'y aucun mario ou le nombre de caisses et d'objectif et incoherent\n");
                }
                else if(TestCaisseOK()==false)
                {
                    printf("Vous ne pouvez sauvegarder car il y a trop de caisse rouge pour le niveau\n");
                }
                else
                {
                    printf("c'est bon!!!!!!!!!!!!!\n");
                    SaveLevel();
                }
                break;

            }

    }

}

int Edit::FindCoord(SDL_Event event)
{
    int indice=0;
    for(int i=0;i<145;i++)
    {
       if(Case[i].GetX() == event.button.x -(event.button.x%34))
        {
            if(Case[i].GetY() == event.button.y-(event.button.y%34))
            {
                indice=i;
            }
        }
    }
    cout<<"indice:"<<indice<<endl;
    return indice;
}

void Edit::SaveLevel()
{
    int num;
ofstream ofile("LevelCreer.txt", ios::out | ios::app);
if(ofile == NULL)
{
    cout<<"Erreur d'ecriture dans le fichier\nVeuillez relancer l'application!\n";
    exit(1);
}

for(int i=0;i<144;i++)
{ //switch impossible sur un string !!
    if(Case[i].GetName()== "images/mur.bmp" ) {num=1;}
    else if(Case[i].GetName()== "images/caisse.bmp" ) {num=2;}
    else if (Case[i].GetName()== "images/objectif.bmp" ) {num=3;}
    else if (Case[i].GetName()== "images/mario_bas.bmp" ) {num=4;}
    else if(Case[i].GetName()== "images/caisse_ok.bmp" ) {num=5;}
    else{num=0;}
    ofile<<num;  //envoi dans le fichier la valeur;
}
ofile<<"\n";//permet d'avoir un niveau par ligne
ofile.close();
}

bool Edit::FindNbMArio()
{
    for(int i=0;i<144;i++)
    {
        if(Case[i].GetName()== "images/mario_bas.bmp")
        {
            return false;  // si on trouve un mario on ne pourrat pas en ecrire d'autre
        }
    }
    return true;
}

bool Edit::TestLevel()
{
    int cptObjectif=0,cptCaisse=0;
    for(int i=0;i<144;i++)
    {
        if(Case[i].GetName()=="images/objectif.bmp")
        {
            cptObjectif++;
        }
        else if(Case[i].GetName()=="images/caisse.bmp")
        {
            cptCaisse++;
        }
    }
    if(cptCaisse==0 || cptObjectif==0)
    {
        return false;
    }
    else if(cptCaisse != cptObjectif)
    {
        return false;
    }
    else  //par logique on en deduis que le nombre de caisse et le nb d'objetif est superieur a 0 et egaux
    {
        return true;
    }
}
bool Edit::TestCaisseOK()
{
    int cptCaisseOK=0;
    for(int i=0;i<145;i++)
    {
        if(Case[i].GetName()=="images/caisse_ok.bmp")
        {
            cptCaisseOK++;
        }
    }
    return cptCaisseOK < 11;
}
