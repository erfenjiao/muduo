/*
    轻量级字符串封装类，用于管理一块不可变的内存区域。

    它的主要作用是封装读取字符串的操作，而不涉及到修改字符串的函数

    StringPiece类最常用的场景是将一个 C 风格的字符串(const char*) 封装成 string_view 对象，
    可以被诸如find、substr等算法使用，提高了代码的清晰度、简洁性和复用性。

    例如:

    c++
    const char* buffer = "hello, world";
    StringPiece piece(buffer, strlen(buffer));

    int index = piece.find("world"); // 返回6
    std::string str = piece.substr(0, index); // 返回"hello,"

    上述代码中，通过 StringPiece 类将 C 风格的字符串 buffer 转为 piece 对象表示可变字符串，
    然后使用内建的 find 函数查找索引位置，返回值为6。接着使用 substr 函数根据找到的位置进行截取字符串操作，
    返回子串 "hello," 。

    需要注意的是，由于 StringPiece 对象不会管理内存空间，因此在使用 StringPiece 参数时，
    被封装的内存必须在 StringPiece 的生命周期内有效，防止访问已经释放的内存。

    使用 StringPiece 类可以用较少的代码处理字符串操作，节省了资源，提高了程序效率。
*/
#ifndef MUDUO_BASE_STRINGPIECE_H
#define MUDUO_BASE_STRINGPIECE_H

#include <string.h>
#include <iosfwd>    // for ostream forward-declaration


// #include "muduo/base/Types.h"
#include "Types.h"

namespace muduo {
    class StringArg // copyable
    {
        public:
        StringArg(const char* str)
            : str_(str)
        { }

        StringArg(const string& str)
            : str_(str.c_str())
        { }

        const char* c_str() const { return str_; }

        private:
        const char* str_;
    };
    class StringPiece {
        private:
        const char* ptr_;
        int length_;

        public:
        StringPiece() : ptr_(NULL), length_(0) {}
        StringPiece(const char* str) : ptr_(str), length_(static_cast<int>(strlen(ptr_))) {}
        StringPiece(const unsigned char* str)
            : ptr_(reinterpret_cast<const char*>(str)),
            length_(static_cast<int>(strlen(ptr_))) { }
        StringPiece(const string& str)
            : ptr_(str.data()), length_(static_cast<int>(str.size())) { }
        StringPiece(const char* offset, int len)
            : ptr_(offset), length_(len) { }

        const char* data() const { 
            return ptr_; 
        }
        int size() const { 
            return length_; 
        }
        bool empty() const { 
            return length_ == 0; 
        }
        const char* begin() const { 
            return ptr_; 
        }
        const char* end() const { 
            return ptr_ + length_; 
        }

        void clear() { 
            ptr_ = NULL; 
            length_ = 0; 
        }
        void set(const char* buffer, int len) { 
            ptr_ = buffer; 
            length_ = len; 
        }
        void set(const char* str) {
            ptr_ = str;
            length_ = static_cast<int>(strlen(str));
        }
        void set(const void* buffer, int len) {
            ptr_ = reinterpret_cast<const char*>(buffer);
            length_ = len;
        }        
        char operator[](int i) const { 
            return ptr_[i];
        }

        void remove_prefix(int n) {
            ptr_ += n;
            length_ -= n;
        }

        void remove_suffix(int n) {
            length_ -= n;
        }

        bool operator==(const StringPiece& x) const {
            return ((length_ == x.length_) &&
                    (memcmp(ptr_, x.ptr_, length_) == 0));
        }
        bool operator!=(const StringPiece& x) const {
            return !(*this == x);
        }

        #define STRINGPIECE_BINARY_PREDICATE(cmp,auxcmp)                             \
        bool operator cmp (const StringPiece& x) const {                           \
            int r = memcmp(ptr_, x.ptr_, length_ < x.length_ ? length_ : x.length_); \
            return ((r auxcmp 0) || ((r == 0) && (length_ cmp x.length_)));          \
        }

        STRINGPIECE_BINARY_PREDICATE(<,  <);
        STRINGPIECE_BINARY_PREDICATE(<=, <);
        STRINGPIECE_BINARY_PREDICATE(>=, >);
        STRINGPIECE_BINARY_PREDICATE(>,  >);
        #undef STRINGPIECE_BINARY_PREDICATE

        int compare(const StringPiece& x) const {
            int r = memcmp(ptr_, x.ptr_, length_ < x.length_ ? length_ : x.length_);
            if (r == 0) {
                if (length_ < x.length_) r = -1;
                else if (length_ > x.length_) r = +1;
            }
            return r;
        }

        string as_string() const {
            return string(data(), size());
        }

        void CopyToString(string* target) const {
            target->assign(ptr_, length_);
        }

        // Does "this" start with "x"
        bool starts_with(const StringPiece& x) const {
            return ((length_ >= x.length_) && (memcmp(ptr_, x.ptr_, x.length_) == 0));
        }
    };
} // namespace muduo

#ifdef HAVE_TYPE_TRAITS
// This makes vector<StringPiece> really fast for some STL implementations
template<> struct __type_traits<muduo::StringPiece> {
  typedef __true_type    has_trivial_default_constructor;
  typedef __true_type    has_trivial_copy_constructor;
  typedef __true_type    has_trivial_assignment_operator;
  typedef __true_type    has_trivial_destructor;
  typedef __true_type    is_POD_type;
};
#endif

// allow StringPiece to be logged
std::ostream& operator<<(std::ostream& o, const muduo::StringPiece& piece);

#endif