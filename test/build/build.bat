REM compile test program  
cls
cl /Zi /W4 /Fe:app.exe ../src/main.c ../src/game.c /I ../../include /link engine.lib

