#ifndef CRAZYBALL_H
#define CRAZYBALL_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <tpl_dynArray.H>
#include <string.h>
#include <random>

//#include "balon.h"

using namespace sf;



class balon
{
    Texture t_balon;
    Sprite s_balon;
    Vector2f velocidad;
    Vector2f aceleracion;
    Vector2f pos;



  public:
    balon(Vector2f vel){
      t_balon.loadFromFile("Imagenes/balon_36x36.png");

      s_balon.setTexture(t_balon);

      s_balon.setPosition(800,130);

      //pelota.setPosition(800,130);
      velocidad = vel;

      //pelota.setRadius(15);
      aceleracion.x = 0;
      aceleracion.y = 0.10;

      s_balon.setOrigin(s_balon.getTexture()->getSize().x/2,
                        s_balon.getTexture()->getSize().y/2);

    };
    void fuer(Vector2f vel){
      //pelota.setPosition(800,130);
      velocidad = -vel;

      //pelota.setRadius(15);
      aceleracion.x = 0;
      aceleracion.y = 0.10;

      s_balon.setOrigin(s_balon.getTexture()->getSize().x/2,
                        s_balon.getTexture()->getSize().y/2);

    };
    void actualizar(){

        pos.y = s_balon.getPosition().y;
        pos.x = s_balon.getPosition().x;

        velocidad.x += aceleracion.x * 1,2;
        velocidad.y += aceleracion.y * 1,2;

        s_balon.setPosition(pos.x + velocidad.x, pos.y + velocidad.y);
        if (s_balon.getPosition().y > 522 || s_balon.getPosition().y < 0)
        {
              velocidad.y = -(velocidad.y/1.2);
              //s_balon.rotate(-5);
        }
        if (s_balon.getPosition().x > 885 || s_balon.getPosition().x < 0 )
        {
              velocidad.x = -velocidad.x;
              //s_balon.rotate(5);
        }

    };

    Sprite get_sprite(){ return s_balon; };


};

class CrazyBall
{
    private:

      bool dirr{false};

      RenderWindow window;
      Event evee, evento_main;

      //Variables del sprite
      Texture t_jugador, t_fondo, t_menu, t_obs;
      Sprite s_jugador, s_fond, s_ball, s_menu, s_obs;

      //Variables de texto
      Font fuente1;
      Text txt_vida, num_vidas, txt_time, num_time, txt_menu,txt_pun, num_pun;

      //variable de movimiento
      Vector2f movimiento, mov2;
      float a_move = 13.f;
      Vector2i frame_actual;
      Vector2i div_sprite;
      CircleShape balltest,balltest1,balltest2, balltest3;
//--------------------------------
int kk, nlife ;

bool jump;
bool band1;
Vector2f ac, vel, pos1;
float acx=0, acy=0.1;
float timer;
Vector2f vel1, vel2, vel3, pos3, pos2;
int puntuacion;
//-----------------------------------

      //variables de sonido
      SoundBuffer buffer;
      Sound sonido;

      //balon_36x36
      DynList<balon> Balones;
      balon * balon1;
      balon * balon2;
      balon * balon3;
      balon * balon4;
      balon * balon5;

      //Dynlist<balon> lista_ba;
      Vector2i tiro_balon;
      int nb;

      //variables de prueba

      //tiempo
      Clock reloj1;
      Time tiempo;
      int tiempo2, tiempo3, tiempo4, tiempo5, tiempo1;
      bool liberar3{true},liberar4{true},liberar5{true};
      int fps;

      bool isPlay{true}, liberar{true}, caminar{false}, patear{false}, atras{false};
      bool UP{false},DOWN{false},LEFT{false},RIGHT{false}, liberar2{true};



      void inic();

      void eventos();
      void update();
      void render();

      void cleared();
      void obtener_frame(Sprite &jug, Vector2i n_frame);

    public:
      CrazyBall();
      void run();


};

#endif
