FROM gcc:13

WORKDIR /app

# Copy everything (code + data files)
COPY . .

# Build the single source file
RUN g++ -std=c++17 -O2 -o university_app src/ums.cpp

# Run the app
CMD ["./university_app"]