; input.asm
; 该文件处理用户输入，响应键盘事件以控制贪吃蛇的移动

.386
.model flat,stdcall
option casemap:none

include windows.inc
include user32.inc

includelib user32.lib

.data 
    ; 定义方向常量
    DIR_UP equ 0
    DIR_RIGHT equ 1
    DIR_DOWN equ 2
    DIR_LEFT equ 3

    current_dir dd DIR_RIGHT ; 当前方向,默认向右

.code
; 处理键盘事件,参数wParam:按键码
HandleInput PROC wParam:DWORD
   mov eax,wParam

    ; 按键处理
    .IF eax == VK_UP ; 按下上键
        ;只有当前不向下走才能向上
        mov ebx,current_dir
        .IF ebx != DIR_DOWN
            mov current_dir,DIR_UP
        .ENDIF

    .ELSEIF eax == VK_RIGHT ; 按下右键
        ;只有当前不向左走才能向右
        mov ebx,current_dir
        .IF ebx != DIR_LEFT
            mov current_dir,DIR_RIGHT
        .ENDIF
    
    .ELSEIF eax == VK_DOWN ; 按下下键
        ;只有当前不向上走才能向下
        mov ebx,current_dir
        .IF ebx != DIR_UP
            mov current_dir,DIR_DOWN
        .ENDIF
    
    .ELSEIF eax == VK_LEFT ; 按下左键
        ;只有当前不向右走才能向左
        mov ebx,current_dir
        .IF ebx != DIR_RIGHT
            mov current_dir,DIR_LEFT
        .ENDIF
    .ENDIF

    ret 
HandleInput ENDP

; 获取当前移动方向
GetDirection PROC public
    mov eax,current_dir
    ret
GetDirection ENDP

;根据当前方向调整蛇头位置
;参数x,y:蛇头位置
UpdateSnakePosition PROC public uses ebx edx, headX:PTR DWORD, headY:PTR DWORD
    mov ebx,headX
    mov edx,headY

    .IF current_dir == DIR_UP
        mov eax,[edx]
        dec eax         ;向上移动,y-1, x不变
        mov [edx],eax

    .ELSEIF current_dir == DIR_RIGHT
        mov eax,[ebx]
        inc eax         ;向右移动,x+1, y不变
        mov [ebx],eax
    
    .ELSEIF current_dir == DIR_DOWN
        mov eax,[edx]
        inc eax         ;向下移动,y+1, x不变
        mov [edx],eax

    .ELSEIF current_dir == DIR_LEFT
        mov eax,[ebx]
        dec eax         ;向左移动,x-1, y不变
        mov [ebx],eax
    .ENDIF

    ret
UpdateSnakePosition ENDP

InitInput PROC public
    mov current_dir,DIR_RIGHT
    ret
InitInput ENDP

END