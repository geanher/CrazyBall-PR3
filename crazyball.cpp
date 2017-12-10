#include <iostream>
#include "CrazyBall.h"


using namespace sf;
using namespace std;

const int TAM_HOR = 900, TAM_VER = 600, radioo = 15;

CrazyBall::CrazyBall():window{VideoMode{TAM_HOR,TAM_VER},"CrazyBall"}
{

}

void CrazyBall::inic()
{



  fps = 60;
  window.setPosition(Vector2i(100,100));
  //para que el juego corra a 60 frame en todas las pcs
  window.setFramerateLimit(fps);
  //al dejar apretado un boton no se repita
  window.setKeyRepeatEnabled(true);
  //Para que parpadee lo menos posible
  window.setVerticalSyncEnabled(true);

//-----------------------------------------------------------
//CARGA DE IMAGENES

  //Comprobar si cargo correctamente la imagen
    if (!t_fondo.loadFromFile("Imagenes/fondo_900x600.png") ||
        !t_jugador.loadFromFile("Imagenes/ani_jugador.png") ||
      !t_menu.loadFromFile("Imagenes/fondo1_900x600.png")   ||
      !t_obs.loadFromFile("Imagenes/obstaculo.png")   )
    {
      // error...
      //return 1;
      std::cout << "error" << '\n';
    }
    //t_obs.setScale(-1,-1);
    s_menu.setTexture(t_menu);
    s_jugador.setTexture(t_jugador);
    s_fond.setTexture(t_fondo);
    s_obs.setTexture(t_obs);
    //s_ball.setTexture(t_balon);

    frame_actual.x = 0;
    frame_actual.y = 0;
    div_sprite.x = 5;
    div_sprite.y = 4;
    nlife= 150;
    s_jugador.setPosition(100,415);

    obtener_frame(s_jugador, frame_actual);

    s_obs.setPosition(400, 322);
    //circulo.setPosition(300,300);
    //balon1();
//-----------------------------------------------------------
 balltest1.setRadius(15);
 balltest1.setPosition(800,100);

 balltest2.setRadius(15);
 balltest2.setPosition(600,100);

 balltest3.setRadius(10);
 balltest3.setPosition(650, 100);

ac.x=0;
ac.y=0.10;
vel1.x = -2;
vel1.y = -3;
vel2.x = -4;
vel2.y = -1;
vel3.x = -3;
vel3.y = -4;



//-----------------------------------------------------

//CARGA de Fuentes

    fuente1.loadFromFile("Fuentes/seguili.ttf");
    //variables de texto
    txt_vida.setFont(fuente1);
    num_vidas.setFont(fuente1);
    txt_time.setFont(fuente1);
    num_time.setFont(fuente1);

    txt_menu.setFont(fuente1);
    txt_menu.setString("START");
    txt_menu.setPosition(40,100);

    txt_pun.setFont(fuente1);
    txt_pun.setString("Puntuacion:");
    txt_pun.setPosition(50,15);
    num_pun.setPosition(199,15);
    num_pun.setFont(fuente1);

    txt_vida.setString("Life:");
    txt_time.setString("Time:");

    txt_time.setPosition(500,15);
    txt_vida.setPosition(250,15);
    num_vidas.setPosition(300,15);
    num_time.setPosition(600,15);
    txt_time.setColor(Color::White);
    txt_vida.setColor(Color::White);
    num_time.setColor(Color::White);
    num_vidas.setColor(Color::White);
//-----------------------------------------------------------
//CARGA de Sonido

    //buffer = new SoundBuffer;
    //sonido = new Sound;
    if (!buffer.loadFromFile("Sonidos/pelota.ogg"))
    {
      cout << "No Se Pudo Cargar El Sonido" << '\n';
    }
    sonido.setBuffer(buffer);


    //return 0;
    //---------------------------------------------------------
      //Inicializar variables aleatorias
      //numeros aleatorios
      random_device rd;
      mt19937 gen(rd());
      uniform_int_distribution<> disf(1, 8);
      nb = 0;
      tiempo2 = 0;

    //inicializar balones

    /*for (size_t i = 0; i < 20; i++) {
      balon * balon2 = new balon({-2,-3});
      Balones.append(balon2);
    }*/
}

