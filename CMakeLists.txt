cmake_minimum_required(VERSION 3.28.3)

set(PROJ_NAME "Assembly_and_Emulator"   ) # TODO: maybe be creatinve with name for this project.
set(PROJ_LANG LANGUAGES ASM C CXX CUDA  ) # ASM and C to be used primarily and CXX+CUDA for parallel processing
set(PROJ_VERS VERSION  0.00.0           ) # Remember to tweak versions on major.minor.patches
set(PROJ_DESC DESCRIPTION "Repository for Computer Organization, Winter 2025 semester, assignment at IIITD")

project(${PROJ_NAME} ${PROJ_DESC} ${PROJ_LANG} ${PROJ_VERS})