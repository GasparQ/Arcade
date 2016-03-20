//
// Created by veyrie_f on 3/19/16.
//

#ifndef CPP_ARCADE_CHRONO_HPP
#define CPP_ARCADE_CHRONO_HPP


#include <chrono>
#include <ostream>
#include <iostream>

class IChrono
{
public:
    virtual ~IChrono()
    {}
    virtual void Update() = 0;
    virtual double GetRemainingTime() const = 0;
    virtual void TriggerEvent() = 0;
    virtual void ResetChrono() = 0;

    virtual bool operator==(std::string const& name) const
    {
        return m_chronoName == name;
    }

protected:
    std::string m_chronoName;
};

/// <summary>
/// This class holds a chronometer and can trigger events
/// </summary>
template <class T, class U>
class Chrono : public IChrono
{
public:
    Chrono(double time, T & object, U method, std::string const& name) :
            m_remaining_time(time),
            m_start_time(m_remaining_time),
            m_object(object),
            m_method(method)
    {
        m_last_clock = std::chrono::steady_clock::now();
        m_chronoName = name;
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

    virtual void ResetChrono()
    {
        m_remaining_time = m_start_time;
    }

public:
    virtual bool operator==(Chrono<T, U> const& other) const
    {
        return m_chronoName == other.m_chronoName;
    }

private:
    std::chrono::steady_clock::time_point m_last_clock;
    double m_remaining_time = 0;
    double m_start_time = 0;
    T & m_object;
    U m_method;
};

#endif //CPP_ARCADE_CHRONO_HPP
