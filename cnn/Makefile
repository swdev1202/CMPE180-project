# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS = -g -Wall

# remove
RM = rm -f

# the build target executable:
TARGET1 = convolution
TARGET2 = convolutionMulti

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(TARGET1).cpp
	$(CC) $(TARGET1).cpp -o $(TARGET1)

$(TARGET2): $(TARGET2).cpp
	$(CC) $(TARGET2).cpp -lpthread -o $(TARGET2)

clean:
	$(RM) $(TARGET1) $(TARGET2)