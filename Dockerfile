FROM ubuntu:24.04

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    python3 \
    python3-venv \
    wget

COPY ./src_cpp /opt/interview_src_cpp
WORKDIR /opt/interview_src_cpp

RUN cd pointcloud_project && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make
