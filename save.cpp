#include "include\save.h"
#include <iostream>
#include <fstream>

void Save(std::vector<Mes> mesesPagamentos, std::vector<Pagamento> pagamentos,
          std::vector<Assinatura> assinaturas)
{
  std::fstream arquivoMeses;
  std::fstream arquivoAssinaturas;
  std::fstream arquivoPagamentos;
  // std::cout << "Salvando mesesPagamentos";

  //////// Manipulação salvar arquivo mesesPagamentos
  // Salvar vetor de meses
  if (mesesPagamentos.size() > 0)
  {
    arquivoMeses.open("data\\mesesPagamentos.txt");
    for (int i = 0; i < mesesPagamentos.size() - 1; i++)
    {
      arquivoMeses << mesesPagamentos[i] << " ";
      for (int k = 0; k < mesesPagamentos[i].objetosMes.size(); k++)
      {
        arquivoMeses << mesesPagamentos[i].objetosMes[k] << " ";
      }
      arquivoMeses << std::endl;
    }
    arquivoMeses << mesesPagamentos[11];
    for (int k = 0; k < mesesPagamentos[11].objetosMes.size(); k++)
    {
      arquivoMeses << mesesPagamentos[11].objetosMes[k] << " ";
    }
  }
  else
  {
    arquivoMeses.open("data\\mesesPagamentos.txt", std::ofstream::out | std::ofstream::trunc);
  }
  arquivoMeses.close();

  // std::cout << "Salvando Assinturas";

  //////// Manipulação salvar arquivo Assinaturas
  int indexassinaturas = 0;
  // Salvar vetor de assinaturas
  if (assinaturas.size() > 1)
  {
    arquivoAssinaturas.open("data\\assinaturas.txt");
    for (int k = 0; k < assinaturas.size() - 1; k++)
    {
      arquivoAssinaturas << assinaturas[k].nome << " " << assinaturas[k].valor << std::endl;
      indexassinaturas++;
    }
    arquivoAssinaturas << assinaturas[indexassinaturas].nome << " " << assinaturas[indexassinaturas].valor;
  }
  else
    arquivoAssinaturas.open("data\\assinaturas.txt", std::ios::out | std::ios::trunc);

  arquivoAssinaturas.close();

  // std::cout << "Salvando Pagamentos";

  //////// Manipulação salvar arquivo Pagamentos
  int indexPagamentos = 0;
  // Salvar vetor de pagamentos
  if (pagamentos.size() > 0)
  {
    arquivoPagamentos.open("data\\pagamentos.txt");
    for (int k = 0; k < pagamentos.size() - 1; k++)
    {
      arquivoPagamentos << pagamentos[k] << std::endl;
      indexPagamentos++;
    }
    arquivoPagamentos << pagamentos[indexPagamentos];
  }
  else
    arquivoPagamentos.open("data\\pagamentos.txt", std::ios::out | std::ios::trunc);
  arquivoPagamentos.close();
}
