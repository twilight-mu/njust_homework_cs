`timescale 1ns / 1ps
module mem( // �ô漶
    input clk, // ʱ��
    input MEM_valid, // �ô漶��Ч�ź�
    input [105:0] EXE_MEM_bus_r,// EXE->MEM ����
    input [ 31:0] dm_rdata, // �ô������
    output [ 31:0] dm_addr, // �ô��д��ַ
    output reg [ 3:0] dm_wen, // �ô�дʹ��
    output reg [ 31:0] dm_wdata, // �ô�д����
    output MEM_over, // MEM ģ��ִ�����
    output [ 69:0] MEM_WB_bus, // MEM->WB ����
    //չʾ PC
    output [ 31:0] MEM_pc
    );
//-----{EXE->MEM ����}begin
//�ô���Ҫ�õ��� load/store ��Ϣ
    wire [3 :0] mem_control; //MEM ��Ҫʹ�õĿ����ź�
    wire [31:0] store_data; //store �����Ĵ������
//alu ������
    wire [31:0] alu_result;
//д����Ҫ�õ�����Ϣ
    wire rf_wen; //д�صļĴ���дʹ��
    wire [4:0] rf_wdest; //д�ص�Ŀ�ļĴ���
//pc
    wire [31:0] pc;
    assign {mem_control,
    store_data,
    alu_result,
    rf_wen,
    rf_wdest,
    pc } = EXE_MEM_bus_r;
//-----{EXE->MEM ����}end
//-----{load/store �ô�}begin
    wire inst_load; //load ����
    wire inst_store; //store ����
    wire ls_word; //load/store Ϊ�ֽڻ�����,0:byte;1:word
    wire lb_sign; //load һ�ֽ�Ϊ�з��� load
    assign {inst_load,inst_store,ls_word,lb_sign} = mem_control;
//�ô��д��ַ
    assign dm_addr = alu_result;
//store ������дʹ��
    always @ (*) // �ڴ�дʹ���ź�
    begin
        if (MEM_valid && inst_store) // �ô漶��Чʱ,��Ϊ store ����
        begin
            if (ls_word)
            begin
                dm_wen <= 4'b1111; // �洢��ָ�дʹ��ȫ 1
            end
            else
            begin // SB ָ���Ҫ���ݵ�ַ����λ��ȷ����Ӧ��дʹ��
                case (dm_addr[1:0])
                2'b00 : dm_wen <= 4'b0001;
                2'b01 : dm_wen <= 4'b0010;
                2'b10 : dm_wen <= 4'b0100;
                2'b11 : dm_wen <= 4'b1000;
                default : dm_wen <= 4'b0000;
                endcase
            end
        end
        else
        begin
            dm_wen <= 4'b0000;
        end
    end
//store ������д����
    always @ (*) // ���� SB ָ���Ҫ���ݵ�ַ����λ���ƶ� store ���ֽ�����Ӧλ��
    begin
        case (dm_addr[1:0])
        2'b00 : dm_wdata <= store_data;
        2'b01 : dm_wdata <= {16'd0, store_data[7:0],8'd0};
        2'b10 : dm_wdata <= {8'd0, store_data[7:0],16'd0};
        2'b11 : dm_wdata <= {store_data[7:0], 24'd0};
        default : dm_wdata <= store_data;
        endcase
    end
//load ����������
    wire load_sign;
    wire [31:0] load_result;
    assign load_sign = (dm_addr[1:0]==2'd0) ? dm_rdata[ 7] :
    (dm_addr[1:0]==2'd1) ? dm_rdata[15] :
    (dm_addr[1:0]==2'd2) ? dm_rdata[23] : dm_rdata[31] ; 
    assign load_result[7:0] = (dm_addr[1:0]==2'd0) ? dm_rdata[ 7:0 ] : 
    (dm_addr[1:0]==2'd1) ? dm_rdata[15:8 ] : 
    (dm_addr[1:0]==2'd2) ? dm_rdata[23:16] : 
    dm_rdata[31:24] ;
    assign load_result[31:8]= ls_word ? dm_rdata[31:8] : 
    {24{lb_sign & load_sign}};
//-----{load/store �ô�}end
//-----{MEM ִ�����}begin
//�������� RAM Ϊͬ����д��,
//�ʶ� load ָ�ȡ����ʱ����һ����ʱ
//������ַ����һ��ʱ�Ӳ��ܵõ� load ������
//�� mem �ڽ��� load ����ʱ����Ҫ����ʱ�����ȡ������
//����������������ֻ��Ҫһ��ʱ��
    reg MEM_valid_r;
    always @(posedge clk)
    begin
        MEM_valid_r <= MEM_valid;
    end
    assign MEM_over = inst_load ? MEM_valid_r :MEM_valid;
//������� ram Ϊ�첽���ģ��� MEM_valid ���� MEM_over �źţ�
//�� load һ�����
//-----{MEM ִ�����}end
//-----{MEM->WB ����}begin
    wire [31:0] mem_result; //MEM ���� WB �� result Ϊ load ����� ALU ���
    assign mem_result = inst_load ? load_result : alu_result;
    assign MEM_WB_bus = {rf_wen,rf_wdest, // WB ��Ҫʹ�õ��ź�
    mem_result, // ����Ҫд�ؼĴ���������
    pc}; // PC ֵ
//-----{MEM->WB ����}begin
//-----{չʾ MEM ģ��� PC ֵ}begin
    assign MEM_pc = pc;
//-----{չʾ MEM ģ��� PC ֵ}end
endmodule