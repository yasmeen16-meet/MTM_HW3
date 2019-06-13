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
        control_participants(new Participant*[max_participants]) {

    this->max_time = max_time;
    this->max_participants = max_participants;
    this->max_votes = max_votes;
    phase = Registration;

    for (int i=0; i<max_participants; i++){
        this->control_participants[i] = NULL;
    }
}

MainControl::~MainControl() {
    for (int i = 0; i < this->max_participants; i++) {
        delete this->control_participants[i];
    }
    delete[] this->control_participants;
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
//*******************************

std::ostream& operator<<(std::ostream& os, const MainControl& main_control) {
    os << "{"  << endl << getPhase(main_control.phase)<<endl;
    for (int i=0; i< main_control.max_participants; i++)
    {
        if(main_control.control_participants[i]!=NULL)
        {
            os << *(main_control.control_participants[i])<<endl;
        }
    }
    os << "}";
    return os;
}

int MainControl::getSize(const MainControl& main_control) {
    int size = 0;
    for (int i = 0; i < main_control.max_participants; i++) {
        if (main_control.control_participants[i] != NULL) {
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

MainControl& MainControl::operator+=(Participant& participant) {
    if (this->phase == Registration) {

        if (getSize(*this) != this->max_participants) {
            if (participant.isRegistered() == 0) {
                if (participant.state() != "" && participant.song() != "" && participant.singer() != "" &&
                    participant.timeLength() <= this->max_time) {
                    if (!(this->stateExists(*this, participant.state()))) {
                        for (int i = 0; i < this->max_participants; i++) {
                            if (this->control_participants[i] == NULL) {
                                this->control_participants[i] = &participant;
                                // this->control_participants[i] = &participant;
                                //(participant).updateRegistered(true);
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
