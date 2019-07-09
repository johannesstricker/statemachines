#include <iostream>
#include <string>
#include "hsm.h"

using namespace hsm;

typedef int DataType;

enum Events
{
  Start = NoEvent + 1,
  Stop,
  Terminate
};

class Entry : public State<DataType>
{
public:
  virtual Event exec(DataType& data) override
  {
    std::cout << data << std::endl;
    if(data <= 0)
      return Events::Stop;
    data -= 1;
    return NoEvent;
  }
};

class Exit : public State<DataType>
{
public:
  virtual Event exec(DataType& data) override
  {
    std::cout << "Terminated." << std::endl;
    return Events::Terminate;
  }
};

int main(int argc, char** argv)
{
  std::cout << "Hierarchical State Machine" << std::endl;

  DataType data = 10;

  TransitionTable<DataType> transitions;
  transitions.set(Events::Start, [](){ return new Entry(); });
  transitions.set(Events::Stop, [](){ return new Exit(); });

  StateMachine<DataType> fsm(&transitions);
  fsm.transition(Events::Start);
  // Run FSM until terminated.
  Event event = NoEvent;
  while(event != Events::Terminate)
  {
    event = fsm.exec(data);
  }
  return 0;
}
