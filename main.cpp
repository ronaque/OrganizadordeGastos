/*
  Criado por Isaque Barbosa
  isaque.bm9@gmail.com

  cmd /k cd C:\Users\isaqu\Documents\Escolaridade\Projetos de Programação\C\OrganizadorGastos
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <string>
#include <vector>

#include <filesystem>
#include <algorithm>
#include <locale>

#include <time.h>

#include <stdio.h>

#include "include\main.h"

std::string tolowerString(std::string string)
{
  std::locale loc;
  char aux;
  for (int i = 0; i < string.size(); i++)
  {
    aux = std::tolower(string[i], loc);
    string[i] = aux;
  }
  return string;
}

std::string toMonthString(int mes)
{
  switch (mes)
  {
  case 1:
    return "Janeiro";
  case 2:
    return "Fevereiro";
  case 3:
    return "Março";
  case 4:
    return "Abril";
  case 5:
    return "Maio";
  case 6:
    return "Junho";
  case 7:
    return "Julho";
  case 8:
    return "Agosto";
  case 9:
    return "Setembro";
  case 10:
    return "Outubro";
  case 11:
    return "Novembro";
  case 12:
    return "Dezembro";
  default:
    return "Inexistente";
  }
}

bool is_empty(std::fstream &pFile)
{
  return pFile.peek() == std::ifstream::traits_type::eof();
}

float sumAssinaturas(std::vector<Assinatura> assianturas)
{
  float sum = 0;
  for (int i = 0; i < assianturas.size(); i++)
  {
    sum += assianturas[i].valor;
  }
  return sum;
}

void printOptions()
{
  std::cout << std::endl
            << "O que deseja fazer?" << std::endl
            << "1 - Adicionar pagamento" << std::endl
            << "2 - Adicionar assinatura" << std::endl
            << "3 - Ver Pagamentos" << std::endl
            << "4 - Reset" << std::endl
            << "5 - Sair" << std::endl;
}

int main(int argc, char const *argv[])
{
  system("chcp 65001");
  system("cls");

  // Tempo
  time_t timeT = time(NULL);
  struct tm *lTime = localtime(&timeT);
  int mesAtual = lTime->tm_mon + 1;     // 9
  int anoAtual = lTime->tm_year + 1900; // 2021

  bool quit = false;
  std::string linha;
  std::string line;
  std::vector<Mes> mesesPagamentos;
  std::vector<Pagamento> pagamentos;
  std::vector<Assinatura> assinaturas;

  int x;

  //////// Manipulação Entrada do arquivo mesesPagamentos
  std::fstream arquivoMeses;
  arquivoMeses.open("\\data\\mesesPagamentos.txt");
  // Recebimento vetor de meses
  if (!is_empty(arquivoMeses))
  {
    while (!arquivoMeses.eof())
    {
      Mes novoMes;
      std::string nomePagamento;

      arquivoMeses >> novoMes.mes >> novoMes.ano >> novoMes.valorTotal;
      std::getline(arquivoMeses, line, '\n');
      std::istringstream fin(line);
      while (fin >> nomePagamento)
      {
        novoMes.objetosMes.push_back(nomePagamento);
      }
      mesesPagamentos.push_back(novoMes);
      // std::cout << novoMes;
    }
  }
  arquivoMeses.close();

  //////// Manipulação Entrada do arquivo Pagamentos
  std::fstream arquivoPagamentos;
  arquivoPagamentos.open("\\data\\pagamentos.txt");
  // Recebimento vetor de pagamentos
  if (!is_empty(arquivoPagamentos))
  {
    while (!arquivoPagamentos.eof())
    {
      Pagamento novoPagamento;

      arquivoPagamentos >> novoPagamento.nome >> novoPagamento.valor >> novoPagamento.quantParcelas;
      pagamentos.push_back(novoPagamento);
    }
  }
  arquivoPagamentos.close();

  //////// Manipulação Entrada do arquivo Assinaturas
  std::fstream arquivoAssinaturas;
  arquivoAssinaturas.open("\\data\\assinaturas.txt");
  //Recebimento do vetor de assinaturas
  if (!is_empty(arquivoAssinaturas))
  {
    while (!arquivoAssinaturas.eof())
    {
      Assinatura novaAssinatura;

      arquivoAssinaturas >> novaAssinatura.nome >> novaAssinatura.valor;
      assinaturas.push_back(novaAssinatura);
    }
  }
  arquivoAssinaturas.close();

  //////// Atualização vetor de meses de acordo com a \\data atual | adição dos 12 meses
  int indexMeses;
  if (mesesPagamentos.size() != 0)
  {
    while (mesesPagamentos[0].mes != mesAtual)
    {
      indexMeses = 0;
      while (indexMeses != 11)
      {
        mesesPagamentos[indexMeses] = mesesPagamentos[indexMeses + 1];
        indexMeses++;
      }
      mesesPagamentos.pop_back();
      Mes novoMes;
      novoMes.mes = mesesPagamentos[indexMeses - 1].mes + 1;

      //Adicionando Assianturas
      novoMes.valorTotal += sumAssinaturas(assinaturas);
      for (int i = 0; i < assinaturas.size(); i++)
      {
        novoMes.objetosMes.push_back(assinaturas[i].nome);
      }

      // Correção meses e ano
      if (novoMes.mes > 12)
      {
        novoMes.mes -= 12;
        novoMes.ano = mesesPagamentos[indexMeses - 1].ano + 1;
      }
      else
        novoMes.ano = mesesPagamentos[indexMeses - 1].ano;
      mesesPagamentos.push_back(novoMes);
    }
  }
  else
  {
    for (int i = 0; i < 12; i++)
    {
      Mes novoMes;
      novoMes.mes = mesAtual + i;
      if (novoMes.mes > 12)
      {
        novoMes.mes -= 12;
        novoMes.ano = anoAtual + 1;
      }
      else
        novoMes.ano = anoAtual;

      novoMes.valorTotal = 0;
      mesesPagamentos.push_back(novoMes);
    }
  }

  //////// Programa
  printOptions();
  while (!quit)
  {

    std::getline(std::cin, linha);
    linha = tolowerString(linha);

    ///// Quit
    if (linha == "quit" || linha == "5")
    {
      std::cout << "Saindo do programa";
      quit = true;
    }

    ///// Adicioanr Pagamentos
    else if (linha == "adicionar pagamento" || linha == "1")
    {
      Pagamento novoPagamento;
      char lixo;

      // Criação do novo objeto
      std::cout << "Digite o nome do pagamento (Nome deve ser simples), a quantidade de parcelas e o valor total do produto" << std::endl;
      std::cin >> novoPagamento.nome >> novoPagamento.quantParcelas >> novoPagamento.valor;
      std::cin.ignore();

      // Erro número de parcelas
      if (novoPagamento.quantParcelas < 1 || novoPagamento.quantParcelas > 12)
      {
        std::cout << "Quantidade inválida de parcelas";
      }
      // Adicionar erro de nome reptido
      // Erro de valor negativo
      else if (novoPagamento.valor <= 0)
      {
        std::cout << "Valor não permitido";
      }
      else
      {
        std::cout << "Adicionado o pagamento " << novoPagamento.nome << " em " << novoPagamento.quantParcelas << " parcelas de R$" << std::fixed << std::setprecision(2) << novoPagamento.valor / novoPagamento.quantParcelas << std::endl;

        //Adiciona o pagamento ao vetor de pagamentos
        pagamentos.push_back(novoPagamento);

        // Adição do pagamento nos meses referentes às parcelas
        for (int i = 0; i < novoPagamento.quantParcelas; i++)
        {
          mesesPagamentos[i].objetosMes.push_back(novoPagamento.nome);
          mesesPagamentos[i].valorTotal += (novoPagamento.valor / novoPagamento.quantParcelas);
        }
      }
      printOptions();
    }

    ///// Adicionar assinatura
    else if (linha == "adicionar assinatura" || linha == "2")
    {
      Assinatura novaAssinatura;
      std::cout << "Digite o nome para a assinatura e o valor dela" << std::endl;
      std::cin >> novaAssinatura.nome >> novaAssinatura.valor;
      std::cin.ignore();
      assinaturas.push_back(novaAssinatura);

      // Adição da assinatura nos 12 meses atuais
      for (int i = 0; i < 12; i++)
      {
        mesesPagamentos[i].objetosMes.push_back(novaAssinatura.nome);
        mesesPagamentos[i].valorTotal += novaAssinatura.valor;
      }
      std::cout << "Adicionado a assinatura " << novaAssinatura.nome << " de R$" << std::fixed << std::setprecision(2) << novaAssinatura.valor << std::endl;
      printOptions();
    }

    ///// Ver Pagamentos
    else if (linha == "ver pagamentos" || linha == "3")
    {
      // Cada mês em uma linha
      for (int i = 0; i < mesesPagamentos.size(); i++)
      {
        std::cout << toMonthString(mesesPagamentos[i].mes) << "/" << mesesPagamentos[i].ano << " - Pagamentos do mês: | ";
        for (int k = 0; k < mesesPagamentos[i].objetosMes.size(); k++)
        {
          std::cout << mesesPagamentos[i].objetosMes[k] << " | ";
        }
        std::cout << "Valor total de R$:" << std::fixed << std::setprecision(2) << mesesPagamentos[i].valorTotal << std::endl;
      }
      printOptions();
    }
    else if (linha == "reset" || linha == "4")
    {
      int mesesSize = mesesPagamentos.size();
      for (int i = 0; i < mesesSize; i++)
        mesesPagamentos.pop_back();
      int assinaturasSize = assinaturas.size();
      for (int i = 0; i < assinaturasSize; i++)
        assinaturas.pop_back();
      int pagamentosSize = pagamentos.size();
      for (int i = 0; i < pagamentosSize; i++)
        pagamentos.pop_back();
      std::cout << "Lista de pagamentos resetada" << std::endl;
      printOptions();
    }
    else
    {
      std::cout << "Digite uma das opções" << std::endl;
      std::cin.ignore();
    }
  }
  //////// Fim Programa
  Save(mesesPagamentos, pagamentos, assinaturas);

  return 0;
}