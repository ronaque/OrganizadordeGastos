#include <iostream>
#include <fstream>

int main(int argc, char const *argv[])
{
  int aaa;
  std::fstream fout;
  int matriz[3][2] = {{11, 21}, {21, 22}, {31, 32}};
  fout.open("teste.txt");
  // for (int i = 0; i < 2; i++)
  // {
  //   for (int k = 0; k < 2; k++)
  //   {
  //     matriz[i][k] = 1;
  //   }
  // }
  for (int i = 0; i < 2; i++)
  {
    for (int k = 0; k < 3; k++)
    {
      std::cout << matriz[i][k];
    }
    std::cout << std::endl;
  }

  fout.close();
  return 0;
}
