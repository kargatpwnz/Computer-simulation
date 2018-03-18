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
    std::cout << "ID " << client.id << std::endl;
    std::cout << "Waiting time " << client.queueing_time << std::endl;
    std::cout << "--------------" << std::endl;
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
  std::uniform_real_distribution<double> double_distr(0, mean_);
  std::uniform_real_distribution<double> exp_distr(0, 1);

  const double min_value = double_distr(gen);
  int id = 0;

  for (auto &client : clients_) {
    switch (type_in) {
      case TIME_CONST:
        client.time_in = min_value;
        break;
      case TIME_UNIFORM:
        client.time_in = double_distr(gen);
        break;
      case TIME_EXPONENT:
        client.time_in = -1 * mean_ * log(exp_distr(gen));
        break;
    }

    switch (type_out) {
      case TIME_CONST:
        client.time_out = mean_ * 0.9;
        break;
      case TIME_UNIFORM:
        double_distr = std::uniform_real_distribution<double>(client.time_in,
                                                              mean_ * 0.9 * 2 - client.time_in);

        client.time_out = double_distr(gen);
        std::cout << client.time_in << " " << client.time_out << std::endl;
        break;
      case TIME_EXPONENT:
        client.time_out = -1 * mean_ * 0.9 * log(exp_distr(gen));
//        std::cout << client.time_in << " " << client.time_out << std::endl;
        break;
    }
    client.id = id++;
    client.queueing_time = 0;
  }
}

QueueingSystem::~QueueingSystem() {

}
