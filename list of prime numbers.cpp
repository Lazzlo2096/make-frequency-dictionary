// https://www.codewars.com/kata/521ef596c106a935c0000519

#include <vector>

std::vector<unsigned> prime(unsigned n)
{
  if (n < 2)
    return {};
  
  std::vector<unsigned> v(n-1);
  
  for (int i = 0; i < v.size(); i++)
    v[i] = i+2;
  
  for (int i = 0; i < v.size(); i++)
    for (int j = i+1; j < v.size(); j++)
       if ( v[j] % v[i] == 0 )
         v.erase(v.begin()+j);
         // erace 
         // Удаление из вектора - дорогая операция
    
  return v;
  
  

}
