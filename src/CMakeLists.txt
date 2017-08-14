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
        stl_def.h
        stl_deque.h
        stl_iterator.h
        stl_list.h
        stl_type_traits.h
        stl_uninitialized.h
        stl_vector.h
        type_traits.h
        util/Vector.h io/File.h map.h
        util/Set.h util/Stack.h util/String.h File.cpp.cpp util/Deque.h)

add_executable(naive_stl ${SOURCE_FILES})