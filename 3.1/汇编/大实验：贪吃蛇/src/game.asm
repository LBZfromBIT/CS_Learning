; game.asm
; 贪吃蛇游戏逻辑

.386
.model flat,stdcall
option casemap:none

include windows.inc
include kernel32.inc
include user32.inc      
include .\include\constants.inc
include .\include\structs.inc

includelib kernel32.lib
includelib user32.lib      


public score
public snake
public food_x
public food_y

UpdateSnakePosition PROTO stdcall :PTR DWORD,: PTR DWORD
HandleInput PROTO stdcall :DWORD
InitInput PROTO stdcall

.data   
    snake Snake <>          ; 贪吃蛇
    food_x dd 0             ; 食物x坐标
    food_y dd 0             ; 食物y坐标
    score dd 0              ; 得分
    game_over dd 0          ; 游戏结束标志

    MOVE_DELAY dd 50        ; 将延迟时间改为 50ms，提高响应速度
    last_move_time dd 0     ; 添加上次移动时间记录

    szGameOver db "Snake is done,and your score is: %d",0
    szGameOverTitle db "Over!!!",0
    szBuffer db 256 dup(?)  ; 用于格式化文本的缓冲区

    ; 定义游戏区域
    max_x dd win_long/20    ;最大x坐标(蛇一个块20px)
    max_y dd win_high/20  ;最大y坐标


.code
; 初始化游戏
InitGame PROC public
    ; 初始化贪吃蛇的长度
    mov snake.len,init_longth


    ; 设置蛇的初始位置
    ; 使用游戏区域中间偏左的位置，确保蛇有向右移动的空间
    mov eax, max_x
    shr eax, 1        ; eax = max_x / 2
    sub eax, init_longth  ; 向左偏移蛇身长度
    
    mov ebx, max_y    
    shr ebx, 1        ; ebx = max_y / 2


    ;设置蛇的初始状态
    xor ecx,ecx
    .WHILE  ecx < init_longth
        push eax          ; 保存 x 坐标
        mov eax, sizeof SnakeCoord
        mul ecx
        mov esi, OFFSET snake.body
        add esi, eax
        pop eax           ; 恢复 x 坐标

        ;设置蛇的坐标
        mov (SnakeCoord PTR [esi]).x,eax
        mov (SnakeCoord PTR [esi]).y,ebx
        dec eax ;x--,横向实现初始蛇朝右

        inc ecx
    .ENDW


    ;初始化分数
    mov score,0
    mov game_over,0
    call GenerateFood
    ret
InitGame ENDP

; 生成食物
GenerateFood PROC
    LOCAL seed:DWORD

    invoke GetTickCount  ;获取系统时间作种子
    mov seed,eax

    ;生成食物的坐标
    mov eax,seed
    xor edx,edx
    div max_x
    mov food_x,edx      ; x坐标使用余数

    mov eax,seed
    shl eax,1           ; 左移一位改变种子
    xor edx,edx
    div max_y
    mov food_y,edx      ; y坐标使用余数

    ret 
GenerateFood ENDP

; 检查是否吃到食物
CheckFood PROC 
    mov esi,OFFSET snake.body
    mov eax, (SnakeCoord PTR [esi]).x
    .IF eax == food_x
        mov eax, (SnakeCoord PTR [esi]).y
        .IF eax == food_y
            ; 吃到食物
            inc snake.len
            add score,10
            call GenerateFood
        .ENDIF
    .ENDIF
    ret
CheckFood ENDP

; 检查是否碰撞
CheckCollision PROC
    LOCAL i:DWORD
    LOCAL headX:DWORD
    LOCAL headY:DWORD

    ; 获取蛇头坐标并保存
    mov esi, OFFSET snake.body
    mov eax, (SnakeCoord PTR [esi]).x
    mov headX, eax
    mov eax, (SnakeCoord PTR [esi]).y
    mov headY, eax

     mov eax, headX
    .IF eax < 0 
        mov game_over, 1
        ret
    .ENDIF
    .IF eax >= max_x
        mov game_over, 1
        ret
    .ENDIF

    mov eax, headY
    .IF eax < 0
        mov game_over, 1
        ret
    .ENDIF
    .IF eax >= max_y
        mov game_over, 1
        ret
    .ENDIF

    ; 检查是否撞到自己
    mov i, 1
    mov ecx, snake.len
    .WHILE i < ecx
        mov eax, i
        imul eax, sizeof SnakeCoord      ; eax = i * sizeof(SnakeCoord)
        mov esi, OFFSET snake.body
        add esi, eax

        ; 获取身体段的坐标
        mov eax, (SnakeCoord PTR [esi]).x
        mov ebx, (SnakeCoord PTR [esi]).y

        ; 比较与蛇头坐标
        .IF eax == headX
            .IF ebx == headY
                mov game_over, 1
                ret
            .ENDIF
        .ENDIF

        inc i
    .ENDW
    
    ret
CheckCollision ENDP

; 更新蛇的位置
UpdateSnake PROC
    LOCAL i:DWORD

    ;移动身体（从尾部开始）
    mov ecx,snake.len
    dec ecx
    .WHILE ecx > 0
        push ecx

        ;计算当前节点位置
        mov eax,sizeof SnakeCoord
        mul ecx
        mov esi,OFFSET snake.body
        add esi,eax

        ;计算前一个节点位置
        mov eax,sizeof SnakeCoord
        dec ecx
        mul ecx
        mov edi,OFFSET snake.body
        add edi,eax

        ;将前一个节点的位置赋值给当前节点
        mov eax,(SnakeCoord PTR [edi]).x
        mov (SnakeCoord PTR [esi]).x,eax
        mov eax,(SnakeCoord PTR [edi]).y
        mov (SnakeCoord PTR [esi]).y,eax

        pop ecx
        dec ecx
    .ENDW

    ;更新蛇头方向和位置
   mov esi, OFFSET snake.body    ; 获取蛇头基址

    invoke UpdateSnakePosition, \
    ADDR (SnakeCoord PTR [esi]).x, \    ; x 坐标地址
    ADDR (SnakeCoord PTR [esi]).y       ; y 坐标地址
    ret
UpdateSnake ENDP

; 游戏循环
GameLoop PROC
    LOCAL current_time:DWORD

    .IF game_over == 0

        ; 获取当前时间
        invoke GetTickCount
        mov current_time, eax

        ; 检查是否到达移动时间
        mov ebx, last_move_time
        mov eax, current_time
        sub eax, ebx        ; 计算时间差
        .IF eax >= MOVE_DELAY
            ; 更新蛇的位置
            invoke UpdateSnake
            
            ; 检查碰撞
            invoke CheckCollision
            
            ; 检查是否吃到食物
            invoke CheckFood
            
            ; 更新上次移动时间
            mov eax, current_time
            mov last_move_time, eax
        .ENDIF
    .ELSE
        ;游戏结束
        invoke wsprintf, ADDR szBuffer, ADDR szGameOver, score
        invoke MessageBox, NULL, ADDR szBuffer, ADDR szGameOverTitle, MB_OK
        invoke InitGame
        invoke InitInput
    .ENDIF
    ret
GameLoop ENDP

END