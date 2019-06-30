//
// Created by w10 on 6/12/2019.
//
#include "assert.h"
#include "eurovision.h"
#include <vector>

///Participant Constructor
Participant::Participant(string state,string song,int length,string singer) {
    this->state_name = state;
    this->song_name = song;
    this->song_length = length;
    this->singer_name = singer;
    this->is_registerd = 0;
}

///Participant Destructor- Empty
Participant::~Participant() {
}

///returns the state's name of the "this" participant
string Participant::state() const {
    return this->state_name;
}

///returns the song of the "this" participant
string Participant::song() const {
    return this->song_name;
}

///returns the timelength of the "this" participant
int Participant::timeLength() const {
    return this->song_length;
}

///returns the singer's name of the "this" participant
string Participant::singer() const {
    return this->singer_name;
}

///overloading the << operator for Participant
std::ostream& operator<<(std::ostream& os, const Participant& participant) {
    os << "[" + participant.state() + "/" + participant.song() + "/" << participant.timeLength()
       << "/" + participant.singer() + "]";
    return os;
}

///returns whether "this" participant is registered or not
int Participant::isRegistered() const {
    return is_registerd;
}

///updates the details of "this" participant
void Participant::update(string new_song, int new_time, string new_singer) {
    if (is_registerd == 0) {
        if (new_song != "") {
            song_name = new_song;
        }
        if (new_time != 0) {
            song_length = new_time;
        }
        if (new_singer != "") {
            singer_name = new_singer;
        }
    }
}

///changes the registration status of "this" participant
void Participant::updateRegistered(bool new_status) {
    is_registerd = new_status;
}

///MainControl Constructor
MainControl::MainControl(int max_time, int max_participants, int max_votes):
        control_participants(new Participant*[max_participants]), regular_votes(new int[max_participants]),
        judge_votes(new int[max_participants]) {

    this->max_time = max_time;
    this->max_participants = max_participants;
    this->max_votes = max_votes;
    phase = Registration;

    for (int i = 0; i < max_participants; i++) {
        this->control_participants[i] = NULL;
    }
    for (int i = 0; i < max_participants; i++) {
        this->regular_votes[i] = 0;
    }
    for (int i = 0; i < max_participants; i++) {
        this->judge_votes[i] = 0;
    }
}

///MainControl Destructor
MainControl::~MainControl() {
    for (int i = 0; i < this->max_participants; i++) {
        if (this->control_participants[i] != NULL) {
            this->control_participants[i]->updateRegistered(false);
        }
        this->control_participants[i] = NULL;
    }
    delete[] this->control_participants;
    delete[] this->regular_votes;
    delete[] this->judge_votes;
}

///returning the current phase of "this" maincontrol object
string getPhase(int phase) {
    if (phase == 0) {
        return "Registration";
    }
    if (phase == 1) {
        return "Contest";
    }
    return "Voting";
}

///overloading the << operator for MainControl
std::ostream& operator<<(std::ostream& os, MainControl& main_control) {
    os << "{" << endl << getPhase(main_control.phase) << endl;
    if (main_control.phase == Registration) {
        for (int i = 0; i < main_control.max_participants; i++) {
            if (main_control.control_participants[i] != NULL) {
                os << *(main_control.control_participants[i]) << endl;
            }
        }
    } else if (main_control.phase == Voting) {
        for (int i = 0; i < main_control.max_participants; i++) {
            if (main_control.control_participants[i] != NULL) {
                os << main_control.control_participants[i]->state() + " : Regular(" << main_control.regular_votes[i]
                   << ") Judge(" << main_control.judge_votes[i] << ")" << endl;
            }
        }
    }
    os << "}" << endl;
    return os;
}

///returns how many participants are in "this" maincontrol
int MainControl::getSize() const {
    int size = 0;
    for (int i = 0; i < this->max_participants; i++) {
        if (this->control_participants[i] != NULL) {
            size++;
        }
    }
    return size;
}

