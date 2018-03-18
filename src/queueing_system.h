//
// Created by na1l on 04.03.18.
//

#ifndef MODELING_QUEUEING_SYSTEM_H
#define MODELING_QUEUEING_SYSTEM_H

#include <set>
#include <queue>

enum Time {
  TIME_CONST,
  TIME_UNIFORM,
  TIME_EXPONENT
};

enum EventType {
  EVENT_ENQUEUE,
  EVENT_DEQUEUE
};

struct Client {
  double time_in;
  double time_out;
  double queueing_time;

  int id;
};

struct Event {
  double time;
  int client_id;

  enum EventType type;

  friend bool operator<(const Event &e1, const Event &e2) {
    return e1.time < e2.time;
  }
};

class QueueingSystem {
 public:
  QueueingSystem(double mean, enum Time type_in, enum Time type_out);
  void PrintEventList();
  void Start();
  void PrintStartList();
  double CalculateAvgQueueingTime();

 private:
  void FillClients(double mean, enum Time type_in, enum Time type_out);
  void FillEvents();
  void GenerateTime(int type_in, int type_out);

  struct Client clients_[10];
  std::multiset<struct Event> enqueued_list_;
  std::multiset<struct Event> processing_events_;
  std::queue<int> queue_;
  double mean_;

};

#endif //MODELING_QUEUEING_SYSTEM_H
