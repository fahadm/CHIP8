
#include <iostream>
#include <vector>
#include <cstdlib>
#define SFML_STATIC
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#ifdef _WIN32
#include <windows.h>
#endif
#include <bitset>

#define WORD unsigned short int
#define byte unsigned char
using namespace std;

namespace CHIP8
{



sf::RenderWindow App(sf::VideoMode(640, 480), "SFML window");

vector<WORD> Stack(16);
class Register
{
public:
  vector<byte>  V;
  WORD IR;
  WORD I;
  WORD PC;
  byte SP;
  byte DT,ST;
  Register():V(16)
  {
    DT=0;
    ST=0;
    for ( unsigned int i=0 ; i <V.size(); i++)
      V[i] =0;

  }
  void UpdateTimers()
  {

    if (DT >0)
      {
        DT--;
      }
    if (ST >0)
      {
#ifdef _WIN32
        Beep(500,16);
#endif

        ST--;
      }

  }

};
Register Reg;
struct Draw
{
  sf::Image Screen;
  sf::Texture FastScreen;
  sf::Sprite DrawableScreen;
  bool DrawIT;

public:
  Draw()
  {

    App.Clear();
    Screen.Create(64,32);
    for ( int i=0 ; i <64; i++)
      {
        for ( int j=0 ; j <32; j++)
          {
            Screen.SetPixel(i,j,sf::Color(0,0,0));
          }

      }
    FastScreen.LoadFromImage(Screen);
    DrawableScreen.SetTexture(FastScreen);
  }

  void DrawOnScreen(int x,int y,byte Sprite)
  {
    DrawIT=true;


    for ( int i=0 ; i <8; i++)
      {
        if ((Sprite&0x1))
          {
            int dx,dy;
            sf::Color Cl=Screen.GetPixel((x+7-i)%64,y%32);

            if (Cl == sf::Color(255,255,255))
              Reg.V[0xf] =1;


            dy=1;
            if (Cl == sf::Color(255,255,255))
              {
                dx=1;
              }
            else dx=0;
            dx=dx^dy;



            if (dx==1)
              Screen.SetPixel((x+7-i)%64,y%32, sf::Color(255,255,255));
            else
              {
                Screen.SetPixel((x+7-i)%64,y%32, sf::Color(0,0,0));
                DrawIT= false;
              }


          }

        Sprite=Sprite>>1;

      }
    FastScreen.Update(Screen);





  }
  void clear()
  {
    for ( int i=0 ; i <64; i++)
      {
        for ( int j=0 ; j <32; j++)
          {
            Screen.SetPixel(i,j,sf::Color(0,0,0));
          }

      }

  }
  void DrawScreen()
  {

        if (DrawIT)
    App.Draw(DrawableScreen);
    App.Display();
  }
};
Draw DScreen;
struct KeyBoard
{
  sf::Keyboard::Key Keys[16];
public:
  KeyBoard()
  {
    Keys[1]= sf::Keyboard::Num1;
    Keys[2]=sf::Keyboard::Num2;
    Keys[3]=sf::Keyboard::Num3;
    Keys[4]=sf::Keyboard::Q;
    Keys[5]=sf::Keyboard::W;
    Keys[6]=sf::Keyboard::E;
    Keys[7]=sf::Keyboard::A;
    Keys[8]=sf::Keyboard::S;
    Keys[9]=sf::Keyboard::D;
    Keys[0xa]=sf::Keyboard::Z;
    Keys[0xb]=sf::Keyboard::C;
    Keys[0xc]=sf::Keyboard::Num4;
    Keys[0xd]=sf::Keyboard::R;
    Keys[0xe]=sf::Keyboard::F;
    Keys[0xf]=sf::Keyboard::V;
    Keys[0]=sf::Keyboard::X;

  }
  void MapKeys(string file)
  {
    fstream fin;
    fin.open(file.c_str(),ios::in);
    //ToBeImpl

  }
  char getKey(byte m)
  {

    if (sf::Keyboard::IsKeyPressed(Keys[m]))
      {
        return true;
      }
    return false;

  }
  char waitforKeypress()
  {
    for (int i=0;; i++)
      {
        if (i==16) i=0;

        if (sf::Keyboard::IsKeyPressed(Keys[i]))
          {
            return i;
          }

      }

  }

};
KeyBoard Kb;
struct MemoryType
{
  vector<byte> Memory;

