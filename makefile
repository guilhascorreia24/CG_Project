
compile:
	g++ utils.cpp main.cpp Object.cpp RotationHandler.cpp World.cpp DiscoNave.cpp CupulaNave.cpp Camera.cpp Sol.cpp Planeta.cpp Satelite.cpp -lm -lGLEW -lGLU -lGL -lglut -o a.out

run:
	./a.out	
