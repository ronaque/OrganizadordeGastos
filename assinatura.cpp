#include "include\assinatura.h"
#include <iostream>
#include <fstream>

std::ostream &operator<<(std::ostream &os, const Assinatura a)
{
  os << a.nome << " " << a.valor;
  return os;
}