FROM alpine

RUN apk update
RUN apk add build-base make

WORKDIR /app
COPY Makefile /app/Makefile

CMD ["tail", "-f"]
