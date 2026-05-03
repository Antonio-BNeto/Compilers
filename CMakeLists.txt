cmake_minimum_required(VERSION 3.10)
project(MeuCompilador VERSION 1.0 LANGUAGES CXX)

# Exigir C++17 ou superior (útil para std::variant e std::optional em compiladores)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Inclui a pasta de headers
include_directories(include)

# Lista todos os arquivos fonte
file(GLOB SOURCES "src/*.cpp")

# Gera o executável
add_executable(compiler ${SOURCES})