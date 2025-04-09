; structs.inc
; 该文件定义了数据结构，例如贪吃蛇的坐标和长度。

; 定义贪吃蛇的坐标结构
SnakeCoord STRUCT
    x DWORD 0      ; x坐标
    y DWORD 0      ; y坐标
SnakeCoord ENDS

; 定义贪吃蛇的结构
Snake STRUCT
    len DWORD ?          ; 贪吃蛇的长度
    body SnakeCoord 100 dup(<>)  ; 贪吃蛇的身体坐标数组，最多100个坐标
Snake ENDS