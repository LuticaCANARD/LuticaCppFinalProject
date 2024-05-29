# CMake 프로그램의 최소 버전
cmake_minimum_required(VERSION 3.11)

# 프로젝트 정보
project(
  NANOINTERACTIVE_CANARIN_LAB
  VERSION 0.1
  DESCRIPTION "KIMAL"
  LANGUAGES CXX
)
# 실행 파일 생성
add_executable(${PROJECT_NAME} main.cpp)