///checks whether the received state exists in "this" maincontrol
bool MainControl::stateExists(const MainControl& main_control, string state) {
    for (int i = 0; i < main_control.max_participants; i++) {
        if (main_control.control_participants[i] != NULL) {
            if ((main_control.control_participants[i])->state() == state) {
                return true;
            }
        }
    }
    return false;
}

///overloading the += operator for MainControl
///adds a new participant to "this" maincontrol
MainControl& MainControl::operator+=(Participant& participant) {
    if (this->phase == Registration) {
        if (this->getSize() != this->max_participants) {
            if (participant.isRegistered() == 0) {
                if (participant.state() != "" && participant.song() != "" && participant.singer() != "" &&
                    participant.timeLength() <= this->max_time) {
                    if (!(this->stateExists(*this, participant.state()))) {
                        //  cout<< "My test:" << *this <<endl;
                        for (int i = 0; i < this->max_participants; i++) {
                            if (this->control_participants[i] == NULL) {
                                this->control_participants[i] = &participant;
                                (participant).updateRegistered(true);
                                int size = this->getSize();
                                Participant **arr = this->sortParticipants();
                                int j;
                                for (j = 0; j < size; j++) {
                                    this->control_participants[j] = arr[j];
                                    arr[j] = NULL;
                                }
                                for (int k = j; k < this->max_participants; k++) {
                                    this->control_participants[k] = NULL;
                                }
                                delete[] arr;
                                return *this;
                            }
                        }

                    }
                }
            }
        }
    }
    return *this;
}

///one round of bubble sort for the participants
int bubble(Participant** arr, int n) {
    int i, swapped = 0;
    for (i = 1; i < n; i++) {
        if (arr[i - 1]->state().compare(arr[i]->state()) > 0) {
            swapped = 1;
            swap(arr[i - 1], arr[i]);
        }
    }
    return swapped;
}

///sorts the participants Lexicographically with Bubble Sort method
void MainControl::sortHelp(Participant** arr, int n) {
    int not_sorted = 1;
    while ((n > 1) && not_sorted)
        not_sorted = bubble(arr, n--);
}

///sorts the participants Lexicographically
Participant** MainControl::sortParticipants() {
    int size = this->getSize();
    Participant **arr = NULL;
    if (size != 0) {
        arr = new Participant *[size];
        int j = 0;
        //building a new arr of pointers to the participants
        for (int i = 0; i < this->max_participants; i++) {
            if (this->control_participants[i] != NULL) {
                arr[j] = this->control_participants[i];
                j++;
            }
        }
        sortHelp(arr, size);
    }
    return arr;
}

///overloading the -= operator for MainControl
///removes the recieved participant from "this" maincontrol
MainControl& MainControl::operator-=(Participant &participant) {
    if (this->phase == Registration) {
        if (participant.isRegistered() == 1) {
            if ((this->stateExists(*this, participant.state()))) {
                for (int i = 0; i < max_participants; i++) {
                    if (this->control_participants[i] != NULL) {
                        if (this->control_participants[i]->state() == participant.state()) {
                            participant.updateRegistered(false);
                            this->control_participants[i] = NULL;
                            int size = this->getSize();
                            Participant **arr = this->sortParticipants();
                            int j;
                            for (j = 0; j < size; j++) {
                                this->control_participants[j] = arr[j];
                                arr[j] = NULL;
                            }
                            for (int k = j; k < this->max_participants; k++) {
                                this->control_participants[k] = NULL;
                            }
                            delete[] arr;
                            return *this;
                        }
                    }
                }
            }
        }
    }
    return *this;
}

///setting the current phase of "this" maincontrol object
void MainControl::setPhase(int new_phase) {
    if (this->phase - new_phase == -1) {
        phase++;
    }
}

///returns whether the received participant is a legal one
bool MainControl::legalParticipant(Participant &participant) const {
    if (participant.state() != "" && participant.song() != "" && participant.singer() != "" &&
        participant.timeLength() <= max_time) {
        return true;
    }
    return false;
}

///checks if the state is a participant in "this" maincontrol
bool MainControl::participate(const string str) {
    if (this->stateExists(*this, str)) {
        return true;
    }
    return false;
}

