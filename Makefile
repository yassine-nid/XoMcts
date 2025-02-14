CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++2a

TARGET = XOGame

SRCS = XOGame.cpp mtcs.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp XOGame.hpp mtcs.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(TARGET)

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS) $(TARGET)

re: fclean all
