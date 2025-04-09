`timescale 1ns / 1ps//指定时间单位和时间精度
// 顶层控制模块
module traffic_light(
input CLOCK, // 时钟信号
input RESET, // 复位信号
output reg LED_RED, // 红灯信号
output reg LED_GREEN, // 绿灯信号
output [6:0] DISP, // 七段数码管的 LED 信号
output [1:0] DISP_D // 七段数码管的段选信号
);

/*参数ONE_SECOND 是指多少个时钟周期被当成红绿灯的一秒，1s=10^9ns*/
parameter ONE_SECOND=8,HALF_SECOND=ONE_SECOND/2; //为了仿真，取8个周期一秒
/*两个参数分别为红灯和绿灯的持续时间和闪烁时间（秒），采用2组BCD码编码，共占8位*/
parameter RED_TIME=8'h30,GREEN_TIME=8'h20,BLINK_TIME_RED=8'h03,BLINK_TIME_GREEN=8'h03; 
integer CLOCK_COUNTER=0; // 时钟计数器

reg [7:0] num=RED_TIME; // 现在倒计时上显示的数字，同样采用2组BCD码编码，每组BCD码对应一个数位
reg isgreen=1'b0; // 现在是红灯亮还是绿灯亮，0 = 红灯亮， 1 = 绿灯亮

// 时钟计数：
always @(posedge CLOCK or negedge RESET) begin
    if (!RESET||CLOCK_COUNTER==ONE_SECOND) begin
        //复位或计数器达到一秒，重置
        CLOCK_COUNTER=0;
    end
    CLOCK_COUNTER=CLOCK_COUNTER+1;//重启计数
end

// 控制显示的数字和红绿灯哪个亮：
always @(posedge CLOCK or negedge RESET) begin
    if (!RESET) begin
        isgreen=1'b0; // 复位后红灯先亮
        num=RED_TIME;//红灯时间
    end 
    else if (CLOCK_COUNTER==ONE_SECOND) begin//计数器达到一秒
        if (num[3:0]!=4'h0) begin//后四位BCD码不为0
            num=num-8'h01;//后4位减1即可
        end 
        else begin
            if (num[7:4]!=4'h0) begin//前4位BCD码不为0，后4位BCD码为0
                num={num[7:4]-4'h1,4'h9};//前4位减1，后4位刷新为9
            end 
            else begin//达到00
               isgreen=~isgreen;//反转灯色
               num=isgreen?GREEN_TIME:RED_TIME;//三目运算符,isgreen反转后为0（假）即num换红灯时间，否则换绿灯时间
            end
        end
    end
end

// 点亮该亮的红绿灯
always @(posedge CLOCK or negedge RESET) begin
    if (!RESET) begin// 按住复位按钮时红绿灯都亮
        LED_RED<=1'b1;
        LED_GREEN<=1'b1; 
    end 
    else if (isgreen) begin//
        LED_RED<=1'b0;//红灯不亮
        /*判断是否在闪烁时间段内且计数器在前半秒中，通过前半秒不亮后半秒亮实现闪烁*/
        LED_GREEN<=(num<=BLINK_TIME_GREEN&&CLOCK_COUNTER<=HALF_SECOND)?1'b0:1'b1;
    end 
    else begin//反过来
        LED_GREEN<=1'b0;
        LED_RED<=(num<=BLINK_TIME_RED&&CLOCK_COUNTER<=HALF_SECOND)?1'b0:1'b1;
    end
end

// 实例化显示控制模块，通过 num 来控制显示的数字
display_control display_control1(
.CLOCK(CLOCK),
.RESET(RESET),
.num(num),
.DISP(DISP),
.DISP_D(DISP_D)
);
endmodule