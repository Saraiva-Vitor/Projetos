#include<iostream>
using namespace std;
int Ackermann(int y)
{
      // Base or Termination Condition
    if (0 == y)
   {
      return y + 1;
 }
// Error Handling condition
   if (y < 0)
  {
      return -1;
   }
// Recursive call by Linear method
   else if (0 == y)
  {
      return Ackermann(1);
  }
   // Recursive call by Nested method
   else
  {
      return Ackermann(Ackermann(y-1));
  }
}
int main(){
    cout<<"\n"<<Ackermann(0);
}
