final: main.cpp
	clang++ -o main -std=c++11 -stdlib=libc++ main.cpp

clean:
	rm main *.o

# -std=c++11 -stdlib=libc++
