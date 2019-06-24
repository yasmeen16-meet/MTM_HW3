#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>
#include <string.h>

//---------------------------------------------------
enum VoterType { All, Regular, Judge };
enum Phase { Registration, Contest, Voting };
using namespace std ;

//---------------------------------------------------

class Participant {
private:
    string state_name;
    string song_name;
    int song_length;
    string singer_name;
    int is_registerd;
    

public :
    Participant(string state, string song, int length, string singer);

    ~Participant();

    string state() const;

    string song() const;

    int timeLength() const;

    string singer() const;

    Participant() = delete;

    Participant(const Participant &) = delete;

    Participant &operator=(const Participant &) = delete;

    int isRegistered() const;

    void update(string new_song, int new_time, string new_singer);

    void updateRegistered(bool);
};
std::ostream& operator<<(std::ostream& , const Participant&);

//---------------------------------------------------

class Voter
{
    int type , counter;
    string state_name;
public :
    Voter (string, int type =Regular);
    string state()const ;
    int voterType()const ;
    int timesOfVotes()const ;
    Voter& operator++( );
};
std::ostream& operator<<(std::ostream& , const Voter&);

// -----------------------------------------------------------

struct Vote
{
    Voter* voter;
    string* state;
    Vote(Voter&, string="", string="",string ="",string="",string ="",string="",string="", string =""
            ,string="" , string= "");
    ~Vote();
};

// -----------------------------------------------------------

class MainControl {
    int max_time, max_participants, max_votes, phase;
    int* regular_votes, *judge_votes;
    Participant **control_participants;


private:
    int getSize()const;
    bool stateExists(const MainControl& , string state);
    ///
    Participant** sortParticipants();
    void sortHelp(Participant**, int);
    int getIndex(string);
    MainControl& operator =(const MainControl&)= default;

public :
    MainControl(int max_time = 180, int max_participants = 26, int max_votes = 5);
    ~MainControl();
    MainControl& operator+=(Participant&);
    friend std::ostream &operator<<(std::ostream&, MainControl&);
    MainControl& operator-=(Participant&);
    void setPhase (int new_phase);
    bool legalParticipant(Participant& participant)const ;
    bool participate (const  string) ;
    friend std::ostream &operator<<(std::ostream&, const MainControl&);
    MainControl& operator+=(Vote );

    ///////part2/////
    MainControl(const MainControl& main_control);
    class Iterator;
    Iterator begin() const;
    Iterator end() const;

};

class MainControl::Iterator {
    const MainControl* main_control;
    int index;
    Iterator (const MainControl* main_control, int index);
    friend class MainControl;
public:
    Iterator();
    const Participant& operator*()const;
    Iterator& operator++();
    bool operator<(const Iterator& it) const;
    bool operator==(const Iterator& it) const;
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&)= default ;
    Iterator& operator--() = delete;
};


// -----------------------------------------------------------

#endif
