
#include "seat.h"
using std::to_string;

///GoldenCircleSeat
string GoldenCircleSeat::location() const {
    string line2 =to_string(this->line);
    string chair2 =to_string(this->chair);
    string str = "Golden Circle-> line: "+ line2+ ", chair: "+ chair2;
    return str;
}

int GoldenCircleSeat::price() const {
    return this->base_price;
}

///DisablePodiumSeat
string DisablePodiumSeat::location() const {
    string line2 =std::to_string(this->line);
    string chair2 =std::to_string(this->chair);
    string str ="Disable Podium-> line: "+line2+", chair: "+chair2;
    return str;
}
int DisablePodiumSeat::price() const {
    return this->base_price;
}

////////FrontRegularSeat/////////
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

////GreenRoomSeat
string GreenRoomSeat::location() const {
    string line2 =to_string(this->line);
    string chair2 =to_string(this->chair);
    string str = "Green Room-> line: "+ line2+ ", chair: "+ chair2;
    return str;
}

int GreenRoomSeat::price() const {
    throw NoPrice();
}

///////NoPrice//////

const char* NoPrice::what() const noexcept{
    return "Not For Sale !";

}
