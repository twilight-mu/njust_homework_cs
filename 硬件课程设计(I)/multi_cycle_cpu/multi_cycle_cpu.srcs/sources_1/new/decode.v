`timescale 1ns / 1ps
module decode( // ���뼶
    input ID_valid, // ���뼶��Ч�ź�
    input [ 63:0] IF_ID_bus_r, // IF->ID ����
    input [ 31:0] rs_value, // ��һԴ������ֵ
    input [ 31:0] rt_value, // �ڶ�Դ������ֵ
    output [ 4:0] rs, // ��һԴ��������ַ
    output [ 4:0] rt, // �ڶ�Դ��������ַ
    output [ 32:0] jbr_bus, // ��ת����
    output jbr_not_link,// ָ��Ϊ��ת��ָ֧��,�ҷ� link ��ָ��
    output ID_over, // ID ģ��ִ�����
    output [149:0] ID_EXE_bus, // ID->EXE ����
    //չʾ PC
    output [ 31:0] ID_pc
    );
//-----{IF->ID ����}begin
    wire [31:0] pc;
    wire [31:0] inst;
    assign {pc, inst} = IF_ID_bus_r; // IF->ID ���ߴ�
//-----{IF->ID ����}end
//-----{ָ������}begin
    wire [5:0] op;
    wire [4:0] rd;
    wire [4:0] sa;
    wire [5:0] funct;
    wire [15:0] imm;
    wire [15:0] offset;
    wire [25:0] target;
    assign op = inst[31:26]; // ������
    assign rs = inst[25:21]; // Դ������ 1
    assign rt = inst[20:16]; // Դ������ 2
    assign rd = inst[15:11]; // Ŀ�������
    assign sa = inst[10:6]; // �����򣬿��ܴ��ƫ����
    assign funct = inst[5:0]; // ������
    assign imm = inst[15:0]; // ������
    assign offset = inst[15:0]; // ��ַƫ����
    assign target = inst[25:0]; // Ŀ���ַ
// ʵ��ָ���б�
    wire inst_ADDU, inst_SUBU , inst_SLT , inst_AND;
    wire inst_NOR , inst_OR , inst_XOR , inst_SLL;
    wire inst_SRL , inst_ADDIU, inst_BEQ , inst_BNE;
    wire inst_LW , inst_SW , inst_LUI , inst_J;
    wire inst_SLTU, inst_JALR , inst_JR , inst_SLLV;
    wire inst_SRA , inst_SRAV , inst_SRLV, inst_SLTIU;
    wire inst_SLTI, inst_BGEZ , inst_BGTZ, inst_BLEZ;
    wire inst_BLTZ, inst_LB , inst_LBU , inst_SB;
    wire inst_ANDI, inst_ORI , inst_XORI, inst_JAL;
    wire op_zero; // ������ȫ 0
    wire sa_zero; // sa ��ȫ 0
    assign op_zero = ~(|op);
    assign sa_zero = ~(|sa);
    assign inst_ADDU = op_zero & sa_zero & (funct == 6'b100001);//�޷��żӷ�
    assign inst_SUBU = op_zero & sa_zero & (funct == 6'b100011);//�޷��ż���
    assign inst_SLT = op_zero & sa_zero & (funct == 6'b101010);//С������λ
    assign inst_SLTU = op_zero & sa_zero & (funct == 6'b101011);//�޷���С����
    assign inst_JALR = op_zero & (rt==5'd0) & (rd==5'd31)& sa_zero & (funct == 6'b001001); //��ת�Ĵ���������
    assign inst_JR = op_zero & (rt==5'd0) & (rd==5'd0 )& sa_zero & (funct == 6'b001000); //��ת�Ĵ���
    assign inst_AND = op_zero & sa_zero & (funct == 6'b100100);//������
    assign inst_NOR = op_zero & sa_zero & (funct == 6'b100111);//�������
    assign inst_OR = op_zero & sa_zero & (funct == 6'b100101);//������
    assign inst_XOR = op_zero & sa_zero & (funct == 6'b100110);//�������
    assign inst_SLL = op_zero & (rs==5'd0) & (funct == 6'b000000);//�߼�����
    assign inst_SLLV = op_zero & sa_zero & (funct == 6'b000100);//�����߼�����
    assign inst_SRA = op_zero & (rs==5'd0) & (funct == 6'b000011);//��������
    assign inst_SRAV = op_zero & sa_zero & (funct == 6'b000111);//������������
    assign inst_SRL = op_zero & (rs==5'd0) & (funct == 6'b000010);//�߼�����
    assign inst_SRLV = op_zero & sa_zero & (funct == 6'b000110);//�����߼�����
    assign inst_ADDIU = (op == 6'b001001); //�������޷��żӷ�
    assign inst_SLTI = (op == 6'b001010); //С������������λ
    assign inst_SLTIU = (op == 6'b001011); //�޷���С������������λ
    assign inst_BEQ = (op == 6'b000100); //�ж������ת
    assign inst_BGEZ = (op == 6'b000001) & (rt==5'd1); //���ڵ��� 0 ��ת
    assign inst_BGTZ = (op == 6'b000111) & (rt==5'd0); //���� 0 ��ת
    assign inst_BLEZ = (op == 6'b000110) & (rt==5'd0); //С�ڵ��� 0 ��ת
    assign inst_BLTZ = (op == 6'b000001) & (rt==5'd0); //С�� 0 ��ת
    assign inst_BNE = (op == 6'b000101); //�жϲ�����ת
    assign inst_LW = (op == 6'b100011); //���ڴ�װ����
    assign inst_SW = (op == 6'b101011); //���ڴ�洢��
    assign inst_LB = (op == 6'b100000); //load �ֽڣ�������չ��
    assign inst_LBU = (op == 6'b100100); //load �ֽڣ��޷�����չ��
    assign inst_SB = (op == 6'b101000); //���ڴ�洢�ֽ�
    assign inst_ANDI = (op == 6'b001100); //��������
    assign inst_LUI = (op == 6'b001111) & (rs==5'd0); //������װ�ظ߰��ֽ�
    assign inst_ORI = (op == 6'b001101); //��������
    assign inst_XORI = (op == 6'b001110); //���������
    assign inst_J = (op == 6'b000010); //��ת
    assign inst_JAL = (op == 6'b000011); //��ת������
    //��ת��ָ֧��
    wire inst_jr; //�Ĵ�����תָ��
    wire inst_j_link;//������תָ��
    assign inst_jr = inst_JALR | inst_JR;
    assign inst_j_link = inst_JAL | inst_JALR;
    assign jbr_not_link= inst_J | inst_JR | inst_BEQ | inst_BNE | inst_BGEZ | inst_BGTZ | inst_BLEZ | inst_BLTZ;//ȫ���� link ����תָ��
    //load store
    wire inst_load;
    wire inst_store;
    assign inst_load = inst_LW | inst_LB | inst_LBU; // load ָ��
    assign inst_store = inst_SW | inst_SB; // store ָ��
    //alu ��������
    wire inst_add, inst_sub, inst_slt,inst_sltu;
    wire inst_and, inst_nor, inst_or, inst_xor;
    wire inst_sll, inst_srl, inst_sra,inst_lui;
    assign inst_add = inst_ADDU | inst_ADDIU | inst_load | inst_store | inst_j_link; // ���ӷ�
    assign inst_sub = inst_SUBU; // ����
    assign inst_slt = inst_SLT | inst_SLTI; // �з���С����λ
    assign inst_sltu= inst_SLTIU | inst_SLTU; // �޷���С����λ
    assign inst_and = inst_AND | inst_ANDI; // �߼���
    assign inst_nor = inst_NOR; // �߼����
    assign inst_or = inst_OR | inst_ORI; // �߼���
    assign inst_xor = inst_XOR | inst_XORI; // �߼����
    assign inst_sll = inst_SLL | inst_SLLV; // �߼�����
    assign inst_srl = inst_SRL | inst_SRLV; // �߼�����
    assign inst_sra = inst_SRA | inst_SRAV; // ��������
    assign inst_lui = inst_LUI; // ������װ�ظ�λ
//ʹ�� sa ����Ϊƫ��������λָ��
    wire inst_shf_sa;
    assign inst_shf_sa = inst_SLL | inst_SRL | inst_SRA;
//������������չ��ʽ����
    wire inst_imm_zero; //������ 0 ��չ
    wire inst_imm_sign; //������������չ
    assign inst_imm_zero = inst_ANDI | inst_LUI | inst_ORI | inst_XORI;
    assign inst_imm_sign = inst_ADDIU | inst_SLTI | inst_SLTIU | inst_load | inst_store;
//����Ŀ�ļĴ����ŷ���
    wire inst_wdest_rt; // �Ĵ�����д���ַΪ rt ��ָ��
    wire inst_wdest_31; // �Ĵ�����д���ַΪ 31 ��ָ��
    wire inst_wdest_rd; // �Ĵ�����д���ַΪ rd ��ָ��
    assign inst_wdest_rt = inst_imm_zero | inst_ADDIU | inst_SLTI | inst_SLTIU | inst_load;
    assign inst_wdest_31 = inst_JAL;
    assign inst_wdest_rd = inst_ADDU | inst_SUBU | inst_SLT | inst_SLTU | inst_JALR | inst_AND | inst_NOR | inst_OR
    | inst_XOR | inst_SLL | inst_SLLV | inst_SRA | inst_SRAV | inst_SRL | inst_SRLV;
//-----{ָ������}end
//-----{��ָ֧��ִ��}begin
//��������ת
    wire j_taken;
    wire [31:0] j_target;
    assign j_taken = inst_J | inst_JAL | inst_jr;
//�Ĵ�����ת��ַΪ rs_value,������תΪ{pc[31:28],target,2'b00}
    assign j_target = inst_jr ? rs_value :
    {pc[31:28],target,2'b00};
//branch ָ��
    wire rs_equql_rt;
    wire rs_ez;
    wire rs_ltz;
    assign rs_equql_rt = (rs_value == rt_value); // GPR[rs]==GPR[rt]
    assign rs_ez = ~(|rs_value); // rs �Ĵ���ֵΪ 0
    assign rs_ltz = rs_value[31]; // rs �Ĵ���ֵС�� 0
    wire br_taken;
    wire [31:0] br_target;
    assign br_taken = inst_BEQ & rs_equql_rt // �����ת
    | inst_BNE & ~rs_equql_rt // ������ת
    | inst_BGEZ & ~rs_ltz // ���ڵ��� 0 ��ת
    | inst_BGTZ & ~rs_ltz & ~rs_ez // ���� 0 ��ת
    | inst_BLEZ & (rs_ltz | rs_ez) // С�ڵ��� 0 ��ת
    | inst_BLTZ & rs_ltz; // С�� 0 ��ת
// ��֧��תĿ���ַ��PC=PC+offset<<2
    assign br_target[31:2] = pc[31:2] + {{14{offset[15]}}, offset};
    assign br_target[1:0] = pc[1:0];
//jump and branch ָ��
    wire jbr_taken;
    wire [31:0] jbr_target;
    assign jbr_taken = j_taken | br_taken;
    assign jbr_target = j_taken ? j_target : br_target;
//ID �� IF ����ת����
    assign jbr_bus = {jbr_taken, jbr_target};
//-----{��ָ֧��ִ��}end
//-----{ID ִ�����}begin
//�����Ƕ����ڵģ��������������
//�� ID ģ��һ�ľ���������в���
//�� ID_valid ���� ID_over �ź�
    assign ID_over = ID_valid;
//-----{ID ִ�����}end
//-----{ID->EXE ����}begin
//EXE ��Ҫ�õ�����Ϣ
//ALU ����Դ�������Ϳ����ź�
    wire [11:0] alu_control;
    wire [31:0] alu_operand1;
    wire [31:0] alu_operand2;
//��ν������ת�ǽ���ת���ص� PC ֵ��ŵ� 31 �żĴ�����
//�ڶ����� CPU ��������ӳٲۣ���������ת��Ҫ���� PC+4����ŵ� 31 �żĴ�����
    assign alu_operand1 = inst_j_link ? pc :
    inst_shf_sa ? {27'd0,sa} : rs_value;
    assign alu_operand2 = inst_j_link ? 32'd4 :
    inst_imm_zero ? {16'd0, imm} :
    inst_imm_sign ? {{16{imm[15]}}, imm} : rt_value;  
    assign alu_control = {inst_add, // ALU �����룬���ȱ���
    inst_sub,
    inst_slt,
    inst_sltu,
    inst_and,
    inst_nor,
    inst_or,
    inst_xor,
    inst_sll,
    inst_srl,
    inst_sra,
    inst_lui};
//�ô���Ҫ�õ��� load/store ��Ϣ
    wire lb_sign; //load һ�ֽ�Ϊ�з��� load
    wire ls_word; //load/store Ϊ�ֽڻ�����,0:byte;1:word
    wire [3:0] mem_control; //MEM ��Ҫʹ�õĿ����ź�
    wire [31:0] store_data; //store �����Ĵ������
    assign lb_sign = inst_LB;
    assign ls_word = inst_LW | inst_SW;
    assign mem_control = {inst_load,
    inst_store,
    ls_word,
    lb_sign };
//д����Ҫ�õ�����Ϣ
    wire rf_wen; //д�صļĴ���дʹ��
    wire [4:0] rf_wdest; //д�ص�Ŀ�ļĴ���
    assign rf_wen = inst_wdest_rt | inst_wdest_31 |
    inst_wdest_rd;
    assign rf_wdest = inst_wdest_rt ? rt ://�ڲ�д�Ĵ�����ʱ������Ϊ0
    inst_wdest_31 ? 5'd31 :
    inst_wdest_rd ? rd : 5'd0;
    assign store_data = rt_value;
    assign ID_EXE_bus = {alu_control,alu_operand1,alu_operand2,//EXE ��Ҫʹ�õ���Ϣ
    mem_control,store_data, //MEM ��Ҫʹ�õ��ź�
    rf_wen, rf_wdest, //WB ��Ҫʹ�õ��ź�
    pc}; //PC ֵ
//-----{ID->EXE ����}end
//-----{չʾ ID ģ��� PC ֵ}begin
    assign ID_pc = pc;
//-----{չʾ ID ģ��� PC ֵ}end
endmodule