#ifndef ADAPTERSTATES_H
#define ADAPTERSTATES_H

class AdapterStates
{
    /* data */
public:
    AdapterStates(/* args */);
    ~AdapterStates();

    bool streaming = true;

private:

};

AdapterStates::AdapterStates(/* args */)
{
}

AdapterStates::~AdapterStates()
{
}

class AdapterSettings{

public:
    uint16_t can_rate_kbs = 500;

private:

};


#endif