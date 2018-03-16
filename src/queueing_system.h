//
// Created by na1l on 04.03.18.
//

#ifndef MODELING_QUEUEING_SYSTEM_H
#define MODELING_QUEUEING_SYSTEM_H

#include <set>
#include <queue>

enum Time {
  TIME_CONST,
  TIME_EQUAL,
  TIME_EXPONENT
};

enum Event_type {
  EVENT_ENQUEUE,
  EVENT_DEQUEUE
};

struct client {
  double time_in;
  double time_out;
  double queueing_time;

  int id;
};

struct event {
  double time;
  int client_id;

  int type;

  friend bool operator<(const event &e1, const event &e2) {
    return e1.time < e2.time;
  }

  friend bool operator==(const event &e1, const event &e2) {
    return e1.time == e2.time &&
        e1.client_id == e2.client_id &&
        e1.type == e2.type;
  }

};

class QueueingSystem {
 public:
  QueueingSystem();
  void PrintEventList();
  void Start();
  void PrintStartList();

 private:
  void FillClients();
  void FillEvents();

  struct client clients_[3];

  std::set<struct event> event_list_;
  std::set<struct event> event_start_;
  std::queue<int> queue_;

};

#endif //MODELING_QUEUEING_SYSTEM_H
