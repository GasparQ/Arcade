//
// Created by veyrie_f on 3/19/16.
//

#ifndef CPP_ARCADE_CHRONO_HPP
#define CPP_ARCADE_CHRONO_HPP


#include <chrono>
#include <ostream>
#include <iostream>

class AChrono
{
public:
    virtual void Update() = 0;
    virtual double GetRemainingTime() const = 0;
    virtual void TriggerEvent() = 0;
};

// <summary>
// This class holds a chronometer and can trigger events
// </summary>
template <class T, class U>
class Chrono : public AChrono
{
public:
    Chrono(double time, T & object, U method) : m_remaining_time(time), m_object(object), m_method(method)
    {
        m_last_clock = std::chrono::steady_clock::now();
    }
    virtual ~Chrono()
    {}

    void Update()
    {
        m_remaining_time -= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()
                                                                                  - m_last_clock).count() / 1000.0;
        m_last_clock = std::chrono::steady_clock::now();
        if (m_remaining_time < 0)
        {
            m_remaining_time = 0;
        }
    }

    double GetRemainingTime() const
    {
        return m_remaining_time;
    }

    void TriggerEvent()
    {
        (m_object.*m_method)();
    }

private:
    std::chrono::steady_clock::time_point m_last_clock;
    double m_remaining_time = 0;
    T & m_object;
    U m_method;
};

#endif //CPP_ARCADE_CHRONO_HPP
