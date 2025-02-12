# Compiler
CXX = c++

# Compiler flags
CXXFLAGS = -Wall -Wextra -Werror -std=c++2a #-fsanitize=address

# Target executable
TARGET = XOGame

# Source files
SRCS = XOGame.cpp mtcs.cpp main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
%.o: %.cpp XOGame.hpp mtcs.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
all: $(TARGET)

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS) $(TARGET)

re: fclean all
