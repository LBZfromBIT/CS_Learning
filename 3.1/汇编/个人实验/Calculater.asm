.386
.model flat, stdcall
option casemap:none

include \masm32\include\windows.inc
include \masm32\include\kernel32.inc
include \masm32\include\user32.inc
include \masm32\include\msvcrt.inc

includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\user32.lib
includelib \masm32\lib\msvcrt.lib

atof PROTO C:DWORD
atoi PROTO C:DWORD
sprintf PROTO C:DWORD,:VARARG

; 常量定义
ID_BTN_ADD     equ 1001    ; 加法按钮ID
ID_BTN_SUB     equ 1002    ; 减法按钮ID
ID_BTN_MUL     equ 1003    ; 乘法按钮ID
ID_BTN_DIV     equ 1004    ; 除法按钮ID
ID_BTN_SIN     equ 1005    ; 正弦按钮ID
ID_BTN_COS     equ 1006    ; 余弦按钮ID
ID_BTN_TAN     equ 1007    ; 正切按钮ID
ID_EDIT1       equ 2001    ; 第一个输入框ID
ID_EDIT2       equ 2002    ; 第二个输入框ID
ID_EDIT_RESULT equ 2003    ; 结果输出框ID
ID_EDIT_OP     equ 2004    ; 运算符号显示框ID

.data
ClassName    db "CalcWinClass", 0
AppName      db "Calculator", 0
EditClass    db "EDIT", 0
ButtonClass  db "BUTTON", 0
fmt_int      db "%d", 0
fmt_float    db "%f", 0
fmt_str      db "%s", 0
btn_add      db "add", 0
btn_sub      db "sub", 0
btn_mul      db "mul", 0
btn_div      db "div", 0
btn_sin      db "sin", 0
btn_cos      db "cos", 0
btn_tan      db "tan", 0

hInstance   dd 0
hWnd        dd 0
hwndEdit1   dd 0
hwndEdit2   dd 0
hwndResult  dd 0
buffer      db 256 dup(0)
msg         MSG <>
wc          WNDCLASSEX <>


.code
start:
    invoke GetModuleHandle, NULL
    mov    hInstance, eax
    
    ; 注册窗口类
    call   RegisterWinClass
    
    ; 创建主窗口
    invoke CreateWindowEx, WS_EX_CLIENTEDGE, \
           ADDR ClassName, ADDR AppName, \
           WS_OVERLAPPEDWINDOW, \
           CW_USEDEFAULT, CW_USEDEFAULT, \
           400, 200, NULL, NULL, \
           hInstance, NULL
    mov   hWnd, eax

    ; 消息循环
    invoke ShowWindow, eax, SW_SHOWNORMAL
    invoke UpdateWindow, eax
    
    .while TRUE
        invoke GetMessage, ADDR msg, NULL, 0, 0
        .break .if (!eax)
        invoke TranslateMessage, ADDR msg
        invoke DispatchMessage, ADDR msg
    .endw
    
    ret

RegisterWinClass proc

    mov wc.cbSize, sizeof WNDCLASSEX
    mov wc.style, CS_HREDRAW or CS_VREDRAW
    mov wc.lpfnWndProc, offset WndProc
    mov wc.cbClsExtra, 0
    mov wc.cbWndExtra, 0
    push hInstance
    pop wc.hInstance
    mov wc.hbrBackground, COLOR_WINDOW+1
    mov wc.lpszMenuName, NULL
    mov wc.lpszClassName, offset ClassName
    
    invoke RegisterClassEx, addr wc
    ret
RegisterWinClass endp

