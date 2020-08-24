#pragma once

struct Goal {
  int m_input;

  int m_output;

  bool atGoal;
  
  Goal(int input, int output): m_input(input), m_output(output)
  {}

};

extern Goal Goal1;
extern Goal Goal2;
