`timescale 1ns / 1ps
module exe( // ִ�м�
    input EXE_valid, // ִ�м���Ч��
    input [149:0] ID_EXE_bus_r,// ID->EXE ����
    output EXE_over, // EXE ģ��ִ�����
    output [105:0] EXE_MEM_bus, // EXE->MEM ����
    //չʾ PC
    output [ 31:0] EXE_pc
    );
//-----{ID->EXE ����}begin
//EXE ��Ҫ�õ�����Ϣ
//ALU ����Դ�������Ϳ����ź�
    wire [11:0] alu_control;
    wire [31:0] alu_operand1;
    wire [31:0] alu_operand2;
//�ô���Ҫ�õ��� load/store ��Ϣ
    wire [3:0] mem_control; //MEM ��Ҫʹ�õĿ����ź�
    wire [31:0] store_data; //store �����Ĵ������
//д����Ҫ�õ�����Ϣ
    wire rf_wen; //д�صļĴ���дʹ��
    wire [4:0] rf_wdest; //д�ص�Ŀ�ļĴ���
//pc
    wire [31:0] pc;
    assign {alu_control,
    alu_operand1,
    alu_operand2,
    mem_control,
    store_data,
    rf_wen,
    rf_wdest,
    pc } = ID_EXE_bus_r;
//-----{ID->EXE ����}end
//-----{ALU}begin
    wire [31:0] alu_result;
    alu alu_module(
    .alu_control (alu_control ), // I, 12, ALU �����ź�
    .alu_src1 (alu_operand1), // I, 32, ALU ������ 1
    .alu_src2 (alu_operand2), // I, 32, ALU ������ 2
    .alu_result (alu_result ) // O, 32, ALU ���
    );
//-----{ALU}end
//-----{EXE ִ�����}begin
//�����Ƕ����ڵģ��������������
//������ ALU ���㶼����һ�������
//�� EXE ģ��һ�ľ���������в���
//�� EXE_valid ���� EXE_over �ź�
    assign EXE_over = EXE_valid;
//-----{EXE ִ�����}end
//-----{EXE->MEM ����}begin
    assign EXE_MEM_bus = {mem_control,store_data, //load/store ��Ϣ�� store ����
    alu_result, //alu ������
    rf_wen,rf_wdest, // WB ��Ҫʹ�õ��ź�
    pc}; // PC
//-----{EXE->MEM ����}end
//-----{չʾ EXE ģ��� PC ֵ}begin
    assign EXE_pc = pc;
//-----{չʾ EXE ģ��� PC ֵ}end
endmodule