WndProc proc hWin:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
    local ps:PAINTSTRUCT
    
    .if uMsg == WM_CREATE
        ; 输入框1
        invoke CreateWindowEx, WS_EX_CLIENTEDGE, \
               ADDR EditClass, NULL, \
               WS_CHILD or WS_VISIBLE or ES_AUTOHSCROLL, \
               10, 10, 80, 25, hWin, ID_EDIT1, \
               hInstance, NULL
        mov hwndEdit1, eax
        ; 输入框2
        invoke CreateWindowEx, WS_EX_CLIENTEDGE, \
            ADDR EditClass, NULL, \
            WS_CHILD or WS_VISIBLE or ES_AUTOHSCROLL, \
            150, 10, 80, 25, hWin, ID_EDIT2, \
            hInstance, NULL
        mov hwndEdit2, eax
        ; 结果输出框
        invoke CreateWindowEx, WS_EX_CLIENTEDGE, \
            ADDR EditClass, NULL, \
            WS_CHILD or WS_VISIBLE or ES_READONLY, \
            260, 10, 100, 25, hWin, ID_EDIT_RESULT, \
            hInstance, NULL
        mov hwndResult, eax
        ; 运算符号显示框
        invoke CreateWindowEx, WS_EX_CLIENTEDGE, \
            ADDR EditClass, NULL, \
            WS_CHILD or WS_VISIBLE or ES_READONLY, \
            100, 10, 40, 25, hWin, ID_EDIT_OP, \
            hInstance, NULL
        ; 加法按钮
        invoke CreateWindowEx, NULL, \
            ADDR ButtonClass, ADDR btn_add, \
            WS_CHILD or WS_VISIBLE or BS_PUSHBUTTON, \
            10, 50, 80, 25, hWin, ID_BTN_ADD, \
            hInstance, NULL
        ; 减法按钮
        invoke CreateWindowEx, NULL, \
            ADDR ButtonClass, ADDR btn_sub, \
            WS_CHILD or WS_VISIBLE or BS_PUSHBUTTON, \
            100, 50, 80, 25, hWin, ID_BTN_SUB, \
            hInstance, NULL
        ; 乘法按钮
        invoke CreateWindowEx, NULL, \
            ADDR ButtonClass, ADDR btn_mul, \
            WS_CHILD or WS_VISIBLE or BS_PUSHBUTTON, \
            190, 50, 80, 25, hWin, ID_BTN_MUL, \
            hInstance, NULL
        ; 除法按钮
        invoke CreateWindowEx, NULL, \
            ADDR ButtonClass, ADDR btn_div, \
            WS_CHILD or WS_VISIBLE or BS_PUSHBUTTON, \
            280, 50, 80, 25, hWin, ID_BTN_DIV, \
            hInstance, NULL
        ; 正弦按钮
        invoke CreateWindowEx, NULL, \
            ADDR ButtonClass, ADDR btn_sin, \
            WS_CHILD or WS_VISIBLE or BS_PUSHBUTTON, \
            10, 90, 110, 25, hWin, ID_BTN_SIN, \
            hInstance, NULL
        ; 余弦按钮
        invoke CreateWindowEx, NULL, \
            ADDR ButtonClass, ADDR btn_cos, \
            WS_CHILD or WS_VISIBLE or BS_PUSHBUTTON, \
            130, 90, 110, 25, hWin, ID_BTN_COS, \
            hInstance, NULL
        ; 正切按钮
        invoke CreateWindowEx, NULL, \
            ADDR ButtonClass, ADDR btn_tan, \
            WS_CHILD or WS_VISIBLE or BS_PUSHBUTTON, \
            250, 90, 110, 25, hWin, ID_BTN_TAN, \
            hInstance, NULL
        
    .elseif uMsg == WM_COMMAND
        ; 处理按钮点击事件
        mov eax, wParam
        .if ax == ID_BTN_ADD
            call PerformAdd
        .elseif ax == ID_BTN_SUB
            call PerformSub
        .elseif ax == ID_BTN_MUL
            call PerformMul
        .elseif ax == ID_BTN_DIV
            call PerformDiv
        .elseif ax == ID_BTN_SIN
            call PerformSin
        .elseif ax == ID_BTN_COS
            call PerformCos
        .elseif ax == ID_BTN_TAN
            call PerformTan
        .endif
        
    .elseif uMsg == WM_DESTROY
        invoke PostQuitMessage, 0
        
    .else
        invoke DefWindowProc, hWin, uMsg, wParam, lParam
        ret
    .endif
    
    xor eax, eax
    ret
WndProc endp

; 根据是否具有小数点，判断一个浮点数是否为整数
IsInt proc num:ptr byte
    mov eax,1
    .while num != 0
        cmp byte ptr[num], '.'; 判断是否有小数点
        je isfloat
        inc num
    .endw
    ret

isfloat:
    mov eax, 0
    ret
   
IsInt endp

; 执行加法运算
PerformAdd proc
    local temp1:QWORD, temp2:QWORD
    local int1:DWORD, int2:DWORD

    ;判断是否是整数
    invoke GetDlgItemText, hWnd, ID_EDIT1, ADDR buffer, 256
    invoke IsInt, ADDR buffer
    .if eax == 0
        jmp add_float
    .endif
    invoke atoi, ADDR buffer
    mov int1, eax

    invoke GetDlgItemText, hWnd, ID_EDIT2, ADDR buffer, 256
    invoke IsInt, ADDR buffer
    .if eax == 0
        jmp add_float
    .endif
    invoke atoi, ADDR buffer
    mov int2, eax

    ; 执行加法
    mov eax, int1
    add eax, int2
    mov int1, eax
    ; 显示结果
    invoke sprintf, ADDR buffer, ADDR fmt_str, ADDR btn_add
    invoke SetDlgItemText, hWnd, ID_EDIT_OP, ADDR buffer
    invoke sprintf, ADDR buffer, ADDR fmt_int,int1 
    invoke SetDlgItemText, hWnd, ID_EDIT_RESULT, ADDR buffer
    ret
    
