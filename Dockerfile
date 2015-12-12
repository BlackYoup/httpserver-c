FROM base/archlinux

RUN pacman-key --refresh-keys
RUN pacman -Syu --noconfirm
RUN pacman-db-upgrade
RUN pacman -S cmake gcc make --noconfirm

ADD . /source
WORKDIR /source

RUN cmake . -G "Unix Makefiles"
RUN make

EXPOSE 8080

CMD bin/HTTPServer
