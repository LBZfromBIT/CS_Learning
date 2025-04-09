`timescale 1ns / 1ps
module testbench();
reg CLOCK=1'b0,RESET=1'b0; // 时钟和复位信号
wire LED_RED,LED_GREEN; // 红绿灯 LED 信号
wire [6:0] DISP; // 七段数码管的 LED 信号
wire [1:0] DISP_D; // 七段数码管的段选信号
parameter PERIOD=4,HALF_PERIOD=PERIOD/2; // 时钟周期4ns

// 生成时钟：
always begin
    #HALF_PERIOD;//2ns反转一次
    CLOCK=~CLOCK;
end

initial begin
    RESET=1'b1;
    #(HALF_PERIOD*5/2);//5ns后开始复位
    RESET=1'b0;
    #PERIOD;//4ns后开始测试
    RESET=1'b1;
    #(PERIOD*500); // 500 个周期后结束仿真
    $finish;
end

// 实例化待测模块
traffic_light traffic_light1(
.CLOCK(CLOCK),
.RESET(RESET),
.LED_RED(LED_RED),
.LED_GREEN(LED_GREEN),
.DISP(DISP),
.DISP_D(DISP_D)
);
endmodule