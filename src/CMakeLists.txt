set(SOURCE_FILES
        algorithm.h
        util/Array.h
        iterator.h
        util/List.h
        main.cpp
        memory.h
        stl_algo.h
        stl_alloc.h
        stl_array.h
        stl_config.h
        stl_construct.h
        stl_iterator.h
        stl_type_traits.h
        stl_uninitialized.h
        type_traits.h
        util/Vector.h io/File.h util/Map.h
        util/Set.h util/Stack.h util/String.h util/Deque.h util/Queue.h)

add_executable(naive_stl ${SOURCE_FILES})