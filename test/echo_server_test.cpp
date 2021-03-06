//
// Created by mojiajun on 2019/9/12.
//

#include <iostream>

#include "glog/logging.h"
#include "src/tcp_server.h"
#include "src/event_loop.h"
#include "src/inet_address.h"
#include "src/tcp_connection.h"


using std::placeholders::_1;
using std::placeholders::_2;

using namespace tinyreactor;

class EchoServer {
 public:
  EchoServer(EventLoop *loop, const InetAddress &listenAddr)
      : loop_(loop),
        server_(loop, listenAddr, "EchoServer") {
      server_.setConnectionCallback(
          std::bind(&EchoServer::onConnection, this, _1));
      server_.setMessageCallback(
          std::bind(&EchoServer::onMessage, this, _1, _2));
  }
  ~EchoServer() = default;

  void startListen() {
      server_.startListen();
  }
  // void stop();

 private:
  // 建立连接之后的回调函数, conn是std::shared_ptr<TcpConnection>的引用
  void onConnection(const TcpConnectionPtr &conn) {
      //std::cout << conn->peerAddress().toIpPort() << " -> "
      //          << conn->localAddress().toIpPort() << " is "
      //          << (conn->connected() ? "UP" : "DOWN");
      //std::cout << conn->getTcpInfoString();

      conn->send("hello from server\n");
  }

  // 怎么确保回调收上来的是完整的数据报文?
  void onMessage(const TcpConnectionPtr &conn, Buffer *buf) {
      std::string msg(buf->retrieveAllAsString());
      LOG(INFO) << "echo server receive: " << msg << '\n';
      LOG(INFO) << conn->conname() << " recv " << msg.size() << " bytes" << '\n';
      conn->send(msg);
      //if (msg == "exit\n")
      //{
      //    conn->send("bye\n");
      //    conn->shutdown();
      //}
      //if (msg == "quit\n")
      //{
      //    loop_->quit();
      //}
  }

  EventLoop *loop_;
  TcpServer server_;
};

int main(int argc, char *argv[]) {
    // 不输出至logfile, 输出到stderr
    FLAGS_logtostderr = 1;
    // >=0级的log都输出出来
    FLAGS_minloglevel = 0;

    ::google::InitGoogleLogging(argv[0]);
    LOG(INFO) << "echo server launch";
    EventLoop loop;
    InetAddress listenAddr("127.0.0.1", 9888);
    EchoServer server(&loop, listenAddr);
    server.startListen();

    loop.loop();
}
