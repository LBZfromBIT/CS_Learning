
ml /c /coff ".\src\main.asm"


ml /c /coff ".\src\game.asm"


ml /c /coff ".\src\draw.asm"


ml /c /coff ".\src\input.asm"




link /SUBSYSTEM:WINDOWS "main.obj" "game.obj" "draw.obj" "input.obj" /OUT:"snake_game.exe"