  MemoryType():Memory(4096)
  {
    int count=0;
    Memory[count++]=0xF0 ;
    Memory[count++]=0x90 ;
    Memory[count++]=0x90;
    Memory[count++]=0x90;
    Memory[count++]=0xF0;
    Memory[count++]=0x20;
    Memory[count++]=0x60;
    Memory[count++]=0x20;
    Memory[count++]=0x20;
    Memory[count++]=0x70;
    Memory[count++]=0xF0;
    Memory[count++]=0x10;
    Memory[count++]=0xF0;
    Memory[count++]=0x80;
    Memory[count++]=0xF0;
    Memory[count++]=0xF0;
    Memory[count++]=0x10;
    Memory[count++]=0xF0;
    Memory[count++]=0x10;
    Memory[count++]=0xF0;
    Memory[count++]=0x90;
    Memory[count++]=0x90;
    Memory[count++]=0xF0;
    Memory[count++]=0x10;
    Memory[count++]=0x10;
    Memory[count++]=0xF0;
    Memory[count++]=0x80;
    Memory[count++]=0xF0;
    Memory[count++]=0x10;
    Memory[count++]=0xF0;
    Memory[count++]=0xF0;
    Memory[count++]=0x80;
    Memory[count++]=0xF0;
    Memory[count++]=0x90;
    Memory[count++]=0xF0;
    Memory[count++]=0xF0;
    Memory[count++]=0x10;
    Memory[count++]=0x20;
    Memory[count++]=0x40;
    Memory[count++]=0x40;
    Memory[count++]=0xF0;
    Memory[count++]=0x90;
    Memory[count++]=0xF0;
    Memory[count++]=0x90;
    Memory[count++]=0xF0;
    Memory[count++]=0xF0;
    Memory[count++]=0x90;
    Memory[count++]=0xF0;
    Memory[count++]=0x10;
    Memory[count++]=0xF0;
    Memory[count++]=0xF0;
    Memory[count++]=0x90;
    Memory[count++]=0xF0;
    Memory[count++]=0x90;
    Memory[count++]=0x90;
    Memory[count++]=0xE0;
    Memory[count++]=0x90;
    Memory[count++]=0xE0;
    Memory[count++]=0x90;
    Memory[count++]=0xE0;
    Memory[count++]=0xF0;
    Memory[count++]=0x80;
    Memory[count++]=0x80;
    Memory[count++]=0x80;
    Memory[count++]=0xF0;
    Memory[count++]=0xE0;
    Memory[count++]=0x90;
    Memory[count++]=0x90;
    Memory[count++]=0x90;
    Memory[count++]=0xE0;
    Memory[count++]=0xF0;
    Memory[count++]=0x80;
    Memory[count++]=0xF0;
    Memory[count++]=0x80;
    Memory[count++]=0xF0;
    Memory[count++]=0xF0;
    Memory[count++]=0x80;
    Memory[count++]=0xF0;
    Memory[count++]=0x80;
    Memory[count++]=0x80;
    Memory[count++]=0xF0;
    Memory[count++]=0x80;
    Memory[count++]=0xF0;
    Memory[count++]=0x80;
    Memory[count++]=0x80;

  }

};
MemoryType Mem;

class Decode
{
#define X ((tempholder&0x0F00)>>8)
#define Y ((tempholder&0x00F0)>>4)
public:
  void DecodeOpCode(unsigned short int opcode)
  {
    short int tempholder =0;
    short int tem=0;
    tempholder = (opcode&0x0FFF);
    switch(opcode>>12)
      {
      case 0:

        switch (tempholder)
          {
          case 0x0E0:
            DScreen.clear();
            DScreen.DrawScreen();
            break;
          case 0x0EE:
            Reg.PC = Stack[Reg.SP];
            Reg.SP--;

            break;
          }
        break;
      case 1:
        Reg.PC = tempholder;
        break;
      case 2:
        Reg.SP++;
        Stack[Reg.SP] = Reg.PC;
        Reg.PC = tempholder;
        break;
      case 3:
        if (Reg.V[X] == (tempholder&0x00FF))
          Reg.PC+=2;
        break;
      case 4:
        if (Reg.V[X] != (tempholder&0x00FF))
          Reg.PC+=2;
        break;
      case 5:
        if (Reg.V[X] == Reg.V[Y])
          Reg.PC+=2;

        break;
      case 6:
        Reg.V[X] = (tempholder&0x00FF);
        break;
      case 7:
        Reg.V[X] += (tempholder&0x00FF);
        break;
      case 8:
        switch (tempholder&0xf)
          {
          case 0 :
            Reg.V[X] = Reg.V[Y];
            break;
          case 1:
            Reg.V[X] |= Reg.V[Y];
            break;
          case 2:
            Reg.V[X] &= Reg.V[Y];
            break;
          case 3:
            Reg.V[X] ^= Reg.V[Y];
            break;
          case 4:

            tem=  Reg.V[X]  + Reg.V[Y];
            if (tem > 255) Reg.V[0xf] =1;
            else Reg.V[0xf] =0;
            Reg.V[X] = (tem&0xff );
            break;
          case 5:
            if (Reg.V[X] > Reg.V[Y]) Reg.V[0xF] =1;
            else Reg.V[0xf] = 0;
            Reg.V[X] = Reg.V[X] - Reg.V[Y];
            break;
          case 6:
            Reg.V[0xf] = Reg.V[X]&0x1;
            Reg.V[X]=Reg.V[X]>>1;
            break;
          case 7:
            if (Reg.V[Y] > Reg.V[X]) Reg.V[0xF] =1;
            else Reg.V[0xf] = 0;
            Reg.V[X] = Reg.V[Y] - Reg.V[X];
            break;
          case 0xE:
            Reg.V[0xf] =( (Reg.V[X]&0x80) == 0x80?1:0 );
            Reg.V[X]=Reg.V[X]<<1;
            break;
          }

        break;
      case 9:
        if (Reg.V[X] != Reg.V[Y])
          Reg.PC+=2;
        break;
      case 0xA:
        Reg.I = tempholder;
        break;
      case 0xB:
        Reg.PC = tempholder +Reg.V[0];
        break;
      case 0xC:
        srand ( time(NULL) );
        Reg.V[X] = ((rand()%255)&(tempholder&0x00FF));

        break;
      case 0xD:
        ///DRAW
        Reg.V[0xf] = 0;

        for (int i=0 ; i < (tempholder&0xF); i++)
          DScreen.DrawOnScreen(Reg.V[X],Reg.V[Y]+i,Mem.Memory[Reg.I+i]);
        DScreen.DrawScreen();

        break;
      case 0xE:
        switch((tempholder&0xff))
          {
          case 0x9E:   ///

            if (Kb.getKey(Reg.V[X]))
              Reg.PC+=2;

            break;
          case 0xA1:

            if (!Kb.getKey(Reg.V[X]))
              Reg.PC+=2;


            break;
          }
        break;
      case 0xF:
        switch((tempholder&0xff))
          {
          case 7:
            Reg.V[X]=Reg.DT;
            break;
          case 0xA:
            Reg.V[X] = Kb.waitforKeypress();
            break;
          case 0x15:
            Reg.DT = Reg.V[X];
            break;
          case 0x18:
            Reg.ST = Reg.V[X];
            break;
          case 0x1E:
            Reg.I += Reg.V[X];
            break;
          case 0x29:
            Reg.I = Reg.V[X]*5;
            break;
          case 0x33:
            Mem.Memory[Reg.I]= Reg.V[X]/100;
            Mem.Memory[Reg.I+1]= Reg.V[X]/10;
            Mem.Memory[Reg.I+2]= Reg.V[X];
          case 0x55:
            for (int i=0 ; i < X ; i++)
              {
                Mem.Memory[Reg.I + i]=Reg.V[i];
              }
            break;
          case 0x65:
            for (int i=0 ; i < X ; i++)
              {
                Reg.V[i]=Mem.Memory[Reg.I + i];
              }

            break;



          }
        break;
      default:
        cout<<"The Program has encountered an illegal instruction";
        throw 1773641;

      }
  }

};
class FileReader
{
  ifstream fin;

public:
  void open(string name)
  {
    fin.open(name.c_str(),ios::binary);
    if (!fin)
      throw 1337;
    fin.seekg (0, ios::end);
    int length = fin.tellg();
    fin.seekg (0, ios::beg);

    fin.read((char *)&Mem.Memory[0x200],length);
    for ( int i=0 ; i <length; i+=2)
      cout<<"PC "<<i<<"  "<<hex<<(unsigned short)Mem.Memory[0x200+i]<<(unsigned short)Mem.Memory[0x200+i+1]<<endl;


  }

};

int run(string file)
{

  FileReader File;
  App.SetView(sf::View(sf::FloatRect( 0,0,64,32)));
  File.open(file);
  Decode D;
  Reg.PC=0x200;
  WORD Exec=0;
  sf::Clock C1;
  App.SetFramerateLimit(60);
  while (1)
    {
      int time = C1.GetElapsedTime();

      Exec = (Mem.Memory[Reg.PC]<<8)|Mem.Memory[Reg.PC+1];

      cout<<"Executing"<<hex<<Exec<<"   PC"<<Reg.PC<<endl;
      if (Exec == 0) break;
      Reg.PC+=2;
      D.DecodeOpCode(Exec);

      if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Escape) ) break;


      if (time >=16) // half baked 60 hz timer
        {
          Reg.UpdateTimers();
          C1.Reset();

        }




    }
  return 0;
}

};
int main(int argc,char * argv[])
{
  try
    {


      if ( argc > 1)
        CHIP8::run(argv[1]);
      else
        CHIP8::run("Games/Pong");
    }
    catch ( int error)
    {
        switch ( error)
        {
            case 1337:
            cerr<<"File Not Found";
            break;
            case 1773641:
            cerr<<"Illegal Instruction Encountered";
            break;

        }
    }
  return 0;
}
