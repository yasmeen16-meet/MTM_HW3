//
// Created by HD on 25/06/2019.
//

#include "seat.h"
using std::to_string;

/////////FrontRegularSeat/////////
int FrontRegularSeat::price() const {
    return this->base_price;
}

string FrontRegularSeat::location() const {
    string area_str(1,this->area);
    string result = "Front-> area: " + area_str + ", line: " + to_string(this->line)
            + ", chair: " + to_string(this->chair);
    return result;
}
///////////////
///////MiddleRegularSeat////////
int MiddleRegularSeat::price() const {
    return this->base_price;
}

string MiddleRegularSeat::location() const {
    string area_str(1, this->area);
    string result = "Middle-> area: " + area_str + ", line: " + to_string(this->line)
                    + ", chair: " + to_string(this->chair);
    return result;
}
///////////////
///////RearRegularSeat////////
int RearRegularSeat::price() const {
    return this->base_price;
}

string RearRegularSeat::location() const {
    string area_str(1, this->area);
    string result = "Rear-> area: " + area_str + ", line: " + to_string(this->line)
                    + ", chair: " + to_string(this->chair);
    return result;
}
