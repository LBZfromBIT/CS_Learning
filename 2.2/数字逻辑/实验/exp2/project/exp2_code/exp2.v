module add_three(A,B,C,D,W,X,Y,Z);
//定义输入输出
    input A,B,C,D;
    output W,X,Y,Z;
//定义内部变量
    wire F;
    assign F=C|D;
    assign W=A|(B&F);
    assign X=(B&~F)|(~B&F);
    assign Y=(~C&~D)|(C&D);
    assign Z=~D;
endmodule