add_float:    
    finit

    ; 获取输入值并转换为浮点数
    invoke GetDlgItemText, hWnd, ID_EDIT1, ADDR buffer, 256
    invoke atof, ADDR buffer
    fstp temp1
    
    invoke GetDlgItemText, hWnd, ID_EDIT2, ADDR buffer, 256
    invoke atof, ADDR buffer
    fstp temp2
    
    ; 执行加法
    fld temp1
    fadd temp2
    fstp temp1
    
    ; 显示结果
    invoke sprintf, ADDR buffer, ADDR fmt_str, ADDR btn_add
    invoke SetDlgItemText, hWnd, ID_EDIT_OP, ADDR buffer
    invoke sprintf, ADDR buffer, ADDR fmt_float, temp1
    invoke SetDlgItemText, hWnd, ID_EDIT_RESULT, ADDR buffer
    
    ret
PerformAdd endp

; 执行减法运算
PerformSub proc
    local temp1:QWORD, temp2:QWORD
    local int1:DWORD, int2:DWORD

    ;判断是否是整数
    invoke GetDlgItemText, hWnd, ID_EDIT1, ADDR buffer, 256
    invoke IsInt, ADDR buffer
    .if eax == 0
        jmp sub_float
    .endif
    invoke atoi, ADDR buffer
    mov int1, eax

    invoke GetDlgItemText, hWnd, ID_EDIT2, ADDR buffer, 256
    invoke IsInt, ADDR buffer
    .if eax == 0
        jmp sub_float
    .endif
    invoke atoi, ADDR buffer
    mov int2, eax

    ; 执行减法
    mov eax,int1
    sub eax,int2
    mov int1,eax
    ; 显示结果
    invoke sprintf, ADDR buffer, ADDR fmt_str, ADDR btn_sub
    invoke SetDlgItemText, hWnd, ID_EDIT_OP, ADDR buffer
    invoke sprintf, ADDR buffer, ADDR fmt_int, int1
    invoke SetDlgItemText, hWnd, ID_EDIT_RESULT, ADDR buffer
    ret

sub_float:
    finit
    
    ; 获取输入值并转换为浮点数
    invoke GetDlgItemText, hWnd, ID_EDIT1, ADDR buffer, 256
    invoke atof, ADDR buffer
    fstp temp1
    
    invoke GetDlgItemText, hWnd, ID_EDIT2, ADDR buffer, 256
    invoke atof, ADDR buffer
    fstp temp2
    
    ; 执行减法
    fld temp1
    fsub temp2
    fstp temp1
    
    ; 显示结果
    invoke sprintf, ADDR buffer, ADDR fmt_str, ADDR btn_sub
    invoke SetDlgItemText, hWnd, ID_EDIT_OP, ADDR buffer
    invoke sprintf, ADDR buffer, ADDR fmt_float, temp1
    invoke SetDlgItemText, hWnd, ID_EDIT_RESULT, ADDR buffer
    
    ret
PerformSub endp

; 执行乘法运算
PerformMul proc
    local temp1:QWORD, temp2:QWORD
    local int1:DWORD, int2:DWORD

    ;判断是否是整数
    invoke GetDlgItemText, hWnd, ID_EDIT1, ADDR buffer, 256
    invoke IsInt, ADDR buffer
    .if eax == 0
        jmp mul_float
    .endif
    invoke atoi, ADDR buffer
    mov int1, eax

    invoke GetDlgItemText, hWnd, ID_EDIT2, ADDR buffer, 256
    invoke IsInt, ADDR buffer
    .if eax == 0
        jmp mul_float
    .endif
    invoke atoi, ADDR buffer
    mov int2, eax

    ; 执行乘法
    mov eax, int1
    imul eax, int2
    mov int1, eax
    ; 显示结果
    invoke sprintf, ADDR buffer, ADDR fmt_str, ADDR btn_mul
    invoke SetDlgItemText, hWnd, ID_EDIT_OP, ADDR buffer
    invoke sprintf, ADDR buffer, ADDR fmt_int, int1
    invoke SetDlgItemText, hWnd, ID_EDIT_RESULT, ADDR buffer
    ret


mul_float:
    finit
    
    ; 获取输入值并转换为浮点数
    invoke GetDlgItemText, hWnd, ID_EDIT1, ADDR buffer, 256
    invoke atof, ADDR buffer
    fstp temp1
    
    invoke GetDlgItemText, hWnd, ID_EDIT2, ADDR buffer, 256
    invoke atof, ADDR buffer
    fstp temp2
    
    ; 执行乘法
    fld temp1
    fmul temp2
    fstp temp1
    
    ; 显示结果
    invoke sprintf, ADDR buffer, ADDR fmt_str, ADDR btn_mul
    invoke SetDlgItemText, hWnd, ID_EDIT_OP, ADDR buffer
    invoke sprintf, ADDR buffer, ADDR fmt_float, temp1
    invoke SetDlgItemText, hWnd, ID_EDIT_RESULT, ADDR buffer
    
    ret
