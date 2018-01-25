#/usr/bin/env python

import caffe
import string
import os
import numpy as np
import struct
from scipy.misc import imread
from PIL import Image
np.set_printoptions(threshold=np.nan)

net = caffe.Net('/opt/caffe/models/bvlc_googlenet/deploy.prototxt' , '/opt/caffe/models/bvlc_googlenet/bvlc_googlenet.caffemodel', caffe.TEST)

layers = ['conv1/7x7_s2', 'conv2/3x3_reduce', 'inception_3a/1x1']
pad = [3,0, 0]
ix = [224,56, 28]
batches = [4,4, 4]
input_d = [3,64, 192]
num_images=4
array_image = np.zeros((num_images,3, 224, 224)).astype(np.float32) 


for i in range(0, num_images-1):
    image_name = 'cars_test/' + "%05d"%(i+1) + '.jpg' 
    img = Image.open(image_name)
    img =  img.resize((224,224), Image.BILINEAR)
    img.save(image_name)
    image = imread(image_name)
    image = image.reshape(1,3,224,224)
    array_image[i] = image

array_image = np.asarray(array_image)
array_image = array_image.reshape(num_images, 3, 224, 224)
net.blobs['data'].data[...] = array_image
net.forward()

num_layer = 0
for layer in layers:
    dirname = string.replace(layer,'/','_')
    if not os.path.exists(dirname):
        os.makedirs(dirname)

    weight_name = dirname  + '/weights'
    weight_file = open(weight_name, 'wb')
    W =  net.params[layer][0].data[...]
    weight_file.write(struct.pack('i' * (1+len(W.shape)), len(W.shape), *W.shape))
    W.tofile(weight_file)
    weight_file.close()

    print "weight_blob shape " + str(W.shape)
    
    b =  net.params[layer][1].data[...]
    bias_name = dirname  + '/biases'
    bias_file = open(bias_name, 'wb')
    bias_file.write(struct.pack('i' * (1+len(b.shape)), len(b.shape), *b.shape))
    b.tofile(bias_file)
    bias_file.close()
    

    print "bias_blob shape " + str(b.shape) 

    input_name = dirname + '/input'

    
    bottom_name = net.bottom_names[layer][0]
    pad_arr = np.zeros((batches[num_layer], input_d[num_layer], ix[num_layer]+2*pad[num_layer], ix[num_layer]+2*pad[num_layer])).astype(np.float32)
    input_blob = net.blobs[bottom_name].data[...]
   
    for i in range(0, batches[num_layer]):
        if (pad[num_layer]>0):
    	    pad_arr[i,:,pad[num_layer]:-pad[num_layer],pad[num_layer]:-pad[num_layer]] = input_blob[i]
	    print "PADDED_INPUT_BLOB" + str(i) 
	    print pad_arr[i]
	    print "INPUT_BLOB" + str(i) 
 	    print input_blob[i]
        else:
            pad_arr = input_blob

    input_file = open(input_name, 'wb')
    input_file.write(struct.pack('i' * (1+len(pad_arr.shape)), len(pad_arr.shape), *pad_arr.shape))
    pad_arr.tofile(input_file)


    print "input_blob shape " + str(input_blob.shape) 
    input_file.close()
    
    output_name = dirname + '/output'
    output_file = open(output_name, 'wb')
    output_blob = net.blobs[layer].data[...]
    output_file.write(struct.pack('i' * (1+len(output_blob.shape)), len(output_blob.shape), *output_blob.shape))
    output_blob.tofile(output_file)
    
    print "output_blob shape " + str(output_blob.shape)
    output_file.close()
    num_layer = num_layer + 1
