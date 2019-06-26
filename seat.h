#include <iostream>
#include <string>
using std::string;
using std::exception;

// ---------------------------------------------

class NoPrice:public exception{
public:
    NoPrice()= default;
    virtual const char* what() const noexcept override;
};

// ---------------------------------------------

class Seat
{
protected:
    int line , chair , base_price;
public:
    Seat (int line , int chair , int base):
    line(line) , chair(chair) , base_price(base){}
    virtual string location() const=0 ;
    virtual int price()const=0 ;
    virtual ~ Seat(){}
};

// ---------------------------------------------

class GreenRoomSeat:public Seat
{
public:
    GreenRoomSeat(int line , int chair):
    Seat(line,chair,0){}
    string location() const override;
    int price () const override;
};

// ---------------------------------------------

class MainHallSeat: public Seat{
public:
        MainHallSeat (int line , int chair , int base):
         Seat(line,chair,base+100)       {}
};

// ---------------------------------------------

class SpecialSeat : public MainHallSeat{
public:
    SpecialSeat(int line , int chair , int base ):
    MainHallSeat(line,chair,base+300){}

};

// ---------------------------------------------

class GoldenCircleSeat : public SpecialSeat{
public:
    GoldenCircleSeat(int line , int chair , int base):
    SpecialSeat(line,chair,base+1000){}
    string location() const override;
    int price () const override;
};

//* ---------------------------------------------

class DisablePodiumSeat : public SpecialSeat
{
public:
    DisablePodiumSeat(int line, int chair , int base=0):
    SpecialSeat(line,chair,base){
        base_price=200;
    }
    string location() const override;
    int price () const override;
};

// ---------------------------------------------
class RegularSeat : public MainHallSeat {
protected:
    char area;
public:
    RegularSeat(char area, int line, int chair, int base_price):
            MainHallSeat(line, chair, base_price),area(area){}
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
