`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:

// Design Name:   single_cycle_cpu
// Module Name:   F:/new_lab/6_single_cycle_cpu/tb.v
// Project Name:  single_cycle_cpu
//
// Verilog Test Fixture created by ISE for module: single_cycle_cpu
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module testbench;

    // Inputs
    reg clk;
    reg resetn;
    reg [4:0] rf_addr;
    reg [31:0] mem_addr;

    // Outputs
    wire [31:0] rf_data;
    wire [31:0] mem_data;
    wire [31:0] IF_pc;
    wire [31:0] IF_inst;
    wire [31:0] ID_pc;
    wire [31:0] EXE_pc;
    wire [31:0] MEM_pc;
    wire [31:0] WB_pc;
    wire [31:0] display_state;

    // Instantiate the Unit Under Test (UUT)
    multi_cycle_cpu uut (
        .clk(clk), 
        .resetn(resetn), 
        .rf_addr(rf_addr), 
        .mem_addr(mem_addr), 
        .rf_data(rf_data), 
        .mem_data(mem_data), 
        //.cpu_pc(cpu_pc), 
        //.cpu_inst(cpu_inst)
        .IF_pc (IF_pc),
        .IF_inst (IF_inst),
        .ID_pc (ID_pc),
        .EXE_pc (EXE_pc),
        .MEM_pc (MEM_pc),
        .WB_pc (WB_pc),
        .display_state(display_state)
    );

    initial begin
        // Initialize Inputs
        clk = 0;
        resetn = 0;
        rf_addr = 0;//11
        mem_addr = 32'h00000000;//28
        // Wait 100 ns for global reset to finish
        #10
        resetn = 1;
        
      //if(!WB_pc)
        //    rf_addr=1;
   
        // Add stimulus here
          //#5
          //rf_addr=1;
          //#10
          //rf_addr=4;
          //#15
          //rf_addr=6;
          //#5
          //rf_addr=8;
          //#5
          //rf_addr=10;
    end
    always #5 clk=~clk;
    always@(posedge clk)
    begin
       //rf_addr=rf_addr+1;
      //#5;
      //end
       if(WB_pc==32'h00000008)
       begin
                rf_addr=2;
                #5;
       end     
       if(WB_pc==32'h0000000c)
       begin
                 rf_addr=3;
                 #5;
       end      
       if(WB_pc==32'h00000010)
       begin
                 rf_addr=4;
                 #5;
       end       
       if(WB_pc==32'h00000014)
       begin
                 rf_addr=25;
                 #5;
       end
       if(WB_pc==32'h00000018)
       begin
                 rf_addr=5;
                 #5;
       end     
       if(WB_pc==32'h0000001C)
       begin
                 mem_addr=32'h00000014;
                 #5;
       end
       if(WB_pc==32'h00000020)
       begin
                 rf_addr=6;
                 #5;
       end
       if(WB_pc==32'h00000024)
       begin
                 rf_addr=7;
                 #5;
       end
       if(WB_pc==32'h00000028)
       begin
                 rf_addr=8;
                 #5;
       end
       if(WB_pc==32'h0000002C)
       begin
                 mem_addr=32'h0000001C;
                 #5;
       end
       if(WB_pc==32'h00000030)
       begin
                 rf_addr=9;
                 #5;
       end  
       if(WB_pc==32'h00000034)
       begin
                 rf_addr=1;
                 #5;
       end  
       if(WB_pc==32'h00000038)
       begin
                 rf_addr=10;
                 #5;
       end  
       if(WB_pc==32'h0000003C)
       begin
                 rf_addr=11;
                 #5;
       end
       if(WB_pc==32'h00000040)
       begin
                 mem_addr=32'h00000024;
                 #5;
       end
       if(WB_pc==32'h00000044)
       begin
                 mem_addr=32'h00000018;
                 #5;
       end
       
       if(WB_pc==32'h00000068)
       begin
                 rf_addr=14;
                 #5;
       end
       if(WB_pc==32'h0000006C)
       begin
                 rf_addr=15;
                 #5;
       end
       if(WB_pc==32'h00000070)
       begin
                 rf_addr=16;
                 #5;
       end
       if(WB_pc==32'h00000074)
       begin
                 rf_addr=16;
                 #5;
       end
       if(WB_pc==32'h00000078)
       begin
                 rf_addr=11;
                 #5;
       end
       if(WB_pc==32'h0000007C)
       begin
                 rf_addr=28;
                 #5;
       end
       if(WB_pc==32'h00000080)
       begin
                 mem_addr=32'h00000015;
                 #5;
       end
       if(WB_pc==32'h00000084)
       begin
                 rf_addr=18;
                 #5;
       end
       if(WB_pc==32'h00000088)
       begin
                 rf_addr=19;
                 #5;
       end
       if(WB_pc==32'h0000008C)
       begin
                 rf_addr=24;
                 #5;
       end
       if(WB_pc==32'h00000090)
       begin
                 rf_addr=20;
                 #5;
       end
       if(WB_pc==32'h00000094)
       begin
                 rf_addr=21;
                 #5;
       end
       if(WB_pc==32'h00000098)
       begin
                 rf_addr=22;
                 #5;
       end                     
    end
endmodule

