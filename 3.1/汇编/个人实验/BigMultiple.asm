.386
.model flat,stdcall
option casemap:none

include \masm32\include\masm32.inc
include \masm32\include\kernel32.inc
include \masm32\include\msvcrt.inc

includelib \masm32\lib\masm32.lib
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\msvcrt.lib

printf PROTO C :DWORD,:VARARG
gets PROTO C :DWORD
strlen PROTO C :DWORD

;---------------------------------------------
.DATA
;缓冲区
sbuffer1 byte 256 dup(0);大数1缓冲区
sbuffer2 byte 256 dup(0);大数2缓冲区
sresult byte 513 dup(0);结果缓冲区
ibuffer1 dword 256 dup(0);存放数字1的反写数字串
ibuffer2 dword 256 dup(0);存放数字2的反写字符串
iresult dword 513 dup(0);存放结果数字的反写字符串

;提示信息
enter1 byte "Enter number 1:",0ah,0
enter2 byte "Enter number 2:",0ah,0
posresult byte "Result is: %s",0ah,0
negresult byte "Result is: -%s",0ah,0

;格式化字符串
form_in byte "%s",0
intstr byte "%d,%d,%d",0ah,0


;全局变量
lenth1 dword 0;ibuffer1长
lenth2 dword 0;ibuffer2长
lenthr dword 0;iresult长
negtive byte 0;结果负否
radix dword 10;除数
;-----------------------------------------------

;-----------------------------------------------
.CODE
;================================================
;brief:将字符串转化为数字并反转存入地址，过程中判断该数负否
;param:
;    src-源地址
;    dst-目的地址
;return:
;    字符串长度
S2I PROC stdcall src:DWORD,dst:DWORD
    LOCAL len:DWORD
    ;保存寄存器
    push esi
    push ecx

    mov esi,src
    .if byte ptr[esi] == 2DH  ;如果为负数
        xor negtive,1 ;符号作用一次
        inc esi
    .endif

    invoke strlen,esi;从esi位置起计算长度
    mov len,eax
    mov ecx,len
L1:
    ;获得数字压入栈
    ;eax=esi[i]
    movzx eax,byte ptr[esi]
    sub eax,'0';转换为数字
    
    push eax;压栈
    inc esi
    loop L1

    ;读出数字
    mov ecx,len
    mov esi,dst
L2:
    pop eax
    mov dword ptr[esi],eax
    add esi,4
    loop L2
    
    mov eax,len
    
    ;恢复寄存器
    pop ecx
    pop esi
    ret
S2I ENDP
;===============================================

;===============================================
;brief:将数字串处理进位后转化为字符并反转存入地址
;param:
;    src-源字符串地址
;    dest-目的字符串地址
;return:
;    字符串长度
I2S PROC stdcall src:DWORD,dst:DWORD
    ;保护寄存器
    push ecx
    push esi
    push edx


    ;采用循环进行进位,src的长度在lenthr中
    mov ecx,lenthr
    mov esi,src
L3:
    mov eax,dword ptr[esi]
    xor edx,edx
    div radix
    add dword ptr[esi+4],eax;商进位
    mov dword ptr[esi],edx;余数写入
    add esi,4
    loop L3

    ;进位处理完毕，考虑从后向前遍历结果确定真实长度
    mov esi,src
    mov ecx,lenthr
L4:
    cmp dword ptr iresult[4*ecx],0
    jne endL4
    dec ecx
    jmp L4
endL4:
    ;写入真实长度
    inc ecx
    mov lenthr,ecx
    
    ;将结果写入dst
    mov esi,src
L5:
    mov eax,dword ptr[esi]
    add eax,'0'
    push eax
    add esi,4
    loop L5
    
    mov esi,dst
    mov ecx,lenthr
L6:
    pop eax
    mov byte ptr[esi],al
    inc esi
    loop L6

    ;恢复寄存器
    pop edi
    pop edx
    pop esi
    pop ecx
    ret
I2S ENDP
;================================================


;================================================
;brief:大数乘法
;param:
;    num1-大数1地址
;    num2-大数2地址
;    result-结果地址
;return:
;    无
BigMultiple PROC stdcall num1:DWORD,num2:DWORD,result:DWORD
    ;保存寄存器
    push ebx
    push ecx
    push edx
    push esi
    push edi

    ;获取两个大数长度并反转
    invoke S2I,num1,offset ibuffer1
    mov lenth1,eax

    invoke S2I,num2,offset ibuffer2
    mov lenth2,eax



    mov ebx,0;外层索引i
outer:
    cmp ebx,lenth1
    jnb end_outer
    xor ecx,ecx;内层索引j
inner:
    xor edx,edx
    mov eax,dword ptr ibuffer1[4*ebx];num1的当前位
    mul dword ptr ibuffer2[4*ecx];num1*num2->edx:eax
    
    ;写入结果
    mov esi,ebx
    add esi,ecx;edi=ebx+ecx为结果本位
    add dword ptr iresult[4*esi],eax;先将结果写入再调用函数处理进位
    inc ecx
    cmp ecx,lenth2
    jb inner
    inc ebx
    jmp outer
end_outer:
    ;给出iresult的可能长度
    mov ecx,lenth1
    add ecx,lenth2
    inc ecx;lenthr=lenth1+lenth2+1
    mov lenthr,ecx
    ;调用函数处理结果
    invoke I2S,offset iresult,result

    ;恢复寄存器
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    ret
BigMultiple ENDP
;================================================

;========================主函数==================
start:         
    ;输入两个大数
    invoke printf,offset enter1
    invoke gets,offset sbuffer1
    invoke printf,offset enter2
    invoke gets,offset sbuffer2
       
    ;调用大数乘法函数
    invoke BigMultiple,offset sbuffer1,offset sbuffer2,offset sresult
    ;输出结果
    .if negtive==1
        invoke printf,offset negresult,offset sresult
    .else
        invoke printf,offset posresult,offset sresult
    .endif
    ret
;================================================
END start