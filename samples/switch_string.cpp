#include <iostream>

enum { EXECUTED, INCOMING, READY, RUNNING, WAIT }; //status

int main(int argc, char* argv[])
{
  std::cout << EXECUTED << "\n";
  // switch( resolveOption(READY) )
  // {
  //     case Option1:
  //     {
  //         //...
  //         break;
  //     }
  //     case Option2:
  //     {
  //         //...
  //         break;
  //     }
  //     // implicitly Option_Invalid, etc
  //     default:
  //     {
  //         //...
  //         break;
  //     }
  // }
  return 0;
}