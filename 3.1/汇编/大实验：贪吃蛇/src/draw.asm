; draw.asm
; 该文件负责绘制游戏界面，包括贪吃蛇和食物的显示

.386
.model flat,stdcall
option casemap:none

include windows.inc
include gdi32.inc
include user32.inc  
include .\include\constants.inc        ; 包含常量定义
include .\include\structs.inc          ; 包含结构体定义

includelib gdi32.lib
includelib user32.lib   

; 声明外部变量
EXTERN snake:Snake
EXTERN food_x:DWORD
EXTERN food_y:DWORD
EXTERN score:DWORD
EXTERN hWnd:HWND

.data
    ;定义画笔和画刷
    hSnakePen dd ?          ; 贪吃蛇画笔
    hSnakeBrush dd ?        ; 贪吃蛇画刷
    hFoodPen dd ?           ; 食物画笔
    hFoodBrush dd ?         ; 食物画刷

    szScore db "SCORE: %d",0
    szScoreBuffer db 32 dup(?)  ; 存储格式化后的分数字符串

    szPosition db "Position: %d",0
    szPositionBuffer db 32 dup(?)

    ;定义每个方块的大小
    block_size equ 20       ; 方块大小20px

.code

; 初始化画笔和画刷
InitDraw PROC hdc:HDC
    ; 创建贪吃蛇画笔
    invoke CreatePen,PS_SOLID,1,snake_rgb
    mov hSnakePen,eax

    ; 创建贪吃蛇画刷
    invoke CreateSolidBrush,snake_rgb
    mov hSnakeBrush,eax

    ; 创建食物画笔
    invoke CreatePen,PS_SOLID,1,food_rgb
    mov hFoodPen,eax

    ; 创建食物画刷
    invoke CreateSolidBrush,food_rgb
    mov hFoodBrush,eax

    ret
InitDraw ENDP

; 绘制单个方块
DrawBlock PROC uses eax ebx, hdc:HDC, x:DWORD, y:DWORD, color:DWORD
    LOCAL rect:RECT
    LOCAL hPen:DWORD
    LOCAL hBrush:DWORD
    LOCAL hOldPen:DWORD
    LOCAL hOldBrush:DWORD

    ; 创建画笔和画刷
    invoke CreatePen, PS_SOLID, 1, color
    mov hPen, eax
    invoke CreateSolidBrush, color    ; 使用相同的颜色创建画刷
    mov hBrush, eax

    ; 选择进设备环境
    invoke SelectObject, hdc, hPen
    mov hOldPen, eax
    invoke SelectObject, hdc, hBrush
    mov hOldBrush, eax

    ; 计算方块位置
    mov eax, x
    mov ebx, block_size    ; 使用寄存器进行乘法
    mul ebx
    mov rect.left, eax

    mov eax, y
    mov ebx, block_size
    mul ebx
    mov rect.top, eax

    ; 计算右下角坐标
    mov eax, rect.left
    add eax, block_size
    mov rect.right, eax

    mov eax, rect.top
    add eax, block_size
    mov rect.bottom, eax

    ; 绘制方块
    invoke Rectangle, hdc, rect.left, rect.top, rect.right, rect.bottom

    ; 恢复原来的画笔和画刷
    invoke SelectObject, hdc, hOldPen
    invoke SelectObject, hdc, hOldBrush

    ; 删除创建的画笔和画刷
    invoke DeleteObject, hPen
    invoke DeleteObject, hBrush
    ret 
DrawBlock ENDP

; 绘制蛇
DrawSnake PROC uses esi, hdc:HDC,pSnake:PTR Snake
    LOCAL i:DWORD

    mov esi, pSnake
    mov ecx, (Snake PTR [esi]).len  
    mov i, 0

   .WHILE i < ecx
        push ecx
        ; 获取蛇身坐标
        mov eax,i
        mov ebx, sizeof SnakeCoord
        mul ebx
        lea ebx, (Snake PTR [esi]).body
        add eax, ebx
        invoke DrawBlock,hdc,\
            (SnakeCoord PTR [eax]).x,\
            (SnakeCoord PTR [eax]).y,\
            snake_rgb

        inc i
        pop ecx
    .ENDW
    ret 
DrawSnake ENDP

; 绘制食物
DrawFood PROC hdc:HDC, foodX:DWORD, foodY:DWORD
    invoke DrawBlock, hdc, foodX, foodY, food_rgb
    ret
DrawFood ENDP

; 绘制分数
DrawScore proc hdc:HDC, pscore:DWORD
    local hOldFont:DWORD
    
    ; 设置文本颜色和背景模式
    invoke SetTextColor, hdc, score_rgb
    invoke SetBkMode, hdc, TRANSPARENT
    
    ; 格式化分数字符串
    invoke wsprintf, ADDR szScoreBuffer, ADDR szScore, pscore
    
    ; 显示分数
    invoke TextOut, hdc, score_x, score_y, ADDR szScoreBuffer, eax
    
    ret
DrawScore endp

; 绘制分数
DrawPosition proc hdc:HDC, pposx:DWORD, pposy:DWORD
    local hOldFont:DWORD
    
    ; 设置文本颜色和背景模式
    invoke SetTextColor, hdc, position_rgb
    invoke SetBkMode, hdc, TRANSPARENT
    
    ; 格式化分数字符串
    invoke wsprintf, ADDR szPositionBuffer, ADDR szPosition, pposx, pposy
    
    ; 显示分数
    invoke TextOut, hdc, position_x, position_y, ADDR szPositionBuffer, eax
    
    ret
DrawPosition endp

; 绘制游戏界面
DrawGame PROC hdc:HDC
    LOCAL rect:RECT
    
    ; 创建并设置背景画刷
    invoke CreateSolidBrush, background_rgb
    push eax        ; 保存画刷句柄
    
    ; 获取客户区大小
    invoke GetClientRect, hWnd, ADDR rect
    
    ; 使用画刷填充背景
    invoke FillRect, hdc, ADDR rect, eax
    
    ; 清理画刷
    pop eax
    invoke DeleteObject, eax
    
    ; 绘制蛇
    invoke DrawSnake, hdc, ADDR snake
    
    ; 绘制食物
    invoke DrawFood, hdc, food_x, food_y
    
    ; 绘制分数
    invoke DrawScore, hdc, score

     ; 获取蛇头坐标
    mov esi, OFFSET snake.body
    mov eax, (SnakeCoord PTR [esi]).x
    mov ebx, (SnakeCoord PTR [esi]).y
    
    ; 绘制位置
    invoke DrawPosition, hdc, eax, ebx
    ret
DrawGame ENDP

CleanupDraw proc
    invoke DeleteObject, hSnakePen
    invoke DeleteObject, hSnakeBrush
    invoke DeleteObject, hFoodPen
    invoke DeleteObject, hFoodBrush
    ret
CleanupDraw endp

END