//
// Created by 18604 on 11/26/2022.
//

#ifndef PDM_PLATFORMS_UI_PDM_STATUS_H
#define PDM_PLATFORMS_UI_PDM_STATUS_H

#include <string>

namespace PDM {

    class Status {
    public:
        enum State {
            NONE,
            LOADING,
            OPEN,
            CLOSED,
            ERROR
        };

    protected:
        State current_status = State::NONE;
    public:
        virtual void change(State status) {
          current_status = status;
        }

        [[nodiscard]] virtual const char* text_status() const {
          switch(current_status) {
            case State::NONE:
              return "NONE";
            case State::LOADING:
              return "LOADING";
            case State::OPEN:
              return "OPEN";
            case State::CLOSED:
              return "CLOSED";
            case State::ERROR:
              return "ERROR";
            default:
              return "UNKNOWN"; // This case shouldn't be reached, but it's here as a fallback
          }
        }

        [[nodiscard]] State get_current_status() const {
          return current_status;
        }
    };
} // namespace PDM
#endif //PDM_PLATFORMS_UI_PDM_STATUS_H