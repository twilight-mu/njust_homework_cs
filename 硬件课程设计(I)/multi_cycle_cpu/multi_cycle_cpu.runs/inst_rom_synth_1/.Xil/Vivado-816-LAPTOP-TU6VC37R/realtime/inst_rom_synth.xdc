set_property SRC_FILE_INFO {cfile:{d:/Vivado Install/hardware_design/multi_cycle_cpu/multi_cycle_cpu.srcs/sources_1/ip/inst_rom/inst_rom_ooc.xdc} rfile:../../../../../multi_cycle_cpu.srcs/sources_1/ip/inst_rom/inst_rom_ooc.xdc id:1 order:EARLY scoped_inst:U0} [current_design]
set_property SRC_FILE_INFO {cfile:{D:/Vivado Install/hardware_design/multi_cycle_cpu/multi_cycle_cpu.runs/inst_rom_synth_1/dont_touch.xdc} rfile:../../../dont_touch.xdc id:2} [current_design]
set_property src_info {type:SCOPED_XDC file:1 line:53 export:INPUT save:INPUT read:FILTER_OUT_OF_CONTEXT} [current_design]
create_clock -period 20.000 -name TS_CLKA [get_ports clka]
set_property src_info {type:SCOPED_XDC file:1 line:54 export:INPUT save:INPUT read:FILTER_OUT_OF_CONTEXT} [current_design]
set_property HD.CLK_SRC BUFGCTRL_X0Y0 [get_ports clka]
set_property src_info {type:XDC file:2 line:9 export:INPUT save:INPUT read:READ} [current_design]
set_property DONT_TOUCH true [get_cells U0]
