#include "event_loop.h"

#include "epoll.h"
#include "channel.h"

#include <iostream>
#include <unistd.h>
#include <memory>
#include <cstdio>
#include <mutex>

using namespace tinyreactor;

EventLoop::EventLoop() :
    poller_(std::make_unique<Epoll>(this)),
    threadIdBelongTo_(std::this_thread::get_id()) {
}

void EventLoop::loop() {
    while (true) {
        activeChannels_.clear();
        poller_->poll(nullptr, activeChannels_);
        std::printf("poller->poll return\n");
        for (auto curChannel : activeChannels_) {
            curChannel->handleEvent();
        }
    }
}

void EventLoop::updateChannel(Channel *channel) {
    poller_->updateChannelInEpoll(channel);
}

void EventLoop::removeChannel(Channel *channel) {
    poller_->removeChannelInEpoll(channel);
}

void EventLoop::runInLoop(Functor functor) {
    if (isInLoopThread()) {
        functor();
    } else {
        queueInLoop(functor);
    }
}

/// 也有可能在loop thread里面调用吗?
void EventLoop::queueInLoop(Functor functor) {
    {
        std::lock_guard<std::mutex> lg(mutex_);
        pendingFunctors_.push_back(functor);
    }
    // 如果不在loop thread
    if (!isInLoopThread()) {
        wakeupLoopThread();
    }
}

void EventLoop::assertInLoopThread() {

}

void EventLoop::wakeupLoopThread() {
    uint64_t one = 1;  // ?
    ssize_t n = ::write(wakeupFd_, &one, sizeof one);
    if (n != sizeof one) {
        std::cout << "wakeupLoopThread fail" << '\n';
    }
}

bool EventLoop::isInLoopThread() {
    return threadIdBelongTo_ == std::this_thread::get_id();
}
