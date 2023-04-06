`timescale 1ns / 1ps
`define STARTADDR 32'd0 // ������ʼ��ַΪ 0
module fetch( // ȡָ��
    input clk, // ʱ��
    input resetn, // ��λ�źţ��͵�ƽ��Ч
    input IF_valid, // ȡָ����Ч�ź�
    input next_fetch,// ȡ��һ��ָ��������� PC ֵ
    input [31:0] inst, // inst_rom ȡ����ָ��
    input [32:0] jbr_bus, // ��ת����
    output [31:0] inst_addr, // ���� inst_rom ��ȡָ��ַ
    output reg IF_over, // IF ģ��ִ�����
    output [63:0] IF_ID_bus, // IF->ID ����
    //չʾ PC ��ȡ����ָ��
    output [31:0] IF_pc,
    output [31:0] IF_inst
    );
//-----{��������� PC}begin
    wire [31:0] next_pc;
    wire [31:0] seq_pc;
    reg [31:0] pc;
//��ת pc
    wire jbr_taken;
    wire [31:0] jbr_target;
    assign {jbr_taken, jbr_target} = jbr_bus; //��ת����
    assign seq_pc[31:2] = pc[31:2] + 1'b1; //��һָ���ַ��PC=PC+4
    assign seq_pc[1 :0] = pc[1:0];
// ��ָ���ָ����ת��Ϊ��ת��ַ������Ϊ��һָ��
    assign next_pc = jbr_taken ? jbr_target : seq_pc;
    always @(posedge clk) // PC ���������
    begin
        if (!resetn)
        begin
            pc <= `STARTADDR; // ��λ��ȡ������ʼ��ַ
        end
        else if (next_fetch)
        begin
            pc <= next_pc; // ����λ��ȡ��ָ��
        end
    end
//-----{��������� PC}end
//-----{���� inst_rom ��ȡָ��ַ}begin
    assign inst_addr = pc;
//-----{���� inst_rom ��ȡָ��ַ}end
//-----{IF ִ�����}begin
    always @(posedge clk)
    begin
        IF_over <= IF_valid;
    end
//���ָ�� rom Ϊ�첽���ģ��� IF_valid ���� IF_over �źţ�
//��ȡָһ�����
//-----{IF ִ�����}end
//-----{IF->ID ����}begin
    assign IF_ID_bus = {pc, inst};
//-----{IF->ID ����}end
//-----{չʾ IF ģ��� PC ֵ��ָ��}begin
    assign IF_pc = pc;
    assign IF_inst = inst;
//-----{չʾ IF ģ��� PC ֵ��ָ��}end
endmodule