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
            Validators/truefalse.c Validators/truefalse.h
            Validators/mcq_SC_Val.c Validators/mcq_SC_Val.h
            Validators/validateOneWord.c Validators/validateOneWord.h
            Printers/printNumerical.c Printers/printNumerical.h
            Printers/printmulmcq.c Printers/printmulmcq.h
            Printers/printTF.c Printers/printTF.h
            Printers/mcqOutputFuncs.c Printers/mcqOutputHeader.h
            Printers/printerOneWord.c Printers/printerOneWord.h
            Utils/lineNumber.h Binarysearch/binary_search.c Binarysearch/binary_search.h
            Bsearch_and_PrintCall/bsearch_and_print.c Bsearch_and_PrintCall/bsearch_and_print.h
            sort/merge_sort.c sort/merge_sort.h
            )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
