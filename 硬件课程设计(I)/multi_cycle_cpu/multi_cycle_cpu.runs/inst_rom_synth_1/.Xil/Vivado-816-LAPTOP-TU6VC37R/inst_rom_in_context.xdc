set_property -quiet CLOCK_PERIOD_OOC_TARGET 20.000 [get_ports -no_traverse -quiet clka]
set_property -quiet IS_IP_OOC_CELL TRUE [get_cells -of [get_ports -no_traverse -quiet addra[0]]]
