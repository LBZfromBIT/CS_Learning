; main.asm - 程序的入口点

.386
.model flat,stdcall
option casemap:none

include windows.inc
include kernel32.inc
include user32.inc
include gdi32.inc      

include .\include\constants.inc
include .\include\structs.inc          

includelib kernel32.lib
includelib user32.lib
includelib gdi32.lib

InitGame PROTO stdcall
InitInput PROTO stdcall
GameLoop PROTO stdcall
CleanupDraw PROTO stdcall
DrawGame PROTO stdcall:HDC
HandleInput PROTO stdcall:DWORD

public hWnd

.data 
    szClassName db "SnakeGameClass",0   ; 窗口类名
    szTitle db "Snake!!!",0             ; 窗口标题

    wc WNDCLASSEX <>                    ; 窗口类
    hdc dd 0                            ; 设备上下文
    ps PAINTSTRUCT <>                   ; 绘制结构
    msg MSG <>                          ; 消息
    hInstance dd 0                      ; 实例句柄
    hWnd dd 0                           ; 窗口句柄

.code 
WinMain PROC 
    ; 获取实例句柄
    invoke GetModuleHandle,NULL
    mov hInstance,eax

    ; 注册窗口类
    mov wc.cbSize,SIZEOF WNDCLASSEX
    mov wc.style,CS_HREDRAW or CS_VREDRAW
    mov wc.lpfnWndProc,OFFSET WndProc
    mov wc.cbClsExtra,NULL
    mov wc.cbWndExtra,NULL
    push hInstance
    pop wc.hInstance
    mov wc.hIcon, NULL
    mov wc.hCursor, NULL
    mov wc.hbrBackground, NULL
    mov wc.lpszMenuName, NULL
    mov wc.lpszClassName, OFFSET szClassName
    mov wc.hIconSm, NULL

    invoke RegisterClassEx,ADDR wc

    ; 创建窗口
    invoke CreateWindowEx,NULL,\
        ADDR szClassName,\
        ADDR szTitle,\
        WS_OVERLAPPEDWINDOW,\
        CW_USEDEFAULT,\
        CW_USEDEFAULT,\
        win_long,win_high,\
        NULL,NULL,\
        hInstance,NULL
    mov hWnd,eax

    ; 初始化游戏
    invoke InitGame
    invoke InitInput

    ; 显示窗口
    invoke ShowWindow,hWnd,SW_SHOW
    invoke UpdateWindow,hWnd


    ; 消息循环
    .WHILE TRUE
        ; 优先处理消息
        invoke PeekMessage, ADDR msg, NULL, 0, 0, PM_REMOVE
        .IF eax != 0
            invoke TranslateMessage, ADDR msg
            invoke DispatchMessage, ADDR msg
            .IF msg.message == WM_QUIT
                .BREAK
            .ENDIF
        .ENDIF

        ; 更新游戏状态
        invoke GameLoop
    
        ; 请求重绘
        invoke InvalidateRect, hWnd, NULL, TRUE
    
        ; 给其他程序让出CPU时间
        invoke Sleep, 1
    .ENDW

    mov eax,msg.wParam
    ret
WinMain ENDP

; 窗口过程
WndProc PROC uses ebx edi esi, hWin:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
    .IF uMsg == WM_DESTROY
        invoke CleanupDraw
        invoke PostQuitMessage,0
    .ELSEIF uMsg == WM_PAINT
        ;处理绘制消息
        invoke BeginPaint,hWin,ADDR ps
        mov hdc, eax
        ; 调用DrawGame进行绘制
        invoke DrawGame,hdc
        invoke EndPaint,hWin,ADDR ps
    .ELSEIF uMsg == WM_KEYDOWN
        ; 处理键盘消息
        invoke HandleInput,wParam
    .ELSE
        invoke DefWindowProc,hWin,uMsg,wParam,lParam
        ret
    .ENDIF
    xor eax,eax
    ret
WndProc ENDP

END WinMain