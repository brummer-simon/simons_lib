# simons_lib
Small collection useful C++ classes (header only implementations) I wrote over the years.
Most class share a certain focus on embedded systems.

# Contents
- CachedCallable: A cache for computation results of callable object. Threadsafety is configurable.
- RandomNumberGenerator: Small wrapper used to combine a random engine and a distribution into a single object. Threadsafety is configurable.
- LockGuard: Simple reimplementation of std::lock_guard.
- DummyMutex: Mutex dummy to use where no threadsafety is required. 
- Math: Several math related functions.

# Optional Dependencies
- [googletest](https://github.com/google/googletest) (unittests)
- [doxygen](www.doxygen.org) (documentation)
