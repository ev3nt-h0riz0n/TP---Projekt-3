cmake_minimum_required(VERSION 3.4...3.29)
project(sygnaly)

list(APPEND CMAKE_PREFIX_PATH "C:/Users/Jarek/AppData/Local/Packages/PythonSoftwareFoundation.Python.3.12_qbz5n2kfra8p0/LocalCache/local-packages/Python312/site-packages/pybind11/share/cmake")
list(APPEND CMAKE_PREFIX_PATH "libsndfile/CMakeBuild")
find_package(pybind11 REQUIRED)
find_package(SndFile REQUIRED)
set(SndFile_DIR "libsndfile/CMakeBuild/sndfileconfig.cmake")
include_directories("C:/Users/Jarek/AppData/Local/Packages/PythonSoftwareFoundation.Python.3.12_qbz5n2kfra8p0/LocalCache/local-packages/Python312/site-packages/pybind11/include")
include_directories("C:/Users/Jarek/miniconda3/include")
include_directories("matplotplusplus/source")
include_directories("libsndfile/CMakeBuild/include")


link_directories("libsndfile/CMakeBuild/Debug")

add_subdirectory(matplotplusplus)
python_add_library(sygnaly MODULE sygnaly.cpp WITH_SOABI)
target_link_libraries(sygnaly PUBLIC matplot)
target_link_libraries(sygnaly PRIVATE sndfile)

#Pamietaj, zeby wpisac | import sys | sys.path.append('C:\\Users\\Jarek\\ProgramIII\\build\\Release') (Informacja dla mnie bo python nie wyszukuje patha do biblioteki)