#ifndef GERENATEPICTURE_H_INCLUDED
#define GERENATEPICTURE_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Window
{
  private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int SCREEN_BPP;
    SDL_Surface *screen;
    bool running;
    int green,red,blue;
  public:
  friend class Image;

  Window(int _SCREEN_WIDTH,int _SCREEN_HEIGHT);
Window();
  void Load();
  void Init();
  void Draw();
  void Quit();
  void Update();
  bool runningState();
  ~Window();
  SDL_Surface* accesScreen();
  void SetColor(int _red,int _green,int _blue);
 void  FillRect();


};

class Image
{
    private:
    string name;
    SDL_Surface *background;
    SDL_Rect positionFond;
    public:
    Image();
    Image(std::string filename);
    ~Image();
    SDL_Surface* accesBackground();
    int   GetX();
    int   GetY();
    void SetY(int _Y);
    void SetX(int _X);
    void BlitSurfaces(const Window & g, Image& i);
    void changeFond(std::string filename);
    string GetName()const;

};


class Edit
{
   private:
   Image *Case;
    SDL_Event event;
   std::ifstream ifile;
   std::ifstream ofile;
   public:
   Edit();
   ~Edit();
   void ReadFile() ;
   void BlitterEcran(const Window& screen);
  void  Input( Window& w);
 int  FindCoord(SDL_Event event);
 void SaveLevel();
 bool FindNbMArio();
 bool TestLevel();
bool  TestCaisseOK();


};

#endif // GERENATEPICTURE_H_INCLUDED

