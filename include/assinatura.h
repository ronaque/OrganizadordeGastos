#ifndef ASSINATURA_H
#define ASSINATURA_H
#include <string>

class Assinatura
{
public:
  std::string nome;
  float valor;

  friend std::ostream &operator<<(std::ostream &os, const Assinatura a);
};
#endif