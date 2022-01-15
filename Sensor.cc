module;

export module Sensor;

import State;

export class Sensor {
public:
    virtual bool is_safe(coordinate_t, coordinate_t) = 0;
};