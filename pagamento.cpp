#include "include\pagamento.h"
#include <iostream>
#include <fstream>

std::ostream &operator<<(std::ostream &os, const Pagamento o)
{
  os << o.nome << " " << o.valor << " " << o.quantParcelas;
  return os;
}