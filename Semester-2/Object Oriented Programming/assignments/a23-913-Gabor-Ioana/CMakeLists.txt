cmake_minimum_required(VERSION 3.24)
project(a23_913_Gabor_Ioana C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(a23_913_Gabor_Ioana
        main.c
        domain/product.c
        domain/product.h
        repository/repository.c
        repository/repository.h
        service/service.c
        service/service.h
        ui/ui.c
        ui/ui.h
        utils/utils.c
        utils/utils.h
        domain/vector.c
        domain/vector.h repository/repository.c repository/undo_redo_repository.h repository/undo_redo_repository.c tests/test_domain.c tests/test_domain.h tests/test_repository.c tests/test_repository.h tests/test_service.c tests/test_service.h)