///creates a new voter -Voter Constructor-
Voter::Voter(string state, int type ) {
    this->state_name = state;
    this->type = type;
    this->counter = 0;
}

///returns the state's name of "this" voter
string Voter::state() const {
    return state_name;
}

///returns the type of "this" voter
int Voter::voterType() const {
    return type;
}

///returns how many times "this" voter has voted
int Voter::timesOfVotes() const {
    return counter;
}

///returns the suited score of the received rank
int rankToScore(int rank) {
    switch (rank) {
        case 0:
            return 12;
        case 1:
            return 10;
        case 2:
            return 8;
        case 3:
            return 7;
        case 4:
            return 6;
        case 5:
            return 5;
        case 6:
            return 4;
        case 7:
            return 3;
        case 8:
            return 2;
    }
    return 1;
}

///overloading the += operator for MainControl
///adds a new vote to "this" maincontrol
MainControl& MainControl::operator +=(Vote vote) {
    if (this->participate(vote.voter->state())) {
        if (vote.voter->voterType() == Regular) {
            if (vote.voter->state() != vote.state[0]) {
                if (participate(vote.voter->state())) {
                    if (vote.voter->timesOfVotes() < max_votes) {
                        ++*vote.voter;
                        int index = getIndex(vote.state[0]);
                        if (index != -1) {
                            this->regular_votes[index]++;
                        }
                    }
                }
            }
        } else {
            if (vote.voter->timesOfVotes() == 0) {
                ++*vote.voter;
                for (int i = 0; i < 10; i++) {
                    if (vote.voter->state() != vote.state[i]) {
                        if (participate(vote.state[i])) {
                            int score = rankToScore(i);
                            int index = getIndex(vote.state[i]);
                            if (index != -1) {
                                this->judge_votes[index] += score;
                            }
                        }
                    }
                }
            }
        }
    }
    delete[] vote.state;
    return *this;
}

///creates a new vote
Vote::Vote(Voter& new_voter, string state1, string state2, string state3, string state4, string state5 , string state6,
        string state7, string state8, string state9, string state10):
         state(new string[10]) {
    for (int i = 0; i < 10; i++) {
        state[i] = "";
    }
    if (new_voter.voterType() == Regular && state1 != "" && state2 == "") {
        voter = &new_voter;
        state[0] = state1;
    } else if (new_voter.voterType() == Judge) {
        voter = &new_voter;
        state[0] = state1;
        state[1] = state2;
        state[2] = state3;
        state[3] = state4;
        state[4] = state5;
        state[5] = state6;
        state[6] = state7;
        state[7] = state8;
        state[8] = state9;
        state[9] = state10;
    }
}

///Voter Destructor - Empty
Vote::~Vote() {
}

///returns the voter type of the recieved voter
string getVoterType(const Voter& voter) {
    if (voter.voterType() == All) {
        return "ALL";
    }
    if (voter.voterType() == Regular) {
        return "Regular";
    }
    return "Judge";
}

///overloading << operator for Voter
std::ostream& operator<<(std::ostream& os, const Voter& voter) {
    os << "<" + voter.state() + "/" + getVoterType(voter) + ">";
    return os;
}

///adds the votes amount of "this" voter by one vote
Voter& Voter::operator++() {
    this->counter++;
    return *this;
}

///returns received state's index from the participants array of "this" maincontrol
int MainControl::getIndex(string state) {
    for (int i = 0; i < max_participants; i++)
        if (control_participants[i] != NULL) {
            if (control_participants[i]->state() == state) {
                return i;
            }
        }
    return -1;
}


//////////////////////part 2////

/// MainControl::Iterator Constructor
 MainControl::Iterator::Iterator(const MainControl* main_control, int index):
 main_control(main_control), index(index) {
}

///returns the participant object at which "this" iterator is pointing
const Participant& MainControl::Iterator::operator*() const {
    //assert(index >= 0 && index < main_control->getSize());
    return *(this->main_control->control_participants[index]);
}

