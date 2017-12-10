#include <iostream>
#include "CrazyBall.h"
#include <memory>


int main()
{

  std::shared_ptr<CrazyBall> mijuego(new CrazyBall());
  mijuego->run();

  return 0;
}
