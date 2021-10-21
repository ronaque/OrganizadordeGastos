#ifndef PAGAMENTO_H
#define PAGAMENTO_H
#include <string>

class Pagamento
{
public:
  std::string nome;
  float valor;
  int quantParcelas;

  friend std::ostream &operator<<(std::ostream &os, const Pagamento o);
};

#endif