PerformMul endp

; 执行除法运算
PerformDiv proc
    local temp1:QWORD, temp2:QWORD
    local int1:DWORD, int2:DWORD

    ;判断是否是整数
    invoke GetDlgItemText, hWnd, ID_EDIT1, ADDR buffer, 256
    invoke IsInt, ADDR buffer
    .if eax == 0
        jmp div_float
    .endif
    invoke atoi, ADDR buffer
    mov int1, eax

    invoke GetDlgItemText, hWnd, ID_EDIT2, ADDR buffer, 256
    invoke IsInt, ADDR buffer
    .if eax == 0
        jmp div_float
    .endif
    invoke atoi, ADDR buffer
    mov int2, eax

    ; 执行除法
    xor edx,edx
    mov eax, int1
    idiv int2
    mov int1, eax
    ; 显示结果
    invoke sprintf, ADDR buffer, ADDR fmt_str, ADDR btn_div
    invoke SetDlgItemText, hWnd, ID_EDIT_OP, ADDR buffer
    invoke sprintf, ADDR buffer, ADDR fmt_int, int1
    invoke SetDlgItemText, hWnd, ID_EDIT_RESULT, ADDR buffer
    ret


div_float:    
    finit   
    ; 获取输入值并转换为浮点数
    invoke GetDlgItemText, hWnd, ID_EDIT1, ADDR buffer, 256
    invoke atof, ADDR buffer
    fstp temp1
    
    invoke GetDlgItemText, hWnd, ID_EDIT2, ADDR buffer, 256
    invoke atof, ADDR buffer
    fstp temp2
    
    ; 执行除法
    fld temp1
    fdiv temp2
    fstp temp1
    
    ; 显示结果
    invoke sprintf, ADDR buffer, ADDR fmt_str, ADDR btn_div
    invoke SetDlgItemText, hWnd, ID_EDIT_OP, ADDR buffer
    invoke sprintf, ADDR buffer, ADDR fmt_float, temp1
    invoke SetDlgItemText, hWnd, ID_EDIT_RESULT, ADDR buffer
    
    ret
PerformDiv endp

; 执行正弦运算
PerformSin proc
    local temp1:QWORD
    
    ; 获取输入值并转换为浮点数
    invoke GetDlgItemText, hWnd, ID_EDIT1, ADDR buffer, 256
    invoke atof, ADDR buffer
    fstp temp1
    
    ; 执行正弦
    fld temp1
    fsin; 计算正弦值并存入xmm0寄存器中
    fstp temp1; 将结果存入temp1中
    
    ; 显示结果
    invoke sprintf, ADDR buffer, ADDR fmt_str, ADDR btn_sin
    invoke SetDlgItemText, hWnd, ID_EDIT_OP, ADDR buffer
    invoke sprintf, ADDR buffer, ADDR fmt_float, temp1
    invoke SetDlgItemText, hWnd, ID_EDIT_RESULT, ADDR buffer
    
    ret
PerformSin endp

; 执行余弦运算
PerformCos proc
    local temp1:QWORD
    
    ; 获取输入值并转换为浮点数
    invoke GetDlgItemText, hWnd, ID_EDIT1, ADDR buffer, 256
    invoke atof, ADDR buffer
    fstp temp1
    
    ; 执行余弦
    fld temp1
    fcos
    fstp temp1
    
    ; 显示结果
    invoke sprintf,ADDR buffer, ADDR fmt_str, ADDR btn_cos
    invoke SetDlgItemText, hWnd, ID_EDIT_OP, ADDR buffer
    invoke sprintf, ADDR buffer, ADDR fmt_float, temp1
    invoke SetDlgItemText, hWnd, ID_EDIT_RESULT, ADDR buffer
    
    ret
PerformCos endp

; 执行正切运算
PerformTan proc
    local temp1:QWORD
    
    ; 获取输入值并转换为浮点数
    invoke GetDlgItemText, hWnd, ID_EDIT1, ADDR buffer, 256
    invoke atof, ADDR buffer
    fstp temp1
    
    ; 执行正切
    fld temp1
    fptan; 计算正切值并存入xmm0寄存器中
    fstp temp1; 将结果存入temp1中
    
    ; 显示结果
    invoke sprintf, ADDR buffer, ADDR fmt_str, ADDR btn_tan
    invoke SetDlgItemText, hWnd, ID_EDIT_OP, ADDR buffer
    invoke sprintf, ADDR buffer, ADDR fmt_float, temp1
    invoke SetDlgItemText, hWnd, ID_EDIT_RESULT, ADDR buffer
    
    ret
PerformTan endp


end start