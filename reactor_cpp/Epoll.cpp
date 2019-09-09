#include "Epoll.h"

#include "Channel.h"

#include <cstdio>
#include <cstring>
#include <sys/epoll.h>

Epoll::Epoll(EventLoop *ownerLoop) :
    ownerLoop_(ownerLoop),
    epfd_(epoll_create(1024)),
    events_(vector<struct epoll_event>(kInitEventListSize)) {  /* 1024 is just an hint for the kernel */ // from redis
}

Epoll::~Epoll() {
    ::close(epfd_);
}

int Epoll::poll(struct timeval *tvp, vector<Channel*> &activeChannels) {
    int retval, numevents = 0;
    retval = ::epoll_wait(epfd_,
                          events_,
                          1024, // epoll_wait() 第三个参数怎么办?
                          tvp ? (tvp->tv_sec * 1000 + tvp->tv_usec / 1000) : -1);
    if (retval > 0) {
        int i;
        numevents = retval;
        for (i = 0; i < numevents; ++i) {
            Channel *channel = static_cast<Channel *>(events_[i].data.ptr);
            channel->set_revents(events_[i].events);
            activeChannels.push_back(channel);
        }
    }
    return numevents;
}

void Epoll::updateChannelInEpoll(Channel *channel) {
    struct epoll_event event;
    ::memset(&event, 0, sizeof event);
    event.events = channel->events();
    event.data.ptr = channel;
    int fd = channel->fd();

    if (::epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &event) == -1)  // < 0的其他返回值?
    {
        std::fprintf(stderr, "epoll_ctl occur error in Epoll::updateChannelInEpoll()\n ");
        // 应该终止吧?
    }
}

void Epoll::removeChannelInEpoll(Channel *channel) {
    // temprary empty
}