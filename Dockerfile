# Use Fedora as the base image
FROM fedora:latest

# Install required packages
RUN dnf -y update && \
    dnf -y install \
        gcc \
        make \
        ncurses-devel \
        perl-Pod-Html \
        mingw64-gcc \
        dos2unix \
        cmp \
        && dnf clean all

# Set the working directory inside the container
WORKDIR /workspace

# Default command
CMD ["/bin/bash"]
