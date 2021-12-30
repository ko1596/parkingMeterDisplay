import cv2
import time
import numpy as np
import sys
import os
from PIL import ImageFont, ImageDraw, Image

WORK_DIR_PATH = "/home/user/printScreen/"         #work dir
# WORK_DIR_PATH = "/home/root/display_HK/"

if os.path.isdir(WORK_DIR_PATH):
    print("set work dir: " + WORK_DIR_PATH)
else:
    print("Can't find dir")

FONT_PATH = WORK_DIR_PATH + "NotoSansCJKtc-Bold.otf"    #font file

if os.path.isfile(FONT_PATH):
    print ("reading font: " + FONT_PATH)
else:
    print ("no font file found")

GENERATED_IMG_NAME = WORK_DIR_PATH + "frame.jpg"        #output frame name

inputImg = WORK_DIR_PATH + sys.argv[1] + ".png"

if os.path.isfile(inputImg):
    print ("reading image: " + inputImg)
else:
    print ("no image found")

img = cv2.imread(inputImg)

font = ImageFont.truetype(FONT_PATH, 45)
img_pil = Image.fromarray(img)
draw = ImageDraw.Draw(img_pil)
text = time.strftime("%Y-%m-%d %H:%M", time.localtime())

w, h = draw.textsize(text, font)

draw.text(((768-w)/2, (1024-65)),  text, font = font, fill = (255, 255, 255, 0))

img = np.array(img_pil)

print("generated: " + GENERATED_IMG_NAME)
cv2.imwrite(GENERATED_IMG_NAME, img)