void CrazyBall::obtener_frame(Sprite &jug, Vector2i n_frame)
{
  //coordenadas iniciales desde donde creara el rectangulo
  // imagen ancho = 494 / (3frame ), altura = 707 / (4frame)
  // inicio de coordenadas

  int coord_x = n_frame.x * ((jug.getTexture()->getSize().x)/ 5);
  int coord_y = n_frame.y * ((jug.getTexture()->getSize().y)/ 4);
  int coord_x_f = (jug.getTexture()->getSize().x)/ 5;
  int coord_y_f = (jug.getTexture()->getSize().y)/ 4;
  // fin de coordenadas

  IntRect posicion(coord_x,coord_y,coord_x_f, coord_y_f);
  jug.setTextureRect(posicion);
}

void CrazyBall::eventos()
{
    while (window.pollEvent(evee))
    {
      if (evee.type == Event::Closed)
          isPlay = false;



      if (evee.type == Event::KeyReleased && evee.key.code == Keyboard::W)
          jump = true;

      if (evee.type == Event::KeyReleased && evee.key.code == Keyboard::Space)
          patear = true;

      //----Caminar hacia adelante-----------------
      if (evee.type == Event::KeyPressed && evee.key.code == Keyboard::D)
          caminar = true;
      if (evee.type == Event::KeyReleased && evee.key.code == Keyboard::D)
          caminar = false;

      //----Caminar hacia atras-----------------
      if (evee.type == Event::KeyPressed && evee.key.code == Keyboard::A)
          atras = true;
      if (evee.type == Event::KeyReleased && evee.key.code == Keyboard::A)
          atras = false;


    }
}



