`timescale  1ns / 1ps//时间单位与时间精度

module tb_add_three();//testbench模块

    // testbench的控制信号
    parameter PERIOD  = 5;//时钟的周期10ns

    //输入信号
    reg   A;
    reg   B;
    reg   C;
    reg   D;

    //输出信号
    wire  W;
    wire  X;
    wire  Y;
    wire  Z;

    //定义激励信号
    initial
    begin
        A=1'b0;
        #(PERIOD*8) A=1'b1;
    end

    initial
    begin
        B=1'b0;
        #(PERIOD*4) B=1'b1;
        #(PERIOD*4) B=1'b0;
    end    

    initial 
    begin
        C=1'b0;
        #(PERIOD*2) C=1'b1;
        #(PERIOD*2) C=1'b0;
        #(PERIOD*2) C=1'b1;
        #(PERIOD*2) C=1'b0;
    end

    initial
    begin
        D=1'b0;
        #(PERIOD) D=1'b1;
        #(PERIOD) D=1'b0;
        #(PERIOD) D=1'b1;
        #(PERIOD) D=1'b0;
        #(PERIOD) D=1'b1;
        #(PERIOD) D=1'b0;
        #(PERIOD) D=1'b1;
        #(PERIOD) D=1'b0;
        #(PERIOD) D=1'b1;
    end    
    //实例化被测试模块
    add_three  test_add_three (
        .A ( A ),
        .B ( B ),
        .C ( C ),
        .D ( D ),

        .W ( W ),
        .X ( X ),
        .Y ( Y ),
        .Z ( Z )
    );

endmodule