#ifndef CRAZYBALL_H_INCLUDED
#define CRAZYBALL_H_INCLUDED

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class balon
{
    Texture t_balon;
    Sprite s_balon;

  public:
    balon();
    Sprite get_sprite(){ return s_balon; };

};



#endif
