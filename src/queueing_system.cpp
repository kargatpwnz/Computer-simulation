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
//  clients_[0].id = 0;
//  clients_[0].time_in = 2.2;
//  clients_[0].time_out = 2.7;
//  clients_[0].queueing_time = 0;
//
//  clients_[1].id = 1;
//  clients_[1].time_in = 1.4;
//  clients_[1].time_out = 0.7;
//
//  clients_[2].id = 2;
//  clients_[2].time_in = 1.6;
//  clients_[2].time_out = 1.2;

  clients_[0].id = 0;
  clients_[0].time_in = 1.2;
  clients_[0].time_out = 0.8;
  clients_[0].queueing_time = 0;

  clients_[1].id = 1;
  clients_[1].time_in = 2.7;
  clients_[1].time_out = 1;
  clients_[1].queueing_time = 0;


  clients_[2].id = 2;
  clients_[2].time_in = 2.1;
  clients_[2].time_out = 1.2;
  clients_[2].queueing_time = 0;

}

void QueueingSystem::FillEvents() {
  for (auto &client : clients_) {
    struct event event;

    event.client_id = client.id;
    event.time = client.time_in;
    event.type = EVENT_ENQUEUE;

    if (event_list_.empty()) {
      event_list_.insert(event);
    } else {
      double time = client.time_in + event_list_.rbegin()->time;
      client.time_in = time;
      event.time = time;
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
    struct event new_event;
    int id = event.client_id;

    // Enqueueing client
    if (running != id &&
        event.type == EVENT_ENQUEUE) {
      queue_.push(id);
      continue;
    }

    if (event.type == EVENT_DEQUEUE && queue_.empty()) {
      running += 1;
      continue;
    }

    if (id == running &&
        event.type == EVENT_DEQUEUE) {

      // Changing running to next client
      if (!queue_.empty()) {
        running = queue_.front();
        clients_[running].queueing_time = event.time - clients_[running].time_in;
        queue_.pop();
      }

      // If event is last add to list and exit
      if (event.type == EVENT_DEQUEUE &&
          event.client_id == event_start_.rbegin()->client_id) {

        clients_[running].time_in = event.time;
        new_event.time = event.time + clients_[running].time_out;
        new_event.client_id = running;
        new_event.type = EVENT_DEQUEUE;

        event_start_.insert(new_event);
        break;
      }

      clients_[running].time_in = event.time;
      new_event.time = event.time + clients_[running].time_out;
      new_event.client_id = running;
      new_event.type = EVENT_DEQUEUE;

      event_start_.insert(new_event);
      continue;
    }
    new_event.client_id = id;
    new_event.time = event.time + clients_[id].time_out;
    new_event.type = EVENT_DEQUEUE;
    event_start_.insert(new_event);
  }
}

void QueueingSystem::PrintStartList() {
  std::cout << "ID\tTIME\tTYPE" << std::endl;
  for (auto _event : event_start_) {
    std::cout << _event.client_id << "\t"
              << _event.time << "\t\t"
              << _event.type << std::endl;

  }

  std::cout << std::endl;
  for (auto client : clients_) {
    std::cout << "ID " << client.id << std::endl;
    std::cout << "Waiting time " << client.queueing_time << std::endl;
    std::cout << "--------------" << std::endl;
  }
}
