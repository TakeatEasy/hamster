

add_library(csrc_utils SHARED StringUtil.cpp
                                C++17.cpp
                                SmallVector.cpp
                                Optional.cpp
                                Type.cpp
                                Backtrace.cpp
                                typeid.cpp
                                UniqueVoidPtr.cpp
                                intrusive_ptr.cpp
                                Logging.cpp
                                flags_use_no_gflags.cpp
                                Exception.cpp)