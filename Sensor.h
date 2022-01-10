#pragma once

#include "state.h"

class Sensor {
public:
    virtual bool is_safe(coordinate_t, coordinate_t) = 0;
};