#include <iostream>
#include <string>
using std::string;
using std::exception;


// ---------------------------------------------
class NoPrice
{
};

// ---------------------------------------------
class Seat {
protected:
    int line, chair, base_price;
public:
    Seat(int line, int chair, int base): line(line), chair(chair), base_price(base) {}

    virtual string location() const = 0;

    virtual int price() const = 0;

    virtual ~ Seat() {}

};

// ---------------------------------------------
class GreenRoomSeat
{

};

// ---------------------------------------------
class MainHallSeat : public Seat{
public:
    MainHallSeat (int line , int chair , int base_price) : Seat(line,chair,base_price+100) {}
};

// ---------------------------------------------
class SpecialSeat
{
};

// ---------------------------------------------
class GoldenCircleSeat
{
};

// ---------------------------------------------
class DisablePodiumSeat
{
};

// ---------------------------------------------
class RegularSeat : public MainHallSeat {
protected:
    char area;
public:
    RegularSeat(char area, int line, int chair, int base_price):
            area(area), MainHallSeat(line, chair, base_price){}
};

// ---------------------------------------------
class FrontRegularSeat : public RegularSeat {
public:
    FrontRegularSeat(char area, int line, int chair, int base_price):
            RegularSeat(area, line, chair, base_price + 500) {}

    int price() const override;

    string location() const override;
};

// ---------------------------------------------
class MiddleRegularSeat : public  RegularSeat {
public:
    MiddleRegularSeat(char area, int line, int chair, int base_price):
            RegularSeat(area, line, chair, base_price + 250) {}

    int price() const override;

    string location() const override;
};

// ---------------------------------------------
class RearRegularSeat : public RegularSeat {
public:
    RearRegularSeat(char area, int line, int chair, int base_price):
            RegularSeat(area, line, chair, base_price) {}

    int price() const override;

    string location() const override;
};

// ---------------------------------------------
