cmake_minimum_required (VERSION 2.6)

project (Simple-Neural-Network)

set(CMAKE_CXX_FLAGS "-fstack-protector-strong")

add_library(snn SHARED NeuralNetwork.cpp Layer.cpp Neuron.cpp Weight.cpp ActivationFunctions.cpp ErrorFunctions.cpp)
include (GenerateExportHeader)
GENERATE_EXPORT_HEADER(snn
	BASE_NAME snn
	EXPORT_MACRO_NAME snn_NeuralNetwork
	EXPORT_FILE_NAME snn_NeuralNetwork.h
	STATIC_DEFINE SNN_NeuralNetwork_BUILT_AS_STATIC)
	
add_executable(driver driver.cpp NeuralNetwork.cpp)
target_link_libraries(driver snn)

#add_executable( NeuralNetwork NeuralNetwork.cpp)
