import os
from PIL import Image

for filename in os.listdir(r'C:\Users\DFZ\Documents\code\ads\project\PJ1\new_pictures'):
    if filename != 'changesize.py':
        im = Image.open(filename)
        size = im.size
        print(size)
        newSize = (int(size[0]/2), int(size[1]/2))
        print(newSize)
        im.resize(newSize).save(filename)
        # im.save(filename)

