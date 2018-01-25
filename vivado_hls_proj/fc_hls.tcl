############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project fc_proj 
set_top fc_layer
add_files ../fc_test/fc_layer.cpp
#add_files -tb /workspace/assignment1/nn_params/fc1/biases
#add_files -tb /workspace/assignment1/nn_params/fc1/input
#add_files -tb /workspace/assignment1/nn_params/fc1/output
#add_files -tb /workspace/assignment1/nn_params/fc1/weights
#add_files -tb /workspace/assignment1/nn_params/fc2/biases
#add_files -tb /workspace/assignment1/nn_params/fc2/input
#add_files -tb /workspace/assignment1/nn_params/fc2/output
#add_files -tb /workspace/assignment1/nn_params/fc2/weights
#add_files -tb /workspace/assignment1/nn_params/fc3/biases
#add_files -tb /workspace/assignment1/nn_params/fc3/input
#add_files -tb /workspace/assignment1/nn_params/fc3/output
#add_files -tb /workspace/assignment1/nn_params/fc3/weights
add_files -tb ../fc_test/fc_layer_test.cpp
add_files -tb ../util/shared.cpp
open_solution "solution1"
set_part {xcvu095-ffvc1517-2-e} -tool vivado
create_clock -period 10 -name default
#source "./test/solution1/directives.tcl"
csim_design -compiler gcc
csynth_design
cosim_design
#export_design -format ip_catalog
