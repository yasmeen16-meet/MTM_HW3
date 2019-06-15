//
// Created by w10 on 6/12/2019.
//

#include "eurovision.h"

Participant::Participant(string state,string song,int length,string singer) {
    this->state_name = state;
    this->song_name = song;
    this->song_length = length;
    this->singer_name = singer;
    this->is_registerd = 0;
}

Participant::~Participant() {

}

string Participant::state() const {
    return this->state_name;
}

string Participant::song() const {
    return this->song_name;
}

int Participant::timeLength() const {
    return this->song_length;
}

string Participant::singer() const {
    return this->singer_name;
}

std::ostream& operator<<(std::ostream& os, const Participant& participant) {
    os << "[" + participant.state() + "/" + participant.song() + "/" << participant.timeLength()
       << "/" + participant.singer() + "]";
    return os;
}

int Participant::isRegistered() const {
    return is_registerd;
}

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

void Participant::updateRegistered(bool new_status) {
    is_registerd = new_status;
}

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
MainControl::~MainControl() {
    for (int i = 0; i < this->max_participants; i++) {
        this->control_participants[i] = NULL;
    }
    delete[] this->control_participants;
    delete [] this->regular_votes;
    delete[] this->judge_votes;
}

string getPhase(int phase){
    if (phase == 0){
        return "Registeration";
    }
    if (phase == 1){
        return "Contest";
    }
    return "Voting";
}
/////////**************///////////
std::ostream& operator<<(std::ostream& os, MainControl& main_control) {
    os << "{" << endl << getPhase(main_control.phase) << endl;
    if (main_control.phase == Registration) {
        for (int i = 0; i < main_control.max_participants; i++) {
            if (main_control.control_participants[i] != NULL) {
                os << *(main_control.control_participants[i]) << endl;
            }
        }
    }

    else if (main_control.phase == Voting){
        for (int i=0; i< main_control.max_participants; i++){
            if (main_control.control_participants[i] != NULL){
                os << main_control.control_participants[i]->state() + " : Regular(" << main_control.regular_votes[i]
                   << ") Judge(" << main_control.judge_votes[i]<< ")" << endl;
            }
        }
    }
    os << "}" << endl;
    return os;
}

int MainControl::getSize() const {
    int size = 0;
    for (int i = 0; i < this->max_participants; i++) {
        if (this->control_participants[i] != NULL) {
            size++;
        }
    }
    return size;
}

bool MainControl::stateExists(const MainControl& main_control, string state) {
    for (int i = 0; i < main_control.max_participants; i++) {
        if (main_control.control_participants[i] != NULL) {
            if((main_control.control_participants[i])->state()==state){
                return true;
            }
        }
    }
    return false;
}

/////////**************///////////
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
                                Participant ** arr = this->sortParticipants();
                                int j;
                                for (j=0; j<size; j++){
                                    this->control_participants[j] = arr[j];
                                    arr[j] = NULL;
                                }
                                for (int k=j; k<this->max_participants; k++){
                                    this->control_participants[k] = NULL;
                                }
                                delete [] arr;
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

/////////**************///////////


///////////Yasmeen////////////

int bubble(Participant** arr, int n) {
    int i, swapped = 0;
    for(i = 1; i < n; i++) {
        if (arr[i - 1]->state().compare(arr[i]->state()) > 0) {
            swapped = 1;
            swap(arr[i-1], arr[i]);
        }
    }
    return swapped;
}

void MainControl::sortHelp(Participant** arr, int n) {
    int not_sorted = 1;
    while( (n > 1) && not_sorted )
        not_sorted = bubble(arr, n--);
}

Participant** MainControl::sortParticipants() {
    int size = this->getSize();
    Participant** arr=NULL;
    if (size != 0){
        arr = new Participant*[size];
        int j=0;
        //building a new arr of pointers to the participants
        for (int i=0; i < this->max_participants; i++){
            if (this->control_participants[i]!=NULL){
                arr[j] = this->control_participants[i];
                j++;
            }
        }
        sortHelp(arr,size);
    }
    return arr;
}


