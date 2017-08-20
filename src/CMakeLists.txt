set(SOURCE_FILES
        algorithm.h
        util/Array.h
        iterator.h
        util/List.h
        main.cpp
        memory.h
        internal/stl_algo.h
        internal/stl_alloc.h
        internal/stl_array.h
        internal/stl_config.h
        internal/stl_construct.h
        internal/stl_iterator.h
        internal/stl_type_traits.h
        internal/stl_uninitialized.h
        type_traits.h
        util/Vector.h util/Map.h
        util/Set.h util/Stack.h util/String.h
        util/Deque.h util/Queue.h internal/stl_rb_tree.h
        io/File.h io/File.h io/File.cpp internal/dynamic_string.h functional.h util/Pair.h)

add_executable(naive_stl ${SOURCE_FILES})