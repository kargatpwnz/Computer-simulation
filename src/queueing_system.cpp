//
// Created by na1l on 04.03.18.
//

#include <iostream>
#include "queueing_system.h"

QueueingSystem::QueueingSystem() {
  FillClients();
  FillEvents();
  event_start_ = event_list_;
}

void QueueingSystem::FillClients() {
  clients_[0].id = 0;
  clients_[0].time_in = 2.2;
  clients_[0].time_out = 2.7;

  clients_[1].id = 1;
  clients_[1].time_in = 1.4;
  clients_[1].time_out = 0.7;

  clients_[2].id = 2;
  clients_[2].time_in = 1.6;
  clients_[2].time_out = 1.2;
}

void QueueingSystem::FillEvents() {
  for (auto client : clients_) {
    struct event event;

    event.client_id = client.id;
    event.time = client.time_in;
    event.type = enum_Event::EVENT_ENQUEUE;

    if (event_list_.empty()) {
      event_list_.insert(event);
    } else {
      event.time = client.time_in + event_list_.rbegin()->time;
      event_list_.insert(event);
    }
  }
}

void QueueingSystem::PrintEventList() {
  std::cout << "ID\tTIME\tTYPE" << std::endl;
  for (auto _event : event_list_) {
    std::cout << _event.client_id << "\t"
              << _event.time << "\t\t"
              << _event.type << std::endl;

  }
}

void QueueingSystem::Start() {
  int running = clients_[0].id;

  for (auto event : event_start_) {
    struct event e;
    int id = event.client_id;

    if (running != id && event.type == enum_Event::EVENT_ENQUEUE) {
      queue_.push(id);
      continue;
    }

    if (event.client_id == running &&
        event.type == enum_Event::EVENT_DEQUEUE) {

      if (!queue_.empty()) {
        running = queue_.front();
        queue_.pop();
      }

      if (event.type == enum_Event::EVENT_DEQUEUE &&
          event.client_id == event_start_.rbegin()->client_id) {

        e.time = event.time + clients_[running].time_out;
        e.client_id = running;
        e.type = enum_Event::EVENT_DEQUEUE;

        event_start_.insert(e);
        break;
      }
      e.time = event.time + clients_[running].time_out;
      e.client_id = running;
      e.type = enum_Event::EVENT_DEQUEUE;

      event_start_.insert(e);
      continue;
    }

    e.client_id = id;
    e.time = event.time + clients_[id].time_out;
    e.type = enum_Event::EVENT_DEQUEUE;
    event_start_.insert(e);

  }
}
void QueueingSystem::PrintStartList() {
  std::cout << "ID\tTIME\tTYPE" << std::endl;
  for (auto _event : event_start_) {
    std::cout << _event.client_id << "\t"
              << _event.time << "\t\t"
              << _event.type << std::endl;

  }
}
