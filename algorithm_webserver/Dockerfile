FROM gcc:latest
LABEL authors="rtyse"


WORKDIR /app

COPY main.cpp .
COPY graph.hpp .
COPY httplib.h .
COPY nlohmann /app/nlohmann

RUN g++ -o main main.cpp

CMD ["./main"]