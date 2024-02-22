#pragma once

#include "Objects.h"



class LAMP : public Object
{
public:
    LAMP(const glm::vec2& position = glm::vec2(0.f));


    ~LAMP();
  

    void changeState();


    void Control();
  

private:
    bool isActive = false;
    bool isfirst = true;
};