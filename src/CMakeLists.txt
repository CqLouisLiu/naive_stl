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
        util/Set.h util/Stack.h
        util/String.h
        util/Deque.h util/Queue.h
        internal/stl_rb_tree.h
        io/File.h io/File.h io/File.cpp
        internal/stl_dynamic_str.h functional.h utility.h
        internal/stl_pair.h
        internal/stl_hash_map.h
        internal/stl_hash_set.h util/MultiMap.h
        util/MultiSet.h internal/stl_hash_table.h
        internal/stl_heap.h util/PriorityQueue.h
        util/HashMap.h
        util/HashSet.h internal/stl_move.h internal/stl_hash_base.h internal/stl_point_traits.h internal/stl_traits_base.h internal/stl_alloc_traits.h internal/stl_memory_base.h thread/ThreadPool.h thread/ThreadPool.cpp exception/exception.h thread/ThreadSafe_Stack.h)

add_executable(naive_stl ${SOURCE_FILES})