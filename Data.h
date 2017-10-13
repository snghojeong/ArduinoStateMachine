#ifndef _DATA_H_
#define _DATA_H_

class Data {
private:
  uint8_t* _buffer;
  size_t _size; // buffer size
  size_t _length; // data length
  bool _isHeap;
  uint16_t _type;

public:
  explicit Data() : _buffer(nullptr), _size(0), _length(0), _isHeap(false) {}
  explicit Data(size_t size) : _size(size), _length(0), _isHeap(true) {
    _buffer = new uint8_t[size];
  }
  virtual ~Data() { if (_isHeap) delete[] _buffer; }

  inline void alloc(size_t size) {
    free();
    _buffer = new uint8_t[size];
    _size = size;
    _isHeap = true;
  }

  inline void alloc(uint8_t* buffer) {
    free();
    _buffer = buffer;
    _size = sizeof(buffer);
    _isHeap = false;
  }

  inline void free() {
    if ( (_buffer != nullptr) && (_isHeap == true) ) {
      delete[] _buffer;
      _buffer = nullptr;
      _isHeap = false;
    }
  }

  inline void copyTo(uint8_t* dest, size_t size) const {
    if (_buffer != nullptr) {
      memcpy(dest, _buffer, _length);
    }
  }

  inline void copyFrom(uint8_t* src, size_t length) {
    if (_buffer != nullptr) {
      memcpy(_buffer, src, length);
      _length = length;
    }
  }

  inline uint8_t* buffer() { return _buffer; }
  inline size_t size() const { return _size; }
  inline size_t length() const { return _length; }
  inline uint16_t type() const { return _type; }
  inline void setType(uint16_t type) { _type = type; }
  inline void setLength(size_t length) { _length = length; }
};

#endif