////////////Yasmeen/////////

/////////**************///////////
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
                            Participant ** arr = this->sortParticipants();
                            int j;
                            for (j=0; j<size; j++){
                                this->control_participants[j] = arr[j];
                                arr[j] = NULL;
                            }
                            for (int k=j; k<this->max_participants; k++){
                                this->control_participants[k] = NULL;
                            }
                            delete [] arr;
                            return *this;
                        }
                    }
                }
            }

        }
    }
    return *this;
}
/////////**************///////////

void MainControl::setPhase(int new_phase) {
    if (this->phase - new_phase==-1){
        phase++;
    }
}


bool MainControl::legalParticipant(Participant &participant) const {
    if (participant.state()!=""&& participant.song()!=""&&participant.singer()!=""&&participant.timeLength()<=max_time){
        return true;
    }
    return false;
}

bool MainControl::participate(const string str) {
    if (this->stateExists(*this, str)) {
        return true;
    }
    return false;
}

Voter::Voter(string state, int type ) {
    this->state_name=state;
    this->type=type;
    this->counter=0;
}

string Voter::state() const {
    return state_name;
}

int Voter::voterType() const {
    return type;
}

int Voter::timesOfVotes() const {
    return counter;
}

int rankToScore(int rank){

    switch (rank){
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

MainControl& MainControl::operator +=(Vote vote) {
    if (this->participate(vote.voter->state())) {
        if (vote.voter->voterType() == Regular) {
            if (vote.voter->state() != vote.state[0]) {
                if (participate(vote.voter->state())) {

                    if (vote.voter->timesOfVotes() < max_votes) {
                        ++*vote.voter;
                        //cout<< "counter" << vote.voter->timesOfVotes()<<endl;
                        int index = getIndex(vote.state[0]);
                        this->regular_votes[index]++;
                    }
                }
            }
        } else {
            if (vote.voter->timesOfVotes() == 0) {
                for (int i = 0; i < 10; i++) {
                    if (vote.voter->state() != vote.state[i]) {
                        if (participate(vote.state[i])) {
                            int score = rankToScore(i);
                            int  index = getIndex(vote.state[i]);
                            this->judge_votes[index]+=score;
                            ++*vote.voter;
                        }
                    }
                }
            }
        }
    }
    return *this;
}
Vote::Vote(Voter& new_voter, string state1, string state2, string state3, string state4, string state5 , string state6,
        string state7, string state8, string state9, string state10):
         state(new string[10]){
    for(int i = 0 ; i <10 ; i++){
        state[i] ="";
    }
    if (new_voter.voterType()==Regular &&state1!="" && state2 == ""){
        voter= &new_voter;
        state[0]=state1;
    } else if (new_voter.voterType()==Judge){
        voter= &new_voter;
        state[0]=state1;
        state[1]=state2;
        state[2]=state3;
        state[3]=state4;
        state[4]=state5;
        state[5]=state6;
        state[6]=state7;
        state[7]=state8;
        state[8]=state9;
        state[9]=state10;
    }

}
Vote::~Vote() {
    this->voter = NULL;
}

string getVoterType(const Voter& voter){
    if (voter.voterType()==0){
        return "ALL";
    }
    if (voter.voterType()==1){
        return "Regular";
    }
    return "Judge";
}

std::ostream& operator<<(std::ostream& os, const Voter& voter){
    os << "<" +voter.state() + "/" + getVoterType(voter) +">" ;
    return os;
}


Voter& Voter::operator++() {
    this->counter++;
    return *this;
}

int MainControl::getIndex(string state) {
    for(int i=0 ; i< max_participants ; i++){
        if (control_participants[i]!=NULL){
            if (control_participants[i]->state()==state){
                return i;
            }
        }
    }
    return  -1;
}