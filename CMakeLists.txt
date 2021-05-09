cmake_minimum_required(VERSION 3.0.0)
project(ExamTEX VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(ExamTEX main.c
            vector/vec.c vector/vec.h
            Utils/cleanText.c Utils/cleanText.h
            Utils/parsers.c Utils/parsers.h
            Utils/readFile.c Utils/readFile.h
            Validators/validateNumerical.c Validators/validateNumerical.h
            Validators/mulmcqs.c Validators/mulmcqs.h
            Printers/printNumerical.c Printers/printNumerical.h
            Printers/printmulmcq.c Printers/printmulmcq.h
            Utils/lineNumber.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
