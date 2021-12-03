import numpy as np
# from PIL import ImageFont, ImageDraw, Image
import cv2
import sys

# for i in sys.argv:
#     print(i)

# # argc
# argc = len(sys.argv)
# print(argc)

SCREEN_WEIDTH = 1600
SCREEN_HEIGHT = 1200
BLOCK_WRIDTH = 200
BLOCK_HEIGHT = 230
b,g,r,a = 0,0,0,0

img = np.zeros((SCREEN_HEIGHT,SCREEN_WEIDTH,3),np.uint8)
img[:] = (0, 0, 0)
cv2.rectangle(img, (200, 100), (1500, 1100), (255, 255, 255), -1)
x = 0
y = 0
for i in sys.argv[1:]:
    if int(i) > 35000 and int(i) < 200:
        red = 0
        green = 0
    elif int(i) > 5000 and int(i) < 50000:
        red = 255
        green = 0
    elif int(i) > 200 and int(i) < 5000:
        red = 0
        green = 255
    else:
        red = 0
        green = 0
    cv2.rectangle(img, (250 + x*BLOCK_WRIDTH+10, 120 + y*BLOCK_HEIGHT+10), (250 + x*BLOCK_WRIDTH + BLOCK_WRIDTH, 120 + y*BLOCK_HEIGHT + BLOCK_HEIGHT), (0, green, red), -1)
    x = x + 1
    if x == 6:
        x = 0
        y = y + 1
    

# fontpath = "./NotoSansCJKtc-Light.otf"
# font = ImageFont.truetype(fontpath, 200) 
# img_pil = Image.fromarray(img)
# draw = ImageDraw.Draw(img_pil)
# # draw.text((500, 500),  "aaaa", font = font, fill = (0, 0, 0, a))
# img = np.array(img_pil)

cv2.imwrite("frame.bmp", img)