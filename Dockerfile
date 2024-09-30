FROM ubuntu:22.04

ENV NODE_VERSION=20.x

RUN apt-get update

RUN apt-get install -y \
    curl \
    build-essential \
    cmake \
    libgtk-3-dev \
    libglu1-mesa-dev \
    git 

RUN rm -rf /var/lib/apt/lists/*

RUN . ~/.bashrc

RUN apt-get install libwxgtk2.8-dev libwxgtk2.8-dbg

RUN curl -fsSL https://deb.nodesource.com/setup_$NODE_VERSION.x -o nodesource_setup.sh \
    && bash nodesource_setup.sh \
    && apt-get install -y nodejs \
    && rm nodesource_setup.sh

RUN npm install --global yarn

WORKDIR /

RUN node -v && npm -v && yarn -v && cmake --version

CMD ["yarn", "run", "browser"]