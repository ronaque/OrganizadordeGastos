#ifndef MES_H
#define MES_H
#include <string>
#include <vector>

class Mes
{
public:
  int mes;
  int ano;
  float valorTotal;
  std::vector<std::string> objetosMes;

  friend std::ostream &operator<<(std::ostream &os, const Mes m);
};

#endif