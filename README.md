# simons_lib
Small collection useful C++ classes (header only implementations) I wrote over the years.
Most class share a certain focus on embedded systems. This means that exceptions can be
disabled (none are thrown) and some behavior can be configured via defines (e.g. remove prints or
stay in a loop in case of hard faults instead of exiting to a OS).

# Contents
- CachedCallable: A cache for computation results of callable object. Thread safety is configurable.
- RandomNumberGenerator: Small wrapper used to combine a random engine and a distribution into a single object. Threadsafety is configurable.
- LockGuard: Simple reimplementation of std::lock_guard.
- NullTypes: Dummy implementations that can act as template parameters (NullObj, NullMutex).
- Result: Alternative to exception based error handling. Heavily inspired by Rusts "Result" type.
- Ringbuffer: Generic fixed-size Ringbuffer. Thread safety is configurable.
- Math: Several math related functions.

# Optional Dependencies
- [googletest](https://github.com/google/googletest) (unittests)
- [doxygen](www.doxygen.org) (documentation)
