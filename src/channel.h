//
// Created by mojiajun on 2019/9/9.
//

#ifndef SRC_CHANNEL_H_
#define SRC_CHANNEL_H_

#include <functional>

namespace tinyreactor {

class EventLoop;

// Channel 负责事件分发
// 每个Channel只负责一个fd
class Channel {
 public:
  using EventCallback = std::function<void()>;

  Channel(EventLoop *loop, int fd);
  ~Channel() = default;

  Channel(const Channel &) = delete;
  Channel &operator=(const Channel &) = delete;

  void handleEvent();

  int events() const { return events_; }
  void set_events(int events) { events_ = events; }
  int revents() const { return revents_; }
  void set_revents(int revents) { revents_ = revents; }
  void set_fd(int fd) { fd_ = fd; }
  int fd() const { return fd_; }

  void remove();  // 这个API设计的...感觉并不好

  void enableReading() {
      events_ |= kReadEvent;
      update();
  }
  void disableReading() {
      events_ &= ~kReadEvent;
      update();
  }
  void enableWriting() {
      events_ |= kWriteEvent;
      update();
  }
  void disableWriting() {
      events_ &= ~kWriteEvent;
      update();
  }
  void disableAll() {
      events_ = kNoneEvent;
      update();
  }

  bool isMonitoringWritable() { return events_ & kWriteEvent; }
  bool isMonitoringReadable() { return events_ & kReadEvent; }

  bool isNoneEvent() const;

  void setReadCallback(EventCallback cb) { readCallback_ = std::move(cb); }
  void setWriteCallback(EventCallback cb) { writeCallback_ = std::move(cb); }

  static const int kNoneEvent;
  static const int kReadEvent;
  static const int kWriteEvent;
 private:

  void update();

  // 这个Channel属于哪个loop
  EventLoop *ownerLoop_;

  int fd_;
  // channel感兴趣的事件集合
  int events_;
  // 用于epoll_wait()返回后填充, r代表return
  int revents_;

  EventCallback readCallback_;
  EventCallback writeCallback_;
};

}
#endif  // SRC_CHANNEL_H_
