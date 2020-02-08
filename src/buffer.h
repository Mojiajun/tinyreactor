//
// Created by Mo Jiajun on 2019/9/13.
//
#ifndef SINGLE_THREAD_REACTOR_SRC_BUFFER_H_
#define SINGLE_THREAD_REACTOR_SRC_BUFFER_H_

#include <cassert>
#include <string>
#include <vector>

namespace tinyreactor {

class Buffer {
 public:
  static const size_t kCheapPrepend = 8;
  static const size_t kInitialSize = 1024;

  explicit Buffer(size_t initialSize = kInitialSize)
      : buffer_(kCheapPrepend + initialSize),
        readerIndex_(kCheapPrepend),
        writerIndex_(kCheapPrepend) {
      assert(readableBytes() == 0);
      assert(writableBytes() == initialSize);
      assert(prependableBytes() == kCheapPrepend);
  }

  size_t prependableBytes() const {
      return readerIndex_;
  }
  size_t readableBytes() const {
      return writerIndex_ - readerIndex_;
  }
  size_t writableBytes() const {
      return buffer_.size() - writerIndex_;
  }

  const char *peek() const { return begin() + readerIndex_; }

  void retrieve(size_t len) {
      assert(len <= readableBytes());
      if (len < readableBytes()) {
          readerIndex_ += len;
      } else {
          retrieveAll();
      }
  }

  void retrieveAll() {
      readerIndex_ = kCheapPrepend;
      writerIndex_ = kCheapPrepend;
  }

  void append(const char * /*restrict*/ data, size_t len) {
      ensureWritableBytes(len);
      std::copy(data, data + len, beginWrite());
      hasWritten(len);
  }

  void hasWritten(size_t len) {
      assert(len <= writableBytes());
      writerIndex_ += len;
  }

  void append(const void * /*restrict*/ data, size_t len) {
      append(static_cast<const char *>(data), len);
  }

  void ensureWritableBytes(size_t len) {
      if (writableBytes() < len) {
          makeSpace(len);
      }
      assert(writableBytes() >= len);
  }

  std::string retrieveAllAsString() {
      return retrieveAsString(readableBytes());
  }

  std::string retrieveAsString(size_t len) {
      assert(len <= readableBytes());
      std::string result(peek(), len);
      retrieve(len);
      return result;
  }

  char *beginWrite() { return begin() + writerIndex_; }
  ssize_t readFd(int fd, int *savedErrno);

 private:
  char *begin() { return &*buffer_.begin(); }

  const char *begin() const { return &*buffer_.begin(); }

  void makeSpace(size_t len) {
      if (writableBytes() + prependableBytes() < len + kCheapPrepend) {  // 真的扩张vector<char>.
          // FIXME: move readable data
          buffer_.resize(writerIndex_ + len);
      } else {
          // move readable data to the front, make space inside buffer
          assert(kCheapPrepend < readerIndex_);
          size_t readable = readableBytes();
          std::copy(begin() + readerIndex_,
                    begin() + writerIndex_,
                    begin() + kCheapPrepend);
          readerIndex_ = kCheapPrepend;
          writerIndex_ = readerIndex_ + readable;
          assert(readable == readableBytes());
      }
  }

  std::vector<char> buffer_;
  size_t readerIndex_;
  size_t writerIndex_;
};

}
#endif //SINGLE_THREAD_REACTOR_SRC_BUFFER_H_
