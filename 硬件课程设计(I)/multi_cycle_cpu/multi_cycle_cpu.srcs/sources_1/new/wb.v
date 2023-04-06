`timescale 1ns / 1ps
module wb( // 写回级
    input WB_valid, // 写回级有效
    input [69:0] MEM_WB_bus_r, // MEM->WB 总线
    output rf_wen, // 寄存器写使能
    output [ 4:0] rf_wdest, // 寄存器写地址
    output [31:0] rf_wdata, // 寄存器写数据
    output WB_over, // WB 模块执行完成
    //展示 PC
    output [ 31:0] WB_pc
    );
//-----{MEM->WB 总线}begin
//寄存器堆写使能和写地址
    wire wen;
    wire [4:0] wdest;
//MEM 传来的 result
    wire [31:0] mem_result;
//pc
    wire [31:0] pc;
    assign {wen,wdest,mem_result,pc} = MEM_WB_bus_r;
//-----{MEM->WB 总线}end
//-----{WB 执行完成}begin
//WB 模块只是传递寄存器堆的写使能/写地址和写数据
//可在一拍内完成
//故 WB_valid 即是 WB_over 信号
    assign WB_over = WB_valid;
//-----{WB 执行完成}end
//-----{WB->regfile 信号}begin
    assign rf_wen = wen & WB_valid;
    assign rf_wdest = wdest;
    assign rf_wdata = mem_result;
//-----{WB->regfile 信号}end
//-----{展示 WB 模块的 PC 值}begin
    assign WB_pc = pc;
//-----{展示 WB 模块的 PC 值}end
endmodule