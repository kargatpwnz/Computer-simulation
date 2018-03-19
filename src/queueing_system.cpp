//
// Created by na1l on 04.03.18.
//

#include <cmath>
#include <iostream>
#include <random>

#include "queueing_system.h"

QueueingSystem::QueueingSystem(double mean, enum Time type_in, enum Time type_out) {
  FillClients(mean, type_in, type_out);
  FillEvents();

  processing_events_ = enqueued_list_;
}

void QueueingSystem::PrintEventList() {
  std::cout << "ID\tTIME_IN\tTYPE" << std::endl;
  for (auto _event : enqueued_list_) {
    std::cout << _event.client_id << "\t"
              << _event.time << "\t"
              << _event.type << std::endl;
  }
}

void QueueingSystem::Start() {
  int running = clients_[0].id;

  for (auto event : processing_events_) {
    struct Event new_event;
    int id = event.client_id;

    if (event.type == EVENT_DEQUEUE) {
      // Line is empty, last Client is gone, changing to next Client
      if (queue_.empty()) {
        running++;
        continue;
      }

      // Changing running to next Client
      running = queue_.front();
      queue_.pop();

      // Calculating time in queue
      clients_[running].queueing_time = event.time - clients_[running].time_in;

      // If Event is last one then add to list and exit
      if (event.client_id == processing_events_.rbegin()->client_id) {
        clients_[running].time_in = event.time;
        new_event.time = event.time + clients_[running].time_out;
        new_event.client_id = running;
        new_event.type = EVENT_DEQUEUE;

        processing_events_.insert(new_event);
        break;
      }

      // Filling DEQUEUE Event, going to next Event
      new_event.time = event.time + clients_[running].time_out;
      new_event.client_id = running;
      new_event.type = EVENT_DEQUEUE;

      processing_events_.insert(new_event);
    } else {

      // Enqueueing Client
      if (running != id) {
        queue_.push(id);
        continue;
      }

      // Queue is empty, nobody is being processed. Calculating DEQUEUE time
      new_event.client_id = id;
      new_event.time = event.time + clients_[id].time_out;
      new_event.type = EVENT_DEQUEUE;
      processing_events_.insert(new_event);
    }
  }
}

void QueueingSystem::PrintStartList() {
  std::cout << "ID\tTIME\t\tTYPE" << std::endl;
  for (auto _event : processing_events_) {
    std::cout << _event.client_id << "\t"
              << _event.time << "\t\t"
              << _event.type << std::endl;

  }

  std::cout << std::endl;
  for (auto client : clients_) {
    std::cout << "ID " << client.id;
    std::cout << "\tWaiting time " << client.queueing_time << std::endl;
  }
}

double QueueingSystem::CalculateAvgQueueingTime() {
  double result = 0;

  for (auto client : clients_)
    result += client.queueing_time;
  return result / size_;
}

void QueueingSystem::FillClients(double mean, enum Time type_in, enum Time type_out) {
  mean_ = mean;

  if (type_in == TIME_CONST &&
      type_out == TIME_CONST) {
    throw -1;
  }

  switch (type_in) {
    case TIME_CONST:
      switch (type_out) {
        case TIME_UNIFORM:
          GenerateTime(TIME_CONST, TIME_UNIFORM);
          break;
        case TIME_EXPONENT:
          GenerateTime(TIME_CONST, TIME_EXPONENT);
          break;
      }
      break;
    case TIME_UNIFORM:
      switch (type_out) {
        case TIME_CONST:
          GenerateTime(TIME_UNIFORM, TIME_CONST);
          break;
        case TIME_UNIFORM:
          GenerateTime(TIME_UNIFORM, TIME_UNIFORM);
          break;
        case TIME_EXPONENT:
          GenerateTime(TIME_UNIFORM, TIME_EXPONENT);
          break;
      }
      break;
    case TIME_EXPONENT:
      switch (type_out) {
        case TIME_CONST:
          GenerateTime(TIME_EXPONENT, TIME_CONST);
          break;
        case TIME_UNIFORM:
          GenerateTime(TIME_EXPONENT, TIME_UNIFORM);
          break;
        case TIME_EXPONENT:
          GenerateTime(TIME_EXPONENT, TIME_EXPONENT);
          break;
      }
  }
}

void QueueingSystem::FillEvents() {
  for (auto &client : clients_) {
    struct Event event;

    event.client_id = client.id;
    event.time = client.time_in;
    event.type = EVENT_ENQUEUE;

    if (enqueued_list_.empty()) {
      enqueued_list_.insert(event);
    } else {
      double time = client.time_in + enqueued_list_.rbegin()->time;
      client.time_in = time;
      event.time = time;
      enqueued_list_.insert(event);
    }
  }
}

void QueueingSystem::GenerateTime(enum Time type_in, enum Time type_out) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> double_distr(0, 1);
  std::uniform_real_distribution<double> time_in_distr(0, 1);
  std::uniform_real_distribution<double> time_out_distr(0, 1);

  int id = 0;
  double min;

  // Configuring generators
  switch (type_in) {
    case TIME_CONST:
      time_in_distr = std::uniform_real_distribution<>(mean_, mean_);
      break;
    case TIME_UNIFORM:
      min = double_distr(gen);
      time_in_distr = std::uniform_real_distribution<>(min, mean_ * 2 - min);
      break;
  }

  switch (type_out) {
    case TIME_CONST:
      time_out_distr = std::uniform_real_distribution<>(mean_ * 0.9, mean_ * 0.9);
      break;
    case TIME_UNIFORM:
      min = double_distr(gen);
      time_out_distr = std::uniform_real_distribution<>(min, mean_ * 0.9 * 2 - min);
      break;
  }

  for (auto &client : clients_) {
    if (type_in == TIME_EXPONENT)
      client.time_in = -1 * mean_ * log(double_distr(gen));
    else
      client.time_in = time_in_distr(gen);

    if (type_out == TIME_EXPONENT)
      client.time_out = -1 * mean_ * 0.9 * log(double_distr(gen));
    else
      client.time_out = time_out_distr(gen);

    client.id = id++;
    client.queueing_time = 0;
  }
}

QueueingSystem::~QueueingSystem() {

}
