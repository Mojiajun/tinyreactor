//
// Created by mojiajun on 2019/9/12.
//

#ifndef SRC_TCPSERVER_H_
#define SRC_TCPSERVER_H_

#include <functional>
#include <map>
#include <memory>
#include <string>

#include "callback.h"
#include "acceptor.h"  // 定义std::unique<Acceptor> acceptor_;需要

namespace tinyreactor {

class EventLoop;
class InetAddress;
class Buffer;

class TcpServer {
 public:
  TcpServer(const TcpServer &) = delete;
  TcpServer &operator=(const TcpServer &) = delete;
  TcpServer(EventLoop *loop, const InetAddress &listenAddr, std::string servername);
  ~TcpServer() = default;

  void startListen() {
      acceptor_->listen();
  }
  void newConnection(int connfd, const InetAddress &peerAddr);
  void setConnectionCallback(const ConnectionCallback &cb) {
      connectionCallback_ = cb;
  }
  void setMessageCallback(const MessageCallback &cb) {
      messageCallback_ = cb;
  }
  std::string ipPort() const {
      return listenIpPort_;
  }
  std::string tcp_server_name() const {
      return servername_;
  }

 private:
  /// Acceptor所在的eventloop
  EventLoop *loop_;
  const std::string listenIpPort_;
  const std::string servername_;
  int nextConnId_;

  std::unique_ptr<Acceptor> acceptor_;  // 直接用Acceptor不行吗?
  ConnectionCallback connectionCallback_;
  MessageCallback messageCallback_;

  /// TcpServer里需要保存从连接名字到TcpConnection的映射
  std::map<std::string, TcpConnectionPtr> connections_;
};

}
#endif //SRC_TCPSERVER_H_
