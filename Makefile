final: main.cpp
	clang++ -o main main.cpp

clean:
	rm main *.o

# -std=c++11 -stdlib=libc++
