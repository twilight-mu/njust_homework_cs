onbreak {quit -force}
onerror {quit -force}

asim -t 1ps +access +r +m+data_ram -L xpm -L blk_mem_gen_v8_4_4 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip -O5 xil_defaultlib.data_ram xil_defaultlib.glbl

do {wave.do}

view wave
view structure

do {data_ram.udo}

run -all

endsim

quit -force
