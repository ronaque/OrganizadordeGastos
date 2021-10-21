#include "include\mes.h"
#include <iostream>
#include <fstream>

std::ostream &operator<<(std::ostream &os, const Mes m)
{
  os << m.mes << " " << m.ano << " " << m.valorTotal << " ";
  return os;
}