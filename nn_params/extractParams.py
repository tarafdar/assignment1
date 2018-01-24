#/usr/bin/env python

import caffe
import string
import os
import numpy as np
from scipy.misc import imread
from PIL import Image

net = caffe.Net('/opt/caffe/models/bvlc_googlenet/deploy.prototxt' , '/opt/caffe/models/bvlc_googlenet/bvlc_googlenet.caffemodel', caffe.TEST)

layers = ['conv1/7x7_s2']
layers = ['conv1/7x7_s2', 'conv2/3x3_reduce']
pad = [3,0]


for layer in layers:
    dirname = string.replace(layer,'/','_')
    if not os.path.exists(dirname):
        os.makedirs(dirname)

    weight_name = dirname  + '/weights'
    weight_file = open(weight_name, 'wb')
    W =  net.params[layer][0].data[...]
    W.tofile(weight_file)
    print "weight_blob shape " + str(W.shape) 
    weight_file.close()
    
    bias_name = dirname  + '/biases'
    bias_file = open(bias_name, 'wb')
    b =  net.params[layer][1].data[...]
    b.tofile(bias_file)
    print "bias_blob shape " + str(b.shape) 
    bias_file.close()

    input_name = dirname + '/input'
    input_file = open(input_name, 'wb')

    i = 1


    image_name = 'cars_test/' + str(i).zfill(5) + '.jpg' 
    img = Image.open(image_name)
    img =  img.resize((224,224), Image.BILINEAR)
    img.save(image_name)
    
    image = imread(image_name)
    image = image.reshape(1,3,224,224)
    array_image = np.asarray([image])
    net.blobs['data'].data[...] = array_image
    net.forward()
    
    
    bottom_name = net.bottom_names[layer][0]
    pad_arr = np.zeros((1, 3, 224+2*pad[i], 224+2*pad[i])).astype(np.float32)
    if (pad[i]>0):
    	pad_arr[:,:,pad[i]:-pad[i],pad[i]:-pad[i]] = net.blobs[bottom_name].data 
    input_blob = pad_arr
    input_blob.tofile(input_file)

    print "input_blob shape " + str(input_blob.shape) 
    input_file.close()
    
    output_name = dirname + '/output'
    output_file = open(output_name, 'wb')
    output_blob = net.blobs[layer].data[...]
    output_blob.tofile(output_file)
    print "output_blob shape " + str(output_blob.shape)
    output_file.close()

