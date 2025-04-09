`timescale 1ns / 1ps
// 十六进制码到七段数码管转换模块
module num2LED(
input [3:0] num, // 输入一位十六进制数，占4位
output [6:0] DISP // 输出七段数码管的 LED 信号，总线[6=0]对应七位数码管A-G
);
/*
  只需考虑A-G七位数码管即可，DP数码管不使用
  由于数码管为共阴极管，因此
  0输出低电平——>LED不亮，1输出高电平——>LED亮
*/

// 数码管A
assign DISP[6]=(num==4'h1||num==4'h4||num==4'hb||num==4'hc||num==4'hd)?1'b0:1'b1; 
//数码管B
assign DISP[5]=(num==4'h5||num==4'h6||num==4'hb||num==4'hc||num==4'he||num==4'hf)?1'b0:1'b1; 
//数码管C
assign DISP[4]=(num==4'h2||num==4'hc||num==4'he||num==4'hf)?1'b0:1'b1; 
//数码管D
assign DISP[3]=(num==4'h1||num==4'h4||num==4'h7||num==4'ha||num==4'hf)?1'b0:1'b1; 
//数码管E
assign DISP[2]=(num==4'h1||num==4'h3||num==4'h4||num==4'h5||num==4'h7||num==4'h9)?1'b0:1'b1; 
//数码管F
assign DISP[1]=(num==4'h1||num==4'h2||num==4'h3||num==4'h7||num==4'hc||num==4'hd)?1'b0:1'b1; 
//数码管G
assign DISP[0]=(num==4'h0||num==4'h1||num==4'h7)?1'b0:1'b1; 
endmodule