///overloading the ++ operator for MainControl::Iterator, moves the iterator by one step
MainControl::Iterator& MainControl::Iterator::operator++() {
    ++index;
    return *this;
///return *(Iterator (this.main_control, ++index));
}

///overloading the < operator for MainControl::Iterator
///checks which iterator has a bigger index from "this" and the received one
bool MainControl::Iterator::operator < (const Iterator& it) const {
    if (index >= 0 && index < main_control->getSize()) {
        return index < it.index;
    }
    return false;
}

///overloading the == operator for MainControl::Iterator
///checks if "this" iterator and the received one have the same index
bool MainControl::Iterator::operator==(const Iterator& it) const {
    if (this->main_control == it.main_control) {
        return index == it.index;
    }
    return false;
}

///returns an iterator pointing to the first participant
MainControl::Iterator MainControl::begin() const {
    return Iterator(this, 0);
}

///returns an iterator pointing one step after the last participant
MainControl::Iterator MainControl::end() const {
    return Iterator(this, this->getSize());
}

/// MainControl::Iterator Constructor - Empty
MainControl::Iterator::Iterator() :
        index(0) {
    main_control = NULL;
}

///a predicate class used to return the bigger int
class nextIsBigger {
public:
    ///returns the bigger int
    bool operator()(int num1, int num2) const {
        return num1 < num2;
    }
};


///generic get function: returns the object at the i rank from a container
template<typename Iterator, typename Predicate>
Iterator get (Iterator first , Iterator last , Predicate pred , int i) {
    int size = 0;
    Iterator current = first;
    while (!(current == last)) {
        size++;
        ++current;
    }
    if (i < 1 || i > size) {
        return last;
    }
    int *arr = new int[size];
    int index = 0;
    for (Iterator it1 = first; !(it1 == last); ++it1) {
        int counter = 0;
        for (Iterator it2 = first; !(it2 == last); ++it2) {
            if (!(it1 == it2) && pred(*it1, *it2)) {
                counter++;
            }
        }
        arr[index] = counter;
        index++;
    }
    int index_result = 0;
    for (int k = 0; k < size; k++) {
        if (arr[k] == i - 1) {
            index_result = k;
            break;
        }
    }
    delete[] arr;
    Iterator result = first;
    while (index_result > 0) {
        ++result;
        index_result--;
    }
    return result;
}

///returns the maxinmum number from an int array
int numEqualBefore(int * arr, int index) {
    if (index == 0) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i <= index; i++) {
        if (arr[i] >= arr[index]) {
            count++;
        }
    }
    return count;
}

///overloading the operator ()
///returns the state's name at the i rank by votes
int getIndexOfMax(int * arr , int size) {
    int index = -1, max = -1;
    for (int i = size - 1; i >= 0; i--) {
        if (arr[i] > max) {
            max = arr[i];
            index = i;
        }
    }
    return index;
}


string MainControl::operator()(int i, int voter_type) const {
    int size = this->getSize();
    if (i < 1 || i > size) {
        return "";
    }
    nextIsBigger pred;
    vector<int> vec(size, 0);
    int *copy_arr = new int[size];
    string result = "";
    if (voter_type == Regular) {
        for (int k = 0; k < size; ++k) {
            copy_arr[k] = this->regular_votes[k];
        }
    } else if (voter_type == Judge) {
        for (int k = 0; k < size; ++k) {
            copy_arr[k] = this->judge_votes[k];
        }
    } else {
        for (int k = 0; k < size; ++k) {
            copy_arr[k] = this->regular_votes[k] + this->judge_votes[k];
        }
    }
    int value = size;
    int index = getIndexOfMax(copy_arr, size);
    while (index != -1) {
        copy_arr[index] = -1;
        vec[index] = value;
        value--;
        index = getIndexOfMax(copy_arr, size);
    }
    vector<int>::iterator result_get = get(vec.begin(), vec.end(), pred, i);
    int place = 0;
    vector<int>::iterator iterator_help = vec.begin();
    while (iterator_help != result_get) {
        place++;
        ++iterator_help;
    }
    result = this->control_participants[place]->state();
    delete[] copy_arr;
    return result;
}
