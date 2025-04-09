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

; 常量定义
BUFFER_SIZE EQU 1024
INVALID_HANDLE_VALUE EQU -1
EDITSTYLE     equ (WS_CHILD or WS_VISIBLE or WS_BORDER or ES_AUTOHSCROLL)
BUTTONSTYLE   equ (WS_CHILD or WS_VISIBLE or BS_PUSHBUTTON)


.data
    szWindowTitle db "Text File Comparator", 0
    szSame        db "The two files are the same.", 0
    szDiff        db "The two files differ at line %d %s %s", 0
    szFilePath1   db 256 dup(0)
    szFilePath2   db 256 dup(0)
    szMessage     db 512 dup(0)
    szEnter       db "Enter the file path:", 0
    szBuffer1     db 256 dup(0)
    szBuffer2     db 256 dup(0)
    szErrorOpen   db "Error opening files!", 0
    szErrorReg    db "RegisterClassEx failed!", 0
    szErrorIns    db "GetModuleHandle failed!", 0

    hInstance     dd 0
    hWnd          dd 0
    hEditFile1    dd 0
    hEditFile2    dd 0
    hButton       dd 0
    wc            WNDCLASSEX <>
    msg           MSG <>
    
    szEditClass   db "EDIT", 0
    szButtonClass db "BUTTON", 0
    szCompareText db "Compare", 0
    szClassName   db "FileCompareClass", 0
    szStaticClass db "STATIC", 0

.code
;Read one line from file
ReadOneLine PROC filehandle:HANDLE,buffer:DWORD
    LOCAL fileptr:DWORD
    LOCAL input_char:BYTE
    
    push ebx
    
    mov ebx,buffer
    .while TRUE
        invoke ReadFile,filehandle,addr input_char,1,addr fileptr,NULL
        .break .if !fileptr;EOF
        .break .if input_char == 10;LF
        mov AL,input_char
        mov [ebx],AL
        inc ebx
    .endw

    mov AL,0
    mov [ebx],AL;NULL ending
    invoke lstrlen,buffer
    pop ebx
    ret
ReadOneLine ENDP

;Open file for comparison
CompareFiles PROC
    LOCAL filehandle1:HANDLE
    LOCAL filehandle2:HANDLE
    LOCAL ptr1:DWORD
    LOCAL ptr2:DWORD
    LOCAL line:DWORD
    LOCAL differentline[1000]:BYTE

    mov line, 0

  
    invoke GetWindowText,hEditFile1,addr szFilePath1,sizeof szFilePath1
    invoke GetWindowText,hEditFile2,addr szFilePath2,sizeof szFilePath2

    
    ; 打开第一个文件
    invoke CreateFile,
        addr szFilePath1,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL 
    mov filehandle1, eax
    
    ; 检查第一个文件是否打开成功
    .if eax == INVALID_HANDLE_VALUE
        invoke MessageBox, 0, addr szErrorOpen, addr szWindowTitle, MB_OK
        ret     ; 直接返回，因为第一个文件就打开失败了
    .endif

    ; 打开第二个文件
    invoke CreateFile,
        addr szFilePath2,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    mov filehandle2, eax
    
    ; 检查第二个文件是否打开成功
    .if eax == INVALID_HANDLE_VALUE
        invoke MessageBox, 0, addr szErrorOpen, addr szWindowTitle, MB_OK
        invoke CloseHandle, filehandle1  ; 关闭第一个文件
        ret
    .endif

READ_LINE_START:
    inc line
    invoke RtlZeroMemory,addr szBuffer1,sizeof szBuffer1
    invoke ReadOneLine,filehandle1,addr szBuffer1
    mov ptr1,eax
    invoke RtlZeroMemory,addr szBuffer2,sizeof szBuffer2
    invoke ReadOneLine,filehandle2,addr szBuffer2
    mov ptr2,eax

    cmp ptr1,0
    jne FILE1_NOT_EMPTY
    cmp ptr2,0
    je COMPARE_END
    jmp DIFFERENT_LINE_FOUND

FILE1_NOT_EMPTY:
    cmp ptr2,0
    jne BOTH_NOT_EMPTY
    jmp DIFFERENT_LINE_FOUND

