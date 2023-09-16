//
// Created by Yi Yang on 9/16/2023.
//

#ifndef PDM_QT_PDM_COMMAND_H
#define PDM_QT_PDM_COMMAND_H


#include <string>
#include <functional>

namespace PDM {
class pdm_command {
public:
  pdm_command(const std::string &name, std::function<void()> action)
      : name_(name), action_(action), toggle_(false), value_(0) {}

  void execute() { action_(); }

  void setToggle(bool state) { toggle_ = state; }

  bool getToggle() const { return toggle_; }

  void setValue(int val) { value_ = val; }

  int getValue() const { return value_; }

private:
  std::string name_;
  std::function<void()> action_;
  bool toggle_;
  int value_;
};

}


#endif //PDM_QT_PDM_COMMAND_H
