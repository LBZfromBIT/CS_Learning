`timescale 1ns/1ps

module status(
    input wire A,//输入
    input wire clk,//时钟信号
    input wire reset,//复位信号
    output wire B//输出
);
    reg X,Y,Z;//三个寄存器，储存状态机状态

    assign B=X&&Y&&!Z; 
    always @(posedge clk) begin//时钟上沿触发
        if(!reset)begin
            X<=(Y&&!Z&&!A)||(X&&Y&&!Z);
            Y<=(Y&&!Z&&!A)||(X&&Y&&!Z)||(!X&&Z&&!A);
            Z<=!X&&!Y&&!A;
        end
        else begin
            X<=0;
            Y<=0;
            Z<=0;    
        end
    end    
endmodule