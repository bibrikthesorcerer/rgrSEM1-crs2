#include "vector.h"
#include <iostream>


int main()
{

   vector obj1;
   vector obj2;
   vector obj3;
   try 
   {
      std::cin >> obj1;



      std::cout << obj1 << std::endl;

      obj3 = obj1.subVec(2, 4);

      std::cout << obj3 << std::endl;


      for (iterator it = obj3.begin(); it != obj3.end(); ++it)
      {
         std::cout << *it << ' ';
      }
   }
   catch (const char* message)
   {
      std::cout << message << std::endl;
   }
   return 0;
}