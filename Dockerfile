FROM ubuntu:22.04

ARG USER_ID=1000
ARG GROUP_ID=1000

ARG DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && apt-get install -y build-essential git software-properties-common lsb-release
RUN apt-get install -y unzip
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

# Install newer version of ninja.
# This was required for modules. Ninja sucks because it seems to have hidden caching things going on,
# so it will sometimes just not build the correct version of your code.
# But it is kept here just in case I ever want to get into modules.
RUN wget https://github.com/ninja-build/ninja/releases/download/v1.13.0/ninja-linux.zip
RUN unzip ninja-linux.zip
RUN cp ninja /usr/bin/ninja

# Install latest version of cmake.
# This was required for modules, but it's good to use the latest version anyways.
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null
RUN echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ jammy main' | tee /etc/apt/sources.list.d/kitware.list >/dev/null
RUN apt update
RUN apt install -y cmake

# Install newer version of clang-format & clangd
# We cannot install version 21 of clangd, because it has a bug where it thinks private types cannot be used inside friend classes.
# So we have to settle with version 20 ¯\_(ツ)_/¯
RUN wget https://apt.llvm.org/llvm.sh
RUN chmod +x llvm.sh
RUN ./llvm.sh 20
RUN apt install -y clang-format-20 clangd-20
RUN rm llvm.sh

# Change the user
USER user
