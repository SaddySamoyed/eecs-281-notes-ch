# Makefile

# 定义编译器
CXX = g++

# 定义编译器标志
CXXFLAGS = -Wall -g

# 定义目标文件名
TARGET = sort.exe

# 定义源文件
SRC = sort012.cpp

# 定义目标
all: $(TARGET)

# 链接和生成可执行文件
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# 清理目标文件
clean:
	rm -f $(TARGET)
