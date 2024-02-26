FROM alpine

RUN apk update && \
    apk add build-base make

WORKDIR /app
COPY Makefile /app/Makefile

CMD ["sh", "-c", "make && tail -f"]
