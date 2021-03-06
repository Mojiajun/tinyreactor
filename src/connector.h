//
// Created by 莫佳骏 on 2019/9/12.
//

#ifndef SINGLE_THREAD_REACTOR_SRC_CONNECTOR_H_
#define SINGLE_THREAD_REACTOR_SRC_CONNECTOR_H_

#include "inet_address.h"

namespace tinyreactor {

class EventLoop;

class Connector {
 public:
  Connector(EventLoop *loop, const InetAddress &serverAddr);
 private:
  EventLoop *loop_;
  InetAddress serverAddr_;  // 这种光有前向声明不行吧?
};

}
#endif //SINGLE_THREAD_REACTOR_SRC_CONNECTOR_H_