void CrazyBall::update()
{

  //---------------------------------------------------------

  ac.x = acx;
  ac.y = acy;

  pos1.y = balltest1.getPosition().y;
  pos1.x = balltest1.getPosition().x;

  vel1.x += ac.x * 1.8;
  vel1.y += ac.y * 1,1;



  balltest1.setPosition(pos1.x + vel1.x, pos1.y + vel1.y);
  if (balltest1.getPosition().y >= 522 || balltest1.getPosition().y <= 0 )
  {

    vel1.y = -(vel1.y/1.2);
        //s_balon.rotate(-5);
  }
  if (balltest1.getPosition().x >= 885 || balltest1.getPosition().x <= 0  )
  {

        vel1.x = -vel1.x;
        //s_balon.rotate(5);
  }

  if ((pos1.x>=740 && pos1.x<=755 && pos1.y>=375) || //barra inferiror vertical
             (pos1.x>=775 && pos1.x<=780 && pos1.y>=130 && pos1.y<=200) )//barra superior vertical
             //(pos1.x>=790 && pos1.x<=800 && pos1.y>=260 && pos1.y<=340) ) // barra del medio vertical
         {
           //colision con barra inferior
           vel1.x = -(vel1.x/1.2);
         }

         if ((pos1.y>=100 && pos1.y<=115 && pos1.x>=775) || //barra superior horizontal
             (pos1.y>=280 && pos1.y<=300 && pos1.x>=785)  ) //barra horizontal media
         {
           //colision con barra superior
           vel1.y = -vel1.y;
         }

  //----------------------------------------------

  vel3.x += ac.x * 1.7;
  vel3.y += ac.y * 1,2;

  pos3.x = balltest3.getPosition().x;
  pos3.y = balltest3.getPosition().y;


  balltest3.setPosition(pos3.x + vel3.x, pos3.y + vel3.y);
  if (pos3.y >= 522 || pos3.y <= 0 )
  {

    vel3.y = -(vel3.y/1.2);
        //s_balon.rotate(-5);
  }
  if (pos3.x >= 885 || pos3.x <= 0  )
  {

        vel3.x = -vel3.x;
        //s_balon.rotate(5);
  }

  if ((pos1.x>=740 && pos1.x<=755 && pos1.y>=375) || //barra inferiror vertical
             (pos1.x>=775 && pos1.x<=780 && pos1.y>=130 && pos1.y<=200) )//barra superior vertical
             //(pos1.x>=790 && pos1.x<=800 && pos1.y>=260 && pos1.y<=340) ) // barra del medio vertical
         {
           //colision con barra inferior
           vel3.x = -(vel3.x/1.2);
         }

         if ((pos1.y>=100 && pos1.y<=115 && pos1.x>=775) || //barra superior horizontal
             (pos1.y>=280 && pos1.y<=300 && pos1.x>=785)  ) //barra horizontal media
         {
           //colision con barra superior
           vel3.y = -vel3.y;
         }

//-------------------------------------------------------

pos2.y = balltest2.getPosition().y;
pos2.x = balltest2.getPosition().x;

vel2.x += ac.x * 1.8;
vel2.y += ac.y * 1,1;



balltest2.setPosition(pos2.x + vel2.x, pos2.y + vel2.y);
if (balltest2.getPosition().y >= 522 || balltest2.getPosition().y <= 0 )
{

  vel2.y = -(vel2.y/1.2);
      //s_balon.rotate(-5);
}
if (balltest2.getPosition().x >= 885 || balltest2.getPosition().x <= 0  )
{

      vel2.x = -vel2.x;
      //s_balon.rotate(5);
}

if ((pos2.x>=740 && pos2.x<=755 && pos2.y>=375) || //barra inferiror vertical
           (pos2.x>=775 && pos2.x<=780 && pos2.y>=130 && pos2.y<=200) )//barra superior vertical
           //(pos1.x>=790 && pos1.x<=800 && pos1.y>=260 && pos1.y<=340) ) // barra del medio vertical
       {
         //colision con barra inferior
         vel2.x = -(vel2.x/1.2);
       }

       if ((pos2.y>=100 && pos2.y<=115 && pos2.x>=775) || //barra superior horizontal
           (pos2.y>=280 && pos2.y<=300 && pos2.x>=785)  ) //barra horizontal media
       {
         //colision con barra superior
         vel2.y = -vel2.y;
       }
//----------------------------

if ((pos2.x<=740 && pos2.x>=755 && pos2.y<=375) || //barra inferiror vertical
           (pos2.x<=775 && pos2.x>=780 && pos2.y<=130 && pos2.y>=200) ||
           (pos2.y<=100 && pos2.y>=115 && pos2.x<=775) || //barra superior horizontal
           (pos2.y<=280 && pos2.y>=300 && pos2.x<=785))
           {
             puntuacion++;
           }


//-----------------------
    txt_vida.setString("Life:");
    num_vidas.setString(to_string(nlife));
    num_time.setString(to_string(timer));
    num_pun.setString(to_string(puntuacion));

    if(liberar) { balon1 = new balon({-2,-4}); liberar  = false;  }
    if(liberar3){ balon3 = new balon({-1.-5,3}); liberar3 = false;  }
    if(liberar4){ balon4 = new balon({-4,-4});   liberar4 = false;  }
    if(liberar5){ balon5 = new balon({-2,-6});   liberar5 = false;  }
    if(liberar2){ balon2 = new balon({-5,-1});   liberar2 = false;  }

    if (caminar)
    {
        if (frame_actual.x < div_sprite.x-1)
        {
            frame_actual.x++;
            frame_actual.y = 0;
            obtener_frame(s_jugador, frame_actual);
            movimiento.x = 0.8f * a_move;
            s_jugador.move(movimiento);

        }
        else {
          frame_actual.x=0;
        }

    }

    if (atras)
    {
        if (frame_actual.x < div_sprite.x-1)
        {
            frame_actual.x++;
            frame_actual.y = 0;
            obtener_frame(s_jugador, frame_actual);
            movimiento.x = -0.8f * a_move;
            s_jugador.move(movimiento);

        }
        else {
          frame_actual.x=0;

        }



    }
    Sprite ballll  = balon1->get_sprite();
    Sprite ballll2 = balon2->get_sprite();
    Sprite ballll3 = balon3->get_sprite();
    Sprite ballll4 = balon4->get_sprite();
    Sprite ballll5 = balon5->get_sprite();
    if (s_jugador.getGlobalBounds().intersects(ballll.getGlobalBounds())||
        s_jugador.getGlobalBounds().intersects(ballll2.getGlobalBounds())||
        s_jugador.getGlobalBounds().intersects(ballll3.getGlobalBounds())||
        s_jugador.getGlobalBounds().intersects(ballll4.getGlobalBounds())||
        s_jugador.getGlobalBounds().intersects(ballll5.getGlobalBounds())

          )
    {

      nlife--;

    }

    if (s_obs.getGlobalBounds().intersects(balltest1.getGlobalBounds()) ||
        s_obs.getGlobalBounds().intersects(balltest2.getGlobalBounds()) ||
        s_obs.getGlobalBounds().intersects(balltest3.getGlobalBounds())  )
    {
      vel1.x = -vel1.x;
      vel2.x = -vel2.x;
      vel3.x = -vel3.x;

    }

    if (s_obs.getGlobalBounds().intersects(s_jugador.getGlobalBounds()) )
    {

    }

    if (patear)
    {
      if (s_jugador.getGlobalBounds().intersects(balltest1.getGlobalBounds()))
      {
        vel1.x=vel1.x+1.5;
        vel1.y=-(vel1.y*1.1);
      }
      if (s_jugador.getGlobalBounds().intersects(balltest2.getGlobalBounds()))
      {
        vel2.x=vel2.x+1.5;
        vel2.y=-(vel2.y*1.1);
      }
      if (s_jugador.getGlobalBounds().intersects(balltest3.getGlobalBounds()))
      {
        vel3.x=vel3.x+1.5;
        vel3.y=-(vel3.y*1.1);
      }

        if (frame_actual.x < div_sprite.x-1)
        {
            frame_actual.y = 2;
            frame_actual.x++;

            obtener_frame(s_jugador, frame_actual);

            //movimiento.x = 0.2f * a_move;
            //s_jugador.move(movimiento);

        }
        else
        {
          movimiento.x = 0;
          frame_actual.x=0;
          frame_actual.y=0;
          patear = false;
          obtener_frame(s_jugador, frame_actual);


        }


    }


    if (jump){
      kk++;
      if (frame_actual.x < div_sprite.x-1)
      {
        if(kk<15){
          frame_actual.x++;
          frame_actual.y = 3;
          obtener_frame(s_jugador, frame_actual);
          mov2.y = -0.8f * a_move;
          s_jugador.move(mov2);
        }
          if (kk>=15){
            //jump=false;
          mov2.y=1.f * a_move;
          s_jugador.move(mov2);
          }

      }

      else {

        frame_actual.x=0;
        frame_actual.y=0;
        mov2.x=0;
        obtener_frame(s_jugador, frame_actual);

      }

      if(s_jugador.getPosition().y >= 410 || s_jugador.getPosition().y <= 0){
            jump=false;
            frame_actual.y=0;
            mov2.y=0;
            mov2.x=0;
            kk=0;
      }
    }

}



