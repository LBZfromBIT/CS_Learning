`timescale 1ns / 1ps
// 显示控制模块
module display_control(
input CLOCK, // 时钟信号
input RESET, // 复位信号
input [7:0] num, // 要显示的数字，2 位 BCD 码或十六进制数
output reg [6:0] DISP, // 七段数码管的 LED 信号
output reg [1:0] DISP_D // 七段数码管的段选信号
);

//参数 CLOCKS_PER_FRAME 代表每隔2ms就刷新一遍显示的数字
parameter CLOCKS_PER_FRAME=4,CLOCKS_PER_HALF_FRAME=CLOCKS_PER_FRAME/2; //为了仿真取4个周期一刷新
integer CLOCK_COUNTER=0; // 时钟计数器
wire [6:0] DISP_LO,DISP_HI; // 分别是低位和高位的七段数码管的 LED 信号

// 时钟计数：
always @(posedge CLOCK or negedge RESET) begin
    if (!RESET||CLOCK_COUNTER==CLOCKS_PER_FRAME) begin
        //复位或计数器满
        CLOCK_COUNTER=0;
    end
    CLOCK_COUNTER=CLOCK_COUNTER+1;//重启计数
end

// 显示数字：
always @(posedge CLOCK or negedge RESET) begin
    if (!RESET) begin// 按住复位按钮时点亮所有数码管
        DISP_D<=2'b11;
        DISP<=7'h7f;
    end 
    else if (CLOCK_COUNTER<=CLOCKS_PER_HALF_FRAME) begin
        //前半个刷新周期刷新低位数码管
        DISP_D<=2'b01;
        DISP<=DISP_LO;
    end 
    else begin
        //后半个刷新周期刷新高位数码管
        DISP_D<=2'b10;
        DISP<=DISP_HI;
    end
end

// 实例化十六进制码到七段数码管转换模块
num2LED num2DISP1(//低位数码管
.num(num[3:0]),
.DISP(DISP_LO)
);

num2LED num2DISP2(//高位数码管
.num(num[7:4]),
.DISP(DISP_HI)
);
endmodule
