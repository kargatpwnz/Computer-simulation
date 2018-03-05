#include_directories()

set(SIMULATION_SRCS
        chain.cpp chain.h
        graph.cpp graph.h
        queueing_system.cpp queueing_system.h
        selection.cpp selection.h
        tree.cpp tree.h
        )

SET(LIB_TYPE STATIC)

add_library(src ${LIB_TYPE} ${SIMULATION_SRCS})