void CrazyBall::render()
{
  window.clear();
  //Dibujar en pantalla el fondo
  window.draw(s_fond);
  //Dibujar en pantalla el jugador
  window.draw(s_jugador);
  //Dibujar en pantalla el balon

  //window.draw(circulo);
  if (balon1 != NULL){ balon1->actualizar(); window.draw(balon1->get_sprite());}
  if (balon2 != NULL){ balon2->actualizar(); window.draw(balon2->get_sprite());}
  if (balon3 != NULL){ balon3->actualizar(); window.draw(balon3->get_sprite());}
  if (balon4 != NULL){ balon4->actualizar(); window.draw(balon4->get_sprite());}
  if (balon5 != NULL){ balon5->actualizar(); window.draw(balon5->get_sprite());}



  if (tiempo1 > 285){ liberar  = true;  tiempo1 = 0;}
  if (tiempo2 > 350){ liberar2 = true;  tiempo2 = 0;}
  if (tiempo3 > 480){ liberar3 = true;  tiempo3 = 0;}
  if (tiempo4 > 590){ liberar4 = true;  tiempo4 = 0;}
  if (tiempo5 > 610){ liberar5 = true;  tiempo5 = 0;}


  //window.draw(s_ball);
  //muestro el circulo
  window.draw(balltest1);
  window.draw(balltest2);
  window.draw(balltest3);

  window.draw(s_obs);

  //

  //mostrar texto
  window.draw(txt_vida);
  window.draw(txt_time);
  window.draw(num_time);
  window.draw(num_vidas);
  window.draw(num_pun);
  window.draw(txt_pun);

  //window.draw(num_vidas);
  //Actualizar la ventana


  window.display();

}

void CrazyBall::cleared()
{

  window.close();
}

void CrazyBall::run()
{

  inic();



      while (isPlay)
      {
        tiempo = reloj1.getElapsedTime();

        if (tiempo.asSeconds() > (1/fps))
        {
          timer =  tiempo.asSeconds();
          //tiempo3 = tiempo.asSeconds();
          //std::cout << "tiempo2= " << tiempo2<<'\n';
          tiempo1++;
          tiempo2++;
          tiempo3++;
          tiempo4++;
          tiempo5++;

          eventos();
          update();

          render();
          //tiempo = reloj.getElapsedTime();
          //tiempo en segundos = tiempo.asSeconds
          //reloj1.restart();
//          num_vidas.setString(to_string(nlife));
          /*if (nlife <= 0 ){
            //window.draw(s_menu);
            //cin.get();
            break;
          }*/

        }

      }





  cleared();
}
