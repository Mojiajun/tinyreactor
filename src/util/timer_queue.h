//
// Created by mojiajun on 2020/2/6.
//
#ifndef TINYREACTOR_SRC_UTIL_TIMER_QUEUE_H_
#define TINYREACTOR_SRC_UTIL_TIMER_QUEUE_H_

#include <map>
#include <memory>
#include <vector>

#include "../channel.h"
#include "../callback.h"
#include "time_stamp.h"
#include "timer_id.h"

namespace tinyreactor {

class TimerQueue {
 public:
  TimerQueue(const TimerQueue &) = delete;
  TimerQueue &operator=(const TimerQueue &) = delete;

  explicit TimerQueue(EventLoop *loop);
  ~TimerQueue();

  /// timercb
  /// when ???
  /// interval
  TimerId addTimer(TimerCallback timercb,
                    Timestamp when,
                    double interval);

  void cancelTimer();

 private:
  void addTimerInLoop(Timer *timer);

  // 被EventLoop持有?用loop_能给EventLoop里面添加Functor
  // 用raw指针万一指针失效了怎么办
  // 因为EventLoop用std::unique_ptr<>持有TimerQueue.所以这个loop指针应该是一直有效的
  // 因为EventLoop的生命周期更长
  EventLoop *loop_;
  // 每个TimerQueue一个timerfd
  const int timerfd_;
  // 管理timerfd_的Channel
  std::unique_ptr<Channel> timerfdChannel_;

  // 可能会出现两个Timer的Timestamp相同的情况
  std::map<Timestamp, std::vector<std::unique_ptr<Timer>>> timers_;

};

}

#endif //TINYREACTOR_SRC_UTIL_TIMER_QUEUE_H_