BOTH_NOT_EMPTY:
    invoke lstrcmp,addr szBuffer1,addr szBuffer2
    .if eax != 0
        jmp DIFFERENT_LINE_FOUND
    .endif
    jmp READ_LINE_START

COMPARE_END:
    invoke MessageBox,0,addr szSame,addr szWindowTitle,MB_OK
    invoke CloseHandle,filehandle1
    invoke CloseHandle,filehandle2
    ret

DIFFERENT_LINE_FOUND:
    invoke wsprintf,addr szMessage,addr szDiff,line,addr szBuffer1,addr szBuffer2
    invoke MessageBox,0,addr szMessage,addr szWindowTitle,MB_OK
    invoke CloseHandle,filehandle1
    invoke CloseHandle,filehandle2
    ret
CompareFiles ENDP

; Window procedure
WndProc PROC hWin:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
    .if uMsg == WM_DESTROY
        invoke PostQuitMessage, 0
    .elseif uMsg == WM_CLOSE
        invoke DestroyWindow, hWin
    .elseif uMsg == WM_COMMAND
        ; Compare when button pressed (ID 3)
        mov eax, wParam
        cmp ax, 3
        jne def_proc
        invoke CompareFiles
    .endif

def_proc:
    invoke DefWindowProc, hWin, uMsg, wParam, lParam
    ret
WndProc ENDP

start:
    ; Get instance
    invoke GetModuleHandle, NULL
    mov hInstance, eax
    .if eax == 0
        invoke MessageBox, 0, addr szErrorIns, addr szWindowTitle, MB_OK
        invoke ExitProcess, 0
    .endif

    ; Register window class
    mov wc.cbSize, sizeof WNDCLASSEX
    mov wc.style, CS_HREDRAW or CS_VREDRAW
    mov wc.lpfnWndProc, offset WndProc
    mov wc.cbClsExtra, 0
    mov wc.cbWndExtra, 0
    push hInstance
    pop wc.hInstance
    invoke LoadCursor, NULL, IDC_ARROW
    mov wc.hCursor, eax
    invoke LoadIcon, NULL, IDI_APPLICATION
    mov wc.hIcon, eax
    mov wc.hbrBackground, COLOR_WINDOW+1
    mov wc.lpszMenuName, NULL
    mov wc.lpszClassName, offset szClassName
    invoke RegisterClassEx, addr wc
    .if eax == 0
        invoke MessageBox, 0, addr szErrorReg, addr szWindowTitle, MB_OK
        invoke ExitProcess, 0
    .endif

    ; Create main window
    invoke CreateWindowEx, 0, addr szClassName, addr szWindowTitle,\
           WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,\
           500, 400, NULL, NULL, hInstance, NULL
    mov hWnd, eax
    .if eax == 0
        invoke MessageBox, 0, addr szErrorOpen, addr szWindowTitle, MB_OK
        invoke ExitProcess, 0
    .endif

    ; Create labels
    invoke CreateWindowEx, 0, addr szStaticClass, addr szEnter,\
           WS_CHILD or WS_VISIBLE, 10, 10, 480, 20, hWnd, NULL, hInstance, NULL
    ; Create edit fields
    invoke CreateWindowEx, 0, addr szEditClass, NULL,\
           EDITSTYLE, 10, 70, 460, 20, hWnd, 1, hInstance, NULL
    mov hEditFile1, eax
    invoke CreateWindowEx, 0, addr szEditClass, NULL,\
           EDITSTYLE, 10, 110, 460, 20, hWnd, 2, hInstance, NULL
    mov hEditFile2, eax

    ; Create compare button
    invoke CreateWindowEx, 0, addr szButtonClass, addr szCompareText,\
           BUTTONSTYLE, 10, 150, 460, 30, hWnd, 3, hInstance, NULL
    mov hButton, eax

    invoke ShowWindow, hWnd, SW_SHOWNORMAL
    invoke UpdateWindow, hWnd

msg_loop:
    invoke GetMessage, addr msg, NULL, 0, 0
    cmp eax, 0
    je end_prog
    invoke TranslateMessage, addr msg
    invoke DispatchMessage, addr msg
    jmp msg_loop

end_prog:
    invoke ExitProcess, 0

end start
