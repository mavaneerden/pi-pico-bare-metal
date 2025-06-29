FROM ubuntu:22.04

ARG USER_ID=1000
ARG GROUP_ID=1000

ARG DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update
RUN apt-get install -y build-essential git
# Build dependencies
RUN apt-get install -y cmake
# Script dependencies
RUN apt-get install -y python-is-python3
# Formatting & checks
RUN apt-get install -y cppcheck wget lsb-release software-properties-common gnupg

# Create a new user
RUN addgroup --gid $GROUP_ID user

# Make the user able to do sudo without a password
RUN adduser --uid $USER_ID --gid $GROUP_ID --disabled-password --gecos '' user

#  Add new user docker to sudo group
RUN adduser user sudo

# Ensure sudo group users are not
# asked for a password when using
# sudo command by ammending sudoers file
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

# Remove the sudo messasge1
RUN touch /home/user/.sudo_as_admin_successful

# Change the working directory
WORKDIR /home/user

# Install newer version of clang-format
RUN wget https://apt.llvm.org/llvm.sh
RUN chmod +x llvm.sh
RUN ./llvm.sh 19
RUN apt install -y clang-format-19 clangd-19
RUN rm llvm.sh

# Change the user
USER user

# ENV PATH="$PATH:/workspaces/OAlpha-flight-software/toolchain/bin"
# ENV TRISKEL_LIBPATH="/workspaces/OAlpha-flight-software/toolchain/lib/gcc/arm-none-eabi/9.3.1/thumb/v7e-m+dp/softfp"

