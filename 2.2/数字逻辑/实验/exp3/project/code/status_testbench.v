`timescale 1ns/1ps

module status_testbench();
    parameter PERIOD = 10;//时间周期
    reg clk;//时钟信号，每5ns反转
    initial begin
        clk = 0 ;
        forever begin
            #(PERIOD/2) clk = ~clk;
        end
    end

    reg reset;//复位信号
    initial begin
        reset=1;
        forever begin
            #(PERIOD) reset=0;
            #(PERIOD*5) reset=1;
        end
    end    
    
    reg A;
    initial begin
        //复位位置
        A=1;
        //测试串1：00000
        #PERIOD A=0;
        #PERIOD A=0;
        #PERIOD A=0;
        #PERIOD A=0;
        #PERIOD A=0;
        //复位位置
        #PERIOD A=1;
        //测试串2：10000
        #PERIOD A=1;
        #PERIOD A=0;
        #PERIOD A=0;
        #PERIOD A=0;
        #PERIOD A=0;
        //复位位置
        #PERIOD A=1;
        //测试串3：00100
        #PERIOD A=0;
        #PERIOD A=0;
        #PERIOD A=1;
        #PERIOD A=0;
        #PERIOD A=0;
        //复位位置
        #PERIOD A=1;
        //测试串4：00001
        #PERIOD A=0;
        #PERIOD A=0;
        #PERIOD A=0;
        #PERIOD A=0;
        #PERIOD A=1;
        //结束测试
        $stop;       
    end

    wire B;

    //模块实例化
    status status_test(
        .A(A),
        .clk(clk),
        .reset(reset),
        .B(B)
    );  

endmodule


