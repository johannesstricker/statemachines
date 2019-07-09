#pragma once
#include <iostream>
#include <map>
#include <functional>
#include <memory>

namespace hsm
{
  typedef int Event;
  constexpr Event NoEvent = -1;

  template<typename T>
  class State
  {
  public:
    virtual Event exec(T& data)
    {
      std::cerr << "Not implemented." << std::endl;
      return NoEvent;
    }
  };

  template<typename T>
  class TransitionTable
  {
  public:
    typedef State<T> State_t;
    typedef std::function<State_t*()> Transition_t;
    void set(Event event, const Transition_t& transition)
    {
      m_transitions[event] = transition;
    }
    State_t* transition(Event event) const
    {
      auto iter = m_transitions.find(event);
      if(iter == m_transitions.end())
        return nullptr;
      return iter->second();
    }
    bool hasTransition(Event event) const
    {
      return m_transitions.find(event) != m_transitions.end();
    }
  private:
    std::map<Event, Transition_t> m_transitions;
  };

  template<typename T>
  class StateMachine : public State<T>
  {
  public:
    typedef State<T> State_t;
    typedef TransitionTable<T> TransitionTable_t;
    StateMachine(const TransitionTable_t* transitions)
    : m_transitions(transitions)
    {
      // empty
    }
    virtual Event exec(T& data) override
    {
      Event event = m_state->exec(data);
      if(event == NoEvent)
        return NoEvent;
      return transition(event)
           ? exec(data)
           : event;
    }
    bool transition(Event event)
    {
      State_t* next = m_transitions->transition(event);
      if(next == nullptr)
        return false;
      m_state.reset(next);
      return true;
    }
  private:
    const TransitionTable_t* m_transitions;
    std::unique_ptr<State_t> m_state;
  };}