#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>
#include <string.h>
// it's allowed to define here any using statements, according to needs.
// do NOT define here : using namespace std;
//---------------------------------------------------
enum VoterType { All, Regular, Judge };
enum Phase { Registration, Contest, Voting };
using namespace std ;

//---------------------------------------------------

class Participant {
// relevant private members can be defined here, if necessary.
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
// need to define here possibly c'tr and d'tr and ONLY methods that


// NO friend is allowed here.


// NO OTHER METHODS SHOULD APPEAR HERE.
// are mentioned and demonstrated in the test example that has been published.

};
std::ostream& operator<<(std::ostream& , const Participant&);

//---------------------------------------------------


class Voter
{
// relevant private members can be defined here, if necessary.

public :

// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

// NO friend is allowed here.

};


// -----------------------------------------------------------

struct Vote
{

// ALL is public here.
// need to define ONLY data members and c'tr and d'tr.
// NO NEED to define anything else.

};

// -----------------------------------------------------------


class MainControl {
    int max_time, max_participants, max_votes, phase;
    Participant **control_participants;
    //votes
// relevant private members can be defined here, if necessary.

private:
    int getSize()const;
    bool stateExists(const MainControl& , string state);
    ///
    Participant** sortParticipants();
    void sortHelp(Participant**, int);
    //int bubble(Participant**, int);

    ///

public :

// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

// Also it's allowed here to define friend.

    MainControl(int max_time = 180, int max_participants = 26, int max_votes = 5);
    ~MainControl();
    MainControl& operator+=(Participant&);
    friend std::ostream &operator<<(std::ostream&, MainControl&);
    MainControl& operator-=(Participant&);
    void setPhase (int new_phase);
    bool legalParticipant(Participant& participant)const ;
    bool participate (const  string) ;
    friend std::ostream &operator<<(std::ostream&, const MainControl&);
};


// -----------------------------------------------------------

#endif
