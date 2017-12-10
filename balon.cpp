#include "balon.h"

balon::balon()
{
    t_balon.loadFromFile("Imagenes/balon_36x36.png");

    s_balon.setTexture(t_balon);

    s_balon.setPosition(800,120);
}
