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

MainControl::MainControl(int max_time, int max_participants, int max_votes) {
    this->max_time=max_time;
    this->max_participants=max_participants;
    this->max_votes=max_votes;
    control_participants = new Participant[max_participants];
    phase= Registration;
}