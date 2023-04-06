`timescale 1ns / 1ps
//**************************************************************
module multi_cycle_cpu_display( // ������ cpu
	//ʱ���븴λ�ź�
	input clk,
	input resetn,	//��׺"n"����͵�ƽ��Ч12
	//���忪�أ����ڲ������� clk��ʵ�ֵ���ִ��
	input btn_clk,
	//��������ؽӿڣ�����Ҫ����
	output lcd_rst,
	output lcd_cs,
	output lcd_rs,
	output lcd_wr,
	output lcd_rd,
	inout[15:0] lcd_data_io,
	output lcd_bl_ctr,
	inout ct_int,
	inout ct_sda,
	output ct_scl,
	output ct_rstn
	);
	//	{ʱ�Ӻ͸�λ�ź�}begin
    wire cpu_clk;	//������ CPU ��ʹ�����忪����Ϊʱ�ӣ���ʵ�ֵ���ִ��
    reg btn_clk_r1;	
    reg btn_clk_r2;	
    always @(posedge clk)
    begin
        if (!resetn)
        begin
            btn_clk_r1<= 1'b0;
        end
        else
        begin
            btn_clk_r1 <= ~btn_clk;
        end

    btn_clk_r2 <= btn_clk_r1;
end

    wire clk_en;
    assign clk_en = !resetn || (!btn_clk_r1 && btn_clk_r2);
    BUFGCE cpu_clk_cg(.I(clk),.CE(clk_en),.O(cpu_clk));
    //	{ʱ�Ӻ͸�λ�ź�}end
    //	{���ö����� CPU ģ��}begin
    //������ FPGA	������ʾ���	
    wire [ 4:0]	rf_addr;	//ɨ��Ĵ����ѵĵ�ַ
    wire [31:0]	rf_data;	//�Ĵ����Ѵӵ��Զ˿ڶ���������
    reg [31:0]	mem_addr;	//Ҫ�۲���ڴ��ַ
    wire [31:0]	mem_data;	//�ڴ��ַ��Ӧ������
    wire [31:0]	IF_pc;	//IF ģ��� PC
    wire [31:0]	IF_inst;	//IF ģ��ȡ����ָ��
    wire [31:0]	ID_pc;	//ID ģ��� PC
    wire [31:0]	EXE_pc;	//EXE ģ��� PC
    wire [31:0]	MEM_pc;	//MEM ģ��� PC
    wire [31:0]	WB_pc;	//WB ģ��� PC
    wire [31:0] display_state; //չʾ CPU ��ǰ״̬
    multi_cycle_cpu cpu(
    .clk	(cpu_clk ),
    .resetn (resetn ),
    
    .rf_addr (rf_addr ),
    .mem_addr(mem_addr),
    .rf_data (rf_data ),
    .mem_data(mem_data),
    .IF_pc	(IF_pc	),
    .IF_inst (IF_inst ),
    .ID_pc	(ID_pc	),
    .EXE_pc (EXE_pc ),
    .MEM_pc (MEM_pc ),
    .WB_pc	(WB_pc	),
    .display_state (display_state)
    );
    //	{���õ����� CPU ģ��}end
    
    //	{���ô�����ģ��}begin	//
    //	{ʵ����������}begin
    //��С�ڲ���Ҫ����
    reg	display_valid;
    reg [39:0] display_name;
    reg [31:0] display_value;
    wire [5 :0] display_number;
    wire	input_valid;
    wire [31:0] input_value;
    
    lcd_module lcd_module(
    .clk	(clk	),
    .resetn	(resetn	),

//���ô������Ľӿ�
    .display_valid (display_valid ),
    .display_name	(display_name ),
    .display_value (display_value ),
    .display_number (display_number),
    .input_valid	(input_valid	),
    .input_value	(input_value	),
	
	//lcd ��������ؽӿڣ�����Ҫ����	
	.lcd_rst	(lcd_rst	),
	.lcd_cs	(lcd_cs	),
	.lcd_rs	(lcd_rs	),
	.lcd_wr	(lcd_wr	),
	.lcd_rd	(lcd_rd	),
	.lcd_data_io	(lcd_data_io	),
	.lcd_bl_ctr	(lcd_bl_ctr	),
	.ct_int	(ct_int	),
	.ct_sda	(ct_sda	),
	.ct_scl	(ct_scl	),
	.ct_rstn	(ct_rstn	)
);		


	//	{�Ӵ�������ȡ����}begin
	//����ʵ����Ҫ��������޸Ĵ�С�ڣ�
	//�����ÿһ���������룬��д����һ�� always ��
	always @(posedge clk)
	begin
	if (!resetn)
	begin
	mem_addr <= 32'd0;
	end
	else if (input_valid)
	begin
	mem_addr <= input_value;
	end
	end
	assign rf_addr = display_number-6'd11;
	//	{�Ӵ�������ȡ����}end
	
	//	{�������������ʾ}begin
	//������Ҫ��ʾ�����޸Ĵ�С�ڣ�
	//�������Ϲ��� 44 ����ʾ���򣬿���ʾ 44 �� 32 λ����
	//44 ����ʾ����� 1 ��ʼ��ţ����Ϊ 1~44��
	always @(posedge clk)
	begin
	if (display_number >6'd10 && display_number <6'd43 )
	begin //��� 5~36 ��ʾ 32 ��ͨ�üĴ�����ֵ
	display_valid <= 1'b1;
	display_name[39:16] <= "REG";
	display_name[15: 8] <= {4'b0011,3'b000,rf_addr[4]};
	display_name[7 : 0] <= {4'b0011,rf_addr[3:0]};
	display_value	<= rf_data;
	end
	else
	begin
	case(display_number)
	6'd1 : //��ʾ IF ģ��� PC
	begin
	display_valid <= 1'b1;
	display_name <= "IF_PC";
	display_value <= IF_pc;
	end
	6'd2 : //��ʾ IF ģ���ָ��
	begin
	display_valid <= 1'b1;
	display_name <= "IF_IN";
	display_value <= IF_inst;
	end
	6'd3 : //��ʾ ID ģ��� PC
	begin
	display_valid <= 1'b1;
	display_name <= "ID_PC";
	display_value <= ID_pc;
	end
	6'd4 : //��ʾ EXE ģ��� PC
	begin
	display_valid <= 1'b1;
	display_name <= "EXEPC";
	display_value <= EXE_pc;
	end
	6'd5 : //��ʾ MEM ģ��� PC
	begin
	display_valid <= 1'b1;
	display_name <= "MEMPC";
	display_value <= MEM_pc;
	end
	6'd6 : //��ʾ WB ģ��� PC
	begin
	display_valid <= 1'b1;
	display_name <= "WB_PC";
	display_value <= WB_pc;
	end
	6'd7 : //��ʾҪ�۲���ڴ��ַ
	begin
	display_valid <= 1'b1;
	display_name <= "MADDR";
	display_value <= mem_addr;
	end
	6'd8 : //��ʾ���ڴ��ַ��Ӧ������
	begin
	display_valid <= 1'b1;
	display_name <= "MDATA";
	display_value <= mem_data;
	end
	6'd9 : //��ʾ CPU ��ǰ״̬
	begin
	display_valid <= 1'b1;
	display_name <= "STATE";
    display_value <= display_state;
    end default :
    begin
    display_valid <= 1'b0;
    display_name<= 40'd0;
    display_value <= 32'd0;
    end
endcase
end
end
endmodule