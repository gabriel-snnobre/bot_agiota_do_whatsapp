FROM archlinux:latest

WORKDIR /app

COPY . .

RUN pacman -Syu --noconfirm gcc curl make && \
    pacman -Scc --noconfirm 

RUN make

CMD ["bin/main"]
