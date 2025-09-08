main: main.c
	gcc main.c -L/opt/homebrew/lib -L/opt/homebrew/opt/ffmpeg/lib -I/opt/homebrew/opt/ffmpeg/include -lavformat -lavcodec -lavutil -lswscale -lswresample -I/opt/homebrew/opt/sdl2/include -L/opt/homebrew/opt/sdl2/lib  -o main -Wall -Werror 
	./main
	

clean: 
	rm main