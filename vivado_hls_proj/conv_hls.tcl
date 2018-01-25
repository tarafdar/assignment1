
open_project conv_proj
set_top conv_layer 
add_files ../conv_test/conv_layer.cpp
add_files -tb ../conv_test/conv_layer_test.cpp
add_files -tb ../util/shared.cpp
open_solution "solution1"
set_part {xcvu095-ffvc1517-2-e} -tool vivado
create_clock -period 10 -name default
#source "./test/solution1/directives.tcl"
csim_design -compiler gcc
#csynth_design
#cosim_design
#export_design -format ip_catalog
